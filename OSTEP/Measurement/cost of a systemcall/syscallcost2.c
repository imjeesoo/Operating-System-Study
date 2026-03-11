//POSIX 권장에 따라 clock_gettime()을 사용하여 시스템콜 비용을 측정해본다.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]){
    
    long count = atol(argv[1]);    
    
    struct timespec start,end;
    
    clock_gettime(CLOCK_MONOTONIC,&start);

    for (long i=0; i < count; i++){
        getpid();
    }   
    
    clock_gettime(CLOCK_MONOTONIC,&end);

    double time_mea = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Total iterations : %ld\n", count);
    printf("Total time : %.6f seconds\n", time_mea);
    printf("Average time per system call: %.2f nanoseconds\n",(time_mea / count) * 1e9);

    return 0;
}
