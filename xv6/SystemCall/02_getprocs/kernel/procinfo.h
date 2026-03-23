// kernel/procinfo.h
#ifndef _PROCINFO_H_
#define _PROCINFO_H_

#include "types.h"

struct procinfo {
  int pid;
  char state[16];
  char name[16];
};

#endif
