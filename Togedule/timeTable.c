#include"structHeader.h"

//● 시간표메뉴함수
void timetableMenu(structMember *s) {	
	char choiceMenu[3];
	char *endP;

	screenBorderDraw() ;

	while(1) {

		listBorderDraw(3,12);
		timetableDraw(s);
		fflush(stdin);

		/*----------메뉴 출력----------*/
		gotoxyPrint(20, 17, " 1 시간표 만들기 ");
		gotoxyPrint(20, 19, " 2 시간표 수  정 ");
		gotoxyPrint(20, 21, " 3 시간표 전체삭제 ");
		gotoxyPrint(20, 23, " 4 시간표 나가기 ");
		gotoxyPrint(13, 26, "원하는 메뉴의 숫자를 입력해주세요");
		gotoxyPrint(12, 27, " >> ");


		/*----------메뉴 선택지 입력------------*/
		fgets(choiceMenu,sizeof(choiceMenu), stdin);

		/*----------(키 입력이 한 문자인 경우)----------*/
		if( (endP=strchr(choiceMenu, '\n')) != NULL ) {
			*endP = '\0';

			/*----------선택한 메뉴 실행----------*/
			switch (choiceMenu[0]) {
				//시간표 만들기
			case '1': makeTimetable(s);  break; 
				//시간표 수정
			case '2': modifyMenu(s); break;
				//시간표 전체삭제
			case '3': removeTimetable(s); break;
				//시간표 종료
			case '4': return;
			case 'b': return;
			case 'B': return;
			case 'x': exit(0);
			case 'X': exit(0);
				//한 문자가 들어왔지만 선택지에 없는 문자일 때
			default: {

				if(choiceMenu[0] == '\0') {
					gotoxyPrint(16, 30, "●메뉴를 선택하지 않았습니다●"); fflush(stdin); Sleep(1000);
				}
				else{

					gotoxyPrint(16, 30, "●메뉴선택이 잘못되었습니다●"); fflush(stdin); Sleep(1000);
				}

					 }
			}
		}

		/*----------(키 입력이 두 문자 이상인 경우)----------*/
		else{
			gotoxyPrint(16, 30, "●메뉴선택이 잘못되었습니다●");
			fflush(stdin);
			Sleep(1000);
		}
	}
}

//● 시간표그리기함수
void timetableDraw(structMember *s){ 

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	FILE *fp;
	char fileName[30];
	structSubject* subjectPointer;
	int subjectTotalNum;
	int tmpintClass[10]={0};
	int i,j,k;

	/*----------시간표 틀 그리기----------*/
	gotoxyPrint(57, 7, "┌───┬─────┬─────┬─────┬─────┬─────┐");
	gotoxyPrint(57, 8, "│ 교시 │    월    │    화    │    수    │    목    │    금    │");
	gotoxyPrint(57, 9, "├───┼─────┼─────┼─────┼─────┼─────┤");
	for(i=0; i<26; i+=2) { 
		gotoxy(57,10+i);
		printf("│  %2d  │          │          │          │          │          │",i/2+1);
		gotoxy(57,10+i+1);
		if(i!= 24)
			printf("├───┼─────┼─────┼─────┼─────┼─────┤");
	}
	gotoxyPrint(57, 35, "└───┴─────┴─────┴─────┴─────┴─────┘");


	/*----------사용자 텍스트파일 오픈----------*/
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");


	/*----------(사용자 텍스트파일이 없는 경우)----------*/
	if(fp == NULL ) {
		gotoxyPrint(83, 20, "*시간표를 만들어주세요*");
	}

	/*----------(사용자 텍스트파일이 있는 경우)----------*/
	else {

		// 텍스트파일에 있는 과목개수를 읽어서 동적할당
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalNum);
		for(i=0;i<subjectTotalNum;i++) 
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		fclose(fp);

		/*----------텍스트파일에 있는 과목교시를 읽어서 맞는 위치에 과목이름 출력----------*/
		for(i=0;i<5;i++) {
			for(j=0;j<subjectTotalNum;j++) {

				/*----------(저장된 과목들의 요일과 월~금요일 비교)----------*/
				if( strstr(subjectPointer[j].dayOfWeek, dayOfWeek[i]) ) {

					//이미 저장된 과목들의 char형교시를 int형으로 변환
					classAtoi(subjectPointer[j].subjectClass, tmpintClass);

					//과목 별로 해당하는 위치에 과목이름 출력
					for(k=0;k<10 ; k++) {

						if(tmpintClass[k] >= 1 && tmpintClass[k] <= 13) {
							gotoxy(67+12*i,8+tmpintClass[k]*2);
							printf("%s",subjectPointer[j].subjectName);
						}

						else
							break;
					}

					for(k=0;k<10; k++)
						tmpintClass[k] = 0;
				}
			}
		}
	}
}

//● 시간표 사용자의 텍스트파일로 저장하는 함수
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalNum, structMember *s) {

	FILE *fp;
	char fileName[30];
	int i;

	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"w");

	fprintf(fp,"%d\n",subjectTotalNum);

	for(i=0;i<subjectTotalNum; i++)
		fprintf(fp,"%s %s %s\n",subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);

	fclose(fp);
}

//● 과목명 빈칸 체크함수
int checkBlankOfSubjectName(char* subjectName) {

	int i;

	for(i=0; subjectName[i] !='\0'; i++) {

		if(subjectName[i] == ' ')
			return 0;
	}

	return 1;

}

//● 교시에 저장된 char형의 숫자를 int형의 숫자로 바뀌어주는 함수.
void classAtoi(char *subjectClass, int *tmpIntClass) {

	int i, j=0, num=0;

	for(i=0; subjectClass[i] != '\0'; i++) {

		/*----------(과목교시에서 (char형)문자인 경우)----------*/
		if(subjectClass[i] == ' ' || subjectClass[i] == ',') {
			tmpIntClass[j]=num;
			num = 0;
			j++;
		}
		/*----------(과목교시에서 (char형)숫자인 경우)----------*/
		else if (subjectClass[i] >= '0' && subjectClass[i] <= '9') {

			// (char형)숫자가 십의 자리일때
			if(num != 0) {

				num = num*10 + (subjectClass[i]-'0');

				if(subjectClass[i+1] == '\0')
					tmpIntClass[j] = num;
			}

			// (char형)숫자가 일의 자리일때
			else {
				num = (subjectClass[i]-'0');

				if(subjectClass[i+1] == '\0')
					tmpIntClass[j] = num;
			}
		}	
	}
}


//● 시간표 교시중복검사 함수
int checkOverlappingInClass(structSubject* subjectPointer, structSubject subject,int subjectTotalNum) {

	int savedClass[10]={0},puttingClass[10]={0};
	int i,j,k;


	//입력중인 과목의 char형교시를 int형으로 변환
	classAtoi(subject.subjectClass,puttingClass);

	/*----------입력중인 과목의 교시와 저장된 과목들 교시와 비교----------*/
	for(i=0; i<subjectTotalNum; i++) {

		/*----------(입력중인 과목이 저장된 과목들중 요일과 같은 경우)----------*/
		if(strstr(subjectPointer[i].dayOfWeek, subject.dayOfWeek)){
			if(subjectPointer[i].subjectClass[0] >= '0' && subjectPointer[i].subjectClass[0] <= '9'){

				//이미 저장된 과목들의 char형교시를 int형으로 변환
				classAtoi(subjectPointer[i].subjectClass,savedClass);

				//과목중복검사
				for(j=0; puttingClass[j] != 0 ; j++){
					for(k=0; savedClass[k] != 0 ; k++) {

						//교시가 같으면 0 (false)
						if(puttingClass[j] == savedClass[k]){
							return 0;
						}
					}
				}
			}
		}
	}
	//교시가 같지 않으면 1 (true)
	return 1;
}

//● 시간표 교시숫자 검사 함수
int checkNumInClass(char* subjectClass) {

	int intSubjectClass[10];
	int i;

	classAtoi(subjectClass,intSubjectClass);

	for(i=0;i<10; i++) {

		//교시가 13교시를 넘으면 return 0
		if(intSubjectClass[i] >13) {
			return 0;
		}
	}	
	return 1;
}

//● 시간표 교시 문자 검사 함수
int checkCharaterInClass(char* subjectClass) {

	int i;

	for(i=0; subjectClass[i] != '\0'; i++){

		//교시가 숫자가 아닐때 ','문자도 아니면 return0
		if(subjectClass[i] <'0' || subjectClass[i] >'9' ){
			if(subjectClass[i] != ',') {
				return 0;

			}
		}
	}
	return 1;
}

//● 시간표정렬함수
void sortTimetable(structSubject* subjectPointer,int subjectTotalNum, structMember *s){

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	structSubject * tmpsubjectPointer;
	int i,j,k=0;

	tmpsubjectPointer = (structSubject *)malloc(sizeof(structSubject) * subjectTotalNum);

	/*----------월요일부터 금요일까지 순서대로 과목들의 순서 정렬----------*/
	for(i=0;i<5; i++ ) {
		for(j=0;j<subjectTotalNum; j++ ){
			if (strstr(dayOfWeek[i], subjectPointer[j].dayOfWeek)){
				strcpy(tmpsubjectPointer[k].dayOfWeek, subjectPointer[j].dayOfWeek);
				strcpy(tmpsubjectPointer[k].subjectClass, subjectPointer[j].subjectClass);
				strcpy(tmpsubjectPointer[k++].subjectName, subjectPointer[j].subjectName);
			}
		}
	}

	saveTimetalbe(tmpsubjectPointer,subjectTotalNum, s);
	gotoxyPrint(15, 31, "**시간표가 수정을 완료하였습니다**");
	Sleep(1000);
}

//● 사용자텍스트파일이름을 리턴해주는 함수
char* getUserTextFileName (structMember *s) {

	char fileName[30];

	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"timetable");
	strcat(fileName,".txt");

	return fileName;
}