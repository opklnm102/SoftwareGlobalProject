#include"structHeader.h"


//시간표 월~금 과목갯수 입력 함수
void InputSubjectCnt() {

	int i, subjectTotalCnt=0;
	int SubjectCntOfday[5]={0};
	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};


	screenBorderDraw() ;
	listBorderDraw(3,12);


	gotoxy(6, 31);
	printf("** 하루 최대과목 갯수는 5개이하.");
	gotoxy(6, 32);
	printf("**  총 최대과목 갯수는 13개 이하.");

	while (1) {
		gotoxy(20,15);
		printf("- 시간표 만들기 -");

		for(i=0;i<5;i++){
			gotoxy(7, 18+i*2);
			printf(" %s요일 과목 갯수 : ", dayOfWeek[i]);
		}

		for(i=0;i<5;i++){
			gotoxy(27,18+i*2);
			scanf("%d", &SubjectCntOfday[i]);

			//하루과목갯수가 초과할 경우
			if(SubjectCntOfday[i] > 5 ) {
				gotoxy(27, 18+i*2);
				printf(" ◀하루최대과목개수(5개)초과!");
				Sleep(1000);
				gotoxy(27, 18+i*2);
				printf("                            ");
				gotoxy(27, 18+i*2);
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
				gotoxy(27, 18+i*2);
				printf("    ");
			}

			gotoxy(12, 28);
			printf(" ※ 총 최대 과목수(13개)를 초과. ※\n");
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
	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
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
	fflush(stdin);
	//과목 이름/교시 입력
	for( i = 0; i < 5; i++){

		strcpy(tmpSubject.dayOfWeek,dayOfWeek[i]);

		for(j=0; j <SubjectCntOfday[i] ; j++){

			y = j+tmp;
			//과목이름
			gotoxy(78,y);
			gets(tmpSubject.subjectName);

			//과목교시
			while(1) {
				gotoxy(107,y);
				gets(tmpSubject.subjectClass);

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