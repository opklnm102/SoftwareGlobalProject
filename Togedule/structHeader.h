#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include <time.h>
#include<malloc.h>
#include <windows.h>
#pragma warning (disable:4996)

//B(뒤로가기), X(종료)를 입력해야하기 때문에 전부 char 형으로 입력을 받아야한다.

/*-------------------------------구조체정의--------------------------------*/
//회원 구조체
typedef struct structMember{  
	char name[13];  //회원이름
	char ID[8];  //학번
	char password[14];  //비밀번호  
	char backupPassword[14];  //고유코드
}structMember;

//약속 구조체
typedef struct structPromise{ 
	char promiseName [41];  //약속명
	char promisePlace[30];  //장소 이름을 모르기 때문에 포인터 DB의 문자열을 가리킬 것이다 //장소DB 계획이 아직 구체적으로 안나와서 일단 배열로 분배.
    char promiseTime[6];  //약속시간
	char Promisedate[10];  //약속날짜
	char promiseFreindsCount[2];//추가
	char **promiseFriendsName;  //인원수의 입력을 받아 동적할당 {“김동희”, “이설희”}
	//비용 포인터 만들어야함
}structPromise;

//과목 구조체
typedef struct Subject{
	char dayOfWeek[4]; //요일
	char subjectName[15]; //과목이름
	char subjectClass[10]; //교시
}structSubject;

//시간표 구조체
typedef struct structTimetable{  //13교시 -> 13을 입력하기 때문에 2개
	structSubject timetable[5][13];  
}structTimetable;

//비용 구조체
typedef struct structCost{
	char cost;
}structCost;

/*-------------------------------구조체정의 끝--------------------------------*/

//char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"}; // 전역변수.

extern char dayOfWeek[5][4]; // 전역변수.

/*-------------------------------함수원형선언--------------------------------*/
//로그인관련
void login(structMember *s);  //로그인
void membership();  //회원가입
void mainMenu(structMember *s);  //로그인 후 메인메뉴
void pwFind();  //비밀번호 찾기

//시간표관련
void timetableMenu(structMember *s); //시간표메뉴함수->시간표 시작
void timetableDraw(); //시간표그리기함수
void InputSubjectCnt(structMember *s); //월~금 과목갯수 입력 함수
void InputSubjectNameAndClass(structMember *s, int* SubjectCntOfday, int subjectSum) ; // 이름/교시 입력함수
void saveTimetalbe(structMember *s,structSubject* subjectPointer, int subjectSum); //시간표 txt로 저장하는 함수
void modifyTimetable(structMember *s); //시간표수정함수
void removeTimetable(structMember *s); //시간표삭제함수(시간표txt파일삭제)

//약속관련
void promise(structMember *s);  //약속 시작
void showMenu();  //약속메뉴들 출력
void promiseList(char *DBname);	// 로그인한 회원의 약속리스트를 불러오는 함수 , 출력만 한다. 없을경우 없다고 출력해준다.
void changeLocation( char* str );
int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13]);
int callendar(int Month);  //달력
int weekday(int year, int month, int day);  //요일 찾는 함수 리턴 정수
void selectDate(int CombineTimetable[5][13],char *DBname,structPromise *newPromise);  //요일, 시간, 날짜 입력받는 함수
void promiseCreatConsole(char *DBname);	//약속만들기 함수 (약속명, 인원수 입력  .이름 검색함수 내부 포함. 약속 리스트 출력)
void promisePlace(char *DBname, struct structPromise *newPromise);  //약속장소 선택
void setMajor(char ID[8], char Major[20]);
void promiseChange(char *DBname);
//비용관련
void moneyShare();  //돈나눠주세요 시작

//공통으로 쓰이는 것들
void gotoxy(int x, int y);  //좌표설정
void screenBorderDraw(); //전체화면틀출력함수
void listBorderDraw(); //메뉴틀출력함수
void checkInput();  //버퍼에 남아있는거 체크


/*-------------------------------함수원형선언 끝--------------------------------*/














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