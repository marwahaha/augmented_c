#ifndef __AKST_ERROR__
#define __AKST_ERROR__

#include <stdio.h>

#define __logfactor(TYPE) \
  fprintf(stderr, "[" TYPE ":(%s:%u)]: ", __FILE__, __LINE__); \

#ifdef AKST_LOG_ERROR
#define lerror(...) \
  __logfactor("ERROR"); \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n");
#else
#define lerror(...);
#endif

#ifdef AKST_LOG_WARN
#define lwarn(...) \
  __logfactor("WARN"); \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n");
#else
#define lwarn(...);
#endif

#ifdef AKST_LOG_INFO
#define linfo(...) \
  __logfactor("INFO"); \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n");
#else
#define linfo(...);
#endif

#ifdef AKST_LOG_DEBUG
#define ldebug(...) \
  __logfactor("DEBUG"); \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n");
#else
#define ldebug(...);
#endif



#endif

