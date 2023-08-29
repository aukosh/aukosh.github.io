//propeller.h
#include "list_arith.h"

/****************************************
 * This contains all of the mathematical of interest in the R^3 Propeller problem.
 * It contains the geometric bounds used, as well as the functions of interest
 * such as formulae for the moduli of continuity and the 3 bound functions.
 * For in-depth discussion of the properties of these functions and their derivations
 * please read Heilman et al. 2011.
 ****************************************/


/****************************************
 ****** Analytic Constraint Functions ***
 ****************************************/

double test_function(long long point[], long long N);

double F_at_crit_pt(long long points[], long long N);

/**************************************
 **** Moduli and Derivative Bonds *****
 **************************************/

double other_derivative_bound(long long points[],long long N,double delta);
double the_new_modulus(long long points[], long long N,double delta);

/**********************************
 ******* GEOMETRIC CONSTRAINS *****
 **********************************/

bool triangle_inequalities(long long x[]);


bool in_bounds(double x[],double delta);

bool adds_up(long long x[],int N);

bool away_from_crit_pts(double x[],double delta);
bool lambda_bound(long long point[], long long N, double delta);
bool bigBound(long long point[], long long N, double delta);

/*******************************
 ******** Misc ****************
 *******************************/

static double alphabetarhosigma[16][4] = { {-1,-1,-1,-1},
					   {-1,-1,-1,1},
					   {-1,-1,1,-1},
					   {-1,-1,1, 1},
					   {-1,1,-1,-1},
					   {-1,1,-1,1},
					   {-1,1,1,-1},
					   {-1,1,1,1},
					   {1,-1,-1,-1},
					   {1,-1,-1,1},
					   {1,-1,1,-1},
					   {1,-1,1, 1},
					   {1,1,-1,-1},
					   {1,1,-1,1},
					   {1,1,1,-1}};
					   

void test_propeller();
