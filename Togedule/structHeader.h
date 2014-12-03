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
	char promisePlace[40];  //장소 이름을 모르기 때문에 포인터 DB의 문자열을 가리킬 것이다 //장소DB 계획이 아직 구체적으로 안나와서 일단 배열로 분배.
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

/*-------------------------------구조체정의 끝--------------------------------*

/*-------------------------------함수원형선언--------------------------------*/
//로그인관련
void login(structMember *s);  //로그인
void membership();  //회원가입
void mainMenu(structMember *s);  //로그인 후 메인메뉴
void pwFind();  //비밀번호 찾기

//내상태보기
void mystatus(structMember *s);  //상태보기시작
void mystatus_promiseList(char *DBname);  //내 상태보기 약속리스트 출력

//시간표관련
void timetableMenu(structMember *s); //시간표메뉴함수
void timetableDraw(structMember *s); //시간표그리기함수
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalCnt, structMember *s); //시간표 txt로 저장하는 함수
void classAtoi(char *dayOfWeek, int *savedClass); //교시를 char->int으로 바꾸어주는 함수
int checkOverlappingClass(structSubject* subjectPointer,structSubject subject,int subjectTotalCnt); //중복교시체크함수
void InputSubjectCnt(structMember *s); // 시간표만들기 - 월~금 과목갯수 입력 함수
void InputSubjectNameAndClass( int* SubjectCntOfday, int subjectTotalCnt, structMember *s) ; // 시간표만들기 - 이름/교시 입력함수
void modifyMenu(structMember *s); //시간표수정메뉴함수
void modifySubjectInfo(structMember *s); // 시간표 과목정보 수정함수
void addSubject(structMember *s); //시간표 과목 추가
void removeSubject(structMember *s); //시간표 과목 삭제
void sortTimetable(structSubject* subjectPointer,int subjectTotalCnt, structMember *s); // 시간표 (요일)정렬 함수
void removeTimetable(structMember *s); //시간표삭제함수(시간표txt파일삭제)

//약속관련

void promiseChange(char *DBname,char *logID);   //약속수정 시작-> 리스트 출력-> 리스트 선택-> 약속수정항목 선택함수 호출-> 약속저장함수들 호출 하는 함수
int selectChange(char *DBname, struct structPromise *old, int listnumber, char **name,int CombineTimetable[5][13],char checkPlace[3]);    //약속수정항목 선택
void changePromiseName(struct structPromise *old);   //약속수정-> 약속명 수정
void changePlace(char *DBname, struct structPromise *old);  //약속수정-> 약속장소 수정
int changeDate(struct structPromise *old,int newCombineTimetable[5][13]);    //약속수정-> 약속날짜 수정
void changeTime(struct structPromise *old,int newCombineTimetable[5][13],int dayofweek);   //약속수정-> 약속시간 수정
int changeName(char *DBname,int CombineTimetable[5][13],int newCombineTimetable[5][13] ,struct structPromise *old);    //약속수정-> 약속을 같이잡을 회원들 이름 수정
int checkDateTime(int CombineTimetable[5][13], struct structPromise *old);   //약속수정-> 현재 약속이 가능한지 체크. 이름을 수정했을때 불러서 바뀐 통합시간표를 근거로 체크
void saveMyPromiseList(struct structPromise *promiseList, char *DBname, int listCount,char **friendsName,char **cost,int listnumber);   //약속리스트 수정부분을 맞는 위치에 저장하는 함수
void deletePromise(char *friendID,char *promiseName, char *promiseDate, char *promiseTime);    //약속리스트를 읽고 매개변수로 주어진 약속이름, 약속날짜, 약속시간과 같은 약속항목을 찾아 삭제하는 함수 약속이 그거 하나만 있었을 때는 파일을 날린다.
void showBG(char copyPromiseName[41],char copyPromisePlace[40],char copyPromisedate[10],char copyPromiseTime[6],char copyName[50]);    //약속수정 UI만드는 도중 화면을 리셋하고 수정전 내용을 출력하는 부분이 필요해서 만든 함수
void saveFriendPromiseList(struct structPromise *promiseList, char *DBname,char **friendsName,char **cost,int listnumber,struct structPromise *newPromise);
//약속 상세보기 부분
int ViewAllPromise(char *DBname,char *logID);
//약속 삭제부분
int deleteAllPromise(char *DBname,char *logID) ;
//약속장소고르기,저장부분
void promisePlace(char *DBname,struct structPromise *newPromise);   //약속 장소 고르기 함수
void saveNewpromise(char *DBname,struct structPromise *newPromise);   //기존 약속리스트에 새 약속을 추가하는 함수
//약속만들기부분
int promise(structMember *s);   //약속만들기 메인함수. 메뉴선택을 입력받는다.
void showMenu();    //약속만들기 메인메뉴출력함수
void promiseList(char *DBname);   //회원의 약속리스트를 출력하는 함수
void promiseCreatConsole(char *DBname, char *logID);    //약속만들기 함수. 입력받는 모든 함수들 호출, 저장하는 함수들 호출
void selectName(char *DBname,struct structPromise *newPromise);   //약속명을 입력받는 함수
int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise);    //회원수를 입력받고 회원수만큼 이름을 입력받아 이름검색함수를 호출하는 함수
int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13],char *MyDB,char IDList[4][13]);   //이름검색함수 (검색할이름, 함께하는회원중 리스트에 안올라간 회원수,새약속구조체,통합시간표) 를 매개변수로 받는다
void setMajor(char ID[8],char Major[20]);   //학번 3번째,4번째 자리를 바탕으로 학과정보를 알아내는 함수
int recordCombineTimetable(int CombineTimetable[5][13], char *DBname);   //통합시간표에 정보를 추가하는 함수, 통합시간표와 '학번+이름' 문자열을 매개변수로 받아서 처리
int selectDate(int CombineTimetable[5][13],structPromise *newPromise);    //만들 약속의 날짜 입력받는 함수
int callendar(int Month);    //달력출력함수. 월을 매개변수로 넘겨받는다. selectDate 함수에서 입력받은 달을 넘겨받음.
int weekday(int year, int month, int day);   //년도, 월, 일 을 매개변수로 받아 요일 찾는 함수. 리턴값은 정수형태
void selectTime(int CombineTimetable[5][13],structPromise *newPromise,int dayofWeek);    //만들 약속의 시간을 입력받는 함수
void saveFriendsID(char ID[8], char *DB);    //학번을 매개변수로 받아 학번+이름을 알아내는 함수
void changeLocation( char* str );    //문자열 처리함수 맨 앞의 글자를 없애고 한글자씩 땡기는 함수

//비용관련
void moneyShare1(structMember *s);  //돈나눠주세요 시작
void moneyShare2();  //돈나누는 모드 고르는 기능

//공통으로 쓰이는 것들
void gotoxy(int x, int y);  //좌표설정
void screenBorderDraw(); //전체화면틀출력함수
void listBorderDraw(int x, int y); //메뉴틀출력함수
void promiselistBorderDraw(int x, int y);  ////약속리스트틀출력(좁은것)
void listBorderDraw1(int x, int y);  //약속리스트틀출력(넓은것)
void listBorderDraw2(int x, int y);	//이름검색리스트틀출력
void listBorderDraw3(int x, int y);	//약속함께할회원리스트틀출력
void checkInput();  //버퍼에 남아있는거 체크
void setcolor(int color, int bgcolor);  //글자색,글자배경색 변경

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