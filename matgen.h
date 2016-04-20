#ifndef _MATRIXGEN_H_
#define _MATRIXGEN_H_

#ifdef ALLINTS
typedef int num_t;
#else
typedef float num_t;
#endif

// Matrix Structure declaration
typedef struct {
    unsigned int width;
    unsigned int height;
    num_t* elements;
} Matrix;


#endif // _MATRIXMUL_H_

