//propeller.cpp
#include "propeller.h"

/**********************************
 ******* GEOMETRIC CONSTRAINS *****
 **********************************/

/* EQ.s 72, \label{three1.1prime} */
bool triangle_inequalities(long long x[])
{
  /*********************************************************
   * Input: long long x[3]
   *                                                      
   * Output: Bool
   *
   * Description: tests whether or not the angles determnied by x
   *              satisfy the spherical triangle inequalities
   *              exactly within an l_infinity ball of radius Pi/(2N) 
   *              (a cube with side-length Pi/N). Notice that
   *              in virtue of our representation of the  parameter
   *              space, we do _not_ need to know the grid spacing.
   *              See eq. 72 in PropR3.pdf or \label{three1.1prime}
   *              in the tex document
   *********************************************************/
  long long t1 = x[0] + x[1] - x[2];
  long long t2 = x[0]  + x[2] - x[1];
  long long t3 = x[1] + x[2] - x[0];
  
  return (2*t1 >= -3 && 2*t2 >= -3 && 2*t3 >= -3);
}

bool in_bounds(double x[],double delta)
{
  /*********************************************************
   * Input: double x[3], double delta
   *                                                      
   * Output: Bool
   *
   * Description: tests whether or not the elements in a 
   *              delta l_infinity ball around x are within
   *              error of being elements of the search space
   *              See eq 72 of the paper (\label{three1.1prime}). In particular,
   *              it checks the inequalities on the individual angles
   *********************************************************/

  //find theta_max
  int amax = 0;
  for(int i = 1; i < 3;i++)
    {
      if(x[amax] < x[i]){ amax = i;}
    }
  bool theta_max_ineq = ((x[amax]+delta)*(1+7*EPSILON) >= M_PI*3/(2*sqrt14)*(1-5*EPSILON)); // 73 line 5

  bool theta_12_ineqs = ((x[0] + delta)*(1+7*EPSILON) >= 0.1*(1-EPSILON)) && (x[0] <= (2*M_PI/3 + delta)*(1 + 10*EPSILON)); // 73 lines 3 and 6
  bool theta_13_ineqs = ((x[1] + delta)*(1+7*EPSILON) >= 0.1*(1-EPSILON)) && ((x[1] + 0.5) <= (M_PI + delta)*(1 + 10*EPSILON)); // 73 lines 4 and 6
  bool theta_23_ineqs = ((x[2] + delta)*(1+7*EPSILON) >= 0.1*(1-EPSILON)) && ((x[2] + 0.5) <= (M_PI + delta)*(1 + 10*EPSILON)); // 73 lines 4 and 6

  return ( theta_12_ineqs && theta_13_ineqs && theta_23_ineqs && theta_max_ineq);

}


bool adds_up(long long x[],int N)
{
  /*********************************************************
   * Input: long long x[3], int N
   *                                                      
   * Output: Bool
   *
   * Description: Another spherical triangle test. It determines
   *              whether or not the angles add up to a value less 
   *              than or equal to 2pi (within error)
   *              See eq 72 line 2 in the paper (\label{three1.1}).
   *********************************************************/

  bool ret = false;
  if(2*(x[0]+x[1]+x[2]) <= 4*N + 3)
    {ret = true;}
  return ret;
}


bool lambda_bound(long long point[],long long N, double delta)
{
  /*********************************************************
   * Input: long long point[3], long long N, double delta
   *                                                      
   * Output: Bool
   *
   * Description: tests the bound on \lambda (see the paper). 
   *              Eq 72 (v12) line 9 (\label{three1.1prime})
   *********************************************************/
  double sinxdx, sinydy, sinzdz, cosx, cosy,cosz, lambda;
  
  sinxdx = my_sin(point[0],N)/(point[0]*M_PI/N);
  sinydy = my_sin(point[1],N)/(point[1]*M_PI/N);
  sinzdz = my_sin(point[2],N)/(point[2]*M_PI/N);
  cosx = my_cos(point[0],N);
  cosy = my_cos(point[1],N);
  cosz = my_cos(point[2],N);

  lambda = (sinxdx*sinxdx + sinydy*sinydy + sinzdz*sinzdz) + 2*(sinzdz*sinydy*cosx + sinzdz*sinxdx*cosy + sinxdx*sinydy*cosz); // eq 71\label{one1.7prime}

  return ((15*delta+2*10000*EPSILON+lambda) >= .03293);

}


bool bigBound(long long point[],long long N, double delta)
{
  /*********************************************************
   * Input: long long point[3], long long N, double delta
   *                                                      
   * Output: Bool
   *
   * Description: tests the bound on the big thetas (the (spherical)
   *              angles of the spherical triangle)
   *              See eq 72 \label{three1.1prime}
   *********************************************************/

  // line 7
  bool condition1 = (-(3*delta + sqrt99per10*(my_sin(point[0], N)*my_sin(point[2], N) + 2*delta))*(1+1500*EPSILON) <= (my_cos(point[1], N) - my_cos(point[0], N)*my_cos(point[2], N) + 2000*EPSILON));
 
  // line 8
  bool condition2 = ((my_cos(point[1], N) - my_cos(point[0], N)*my_cos(point[2], N) - 2000*EPSILON) <= (3*delta + sqrt99per10*(my_sin(point[0], N)*my_sin(point[2], N) + 2*delta))*(1+1500*EPSILON));

  return (condition1 && condition2);
}

/* End EQ.s 72 */

/* EQ 73 \label{five0} */
bool away_from_crit_pts(double angles[],double delta)
{
  /*********************************************************
   * Input: double angles[3], double delta
   *                                                      
   * Output: Bool
   *
   * Description: tests whether or not the point angles[3]
   *              is bounded away from the known critical points.
   *              See eq 73 \label{five0}
   *********************************************************/

  double squared_dist_from_reg_part = squared_distance(angles,REG_PART);
  double l_1_dist_from_reg_part = l_1_distance(angles,REG_PART);
  double squared_dist_from_min = squared_distance(angles,MIN);
  double l_1_dist_from_min = l_1_distance(angles,MIN);

  bool away_from_reg_part = ( (squared_dist_from_reg_part + 40000*EPSILON + 2*delta*(l_1_dist_from_reg_part+ 6000*EPSILON + 3*delta))*(1+20*EPSILON) > .0001*(1-2*EPSILON) );
  bool away_from_min = ( (squared_dist_from_min + 40000*EPSILON + 2*delta*(l_1_dist_from_min+ 6000*EPSILON + 3*delta))*(1+20*EPSILON) > .0001*(1-2*EPSILON) );

  return (away_from_reg_part && away_from_min);
}




/****************************************
 ****** Analytic Constraint Functions ***
 ****************************************/


/* modified H, or Right hand side of Eqs 74, 75 */
double test_function(long long point[], long long N)
 {
   /*********************************************************
    * Input: long long point[3], long long N
    *                                                      
    * Output: double H(point*Pi/N)
    *
    * Description: This is used to test the modified version of H
    *              as per equations  75 and 76 of the text.\label{five1},
    *              \label{five1.1}
    *********************************************************/
   
   double sinxdx, sinydy, sinzdz, cosx, cosy,cosz, sqrtlambda,costhing,gamma,mpinsquared,ret;
   
   sinxdx = my_sin(point[0],N)/(point[0]*M_PI/N);
   sinydy = my_sin(point[1],N)/(point[1]*M_PI/N);
   sinzdz = my_sin(point[2],N)/(point[2]*M_PI/N);
   cosx = my_cos(point[0],N);
   cosy = my_cos(point[1],N);
   cosz = my_cos(point[2],N);
   mpinsquared = M_PI*M_PI/(N*N);
   
   sqrtlambda = my_sqrt((sinxdx*sinxdx + sinydy*sinydy + sinzdz*sinzdz) + 2*(sinzdz*sinydy*cosx + sinzdz*sinxdx*cosy + sinxdx*sinydy*cosz) - 2*10000*EPSILON*alphabetarhosigma[0][3]); //eq 71/74/75
   // \label{five1}, \label{five1}, \label{five1.1}
   
   gamma = sinydy*cosx + sinzdz + sinxdx*cosy; //eq 65 \label{three0}
   
  
  costhing = my_cos(my_sqrt((point[0]*point[0]*mpinsquared + point[1]*point[1]*mpinsquared + 2*point[0]*point[1]*mpinsquared*(cosz - cosx*cosy + 2000*alphabetarhosigma[0][0]*EPSILON)*my_csc(point[0],N)*my_csc(point[1],N))));
  double min = (sqrtlambda*(costhing + 25000*EPSILON*alphabetarhosigma[0][1]) + (gamma+ 3000*EPSILON*alphabetarhosigma[0][2]));
  double max = min;
  for(int i = 1; i < 16;i++)
    {
      sqrtlambda = my_sqrt((sinxdx*sinxdx + sinydy*sinydy + sinzdz*sinzdz) + 2*(sinzdz*sinydy*cosx + sinzdz*sinxdx*cosy + sinxdx*sinydy*cosz) - 2*10000*EPSILON*alphabetarhosigma[i][3]);
      costhing = my_cos(my_sqrt((point[0]*point[0]*mpinsquared + point[1]*point[1]*mpinsquared + 2*point[0]*point[1]*mpinsquared*(cosz - cosx*cosy + 2000*alphabetarhosigma[i][0]*EPSILON)*my_csc(point[0],N)*my_csc(point[1],N))));

      double test = (sqrtlambda*(costhing + 25000*EPSILON*alphabetarhosigma[i][1]) + (gamma+ 3000*EPSILON*alphabetarhosigma[i][2]));
      if( min > test)
	{
	  min = test;
	}
      if (max < test)
	{
	  max = test; 
	}
    }

  if((max > 0) && (min >=0)){
    ret = fabs(min)*(1 - 3000*EPSILON);  // if no sign change, and theyre both positive, the minimum in norm is the minimum.
  }
  else if ( (max <=0 ) && (min < 0) ) {
    ret = fabs(max)*(1 - 3000*EPSILON);  // if no sign change, and theyre both negative, the minimum in norm is the maximum. 
  }
  else{
    ret = -100; // if sign change, signal that we dont use. since test is always bounded below by a value much larger (less negative) than -100, this is a reasonable signal
  }
  return ret;


 }





double F_at_crit_pt(long long points[], long long N)
{
   /*********************************************************
    * Input: long long points[3], long long N
    *                                                      
    * Output: double F|C(points*Pi/N)
    *
    * Description: This returns the value of the modified version
    *              of F restricted to the set of critical points.
    *              See eq 77 and the formulas between 76 and 77
    *              \label{five2}
    *********************************************************/
  double cosx,cosy,cosz,cscx,cscy,cscz,x,y,z;
  x = points[0];
  y = points[1];
  z = points[2];
  cosx = my_cos(points[0],N);
  cosy = my_cos(points[1],N);
  cosz = my_cos(points[2],N);
  cscx = my_csc(points[0],N);
  cscy = my_csc(points[1],N);
  cscz = my_csc(points[2],N);
  x = x*M_PI/N; y = y*M_PI/N; z = z*M_PI/N;
  return (3*(x*x + y*y+z*z) + 2*(cosz - cosx*cosy+2000*EPSILON)*cscx*cscy*x*y +2*(cosy - cosx*cosz+2000*EPSILON)*cscx*cscz*x*z + 2*(cosx - cosz*cosy+2000*EPSILON)*cscz*cscy*y*z);
}



/**************************************
 **** Moduli and Derivative Bonds *****
 **************************************/

/* G, left hand side of Eqs 74, 75 */
double the_new_modulus(long long points[], long long N,double delta)
{
   /*********************************************************
    * Input: long long points[3], long long N, double delta
    *                                                      
    * Output: double G(delta,point*Pi/N,lambda-10^4eps)
    *
    * Description: This returns is the modulus G or its alternative form
    *              depending on what the context demands. eqs 75 76\label{five1}
    *              \label{five1.1}
    *********************************************************/
  double x,y,z, sinxdx, sinydy, sinzdz, cosx, cosy,cosz, lambda,costhing,gamma,ret;

  x = points[0]*M_PI/N;
  y = points[1]*M_PI/N;
  z = points[2]*M_PI/N;
  sinxdx = my_sin(points[0],N)/x;
  sinydy = my_sin(points[1],N)/y;
  sinzdz = my_sin(points[2],N)/z;
  cosx = my_cos(points[0],N);
  cosy = my_cos(points[1],N);
  cosz = my_cos(points[2],N);


  lambda = (sinxdx*sinxdx + sinydy*sinydy + sinzdz*sinzdz) + 2*(sinzdz*sinydy*cosx + sinzdz*sinxdx*cosy + sinxdx*sinydy*cosz) - 2*10000*EPSILON ;
  //eq 71/74/75
   // \label{five1}, \label{five1}, \label{five1.1}
   
  ret = 7.0/2 ;
  ret += 3*(2*(x+delta)+2*(y+delta) + (x+delta)*(y+delta)*(2/my_sin(x+delta) + 2/my_sin(y+delta) + 1/(my_sin(x+delta)*my_sin(y+delta)) ) );
  
  if(lambda < ETA)
    {
      ret *= (1+3000*EPSILON)*delta; // Eq 76
      ret+= (1+5*EPSILON)*my_sqrt(15*delta);
    }
  else
    {
      ret += 15*delta/(2*my_sqrt(ETA - 15*delta));
      ret *= (1+3000*EPSILON)*delta; // Eq 75 Eq 69
    }
    
    

  return ret;

}



double other_derivative_bound(long long points[], long long N,double delta)
{
  /*********************************************************
   * Input: long long points[3], long long N, double delta
   *                                                      
   * Output: double G_{ij}^{\epsilon}(delta,point*Pi/N,lambda-10^4eps)
   *
   * Description: This returns the modulus of continuity for F_0^{\epsilon}
   *              See eq 77.  \label{five2}
   *********************************************************/

  double x = points[0]*M_PI/N;
  double y = points[1]*M_PI/N;
  double z = points[2]*M_PI/N;
  double d = delta;
  return (6*(x+d) +4*(y+d)*(z+d)*my_csc(2*points[1]+1,2*N)*my_csc(2*points[2]+1,2*N) + 2*(x+d)*(y+d)*my_csc(2*points[1]+1,2*N) + 2*(x+d)*(z+d)*my_csc(2*points[2]+1,2*N) + 2*(y+z+2*delta)*(1-((x+delta)*(1+1200*EPSILON)/my_tan(2*points[0]+1,2*N)+EPSILON)));

}

void test_propeller()
{
  printf("testing propeller.c.\n");

  long long test1[3] = {7,2,2};
  long long test2[3] = {1,1,1};
  printf("triangle inequalities: ");
  if(!(triangle_inequalities(test1))&& triangle_inequalities(test2))
    {
      printf("passed.\n");
    }
  else
    {
      printf("failed.\n");
    }
  printf("in_bounds: ");
  if(!(in_bounds(times_pi_by_N(test1,2),M_PI/4))&&(in_bounds(times_pi_by_N(test2,4),M_PI/4)))
    {
      printf("passed.\n");
    }
  else
    {
      printf("failed.\n");
    }

}
