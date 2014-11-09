#include <stdio.h>
#include <Windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}


int main() {
	
	system("mode con:cols=130 lines=45");
	int hakbun, pw;
	int i;

	gotoxy(35,12);
	printf("*Togedule*");
	gotoxy(35,14);
	printf("- login -");

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

	
	gotoxy(25, 17);
	printf("학번 :");
	gotoxy(25, 19);
	printf("PW : ");
	gotoxy(33, 17);
	scanf("%d", &hakbun);
	gotoxy(30, 19);
	scanf("%d", &pw);
	gotoxy(50, 35);
	printf("환영합니다!");
	gotoxy(50, 36);
	
}
