#include <pthread.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

void clear();
bool allNumbers(char *fileName);
int countOpenFiles(char *filePath);
char *getStatusName(char letter);
void createSnapshot();

bool allNumbers(char *fileName){
  for (int i =0; i < strlen(fileName); i++){
    if(isdigit(fileName[i]) == 0){
      return false;
    }
    return true;
  }
}

int countOpenFiles(char *filePath){
  int fileCount = 0;
  DIR *fd = opendir(filePath);
  struct dirent *usedFile;

  if(fd == NULL){
    printf("Could not open current directory\n");
    return -1;
  }
  while ((usedFile = readdir(fd)) != NULL) {
      fileCount++;
  }
  closedir(fd);
  return fileCount - 2;
}

char *getStatusName(char letter){
  char *statusName;
  switch (letter){
    case 'R':
      statusName = "Running";
      break;
    case 'S':
      statusName = "Sleeping";
      break;
    case 'I':
      statusName = "Idle";
      break;
    case 'D':
      statusName = "Waiting";
      break;
    case 'Z':
      statusName = "Zombie";
      break;
    case 't':
      statusName = "Tracing";
      break;
    case 'X':
      statusName = "Dead";
      break;
    default:
      statusName = "Other";
  }
}

void createSnapshot(){
  int fileWrite;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char snapshotFile[100];
  sprintf(snapshotFile,"mytop-status-%d%d%d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
  if((fileWrite = open(snapshotFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0){
    printf("Can't create snapshot file\n");
    exit(EXIT_FAILURE);
  }
  write(fileWrite,"This is the file\n",17);
  close(fileWrite);
}

int main(){
  if (signal(SIGINT, createSnapshot) == SIG_ERR){
    printf("Error with signal\n");
    exit(EXIT_FAILURE);
  }

  while(true){
    DIR *proc = opendir("/proc");
    struct dirent *processFile;
    if(proc == NULL){
      printf("Could not open current directory\n");
      return -1;
    }

    printf("| %-6s | %-6s | %-20s | %-10s | %-14s | %-10s | %-10s |\n",
        "PID", "Parent", "Name", "State", "Memory(bytes)", "# Threads", "Open Files");
    for (int u = 0; u < 100; u++){
      printf("-");
    }
    printf("-\n");
    while((processFile = readdir(proc)) != NULL){
      char *pID = processFile->d_name;
      if(allNumbers(pID)){
        char statusFile[100];
        sprintf(statusFile,"/proc/%s/stat",pID);
        FILE *actualProcess = fopen(statusFile,"r");

        char name[100];
        char state;
        int ppid;
        unsigned long memory;
        long int numThreads;
        fscanf(actualProcess,"%*d %s %s %d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %ld %*ld %*llu %lu", name, &state, &ppid, &numThreads, &memory);

        char fdPath[100];
        sprintf(fdPath,"/proc/%s/fd",pID);
        int numOpenFiles = countOpenFiles(fdPath);
        if(numOpenFiles == -1){
          printf("Error opening the fd for process %s\n",pID);
          return -1;
        }
        printf("| %-6s | %-6d | %-20s | %-10s | %-14lu | %-10ld | %-10d |\n",
    			pID,ppid == 0 ? atoi(pID):ppid,name,getStatusName(state),memory,numThreads,numOpenFiles);
        //printf("PID: %s, PPID: %d, NAME: %s, STATE: %c,No Threads: %ld, Memory: %lu, Open files: %d\n", processFile->d_name,ppid,name,state,numThreads,memory,numOpenFiles);
      }
    }
    closedir(proc);
    sleep(2);
    clear();
  }
  return 0;
}

void clear() {
  printf("\e[1;1H\e[2J");
}
