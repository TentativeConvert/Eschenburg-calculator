#pragma once
#include "config.h"
#include <cmath>     
using std::abs; //*
using std::sqrt;//*

#include <algorithm>
using std::max; //* 
using std::min; //*

#include <boost/math/common_factor.hpp>
using boost::math::gcd; //*

INT_KS square(INT_KS a);
INT_R signed_mod (INT_R a, INT_R base);
long absolute_mod (long a, long base);
//int absolute_mod (int a, int base); perhaps not needed
int sign(const INT_P &i);
int sign(const INT_R &i);
int sign(const INT_KS &i);

// rationals:
#include <boost/rational.hpp>
using boost::rational; //*
//template<class Typ> rational<Typ> reduce_mod_ZZ(const rational<Typ> &q);
rational<INT_KS> reduce_mod_ZZ(const rational<INT_KS> &q);
int sign(const rational<INT_KS> &r);



/* 

* Using "using" directives and declarations in header files is generally discouraged, for good reason.  However, here I am simply including std::abs, std::sqrt, ...  in place of custom implementations of these functions.  The effect on a file with an 

  #include "aux_math.h"

directive is exactly the same as if I had implemented by own functions abs(...), sqrt(...), in aux_math.h.

*/
