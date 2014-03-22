This is a package skeleton for incorporating the Polya-Gamma distribution into your own code or R package. It assumes that you will be using RcppArmadillofor matrix computations.

The main wrapper C++ function, defined in helloPG.cpp, is rpg(colvec shape, colvec scale).  This returns a colvec of random draws with the corresponding shape and scale parameters.  This is a very thin wrapper to the underlying PolyaGamma C++ class, defined in PolyaGamma.h.  It doesn't do things that it probably should, like type-checking and size-checking on shape and scale.  (Thus, e.g., if you feed it shape and scale vectors of different lengths, you will probably get garbage and/or a segfault.)  It should be obvious how to modify the wrapper, if you want.

There is also a simple function called helloPG(n,z) that gets exported to R.  All this does is draw n Polya-Gamma random variables with shape 1 and scale z.  This calls the rpg wrapper function.  It is thus is a thin R wrapper to the thin C++ wrapper to the underlying PolyaGamma class.

Probably you will want to modify the helloPG.cpp to accomplish whatever you want it to, and perhaps put your own source code in the src/ directory.  Then, fix the NAMESPACE and DESCRIPTION file in according with R conventions, and build the package.  I use Hadley Wickham's devtools package, and run

    library(devtools)
    build('helloPG')

