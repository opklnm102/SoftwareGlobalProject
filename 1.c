#include<stdio.h>
#include<Windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

int main() 
{
	int i;
	int tmp;

	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 

	gotoxy(35,12);
	printf("*Togedule*");

	for(i=0; i<30; i++){
		gotoxy(10+i*2, 10);
		printf("��");
	}

	for(i=0;i <15; i++){
		gotoxy(10, 10+i);
		printf("��");
	}

	for(i=0;i <30; i++){
		gotoxy(10+i*2, 25);
		printf("��");
	}

	for(i=0;i <15; i++){
		gotoxy(68, 10+i);
		printf("��");
	}

	gotoxy(20, 15);
	printf("1. ��  ��  ��");
	gotoxy(20, 18);
	printf("2. ȸ �� �� ��");
	gotoxy(20, 21);
	printf("3. ��й�ȣ ã��");

	gotoxy(45,23);
	printf("�޴����� : ");
	gotoxy(56,23);
	scanf("%d",&tmp);

	gotoxy(50,50);
}
