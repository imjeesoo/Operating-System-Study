#include "kernel/types.h"
#include "user/user.h"

int main()
{
  volatile int i;
  for(i = 0; i < 1000000000; i++){
    if (i % 1000000 == 0) {
    }
  }
  exit(0);
}
