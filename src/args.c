#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "log.h"
#include "args.h"

struct args {
  // optional, can be equal to NULL
  char * const out_dir;

  // is the length of `rfiles'
  char * const main_path;
};

struct args *parse_args(int argc, char **args) {
  ldebug("Parsing arguments");
  char *mfile = NULL;
  char *ofile = NULL;

  /**
   * Because it's a heckin pain to write this out by hand
   * also C has no standardised higher level functions :(
   */
  #define free_memory(...) { \
    if (ofile != NULL) free(ofile); \
    if (mfile != NULL) free(mfile); \
  }

  for (int i = 1; i < argc; i++) {
    if (args[i][0] == '-') switch (args[i][1]) {
      case '-': switch (args[i][2]) {
        case ' ':
          break;
        default:
          lerror("Unknown flag");
          free_memory();
          return NULL;
      } break;
      case 'o': {
        ldebug("  Paring `-o'");
        if (i + 1 >= argc) {
          lerror("Expected argument for write file.");
          free_memory();
          return NULL;
        }
        else if (ofile == NULL) {
          ofile = strdup(args[++i]);
        }
        else {
          lerror("Can only specify 1 write file.");
          free_memory();
          return NULL;
        }
      } break;
      default: {
        lerror("Unknown flag.");
        free_memory();
        return NULL;
      }
    }
    // when an argument isn't prefixed with a hypen
    // it's a read file name, so we'll add it here.
    else {
      ldebug("  Parsing main name");
      if (mfile == NULL) {
        mfile = strdup(args[i]);
      }
      else {
        lerror("Already parsed main file.");
        free_memory();
        return NULL;
      }
    }
  }

  // allocate the arguments structure.
  struct args *arguments = malloc(sizeof(struct args));
  *arguments = (struct args) {
    .main_path = mfile,
    .out_dir   = ofile,
  };
  return arguments;
}

void free_args(struct args * args) {
  if (args->main_path) free(args->main_path);
  if (args->out_dir) free(args->out_dir);
  free(args);
}

void fprintargs(FILE *writef, struct args * args) {
  fprintf(writef, "arguments:\n");
  fprintf(writef, "  main: %s\n", args->main_path == NULL ? "NULL" : args->main_path);
  fprintf(writef, "  dist: %s\n", args->out_dir == NULL ? "NULL" : args->out_dir);
}

const char *arg__out_dir(struct args * args) {
  return args->out_dir;
}

const char *arg__main_path(struct args * args) {
  return args->main_path;
}

