#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
  char *nargv[MAXARG];

  //check arguments
  if(argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9')){
    fprintf(2, "Usage: %s mask command\n", argv[0]);
    exit(1);
  }

  int mask = atoi(argv[1]);

  // Call trace to set trace mask for current process
  if (trace(mask) < 0) {
    fprintf(2, "%s: trace failed\n", argv[0]);
    exit(1);
  }

  // Prepare arguments for exec
  for(i = 2; i < argc && i < MAXARG; i++){
    nargv[i-2] = argv[i];
  }
  nargv[i-2] = 0; // Null-terminate the argument list

  // Execute the command
  exec(nargv[0], nargv);

  fprintf(2, "exec %s failed\n", nargv[0]);
  exit(1);
}