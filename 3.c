#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
	 COORD Cur;
	 Cur.X=x;
	 Cur.Y=y;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

int main() {
	int i;
	char command,finishC;
	char name[10];
	int studentN,pw,originC;

	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 
	gotoxy(55,4);
	printf("-회원 가입-");
		

	for(i=0; i<45; i++){
		gotoxy(15+2*i, 8);
		printf("■");
	}

	for(i=0;i <15; i++){
	  gotoxy(15, 8+i);
	 printf("■");
	}

	for(i=0;i <45; i++){
	  gotoxy(15+i*2, 22);
	 printf("■");
	}

	for(i=0;i <15; i++){
	  gotoxy(105, 8+i);
	  printf("■");
	}
	gotoxy(70,7);
	printf("뒤로가기 : B 종료 : X 유지 : S");	
	gotoxy(22,11); 
	printf("학번      :");
	gotoxy(22,13); 
	printf("PW        :");
	gotoxy(22,15); 
	printf("이름      :");
	gotoxy(22,17); 
	printf("고유코드  :");
	gotoxy(22,20);
	printf("모든 입력이 끝났습니까? (Y/N)"); 
	
	gotoxy(103,7);
	scanf("%c",&command);
	gotoxy(40,11);
	scanf("%d",&studentN);
	gotoxy(40,13);
	scanf("%d",&pw);
	gotoxy(40,15);
	scanf("%s",&name);
	gotoxy(40,17);
	scanf("%d",&originC);
	gotoxy(60,20);
	fflush(stdin);
	scanf("%c",&finishC);
	gotoxy(22,23);
	
}
