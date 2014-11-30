#include"structHeader.h"


//시간표 수정메뉴
void modifyMenu () {

	int choiceMenu;

	fflush(stdin);
	listBorderDraw(3,12);

	gotoxy(22,15);
	printf("*시간표 수정메뉴*");


	gotoxy(17, 18);
	printf(" 1. 시간표 과목정보 수정 ");
	gotoxy(17,20);
	printf(" 2. 시간표 과목 추가 ");
	gotoxy(17,22);
	printf(" 3. 시간표 과목 삭제 ");
	gotoxy(17,24);
	printf(">> ");
	scanf("%d", &choiceMenu);

	switch (choiceMenu) {
	case 1: modifySubjectInfo();  break; //시간표 과목정보 수정
	case 2: addSubject(); break; //시간표 과목 추가
	case 3: removeSubject(); break; //시간표 과목 삭제
	}

}

//시간표 과목정보 수정
void modifySubjectInfo() {

	FILE *fp;
	structSubject* subjectPointer;//시간표포인터
	structSubject tmpSubject;
	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	int subjectTotalCnt; //과목총갯수
	char charModifyDay[15]; //char형수정요일변수 
	int intModifyDay[5] ={0}; //int형수정요일변수
	char charModifySubjectNum[5]={0}; //수정과목번호
	int intModifySubjectNum;
	int i,j=0,k=0;


	fflush(stdin);
	listBorderDraw(3,12);


	//txt파일에 저장된 시간표 읽어오기
	fp=fopen("timetable.txt","r");

	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("●시간표가 없습니다. 시간표를 만들어주세요.●");
		Sleep(1500);
		return;
	}


	else {
		fscanf(fp, "%d", &subjectTotalCnt);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);


		for(i=0;i<subjectTotalCnt;i++) {
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		}

		fclose(fp);


	gotoxy(20,12);
	printf("- 시간표 수정 -");

	
	gotoxy(15, 14);
	printf("수정할 과목 요일 : ");

	while(1) {
	gotoxy(33, 14);
	gets(charModifyDay);

		//수정할 해당 요일 과목출력 
		for(k=0; k<5; k++) {
			if ( strstr(charModifyDay, dayOfWeek[k]) ) { //어떤 요일인지 체크
				for(i=0;i<subjectTotalCnt;i++) {
					if(strstr(dayOfWeek[k],subjectPointer[i].dayOfWeek)) { //입력된 시간표에서 과목정보를 찾고 해당 요일 과목출력
						intModifyDay[j] = i; //시간표 몇번째에 과목이 있는지 저장
						gotoxy(15, 17+j*2);
						printf("%d) %s %s %s교시", j+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
						j++;
					}
				}
				if(intModifyDay[0] == 0 ) {
					gotoxy(13,20);
					printf("●해당 요일에 과목이 없습니다.●");
					Sleep(1000);
					gotoxy(13,20);
					printf("                                 ");
					gotoxy(33, 14);
					printf("               ");
					strstr(charModifyDay,"");
					break;
				}
			}
		}
		if(intModifyDay[0] != 0) {
			break;
		}
	}


		gotoxy(15,26);
		printf(">> ");
		gotoxy(18,26);
		gets(charModifySubjectNum);
		intModifySubjectNum = atoi(charModifySubjectNum)-1;


		//해당과목정보수정
		listBorderDraw(3,12);

		gotoxy(6, 12);
		printf("＊＊＊＊＊＊＊＊＊＊＊현재＊＊＊＊＊＊＊＊＊＊＊");
		gotoxy(9, 14);
		printf("요  일 : %s",subjectPointer[intModifyDay[intModifySubjectNum]].dayOfWeek);
		gotoxy(9, 16);
		printf("과목명 : %s",subjectPointer[intModifyDay[intModifySubjectNum]].subjectName);
		gotoxy(9, 18);
		printf("교  시 : %s",subjectPointer[intModifyDay[intModifySubjectNum]].subjectClass);

		gotoxy(6, 21);
		printf("＊＊＊＊＊＊＊＊＊＊＊수정＊＊＊＊＊＊＊＊＊＊＊");
		gotoxy(9, 23);
		printf("요  일 :");
		gotoxy(9, 25);
		printf("과목명 :");
		gotoxy(9, 27);
		printf("교  시 :");

		fflush(stdin);

		gotoxy(18, 23);
		gets(tmpSubject.dayOfWeek);
		gotoxy(18, 25);
		gets(tmpSubject.subjectName);

		while(1) {

			gotoxy(18, 27);
			gets(tmpSubject.subjectClass);

			if (checkOverlappingClass(subjectPointer,tmpSubject,subjectTotalCnt) == 0){

				if(checkOverlappingClass(&subjectPointer[intModifyDay[intModifySubjectNum]],tmpSubject,1) == 0) {

					break;
				}
				else
					gotoxy(18, 27);
				printf("◀교시중복!");
				Sleep(1000);
				gotoxy(18, 27);
				printf("              ");
			}

			else {
				break;
			}

		}

		strcpy(subjectPointer[intModifyDay[intModifySubjectNum]].dayOfWeek, tmpSubject.dayOfWeek);
		strcpy(subjectPointer[intModifyDay[intModifySubjectNum]].subjectName, tmpSubject.subjectName);
		strcpy(subjectPointer[intModifyDay[intModifySubjectNum]].subjectClass, tmpSubject.subjectClass);

		sortTimetable(subjectPointer,subjectTotalCnt);
		free(subjectPointer);
	}
}

//시간표 과목 추가
void addSubject() {

	FILE *fp;
	structSubject* subjectPointer;
	structSubject tmpSubject;

	int subjectTotalCnt;
	int i;

	fflush(stdin);
	listBorderDraw(3,12);


	//txt파일에 저장된 시간표 읽어오기
	fp=fopen("timetable.txt","r");

	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("●시간표가 없습니다. 시간표를 만들어주세요.●");
		Sleep(1500);
		return;
	}

	else {
		fscanf(fp, "%d", &subjectTotalCnt);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*(subjectTotalCnt+1));



		for(i=0;i<subjectTotalCnt;i++) {
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		}

		fclose(fp);

		gotoxy(9, 17);
		printf("요  일 :");
		gotoxy(9, 19);
		printf("과목명 :");
		gotoxy(9, 21);
		printf("교  시 :");

		fflush(stdin);

		gotoxy(18, 17);
		gets(tmpSubject.dayOfWeek);
		gotoxy(18, 19);
		gets(tmpSubject.subjectName);

		while(1) {

			gotoxy(18, 21);
			gets(tmpSubject.subjectClass);

			if (checkOverlappingClass(subjectPointer,tmpSubject,subjectTotalCnt) == 0){

				gotoxy(18, 21);
				printf("◀교시중복!");
				Sleep(1000);
				gotoxy(18, 21);
				printf("              ");
				strcpy(tmpSubject.subjectClass,"");

			}
			else{
				break;
			}

		}

		strcpy(subjectPointer[subjectTotalCnt].dayOfWeek, tmpSubject.dayOfWeek);
		strcpy(subjectPointer[subjectTotalCnt].subjectName, tmpSubject.subjectName);
		strcpy(subjectPointer[subjectTotalCnt].subjectClass, tmpSubject.subjectClass);

		sortTimetable(subjectPointer,subjectTotalCnt+1);

		free(subjectPointer);
	}

}

//과목삭제
void removeSubject() {

	FILE *fp;
	structSubject* subjectPointer;//시간표포인터
	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	int subjectTotalCnt; //과목총갯수
	char charRemoveDay[15]; //char형삭제요일변수 
	int intRemoveDay[5] ={0}; //int형삭제요일변수
	char charRemoveSubjectNum[5]={0}; //삭제과목번호
	int intRemoveSubjectNum;
	int nResult;
	int i,j=0,k=0;

	fflush(stdin);
	listBorderDraw(3,12);


	//txt파일에 저장된 시간표 읽어오기
	fp=fopen("timetable.txt","r");

	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("●시간표가 없습니다. 시간표를 만들어주세요.●");
		Sleep(1500);
		//return;
	}

	else {

		fscanf(fp, "%d", &subjectTotalCnt);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);

		for(i=0;i<subjectTotalCnt;i++) {
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		}

		fclose(fp);


		gotoxy(20,12);
		printf("- 시간표 과목삭제 -");

		while(1) {
		gotoxy(15, 14);
		printf("삭제할 과목 요일 : ");
		gotoxy(33, 14);
		gets(charRemoveDay);

		//수정할 해당 요일 과목출력 
		for(k=0; k<5; k++) {
			if ( strstr(charRemoveDay, dayOfWeek[k]) ) { //어떤 요일인지 체크
				for(i=0;i<subjectTotalCnt;i++) {
					if(strstr(dayOfWeek[k],subjectPointer[i].dayOfWeek)) { //입력된 시간표에서 과목정보를 찾고 해당 요일 과목출력
						intRemoveDay[j] = i; //시간표 몇번째에 과목이 있는지 저장
						gotoxy(15, 17+j*2);
						printf("%d) %s %s %s교시", j+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
						j++;
					}
				}
					if(intRemoveDay[0] == 0 ) {
					gotoxy(13,20);
					printf("●해당 요일에 과목이 없습니다.●");
					Sleep(1000);
					gotoxy(13,20);
					printf("                                 ");
					gotoxy(33, 14);
					printf("               ");
					strstr(charRemoveDay,"");
					break;
				}
			}
		}
		if(intRemoveDay[0] != 0) {
			break;
		}

		}

		gotoxy(15,26);
		printf(">> ");
		gotoxy(18,26);
		scanf("%s", &charRemoveSubjectNum);
		intRemoveSubjectNum = atoi(charRemoveSubjectNum)-1;



		for(i=intRemoveDay[intRemoveSubjectNum]+1;i<subjectTotalCnt-1;i++) {

			strcpy(subjectPointer[i-1].dayOfWeek, subjectPointer[i].dayOfWeek);
			strcpy(subjectPointer[i-1].subjectName, subjectPointer[i].subjectName);
			strcpy(subjectPointer[i-1].subjectClass, subjectPointer[i].subjectClass);

		}

		if(subjectTotalCnt-1 == 0 ) {
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
		else
		saveTimetalbe(subjectPointer,subjectTotalCnt-1);


	}
}