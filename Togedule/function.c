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

	gotoxy(96,41);
	printf("�����޴��� B, ���� X");
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

//��Ӹ���ƮƲ���
void listBorderDraw1(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("����������������������������������������������������������������������������������");

	for(i=0; i<9; i++) { 
		gotoxy(x,y+1+i);
		printf("��                                                                              ��");
	}

	gotoxy(x,y+10);
	printf("����������������������������������������������������������������������������������");
}
//�̸� �˻�Ʋ ���
void listBorderDraw2(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("����������������������������������������������������������");

	for(i=0; i<12; i++) { 
		gotoxy(x,y+1+i);
		printf("��                                                      ��");
	}

	gotoxy(x,y+13);
	printf("����������������������������������������������������������");
}
//�Բ��ϴ� ȸ������Ʈ ���
void listBorderDraw3(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("��������������������������");

	for(i=0; i<14; i++) { 
		gotoxy(x,y+1+i);
		printf("��                      ��");
	}

	gotoxy(x,y+15);
	printf("��������������������������");
}
//���ڻ�,���ڹ��� ����
void setcolor(int color, int bgcolor){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor&0xf)<<4) | (color&0xf));
} 

//�����̸������(������ �����̸�,ȸ������ü,����Ÿ��(timetable,promiseList��)
void getUserfileName(char *fileName,structMember *s,char *filetype){
	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	if(strcmp(filetype,"\0") != 0)
		strcat(fileName,filetype);
	strcat(fileName,".txt");

}

//���ڿ����� �����̿��� ���� �����°� üũ
int numberErrorcheck(char *s){
	int len=strlen(s);
	int i;

	for(i=0; i<len; i++){
		if(s[i]<48 || 57<s[i])  //���ڹ��� ���̸� 1����
			return 1;
	}
	return 0;  //�ƴϸ� 0����
}

//���ڿ� ���� üũ(���ڿ��̶� ���̸� ����)
int stringLengthcheck(char *s,int n){
	if(strlen(s)>n)
		return 1;  //���� ��ġ�� 1����
	return 0;  //�ƴϸ� 0����
}

//�ѱ��̿��� �� üũ
int hanErrorcheck(char *s){
	int len=strlen(s);
	int i;

	for(i=0; i<len; i++){
		if(0<s[i] && s[i]<127)  //���ڹ��� ���̸� 1����
			return 1;
	}
	return 0;  //�ƴϸ� 0����
}

void gotoxyPrint(int x, int y, char* word) {

	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);

	printf(word);
}


