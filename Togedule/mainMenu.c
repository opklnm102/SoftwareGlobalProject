#include"structHeader.h"

void mainMenu(structMember *s){
	char menuSelect;
	system("cls");

	printf("%s�� �ȳ��ϼ���!\n",s->name);
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
		timetableMenu(s);
		break;
	case '3' :  //��� ����ּ���
		promise(s);
		break;
	case '4' :  //�� �����ּ���
		moneyShare(); break;
	case '5' :  //��������
		exit(1);
	}
}

