/*
  Skelton for root finding using GSL library
*/

/*! 
  @file gslfindroot_skel.c 
  @brief 
  @author J. Motohisa
  @date
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>

// #include "../config.h"

#define GLOBAL_VALUE_DEFINE
#include "gslfindroot_func_skel.h"

typedef struct param_F_func_skel_struct
{
  param_func_skel p;
} param_F_func_skel;

#define MAXITER 100
#define GSL_FN_EVAL(F,x) (*((F)->function))(x,(F)->params)
#define GSL_FN_FDF_EVAL_F(FDF,x) (*((FDF)->f))(x,(FDF)->params)
#define GSL_FN_FDF_EVAL_DF(FDF,x) (*((FDF)->df))(x,(FDF)->params)
#define BADNUM(x) ((x) != (x) || (x) > 1e50 || (x) < -1e50)

#ifdef DEBUG
int verbose_level0=1;
#else
int verbose_level0=0;
#endif

double solve_func_skel(param_func_skel p, double low, double high, int *status)
{
  param_F_func_skel params={p};
  int max_iter=MAXITER;
  gsl_function F;
  int iter = 0;
  double r;
  double y1, y2;
  const gsl_root_fsolver_type *T;
  gsl_root_fsolver *s;
  
  // findroot
  F.function = &findroot_F_func_skel;
  F.params = &params;
  if(verbose_level0) {
    y1=GSL_FN_EVAL(&F,low);
    y2=GSL_FN_EVAL(&F,high);
    if(y1*y2>0){
      printf("gsl findroot error: low and high values do not bracket 0\n");
      *status = -1;
      return NAN;
    }
  }
      
  T= gsl_root_fsolver_brent;
  s = gsl_root_fsolver_alloc(T);
  gsl_root_fsolver_set(s,&F,low,high);
  do {
    iter++;
    *status = gsl_root_fsolver_iterate(s);
    r=gsl_root_fsolver_root(s);
    low = gsl_root_fsolver_x_lower(s);
    high = gsl_root_fsolver_x_upper(s);
    *status = gsl_root_test_interval(low,high,0,0.001);
  } while (*status==GSL_CONTINUE && iter < max_iter);
  return r;
}

int solve_all_func_skel(param_func_skel p, int n_roots, double *roots,
			double *lows, double *highs)
{
  int i;
  int status;
  for(i=0;i<n_roots;i++)
    *(roots+i)=solve_func_skel(p,*(lows+i),*(highs+1),&status);
  return status;
}

/* function skelton */
/* Write your oun functions */
double findroot_func_skel0(double x, double foo,double bar)
{
  return foo - bar * x;
}

double findroot_func_skel(double x, param_func_skel p)
{
  return (findroot_func_skel0(x,p.foo,p.bar));
}

double findroot_F_func_skel(double x, void *params)
{
  param_F_func_skel *p = (param_F_func_skel *)params;
  return(findroot_func_skel(x,p->p));
}

double findroot_dffunc_skel0(double x, double foo,double bar)
{
  return -bar;
}

double findroot_dffunc_skel(double x, param_func_skel p)
{
  return (findroot_dffunc_skel0(x,p.foo,p.bar));
}

double findroot_F_dffunc_skel(double x, void *params)
{
  param_F_func_skel *p = (param_F_func_skel *)params;
  return(findroot_dffunc_skel(x,p->p));
}

void findroot_fdffunc_skel0(double x, double foo, double bar,
			    double *y, double *dy)
{
  *y = foo - bar*x;
  *dy = - bar;
  return;
}

void findroot_fdffunc_skel(double x, param_func_skel p,
			   double *y, double *dy)
{
  findroot_fdffunc_skel0(x,p.foo,p.bar,y,dy);
  return;
}

void findroot_F_fdffunc_skel(double x,void *params,double *y, double *dy)
{
  param_F_func_skel *p = (param_F_func_skel *)params;
  findroot_fdffunc_skel(x,p->p,y,dy);
  return;
}
/* write your own functions -end- */

/*
  @brief lows and highs should be memory pre-allocated
 */
int find_brackets_func_skel(param_func_skel p,
			    double low, double high,
			    int ndiv, int nmax,double *lows,double *highs)
{
  gsl_function F;
  param_F_func_skel params={p};
  double x,dx;
  double xlow,ylow,yhigh;
  int i;
  int nbra;

  F.function = &findroot_F_func_skel;
  F.params = &params;
  
  dx = (high-low)/(ndiv-1);
  xlow=low;
  ylow=GSL_FN_EVAL(&F,xlow);
  nbra=0;
  /* printf("xlow=%lf,ylow=%lf\n",xlow,ylow); */
  
  for(i=1;i<ndiv;i++)
    {
      x=low+dx*i;
      yhigh=GSL_FN_EVAL(&F,x);
      if(ylow*yhigh<0 && nbra<nmax)
	{
	  *(lows+(nbra))=xlow;
	  *(highs+(nbra))=x;
	  (nbra)++;
	}
      xlow=x;
      ylow=yhigh;
      /* printf("xlow=%lf,ylow=%lf\n",xlow,ylow); */
    }
  return(nbra);
}

double solve_newton_func_skel(param_func_skel p, double x, int *status)
{
  param_F_func_skel params={p};
  int max_iter=MAXITER;
  gsl_function_fdf FDF;
  int iter = 0;
  double x0,r,r_expected;
  const gsl_root_fdfsolver_type *T;
  gsl_root_fdfsolver *s;
  
  // findroot
      
  FDF.f = &findroot_F_func_skel;
  FDF.df = &findroot_F_dffunc_skel;
  FDF.fdf = &findroot_F_fdffunc_skel;
  FDF.params = &params;
  /* y=GSL_FN_FDF_EVAL_F(FDF,x); */
  /* dy=GSL_FN_FDF_EVAL_DF(FDF,x); */
  T = gsl_root_fdfsolver_newton;
  s = gsl_root_fdfsolver_alloc(T);
  gsl_root_fdfsolver_set(s, &FDF, x);
  
  do {
    iter++;
    *status = gsl_root_fdfsolver_iterate(s);
    x0 = x;
    x = gsl_root_fdfsolver_root(s);
    *status = gsl_root_test_delta (x, x0, 0, 1e-3);
  }
  while (*status == GSL_CONTINUE && iter < max_iter);
  return r;
  
  /* do { */
  /*   iter++; */
  /*   *status = gsl_root_fsolver_iterate(s); */
  /*   r=gsl_root_fsolver_root(s); */
  /*   low = gsl_root_fsolver_x_lower(s); */
  /*   high = gsl_root_fsolver_x_upper(s); */
  /*   *status = gsl_root_test_interval(low,high,0,0.001); */
  /* } while (*status==GSL_CONTINUE && iter < max_iter); */
  /* return r; */
}
