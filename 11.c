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
	char command;

	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 

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
	gotoxy(47,14); 
	printf("시간표가 전체 삭제됩니다. (Y/N)");
	gotoxy(60,15);
	scanf("%c",&command);	
	gotoxy(22,23);
}
