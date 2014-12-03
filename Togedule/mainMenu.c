#include"structHeader.h"

void mainMenu(structMember *s){
	int x=10, y=7;  //좌표
	char menuSelect;
	int check;

	//----------------------------UI그리기-----------------------------------------------
	while(1){
		check=1;
		screenBorderDraw();  //전체틀출력
		listBorderDraw(40,13);  //메뉴틀출력

		gotoxy(58,10);
		printf("%s님 안녕하세요!",s->name);
		gotoxy(40+x,11+y); 
		printf("1. 내 상태보기"); 
		gotoxy(40+x,13+y); 
		printf("2. 시간표 만들기");
		gotoxy(40+x,15+y); 
		printf("3. 약속 잡아주세요"); 
		gotoxy(40+x,17+y); 
		printf("4. 돈 나줘누세요"); 
		gotoxy(40+x,19+y);
		printf("5. 나갈래요"); 
		gotoxy(73,29);
		printf("메뉴선택>> "); 
		scanf("%c",&menuSelect); fflush(stdin);

		switch(menuSelect){
		case '1' :  //내 상태보기
			mystatus(s);
			break;
		case '2' :  //시간표 만들기
			timetableMenu(s);
			break;
		case '3' :  //약속 잡아주세요
			while(check){check=promise(s);}
			break;
		case '4' :  //돈 나눠주세요
			moneyShare1(s); break;
		case '5' :  //나갈래요
			exit(1);
		}
	}
}

