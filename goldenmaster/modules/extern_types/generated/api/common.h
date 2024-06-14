#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
  #define TEST_EXTERN_TYPES_EXPORT __attribute__ ((dllexport))
#else
  #define TEST_EXTERN_TYPES_EXPORT __declspec(dllexport)
#endif
#else
  #if __GNUC__ >= 4
    #define TEST_EXTERN_TYPES_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define TEST_EXTERN_TYPES_EXPORT
  #endif
#endif

#ifndef THIRD_PARTY_INCLUDES_START
  #if defined __clang__ || defined __GNUC__
    #define THIRD_PARTY_INCLUDES_START \
      _Pragma("GCC diagnostic push")                           /* Pushes the current diagnostic state onto a stack */ \
      _Pragma("GCC diagnostic ignored \"-Wall\"")              /* Ignores warnings related to all enabled diagnostics */ \
      _Pragma("GCC diagnostic ignored \"-Wextra\"")            /* Ignores extra warnings not covered by -Wall */ \
      _Pragma("GCC diagnostic ignored \"-Wpedantic\"")         /* Ignores warnings that are pedantic and not required by the C++ standard */ \
      _Pragma("GCC diagnostic ignored \"-Wconversion\"")       /* Ignores warnings related to implicit type conversions */ \
      _Pragma("GCC diagnostic ignored \"-Wsign-conversion\"")  /* Ignores warnings related to sign conversions */ \
      _Pragma("GCC diagnostic ignored \"-Wshadow\"")           /* Ignores warnings related to variable shadowing */ \
      _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")    /* Ignores warnings related to uninitialized variables */
  #elif defined _MSC_VER
    #define THIRD_PARTY_INCLUDES_START \
      __pragma(warning(push, 0))           /* Pushes the current warning state onto a stack, set warning level to 0 */
  #endif
#endif

#ifndef THIRD_PARTY_INCLUDES_END
  #if defined __clang__ || defined __GNUC__
    #define THIRD_PARTY_INCLUDES_END \
      _Pragma("GCC diagnostic pop")  /* Pops the last diagnostic state from the stack */
  #elif defined _MSC_VER
    #define THIRD_PARTY_INCLUDES_END \
      __pragma(warning(pop))  /* Pops the last warning state from the stack */
  #endif
#endif
