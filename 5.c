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
	
	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 
	gotoxy(53,4);
	printf("%s �� �ȳ��ϼ���!",name);		

	for(i=0; i<30; i++){
		gotoxy(30+2*i, 8);
		printf("��");
	}

	for(i=0;i <15; i++){
	  gotoxy(30, 8+i);
	 printf("��");
	}

	for(i=0;i <30; i++){
	  gotoxy(30+i*2, 22);
	 printf("��");
	}

	for(i=0;i <15; i++){
	  gotoxy(88, 8+i);
	  printf("��");
	}
	gotoxy(40,11); 
	printf("1. �� ���º���");
	gotoxy(40,13); 
	printf("2. �ð�ǥ �����");
	gotoxy(40,15); 
	printf("3. ��� ����ּ���");
	gotoxy(40,17); 
	printf("4. �� �����ּ���");
	gotoxy(40,19);
	printf("5. ��������"); 
	gotoxy(40,21);
	printf("�޴� ����  :"); 	
	gotoxy(54,21);
	scanf("%c",&command);	
	gotoxy(22,23);
}
