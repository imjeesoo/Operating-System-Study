# xv6-riscv Kernel Projects

MIT의 xv6 운영체제를 통해 커널의 핵심 메커니즘을 직접 구현하고 실습한 기록입니다.

## Index

### 01. System Call Implementation(./01_SystemCall)
- **핵심 목표**: User ↔ Kernel Mode 전환 및 Trap 매커니즘 이해
- **주요 내용**: 
  - hello(),getproc() 시스템 콜 추가
  - RISC-V 레지스터 및 Trapframe 활용 분석

### 02. Scheduler Customizing(./02_Scheduler)
- **핵심 목표**: 프로세스 스케줄링 정책 분석 및 우선순위 알고리즘 구현
- **주요 내용**: 
  - xv6 기본 Round Robin 분석
  - MLFQ 구현 



## 실습 환경
- **Environment**: Ubuntu (VMware) / QEMU
- **Language**: C, RISC-V Assembly
