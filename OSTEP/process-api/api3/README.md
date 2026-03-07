## 3. api3.c : 파일 디스크립터 할당 규칙과 I/O redirection

### 1) 실험 목적  
파일 디스크립터(FD)의 할당 방식인 '가장 낮은 번호 우선 할당' 규칙을 이해한다.  
표준 출력(stdout, FD 1)을 close()한 후 새로운 파일을 open()하여,  
printf()의 데이터 출력이 터미널이 아닌 파일로 Redirection되는지 확인한다.  
### 2) 구현 세부 사항 (api3.c)  
fork()를 호출하여 자식 프로세스를 생성한다.  
자식 프로세스:  
close(1)을 실행하여 현재 터미널 화면으로 연결된 표준 출력을 닫는다.  
test.txt 파일을 open()한다. 운영체제는 현재 비어 있는 가장 낮은 FD 번호인 1번을 test.txt에 할당한다.  
printf("hello!\n")을 실행한다.  
부모 프로세스: 자식의 작업과 독립적으로 실행을 마친다.  

### 3) 결과 분석 및 결론  
<img width="547" height="83" alt="image" src="https://github.com/user-attachments/assets/748b5335-598e-4f24-ba1b-f201d508f064" />

실행 결과: ./api3 실행 시 터미널 화면에는 아무런 문자열도 출력되지 않음을 확인했다.  
데이터 추적: cat test.txt 명령어 실행 시, 터미널에 출력되어야 할 "hello!"가 파일 내부에 정상적으로 저장되어 있음을 확인했다.  
printf()는 물리적인 화면이 아닌 FD 1번이라는 추상화된 통로로 데이터를 보낸다는 것을 확인했다.  
쉘(Shell)의 redirection(>) 연산자가 내부적으로 close()와 open() 시스템 콜의 조합을 통해 어떻게 동작하는지 그 하부 메커니즘을 이해했다.  
