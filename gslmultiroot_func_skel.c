/*
 *  gslmultiroot_skel.c - Time-stamp: <Tue Nov 11 22:59:47 JST 2025>
 *
 *   Copyright (c) 2025  jmotohisa (Junichi Motohisa)  <motohisa@ist.hokudai.ac.jp>
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  $Id: gslmultiroot_v_skel.c 2025-11-11 21:37:14 jmotohisa $
 */

/*! 
  @file gslmultiroot_v_skel.c 
  @brief 
  @author J. Motohisa
  @date
*/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <tgmath.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

#define GLOBAL_VALUE_DEFINE
#include "gslmultiroot_func_skel.h"

/*!
  @brief
  @param[in]
  @param[out]
  @param[in,out]
  @return
*/

/* define your own functions here */
double findroot_v0_func_skel(double x0,double x1,params_func_skel params)
{
  double y=0;
  return(y);
}

double findroot_v1_func_skel(double x0,double x1,params_func_skel params)
{
  double y=0;
  return(y);
}
/* define your own functions here - end - */

int findroot_v_func_skel(const gsl_vector *x, void *p, gsl_vector *f)
{
  params_func_skel *params = (params_func_skel *)p;
  const double x0 = gsl_vector_get(x,0);
  const double x1 = gsl_vector_get(x,1);
  
  gsl_vector_set(f,0,findroot_v0_func_skel(x0,x1,*params));
  gsl_vector_set(f,1,findroot_v1_func_skel(x0,x1,*params));

  return GSL_SUCCESS;
}

double multiroot_func_skel(double *x0,double *x1,params_func_skel p)
{
  double y0,y1;
  const gsl_multiroot_fsolver_type *T;
  gsl_multiroot_fsolver *s;
  int status;
  size_t iter=0;
  const size_t n=2;
  gsl_multiroot_function F;
  params_func_skel params=p;; 
  
  double x_init[2]={*x0,*x1};
  gsl_vector *x = gsl_vector_alloc(n);

  F.f = &findroot_v_func_skel;
  F.n = 2;
  F.params = &params;

  gsl_vector_set(x,0,x_init[0]);
  gsl_vector_set(x,1,x_init[1]);
  T=gsl_multiroot_fsolver_hybrids;
  s=gsl_multiroot_fsolver_alloc(T,2);

  gsl_multiroot_fsolver_set(s,&F,x);

  do {
    iter++;
    status = gsl_multiroot_fsolver_iterate(s);
    if(status)
      break;
    status = gsl_multiroot_test_residual(s->f,1e-7);
  } while(status==GSL_CONTINUE && iter <1000);
  y0 = findroot_v0_func_skel(gsl_vector_get(s->x,0),gsl_vector_get(s->x,1),p);
  y1 = findroot_v1_func_skel(gsl_vector_get(s->x,0),gsl_vector_get(s->x,1),p);
  gsl_multiroot_fsolver_free(s);
  *x0=gsl_vector_get(s->x,0);
  *x1=gsl_vector_get(s->x,1);
  gsl_vector_free(x);
  return(y0);
}
