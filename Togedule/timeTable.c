
#include"structHeader.h"

char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};


//시간표메뉴함수
void timetableMenu(structMember *s) {
	int choiceMenu;
	while(1) {
		screenBorderDraw() ;
		listBorderDraw(3,10);
		timetableDraw();

		gotoxy(20, 18);
		printf(" 1. 시간표 만들기 ");
		gotoxy(20,20);
		printf(" 2. 시간표 수  정 ");
		gotoxy(20,22);
		printf(" 3. 시간표 삭  제 ");
		gotoxy(20,24);
		printf(">> ");
		scanf("%d", &choiceMenu);
		switch (choiceMenu) {
		case 1: InputSubjectCnt();  break; // 시간표만들기시작
		case 2: modifyMenu(); break; //시간표수정
		case 3: removeTimetable(); break; //시간표삭제
		}

	}
}
//시간표그리기함수
void timetableDraw(){ 

	FILE *fp1;
	int i,j,k;
	int Subjectcnt;
	structSubject* subjectPointer;
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
	fp1=fopen("timetable.txt","r");

	//timetable.txt가 없는 경우
	if(fp1 == NULL ) {
		gotoxy(83,20);
		printf("*시간표를 만들어주세요*");
	}
	//timetable.txt가 있는 경우
	else {

		fscanf(fp1, "%d", &Subjectcnt);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*Subjectcnt);
		for(i=0;i<Subjectcnt;i++) 
			fscanf(fp1,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);

		fclose(fp1);

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
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalCnt) {
	FILE *fp1;   
	int i;

	fp1=fopen("timetable.txt","w");
	fprintf(fp1,"%d\n",subjectTotalCnt);
	for(i=0;i<subjectTotalCnt; i++) {
		fprintf(fp1,"%s ",subjectPointer[i].dayOfWeek);
		fprintf(fp1,"%s ",subjectPointer[i].subjectName);
		fprintf(fp1,"%s\n", subjectPointer[i].subjectClass);
	}
	fclose(fp1);
}


void checkInput(){
	int ch;
	ch = getchar();
	if(ch == 32){
		printf("please check the input whether it is valld or not.\n");
		exit(0);
	}
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

//시간표 월~금 과목갯수 입력 함수
void InputSubjectCnt() {

	int i, subjectTotalCnt=0;
	int SubjectCntOfday[5]={0};


	screenBorderDraw() ;
	listBorderDraw(3,10);


	gotoxy(6, 31);
	printf("** 하루 최대과목 갯수는 5개이하.");
	gotoxy(6, 32);
	printf("**  총 최대과목 갯수는 13개 이하.");

	while (1) {
		gotoxy(20,15);
		printf("- 시간표 만들기 -");

		for(i=0;i<5;i++){
			gotoxy(10, 18+i*2);
			printf(" %s요일 과목 갯수 : ", dayOfWeek[i]);
		}

		for(i=0;i<5;i++){
			gotoxy(30,18+i*2);
			scanf("%d", &SubjectCntOfday[i]);

			//하루과목갯수가 초과할 경우
			if(SubjectCntOfday[i] > 5 ) {
				gotoxy(30, 18+i*2);
				printf(" ◀하루최대과목갯수초과!");
				Sleep(1000);
				gotoxy(30, 18+i*2);
				printf("                        ");
				gotoxy(30, 18+i*2);
				printf("   ");
				i--;
			}

			else {
				subjectTotalCnt += SubjectCntOfday[i];
			}

		}
		//총과목갯수가 초과할 경우
		if(subjectTotalCnt > 13 ){

			for(i=0;i<5;i++){
				gotoxy(35, 18+i*2);
				printf("    ");
			}

			gotoxy(8, 28);
			printf(" ※ 총 최대 과목수(13개)를 초과하셨습니다. ※\n");
			Sleep(1000);
			gotoxy(8, 28);
			printf("                                              ");
			subjectTotalCnt =0;
		}
		else {
			break;
		}
	}
	InputSubjectNameAndClass(SubjectCntOfday,subjectTotalCnt) ;
}

// 이름/교시 입력함수
void InputSubjectNameAndClass(int* SubjectCntOfday, int subjectTotalCnt) {

	structSubject* subjectPointer;
	structSubject tmpSubject;
	int i, j;
	int tmp=12;
	int y=0, k=0;


	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);

	for( i = 0; i < 5; i++){
		if( SubjectCntOfday[i] != 0 ) {
			y++;
			gotoxy(64,10+y);
			printf("*＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊*＊＊＊＊＊\n", dayOfWeek[i]);

			for(j=0; j <SubjectCntOfday[i] ; j++){
				// 과목 구조체에 시간표 요일 입력
				strcpy(subjectPointer[k].dayOfWeek,dayOfWeek[i]);
				k++;
				y++;
				gotoxy(65,10+y);
				printf(" %d. 과목명 :                       교시 :       \n",j+1);
			}
			y++;
			gotoxy(65,10+y);
			printf("\n");
		}
	}

	//이름/교시 입력 조건문
	gotoxy(65, 31);
	printf("** 과목명은 5자이내.");
	gotoxy(65, 32);
	printf("** ex) 교시 : 1,2,3 으로 입력.");

	k=0;
	//과목 이름/교시 입력
	for( i = 0; i < 5; i++){

		strcpy(tmpSubject.dayOfWeek,dayOfWeek[i]);

		for(j=0; j <SubjectCntOfday[i] ; j++){

			y = j+tmp;
			//과목이름
			gotoxy(78,y);
			scanf("%s",&tmpSubject.subjectName);

			//과목교시 ★
			while(1) {
				gotoxy(107,y);
				scanf("%s",&tmpSubject.subjectClass);

				//과목중복교시 검사
				if (checkOverlappingClass(subjectPointer,tmpSubject,subjectTotalCnt) == 0){
					gotoxy(107,y);
					printf("◀교시중복!");
					Sleep(1000);
					gotoxy(107,y);
					printf("           ");
					strcpy(tmpSubject.subjectClass,"");
					//scanf("%s",&subjectPointer[k].subjectClass);
				}
				else
					break;

			}
			
			strcpy(subjectPointer[k].subjectName,tmpSubject.subjectName);
			strcpy(subjectPointer[k].subjectClass,tmpSubject.subjectClass);

			strcpy(tmpSubject.subjectName,"");
			strcpy(tmpSubject.subjectClass,"");
			


			if(j+1 == SubjectCntOfday[i]){
				tmp = 3+y; 
			}
			k++;
		}
		printf("\n");
	}


	saveTimetalbe(subjectPointer,subjectTotalCnt);
	free(subjectPointer);
	system("cls"); 

}

//시간표 수정메뉴
void modifyMenu () {

	int choiceMenu;

	fflush(stdin);
	listBorderDraw(3,10);

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
	int subjectTotalCnt; //과목총갯수
	char charModifyDay[15]; //char형수정요일변수 
	int intModifyDay[5] ={0}; //int형수정요일변수
	char charModifySubjectNum[5]={0}; //수정과목번호
	int intModifySubjectNum;
	int i,j=0,k=0;


	fflush(stdin);
	listBorderDraw(3,10);


	gotoxy(20,12);
	printf("- 시간표 수정 -");
	gotoxy(15, 14);
	printf("수정할 과목 요일 : ");
	gotoxy(33, 14);
	gets(charModifyDay);

	//txt파일에 저장된 시간표 읽어오기
	fp=fopen("timetable.txt","r");
	fscanf(fp, "%d", &subjectTotalCnt);
	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);


	for(i=0;i<subjectTotalCnt;i++) {
		fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
	}

	fclose(fp);

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
			break;
		}
	}


	gotoxy(15,26);
	printf(">> ");
	gotoxy(18,26);
	scanf("%s", &charModifySubjectNum);
	intModifySubjectNum = atoi(charModifySubjectNum)-1;


	//해당과목정보수정
	listBorderDraw(3,10);

	gotoxy(6, 12);
	printf("＊＊＊＊＊＊＊＊＊＊＊현재＊＊＊＊＊＊＊＊＊＊＊");
	gotoxy(9, 14);
	printf("요  일 : %s",subjectPointer[intModifyDay[intModifySubjectNum]].dayOfWeek);
	gotoxy(9, 16);
	printf("과목명 : %s", subjectPointer[intModifyDay[intModifySubjectNum]].subjectName);
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

			gotoxy(18, 27);
			printf("◀교시중복!");
			Sleep(1000);
			gotoxy(18, 27);
			printf("              ");

		}
		else{
			break;
		}

	}

	strcpy(subjectPointer[intModifyDay[intModifySubjectNum]].dayOfWeek, tmpSubject.dayOfWeek);
	strcpy(subjectPointer[intModifyDay[intModifySubjectNum]].subjectName, tmpSubject.subjectName);
	strcpy(subjectPointer[intModifyDay[intModifySubjectNum]].subjectClass, tmpSubject.subjectClass);

	sortTimetable(subjectPointer,subjectTotalCnt);
	free(subjectPointer);
}

//시간표 과목 추가
void addSubject() {
	
	FILE *fp;
	structSubject* subjectPointer;
	structSubject tmpSubject;
	
	int subjectTotalCnt;
	int i;

	fflush(stdin);
	listBorderDraw(3,10);


	fp=fopen("timetable.txt","r");
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

//과목삭제
void removeSubject() {

	FILE *fp;
	structSubject* subjectPointer;//시간표포인터
	int subjectTotalCnt; //과목총갯수
	char charRemoveDay[15]; //char형삭제요일변수 
	int intRemoveDay[5] ={0}; //int형삭제요일변수
	char charRemoveSubjectNum[5]={0}; //삭제과목번호
	int intRemoveSubjectNum;
	int i,j=0,k=0;


	fflush(stdin);
	listBorderDraw(3,10);


	gotoxy(20,12);
	printf("- 시간표 과목삭제 -");
	gotoxy(15, 14);
	printf("삭제할 과목 요일 : ");
	gotoxy(33, 14);
	gets(charRemoveDay);

	//txt파일에 저장된 시간표 읽어오기
	fp=fopen("timetable.txt","r");
	fscanf(fp, "%d", &subjectTotalCnt);
	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);

	for(i=0;i<subjectTotalCnt;i++) {
		fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
	}

	fclose(fp);

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
			break;
		}
	}


	gotoxy(15,26);
	printf(">> ");
	gotoxy(18,26);
	scanf("%s", &charRemoveSubjectNum);
	intRemoveSubjectNum = atoi(charRemoveSubjectNum)-1;

	j=0;

	for(i=intRemoveDay[intRemoveSubjectNum]+1;i<subjectTotalCnt-1;i++) {

		strcpy(subjectPointer[i-1].dayOfWeek, subjectPointer[i].dayOfWeek);
		strcpy(subjectPointer[i-1].subjectName, subjectPointer[i].subjectName);
		strcpy(subjectPointer[i-1].subjectClass, subjectPointer[i].subjectClass);

	}

	saveTimetalbe(subjectPointer,subjectTotalCnt-1);


}


//시간표정렬함수
void sortTimetable(structSubject* subjectPointer,int subjectTotalCnt){


	structSubject * tmpsubjectPointer;
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

	saveTimetalbe(tmpsubjectPointer,subjectTotalCnt);
	gotoxy(15, 29);
	printf("**시간표가 수정을 완료하였습니다**");
	Sleep(1000);
}


void removeTimetable() {

	int nResult;
	char answer;

	listBorderDraw(3,10);

	gotoxy(8,22);
	printf("※ 시간표 전체 삭제가 됩니다. 삭제하시겠습니까?(y/n)");
	gotoxy(8,24);
	printf(">>");
	gotoxy(12,24);
	scanf("%c",&answer);

	if(answer == 'y' || answer == 'Y') {
		nResult = remove("timetable");
		if(nResult == 0) {
			gotoxy(20,26);
			printf("*시간표가 정상적으로 삭제되었습니다*");  //지우기 성공
		} else if (nResult == -1) {
			gotoxy(20,26);
			printf("fail");  //지우기 실패
		}

		Sleep(10000);
	}
}
