#include"structHeader.h"

void mainMenu(){
	char menuSelect;

	printf("  �� �ȳ��ϼ���!\n");
	printf("1. �� ���º���\n"); 
	printf("2. �ð�ǥ �����\n");
	printf("3. ��� ����ּ���\n"); 
	printf("4. �� ���ഩ����\n"); 
	printf("5. ��������\n"); 
	scanf("%c",&menuSelect); fflush(stdin);

	switch(menuSelect){
	case '1' :  //�� ���º���
		break;
	case '2' :  //�ð�ǥ �����
		break;
	case '3' :  //��� ����ּ���
		break;
	case '4' :  //�� �����ּ���
		break;
	case '5' :  //��������
		exit(1);
	}
}

