## System Call Overhead Measurement on Linux

### 실험 개요
 systemcall overhead를 측정해본다.
 가장 단순한 systemcall 인 getpid()를 반복 호출하고, 전체 실행시간을 측정하여 평균 systemcall cost를 계산하였다.
 시간 측정에는 다음 두 가지 방법을 사용하였다.
 1. gettimeofday()
 2. clock_gettime()
 전통적인 시간 측정 방식과 POSIX 권장 방식의 차이를 비교하고,
 현대 시스템 운영체제 성능 측정에 적절한 방식을 이해하는것을 목표로 한다.

### 실험 목적
 1. 시스템콜의 평균 overhead 측정
 2. gettimeofday()와 clock_gettime() 기반 측정 방식 비교
 3. 시스템콜 실행 시 발생하는 모드 전환 비용 이해 (user -> kernel -> user)

### 실험 환경
 - OS : Ubuntu
 - 실행 환경 : VMware Virtual Machine
 - 언어 : C
 - 컴파일러 : GCC
   
### 측정 방법
 1. 시작 시간 기록
 2. getpid() 시스템콜을 n번 반복 호출
    cf) getpid()는 내부 연산이 매우 단순한 시스템콜이므로 커널 진입 및 복귀 비용을 비교적 잘 반영한다.
 4. 종료 시간 기록
 5. 전체 시간을 반복 횟수로 나누어 평균 시스템콜 비용 계산

### 시간 측정 방식
 - gettimeofday() 는 전통적으로 많이 사용되던 시간 측정 함수. 마이크로초 단위시간을 반환한다.
 - clock_gettime() 은 PISIX 권장방식으로, 나노초 단위 시간을 반환한다.
   따라서 현대 Linux환경에서는 clock_gettime() 이 더 적절한 측정 방법으로 사용된다.

### 실험 해석 및 정리 
<img width="668" height="724" alt="image" src="https://github.com/user-attachments/assets/1ee4c32b-22a1-4f2c-aa4c-5bd6d43d27d7" />

 
 이 실험에서 측정되는 값은 시스템콜 자체의 작업 비용이아니라, 다음의 요소들을 포함한 전체 오버헤드이다.
  - trap 발생
  - kernel mode 진입
  - systemcall handler 실행(getpid())
  - return from trap
  - user mode 복귀
 따라서 측정 결과는 시스템콜의 최소 overhead를 근사적으로 나타낸다.
 또한 반복 횟수가 증가할수록 측정값이 안정되는 이유는 시간 측정 오버헤드(시작/끝 측정 비용, loop 비용 등)의 영향이 상대적으로 감소하기 때문이다.
 (즉, 반복횟수가 작을수록 시간측정오버헤드의 영향이 크게미친다.)

 실험을 통해 확인한 것은, 시스템콜은 단순한 함수 호출보다 더 큰 비용이 발생한다.
