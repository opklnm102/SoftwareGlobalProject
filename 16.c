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
	char command,command1;
	int number;

	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 
	
	gotoxy(21,5); 
	printf("�� ��� ���� ��");
	gotoxy(23,7); 
	printf("�� ��� ����Ʈ");
	
	list_border_draw(22,7,35,10);
	list_border_draw(23,20,35,10);
	gotoxy(25,9);
	printf("           ��Ӹ�              |             ��ӳ�¥");
	gotoxy(24,10);
	printf("������������������������������������������������������������������");
	gotoxy(24,11); 
	printf("��");
	gotoxy(35,11); 
	printf("��������");
	gotoxy(71,11); 
	printf("11/9");
	gotoxy(24,13); 
	printf("��");
	gotoxy(30,13); 
	printf("����Ʈ�۷ι� ������Ʈ");
	gotoxy(71,13); 
	printf("11/11");
	gotoxy(23,19);
	printf("������ ��� ���� :");
	gotoxy(26,23); 
	printf("�� ��Ӹ� : ");
	gotoxy(40,23); 
	printf("����Ʈ�۷ι� ������Ʈ ");
	gotoxy(26,25); 
	printf("�� ��ӳ�¥ : ");
	gotoxy(40,25); 
	printf("11/11 ");
	gotoxy(26,27); 
	printf("�� ��ӽð� : ");
	gotoxy(40,27); 
	printf("3~4���� ");
	gotoxy(26,29); 
	printf("�� ��Ӹ�� : ");
	gotoxy(40,29); 
	printf("�赿��, ������, �̼���, ������ ");
	gotoxy(25,32);
	printf("�� �����Ͻðڽ��ϱ�? (Y/N) ");
	
	gotoxy(60,6); 
	printf("�ڷΰ��� B, ���� X, ����ϱ� S :");
	scanf("%c",&command);	
	
	gotoxy(43,19);	
	scanf("%d",&number);
	gotoxy(53,32);	
	scanf("%d",&command1);
	gotoxy(23,34);	
}
