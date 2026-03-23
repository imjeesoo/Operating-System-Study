#include "kernel/types.h"
#include "kernel/procinfo.h"
#include "user/user.h"

#define MAXPROC 64

int
main(void)
{
  struct procinfo table[MAXPROC];
  int n, i;

  n = getprocs(MAXPROC, table);
  if(n < 0){
    printf("getprocs failed\n");
    exit(1);
  }

  printf("PID\tSTATE\t\tNAME\n");
  for(i = 0; i < n; i++){
    printf("%d\t%s\t%s\n",
           table[i].pid,
           table[i].state,
           table[i].name);
  }

  exit(0);
}
