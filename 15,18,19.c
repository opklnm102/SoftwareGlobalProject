#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
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

int main()
{	
	int x=10,y=3;  //���� ��ǥ
	int i,j;
	int place_category,place;  //��Ҹ���Ʈ(P-1-7)
	int delete_promise;  //��ӻ���(P-3)
	char delete_selection;  
	int division_money,money;  //���й�(D)
	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 

	//��Ҽ���(P-1-7)
	//list_border_draw(3,7,40,10);  //����Ʈ�׵θ� �׸���
	//gotoxy(3,3);
	//printf("������");
	//gotoxy(35,6);
	//printf("��Ҹ���Ʈ");
	//gotoxy(6,9);
	//printf("1.�н����ýü�");
	//gotoxy(6,11);
	//printf("2.�ްԽü�");
	//gotoxy(6,13);
	//printf("3.��Ÿ�ü�");
	//gotoxy(3,19);
	//printf("���ϴ� ���>> "); scanf("%d",&place_category);	
	//
	//system("cls");		
	//
	//list_border_draw(3,7,40,10);  //����Ʈ�׵θ� �׸���
	//gotoxy(3,3);
	//printf("������");
	//gotoxy(35,6);
	//printf("��Ҹ���Ʈ");
	//gotoxy(6,9);
	//printf("1.Ž���� ���� ����");
	//gotoxy(6,11);
	//printf("2.�İ� �����ǽ���");
	//gotoxy(3,19);
	//printf("���>> ");	scanf("%d",&place);	
	//
	//system("cls");

	//��ӻ���(P-3)
	list_border_draw(3,6,40,10);  //����Ʈ�׵θ� �׸���
	gotoxy(3,3);
	printf("--���� ��Ӹ���Ʈ--");
	gotoxy(6,8);
	printf("  ��Ӹ�                 ��ӳ�¥");
	gotoxy(6,10);
	printf("1.ȫ�밡��                11/28");
	gotoxy(6,12);
	printf("2.�б�����                11/17");

	list_border_draw(3,19,40,10);  //����Ʈ�׵θ� �׸���

	gotoxy(5,18);
	printf("�����Ͻ� ���>> "); scanf("%d",&delete_promise);

	gotoxy(6,21);
	printf(" ��Ӹ�            ���             ��¥        �ð�        �Բ���ģ��");
	gotoxy(6,23);
	printf("�б�����        ���а�(405)        11/14        2��          ������");
	
	gotoxy(5,30);
	printf("��ü�����˴ϴ�. �����Ͻðڽ��ϱ�?(Y/N)"); fflush(stdin);
	scanf("%c",&delete_selection);

	system("cls");

	list_border_draw(3,6,40,10);  //����Ʈ�׵θ� �׸���
	gotoxy(3,3);
	printf("--�� �����帱����!--");
	gotoxy(6,8);
	printf("  ��Ӹ�                 ��ӳ�¥");
	gotoxy(6,10);
	printf("1.ȫ�밡��                11/28");
	gotoxy(6,12);
	printf("2.�б�����                11/17");	
	
	list_border_draw(3,20,40,10);  //����Ʈ�׵θ� �׸���
	gotoxy(4,20);
	printf("<���õ� ���>");

	gotoxy(5,18);
	printf("�� ���� ���>> "); scanf("%d",&division_money);

	gotoxy(6,22);
	printf(" ��Ӹ�            ���             ��¥        �ð�        �Բ���ģ��");
	gotoxy(6,24);
	printf("�б�����        ���а�(405)        11/14        2��          ������");

	gotoxy(5,31);
	printf("���� �ݾ� �Է�>> "); fflush(stdin);
	scanf("%d",&money);
}

