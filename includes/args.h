#ifndef __AKST_ARGS__
#define __AKST_ARGS__

#include <stdint.h>
#include <stdio.h>

/**
 * Structural representation of arguments.
 */
struct args;

/**
 * Takes the arguments passed to `int main(int argc, char **args)',
 * and returns an `struct args` pointer, if NULL arguments failed
 * to parse
 */
struct args *parse_args(int argc, char **args);

/**
 * Frees args, and handles the proper junk optional, write file
 */
void free_args(struct args *);

/**
 * Name is potenailly miss leading so I may need to comsider
 * renaming this function.
 */
void fprintargs(FILE *, struct args *);

/**
 * Gets the write file
 */
const char *arg__main_path(struct args *);

/**
 * Gets the output file
 */
const char *arg__out_dir(struct args *);

#endif

