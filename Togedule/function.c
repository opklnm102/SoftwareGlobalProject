#include"structHeader.h"

void gotoxy(int x, int y) { 
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

//전체화면틀출력
void screenBorderDraw(){
	int i;

	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	for(i=0;i<44;i++){
		gotoxy(0,i+1);
		printf("■                                                                                                                              ■");
	}

	gotoxy(0,44);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(88,41);
	printf("상위메뉴로 B, 종료 X, 계속하기 S");
}

//메뉴틀출력
void listBorderDraw(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("┌─────────────────────────┐");

	for(i=0; i<20; i++) { 
		gotoxy(x,y+1+i);
		printf("│                                                  │");
	}

	gotoxy(x,y+20);
	printf("└─────────────────────────┘");
}

//약속리스트틀출력
void listBorderDraw1(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("┌───────────────────────────────────────┐");

	for(i=0; i<9; i++) { 
		gotoxy(x,y+1+i);
		printf("│                                                                              │");
	}

	gotoxy(x,y+10);
	printf("└───────────────────────────────────────┘");
}
//이름 검색틀 출력
void listBorderDraw2(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("┌───────────────────────────┐");

	for(i=0; i<12; i++) { 
		gotoxy(x,y+1+i);
		printf("│                                                      │");
	}

	gotoxy(x,y+13);
	printf("└───────────────────────────┘");
}
//함께하는 회원리스트 출력
void listBorderDraw3(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("┌───────────┐");

	for(i=0; i<14; i++) { 
		gotoxy(x,y+1+i);
		printf("│                      │");
	}

	gotoxy(x,y+15);
	printf("└───────────┘");
}
//글자색,글자배경색 변경
void setcolor(int color, int bgcolor){
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor&0xf)<<4) | (color&0xf));
} 