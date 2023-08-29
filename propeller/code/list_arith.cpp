//list_arith.cpp
#include "list_arith.h"



/************* distances in various metrics ***************/

double squared_distance(double x[],double y[])
{
  /*********************************************************
   * Input: double x[3], double y[3]
   *                                                       
   * Output: double sum = \dot(x-y,x-y) = \sum_{i=0}^3 (x_i -y_i)^2     
   *
   * Description: Calculate the squared euclidean distance between the vectors
   *********************************************************/


  double * diff = subtract(x,y);

  double * diff_squared = multiply(diff,diff);
  double sum = 0;
  for (int i = 0; i < 3; i++)
    {
      sum += diff_squared[i];
    }
  delete[] diff; delete[] diff_squared;
  return sum;
}

double l_infinity_distance(double x[], double y[])
{
  /*********************************************************
   * Input: double x[3], double y[3]
   *                                                      
   * Output: double dist = ||x-y||_{l_\infty}= max over i of |x_i -y_i|         
   *
   * Description: Calculate the distance between x and y
   *              in the L_infinity norm.
   *********************************************************/
  double * diff = subtract(x,y);
  int argmax = 0;
  for(int i = 1; i <= 2; i++)
    {
      if(fabs(diff[argmax]) < fabs(diff[i])){ argmax = i; }
    }
  delete[] diff;
  return fabs(diff[argmax]);
}

double l_1_distance(double x[], double y[])
{
  /*********************************************************
   * Input: double x[3], double y[3]
   *                                                      
   * Output: double dist = ||x-y||_{l_1} = \sum_{i=0}^3 |x_i -y_i|         
   *
   * Description: Calculates the distance between x and y in the
   *              L_1 norm
   *********************************************************/
  double * diff = subtract(x,y);
  double sum = 0;
  for(int i = 0; i < 3; i++)
    {
      sum += fabs(diff[i]);
    }
  delete[] diff;
  return sum;
}


/* the following are list arithmetic operations */

double * subtract(double x[], double y[])
{
  /*********************************************************
   * Input: double x[3], double y[3]
   *                                                      
   * Output: double  z[3] = x - y
   *
   * Description: performs x-y component-wise
   *              
   *********************************************************/

  double * z = new double [3];
  for(int i = 0;i<3;i++)
    {
      z[i] = x[i] - y[i];
    }
  return z;
}

long long * add(long long x[], long long y[])
{
  /*********************************************************
   * Input: double x[3], double y[3]
   *                                                      
   * Output: double  z[3] = x + y
   *
   * Description: performs x+y component-wise
   *              
   *********************************************************/
  long long * z = new long long[3];
  for(int i = 0; i < 3; i++)
    {
      z[i] = x[i]+y[i];
    }
  return z;
}

long long * multiply(long long x[], long long y[])
{
  /*********************************************************
   * Input: long long x[3], long long y[3]
   *                                                      
   * Output: long long  z[3] = x*y
   *
   * Description: performs x*y component-wise
   *              
   *********************************************************/
  long long * z = new long long[3];
  for(int i = 0;i < 3;i++)
    {
      z[i] = x[i]*y[i];
    }
  return z;
}

long long * multiply(long long x[], long long y)
{
  /*********************************************************
   * Input: long long x[3], long long
   *                                                      
   * Output: double  z[3] = y*x
   *
   * Description: performs y*x component-wise where y is a scalar
   *              
   *********************************************************/
  long long * z = new long long[3];
  for(int i = 0; i < 3;i ++)
    {
      z[i] = x[i]*y;
    }
  return z;
}

double * multiply(double x[], double y[])
{
  /*********************************************************
   * Input: double x[3], double y[3]
   *                                                      
   * Output: double  z[3] = x*y
   *
   * Description: performs x*y component-wise
   *              
   *********************************************************/
  double * z = new double[3];
  for(int i = 0; i  < 3; i++)
    {
      z[i] = x[i]*y[i];
    }
  return z;
}


double* times_pi_by_N(long long x[],long long interval_length)
{
  /*********************************************************
   * Input: long long x[3], long long interval_length
   *                                                      
   * Output: double  diff[3] = x*(pi/(interval_length -1))
   *
   * Description: multiplies x by the grid spacing (M_PI/(interval_length-1))
   *              
   *********************************************************/
  double * ret = new double[3];
  for(int i = 0; i <3; i++){ ret[i] = x[i]*M_PI/(interval_length-1);}
  return ret;

}





/************* Comparisons **************/

bool areequal(long long x[],long long y[])
{
 /*********************************************************
   * Input: long long x[3], long long y[3]
   *                                                      
   * Output: bool x == y
   *
   * Description: determines if x == y component wise.
   *              
   *********************************************************/
 
  return (x[0] == y[0])&&(x[1] == y[1])&&(x[2]==y[2]);
}

bool leq(long long x[], long long y[])
{
 /*********************************************************
   * Input: long long x[3], long long y[3]
   *                                                      
   * Output: bool x <= y
   *
   * Description: determines if x <= y using the dictionary order.
   *              
   *********************************************************/
  bool ret = true;
  for(int i =0; i <=2; i++)
    {
      if(x[i] > y[i])
	{
	  ret = false;
	  break;
	}
      else if(x[i] < y[i])
	{
	  break;
	}
     }
  return ret;
}
bool areequaldbl(double x[], double y[])
{
 /*********************************************************
   * Input: double x[3], double y[3]
   *                                                      
   * Output: bool x == y
   *
   * Description: determines if x == y component wise.
   *              
   *********************************************************/

  return (fabs(x[0] - y[0]) < 10*EPSILON )&&(fabs(x[1] - y[1])< 10*EPSILON)&&(fabs(x[2] - y[2])< 10*EPSILON);
}

void print_list(long long x[3])
{
 /*********************************************************
   * Input: long long x[3]
   *                                                      
   * Output: (x[0],x[1],x[2])
   *
   * Description: prints the vector
   *              
   *********************************************************/
  printf("(%lli , %lli , %lli )",x[0],x[1],x[2]);
}

void print_list(double x[3])
{
 /*********************************************************
   * Input: double x[3]
   *                                                      
   * Output: (x[0],x[1],x[2])
   *
   * Description: prints the vector
   *              
   *********************************************************/

  printf("(%.16f , %.16f , %.16f )",x[0],x[1],x[2]);
}

void test_list_arith()
{
  int success = 0;
  printf("\n\n Testing_list_arith....\n");

  long long x[3] ={1,2,3};
  long long y[3] = {1,1,2};

  long long xy[3] = {1,2,6};
  long long x3[3] = {3,6,9};
  long long xpy[3] = {2,3,5};

  long long * xtimesy = multiply(x,y);
  long long * xtimes3 = multiply(x,3);
  long long * xplusy = add(x,y);
 
  double u[3] = {1.1,2.0,3.0};
  double v[3] = {1.0,1.5,3.3};
  double uv[3] ={1.1,3.0,9.9};
  double umv[3] = {0.1,0.5,-0.3};
  double * utimesv = multiply(u,v);
  double * uminusv = subtract(u,v);

  
  printf("areequal: (%lli ,%lli ,%lli ) == ( %lli , %lli , %lli )? ",x[0],x[1],x[2],y[0],y[1],y[2]);
  if (areequal(x,y))
    {
      printf(" True.");
      success += 1;
    }
  else
    {
      printf(" False.");
    }
  
  printf("\nareequal: (%lli , %lli , %lli ) == (%lli , %lli , %lli )? ",x[0],x[1],x[2],x[0],x[1],x[2]);
  if (areequal(x,x))
    {
      printf(" True.");
    }
  else
    {
      printf(" False.");
      success += 1;
    }
  
  printf("\nx = ");
  print_list(x);
  printf("\n");
  
  printf("y = ");
  print_list(y);
  printf("\n");
  

  printf("multiply: x*y = ");
  print_list(xy);
  printf("?\n");
  printf("value: ");
  print_list(xtimesy);
  if(areequal(xy,xtimesy))
    {
      printf("\nTrue.\n");
    }
  else
    {
      printf("\nFalse.\n");
      success +=1;
    }

  printf("multiply: 3*y = ");
  print_list(x3);
  printf("?\n");
  printf("value: ");
  print_list(xtimes3);
  if(areequal(x3,xtimes3))
    {
      printf("True.\n");
    }
  else
    {
      printf("False.\n");
      success +=1;
    }

  printf("add: x+y = ");
  print_list(xpy);
  printf("?\n");
  printf("value: ");
  print_list(xplusy);
  if(areequal(xpy,xplusy))
    {
      printf("True.\n");
    }
  else
    {
      printf("False.\n");
      success +=1;
    }



  printf("\nareequaldbl: (%.8f , %.8f , %.8f ) == (%.8f , %.8f , %.8f )? ",u[0],u[1],u[2],v[0],v[1],v[2]);
  if (areequaldbl(u,v))
    {
      printf("True.");
      success += 1;
    }
  else
    {
      printf("False.");

    }
  
  printf("\nareequaldbl: (%.8f , %.8f , %.8f ) == (%.8f , %.8f , %.8f )? ",u[0],u[1],u[2],u[0],u[1],u[2]);
  if (areequaldbl(u,u))
    {
      printf("True.");
    }
  else
    {
      printf("False.");
      success += 1;
    }

  printf("\nu = ");
  print_list(u);
  printf("\n");
  
  printf("v = ");
  print_list(v);
  printf("\n");


  printf("multiply: u*v = ");
  print_list(uv);
  printf("?\n");
  printf("value: ");
  print_list(utimesv);
  if(areequaldbl(uv,utimesv))
    {
      printf("True.\n");
    }
  else
    {
      printf("False.\n");
      success +=1;
    }

  printf("subtract: u-v = ");
  print_list(umv);
  printf("?\n");
  printf("value: ");
  print_list(uminusv);
  if(areequaldbl(umv,uminusv))
    {
      printf("True.\n");
    }
  else
    {
      printf("False.\n");
      success +=1;
    }


  if(success == 0)
    {
      printf("\nPassed.\n");
    }
  else
    {
      printf("\nFailed.\n");
    }
 
}
