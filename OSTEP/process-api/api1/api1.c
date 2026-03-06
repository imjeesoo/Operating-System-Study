// 실험 목적 : fork() 후 부모와 자식 간의 변수(메모리) 공유 여부 확인
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main(int argc,char* argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed.\n");
    } else if (rc == 0){
      // 자식 프로세스 : 부모로 부터 복사된 x값을 가진다.
        printf("I'm child. x = %d.\n",x);
        x = 200;
        printf("I'm child. x = %d.\n",x);
    } else {
      // 부모 프로세스 : 자식 프로세스가 종료될 때까지 대기
        wait(NULL);
      // 자식이 x의 값을 200으로 변경했으나, 부모의 x는 독립적이므로 100으로 유지될 것으로 예상
        printf("I'm parent. x = %d.\n",x);
        x = 300;
        printf("I'm parent. x = %d.\n",x);
    // 최종 결과 출력
    printf("x = %d.\n",x);
    }
return 0;
}
