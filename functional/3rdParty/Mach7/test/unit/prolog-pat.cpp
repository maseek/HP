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
/// An example of implementing parts of Prolog interpreter based on Mach7.
///
/// \author Yuriy Solodkyy <yuriy.solodkyy@gmail.com>
///
/// \see https://parasol.tamu.edu/mach7/
/// \see https://github.com/solodon4/Mach7
/// \see https://github.com/solodon4/SELL
///

#include <cstdarg>
#include <iostream>
#include <iomanip>
#include <map>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "config.hpp"

//------------------------------------------------------------------------------

/// The word-like entities in the Prolog language are called Terms. 
/// The statements, or sentence-like constructs of Prolog consist of one or 
/// more of these terms combined according to the syntax and morphology of the 
/// language. Like the words of a natural language, Prolog terms may be 
/// classified according to several "lexical categories." The principal 
/// categories into which Prolog terms can be classified are as follows:
///
/// \li #Atom
/// \li #Number
/// \li #String
/// \li #Variable
/// \li #Structure
/// \li #List
/// \li #Operator
/// \li #Comment
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/terms.html
struct Term
{
    virtual ~Term() {}
};

//------------------------------------------------------------------------------

/// Atoms are the fundamental word-like entities in the Prolog language. They 
/// are analogous to the root or stem morphemes of a natural language in that, 
/// although they might appear by themselves, they normally form the basis for 
/// the derivation or construction of more complex words. Their normal role in 
/// Prolog is as data objects, and they can serve as names.
///
/// Atoms are often represented by sequences of one or more lower case letters; 
/// but, they can include both upper case letters and numbers as well as 
/// underscore characters, "_", and dollar signs, "$". The sequence of 
/// characters must begin, however, with a lower case letter.
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/atoms.html
struct Atom : Term
{
    Atom(const char* s) : value(s) {}
    std::string value;
};

//------------------------------------------------------------------------------

/// Numbers are morpheme-like entities in Prolog which carry the meaning that 
/// we normally ascribe to numbers; that is, they can be used to count things 
/// and they can be used to represent the results of measurement processes. 
/// The numbers normally used to count things are called integers, but they can
/// also include negative quantities, while the numbers that usually result from
/// measurements are called floating point numbers. These two varieties of 
/// numbers are distinguished because they are often represented and processed 
/// differently by the computer. They are also represented differently in a 
/// Prolog program.
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/numbers.html
struct Number : Term
{
};

//------------------------------------------------------------------------------

struct Integer : Number 
{
    Integer(int v = 0) : value(v) {}
    int value; 
};

//------------------------------------------------------------------------------

struct Float   : Number
{
    Float(double v = 0.0) : value(v) {}
    double value; 
};

//------------------------------------------------------------------------------

/// Strings are morpheme-like entities in the Prolog language that can be used 
/// to represent information consisting of sequences of characters that will not
/// normally be operated upon, or be used as names, as is the case with atoms.
///
/// Strings are represented by beginning, and ending, a sequence of characters 
/// with dollar signs, $
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/strings.html
struct String : Term
{
    String() : value() {}
    String(const char* s) : value(s) {}
    std::string value;
};

//------------------------------------------------------------------------------

/// Variables are morpheme-like entities in Prolog that function as place 
/// holders for information that is unknown at some stage in the processing of 
/// a statement, but which will normally become available at a later stage of 
/// the process.
///
/// Variables are represented by sequences of one or more upper and lower case 
/// letters, as well as numbers, which may include underscore characters, but 
/// which must begin with either an upper case letter or an underscore.
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/variables.html
struct Variable : Term
{
    Variable(const char* n) : name(n) {}
    std::string name;
};

//------------------------------------------------------------------------------

/// Structures are compound word-like entities in Prolog that are constructed by
/// combining other morpheme-like objects in the language according to the 
/// following schema:
/// 
/// \code{.pl}
/// name(arg1, arg2, ..., argn)
/// \endcode
///   
/// wherein name is an atom, and the entities arg1, arg2, ..., argn, which are 
/// enclosed in parentheses and separated by commas, may be any Prolog terms. 
/// There can be no space between the atom name and the left parenthesis; but, 
/// there may be spaces between the terms within the parentheses.
///
/// The atom in the name position represents the name or principal functor of 
/// the structure. The terms inside the parentheses are called the arguments of
/// the structure, and a given structure is identified by its name and by the 
/// number of its arguments, which is called the arity of the structure. Two 
/// structures with the same name, but with a different number of arguments, are
/// different structures.
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/structures.html
struct Structure : Term
{
    Structure(const char* n) : name(n) {}
    Structure(const char* n, Term** b, Term** e) : name(n), terms(b,e) {}
    size_t arity() const { return terms.size(); }
    std::string name;
    std::vector<Term*> terms;
};

//------------------------------------------------------------------------------

/// Lists are special structures that represent sequences of Prolog terms. 
/// A closed or definite list is represented as follows:
/// 
/// \code{.pl}
/// [e1, e2, ..., en]
/// \endcode
///   
/// where e1, e2, ..., en are called the elements of the list. The elements are 
/// separated by commas, and they may be any Prolog terms, including other lists
/// or structures. The initial element, e1, is called the head of the list, and 
/// the remaining elements, e2, ..., en, comprise the tail of the list.
///
/// The sequence of elements comprising a list is enclosed in brackets 
/// (sometimes called "square brackets" to ensure there is no confusion with 
/// parentheses).
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/lists.html
struct List : Term
{
    List(Term* h, List* t = nullptr) : head(h), tail(t) {}
    Term* head;
    List* tail;
};

//------------------------------------------------------------------------------

/// Operators are special Prolog structures that have operator signs as their 
/// names. Since they are structures, operators are word-like entities in the 
/// Prolog language.
///
/// The Prolog interpreter treats operator signs as special atoms that can be 
/// the names of structures. Operators can be represented according to the 
/// customary format for structures, that is, by writing the structure name 
/// followed by its arguments, with these being enclosed in parentheses and 
/// separated by commas. Thus, an operator can be represented as
/// 
/// \code{.pl}
/// op_sign(op1, op2)
/// \endcode
///   
/// where the operator sign, op_sign, is followed by its operands, op1 and op2.
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/operators.html
struct Operator : Structure
{
    Operator(const char* n) : Structure(n) {}
};

//------------------------------------------------------------------------------

/// Comments represent a device whereby English text might be inserted into a 
/// Prolog program. The English text is normally intended to describe or 
/// document the Prolog program. This descriptive or documentary information 
/// serves to clarify and explain the Prolog clauses among which the comments 
/// have been inserted.
///
/// Comments are preceded by a percent sign, "%." The Prolog interpreter ignores
/// all the characters to the right of the % sign up to the end of the line. 
/// Thus, only the % is a Prolog entity.
///
/// Comments may appear on lines separate from lines containing Prolog 
/// statements, in which case the comment line will begin with a %. Comments may
/// also appear on the same line as a Prolog statement; but, in this case, the %
/// follows the Prolog statement.
///
/// \see http://web.uvic.ca/~ling48x/ling482/prolog/comments.html
struct Comment : Term
{
    Comment() : text() {}
    Comment(const char* s) : text(s) {}
    std::string text;
};

//------------------------------------------------------------------------------

inline Atom*      A(const char*  v) { return new Atom(v); }
inline Integer*   I(const int    v) { return new Integer(v); }
inline Float*     F(const double v) { return new Float(v); }
inline String*    L(const char*  v) { return new String(v); }
inline Variable*  V(const char*  n) { return new Variable(n); }
inline Structure* S(const char*  n, size_t l, ...) 
{
    Structure* result = new Structure(n);
    result->terms.reserve(l);
     
    va_list vl;
    va_start(vl,l);

    for (size_t i = 0; i < l; i++)
    {
        Term* t = va_arg(vl,Term*);
        //XTL_ASSERT(t); // Must be ensured by caller
        result->terms.push_back(t);
    }

    va_end(vl);
    return result; 
}
inline List*      L(size_t l, ...)
{
    List* result = nullptr;
    List* prev   = nullptr;
     
    va_list vl;
    va_start(vl,l);

    for (size_t i = 0; i < l; i++)
    {
        Term* t = va_arg(vl,Term*);
        //XTL_ASSERT(t); // Must be ensured by caller
        List* tail = new List(t);

        if (prev)
            prev->tail = tail;
        else
            prev = result = tail;
    }

    va_end(vl);
    return result; 
}
inline Operator*  O(const char*  n, size_t l, ...)
{
    Operator* result = new Operator(n);
    result->terms.reserve(l);
     
    va_list vl;
    va_start(vl,l);

    for (size_t i = 0; i < l; i++)
    {
        Term* t = va_arg(vl,Term*);
        //XTL_ASSERT(t); // Must be ensured by caller
        result->terms.push_back(t);
    }

    va_end(vl);
    return result; 
}

inline Comment*   K(const char*  v) { return new Comment(v); }

//------------------------------------------------------------------------------

#include "type_switchN-patterns.hpp"
#include "patterns/constructor.hpp"
#include "patterns/primitive.hpp"

//------------------------------------------------------------------------------

namespace mch ///< Mach7 library namespace
{
template <> struct bindings<Atom>      { CM(0,Atom::value);     };
template <> struct bindings<Number>    { };
template <> struct bindings<Integer>   { CM(0,Integer::value);  };
template <> struct bindings<Float>     { CM(0,Float::value);    };
template <> struct bindings<String>    { CM(0,String::value);   };
template <> struct bindings<Variable>  { CM(0,Variable::name);  };
template <> struct bindings<Structure> { CM(1,Structure::arity); CM(0,Structure::name); CM(2,Structure::terms); }; // FIX: MSVC doesn't compile this unless we go in exactly that order!!!
template <> struct bindings<List>      { CM(0,List::head);      CM(1,List::tail); };
template <> struct bindings<Operator>  { CM(0,Operator::name);  };
template <> struct bindings<Comment>   { CM(0,Comment::text);   };
} // of namespace mch

//------------------------------------------------------------------------------

using mch::C; // Enable use of constructor pattern without namespace qualification

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Term& t)
{
    std::string s;
    int         n;
    double      f;
    const Term* hd;
    const List* tl;

    Match(t)
    {
    Case(C<Atom>(s))     return os << s;
    Case(C<Integer>(n))  return os << n;
    Case(C<Float>(f))    return os << f;
    Case(C<String>(s))   return os << s;
    Case(C<Variable>(s)) return os << s;
  //Case(C<Operator>(s)) return os << s;
    Case(C<Structure>(s)) 
        os << s << '(';
        for (auto p = match0.terms.begin(); p != match0.terms.end(); ++p)
            os << (p == match0.terms.begin() ? "" : ",") << **p;
        return os << ')';
    Case(C<List>(hd,tl))
        os << '[' << *hd;
        for (const List* l = tl; l; l = l->tail) 
            os << ',' << *l->head;
        return os << ']';
    Case(C<Comment>(s)) return os << s;
    }
    EndMatch

    return os << "???";
}

//------------------------------------------------------------------------------

bool operator==(const Term&, const Term&);
inline bool operator!=(const Term& left, const Term& right) { return !(left == right); }

//------------------------------------------------------------------------------

bool operator==(const Term& left, const Term& right)
{
    std::string a,b;
    int         n,m;
    double      f,d;
    const Term* h0,*h1;
    const List* t0,*t1;

    Match(left,right)
    {
    Case(C<Atom>(a),      C<Atom>(b)     ) return a == b;
    Case(C<Integer>(n),   C<Integer>(m)  ) return n == m;
    Case(C<Float>(f),     C<Float>(d)    ) return f == d;
  //Case(C<Number>(s),    C<Number>(s)   ) return false;
    Case(C<String>(a),    C<String>(b)   ) return a == b;
    Case(C<Variable>(a),  C<Variable>(b) ) return a == b;
  //Case(C<Operator>(s),  C<Operator>(s) ) return false;
    Case(C<Structure>(a), C<Structure>(b)) return a == b && match0.terms == match1.terms;
    Case(C<List>(h0,t0),  C<List>(h1,t1) ) return *h0 == *h1 && (t0 && t1 ? *t0 == *t1 : t0 == t1);
    Case(C<Comment>(a),   C<Comment>(b)  ) return a == b;
    Otherwise()                            return false;
    }
    EndMatch

    return false;
}

//------------------------------------------------------------------------------

bool occurs(const Term& what, const Term& where)
{
    if (what == where)
        return true;

    const Term* hd;
    const List* tl;

    Match(where)
    {
    Case(C<Structure>())
#if defined(_MSC_VER) && _MSC_VER >= 1700 || defined(__GNUC__) && (XTL_GCC_VERSION >= 40600)
        for (auto t : match0.terms)
            if (occurs(what,*t))
                return true;
#else
        for (auto p = match0.terms.begin(); p != match0.terms.end(); ++p)
            if (occurs(what,**p))
                return true;
#endif
        return false;
    Case(C<List>(hd,tl)) 
        return occurs(what,*hd) || (tl && occurs(what,*tl));
    }
    EndMatch

    return false;
}

//------------------------------------------------------------------------------

Term* subs(const Term* what, Term* with, Term* where)
{
    if (*what == *where)
        return with;

    Term* hd;
    List* tl;

    Match(where)
    {
    Case(C<Structure>())
#if defined(_MSC_VER) && _MSC_VER >= 1700 || defined(__GNUC__) && (XTL_GCC_VERSION >= 40600)
        for (auto& t : match0.terms)
            t = subs(what,with,t);
#else
        for (auto p = match0.terms.begin(); p != match0.terms.end(); ++p)
            *p = subs(what,with,*p);
#endif
        return &match0;
    Case(C<List>(hd,tl)) 
        match0.head = subs(what,with,hd);
        match0.tail = static_cast<List*>(subs(what,with,tl));
        return &match0;
    }
    EndMatch

    return where;
}

//------------------------------------------------------------------------------

typedef std::map<std::string,Term*> substitution_map;
typedef std::pair<Term*,Term*>      term_pair;

//------------------------------------------------------------------------------

bool unify(std::list<term_pair>& pairs, substitution_map& substitutions)
{
    while (!pairs.empty())
    {
        term_pair p = pairs.front();
        pairs.pop_front();

        // Delete/Trivial rule: Drop the expression pair if both expressions are 
        // equal: e.g. you can drop <f(G,x), f(G,x)>
        if (*p.first == *p.second) 
            continue;

        // Decompose rule: If a pair has the same functor and length of the 
        // compound term (and the first rule doesn't apply), remove the functor 
        // and add the pairs of the remaining expressions to the set: 
        // e.g. {<f(a,b,c),f(A,B,C)>} becomes {<a,A>, <b,B>, <c,C>}
        if (Structure* s1 = dynamic_cast<Structure*>(p.first))
        if (Structure* s2 = dynamic_cast<Structure*>(p.second))
        {
        if (s1->arity() == s2->arity() && s1->name == s2->name)
        {
            for (size_t i = 0, n = s1->arity(); i < n; ++i)
                pairs.push_back(term_pair(s1->terms[i],s2->terms[i]));

            continue;
        }
        else
        {
            return false;
        }
        }
        // Orient rule: If the first expressions of the pair is not a variable 
        // and the second is, just switch the expression (we will need this 
        // step to instantiate variables): e.g.  <t,X> becomes <X,t>
        if (!dynamic_cast<Variable*>(p.first) && 
             dynamic_cast<Variable*>(p.second))
            std::swap(p.first,p.second);

        // Variable Elimination: If the first expression is a variable and 
        // doesn't occur in the second, you can drop the pair and add the 
        // instantiation to the substitution-set: 
        // e.g. {<X,f(G)>};{} becomes {}; {X -> f(G)}
        if (Variable* v = dynamic_cast<Variable*>(p.first))
        {
        if (occurs(*v,*p.second))
        {
            return false;
        }
        else
        {
            substitutions[v->name] = p.second;

            // Substitute variable in existing terms in substitution
            for (auto& x : substitutions)
                x.second = subs(v,p.second,x.second);

            // Substitute variable in the current instantiations set
            for (auto& q : pairs)
            {
                q.first  = subs(v,p.second,q.first);
                q.second = subs(v,p.second,q.second);
            }

            continue;
        }
        }

        return false; // None of the rules applies
    }

    return true;
}

//------------------------------------------------------------------------------

void unify(Term* t1, Term* t2)
{
    std::cout << "Unifying " << *t1 << " and " << *t2 << std::endl;

    substitution_map    substitutions;
    std::list<term_pair> pairs;

    pairs.push_back(term_pair(t1,t2));

    if (unify(pairs, substitutions))
#if defined(_MSC_VER) && _MSC_VER >= 1700 || defined(__GNUC__) && (XTL_GCC_VERSION >= 40600)
        for (const auto& x : substitutions)
            std::cout << std::setw(8) << x.first << " -> " << *x.second << std::endl;
#else
        for (auto p = substitutions.begin(); p != substitutions.end(); ++p)
            std::cout << std::setw(8) << p->first << " -> " << *p->second << std::endl;
#endif
    else
        std::cout << "\tERROR: Unable to unify" << std::endl;

}

//------------------------------------------------------------------------------

int main()
{
    Term* terms[] = {
        A("atom"),
        A("atom"),
        I(42),
        I(42),
        F(3.14),
        F(3.14),
        L("$string$"),
        L("$string$"),
        V("X"),
        V("X"),
        S("test", 5, A("a1"), I(7), F(3.1415926), L("$sss$"), V("X")),
        S("test", 5, A("a1"), I(7), F(3.1415926), L("$sss$"), V("X")),
        L(2, A("a2"), V("Y")),
        L(2, A("a2"), V("Y")),
        O("==",0),
        O("==",0),
        K("% comment"),
        K("% comment"),
        // ----
        A("atom2"),
        I(4),
        F(3.1415),
        L("$string2$"),
        V("Y"),
        S("test", 5, A("a1"), I(8), F(3.1415926), L("$sss$"), V("X")),
        L(2, A("a2"), V("Z")),
        O("!=",0),
        K("% another comment")
    };

    const size_t N = XTL_ARR_SIZE(terms);

    for (size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
            std::cout << (*terms[i] == *terms[j]);
        
        std::cout << ' ' << *terms[i] << std::endl;
    }

    unify(
        S("f",3, A("a"), V("X"), S("g",2,A("y"),V("Y")) ), 
        S("f",3, V("Y"), A("b"), V("Z")                 )
    );

    // Unify f(X, Y, g(Z)) and f(X, g(h(Z)), Y)
    unify(
        S("f",3, V("X"), V("Y"),                   S("g",1,V("Z")) ), 
        S("f",3, V("X"), S("g",1,S("h",1,V("Z"))), V("Y")          )
    );

    // Unify p(f(a); g(x)) and p(y; y)
    unify(
        S("p",2, S("f",1,V("A")), S("g",1,V("X"))), 
        S("p",2, V("Y"),          V("Y"))
    );

    // Unify p(a; x; h(g(z))) and p(z; h(y); h(y))
    unify(
        S("p",3, A("a"), V("X"),          S("h",1,S("g",1,V("Z"))) ), 
        S("p",3, V("Z"), S("h",1,V("Y")), S("h",1,V("Y"))          )
    );

    // Unify E = f(x; b; g(z)); and F = f(f(y); y; g(u)):
    unify(
        S("f",3, V("X"),          A("b"), S("g",1,V("Z")) ), 
        S("f",3, S("f",1,V("Y")), V("Y"), S("g",1,V("U")) )
    );

    // Unify p(x; x) and p(y; f(y)).
    unify(
        S("p",2, V("X"), V("Y")          ), 
        S("p",2, V("X"), S("f",1,V("Y")) )
    );

}
