// 두 개의 자식 프로세스를 생성하여 pipe() 시스템콜을 사용해
// 자식1의 표준출력(stdout, fd 1)을 자식2의 표준입력(stdin, fd 0)으로 연결하는 프로그램

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int rc_pipe[2];
    pipe(rc_pipe);

    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc1 == 0) {
        close(rc_pipe[0]);
        dup2(rc_pipe[1], 1); //stdout -> pipe write
        close(rc_pipe[1]);

        printf("hello. I'm child 1.\n");
        exit(0);
    }

    int rc2 = fork();
    if (rc2 < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc2 == 0) {
        close(rc_pipe[1]);
        dup2(rc_pipe[0], 0); //stdin <- pipe read
        close(rc_pipe[0]);

        char buf[100];
        int len = read(0, buf, sizeof(buf) - 1);
        buf[len] = '\0';
        
        printf("child 2 received: %s", buf);
        exit(0);
    }

    close(rc_pipe[0]);
    close(rc_pipe[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
