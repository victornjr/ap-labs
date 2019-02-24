#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

	int main(int argc, char **argv)
	{
		if (argc <= 1) {
			printf("Usage: ./broadcast This is the message\n");
		}

		size_t sizeMsg = 0;
		for (int i = 1; i < argc; i++) {
			sizeMsg += strlen(argv[i]) + 1;
		}

		char *fullMsg;
		fullMsg = calloc(sizeMsg, sizeof(char));
		fullMsg[0] = '\0';

		for (int i = 1; i < argc; i++) {
			strcat(fullMsg, argv[i]);
			strcat(fullMsg, " ");
		}
		fullMsg[sizeMsg - 1] = '\n';


		struct dirent *de;
		//char path[] = "ap-labs/";
		char *path = "/dev/pts/";
		DIR *dr;

		dr = opendir(path);

		if (dr == NULL) {
			perror("Could not open current directory\n");
			return -1;
		}

		char *pathpts;
		size_t c, len;
		int flag = 0;
		int fd;
		int i = 0;
		while ((de = readdir(dr)) != NULL) {
			len = strlen(de->d_name);

			for (c = de->d_name[i]; i < strlen(de->d_name); i++) {
				if (isdigit(c) != 0) {
					continue;
				} else {
					flag = -1;
					break;
				}
			}
			if (flag == -1) {
				flag = 0;
				continue;
			}

			if ((pathpts =
			     calloc((strlen(de->d_name) + strlen(path)) + 1,
				    sizeof(char))) == NULL) {
				perror("There was an error when finding/writing the file");
			} else {
				pathpts[0] = '\0';
				strcat(pathpts, path);
				strcat(pathpts, de->d_name);
			}

			fd = open(pathpts, O_WRONLY | O_NOCTTY | O_NONBLOCK | O_ASYNC);
			if (fd == -1) {
				perror("Could not open the file");
			}
			write(fd, fullMsg, sizeMsg);
			close(fd);
		}

		closedir(dr);
		return -1;
	}

