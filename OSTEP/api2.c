//file open 후 fork 시 부모프로세스와 자식프로세스간 open된 file descriptor에 접근 가능한지, 동시에 write가능한지 test
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
    int fd = open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
    if (fd < 0) {
        fprintf(stderr,"open failed.\n");
        exit(1);
    }

    int rc = fork(); 
    if (rc < 0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("hello.I'm child.\n");
      //fd를 통해 write 하여 공유된 discriptor에 접근하는지 확인.
        write(fd,"hello.I'm child!\n",17);
    } else {
      // wait()함수가 없으므로, 순서는 보장되지 않을것으로 예측. 내용이 덮어쓰기 되지 않는지 test.
        printf("hello.I'm parent.\n");
        write(fd,"hello.I'm parent!\n",18);
    }

    close(fd);
    return 0;
}
