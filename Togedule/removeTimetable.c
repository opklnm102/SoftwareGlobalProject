#include"structHeader.h"

//�ð�ǥ(txt����)����
void removeTimetable(structMember *s) {

	FILE *fp;
	char fileName[30];
	int nResult;
	char answer[3];
	char*endP;


	listBorderDraw(3,12);

	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	//timetable.txt�� ���� ���
	if(fp == NULL ) {
		gotoxyPrint(8, 24, "�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
		Sleep(1500);
		return;
	}

	fclose(fp);

	fflush(stdin);
	gotoxyPrint(8, 20, "�� �ð�ǥ ��ü �����Ͻðڽ��ϱ�?(y/n)");
	gotoxyPrint(8, 22, ">>");

	while(1) {
		fflush(stdin);
		gotoxy(12,22);
		fgets(answer,3, stdin);

		if( (endP=strchr(answer, '\n')) != NULL ) {
			*endP = '\0';

			if(answer[0] == 'y' || answer[0] == 'Y') {
				nResult = remove(fileName);
				if(nResult == 0) {
					gotoxyPrint(8, 24, "*�ð�ǥ�� ���������� �����Ǿ����ϴ�*");  //����� ����
					Sleep(1500);
					return;
				} else if (nResult == -1) {
					gotoxyPrint(20, 24, "*������ ���� ����, ������ �����߽��ϴ�*");  //����� ����
				}

				Sleep(10000);
			}
			else if(answer[0] == 'n' || answer[0] == 'N') {
				return;
			}


			else if(answer[0] == '\0') {
				warningRemoveAnwer("����ü ���� ���θ� �Է����ּ����");
				fflush(stdin);
			}

			else {
				warningRemoveAnwer( "��Y,��y,��N,��n�� ���� ���ڸ� �Է��ϼ̽��ϴ١�");
				fflush(stdin);
			}

		}
		else {
				warningRemoveAnwer( "��Y,��y,��N,��n�� ���� ���ڸ� �Է��ϼ̽��ϴ١�");
				fflush(stdin);
			}
	}
}

void warningRemoveAnwer(char* warning) {


	gotoxyPrint(8, 24, warning);
	Sleep(1000);
	gotoxyPrint(8, 24, "                                              ");
	gotoxyPrint(12, 22, "                                         ");

}
