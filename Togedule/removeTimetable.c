#include"structHeader.h"

//�ð�ǥ(txt����)����
void removeTimetable(structMember *s) {

	FILE *fp;
	int nResult;
	char answer;
	char fileName[30];

	listBorderDraw(3,12);

	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"timetable");
	strcat(fileName,".txt");

	fp=fopen(fileName,"r");

	//timetable.txt�� ���� ���
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
		Sleep(1500);
		return;
	}

	fclose(fp);

	fflush(stdin);
	gotoxy(8,20);
	printf("�� �ð�ǥ ��ü �����Ͻðڽ��ϱ�?(y/n)");
	gotoxy(8,24);
	printf(">>");
	gotoxy(12,24);
	scanf("%c",&answer);

	if(answer == 'y' || answer == 'Y') {
		nResult = remove(fileName);
		if(nResult == 0) {
			gotoxy(8,26);
			printf("*�ð�ǥ�� ���������� �����Ǿ����ϴ�*");  //����� ����
			Sleep(1500);
			return;
		} else if (nResult == -1) {
			gotoxy(20,26);
			printf("*������ ���� ����, ������ �����߽��ϴ�*");  //����� ����
		}

		Sleep(10000);
	}
}