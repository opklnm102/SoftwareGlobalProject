#include<stdio.h>
#include <windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}


int main(){

	int i;
	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 

	gotoxy(33,12);
	printf("-��й�ȣ �缳��-");

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
	printf("�й�:"); 
	gotoxy(20, 18);
	printf("�����ڵ�:"); 
	gotoxy(20, 21);
	printf("���ο� PW:"); 

	gotoxy(0,40);  //������ �� ��ġ����
}

