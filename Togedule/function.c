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
	printf("�����޴��� B, ���� X, ����ϱ� S");
}

//�޴�Ʋ���
void listBorderDraw(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("������������������������������������������������������");

	for(i=0; i<20; i++) { 
		gotoxy(x,y+1+i);
		printf("��                                                  ��");
	}

	gotoxy(x,y+20);
	printf("������������������������������������������������������");
}

//���ۿ� �����ִ°� üũ
void checkInput(){
	int ch;
	ch = getchar();
	if(ch == 32){
		printf("please check the input whether it is valld or not.\n");
		exit(0);
	}
}
//���ڻ�,���ڹ��� ����
void setcolor(int color, int bgcolor){
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor&0xf)<<4) | (color&0xf));
} 