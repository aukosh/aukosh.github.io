//my_math.cpp
#include "my_math.h"

double ETA = .0329;
/*********************************************************
 ************ TRIGONOMETRIC FUNCTIONS ********************
 *********************************************************/


/* we will be using the 19th order taylor expansion around x = 0, notice that for this calculation our argument will always be within the interval [0,3pi/2] */
double my_sin(long long n, long long N){
  /*********************************************************
   * Input: long long n, long long N
   *                                                      
   * Output: double  sin(n*M_PI/N)
   *
   * Description: calculate sin using the 19th order taylor expansion around x = 0. 
   *              The argument is shifted so that the angle is between [-pi/2,pi/2) 
   *              in order to maximize precision.
   *********************************************************/
  double ret = 0.0;

  /* the goal is to move x to the interval [-pi/2, pi/2)*/

  // if the angle >= pi/2, send x to pi - x
  if( N <= 2*n){ 
    n = N - n;
  }
  
  double t = n*M_PI/N;  
  
  for(int i = 0; i < 10; i++)
    {
      ret = ret+ t * factorials[i];
      t = t*n*n*M_PI*M_PI/(N*N);

    }

  return ret;
}

double my_cos(long long n, long long N) {
  /*********************************************************
   * Input: long long n, long long N
   *                                                      
   * Output: double  my_cos(n*M_PI/N)
   *
   * Description: Calculate cos(x) using the identity cos(x) = sin(x+pi/2).
   *********************************************************/
  return my_sin(2*n+N,2*N);
}

double my_tan(long long n, long long N)
{
 /*********************************************************
   * Input: long long n, long long N
   *                                                      
   * Output: double  my_tan(n*M_PI/N)
   *
   * Description: Calculate tan using sin and cos.
   *********************************************************/

  return my_sin(n,N)/my_cos(n,N);
}

double my_csc(long long n, long long N)
{
 /*********************************************************
   * Input: long long n, long long N
   *                                                      
   * Output: double  my_csc(n*M_PI/N)
   *
   * Description: Calculate csc as 1/sin
   *********************************************************/
  return 1.0/my_sin(n,N);
}

double my_sin(double x) {
 /*********************************************************
   * Input:  double x
   *                                                      
   * Output: double  sin(x)
   *
   * Description: calculate sin using the 19th order taylor expansion around x = 0. 
   *              The argument is shifted so that the angle is between [-pi/2,pi/2) 
   *              in order to maximize precision.
   *********************************************************/
  double ret = 0;
  double x_squared;
  // shift
  // put x in [-pi, pi)
  x = fmod(x, 2*M_PI);
  if(x >= M_PI)
    {
      x = x - 2*M_PI;
    }
  else if(x < - M_PI)
    {
      x = x + 2*M_PI;
    }

  // put x in [-pi/2,pi/2)
  if(x >= M_PI_2)
    {
      x = M_PI - x;
    }
  else if(x < -M_PI_2)
    {
      x = -M_PI - x;
    }
  x_squared = x*x;
  for(int i = 0; i < 10; i++)
    {

      ret = ret+ x*factorials[i];
      x = x*x_squared;
    }

  return ret;
}

double my_cos(double x)
{
  /*********************************************************
   * Input: double x
   *                                                      
   * Output: double  my_cos(x)
   *
   * Description: Calculate cos(x) using the identity cos(x) = sin(x+pi/2).
   *********************************************************/
  return my_sin(x+M_PI_2);
}


/**********************************************
 ********* OTHER MATHEMATICAL FUNCTIONS *******
 **********************************************/

double my_sqrt(double x){
  /*********************************************************
   * Input: double x
   *                                                      
   * Output: double  sqrt(x)
   *
   * Description: Calculate sqrt(x) using the newton method
   *********************************************************/
  if(x < 0.0)
    {
      return NAN;
    }
 
  double x0 = 0.0;
  double x1 = x;
  double epsilon = x*DBL_EPSILON;;
  while(fabs(x1 - x0) > epsilon)
    {
      x0 = x1;
      x1 = 0.5*(x0 + x/x0);
      epsilon = DBL_EPSILON*x0;
    }
  return x1;
}


void test_my_math()
{
  printf("\n\nBegin: test_my_math\n");
  printf("EPSILON: %.19f\n", EPSILON);



  printf("factorials \n");
  for(int i = 0; i <10; i++)
    {
      printf("factorials[%i]: %.20f\n",i,factorials[i]);

    }
  printf("\n trig \n pi/2: \n");
  printf("My_Cos(1,2): %.16f\n",my_cos(1,2));
  printf("My_Cos(2,4): %.16f\n",my_cos(2,4));
  printf("My_Sin(1,2): %.16f\n", my_sin(1,2));
  printf("My_Sin(2,4): %.16f\n", my_sin(2,4));
  printf("My_Cos(2pi/4): %.16f\n",my_cos(2*M_PI/4));
  printf("my_sin(2pi/4): %.16f\n",my_sin(2*M_PI/4));
 
  printf("pi/4: \n");
  printf("My_Cos(1,4): %.16f\n",my_cos(1,4));
  printf("My_Sin(1,4): %.16f\n",my_sin(1,4));
  printf("My_Cos(pi/4): %.16f\n",my_cos(M_PI/4));
  printf("my_sin(pi/4): %.16f\n",my_sin(M_PI/4));
 

  printf("2pi/3\n");
  printf("My_Cos(2,3): %.16f\n",my_cos(2,3));
  printf("My_Sin(2,3): %.16f\n",my_sin(2,3));
  printf("My_Cos(2pi/3): %.16f\n",my_cos(2*M_PI/3));
  printf("my_sin(2pi/3): %.16f\n",my_sin(2*M_PI/3));
 
  printf("5pi/6\n");
  printf("My_Cos(5,6): %.16f\n",my_cos(5,6));
  printf("My_Sin(5,6): %.16f\n",my_sin(5,6));
  printf("My_Cos(5pi/6): %.16f\n",my_cos(5*M_PI/6));
  printf("my_sin(5pi/6): %.16f\n",my_sin(5*M_PI/6));
 
  printf("\n my_sqrt \n");
  printf("my_sqrt(2): %.16f\n", my_sqrt(2.0));
  printf("my_sqrt(4): %.16f\n",my_sqrt(4.0));
  
}
