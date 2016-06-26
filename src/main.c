#include <stdlib.h>
#include <stdio.h>


#include "args.h"
#include "log.h"


int main(int argc, char **args) {
  struct args *arguments;
  if ((arguments = parse_args(argc, args)) == NULL) {
    fprintf(stderr, "[ERROR]: failed to parse args\n");
    return 1;
  }
  else {
    fprintargs(stdout, arguments);
    free_args(arguments);
    return 0;
  }
}

