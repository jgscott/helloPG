////////////////////////////////////////////////////////////////////////////////

// Copyright 2012 Nick Polson, James Scott, and Jesse Windle.

// This file is part of BayesLogit.

// BayesLogit is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or any later version.

// BayesLogit is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along with
// BayesLogit.  If not, see <http://www.gnu.org/licenses/>.

////////////////////////////////////////////////////////////////////////////////

#ifdef USE_R
#include "R.h"
#include "Rmath.h"
#endif

#include "Wrapper.h"
#include "RNG.h"
#include "PolyaGamma.h"
#include "PolyaGammaAlt.h"
#include "PolyaGammaSP.h"
#include <exception>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
				// PolyaGamma //
////////////////////////////////////////////////////////////////////////////////

void rpg_gamma(double *x, double *n, double *z, int *num, int *trunc)
{
  RNG r;
  PolyaGamma pg(*trunc);

  #ifdef USE_R
  GetRNGstate();
  #endif

  for(int i=0; i < *num; ++i){
    #ifdef USE_R
      if (i % 1000 == 0) R_CheckUserInterrupt();
    #endif
      if (n[i]!=0.0) 
	x[i] = pg.draw_sum_of_gammas(n[i], z[i], r);
      else 
	x[i] = 0.0;

  }

  #ifdef USE_R
  PutRNGstate();
  #endif
} // rpg



void rpg_devroye(double *x, int *n, double *z, int *num)
{
  RNG r;
  PolyaGamma pg(1);

  #ifdef USE_R
  GetRNGstate();
  #endif

  for(int i=0; i < *num; ++i){
    if (n[i]!=0)
      x[i] = pg.draw(n[i], z[i], r);
    else
      x[i] = 0.0;
  }

  #ifdef USE_R
  PutRNGstate();
  #endif
} // rpg

void rpg_alt(double *x, double *h, double *z, int* num)
{
  RNG r;
  PolyaGammaAlt pg;

  #ifdef USE_R
  GetRNGstate();
  #endif

  for(int i=0; i < *num; ++i){
    if (h[i]!=0)
      x[i] = pg.draw(h[i], z[i], r);
    else
      x[i] = 0.0;
  }

  #ifdef USE_R
  PutRNGstate();
  #endif
}

void rpg_sp(double *x, double *h, double *z, int* num, int *iter)
{
  RNG r;
  PolyaGammaSP pg;
  
  #ifdef USE_R
  GetRNGstate();
  #endif

  for(int i=0; i < *num; ++i){
    if (h[i]!=0)
      iter[i] = pg.draw(x[i], h[i], z[i], r);
    else
      x[i] = 0.0;
  }

  #ifdef USE_R
  PutRNGstate();
  #endif
}

void rpg_hybrid(double *x, double *h, double *z, int* num)
{
  RNG r;
  PolyaGamma dv;
  PolyaGammaAlt alt;
  PolyaGammaSP sp;
  
  #ifdef USE_R
  GetRNGstate();
  #endif

  for(int i=0; i < *num; ++i){
    double b = h[i];
    if (b > 170) {
      double m = dv.pg_m1(b,z[i]);
      double v = dv.pg_m2(b,z[i]) - m*m;
      x[i] = r.norm(m, sqrt(v));
    }
    else if (b > 13) {
      sp.draw(x[i], b, z[i], r);
    }
    else if (b==1 || b==2) {
      x[i] = dv.draw((int)b, z[i], r);
    }
    else if (b > 1) {
      x[i] = alt.draw(b, z[i], r);
    }
    else if (b > 0) {
	x[i] = dv.draw_sum_of_gammas(b, z[i], r);
    }
    else {
      x[i] = 0.0;
    }
  }

  #ifdef USE_R
  PutRNGstate();
  #endif
}
