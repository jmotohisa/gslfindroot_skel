/*
 *  gslfindroot_v_func_skel.h - last saved: Time-stamp: <Tue Nov 11 23:00:33 JST 2025>
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
 *  $Id: gslfindroot_v_func_skel.h 2025-11-11 22:44:50 jmotohisa $
 */

/*! 
  @file gslfindroot_v_func_skel.h 
  @brief 
  @author J. Motohisa
*/

#ifndef _GSLFINDROOT_V_FUNC_SKEL_H
#define _GSLFINDROOT_V_FUNC_SKEL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	GLOBAL_VALUE_DEFINE
#define	GLOBAL
#else
#define	GLOBAL extern
#endif

/* define your own struct here */

typedef struct params_func_skel_struct
{
  double Vds;
  double Vgs;
  double cMOS;
  double cMES;
  double ps;
}
  params_func_skel;

/* define your own struct here - end -*/

  GLOBAL double findroot_v0_func_skel(double x0,double x1,params_func_skel params);
  GLOBAL double findroot_v1_func_skel(double x0,double x1,params_func_skel params);
  GLOBAL double multiroot_func_skel(double *x0,double *x1,params_func_skel p);

#undef GLOBAL_VALUE_DEFINE
#undef GLOBAL

#ifdef __cplusplus
}
#endif

#endif  // _GSLFINDROOT_V_FUNC_SKEL_H
