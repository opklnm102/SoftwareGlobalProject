#include"structHeader.h"

//시간표메뉴함수
void timetableMenu(structMember *s) {

	int choiceMenu;

	while(1) {
		screenBorderDraw() ;
		listBorderDraw(3,12);
		timetableDraw(s);

		gotoxy(20, 18);
		printf(" 1. 시간표 만들기 ");
		gotoxy(20,20);
		printf(" 2. 시간표 수  정 ");
		gotoxy(20,22);
		printf(" 3. 시간표 삭  제 ");
		gotoxy(20,24);
		printf(" 4. 시간표 나가기 ");

		gotoxy(20,26);
		printf(">> ");
		scanf("%d", &choiceMenu);
		switch (choiceMenu) {
		case 1: InputSubjectCnt(s);  break; // 시간표만들기시작
		case 2: modifyMenu(s); break; //시간표수정
		case 3: removeTimetable(s); break; //시간표삭제
		case 4: return;
		}

	}
}
//시간표그리기함수
void timetableDraw(structMember *s){ 

	FILE *fp;
	char fileName[30];
	int i,j,k;
	int Subjectcnt;
	structSubject* subjectPointer;
	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	int tmpClassCnt[10]={0};
	int b=0;

	gotoxy(57,7); 
	printf("┌───┬─────┬─────┬─────┬─────┬─────┐");
	gotoxy(57,8);
	printf("│ 교시 │    월    │    화    │    수    │    목    │    금    │"); 
	gotoxy(57,9);
	printf("├───┼─────┼─────┼─────┼─────┼─────┤");
	for(i=0; i<26; i+=2) { 
		gotoxy(57,10+i);
		printf("│  %2d  │          │          │          │          │          │",i/2+1);
		gotoxy(57,10+i+1);
		if(i!= 24)
			printf("├───┼─────┼─────┼─────┼─────┼─────┤");
	}
	gotoxy(57,35);
	printf("└───┴─────┴─────┴─────┴─────┴─────┘");

	
	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"timetable");
	strcat(fileName,".txt");

	fp=fopen(fileName,"r");


	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxy(83,20);
		printf("*시간표를 만들어주세요*");
	}
	//timetable.txt가 있는 경우
	else {

		fscanf(fp, "%d", &Subjectcnt);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*Subjectcnt);
		for(i=0;i<Subjectcnt;i++) 
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);

		fclose(fp);

		for(j=0;j<5;j++) {
			for(i=0;i<Subjectcnt;i++) {

				if( strstr(subjectPointer[i].dayOfWeek, dayOfWeek[j]) ) {

					classAtoi(subjectPointer[i].subjectClass, tmpClassCnt);

					for(k=0;k<10 ; k++) {

						if(tmpClassCnt[k] >= 1 && tmpClassCnt[k] <= 13) {
							gotoxy(67+12*j,8+tmpClassCnt[k]*2);
							printf("%s",subjectPointer[i].subjectName);
						}

						else
							break;
					}

					for(k=0;k<10; k++)
						tmpClassCnt[k] = 0;
				}
			}
		}
	}

	

}
//시간표 txt로 저장하는 함수
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalCnt, structMember *s) {
	
	FILE *fp;
	char fileName[30];
	int i;


	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"timetable");
	strcat(fileName,".txt");

	fp=fopen(fileName,"w");
	fprintf(fp,"%d\n",subjectTotalCnt);

	for(i=0;i<subjectTotalCnt; i++) {
		fprintf(fp,"%s ",subjectPointer[i].dayOfWeek);
		fprintf(fp,"%s ",subjectPointer[i].subjectName);
		fprintf(fp,"%s\n", subjectPointer[i].subjectClass);
	}
	fclose(fp);
}




//교시에 저장된 char형의 숫자를 int형의 숫자로 바뀌어주는 함수.
void classAtoi(char *subjectClass, int *savedClass) {


	int i, k=0, num=0;


	for(i=0; subjectClass[i] != '\0'; i++) {

			 if(subjectClass[i] == ' ' || subjectClass[i] == ',') {

				 savedClass[k]=num;
				 num = 0;
				 k++;
			 }

			 else if (48 <= subjectClass[i] && subjectClass[i] <= 57) {

				 if(num != 0) {
					 num = num*10 + (subjectClass[i]-48);

					 if(subjectClass[i+1] == '\0')
						 savedClass[k] = num;
				 }

				 else {
					 num = (subjectClass[i]-48);

					 if(subjectClass[i+1] == '\0')
						 savedClass[k] = num;
				 }

			 }			

		 }

}


///시간표 교시중복검사 함수
int checkOverlappingClass(structSubject* subjectPointer, structSubject subject,int subjectTotalCnt) {

	int i,j,k;
	int savedClass[10]={0},puttingClass[10]={0};


	classAtoi(subject.subjectClass,puttingClass);

	for(i=0;i<subjectTotalCnt;i++) {

		if(strstr(subjectPointer[i].dayOfWeek, subject.dayOfWeek)){
			if(subjectPointer[i].subjectClass[0] >= '0' && subjectPointer[i].subjectClass[0] <= '9'){

				classAtoi(subjectPointer[i].subjectClass,savedClass);
				
				for(j=0; puttingClass[j] != 0 ; j++){
					for(k=0; savedClass[k] != 0 ; k++) {
						if(puttingClass[j] == savedClass[k]){
							return 0;
						}
							
					}
				}
				

			}

		}
	}
	return 1;


}



//시간표정렬함수
void sortTimetable(structSubject* subjectPointer,int subjectTotalCnt, structMember *s){

	structSubject * tmpsubjectPointer;
	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	int i,j,k=0;

	tmpsubjectPointer = (structSubject *)malloc(sizeof(structSubject) * subjectTotalCnt);

	for(i=0;i<5; i++ ) {
		for(j=0;j<subjectTotalCnt; j++ ){

			if (strstr(dayOfWeek[i], subjectPointer[j].dayOfWeek)){
				strcpy(tmpsubjectPointer[k].dayOfWeek, subjectPointer[j].dayOfWeek);
				strcpy(tmpsubjectPointer[k].subjectClass, subjectPointer[j].subjectClass);
				strcpy(tmpsubjectPointer[k++].subjectName, subjectPointer[j].subjectName);
			}
		}
	}

	saveTimetalbe(tmpsubjectPointer,subjectTotalCnt, s);
	gotoxy(15, 31);
	printf("**시간표가 수정을 완료하였습니다**");
	Sleep(1000);
}