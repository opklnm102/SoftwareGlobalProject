#include"structHeader.h"

int main()
{

	char menuSelect;

	system("mode con:cols=130 lines=46");  //���� 130, ���� 45 

	while(1){

		printf("*togedule*\n");
		printf("1. �α���\n");
		printf("2. ȸ������\n");
		printf("3. ��й�ȣ�缳��\n");
		printf("�޴����� >> "); scanf("%c",&menuSelect); fflush(stdin);
		
		switch(menuSelect){
		case '1' :  //�α���
			login();
			
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