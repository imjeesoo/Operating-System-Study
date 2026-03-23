# Project : xv6-riscv Kernel Customization (System Call Implementation)  
System Call 추가 및 Kernel 동작 이해 프로젝트  
  
## Overview  
운영체제는 User Mode와 Kernel Mode를 분리하여 시스템 자원과 메모리를 보호한다.  
User 프로그램은 하드웨어나 커널 메모리에 직접 접근할 수 없으며, 반드시 System Call을 통해 커널에 진입해야 한다.    
이 과정은 trap을 통해 발생하며, CPU는 권한 레벨을 전환하여 Kernel이 요청을 안전하게 처리하도록 한다.  
본 프로젝트는 xv6 (RISC-V)를 기반으로 User → Kernel 전환 과정과 System Call 처리 흐름을 직접 추적하고 구현하여   
커널의 동작 원리를 이해하는 것을 목표로 한다.  
  
## Objectives  
 - User mode <-> Kernel mode 전환 과정 이해  
 - System Call 전체 흐름 분석 (user -> trap -> kernel -> return)  
 - 커널 내부에서의 자원 접근 방식 이해  
 - xv6 커널을 직접 수정하여 기능 확장 경험 확보  
     
## 진행 내용  
  
### 1. 'ls'명령어를 통한 File System 흐름 분석   
ls 명령어의 실행 과정을 분석하여,  
user program이 File System 정보를 얻기 위해 kernel과 어떻게 상호작용하는지 확인하였다.  
  
### 2. System Call 추가  
user process에서 kernel 기능을 호출하는 System Call 전체 경로를 구현함.  
 **수정 파일:**  
 - kernel/syscall.h: 'SYS_hello' System Call 번호 정의  
 - kernel/syscall.c: 'hello' System Call 테이블 등록  
 - kernel/sysproc.c: `sys_hello` 실제 커널 함수 로직 작성  
 - user/user.h, user/usys.pl: user 영역 라이브러리 인터페이스 추가  
 - user/hello.c: System Call을 테스트하는 user 프로그램 작성  
  
## 실행 결과  
<img width="443" height="279" alt="image" src="https://github.com/user-attachments/assets/870a5fba-9f4d-436c-bfec-2061ec7a363f" />
  
  
## 결론 및 정리  
System Call을 통한 mode 전환을 이해하였다.   
또한 System Call 호출 시 user의 register 정보가 어떻게 PCB(trapframe)에 저장되는지 이해하였다.  
  
### System Call의 구체적 동작 및 흐름은 다음과 같다.  
  
[User Mode]  
1. User Program (hello.c)  
↓  
2. User Library (usys.pl로 어셈블리 생성, a7에 번호 저장)  
↓  
3. ecall 명령어 발생 (Trap → Kernel Mode 전환)  
↓  
4. syscall() 함수 실행 (a7 레지스터 번호 식별)  
↓  
5. sys_hello() 실제 로직 수행  
↓  
6. sret (User Mode 복귀, a0에 결과값 저장)  
   
### user, kernel 부분의 역할을 나눠 흐름을 정리하면 다음과 같다.    
<img width="451" height="205" alt="image" src="https://github.com/user-attachments/assets/9128dabd-bbd2-4ea5-b247-99336b8b6906" />

