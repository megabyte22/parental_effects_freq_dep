#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cassert>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>
#include "bramauxiliary.h"


using namespace std;

string filename("iter_freqdep");
string filename_new(create_filename(filename));
ofstream DataFile(filename_new.c_str());  // output file 

struct rparams
{
    // 
double d;
double md_0;
double mh_1;
double md_1;
double mh_2;
double pdhinit;
double phhinit;
double err;
double f_0;
double f_1;
double pdh1;
double pdh0;
double phh1;
double phh2;
double rhh;
double rhd;
double rdd;
double vh_1;
double vh_2;
double vd_0;
double vd_1;

};

double bound0(double val)
{
    if (val < 0)
    {
        val = 0.001;
    }

    return(val);
}

double bound01(double val)
{
    val = val < 0 ? 0.0001 : val > 1.0 ? 0.9999 : val;

    return(val);
}

// recursions of all the patch frequencies
int psys_recur(void *params, gsl_vector *f)
{
    //
double d = ((struct rparams *) params)->d;
double md_0 = ((struct rparams *) params)->md_0;
double mh_1 = ((struct rparams *) params)->mh_1;
double md_1 = ((struct rparams *) params)->md_1;
double mh_2 = ((struct rparams *) params)->mh_2;
double pdhinit = ((struct rparams *) params)->pdhinit;
double phhinit = ((struct rparams *) params)->phhinit;
double err = ((struct rparams *) params)->err;
double f_0 = ((struct rparams *) params)->f_0;
double f_1 = ((struct rparams *) params)->f_1;
double pdh1 = ((struct rparams *) params)->pdh1;
double pdh0 = ((struct rparams *) params)->pdh0;
double phh1 = ((struct rparams *) params)->phh1;
double phh2 = ((struct rparams *) params)->phh2;
double rhh = ((struct rparams *) params)->rhh;
double rhd = ((struct rparams *) params)->rhd;
double rdd = ((struct rparams *) params)->rdd;
double vh_1 = ((struct rparams *) params)->vh_1;
double vh_2 = ((struct rparams *) params)->vh_2;
double vd_0 = ((struct rparams *) params)->vd_0;
double vd_1 = ((struct rparams *) params)->vd_1;

    
    
    // 

double df0dt = 0;

double df1dt = 0;

for (int rtime=0;rtime<1e7;++rtime)
{

 df0dt=f_0 + 0.01*(-(f_0*md_0*(2*(1 - d)*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))) + f_1*mh_1*(1 + (-((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.));

df1dt=f_1 + 0.01*(f_0*md_0*(2*(1 - d)*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.))) - (f_1*md_1*((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.))))/2. + 2*(1 - f_0 - f_1)*mh_2*(1 + (-2*(1 - d)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.) - f_1*mh_1*(1 + (-((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.));

if (fabs(df0dt-f_0)<1e-7 && fabs(df1dt-f_1)<1e-7)
{

f_0=bound01(df0dt);

f_1=bound01(df1dt);

break;
}
f_0=bound01(df0dt);

f_1=bound01(df1dt);

}
gsl_vector_set(f,0,df0dt);
gsl_vector_set(f,1,df1dt);
    
    return GSL_SUCCESS;
}

void relcoeff(void *params, gsl_vector *f)
{
    //
double d = ((struct rparams *) params)->d;
double md_0 = ((struct rparams *) params)->md_0;
double mh_1 = ((struct rparams *) params)->mh_1;
double md_1 = ((struct rparams *) params)->md_1;
double mh_2 = ((struct rparams *) params)->mh_2;
double pdhinit = ((struct rparams *) params)->pdhinit;
double phhinit = ((struct rparams *) params)->phhinit;
double err = ((struct rparams *) params)->err;
double f_0 = ((struct rparams *) params)->f_0;
double f_1 = ((struct rparams *) params)->f_1;
double pdh1 = ((struct rparams *) params)->pdh1;
double pdh0 = ((struct rparams *) params)->pdh0;
double phh1 = ((struct rparams *) params)->phh1;
double phh2 = ((struct rparams *) params)->phh2;
double rhh = ((struct rparams *) params)->rhh;
double rhd = ((struct rparams *) params)->rhd;
double rdd = ((struct rparams *) params)->rdd;
double vh_1 = ((struct rparams *) params)->vh_1;
double vh_2 = ((struct rparams *) params)->vh_2;
double vd_0 = ((struct rparams *) params)->vd_0;
double vd_1 = ((struct rparams *) params)->vd_1;



    // 

	double rhhtplus1;
	double rhdtplus1;
	double rddtplus1;
	for (int rtime=0; rtime<1e07; ++rtime) {
		rhhtplus1 = bound01(((1 - d)*(0.5 + rhh/2.)*(1 - f_0 - f_1)*mh_2*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*md_1*(((1 - d)*rhd*((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2. + ((1 - d)*((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2.))/((1 - f_0 - f_1)*mh_2*(2*(1 - d)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.))) + (f_1*md_1*((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.))))/2.));
		rhdtplus1 = bound01(((1 - d)*(0.5 + rhh/2.)*(1 - f_0 - f_1)*mh_2*(1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + (1 - d)*(0.5 + rdd/2.)*f_0*md_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*md_1*(((1 - d)*rhd*(1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2. + ((1 - d)*(1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2.) + f_1*mh_1*(((1 - d)*((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2. + ((1 - d)*rhd*((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2.))/(f_0*md_0*(2*(1 - d)*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.))) + (f_1*mh_1*((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.))))/2. + 2*(1 - f_0 - f_1)*mh_2*(1 + (-2*(1 - d)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.) + f_1*md_1*(1 + (-((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.)));
		rddtplus1 = bound01(((1 - d)*(0.5 + rdd/2.)*f_0*md_0*(1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*mh_1*(((1 - d)*(1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2. + ((1 - d)*rhd*(1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2.))/(2*f_0*md_0*(1 + (-2*(1 - d)*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.) + f_1*mh_1*(1 + (-((1 - d)*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)) - d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.)));

		if (
				fabs(rhhtplus1 - rhh) < 1e-07 &&
				fabs(rhdtplus1 - rhd) < 1e-07 &&
				fabs(rddtplus1 - rdd) < 1e-07
			)
		{
			break;
		}
		rhh = rhhtplus1;
		rhd = rhdtplus1;
		rdd = rddtplus1;
	}
	gsl_vector_set(f, 0, rhh);
	gsl_vector_set(f, 1, rhd);
	gsl_vector_set(f, 2, rdd);
}


void reproductive_values(void *params, gsl_vector *f)
{
    // 
double d = ((struct rparams *) params)->d;
double md_0 = ((struct rparams *) params)->md_0;
double mh_1 = ((struct rparams *) params)->mh_1;
double md_1 = ((struct rparams *) params)->md_1;
double mh_2 = ((struct rparams *) params)->mh_2;
double pdhinit = ((struct rparams *) params)->pdhinit;
double phhinit = ((struct rparams *) params)->phhinit;
double err = ((struct rparams *) params)->err;
double f_0 = ((struct rparams *) params)->f_0;
double f_1 = ((struct rparams *) params)->f_1;
double pdh1 = ((struct rparams *) params)->pdh1;
double pdh0 = ((struct rparams *) params)->pdh0;
double phh1 = ((struct rparams *) params)->phh1;
double phh2 = ((struct rparams *) params)->phh2;
double rhh = ((struct rparams *) params)->rhh;
double rhd = ((struct rparams *) params)->rhd;
double rdd = ((struct rparams *) params)->rdd;
double vh_1 = ((struct rparams *) params)->vh_1;
double vh_2 = ((struct rparams *) params)->vh_2;
double vd_0 = ((struct rparams *) params)->vd_0;
double vd_1 = ((struct rparams *) params)->vd_1;



    // 

	double vh_1_tplus1;
	double vh_2_tplus1;
	double vd_0_tplus1;
	double vd_1_tplus1;
	for (int rtime=0;rtime<1e07;++rtime) {
		vh_1_tplus1 = bound0(vh_1 + 0.01*(((1 - d)*md_1*(1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1)/2. + ((1 - d)*mh_1*(1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(vd_0 - vh_1))/2. - ((1 - d)/2. + d)*mh_1*vh_1 + d*f_0*md_0*((1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1) + (d*f_1*mh_1*((1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1))/2. + md_1*(((1 - d)*((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.))/2. + (d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))/2.)*(-vh_1 + vh_2) + ((1 - d)*md_1*((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(-vh_1 + 2*vh_2))/2. + (d*f_1*md_1*((1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2)));
		vh_2_tplus1 = bound0(vh_2 + 0.01*(d*f_0*md_0*((1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1) + (d*f_1*mh_1*((1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1))/2. + ((1 - d)*mh_2*(1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(vd_1 - vh_2))/2. + (mh_2*((1 - d)*(1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(f_1*(2 - (1 - err)*pdh1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/2.) + 2*f_0*(1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*(1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)))*(vh_1 - vh_2))/2. + ((1 - d)*mh_2*(1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(vd_1 + vh_1 - vh_2))/2. - ((1 - d)/2. + d)*mh_2*vh_2 + ((1 - d)*mh_2*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2)/2. + (d*f_1*md_1*((1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2)));
		vd_0_tplus1 = bound0(vd_0 + 0.01*(-(((1 - d)/2. + d)*md_0*vd_0) + ((1 - d)*md_0*(1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0)/2. + (md_0*((1 - d)*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(2*f_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*((1 - err)*phh2 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + f_1*((1 - err)*pdh1 + (1 - err)*phh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/2.)))*(-vd_0 + vd_1))/2. + ((1 - d)*md_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(-vd_0 + vh_1))/2. + ((1 - d)*md_0*((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(-vd_0 + vd_1 + vh_1))/2. + d*f_0*md_0*((1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1) + (d*f_1*mh_1*((1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1))/2. + (d*f_1*md_1*((1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*pdh0 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2)));
		vd_1_tplus1 = bound0(vd_1 + 0.01*((mh_1*((1 - d)*(1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + d*(f_1*(2 - (1 - err)*pdh1 - (1 - err)*phh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/2.) + 2*f_0*(1 - (1 - err)*pdh0 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.) + 2*(1 - f_0 - f_1)*(1 - (1 - err)*phh2 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)))*(vd_0 - vd_1))/2. + ((1 - d)*mh_1*(1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(2*vd_0 - vd_1))/2. - ((1 - d)/2. + d)*md_1*vd_1 + ((1 - d)*mh_1*((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1)/2. + d*f_0*md_0*((1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1) + (d*f_1*mh_1*((1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_0 + ((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_1))/2. + ((1 - d)*md_1*((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*(-vd_1 + vh_2))/2. + (d*f_1*md_1*((1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((1 - (1 - err)*pdh1 - (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vd_1 + ((1 - err)*pdh1 + (err*(pdh0 + pdh1 + phh1 + phh2))/4.)*vh_2)));

		if (fabs(vh_1_tplus1 - vh_1) < 1e-7 &&
				fabs(vh_2_tplus1 - vh_2) < 1e-7 &&
				fabs(vd_0_tplus1 - vd_0) < 1e-7 &&
				fabs(vd_1_tplus1 - vd_1) < 1e-7)
		{
			break;
		}

		vh_1 = vh_1_tplus1;
		vh_2 = vh_2_tplus1;
		vd_0 = vd_0_tplus1;
		vd_1 = vd_1_tplus1;
	}
	gsl_vector_set(f, 0, vh_1);
	gsl_vector_set(f, 1, vh_2);
	gsl_vector_set(f, 2, vd_0);
	gsl_vector_set(f, 3, vd_1);

}

void selgrads(void *params, gsl_vector *f)
{
    // 
double d = ((struct rparams *) params)->d;
double md_0 = ((struct rparams *) params)->md_0;
double mh_1 = ((struct rparams *) params)->mh_1;
double md_1 = ((struct rparams *) params)->md_1;
double mh_2 = ((struct rparams *) params)->mh_2;
double pdhinit = ((struct rparams *) params)->pdhinit;
double phhinit = ((struct rparams *) params)->phhinit;
double err = ((struct rparams *) params)->err;
double f_0 = ((struct rparams *) params)->f_0;
double f_1 = ((struct rparams *) params)->f_1;
double pdh1 = ((struct rparams *) params)->pdh1;
double pdh0 = ((struct rparams *) params)->pdh0;
double phh1 = ((struct rparams *) params)->phh1;
double phh2 = ((struct rparams *) params)->phh2;
double rhh = ((struct rparams *) params)->rhh;
double rhd = ((struct rparams *) params)->rhd;
double rdd = ((struct rparams *) params)->rdd;
double vh_1 = ((struct rparams *) params)->vh_1;
double vh_2 = ((struct rparams *) params)->vh_2;
double vd_0 = ((struct rparams *) params)->vd_0;
double vd_1 = ((struct rparams *) params)->vd_1;


    // 
double phh1tplus1=bound01(phh1 + 0.01*(f_0*(-((1 - d)*err*md_0*vd_0)/8. + ((1 - d)*err*rdd*md_0*(-vd_0 + vd_1))/8. + ((1 - d)*err*md_0*(-vd_0 + vh_1))/8. + ((1 - d)*err*md_0*(-vd_0 + vd_1 + vh_1))/8. + d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)) + (1 - f_0 - f_1)*(d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. - ((1 - d)*err*mh_2*(vd_1 - vh_2))/8. - ((1 - d)*err*rhh*mh_2*(vh_1 - vh_2))/8. - ((1 - d)*err*mh_2*(vd_1 + vh_1 - vh_2))/8. + ((1 - d)*err*mh_2*vh_2)/8. + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)) + (f_1*(-((1 - d)*(1 - (3*err)/4.)*rhd*mh_1*(vd_0 - vd_1))/2. - ((1 - d)*err*mh_1*(2*vd_0 - vd_1))/8. + ((1 - d)*(-1 + (3*err)/4.)*md_1*vd_1)/2. + ((1 - d)*(-1 + (3*err)/4.)*mh_1*(vd_0 - vh_1))/2. + ((1 - d)*err*mh_1*vh_1)/8. + d*f_0*md_0*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1) + (d*f_1*mh_1*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1))/2. + d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. + ((1 - d)*err*md_1*(-vd_1 + vh_2))/8. + ((1 - d)*err*rhd*md_1*(-vh_1 + vh_2))/8. + ((1 - d)*(1 - (3*err)/4.)*md_1*(-vh_1 + 2*vh_2))/2. + (d*f_1*md_1*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2) + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)))/2.));

double phh2tplus1=bound01(phh2 + 0.01*((1 - f_0 - f_1)*(d*f_0*md_0*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1) + (d*f_1*mh_1*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1))/2. + ((1 - d)*(-1 + (3*err)/4.)*mh_2*(vd_1 - vh_2))/2. - ((1 - d)*(1 - (3*err)/4.)*rhh*mh_2*(vh_1 - vh_2))/2. + ((1 - d)*(-1 + (3*err)/4.)*mh_2*(vd_1 + vh_1 - vh_2))/2. + ((1 - d)*(1 - (3*err)/4.)*mh_2*vh_2)/2. + (d*f_1*md_1*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2)) + f_0*(-((1 - d)*err*md_0*vd_0)/8. + ((1 - d)*err*rdd*md_0*(-vd_0 + vd_1))/8. + ((1 - d)*err*md_0*(-vd_0 + vh_1))/8. + ((1 - d)*err*md_0*(-vd_0 + vd_1 + vh_1))/8. + d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)) + (f_1*(-((1 - d)*err*rhd*mh_1*(vd_0 - vd_1))/8. - ((1 - d)*err*mh_1*(2*vd_0 - vd_1))/8. - ((1 - d)*err*md_1*vd_1)/8. - ((1 - d)*err*mh_1*(vd_0 - vh_1))/8. + ((1 - d)*err*mh_1*vh_1)/8. + 2*d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.) + ((1 - d)*err*md_1*(-vd_1 + vh_2))/8. + ((1 - d)*err*rhd*md_1*(-vh_1 + vh_2))/8. + ((1 - d)*err*md_1*(-vh_1 + 2*vh_2))/8. + d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.) + 2*d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)))/2.));

double pdh1tplus1=bound01(pdh1 + 0.01*(f_0*(-((1 - d)*err*md_0*vd_0)/8. + ((1 - d)*err*rdd*md_0*(-vd_0 + vd_1))/8. + ((1 - d)*err*md_0*(-vd_0 + vh_1))/8. + ((1 - d)*err*md_0*(-vd_0 + vd_1 + vh_1))/8. + d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)) + (1 - f_0 - f_1)*(d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. - ((1 - d)*err*mh_2*(vd_1 - vh_2))/8. - ((1 - d)*err*rhh*mh_2*(vh_1 - vh_2))/8. - ((1 - d)*err*mh_2*(vd_1 + vh_1 - vh_2))/8. + ((1 - d)*err*mh_2*vh_2)/8. + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)) + (f_1*(-((1 - d)*err*rhd*mh_1*(vd_0 - vd_1))/8. + ((1 - d)*(-1 + (3*err)/4.)*mh_1*(2*vd_0 - vd_1))/2. - ((1 - d)*err*md_1*vd_1)/8. - ((1 - d)*err*mh_1*(vd_0 - vh_1))/8. + ((1 - d)*(1 - (3*err)/4.)*mh_1*vh_1)/2. + d*f_0*md_0*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1) + (d*f_1*mh_1*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1))/2. + d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. + ((1 - d)*(1 - (3*err)/4.)*md_1*(-vd_1 + vh_2))/2. + ((1 - d)*(1 - (3*err)/4.)*rhd*md_1*(-vh_1 + vh_2))/2. + ((1 - d)*err*md_1*(-vh_1 + 2*vh_2))/8. + (d*f_1*md_1*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2) + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)))/2.));

double pdh0tplus1=bound01(pdh0 + 0.01*(f_0*(((1 - d)*(-1 + (3*err)/4.)*md_0*vd_0)/2. + ((1 - d)*(1 - (3*err)/4.)*rdd*md_0*(-vd_0 + vd_1))/2. + ((1 - d)*(1 - (3*err)/4.)*md_0*(-vd_0 + vh_1))/2. + ((1 - d)*(1 - (3*err)/4.)*md_0*(-vd_0 + vd_1 + vh_1))/2. + d*f_0*md_0*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1) + (d*f_1*mh_1*((-1 + (3*err)/4.)*vd_0 + (1 - (3*err)/4.)*vh_1))/2. + (d*f_1*md_1*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2))/2. + d*(1 - f_0 - f_1)*mh_2*((-1 + (3*err)/4.)*vd_1 + (1 - (3*err)/4.)*vh_2)) + (1 - f_0 - f_1)*(d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + (d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.))/2. - ((1 - d)*err*mh_2*(vd_1 - vh_2))/8. - ((1 - d)*err*rhh*mh_2*(vh_1 - vh_2))/8. - ((1 - d)*err*mh_2*(vd_1 + vh_1 - vh_2))/8. + ((1 - d)*err*mh_2*vh_2)/8. + (d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.))/2. + d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)) + (f_1*(-((1 - d)*err*rhd*mh_1*(vd_0 - vd_1))/8. - ((1 - d)*err*mh_1*(2*vd_0 - vd_1))/8. - ((1 - d)*err*md_1*vd_1)/8. - ((1 - d)*err*mh_1*(vd_0 - vh_1))/8. + ((1 - d)*err*mh_1*vh_1)/8. + 2*d*f_0*md_0*(-(err*vd_0)/4. + (err*vh_1)/4.) + d*f_1*mh_1*(-(err*vd_0)/4. + (err*vh_1)/4.) + ((1 - d)*err*md_1*(-vd_1 + vh_2))/8. + ((1 - d)*err*rhd*md_1*(-vh_1 + vh_2))/8. + ((1 - d)*err*md_1*(-vh_1 + 2*vh_2))/8. + d*f_1*md_1*(-(err*vd_1)/4. + (err*vh_2)/4.) + 2*d*(1 - f_0 - f_1)*mh_2*(-(err*vd_1)/4. + (err*vh_2)/4.)))/2.));

gsl_vector_set(f,0, phh1tplus1);

gsl_vector_set(f,1, phh2tplus1);

gsl_vector_set(f,2, pdh1tplus1);

gsl_vector_set(f,3, pdh0tplus1);

}


void write_params(void *params)
{
    // 
double d = ((struct rparams *) params)->d;
double md_0 = ((struct rparams *) params)->md_0;
double mh_1 = ((struct rparams *) params)->mh_1;
double md_1 = ((struct rparams *) params)->md_1;
double mh_2 = ((struct rparams *) params)->mh_2;
double pdhinit = ((struct rparams *) params)->pdhinit;
double phhinit = ((struct rparams *) params)->phhinit;
double err = ((struct rparams *) params)->err;
double f_0 = ((struct rparams *) params)->f_0;
double f_1 = ((struct rparams *) params)->f_1;
double pdh1 = ((struct rparams *) params)->pdh1;
double pdh0 = ((struct rparams *) params)->pdh0;
double phh1 = ((struct rparams *) params)->phh1;
double phh2 = ((struct rparams *) params)->phh2;
double rhh = ((struct rparams *) params)->rhh;
double rhd = ((struct rparams *) params)->rhd;
double rdd = ((struct rparams *) params)->rdd;
double vh_1 = ((struct rparams *) params)->vh_1;
double vh_2 = ((struct rparams *) params)->vh_2;
double vd_0 = ((struct rparams *) params)->vd_0;
double vd_1 = ((struct rparams *) params)->vd_1;



    // 
DataFile << endl << endl  << "d;" << d << endl
 << "md_0;" << md_0 << endl
 << "mh_1;" << mh_1 << endl
 << "md_1;" << md_1 << endl
 << "mh_2;" << mh_2 << endl
 << "pdhinit;" << pdhinit << endl
 << "phhinit;" << phhinit << endl
 << "err;" << err << endl
 << endl;
}


void write_data(void *params, int time)
{
    // 
double d = ((struct rparams *) params)->d;
double md_0 = ((struct rparams *) params)->md_0;
double mh_1 = ((struct rparams *) params)->mh_1;
double md_1 = ((struct rparams *) params)->md_1;
double mh_2 = ((struct rparams *) params)->mh_2;
double pdhinit = ((struct rparams *) params)->pdhinit;
double phhinit = ((struct rparams *) params)->phhinit;
double err = ((struct rparams *) params)->err;
double f_0 = ((struct rparams *) params)->f_0;
double f_1 = ((struct rparams *) params)->f_1;
double pdh1 = ((struct rparams *) params)->pdh1;
double pdh0 = ((struct rparams *) params)->pdh0;
double phh1 = ((struct rparams *) params)->phh1;
double phh2 = ((struct rparams *) params)->phh2;
double rhh = ((struct rparams *) params)->rhh;
double rhd = ((struct rparams *) params)->rhd;
double rdd = ((struct rparams *) params)->rdd;
double vh_1 = ((struct rparams *) params)->vh_1;
double vh_2 = ((struct rparams *) params)->vh_2;
double vd_0 = ((struct rparams *) params)->vd_0;
double vd_1 = ((struct rparams *) params)->vd_1;



    if (time < 0)
    {
        // 
DataFile << "time;phh1;pdh0;vh_1;pdh1;vd_1;vd_0;rdd;rhd;rhh;vh_2;f_0;phh2;f_1;" << endl;
    }

    // 
DataFile << time << ";" << phh1 << ";" << 
pdh0 << ";" << 
vh_1 << ";" << 
pdh1 << ";" << 
vd_1 << ";" << 
vd_0 << ";" << 
rdd << ";" << 
rhd << ";" << 
rhh << ";" << 
vh_2 << ";" << 
f_0 << ";" << 
phh2 << ";" << 
f_1 << ";" << 
 endl;
}


int main (int argc, char **argv)
{
    int max_iter = atoi(argv[1]);

    // initialize the vectors that contain the variables
    // functions solve for
    //
    // vector for patch frequencies
    gsl_vector *x_p = gsl_vector_alloc(2);
    
    // vector for relatedness
    gsl_vector *x_r = gsl_vector_alloc(3);

    // vector for reproductive values
    gsl_vector *x_v = gsl_vector_alloc(4);

    // vector for selection gradients
    gsl_vector *x_selgrad = gsl_vector_alloc(4);

    // initialize the struct with parameters
    struct rparams paramstruct; 

    // initialize command line argument things
    // see generate_cpp.py 
    // 
		paramstruct.d = atof(argv[2]);
		paramstruct.md_0 = atof(argv[3]);
		paramstruct.mh_1 = atof(argv[4]);
		paramstruct.md_1 = atof(argv[5]);
		paramstruct.mh_2 = atof(argv[6]);
		paramstruct.pdhinit = atof(argv[7]);
		paramstruct.phhinit = atof(argv[8]);
		paramstruct.err = atof(argv[9]);
		paramstruct.f_0 = atof(argv[10]);
		paramstruct.f_1 = atof(argv[11]);
		paramstruct.pdh1 = atof(argv[12]);
		paramstruct.pdh0 = atof(argv[13]);
		paramstruct.phh1 = atof(argv[14]);
		paramstruct.phh2 = atof(argv[15]);
		paramstruct.rhh = atof(argv[16]);
		paramstruct.rhd = atof(argv[17]);
		paramstruct.rdd = atof(argv[18]);
		paramstruct.vh_1 = atof(argv[19]);
		paramstruct.vh_2 = atof(argv[20]);
		paramstruct.vd_0 = atof(argv[21]);
		paramstruct.vd_1 = atof(argv[22]);

   

    
    
    // ranges for cycling: sometimes numerical iterations
    // won't resolve as solutions slightly cycle around
    // the final value. To see whether cyling behaviour
    // is repetitive over time, however, we create these
    // vectors that stores a series of past values of 
    // the values for the switching rates and compares
    // those to values that are currently found
    gsl_vector *phh1_range = gsl_vector_alloc(10);
    gsl_vector *phh2_range = gsl_vector_alloc(10);
    gsl_vector *pdh1_range = gsl_vector_alloc(10);
    gsl_vector *pdh0_range = gsl_vector_alloc(10);

    for (int ik = 0; ik < 10; ++ik)
    {
        // initialize the vector
        gsl_vector_set(phh1_range, ik, 0);        
        gsl_vector_set(phh2_range, ik, 0);        
        gsl_vector_set(pdh1_range, ik, 0);        
        gsl_vector_set(pdh0_range, ik, 0);        
    }

    // write the initial data set
    write_data(&paramstruct,-1);

    // iterate
    int iter;
    for (iter = 0; iter < max_iter ; ++iter)
    {
        // patch frequencies
        psys_recur(&paramstruct, x_p);

        paramstruct.f_0= gsl_vector_get(x_p,0);
        paramstruct.f_1= gsl_vector_get(x_p,1);

        assert(isnan(paramstruct.f_0) == 0);
        assert(isnan(paramstruct.f_1) == 0);

        // relatedness
        relcoeff(&paramstruct, x_r);        
        
        paramstruct.rhh = gsl_vector_get(x_r, 0);
        paramstruct.rhd = gsl_vector_get(x_r, 1);
        paramstruct.rdd = gsl_vector_get(x_r, 2);
        
        assert(isnan(paramstruct.rhh) == 0);
        assert(isnan(paramstruct.rhd) == 0);
        assert(isnan(paramstruct.rdd) == 0);

        // reproductive values
        reproductive_values(&paramstruct, x_v);
        
        paramstruct.vh_1 = gsl_vector_get(x_v, 0);
        paramstruct.vh_2 = gsl_vector_get(x_v, 1);
        paramstruct.vd_0 = gsl_vector_get(x_v, 2);
        paramstruct.vd_1 = gsl_vector_get(x_v, 3);
        
        assert(isnan(paramstruct.vh_1) == 0);
        assert(isnan(paramstruct.vh_2) == 0);
        assert(isnan(paramstruct.vd_0) == 0);
        assert(isnan(paramstruct.vd_1) == 0);

        // selection gradients
        selgrads(&paramstruct, x_selgrad);

        bool condition_phh1 = (fabs(paramstruct.phh1 - gsl_vector_get(x_selgrad, 0)) < 1e-7 || paramstruct.phh1 >= 0.999) || paramstruct.phh1 <= 0.001;
        bool condition_phh2 = (fabs(paramstruct.phh2 - gsl_vector_get(x_selgrad, 1)) < 1e-7 || paramstruct.phh2 >= 0.999) || paramstruct.phh2 <= 0.001;
        bool condition_pdh1 = (fabs(paramstruct.pdh1 - gsl_vector_get(x_selgrad, 2)) < 1e-7 || paramstruct.pdh1 >= 0.999) || paramstruct.pdh1 <= 0.001;
        bool condition_pdh0 = (fabs(paramstruct.pdh0 - gsl_vector_get(x_selgrad, 3)) < 1e-7 || paramstruct.pdh0 >= 0.999) || paramstruct.pdh0 <= 0.001;

        if (condition_phh2 && 
                condition_phh1 && 
                condition_pdh1 && 
                condition_pdh0)
        {
            paramstruct.phh1 = gsl_vector_get(x_selgrad, 0);
            paramstruct.phh2 = gsl_vector_get(x_selgrad, 1);
            paramstruct.pdh1 = gsl_vector_get(x_selgrad, 2);
            paramstruct.pdh0 = gsl_vector_get(x_selgrad, 3);

            break;
        }
        paramstruct.phh1 = gsl_vector_get(x_selgrad, 0);
        paramstruct.phh2 = gsl_vector_get(x_selgrad, 1);
        paramstruct.pdh1 = gsl_vector_get(x_selgrad, 2);
        paramstruct.pdh0 = gsl_vector_get(x_selgrad, 3);
        
        assert(isnan(paramstruct.phh1) == 0);
        assert(isnan(paramstruct.phh2) == 0);
        assert(isnan(paramstruct.pdh1) == 0);
        assert(isnan(paramstruct.pdh0) == 0);
       
        // check for stable nonequilibrium behaviour 
        if (iter > 50000)
        {
            bool found_in_range1 = false;
            bool found_in_range2 = false;
            bool found_in_range3 = false;
            bool found_in_range4 = false;

            bool done = false;

            for (int ik = 0; ik < 10; ++ik)
            {
                if (!found_in_range1 && fabs(gsl_vector_get(phh1_range, ik)-paramstruct.phh1) < 1e-10)
                {
                    found_in_range1 = true;
                }
                if (!found_in_range2 && fabs(gsl_vector_get(phh2_range, ik)-paramstruct.phh2) < 1e-10)
                {
                    found_in_range2 = true;
                }
                if (!found_in_range3 && fabs(gsl_vector_get(pdh1_range, ik)-paramstruct.pdh1) < 1e-10)
                {
                    found_in_range3 = true;
                }
                if (!found_in_range4 && fabs(gsl_vector_get(pdh0_range, ik)-paramstruct.pdh0) < 1e-10)
                {
                    found_in_range4 = true;
                }

                if (found_in_range1 && found_in_range2 && found_in_range3 && found_in_range4)
                {
                    done = true;
                    break;
                }
            }

            if (done)
            {
                break;
            }
        }


        for (int ik = 9; ik > 0; --ik)
        {
            gsl_vector_set(phh1_range, ik, gsl_vector_get(phh1_range, ik - 1));
            gsl_vector_set(phh2_range, ik, gsl_vector_get(phh2_range, ik - 1));
            gsl_vector_set(pdh1_range, ik, gsl_vector_get(pdh1_range, ik - 1));
            gsl_vector_set(pdh0_range, ik, gsl_vector_get(pdh0_range, ik - 1));
        }

        gsl_vector_set(phh1_range, 0, paramstruct.phh1);
        gsl_vector_set(phh2_range, 0, paramstruct.phh2);
        gsl_vector_set(pdh1_range, 0, paramstruct.pdh1);
        gsl_vector_set(pdh0_range, 0, paramstruct.pdh0);

        if (iter % 100 == 0)
        {
            write_data(&paramstruct,iter);
        }
    }

    write_data(&paramstruct,iter);
    write_params(&paramstruct);


    gsl_vector_free(x_p);
    gsl_vector_free(x_r);
    gsl_vector_free(x_v);
    gsl_vector_free(x_selgrad);
}

