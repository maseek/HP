//
//  Mach7: Pattern Matching Library for C++
//
//  Copyright 2011-2013, Texas A&M University.
//  Copyright 2014 Yuriy Solodkyy.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//
//      * Neither the names of Mach7 project nor the names of its contributors
//        may be used to endorse or promote products derived from this software
//        without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

///
/// \file
///
/// This file is a part of Mach7 library test suite.
///
/// \author Yuriy Solodkyy <yuriy.solodkyy@gmail.com>
///
/// \see https://parasol.tamu.edu/mach7/
/// \see https://github.com/solodon4/Mach7
/// \see https://github.com/solodon4/SELL
///

/*
x^0       = 1
x^(2*n)   = xn*xn where xn = x^n
x^(2*n+1) = x * x^(2*n)

and a very fast implementation of Fibonacci numbers would be

fib 1       = 1
fib 2       = 1
fib (2*n)   = (fib(n+1))^2 - (fib(n-1))^2
fib (2*n+1) = (fib(n+1))^2 + (fib n   )^2
*/

#define XTL_DEFAULT_SYNTAX 'S'

#include "match.hpp"                // Support for Match statement
#include "patterns/constructor.hpp" // Support for constructor patterns
#include "patterns/n+k.hpp"         // Support for n+k patterns

#include <math.h>
#include <iostream>
#include "testshape.hpp"
#include "testutils.hpp"

using namespace mch; // Mach7's library namespace

//------------------------------------------------------------------------------

int factorial(int n)
{
    var<int> m;

	if (C<int>(0)(n))   return 1;
	if (C<int>(m+1)(n)) return (m+1)*factorial(m);
	XTL_ASSERT(!"Should never happen");	
    return 0;
}

//------------------------------------------------------------------------------

int fac(int n)
{
    unsigned short m;

    Match (n)
    {
      When(0) return 1;
      When(1) return 1;
      When(m) return m*fac(m-1);
      When(_) return 0;
    }
    EndMatch

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

template <typename T>
inline T sqr(const T& x) { return x*x; }

//------------------------------------------------------------------------------

double power(double x, int n)
{
	if (n == 0) return 1.0;
	if (n == 1) return x;
	if (n % 2 == 0) return sqr(power(x,n/2));
	if (n % 2 == 1) return x*power(x,n-1);

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

double power_opt(double x, int n)
{
	if (n == 0) return 1.0;
	if (n == 1) return x;
	return 
        n%2 == 0
            ?   sqr(power_opt(x,n/2)) 
            : x*sqr(power_opt(x,n/2));
}

//------------------------------------------------------------------------------

double power1(double x, int n)
{
	var<int> m;

	if (C<int>(0)(n))     return 1.0;
    if (C<int>(1)(n))     return x;
	if (C<int>(m*2)(n))   return sqr(power1(x,m));
	if (C<int>(m*2+1)(n)) return x*power1(x,2*m);

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

double power2(double x, int n)
{
    var<int> m;

    Match(n)
    {
      When(0)     return 1.0;
      When(1)     return x;
      When(2*m)   return   sqr(power2(x,m));
      When(2*m+1) return x*sqr(power2(x,m));
    }
    EndMatch

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

int fib(int n)
{
	if (n == 1 || n == 2) return 1;
	if (n % 2 == 0) return sqr(fib(n/2+1)) - sqr(fib(n/2-1));
	if (n % 2 == 1) return sqr(fib(n/2+1)) + sqr(fib(n/2));

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

int fib_opt(int n)
{
	if (n == 1 || n == 2) 
        return 1;

    return 
        n%2 == 0 
            ? sqr(fib_opt(n/2+1)) - sqr(fib_opt(n/2-1))
            : sqr(fib_opt(n/2+1)) + sqr(fib_opt(n/2));
}

//------------------------------------------------------------------------------

int fib1(int n)
{
    var<int> m;

    if (C<int>(1)(n))     return 1;
    if (C<int>(2)(n))     return 1;
    if (C<int>(m*2)(n))   return sqr(fib1(m+1)) - sqr(fib1(m-1));
    if (C<int>(m*2+1)(n)) return sqr(fib1(m+1)) + sqr(fib1(m));

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

int fib2(int n)
{
    var<int> m;

    Match(n)
    {
      When(1)     return 1;
      When(2)     return 1;
      When(2*m)   return sqr(fib2(m+1)) - sqr(fib2(m-1));
      When(2*m+1) return sqr(fib2(m+1)) + sqr(fib2(m));
    }
    EndMatch

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

struct DummyShape : Shape
{
    void accept(ShapeVisitor&) const {}
};

//------------------------------------------------------------------------------

struct ShapeVisitor {};

//------------------------------------------------------------------------------

XTL_TIMED_FUNC_BEGIN
size_t do_match(const Shape&, size_t n)
{
    return (size_t)power2(1.01,n);
  //return (size_t)fib2(n%100+1);
}
XTL_TIMED_FUNC_END

//------------------------------------------------------------------------------

XTL_TIMED_FUNC_BEGIN
size_t do_visit(const Shape&, size_t n)
{
    return (size_t)power_opt(1.01,n);
  //return (size_t)fib_opt(n%100+1);
}
XTL_TIMED_FUNC_END

//------------------------------------------------------------------------------

Shape* make_shape(size_t)
{
    return new DummyShape;
}

//------------------------------------------------------------------------------

#include "testvismat1.hpp"    // Utilities for timing tests

//------------------------------------------------------------------------------

int main()
{
    std::cout << fac(-1);
    std::cout << fac(0) << fac(1) << fac(2) << fac(3) << fac(4) << std::endl;

	double x = 2.0;

	for (int i = 0; i < 10; ++i)
		std::cout << x << '^' << i << '=' << power2(x,i) << (power_opt(x,i) == power2(x,i) ? "" : "WRONG") << std::endl;

	for (int i = 1; i < 10; ++i)
		std::cout << "fib(" << i << ")=" << fib2(i) << (fib_opt(i) == fib2(i) ? "" : "WRONG") << std::endl;

	for (int i = 1; i < 10; ++i)
		std::cout << "factorial(" << i << ")=" << factorial(i) << std::endl;

    using namespace mch; // Mach7's library namespace

    verdict pp = test_repetitive();
    std::cout << "OVERALL: "
              << "Repetitive: " << pp << "; "
              << std::endl; 
}

//------------------------------------------------------------------------------
