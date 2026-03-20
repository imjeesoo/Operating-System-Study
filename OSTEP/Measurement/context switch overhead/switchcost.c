// context switch overhead 비용을 측정해본다.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h> //CPU 고정 관련 헤더

int main(int argc, char *argv[]){

    long i;
    long count = atol(argv[1]);
    char buf = 'x';

    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);

    //부모와 자식이 같은 CPU 코어에서만 돌도록 고정한다.
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
        fprintf(stderr,"sched_setaffinity");
        exit(1);
    }   
    
    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr,"fork failed.\n");
        exit(1);

    } else if(rc == 0) {
        close(p1[1]);
        close(p2[0]);
    
        for (i = 0; i < count; i++) {
            read(p1[0],&buf,1);
            write(p2[1],&buf,1);
        }

        close(p1[0]);
        close(p2[1]);

        exit(0);

     } else {
        close(p1[0]);
        close(p2[1]);

        struct timespec start,end;
        clock_gettime(CLOCK_MONOTONIC,&start);

        for (i=0; i < count; i++) {
            write(p1[1],&buf,1);
            read(p2[0],&buf,1);
        }

        clock_gettime(CLOCK_MONOTONIC,&end);

        close(p1[1]);
        close(p2[0]);

        wait(NULL);

        double cost_result = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Total time : %.6f seconds\n",cost_result);
        printf("Average context switch cost : %.6f microseconds\n",(cost_result/(2*count)) * 1e6);
        printf("Average context switch cost : %.2f nano second.\n",(cost_result/(2*count)) * 1e9);

        exit(0);
     }

    return 0;
}
