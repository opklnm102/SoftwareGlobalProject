#include"structHeader.h"

int main() {
	char menuSelect;
	structMember s;  //�ٸ� �޴��� ȸ�������� �Ѱ��ش�.
	//system("color 04");
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
		gotoxy(73,27); printf("�޴����� >> "); gotoxy(85,27); scanf("%c",&menuSelect); fflush(stdin);
		gotoxy(50,30);
		switch(menuSelect){
		case '1' :  //�α���
			login(&s);			
			break;
		case '2' :  //ȸ������
			membership();
			break;
		case '3' :  //��й�ȣ�缳��
			pwFind();
			break;
		}
		system("cls");
	}
}