#include"structHeader.h"

//시간표(txt파일)삭제
void removeTimetable(structMember *s) {

	FILE *fp;
	char fileName[30];
	int nResult;
	char answer[3];
	char*endP;


	listBorderDraw(3,12);

	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxyPrint(8, 24, "●시간표가 없습니다. 시간표를 만들어주세요.●");
		Sleep(1500);
		return;
	}

	fclose(fp);

	fflush(stdin);
	gotoxyPrint(8, 20, "※ 시간표 전체 삭제하시겠습니까?(y/n)");
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
					gotoxyPrint(8, 24, "*시간표가 정상적으로 삭제되었습니다*");  //지우기 성공
					Sleep(1500);
					return;
				} else if (nResult == -1) {
					gotoxyPrint(20, 24, "*파일을 열지 못해, 삭제를 실패했습니다*");  //지우기 실패
				}

				Sleep(10000);
			}
			else if(answer[0] == 'n' || answer[0] == 'N') {
				return;
			}


			else if(answer[0] == '\0') {
				warningRemoveAnwer("●전체 삭제 여부를 입력해주세요●");
				fflush(stdin);
			}

			else {
				warningRemoveAnwer( "●Y,‘y,‘N,‘n’ 외의 문자를 입력하셨습니다●");
				fflush(stdin);
			}

		}
		else {
				warningRemoveAnwer( "●Y,‘y,‘N,‘n’ 외의 문자를 입력하셨습니다●");
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
