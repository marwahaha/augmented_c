#ifndef __AKST_ARGS__
#define __AKST_ARGS__

#include <stdio.h>

struct args;

struct args *parse_args(int argc, char **args);
void free_args(struct args *);
void fprintargs(FILE *, struct args *);

#endif
