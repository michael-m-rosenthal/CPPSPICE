The following rules, guidelines, and best practices are based on [Sutter and Alexandrescu: “C++ Coding Standards”](https://www.amazon.com/exec/obidos/ASIN/0321113586/).

According to the [ISO Coding Standards](https://isocpp.org/wiki/faq/coding-standards), Stroustrup considers [the JSF air vehicle C++ coding standards](http://stroustrup.com/JSF-AV-rules.pdf) to be a pretty good set of rules for safety critical and performance critical code. The latest might be overly restrictive, but definitely serves as a good reference.

As of October 23, 2017, [C++ Core Guidelines by Bjarne Stroustrup and Herb Sutter](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) are available as another good reference.

***

Draft versions of the [C++ Standard](http://www.open-std.org/jtc1/sc22/wg21/docs/standards) are available online for easier text navigation :)

***

## Atom Snippets

A set of snippets for the Atom editor is available for the team use: [SPICE-2.0/src/prototypes/wiki/atom/snippets.cson]( https://github.jpl.nasa.gov/NAIF/SPICE-2.0/raw/master/src/prototypes/wiki/atom/snippets.cson ). Snippets allow to enter a simple prefix in the editor (the keyword identified by *prefix* of each snippet) and hit tab to expand the prefix into a larger code block with templated values.

One can edit its version of Atom's snippets or replace the snippet file with the one provided. To navigate to the location of your Atom's snippet file, please open **Atom --> Snippets...** menu, then hover over the filename under the tree view to see its absolute or relative path.

## Coding Style

### Filename convention
* Use .hpp for the header filename
* Use .cpp for the source filename
* Name file according to the C++ class it represents.
For example, _TestClass.hpp_ and _TestClass.cpp_ contain declaration and implementation of spice2::TestClass class.
* For template classes, all template definitions should be included in an additional _[baseFileName]Impl.hpp_ file.  For example, the header file _ZZKernelPtr.hpp_ has a companion implementation file _ZZKernelPtrImpl.hpp_.


### File version and date string

Within each file's header, include the package name, its version number, release date, and the author's initials (shown in parenthesis with the `XXX` placeholder below):

`//    SPICE2 Version 1.0.0, 01-JAN-2017 (XXX)`

Following from SPICE 1.0, the version update rule for the pattern:


I.J.K

is:

- If the update is functional, increment I and set J, K to 0.
- If only the implementation is updated, increment J and set K to 0.
- If only the comments are updated, increment K.

In SPICE2, prior to release, the latest version is always 1.0.0, but a new
date and description is needed any time a file is touched.


### Naming conventions
Never use "underhanded names", ones that begin with an underscore or contain double underscore.

#### SPICE-public functionality

* Name classes, structs, and **enum**s **LikeThis**
* Name variables **likeThis** (allow all lower case)
* Name data member variables **m_likeThis**
* Name static data members **s_likeThis**
* Name methods **likeThis** (allow all lower case)
* Name macros, enumerator values and constants  **LIKE_THIS**
* Use all upper case letters for acronyms that appear as part of the name **likeCIAVariable**
* Don't start variable names with acronyms
* Generally speaking, name namespaces **likethis**.  An exception to this rule are namespaces that contain **only** static methods, which may use a class-like naming convention, where applicable.  Examples include the namespace PCKType02, and the namespace ChebyshevPolynomials.


#### SPICE-private functionality

All SPICE functionality, that is intended for the SPICE Toolkit developers use only, should follow the following conventions:

* Name classes, structs, and **enum**s **ZZLikeThis**
* Name data member variables **zzm_likeThis**
* Name static data members **zzs_likeThis**
* Name methods **zzLikeThis** (allow all lower case)
* Name macros, enumerator values and constants  **ZZ_LIKE_THIS**
* Name namespaces **zzlikethis**


### Variable name length
24


### File line length
78


### Spaces

* Spaces vs. tabs: **no tabs**

* The dereference operator **\*** and the address-of operator **&** shall be directly connected with the type-specifier:

   int* ptr;
   int& ref;
   template< typename T > std::vector< T* > vptr;
   const SpiceClass< SPICE::Double >& tref{ 0 };
   for ( auto& p: container ) ...


* Spaces in function/method signatures:

   void ClassMethod( int numInt, int numDouble );
   static void ClassMethod( int numInt, int numDouble );
   virtual ClassMethod( int numInt, int numDouble ) = 0;
   void ClassMethod( int numInt, int numDouble ) override;
   void ClassMethod( int numInt, int numDouble ) const;
   void ClassMethod( const SpiceClass& obj ) = default;
   void ClassMethod( const SpiceClass& obj ) = delete;


* Use spaces before and after opening parenthesis, before closing parenthesis, after control keywords (if, for), and after commas/semicolons:

   for ( int i = 0; i < 3; ++i )
   {
      if ( someVar < anotherVar )
      {
         foo( var1, var2, var3 );
      }
   }


### Indentation

* Do indent to show structure

* Use three-space indent

   void SpiceFunction( const std::vector< SpiceClass >& v )
   {
      //
      // some comments
      //

      for( auto & eachElement: v )
      {
         //
         // do something
         //
         ...
      }
   }


### Each expression-statement should be on a separate line

a[i] = k[j];
++i;
++j;


### The bodies of _if, else if, else, while, do..while_ and _for_ statements should always be enclosed in braces

if( flag == 1 )
{
    success();
}


### Namespace
* Define all SPICE 2.0 functionality within **spice2** namespace

* Introduce new namespace within **spice2** namespace to group related functionality if it makes sense (team's decision to introduce new namespaces)

* Enclose all _private_ SPICE2 functionality (not to be exposed to the end user) within a private namespace **zzprivate**

     namespace spice2
     {
        namespace zzprivate
        {
           ...
        }
        ...
     }
     //
     // namespace spice2
     //

* Allow a comment at the end of the namespace scope

     namespace spice2
     {
        ...
     }
     //
     // namespace spice2
     //


* Indent everything within namespace

     namespace spice2
     {
        //
        // Forward declarations
        //
        class SomeType;

        //
        // Class definition
        //
        class NewClass : public BaseClass
        {
           public:
              ...
        };
     }
     //
     // namespace spice2
     //



### Templates

* Use **typename** keyword in template declarations:

     template< typename C > class SpiceClass
     {
        ...
     };

  * There is one exception (up to and including C++14 - to be confirmed with our set of compilers) when **class** keyword is required for the declaration of template template parameters (when template parameter is a class template):

         template< typename TYPE, template< typename > class CONTAINER = std::deque >
         class SomeType
         {
            ...
         };

* Use suffix return type in function template declarations where return type depends on input arguments

    template< typename T, typename U >
    auto product( const T& x, const T& u ) -> decltype( x*u );


* For the **TemplateClass** template class place:

* Class declaration and user specializations into _TemplateClass.hpp_ file
* Methods definitions into _TemplateClassImpl.hpp_ file
* Templates instantiations and user specializations in _TemplateClass.cpp_ file

For example, file "_TemplateClass.hpp_" would have the following content:

     #ifndef HAVE_SPICE2_TEMPLATECLASS
     #define HAVE_SPICE2_TEMPLATECLASS

     template< typename T > class TemplateClass :
     {
        ...

        const T state();

        ...
     };

     //
     // Declare user specializations
     //
     template<>
     const std::string TemplateClass< std::string >::state();

     #endif
     //
     // HAVE_SPICE2_TEMPLATECLASS
     //

File "_TemplateClassImpl.hpp_" should have method definitions for TemplateClass< T >.

File "_TemplateClass.cpp"_ should have implementation of user specializations and explicit template instantiations:

     #include <string>

     #include "TemplateClass.hpp"
     #include "TemplateClassImpl.hpp"
     #include "SomeType.hpp"

     //
     // Provide user specializations
     template<>
     const std::string TemplateClass< std::string >::state()
     {
         //
         // Implementation specific to the std::string type
         //
         ...
     }

     //
     // Instantiate class templates
     //
     template class TemplateClass < SomeType >;
     template class TemplateClass < std::string >;


If you need to use instantiated class template **class TemplateClass < SomeType >** in other source files, use forward declaration with **extern** specifier:

File "SomeSource.cpp":

     #include "TemplateClass.hpp"
     #include "SomeType.hpp"

     extern template class TemplateClass < SomeType >;


### Long lines

*  If more than one input argument is provided in function's declaration or definition, these arguments should be broken up onto multiple lines and variable names should be aligned

     namespace toplevel
     {
        int Class::max() const
        { ... }

        int Class::max( int i ) const
        { ... }

        int Class::max(
           int i,
           int j ) const
        { ... }

        template< typename T, typename U, typename Y >
        SomeVeryLongType AberrationCorrection::getLightTimeCorrection(
           T             a,
           U             b,
           Y             moreA,
           SomeLongType  moreB ) const
        { ... }

        template< typename T, typename U >
        auto product(
           const T& x,
           const T& u
           ) -> decltype( x*u )
        { ... }

     }
     //
     // namespace toplevel
     //


* Wrap around method signature within class declarations depending on a list of input arguments

    class SPICEClass
    {
        ...
        int max( int i ) const;

        virtual void virtualMethod(
           const std::vector< anothernamespace::AnotherSPICEClass >& s,
           const int position );

        void method(
           const std::vector< anothernamespace::AnotherSPICEClass >& s,
           const int position );
        ...
    };

* Wrap around long initializer lists (accept both forms of formats)

   std::vector< int > iv { 1, 2, 3 };

   std::vector< std::string > sv {
      "first string",
      "second string",
      "third string" };

* Wrap around loops with long expressions (with optional variable alignment)

   for ( auto iter = mArraySummaries.begin(),
         end_iter  = mArraySummaries.end();
         iter != end_iter;
         ++iter )
   {
      ...
   }

* &#x1F534; Wrap around multiple input arguments and indent relative to the calling function

   std::ostringstream records;

   records << mSearchIterator->current().readArrayRecords(
                 mStream,
                 mSearch );


   auto searchIterator{ SomeIteratorFactory< SomeLongType >::create(
           someLongTypeID,
           containerToSearch ) };


* Always wrap in class constructor's initializer list

    SpiceClass::SpiceClass( const std::vector< int >& v ) :
       mVector { v },
       mString { "InitialValue" }
    {}


### Class format
* Declare methods and data members in public first, protected, and private last scope order

class SpiceClass
{
    public:

       //
       // Enums
       //
       enum class SpiceEnumeration : int {
          START  = 8,
          MIDDLE = 12,
          STOP   = 16 };

       //
       // Aliases, typedefs
       //
       using constIter = std::vector< int >::const_iterator;

       //
       // Constructors
       //
       SpiceClass();

       SpiceClass( const std::vector< int >& v );

       SpiceClass(
          const std::vector< int >& someVeryLongName,
          const std::vector< int >& anotherVeryLongName );

       //
       // Copy constructor and assignment operator
       //
       SpiceClass( const SpiceClass& ) = default;

       SpiceClass& operator=( const SpiceClass& ) = default;

       //
       // Move constructor and assignment operator
       //
       SpiceClass( SpiceClass&& ) = delete;

       SpiceClass& operator=( SpiceClass&& ) = delete;

       //
       // Destructor
       //
       virtual ~SpiceClass();

       //
       // Static methods
       //
       static const std::string id() const;

       //
       // Other public methods
       //
       void read( std::istream& s );

       void write( std::ostream& s ) const;

       //
       // Friends declarations
       //
       friend std::ostream& operator<< (std::ostream& os, const SpiceClass& obj);


    protected:

       virtual void formatType();


    private:

       //
       // Static data members
       //
       static std::string       s_id;

       //
       // Other data members
       //
       SpiceEnumeration         m_type;

       //
       // Align data members (use an editor's snippet with standard
       // column offset for data members)
       //
       std::vector< SpiceType > m_vector;

       std::string              m_string;
};

## Coding Standards

### On the use of Native Types, and SPICE Primitive Types

* When we must use 64-bit integer types, and when the types are not already dictated by C++ compatibility concerns, we agree to use

                 std::int64_t
                 std::uint64_t

for signed and unsigned integers, respectively. Note that these type are not strictly portable, since their existence is not guaranteed by the ISO standard. They are however supported by all compilers we plan to support.

Where we're interfacing with C++ code that already uses:

                 std::size_t

we should use that type. Note: in practice this type likely will always be equivalent to std::uint64_t.

* The signed type:

                std::ptrdiff_t

is guaranteed to exist, but its size, while in practice probably always 64 bits, is not guaranteed in terms of bits. Instead the size guarantee is related to sufficient capacity to support pointer arithmetic.

The guidance is to not use this type except for pointer arithmetic or C++ compatibility.  Note: in practice this type likely will always be equivalent to:

                 std::int64_t

* In general, use signed types for integer arithmetic, except for the special case of addition of unsigned values.  Note that:

                - Any subtraction should be done using signed types

                - When signed and unsigned types must be compared, we should
                  convert the unsigned type to signed, not the other way
                  around.

* When cross-Toolkit compatibility is required, we should either use

                       SpiceInt

or a "using" directive that maps to SpiceInt, as we've done for body and frame IDs.



### Prefer prefix to postfix

### Should I use "using namespace std;"
* Do not (namespaces are used to prevent namespace collisions, so don't dump one namespace into another)
* Prefer using the "using" declaration over using namespaces as qualifiers to bring explicit names into the scope:

   //
   // Prefer this style
   //
   using std::endl;

   //
   // Use aliases to simplify if necessary
   //
   using std_cout = std::cout;

   std_cout << "Values" << endl;

### Do not modify the precision of std::cout

Modifying the precision of std::cout can affect the downstream output of compiled programs; our test families, for example.  If you need to modify the precision of your console output, make use of a temporary variable.

   //
   // Prefer this style
   //
   std::ostringstream tmp;
   tmp << std::setprecision(20) << someDoubleValue << std::endl;
   std::cout << tmp.str();

   //
   // Do NOT do this
   //
   std::ostringstream tmp;
   std::cout << std::setprecision(20) << someDoubleValue << std::endl;


### Use correct resource handling

* **Resource Acquisition is Initialization** (RAII) idiom

* Smart pointers

    DO:    std::unique_ptr< SpiceClass > ptr( new SpiceClass );
    DON'T: SpiceClass* ptr( new SPICEClass );

### Class constructors and destructors

* Initialize data members in their declaration order
* Prefer initialization list to in-body assignment of the data members to avoid resource leaks (see Item #10 of "More Effective C++")

    SPICEClass:SPICEClass():
       mStream( open( "filename.txt" ) ),
       ...
    {}

instead of:

    SPICEClass:SPICEClass():
       mStream(),
       ...
    {
       mStream = open( "filename.txt" );
    }

* Do not write constructors that return modified input parameters.

* Do not write custom destructors.  They are not guaranteed to execute in C++11 when an object goes out of scope.

* For **all** SPICE 2.0 classes, the class must either:

  1. Be declared **final**, if the class is not intended to be inherited from.  This is the preferred approach, when possible.
  2. Declare a virtual destructor, if the class is intended to be inherited from.


* Prevent exceptions from leaving destructors (see Item #11 of "More Effective C++")



### Try/Catch Blocks

* Ensure that every method has try/catch logic, unless it qualifies for an exemption.
* In constructors, an example of a try/catch implementation is as follows:

    DAFSearchState()
      try:
         m_reader     { spice2::daf::createDAFReader() },
         m_beginIter  { DAFReader::const_iterator{} },
         m_endIter    { m_beginIter },
         m_currentIter{ m_beginIter },
         m_atBegin    { true }
      {}
      catch( ... )
      {
         throw SpiceException{ __func__, __FILE__, __LINE__ };
      }

* In general, method code should follow that same pattern:

      try
      {

         Some stuff...

      }
      catch( ... )
      {
         throw SpiceException{ __func__, __FILE__, __LINE__ };
      }





### Don't use C-style casting
* Use \<const_cast\>
* Use \<static_cast\>
* Use \<dynamic_cast\>
* Use \<reinterpret_cast\>

### Minimize definitional dependencies. Avoid cyclic dependencies.
* Don't **#include** a definition when a forward declaration will do

   class Child;
   class Parent
   {
      std::unique_ptr< Child > m_child;
   };

  * Forward declaring symbols from namespace **std::** yields undefined behavior (per Google style guidelines).

* **#include \<iosfwd\>** in a header file (not **#include \<iostream\>**) if you use only a reference or a pointer to any of the standard input/output library types

### Use header file protectors

* Eliminate multiple inclusions of the same header file in a standard way. For header.hpp file:

   #ifndef HAVE_SPICE2_HEADER
   #define HAVE_SPICE2_HEADER

      ...

   #endif
   //
   // HAVE_SPICE2_HEADER
   //

* Use **HAVE_SPICE2_CLASSNAME** naming convention for the guarding macro

### No second order includes

* Don't rely on a second order includes and provide **#include** directive for each necessary header file to be included. For example, if "class1.hpp" includes "class2.hpp", and the code requires definition of both classes at compile time, then include both header files into the compilation module:

   //
   // DO:
   //
   #include "class1.hpp"
   #include "class2.hpp"

   //
   // DO NOT even though it is sufficient for the time being:
   //
   #include "class1.hpp"

### Explicitly delete unneeded class methods that are implicitly generated by the compiler otherwise

class SpiceClass
{
public:
    //
    // Constructors
    //
    SpiceClass() = delete;
    explicit SpiceClass( const int value );

    //
    // Destructor
    //
    virtual ~SpiceClass();

    //
    // Copy constructor and assignment operator
    //
    SpiceClass( const SpiceClass& ) = delete;
    SpiceClass& operator=( const SpiceClass& ) = delete;

    //
    // Move constructor and assignment operator
    //
    SpiceClass( SpiceClass&& ) = delete;
    SpiceClass& operator=( SpiceClass&& ) = delete;
  };

## &#x1F534; Lambda expressions

Format parameters and bodies as for any other function, and capture lists like other comma-separated lists:

   int x = 0;
   auto x_plus_n = [ &x ]( int n ) -> int { return x + n; }

## Avoid magic numbers

## Variable initialization
* Declare variables as locally as possible
* Never declare a variable before you can initialize it sensibly
* Always initialize variables

## Operator overloading
* Overload operators only for good reason
* Preserve natural semantics
* When defining binary arithmetic operators, provide their assignment versions as well: if you **a+b**, also **a+=b** (**operator+** is implemented in terms of **operator+=**)

## Take parameters appropriately by value, smart pointer, or reference
* Always const-qualify all pointers and references to input-only parameters
* Prefer taking inputs of primitive types (char, int, float...) and value objects that are cheap to copy by value (complex<float>)

## Prefer std:: algorithms to handwritten loops

## Don't derive from std:: containers as they don't have virtual destructors

## Rely on _return value optimization_ where possible to avoid creation of temporary objects (which might be expensive to create) (see Item #20 of "More Effective C++)
