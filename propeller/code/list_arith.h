//list_arith.h
#include "my_math.h"


/**********************************************
 * This is a list of convenience functions for
 * list arithmetic that is analagous to the
 * numpy array package.
 **********************************************/


/******* Arithmetic *******/

long long * multiply(long long x[],long long y []);
long long * multiply(long long x[],long long y);
double * multiply(double x[], double y[]);
double * subtract(double x[],double y[]);
long long* add(long long x[],long long y[]);
double* times_pi_by_N(long long x[], long long longerval_length);

/******** various distance metrics ************/
double squared_distance(double x[], double y[]);
double l_infinity_distance(double x[], double y[]);
double l_1_distance(double x[], double y[]);




/************ Comparators ******************/

bool areequal(long long x[],long long y[]);
bool leq(long long x[], long long y[]);

/******** Only used for functional testing ******/
bool areequaldbl(double x[],double y[]); 


void print_list(long long x[]);
void print_list(double x[]);


void test_list_arith();
