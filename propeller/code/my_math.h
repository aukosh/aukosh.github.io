//my_math.h
#pragma once

#include "stdlib.h"
#include "stdio.h"
#include <stdint.h>
#include <float.h>
#include "math.h"


/*********************************
 ********* Useful constants ******
 *********************************/

const double EPSILON =  6.62e-16;
static double REG_PART[3] = {1.9106332362490185563277142050315155,1.9106332362490185563277142050315155,1.9106332362490185563277142050315155};
static double MIN[3] = {1.5379684120790425,1.5379684120790425,1.5379684120790425};

extern double ETA;

static double factorials[] = {
  1.0,                                              // 1 / 1!
  -1.0 / 6.0,                                              // 1 / 3!
  1.0 / 120.0,                                    // 1 / 5!
  -1.0 / 5040.0,                                   // 1 / 7!
  1.0 / 362880.0,                                 // 1 / 9!
  -1.0 / 39916800.0,                               // 1 / 11!
  1.0 / 6227020800.0,                             // 1 / 13!
  -1.0 / 1307674368000.0,                  // 1 / 15!
  1.0 / 355687428096000.0,                // 1 / 17!
  -1.0 / 121645100408832000.0,             // 1 / 19!
};

/********************************
 ******** Functions used ********
 ********************************/

/**** Trig ****/

double my_sin(long long n, long long N);
double my_cos(long long n, long long N);
double my_sin(double x);
double my_cos(double x);

double my_tan(long long n, long long N);
double my_csc(long long n, long long N);


/**** Others ****/
double my_sqrt(double x); 

void test_my_math();

/**/
const double sqrt99per10 = my_sqrt(99)/10;
const double sqrt14 = my_sqrt(14);
