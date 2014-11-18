#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include <time.h>

//B(뒤로가기), X(종료)를 입력해야하기 때문에 전부 char 형으로 입력을 받아야한다.

//회원 구조체
typedef struct structMember{  
	char name[13];  //회원이름
	char ID[8];  //학번
	char password[14];  //비밀번호  
	char backupPassword[14];  //고유코드
}structMember;

//약속 구조체
typedef struct structPromise{ 
	char name [41];  //약속명
	char *promisePlace;  //약속장소 이름을 모르기 때문에 DB의 문자열을 가리킨다
    char promiseTime[6];  //약속시간
	char Promisedate[10];  //약속날짜
	char **promiseFriendsName;  //인원수의 입력을 받아 동적할당 {“김동희”, “이설희”}
	//비용 포인터 만들어야함
}structPromise;

//과목 구조체
typedef struct structSubject{  
	char subjectName[15];  //과목이름
	char subjectClass[10];  //입력받는 과목교시  ->1,2,3 ->함수로 처리해야함.
}structSubject;

//시간표 구조체
typedef struct structTimetable{  //13교시 -> 13을 입력하기 때문에 2개
	structSubject timetable[5][13];  
}structTimetable;

//비용 구조체
typedef struct structCost{
	char cost;
}structCost;

//char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"}; // 전역변수.

void login();  //로그인
void membership();  //회원가입
void mainMenu();  //로그인 후 메인메뉴
void pwFind();  //비밀번호 찾기


//파일입출력 모드 
//r - 읽기모드
//파일이 없으면 에러발생
//
//r+ - 읽기,쓰기모드. 
//파일이 없으면 에러
//
//w - 쓰기모드
//(이모드로 여는 순간 파일의 내용이 다 날라감... 다들 주의바람.수정메뉴같은거에 절대쓰지말것)
//(나 그래서 뻘짓함....이러지말라고 이글을 남김...)
//파일이 없으면 새로만들고 기존의 파일이 있으면 그 이전의 내용은 없어지고 
//파일의 처음부터 쓴다.
//이모드로는 파일 내용을 읽을수없다.
//
//w+ - 읽기,쓰기모드. 
//파일이 없으면 새로 만들고 기존의 파일이 있으면 그 이전의 내용은 없어지고 
//파일의 처음부터 쓴다.
//
//a - 추가쓰기 모드
//파일이 없으면 새로만든다.
//기존파일이 있으면 그파일의 가장 뒤부터 파일에 추가
//
//a+ - 추가쓰기모드
//파일이 없으면 새로 만들고, 기존의 파일이있으면 그파일의 가장 뒤부터 추가한다.
//파일의 어느 곳이나 읽기는 가능하나 쓰기는 파일끝에 추가적으로만 가능하다.