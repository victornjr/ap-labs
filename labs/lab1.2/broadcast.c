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
	if (argc == 1) {
		char message[] = "Please insert a message after the prgram name to send it\nExample: ./broadcast This is the message";
		write(1,message,strlen(message));
	}
	int sizeMsg = 0;
	for (int i = 1; i < argc; i++) {
		sizeMsg += strlen(argv[i]) + 1;
	}

	char *completeStr = (char *)malloc(sizeMsg);
	completeStr[0] = '\n';

	int i = argc;
	while(--argc > 0){
		strcat(completeStr, argv[i - argc]);
		strcat(completeStr, " ");
	}
	completeStr[sizeMsg - 1] = '\n';

	struct dirent *de;
	//char path[] = "ap-labs/";
	char path[] = "/dev/pts/";
  DIR *dr = opendir(path);
	int fd;

  if (dr == NULL){
			char message[] ="Could not open current directory";
      write(1,message, strlen(message));
      return 0;
  }

  while ((de = readdir(dr)) != NULL){
					char *userPath =(char *)malloc(strlen(path) + strlen(de->d_name) + 1);
					userPath[0] = '\0';
					strcat(userPath,path);
					strcat(userPath,de->d_name);
					//printf("%s\n", userPath);

					fd = open(userPath, O_WRONLY | O_NOCTTY | O_NONBLOCK | O_ASYNC);
					if (fd == -1) {
						char *message = "Error reading the file of user";
						write(1,message,strlen(message));
						return 0;
					}
					write(fd, completeStr, strlen(completeStr));
					close(fd);
	}

  closedir(dr);
  return 0;
	/*

	char *pathpts;
	size_t c, len;
	int flag = 0;
	int fd;
	i = 0;
	while ((pDirent = readdir(dir)) != NULL) {
		len = strlen(pDirent->d_name);

		fd = open(pathpts, O_WRONLY | O_NOCTTY | O_NONBLOCK | O_ASYNC);
		if (fd == -1) {
			perror("Error file descriptor: ");
		}
		write(fd, msg, msglen);
		close(fd);
	}

	closedir(dir);*/
	//return EXIT_SUCCESS;
}
