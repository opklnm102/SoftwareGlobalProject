#include"structHeader.h"

void gotoxy(int x, int y) { 
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

//��üȭ��Ʋ���
void screenBorderDraw(){
	int i;

	printf("������������������������������������������������������������������");

	for(i=0;i<44;i++){
		gotoxy(0,i+1);
		printf("��                                                                                                                              ��");
	}

	gotoxy(0,44);
	printf("������������������������������������������������������������������");

	gotoxy(88,41);
	printf("�ڷΰ��� B, ���� X, ����ϱ� S");
}

//�޴�Ʋ���
void listBorderDraw(){  
	int i;   

	gotoxy(3,10);
	printf("������������������������������������������������������");

	for(i=0; i<20; i++) { 
		gotoxy(3,11+i);
		printf("��                                                  ��");
	}

	gotoxy(3,30);
	printf("������������������������������������������������������");
}


