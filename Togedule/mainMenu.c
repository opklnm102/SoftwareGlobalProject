#include"structHeader.h"

void mainMenu(structMember *s){
	int x=10, y=7;  //��ǥ
	char menuSelect;
	int check;

	//----------------------------UI�׸���-----------------------------------------------
	while(1){
		check=1;
		screenBorderDraw();  //��üƲ���
		listBorderDraw(40,13);  //�޴�Ʋ���

		gotoxy(58,10);
		printf("%s�� �ȳ��ϼ���!",s->name);
		gotoxy(40+x,11+y); 
		printf("1. �� ���º���"); 
		gotoxy(40+x,13+y); 
		printf("2. �ð�ǥ �����");
		gotoxy(40+x,15+y); 
		printf("3. ��� ����ּ���"); 
		gotoxy(40+x,17+y); 
		printf("4. �� ���ഩ����"); 
		gotoxy(40+x,19+y);
		printf("5. ��������"); 
		gotoxy(73,29);
		printf("�޴�����>> "); 
		scanf("%c",&menuSelect); fflush(stdin);

		switch(menuSelect){
		case '1' :  //�� ���º���
			mystatus(s);
			break;
		case '2' :  //�ð�ǥ �����
			timetableMenu(s);
			break;
		case '3' :  //��� ����ּ���
			while(check){check=promise(s);}
			break;
		case '4' :  //�� �����ּ���
			moneyShare1(s); break;
		case '5' :  //��������
			exit(1);
		}
	}
}

