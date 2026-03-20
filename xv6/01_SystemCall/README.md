# xv6-riscv System Call Lab

OS의 핵심 원리를 이해하기 위해 진행한 xv6 RISC-V 커스터마이징 프로젝트.

## 진행 내용
### 1. `ls` 명령어 커스텀
- `user/ls.c`를 수정하여 출력 전후에 디버깅 메시지(`ls start ->`, `ls end!`)를 추가함.
- 파일 시스템 탐색 로직과 `stat` 구조체의 데이터 흐름을 분석함.

### 2. `hello` 시스템 콜 추가
- 유저 모드에서 커널 모드의 기능을 호출하는 System Call 전체 과정을 구현함.
- **수정 파일:**
  - kernel/syscall.h: 시스템 콜 번호(`SYS_hello`) 정의
  - kernel/syscall.c7: 시스템 콜 테이블 등록 및 인터페이스 구현
  - kernel/sysproc.c: 실제 커널 함수(`sys_hello`) 로직 작성
  - user/user.h, user/usys.pl: 유저 영역 라이브러리 인터페이스 추가
  - user/hello.c: 시스템 콜을 테스트하는 유저 프로그램 작성

## 📸 실행 결과

- **Trapframe**: 시스템 콜 호출 시 유저의 레지스터 정보가 어떻게 PCB(trapframe)에 저장되는지 학습.
- **Register Convention**: RISC-V의 `a7`(번호), `a0`(인자/리턴값) 활용 방식 이해.
- **User vs Kernel**: 유저 영역과 커널 영역의 메모리 격리 및 `copyin/copyout`의 필요성 체감.
