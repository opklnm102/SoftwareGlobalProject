#include<stdio.h> 
#include<windows.h> 
 
 
 void gotoxy(int x,int y) 
 {	 
 	COORD pos={x,y}; 
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  
 }  
 
 //�׵θ� �׸���(������ǥ(x,y), ũ��(width X height), �׸�����) 2��Ʈ¥�� ���� 
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

 
 //�׵θ� �׸���(������ǥ(x,y), ũ��(width X height))  
 void list_border_draw(int x,int y,int width,int height){   
	int i,j; 

 
 	gotoxy(x,y);  //������ǥ	 
 	i=y; 
 	while(i<y+height){ //���� 
 		j=x; 
		gotoxy(j,i+1); 
 		while(j<x+width){  //���� 
			if(i==y && j==x)  //������ ���� 
				printf("%s","��"); 
		else if(i==y && j==x+width-1)  //�������� ���� 
				printf("%s","��"); 
			else if(i==y+height-1 && j==x)  //���ʾƷ� ���� 
			printf("%s","��"); 
 			else if(i==y+height-1 && j==x+width-1)  //������ �Ʒ� ���� 
			printf("%s","��"); 
			else if(i==y || i==y+height-1)  //���� �׸��� 
				printf("%s","��"); 
 			else if(j==x || j==x+width-1)  //���� �׸��� 
				printf("%s","��"); 
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
	char appname[41],name[13];
	int command1,number;

	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 	

	gotoxy(21,5); 
	printf("�� ��� ����� ��");
	gotoxy(23,7); 
	printf("��Ӹ� :");
	gotoxy(53,7); 
	printf("�ο��� :");
	gotoxy(23,9); 
	printf("�̸��˻� :");
	gotoxy(73,10); 
	printf("��Ӹ��");

	list_border_draw(22,10,25,10);
	list_border_draw(73,10,10,10);
	gotoxy(25,12); 
	printf("ex)");
	gotoxy(25,13);
	printf("�� ��ǻ�Ͱ��а� 13920 �̼���");
	gotoxy(25,15); 
	printf("�� �����а� 13920 �̼���");	
	gotoxy(25,19); 
	printf("�� �̸���ȣ ���� : ");
	gotoxy(77,12); 
	printf("ex)");	
	gotoxy(77,13); 
	printf("������");	
	gotoxy(77,15); 
	printf("�赿��");	
	gotoxy(77,17); 
	printf("������");	
	gotoxy(60,6); 
	printf("�ڷΰ��� B, ���� X, ����ϱ� S :");
	scanf("%c",&command);	
	gotoxy(33,7);	
	scanf("%s",&appname);
	gotoxy(63,7);	
	scanf("%d",&number);
	gotoxy(34,9);	
	scanf("%s",&name);
	gotoxy(45,19);	
	scanf("%d",&command1);
	gotoxy(23,21);	
}
