#include"structHeader.h"

int main()
{
	char menuSelect[20];
	int menu;
	structMember s;  //�ٸ� �޴��� ȸ�������� �Ѱ��ش�.
	setcolor(0,15);  //���ڻ�,���ڹ��� ����(����,��)
	system("mode con:cols=130 lines=46");  //���� 130, ���� 45 


	while(1){
		screenBorderDraw();  //��üȭ��Ʋ���
		listBorderDraw(40,13);  //�޴�Ʋ���
		//----------------------------UI�׸���-----------------------------------------------
		gotoxy(60,10);
		printf("*Togedule*");
		gotoxy(50, 18); printf("1. �α���");
		gotoxy(50, 21); printf("2. ȸ������");
		gotoxy(50, 24); printf("3. ��й�ȣ�缳��");
		gotoxy(73,27); printf("�޴����� >> "); 
		while(1){
			gotoxy(85,27); scanf("%s",menuSelect); fflush(stdin);
			if(!strcmp(menuSelect,"1") || !strcmp(menuSelect,"2") || !strcmp(menuSelect,"3"))
			{
				menu=atoi(menuSelect);
				gotoxy(50,30);
				switch(menu){
				case 1 :  //�α���
					login(&s);			
					break;
				case 2 :  //ȸ������
					membership();
					break;
				case 3 :  //��й�ȣ�缳��
					pwFind();
					break;
				}
			}
			else{
				gotoxy(65,29); printf("1~3�� �Է�");
				gotoxy(85,27); printf("       ");
			}
		}
		system("cls");
	}
}