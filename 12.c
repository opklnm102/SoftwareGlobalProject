#include <stdio.h>
#include <windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

//�׵θ� �׸���(������ǥ(x,y), ũ��(width X height), �׸�����)
void border_draw(int x,int y,int width,int height,char figure[]){  
	int i,j;

	gotoxy(x,y);  //������ǥ	
	i=y;
	while(i<y+height){ //����
		j=x;
		gotoxy(j,i+1);
		while(j<x+width){  //����
			if(i==y || i==y+height-1 || j==x || j==x+width-1)
				printf("%c%c",figure[0],figure[1]);
			else
				printf("  ");
			j++;
		}
		i++;
	}
}

int main() {
	int i;
	char command;
	char name[10]={' '};

	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 

	border_draw(60,5,22,16,"��");
	gotoxy(60,6);
	printf("��");
	gotoxy(102,6);
	printf("��");
	gotoxy(60,21);
	printf("��");
	gotoxy(102,21);
	printf("��");
	for(i=0;i <14; i++){
	  gotoxy(60, 7+i);
	 printf("��");
	}
	for(i=0;i <14; i++){
	  gotoxy(102, 7+i);
	 printf("��");
	}	
	gotoxy(60,5);
	printf("���� ���");	
	gotoxy(20,5); 
	printf("�� ��� �޴� ��");
	gotoxy(23,7); 
	printf("1. ��Ӹ����");
	gotoxy(23,9); 
	printf("2. ��� ����");
	gotoxy(23,11); 
	printf("3. ��� ����");
	gotoxy(23,13); 
	printf("4. ��� ��ƺ���");
	gotoxy(25,16);
	printf("�� �޴� ���� :"); 
	
	gotoxy(65,8);
	printf("����������Ʈ     / (11/9)");
	gotoxy(65,11);
	printf("����������Ʈ2    / (11/11)");
	gotoxy(65,14);
	printf("����������       / (11/18)");
	gotoxy(40,16);
	scanf("%c",&command);	
	gotoxy(22,23);

	
}
