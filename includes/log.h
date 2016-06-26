#ifndef __AKST_ERROR__
#define __AKST_ERROR__

#include <stdio.h>

#define __logfactory__(TYPE, FORMAT) \
  fprintf(stderr, "[" TYPE ":(%s:%u)]: ", __FILE__, __LINE__); \
  fprintf(stderr, FORMAT); \
  fprintf(stderr, "\n");

#ifdef AKST_LOG_ERROR
#define lerror(...) __logfactory__("ERROR", __VA_ARGS__);
#else
#define lerror(...);
#endif

#ifdef AKST_LOG_WARN
#define lwarn(...) __logfactory__("WARN", __VA_ARGS__);
#else
#define lwarn(...);
#endif

#ifdef AKST_LOG_INFO
#define linfo(...) __logfactory__("INFO", __VA_ARGS__);
#else
#define linfo(...);
#endif

#ifdef AKST_LOG_DEBUG
#define ldebug(...) __logfactory__("DEBUG", __VA_ARGS__);
#else
#define ldebug(...);
#endif

#endif

