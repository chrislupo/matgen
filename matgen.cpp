/* Matrix multiplication: C = A * B.
 * Host code.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <sys/time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

// includes, kernels
#include "matgen.h"

Matrix AllocateMatrix(int height, int width, int init);

void WriteFile(Matrix M, char* file_name);
void FreeMatrix(Matrix* M);

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
  Matrix  M;
  Matrix  N;
  char *str;

  if(argc == 5) {
    // Allocate and initialize the matrices
    srand(time(0));
    M  = AllocateMatrix(strtol(argv[1],&str,10), strtol(argv[2],&str,10), 1);
    N  = AllocateMatrix(strtol(argv[3],&str,10), strtol(argv[4],&str,10), 1);
    WriteFile(M, (char *)"m1.in");
    WriteFile(N, (char *)"m2.in");
    FreeMatrix(&M);
    FreeMatrix(&N);
    return 0;
  }
  else {
    printf("Incorrect number of arguments\n");
    exit(1);
  }
  return 0;
}

// Allocate a device matrix of dimensions height*width
//	If init == 0, initialize to all zeroes.  
//	If init == 1, perform random initialization.
Matrix AllocateMatrix(int height, int width, int init) {
  Matrix M;
  M.width = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  // don't allocate memory on option 2
  if(init == 2)
    return M;

  M.elements = (num_t*) malloc(size*sizeof(num_t));

  for(unsigned int i = 0; i < M.height * M.width; i++) {
#ifdef ALLINTS
    M.elements[i] = (init == 0) ? (0) : 
      ((1000*(rand()-(RAND_MAX/2))/(RAND_MAX/1000)));
#else
    M.elements[i] = (init == 0) ? (0.0f) : (10*(rand()*3 / (num_t)RAND_MAX));
#endif
  }
  return M;
}	

void WriteFile(Matrix M, char* file_name) {
  FILE *file = fopen(file_name, "w");
  if (!file) {
    perror(file_name);
    return;
  }

  for (long r = 0; r < M.height; r++) {
    for (long c = 0; c < M.width; c++) {
#ifdef ALLINTS
      fprintf(file, "%d ", M.elements[M.width * r + c]);
#else
      fprintf(file, "%.2f ", M.elements[M.width * r + c]);
#endif
    }
    fprintf(file, "\n");
  }
  printf("Done writing result matrix with %d rows and %d columns\n", 
      M.height, M.width);

  fclose(file);
}

// Free a host Matrix
void FreeMatrix(Matrix* M) {
  free(M->elements);
  M->elements = NULL;
}

