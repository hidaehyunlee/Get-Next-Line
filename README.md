# Get Next Line

> Reading a line on a fd is way too tedious.



### 1. 소개

```c
int get_next_line(int fd, char **line);
```

#### **Turn in ﬁles**

get_next_line.c, get_next_line_utils.c, get_next_line.h

#### **Parameters**

\#1. file descriptor for reading

\#2. The value of what has been read

#### **Return value**

1 : A line has been read

0 : EOF has been reached

-1 : An error happened

#### **External functs.**

read, malloc, free

#### **Description**

Write a function which returns a line read from a file descriptor, without the newline.



### 2. 목표

- GNL 함수를 loop 안에서 호출하면 fd의 텍스트를 EOF가 올 때 까지 한 번에 한 줄씩 읽을 수 있다.
- GNL 함수를 처음 호출 했을 때 파일을 끝까지 읽었다 하더라도, 두 번째 호출했을 때는 두 번째 line부터 시작해야한다.
- file로부터, redirection으로부터, stdin으로부터 읽었을 때 함수가 제대로 동작해야 한다.
- 이 프로그램은 -D BUFFER_SIZE=xx 플래그를 붙여서 컴파일 해야 한다. 즉, read 함수는 표준입력으로 또는 파일로부터 읽어들이기 위해서 컴파일할 때 정의된 BUFFER_SIZE를 사용해야 한다.
- BUFFER_SIZE가 1일 때도, 9999일 때도, 10000000 (1000만)일 때도 함수가 제대로 동작해야 한다.
- Single Static Variable로 get_next_line 성공하기.
- 다중 file descriptor를 관리 할 수 있는 함수로 만들기. 예를 들어 file descriptor 3, 4, 5를 읽을 수 있는 경우, get_next_line은 3에서 한 번, 4에서 한 번, 다시 3에 서 한 번, 5에서 한 번 호출할 수 있어야 한다. 각 descriptor의 reading thread를 잃지 않으면서 말이다.



### 3. 삽질의 기록들

프로젝트를 진행하기 위해서 몇 가지 선행 지식들을 공부할 필요가 있었고, 코드를 짜면서도 고민해야할 지점들이 많았다. 그 삽질의 기록(?)을 [블로그](https://velog.io/@hidaehyunlee/GetNextLine-%EC%82%BD%EC%A7%88%EC%9D%98-%EA%B8%B0%EB%A1%9D)에 정리해 두었다.

