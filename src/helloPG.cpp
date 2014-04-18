#include "RcppArmadillo.h"
#include <R_ext/Utils.h>
#include <iostream>
#include <exception>
#include "Wrapper.h"
// Rcpp::depends(RcppArmadillo)

using namespace Rcpp;
using namespace arma;

colvec rpg(colvec shape, colvec scale) {
// C++-only interface to PolyaGamma class
// draws random PG variates from arma::vectors of n's and psi's
  int d = shape.n_elem;
  colvec result(d);

  rpg_hybrid(&result(0), &shape(0), &scale(0), &d);

  return result;
}

// [[Rcpp::export]]
SEXP helloPG(int n, double z) {
  // returns n draws from PG(1,z)
  colvec pgscale(n, fill::ones);
  colvec pgshape(n);
  for(int i=0; i<n; i++) {
    pgshape[i] = z;
  }
  colvec out = rpg(pgscale, pgshape);

  return Rcpp::List::create(Rcpp::Named("draws")=out
			    );
}

