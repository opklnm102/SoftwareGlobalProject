#include<stdio.h>
#include <windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

int main() {
	int i;
	char command;
	char name[10]={' '};
	
	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 
	gotoxy(53,4);
	printf("%s 님 안녕하세요!",name);		

	for(i=0; i<30; i++){
		gotoxy(30+2*i, 8);
		printf("■");
	}

	for(i=0;i <15; i++){
	  gotoxy(30, 8+i);
	 printf("■");
	}

	for(i=0;i <30; i++){
	  gotoxy(30+i*2, 22);
	 printf("■");
	}

	for(i=0;i <15; i++){
	  gotoxy(88, 8+i);
	  printf("■");
	}
	gotoxy(40,11); 
	printf("1. 내 상태보기");
	gotoxy(40,13); 
	printf("2. 시간표 만들기");
	gotoxy(40,15); 
	printf("3. 약속 잡아주세요");
	gotoxy(40,17); 
	printf("4. 돈 나눠주세요");
	gotoxy(40,19);
	printf("5. 나갈래요"); 
	gotoxy(40,21);
	printf("메뉴 선택  :"); 	
	gotoxy(54,21);
	scanf("%c",&command);	
	gotoxy(22,23);
}
