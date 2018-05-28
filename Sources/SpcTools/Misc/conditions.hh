#ifndef CONDITIONS_HH
#define CONDITIONS_HH

// ============================================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     conditions.hh
//
// = AUTHOR(S)
//     Frederic Guidec (EPFL)
//     Alexandre Dupuis
// 
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:05:17 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
// ============================================================================

// = DESCRIPTION 
//
// The macros 'require', 'always_require', 'ensure' and
// 'always_ensure' permit to check preconditions and postconditions in
// C or C++ code.
//
// Preconditions can be expressed and checked using the macros
// 'require' and 'always_require'
//
// Postconditions can be expressed and checked using the macros
// 'ensure' and 'always_ensure'
//
// The checking of assertions expressed with 'require' can be enabled
// at compile-time by setting the 'ASSERT_REQUIRE' macro
//
// The checking of assertions expressed with 'ensure' can be enabled
// at compile-time by setting the 'ASSERT_ENSURE' macro
//
// The checking of assertions expressed with 'always_require' or
// 'always_ensure' cannot be disabled
//
// = EXAMPLE OF USE
//
// void setIthValue (int i, float v)
// {
//  require ("i_valid", (i >=0) && (i < iMax));
//  myArray[i] = v;
//  ensure ("setComplete", myArray[i] == v);
// }
//

#include <assert.h>
#include <stdio.h>

// ======================================================================
// = PRECONDITIONS
// ======================================================================

// void require (const char* assertion_name, int expression)
//   If ASSERT_REQUIRE is defined, and 'expression' is not zero, 
//   print an error message and abort.
//   If ASSERT_REQUIRE is not defined, do nothing

#ifdef ASSERT_REQUIRE

#define require(assertion_name, expression) \
    if (!(expression)) { \
	fprintf(stderr, "Precondition '%s' violated\n", assertion_name); \
	assert (expression); }

#else  /* Not ASSERT_REQUIRE */

#define require(assertion_name, expression)   ((void) 0)

#endif /* ASSERT_REQUIRE */

// void always_require (const char* assertion_name, int expression)
//   If 'expression' is not zero, print an error message and abort.

#define always_require(assertion_name,  expression) \
if (!(expression)) { \
     fprintf(stderr, "Precondition '%s' violated\n", assertion_name); \
     assert (expression); }

// ======================================================================
// = POSTCONDITIONS
// ======================================================================

// void ensure (const char* assertion_name, int expression)
//   If ASSERT_ENSURE is defined, and 'expression' is not zero, 
//   print an error message and abort.
//   If ASSERT_ENSURE is not defined, do nothing


#ifdef ASSERT_ENSURE

#define ensure(assertion_name,  expression) \
if (!(expression)) { \
     fprintf(stderr, "Postcondition '%s' violated\n", assertion_name); \
     assert (expression); }

#else  /* Not ASSERT_ENSURE */

#define ensure(assertion_name, expression)   ((void) 0)

#endif /* ASSERT_ENSURE */

// void always_ensure (const char* assertion_name, int expression)
//   If 'expression' is not zero, print an error message and abort.

#define always_ensure(assertion_name,  expression) \
if (!(expression)) { \
     fprintf(stderr, "Postcondition '%s' violated\n", assertion_name); \
     assert (expression); }

#endif
