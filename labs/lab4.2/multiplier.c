#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "logger.h"

long *readMatrix(char *filename);
long *getColumn(int col, long *matrix);
long *getRow(int row, long *matrix);
int getLock();
int releaseLock(int lock);
long dotProduct(long *vec1, long *vec2);
void multiply(long *matA, long *matB);
void actualMult(void *tuple);
int saveResultMatrix(long *result);

int NUM_BUFFERS;
long **buffers;
pthread_mutex_t *mutexes;
long *result;

long *readMatrix(char *filename){
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL){
		errorf("Can't open file: %s\n", filename);
		return NULL;
	}

  long *matrix;
	matrix = (long *) malloc(4000000 * sizeof(long));

	int i = 0;
  char *line = NULL;
  size_t len = 0;
	while (getline(&line, &len, file) != -1){
		matrix[i] = strtol(line, NULL, 10);
    i++;
	}

	return matrix;
}

long * getColumn(int col, long *matrix){
	if (col < 0 || col > 1999){
		errorf("The column should be between 0 and 1999, included\n");
		exit(EXIT_FAILURE);
	}

	long *column = (long *) malloc(2000 * sizeof(long));

	for (int i = 0; i < 2000; i++){
		column[i] = matrix[col];
		col += 2000;
	}
	return column;
}

long * getRow(int row, long *matrix){
	if (row < 0 || row > 1999){
		errorf("The row should be between 0 and 1999, included\n");
		exit(EXIT_FAILURE);
	}

	long *resRow = (long *) malloc(2000 * sizeof(long));

  size_t matrixIndex = row * 2000;
	for (int i = 0; i < 2000; i++){
		resRow[i] = matrix[matrixIndex];
    matrixIndex++;
	}
	return resRow;
}

int getLock(){
	for (int i = 0; i < NUM_BUFFERS; i++){
		if (pthread_mutex_trylock(&mutexes[i]) == 0)
			return i;
	}
	return -1;
}

int releaseLock(int lock){
	if (pthread_mutex_unlock(&mutexes[lock]) == 0){
		return 0;
	}
	return -1;
}

long dotProduct(long *vec1, long *vec2){
	long result = 0;
	for (int i = 0; i < 2000; i++)
			result += vec1[i]*vec2[i];
	return result;
}

struct TupleMatrix {
  long *matrixA;
  long *matrixB;
  size_t row;
  size_t column;
};
pthread_t threads[2000];
void multiply(long *matA, long *matB){
	result  = (long *) malloc(4000000 * sizeof(long));

  for(size_t i = 0;i<2000;i++){ //rows
    for(size_t j = 0;j<2000;j++){ //columns
      struct TupleMatrix *actualTuple = (struct TupleMatrix *)malloc(sizeof(struct TupleMatrix));
      actualTuple->matrixA = matA;
      actualTuple->matrixB = matB;
      actualTuple->row = i;
      actualTuple->column = j;
      pthread_create(&threads[j],NULL,actualMult,(void *)actualTuple);
    }

    for (size_t j = 0; j < 2000; j++){
			pthread_join(threads[j], NULL);
    }
		printf("\rProcess: %ld%%", (i * 100) / 1999);
		fflush(stdout);
  }
}

void actualMult(void *tuple){
  struct TupleMatrix *actualTuple = (struct TupleMatrix *)tuple;
  int lock;
	while ((lock = getLock()) == -1);

  long *rowA = getRow(actualTuple->row, actualTuple->matrixA);
  long *colB = getColumn(actualTuple->column, actualTuple->matrixB);

  long index = (actualTuple->row *2000) + actualTuple->column;
  result[index] = dotProduct(rowA, colB);

  while (releaseLock(lock) != 0);
}

int saveResultMatrix(long *result){
  FILE *resultFile;
	if ((resultFile = fopen("result.dat", "w")) == NULL){
		errorf("Can't create result file\n");
		return -1;
	}
	for (int i = 0; i < 4000000; i++){
		fprintf(resultFile,"%ld\n",result[i]);
	}

  fclose(resultFile);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 3){
		errorf("Usage: ./multiplier -n #\n");
		exit(EXIT_FAILURE);
	}
	NUM_BUFFERS = strtol(argv[2], NULL, 10);
	infof("Using %d buffers\n", NUM_BUFFERS);

	buffers = (long **) malloc(NUM_BUFFERS * sizeof(long*));
	mutexes = (pthread_mutex_t *) malloc(NUM_BUFFERS * sizeof(pthread_mutex_t));

	for (int i = 0; i < NUM_BUFFERS; i++){
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		mutexes[i] = mutex;
		pthread_mutex_init(&mutexes[i], NULL);
	}

	long *matrixA, *matrixB;
  infof("Reading matrices\n");
	matrixA = readMatrix("matA.dat");
	matrixB = readMatrix("matB.dat");
  infof("Done reading matrices\n");

  infof("Doing multiplication\n");
  multiply(matrixA,matrixB);
  infof("Saving result\n");
  saveResultMatrix(result);
  infof("DONE\n");

  return 0;
}
