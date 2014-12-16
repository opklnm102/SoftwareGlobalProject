#include"structHeader.h"

//�ܽð�ǥ(txt����)����
void removeTimetable(structMember *s) {

	FILE *fp;
	char fileName[30];
	int nResult;
	char answer[3];
	char*endP;


	listBorderDraw(3,12);

	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	/*----------(������� �ð�ǥ �ؽ�Ʈ ������ ���� ���)----------*/
	if(fp == NULL ) {
		gotoxyPrint(8, 24, "�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
		Sleep(1500);
		return;
	}

	fclose(fp);


	/*----------(������� �ð�ǥ �ؽ�Ʈ ������ �ִ� ���)----------*/
	fflush(stdin);
	gotoxyPrint(8, 20, "�� �ð�ǥ ��ü �����Ͻðڽ��ϱ�?(y/n)");
	gotoxyPrint(8, 22, ">>");


	/*----------�ð�ǥ ��ü ������ ���� �Է�----------*/
	while(1) {

		fflush(stdin);
		gotoxy(12,22);
		fgets(answer,3, stdin);

		if( (endP=strchr(answer, '\n')) != NULL ) {
			*endP = '\0';

			/*----------('b'�Ǵ� 'B'�� �Է��� ��� ->�ڷΰ���)----------*/
			if((answer[0] == 'b'|| answer[0] == 'B' )&& answer[1] == '\0' ) return;

			/*----------('x'�Ǵ� 'X'�� �Է��� ��� ->���α׷� �����ϱ�)----------*/
			else if((answer[0] == 'x'|| answer[0] == 'X' )&& answer[1] == '\0' )  exit(0);

			/*----------('y'�Ǵ� 'Y'�� �Է��� ���)----------*/
			else if(answer[0] == 'y' || answer[0] == 'Y') {
				nResult = remove(fileName);
				//�ð�ǥ ��ü ���� ����
				if(nResult == 0) {
					gotoxyPrint(8, 24, "*�ð�ǥ�� ���������� �����Ǿ����ϴ�*");  //����� ����
					Sleep(1500);
					return;
				} 

				//�ð�ǥ ��ü ���� ����
				else if (nResult == -1) {
					gotoxyPrint(20, 24, "*������ ���� ����, ������ �����߽��ϴ�*");  //����� ����
				}

				Sleep(10000);

			}

			/*----------('n'�Ǵ� 'N'�� �Է��� ��� -> �ڷΰ���)----------*/
			else if(answer[0] == 'n' || answer[0] == 'N') {
				return;
			}

			/*----------(�Է¾��� Enter�� �Է��� ���)----------*/
			else if(answer[0] == '\0') {
				warningRemoveAnwer("����ü ���� ���θ� �Է����ּ����");
				fflush(stdin);
			}

			/*----------(Y,y,N,n ���� ���ڸ� �Է��� ���� ���)----------*/
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

//�ܻ������ΰ���Լ�
void warningRemoveAnwer(char* warning) {


	gotoxyPrint(8, 24, warning);
	Sleep(1000);
	gotoxyPrint(8, 24, "                                              ");
	gotoxyPrint(12, 22, "                                         ");

}
