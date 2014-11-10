#include <stdio.h>
#include <Windows.h>

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
	
	int i, j, k, m, n, q;
	
	system("mode con:cols=130 lines=45");  //���� 130, ���� 45 
	gotoxy( 6, 6 );
	printf("   ������ ������ �����ϼ���: \n\n");
	gotoxy( 6, 8 );
	printf("1. ��Ӹ�      : \n");
	gotoxy( 6, 9 );
	printf("2. ������    : \n");
	gotoxy( 6, 10);
	printf("3. ��ӳ�¥    : \n");
	gotoxy( 6, 11 );
	printf("4. ��ӽð�    : \n");
	gotoxy( 6, 12 );
	printf("5. �Բ��� ģ�� : \n");

	
	list_border_draw(7,13,25,15);
	gotoxy( 34, 6  );
	scanf("%d", &i );
	gotoxy( 23, 8  );
	scanf("%d", &j );
	gotoxy( 23, 9  );
	scanf("%d", &k );
	gotoxy( 23, 10 );
	scanf("%d", &m );
	gotoxy( 23, 11 );
	scanf("%d", &n );
	gotoxy( 23, 12 );
	scanf("%d", &q );
	printf("\n");
	gotoxy( 23, 30 );
}
