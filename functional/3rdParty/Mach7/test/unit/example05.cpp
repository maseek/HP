//
//  Mach7: Pattern Matching Library for C++
//
//  Copyright 2011-2013, Texas A&M University.
//  Copyright 2014-2015, Yuriy Solodkyy.
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

#include "type_switchN-patterns.hpp"
#include "patterns/all.hpp"

#include <complex>
#include <iostream>


// We introduce 2 layouts: cart (for cartesian, default since std::complex uses it by default) and plar (for polar).
enum { cart = mch::default_layout, plar = 1 };

// We can now provide bindings for each layout independently:

namespace mch ///< Mach7 library namespace
{
#if defined(_MSC_VER) && _MSC_VER >= 1700 || defined(__GNUC__) && XTL_GCC_VERSION > 40700
    /// C++ 11 introduced a weird overload for numeric types T for
    /// std::real<T>, std::imag<T>, std::abs<T> and std::arg<T>, which messed up our
    /// nice syntax, and which is why we had to take address of member-functions
    /// or do the explicit cast first:
    template <typename T> struct bindings<std::complex<T>, cart> { Members(std::complex<T>::real, std::complex<T>::imag); };
    template <typename T> struct bindings<std::complex<T>, plar> { Members((T (&)(const std::complex<T>&))std::abs<T>, (T (&)(const std::complex<T>&))std::arg<T>); };
#else
    /// Otherwise you should be able to write nicely like this:
    template <typename T> struct bindings<std::complex<T>, cart> { Members(std::real<T>, std::imag<T>); };
    template <typename T> struct bindings<std::complex<T>, plar> { Members(std::abs<T> , std::arg<T>);  };
#endif
} // of namespace mch

//------------------------------------------------------------------------------

// First we test use of std::complex directly with its default bindings:
void test_complex(const std::complex<double>& v)
{
    using namespace mch;

    var<double> a, b;

    Match(v)
    {
        Case(C<std::complex<double>>(0, 0)) std::cout << "Null"                                        << std::endl; break;
        Case(C<std::complex<double>>(a, 0)) std::cout << "Real      number: " << a                     << std::endl; break;
        Case(C<std::complex<double>>(0, b)) std::cout << "Imaginary number: "             << b << "*i" << std::endl; break;
        Case(C<std::complex<double>>(a, b)) std::cout << "Complex   number: " << a << '+' << b << "*i" << std::endl; break;
    }
    EndMatch
}

//------------------------------------------------------------------------------

// Now we merry layout with the class via Mach7 library view class:
typedef mch::view<std::complex<double>,cart> cartesian;
typedef mch::view<std::complex<double>,plar> polar;

//------------------------------------------------------------------------------

// And now can use views in much the same way we could use std::complex earlier:
void test_cartesian(const std::complex<double>& v)
{
    using namespace mch;

    var<double> a, b;

    Match(v)
    {
        Case(C<cartesian>(0, 0)) std::cout << "Null"                                        << std::endl; break;
        Case(C<cartesian>(a, 0)) std::cout << "Real      number: " << a                     << std::endl; break;
        Case(C<cartesian>(0, b)) std::cout << "Imaginary number: "             << b << "*i" << std::endl; break;
        Case(C<cartesian>(a, b)) std::cout << "Complex   number: " << a << '+' << b << "*i" << std::endl; break;
    }
    EndMatch
}

//------------------------------------------------------------------------------

// Alternatively, we can use polar view of std::complex
void test_polar(const std::complex<double>& v)
{
    using namespace mch;

    const double PI = 3.1415926;
    var<double> r, f;

    Match(v)
    {
        Case(C<polar>(0, _))                      std::cout << "Null"                       << std::endl; break;
        Case(C<polar>(r, f |= f == -PI/2))        std::cout << "Imaginary number: -i*" << r << std::endl; break; // Imprecise because of == on doubles
        Case(C<polar>(r, f |= f ==  PI/2))        std::cout << "Imaginary number: +i*" << r << std::endl; break; // Imprecise because of == on doubles
        Case(C<polar>(r, f |= f == 0 || f == PI)) std::cout << "Real      number: "    << (f > PI/2 ? '-' : '+') << r << std::endl; break;
        Case(C<polar>(r, f))                      std::cout << "Complex   number: "    << r << "*e^(i*" << f << ')'   << std::endl; break;
    }
    EndMatch
}

//------------------------------------------------------------------------------

// As well as mix both views in the same Match statement
void test_mixed(const std::complex<double>& v)
{
    using namespace mch;

    const double PI = 3.1415926;
    var<double> a, b, r, f;

    Match(v)
    {
        Case(C<polar>(0, _))                            std::cout << "Null"               << std::endl; break;
        Case(C<polar>(r, f |= f == -PI/2 || f == PI/2)) std::cout << "Imaginary number"   << (f > 0 ? '+' : '-') << "i*" << r << std::endl; break;  // Imprecise because of == on doubles
        Case(C<cartesian>(a, 0))                        std::cout << "Real      number: " << a << std::endl; break;
        Case(C<cartesian>(a, b))                        std::cout << "Complex   number: " << a << '+' << b << "*i" << std::endl; break;
    }
    EndMatch
}

//------------------------------------------------------------------------------

int main()
{
	typedef std::complex<double> cmpl;
    const cmpl values[] = {cmpl(0,0), cmpl(2,0), cmpl(0,2), cmpl(3.14), cmpl(2.15)};

    for (size_t j = 0; j < XTL_ARR_SIZE(values); ++j)
    {
        test_complex(values[j]);
        test_cartesian(values[j]);
        test_polar(values[j]);
        test_mixed(values[j]);
    }
}

//------------------------------------------------------------------------------
