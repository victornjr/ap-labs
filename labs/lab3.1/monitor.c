#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <sys/inotify.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logger.h"

int inotifyFd;

static void /* Display information from inotify_event structure */
displayInotifyEvent(struct inotify_event *i)
{
	printf("    wd =%2d; ", i->wd);
	if (i->cookie > 0)
			printf("cookie =%4d; ", i->cookie);

	printf("mask = \n");
	if (i->mask & IN_CREATE)        infof("IN_CREATE ");
	if (i->mask & IN_DELETE)        infof("IN_DELETE ");
	if (i->mask & IN_MOVED_FROM)    infof("IN_MOVED_FROM ");
	if (i->mask & IN_MOVED_TO)      infof("IN_MOVED_TO ");
	printf("\n");

	if (i->len > 0)
		printf("        name = %s\n", i->name);
}

static int
addInotifyWatchToFiles(const char *filePath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{

	int wd = inotify_add_watch(inotifyFd, filePath, IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);

	if (wd == -1) {
		errorf("inotify_add_watch not added\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(int argc, char *argv[])
{
	char buf[BUF_LEN] __attribute__ ((aligned(8)));
	ssize_t numRead;
	char *p;
	struct inotify_event *event;

	inotifyFd = inotify_init();
	if (inotifyFd == -1) {
		errorf("couldn't create inotifyFd");
		exit(EXIT_FAILURE);
	}

	if (argc < 2){
		errorf("Usage: %s pathname...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (nftw(argv[1], addInotifyWatchToFiles, 20, FTW_PHYS) == -1) {
		errorf("nftw failure");
		exit(EXIT_FAILURE);
	}

	for (;;) {		/* Read events forever */
		numRead = read(inotifyFd, buf, BUF_LEN);
		if (numRead == 0) {
			panicf("read() from inotify fd returned 0!");
			exit(EXIT_FAILURE);
		}
		if (numRead == -1) {
			errorf("read");
			exit(EXIT_FAILURE);
		}

		printf("Read %ld bytes from inotify fd\n", (long) numRead);

		for (p = buf; p < buf + numRead;) {
			event = (struct inotify_event *)p;
			displayInotifyEvent(event);

			p += sizeof(struct inotify_event) + event->len;
		}

		inotifyFd = inotify_init();
		if (nftw(argv[1], addInotifyWatchToFiles, 20, FTW_PHYS) == -1) {
			errorf("nftw failure");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}
