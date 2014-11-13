#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//B(뒤로가기), X(종료)를 입력해야하기 때문에 전부 char 형으로 입력을 받아야한다.

//회원 구조체
typedef struct structMember{  
	char name[13];  //회원이름
	char ID[7];  //학번
	char password[13];  
	char backupPassword[13];  //고유코드
}structMember;

//약속 구조체
typedef struct structPromise{ 
	char name [41];  //약속명
	char *promisePlace;  //약속장소 이름을 모르기 때문에 DB의 문자열을 가리킨다
    char promiseTime[6];  //약속시간
	char Promisedate[10];  //약속날짜
	char **promiseFriendsName;  //인원수의 입력을 받아 동적할당 {“김동희”, “이설희”}
	//비용 포인터 만들어야함
}structMember;

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

char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"}; // 전역변수.
