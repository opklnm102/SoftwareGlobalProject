#include"structHeader.h"

int main()
{
	char menuSelect;
	structMember s;  //�ٸ� �޴��� ȸ�������� �Ѱ��ش�.

	system("mode con:cols=130 lines=46");  //���� 130, ���� 45 

<<<<<<< HEAD

=======
>>>>>>> 621e311dcf005304b617c9e2ae3aadb755b5ced3
	while(1){

		printf("*togedule*\n");
		printf("1. �α���\n");
<<<<<<< HEAD
		printf("2. ȸ������\n");
		printf("3. ��й�ȣ�缳��\n");
		printf("�޴�����>> "); scanf("%c",&menuSelect);
=======
>>>>>>> 621e311dcf005304b617c9e2ae3aadb755b5ced3

		printf("2. ȸ������\n");
		printf("3. ��й�ȣ�缳��\n");
		printf("�޴����� >> "); scanf("%c",&menuSelect); fflush(stdin);
		
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