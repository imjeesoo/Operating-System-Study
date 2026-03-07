//두개의 자식프로세스를 생성하여 pipe()시스템콜을 사용하여 한 자식의 표준출력(stdout,fd1) 을 다른 자식의 입력으로 연결하는 프로그램 작성.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int rc_pipe[2];
    pipe(rc_pipe);
// child1(입력) process 생성 및 dup2를 활용한 표준입력 파일 변경
    int rc[2];
    rc[0] = fork();

    if(rc[0] < 0){
        fprintf(stderr,"fork failed.\n");
    } else if (rc[0] == 0){
        close(rc_pipe[0]);
        dup2(rc_pipe[1], 1);
        close(rc_pipe[1]);
        printf("hello. I'm child 1.\n");
        exit(0);
    } else {
        wait(NULL);
    }
// child2(출력) process 생성 및 dup2를 활용한 표준출력 파일 변경
    rc[1] = fork();

    if (rc[1] < 0){
        fprintf(stderr,"fork failed.\n");
    } else if (rc[1] == 0){
        close(rc_pipe[1]);
        char buf[100];
        int len = read(0, buf, sizeof(buf)-1);
      //읽기 마지막을 알 수 있도록 NULL 을 읽어들인 문자열 마지막 배열에 넣어준다.
        buf[len] = '\0';
        printf("child 2 received : %s", buf);
        exit(0);
    } else {
        close(rc_pipe[0]);
        close(rc_pipe[1]);

        wait(NULL);
    }
    return 0;
}

