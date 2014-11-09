#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
	 COORD Cur;
	 Cur.X=x;
	 Cur.Y=y;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

int main()
{
	system("color FC");
	gotoxy(55,4);
	printf("-회원 가입-");

	gotoxy(88,7);
	printf("뒤로가기 : B 종료 : X");
	gotoxy(15,8);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	gotoxy(15,9);
	printf("□                                                                                          □\n");
	gotoxy(15,10);
	printf("□                                                                                          □\n");
	gotoxy(15,11); 
	printf("□        학번      :     1092011                                                           □\n");
	gotoxy(15,12);
	printf("□                                                                                          □\n");
	gotoxy(15,13);
	printf("□        PW        :     ********                                                          □\n");
	gotoxy(15,14);
	printf("□                                                                                          □\n");
	gotoxy(15,15);
	printf("□        이름      :     김진삼                                                            □\n");
	gotoxy(15,16);
	printf("□                                                                                          □\n");
	gotoxy(15,17);
	printf("□        고유코드  :     0000                                                              □\n");
	gotoxy(15,18);
	printf("□                                                                                          □\n");
	gotoxy(15,19);
	printf("□                                                                                          □\n");
	gotoxy(15,20);
	printf("□        모든 입력이 끝났습니까? (Y/N)                                                     □\n");
	gotoxy(15,21);
	printf("□                                                                                          □\n");
	gotoxy(15,22);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	
		printf("\n");
	
}
