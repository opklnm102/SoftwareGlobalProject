#include"structHeader.h"

//시간표(txt파일)삭제
void removeTimetable() {

	FILE *fp;
	int nResult;
	char answer;

	listBorderDraw(3,12);


	fp=fopen("timetable.txt","r");

	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("●시간표가 없습니다. 시간표를 만들어주세요.●");
		Sleep(1500);
		return;
	}

	fclose(fp);

	fflush(stdin);
	gotoxy(8,20);
	printf("※ 시간표 전체 삭제하시겠습니까?(y/n)");
	gotoxy(8,24);
	printf(">>");
	gotoxy(12,24);
	scanf("%c",&answer);

	if(answer == 'y' || answer == 'Y') {
		nResult = remove("timetable.txt");
		if(nResult == 0) {
			gotoxy(8,26);
			printf("*시간표가 정상적으로 삭제되었습니다*");  //지우기 성공
			Sleep(1500);
			return;
		} else if (nResult == -1) {
			gotoxy(20,26);
			printf("*파일을 열지 못해, 삭제를 실패했습니다*");  //지우기 실패
		}

		Sleep(10000);
	}
}