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
	int command1;
	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 	
	
	system("color F0");
	gotoxy(21,5); 
	printf("�� �� ������ ��");
	gotoxy(23,7); 
	printf("1. �����ֱ�");
	gotoxy(23,9); 
	printf("2. ������ �����ֱ�");
	list_border_draw(23,9,25,5);
	gotoxy(23,15); 
	printf("3. �����ϰ� �����ֱ�");
	list_border_draw(23,15,25,5);
	gotoxy(26,12);
	printf("3000��           2000��           3000��");
	gotoxy(26,18);
	printf("2600��           2600��           2800��");
	gotoxy(23,21);
	printf("�޴� ���� :");
	gotoxy(60,6); 
	printf("�ڷΰ��� B, ���� X, ����ϱ� S :");
	scanf("%c",&command);
	gotoxy(35,21);	
	scanf("%d",&command1);
	gotoxy(23,22);	
}
