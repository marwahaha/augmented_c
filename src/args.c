#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "log.h"
#include "args.h"

struct args {
  char*  wfile;
  char** rfiles;
  uint32_t rfilec;
};


struct args *parse_args(int argc, char **args) {
  ldebug("Parsing arguments");
  uint32_t rf_alloc = 1;
  uint32_t rf_count = 0;
  char **rfiles = malloc(sizeof(char *) * rf_alloc);
  char  *wfile  = NULL;

  // TODO better failure behaviour
  for (int i = 1; i < argc; i++) {
    if (args[i][0] == '-') switch (args[i][1]) {
      case '-': {
        //
        // add the rest of the arguments as files
        //
        ldebug("  Parsing `--' file args");
        int rest = argc - ++i;
        int new_count = rf_count + rest;

        if (new_count > rf_alloc) {
          //
          // realloc rfiles, as twice the size, and copy values,
          // grow allocation till it fits all the files. Loops
          // till rf_alloc at least bigger, unlike -f `rest'
          // can be an arbitrary number of files.
          //
          ldebug("    Reallocating for parse phase");
          while (rf_alloc < new_count) rf_alloc = rf_alloc * 2;
          char **new_rfiles = malloc(sizeof(char *) * rf_alloc);

          // copy old allocation into new allocation, plus rest
          memcpy(new_rfiles, rfiles, rf_count);

          // swap the new and old allocation with each other.
          free(rfiles);
          rfiles = new_rfiles;

          ldebug("      rf_alloc => %u", rf_alloc);

        }

        ldebug("    len(rfiles) when past => %u", rf_count);
        ldebug("    len(rfiles) when now  => %u", rf_count + rest);

        // deep copy the remaining arguments
        for (uint32_t j = 0; j < rest; j++) {
          ldebug("    - argument '%s'", args[i + j]);
          rfiles[rf_count + j] = strdup(args[i + j]);
        }

        // `i = argc` results in the loop ending
        i = argc;
        rf_count = rf_count + rest;
      } break;
      case 'f': {
        ldebug("  Paring `-f'");
        if (1 + i < argc) {
          lerror("Expecting argument for read file.");
          free(rfiles);
          return NULL;
        }
        else if (rf_count + 1 > rf_alloc) {
          ldebug("  Reallocing for parse phase");
          ldebug("    rf_alloc              => %u", rf_alloc);
          rf_alloc = 2 * rf_alloc;
          char **new_rfiles = malloc(sizeof(char *) * rf_alloc);
          memcpy(new_rfiles, rfiles, sizeof(char *) * rf_count);
          free(rfiles);
          rfiles = new_rfiles;
        }
        ldebug("  len(rfiles) when past => %u", rf_count);
        rfiles[rf_count++] = args[++i];
        ldebug("  len(rfiles) when now  => %u", rf_count);
      } break;
      case 'o': {
        ldebug("  Paring `-o'");
        if (i + 1 < argc) {
          lerror("Expected argument for write file.");
          free(rfiles);
          return NULL;
        }
        else if (wfile == NULL) {
          wfile = strdup(args[++i]);
        }
        else {
          lerror("Can only specify 1 write file.");
          free(rfiles);
          return NULL;
        }
      } break;
      default: {
        ldebug("  Unknown flag");
        lerror("Unknown flag.");
        free(rfiles);
        return NULL;
      }
    }
    // when an argument isn't prefixed with a hypen
    // it's a read file name, so we'll add it here.
    else {
      ldebug("  Parsing file name");
      if (rf_count + 1 > rf_alloc) {
        ldebug("    Reallocating for parse phase");
        rf_alloc = rf_alloc * 2;
        char **new_rfiles = malloc(rf_alloc * sizeof(char *));
        memcpy(new_rfiles, rfiles, rf_count * sizeof(char *));
        free(rfiles);
        rfiles = new_rfiles;

        ldebug("      rf_alloc => %u", rf_alloc);
      }
      ldebug("    - argument '%s'", args[i]);
      rfiles[rf_count++] = strdup(args[i]);
    }
  }

  // allocate the arguments structure.
  struct args *arguments = malloc(sizeof(struct args));
  *arguments = (struct args) {
    .wfile = wfile,
    .rfiles = rfiles,
    .rfilec = rf_count
  };
  return arguments;
}

void free_args(struct args *args) {
  free(args->rfiles);
  free(args);
}

void fprintargs(FILE *writef, struct args *args) {
  fprintf(writef, "arguments:\n");
  fprintf(writef, "  wfile: %s\n",
          args->wfile == NULL
          ? "stdin"
          : args->wfile);
  fprintf(writef, "  rfilec: %u\n", args->rfilec);
  fprintf(writef, "  rfiles:\n");
  for (uint32_t i = 0; i < args->rfilec; i++) {
    fprintf(writef, "    - %s\n", args->rfiles[i]);
  }
}

