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

#ifndef __LOGITWRAPPER__
#define __LOGITWRAPPER__

extern "C" {

  // RPG

  void rpg_gamma(double *x, double *n, double *z, int *num, int *trunc);

  void rpg_devroye(double *x, int *n, double *z, int *num);

  void rpg_alt(double *x, double *h, double *z, int* num);

  void rpg_sp(double *x, double *h, double *z, int* num, int* iter);

  void rpg_hybrid(double *x, double *h, double *z, int* num);

}

#endif
