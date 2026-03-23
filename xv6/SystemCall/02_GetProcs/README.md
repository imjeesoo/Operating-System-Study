# xv6-riscv Process Management (getprocs System Call)  
  
## 프로세스 정보 조회  
  
### Overview  
운영체제는 모든 프로세스의 정보를 PCB(Process Control Block) 형태의 구조체로 관리한다.  
xv6 커널은 struct proc 배열을 통해 시스템 내 모든 프로세스의 상태를 관리하며, 이는 커널 메모리 영역에 존재하여 사용자 프로그램이 직접 접근할 수 없다.  
본 프로젝트는 getprocs 시스템 콜을 구현하여, 커널 내부의 전역 프로세스 테이블(proc[])을 안전하게 탐색하고 사용자에게 프로세스 상태 정보를 전달하는 과정을 학습하는 것을 목표로 한다.  
  
### Objectives  
 - 커널 내부 전역 변수인 proc[NPROC] 배열의 구조 이해  
 - 프로세스 상태(state)의 내부 표현(enum) 이해   
 - 멀티코어 환경에서의 데이터 일관성을 위한 Spinlock(acquire, release) 사용법 익힘   
 - system call 을 통한 커널 <-> 사용자 공간 데이터 전달 흐름 이해
 - 커널 내부 데이터 접근 및 출력 과정 이해 
  
### 진행 내용  
**1. 커널 프로세스 테이블 분석**  
kernel/proc.h 내의 struct proc 구조체를 분석하여 PID, State, Name 중심으로 필요한 정보를 추출하였다.   
UNUSED 상태를 제외한 활성화된 프로세스만을 필터링하도록 설계하였다.
  
**2. System Call 구현**  
getprocs 시스템 콜을 추가하고, 커널 내부에서 proc 배열을 순회하며 각 프로세스 정보를 출력하도록 구현하였다.  
 1) proc 배열을 순회    
 2) 각 proc entry 접근 시 p->lock을 획득하여 race condition 방지  
 3) enum으로 정의된 상태 값을 문자열로 변환  
  
**3. 사용자 프로그램 구현**
user/getprocs.c에서 시스템 콜을 호출하여 커널의 기능을 실행하도록 구현하였다.  
실제 프로세스 정보 출력은 커널 내부에서 수행된다.  
   
**수정 파일:**  
 - kernel/syscall.h: SYS_getprocs 번호 정의   
 - kernel/syscall.c: 시스템 콜 테이블 등록  
 - kernel/sysproc.c: sys_getprocs 구현 (프로세스 배열 순회 및 printf 출력)  
 - user/user.h, user/usys.pl: 사용자 영역 인터페이스 등록  
 - user/getprocs.c: 시스템 콜을 호출하여 결과를 보여주는 사용자 프로그램 작성 (명령어: getprocs)

### 실행 결과
<img width="380" height="189" alt="image" src="https://github.com/user-attachments/assets/c09d06e6-b783-464e-8508-0bd0d4dd95f1" />

getprocs 실행 시 현재 실행 중인 프로세스 목록이 출력됨
PID 1 (init): sleeping 상태
PID 2 (sh): sleeping 상태
PID 3 (getprocs): running 상태 (현재 실행 중인 자신)  
  
### 결론 및 정리  
커널 내부에 정의된 구조체와 전역 변수(프로세스 테이블)를 활용하여 새로운 시스템 콜을 직접 설계하고 구현해 보았다.
이를 통해 사용자 프로그램의 시스템 콜 요청이 커널 모드로 전달되고, 커널 내부에서 프로세스 정보를 순회한 뒤 다시 사용자 모드로 복귀하는 전체 흐름을 코드 수준에서 확인할 수 있었다.
또한 프로세스 상태를 문자열로 변환하여 출력하는 과정을 통해, xv6 커널의 프로세스 관리 구조와 시스템 콜 동작 방식을 보다 구체적으로 이해할 수 있었다.
