#include "omp.h"
int main ()
{
  int i, ID;
#pragma omp parallel
{
  ID = omp_get_thread_num();
  printf("Hello World %d\n", ID);
}


}
