#include<stdio.h>
#include < windows.h >
void gotoxy(int x, int y) { 
	COORD Cur; Cur.X=x; Cur.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

int main() {

	int i;
	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 

	gotoxy(33,12);
	printf("-비밀번호 재설정-");

	for(i=0; i<30; i++){
		gotoxy(10+i*2, 10);
		printf("■");
	}

	for(i=0;i <15; i++){
		gotoxy(10, 10+i);
		printf("■");
	}

	for(i=0;i <30; i++){
		gotoxy(10+i*2, 25);
		printf("■");
	}

	for(i=0;i <15; i++){
		gotoxy(68, 10+i);
		printf("■");
	}

	gotoxy(20, 15);
	printf("학번:"); 
	gotoxy(20, 18);
	printf("고유코드:"); 
	gotoxy(20, 21);
	printf("새로운 PW:"); 

	gotoxy(0,40);  //마지막 줄 위치변경
}

