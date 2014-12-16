#include"structHeader.h"

//● 시간표 만들기 함수
void makeTimetable(structMember *s) {

	int SubjectNumOfoneday[5]={0}, subjectTotalNum=0;

	if(InputSubjectNum(SubjectNumOfoneday,&subjectTotalNum, s) == 1) 
		InputSubjectNameAndClass(SubjectNumOfoneday,subjectTotalNum, s);
}


//● 시간표 월~금 과목갯수 입력 함수
int InputSubjectNum(int* SubjectNumOfoneday, int* subjectTotalNum, structMember *s) {

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	char tmpSubjectNum[3];
	char *endP;
	int i;


	screenBorderDraw() ;
	listBorderDraw(3,12);
	fflush(stdin);

	/*----------과목 개수 제한문 출력----------*/
	gotoxyPrint(6, 34,"▩ 하루 최대과목 개수는 5개 이하입니다");
	gotoxyPrint(6, 35,"▩ 총 최대과목 개수는 13개 이하입니다");

	/*----------요일 별로 과목 개수 입력받는 while문----------*/
	while (1) {

		/*----------과목 개수 입력받는 틀 출력----------*/
		gotoxyPrint(20, 15,"- 시간표 만들기 -");

		for(i=0;i<5;i++){
			gotoxy(7, 19+i*2);
			printf(" %s요일 과목 개수 : ", dayOfWeek[i]);
		}

		/*----------요일 별로 과목 개수 입력 받기----------*/
		for(i=0;i<5;i++){

			fflush(stdin);

			//요일별로 과목 개수 입력
			gotoxy(27,19+i*2);
			fgets(tmpSubjectNum,sizeof(tmpSubjectNum), stdin);
			if( (endP=strchr(tmpSubjectNum, '\n')) != NULL ) {
				*endP = '\0';

				/*----------(키 입력이 한 문자인 경우)----------*/

				//하루과목개수가 5이상 9이하인 경우 (한자리 문자)
				if(tmpSubjectNum[0] > '5' && tmpSubjectNum[0] <= '9') {
					warning(27,19+i*2,"◀하루최대과목개수(5개)초과","                           ");
					i--;
				}

				//입력값이 문자인 경우
				else if((tmpSubjectNum[0] == 'b'|| tmpSubjectNum[0] == 'B' )&& tmpSubjectNum[1] == '\0' ){

					gotoxyPrint(6, 34,"                                      ");
					gotoxyPrint(6, 35,"                                       ");
					return 0;
				}

				else if((tmpSubjectNum[0] == 'x'|| tmpSubjectNum[0] == 'X' )&& tmpSubjectNum[1] == '\0' )exit(0);

				//입력값이 문자인 경우
				else if((tmpSubjectNum[0] < '0' || tmpSubjectNum[0] > '9') && tmpSubjectNum[0] != '\0') {
					warning(27,19+i*2,"◀숫자를 입력해주세요","                           ");
					i--;
				}

				//입력 없이 Enter를 누른 경우
				else if(tmpSubjectNum[0] == '\0') {
					warning(27,19+i*2,"◀과목개수를 입력해주세요","                           ");
					i--;
				}
				//과목 개수 입력이 올바른 경우
				else {
					SubjectNumOfoneday[i] = tmpSubjectNum[0] - '0';
					*subjectTotalNum += SubjectNumOfoneday[i];
				}
			}

			/*----------(키 입력이 두 문자 이상인 경우)----------*/
			else{

				//과목개수를 음수로 입력한 경우
				if(tmpSubjectNum[0] == '-') {
					warning(27,19+i*2,"◀양수로 입력해주세요","                           ");
					i--;
				}
				//두자리이상의 숫자를 입력한 경우
				else if((tmpSubjectNum[0] > '0' && tmpSubjectNum[0] <= '9') ) {


					if(tmpSubjectNum[1] < '0' || tmpSubjectNum[1] > '9') {
						warning(27,19+i*2,"◀숫자를 입력해주세요","                           ");
						i--;
					}
					else {
						warning(27,19+i*2,"◀하루최대과목개수(5개)초과","                           ");
						i--;
					}



				}
				//문자가 입력된 경우
				else if((tmpSubjectNum[0] < '0' || tmpSubjectNum[0] > '9' )) {
					warning(27,19+i*2,"◀숫자를 입력해주세요","                           ");
					i--;
				}
				//그외 나머지인 경우
				else {
					warning(27,19+i*2,"◀입력이 잘못되었습니다.","                           ");
					i--;
				}

			}

		}

		/*----------(시간표의 총 과목개수가 초과할 경우)----------*/
		if(*subjectTotalNum > 13 ){

			// 스크린에 입력한 데이터를 지우고 경고문 출력 후 while문을 다시 반복
			for(i=0;i<5;i++)
				gotoxyPrint(27, 19+i*2, "    ");

			gotoxyPrint(12, 29, " ※ 총 최대 과목수(13개)를 초과. ※\n");
			Sleep(1000);
			gotoxyPrint(8, 29, "                                              ");
			*subjectTotalNum =0;
		}

		/*----------(시간표의 총 과목개수가 초과하지 않는 경우)----------*/
		else {
			//while문 끝냄
			break;
		}
	}

	return 1;
}

//● 과목명/교시 입력함수
void InputSubjectNameAndClass(int* SubjectNumOfoneday, int subjectTotalNum, structMember *s) {

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	structSubject* subjectPointer;
	structSubject tmpSubject;
	char *endPointer;
	int StartCourYOfSubject=12;
	int frameCourY=0, inputCurY=0;
	int subjectCnt=0;
	int i, j;

	/*----------과목 총 개수만큼 동적할당----------*/
	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalNum);

	/*----------요일별 과목 이름/교시 입력 틀 출력----------*/
	for( i = 0; i < 5; i++){

		/*----------(요일 별로 과목 개수가 0개가 아닌 경우)----------*/
		if( SubjectNumOfoneday[i] != 0 ) {
			frameCourY++;
			gotoxy(59,10+frameCourY);
			printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n", dayOfWeek[i]);

			//해당 요일의 하루당 과목 개수만큼 과목명/교시 틀 출력
			for(j=0; j <SubjectNumOfoneday[i] ; j++){
				strcpy(subjectPointer[subjectCnt++].dayOfWeek,dayOfWeek[i]);
				frameCourY++;
				gotoxy(60,10+frameCourY);
				printf(" %d. 과목명 :                          교시 :       \n",j+1);
			}
			frameCourY++;
			gotoxyPrint(60,10+frameCourY, "\n");
		}
	}

	/*----------과목명/교시 입력 제한문 출력----------*/
	gotoxyPrint(60, 12+frameCourY, "▩ 과목명은 빈칸없이 5자이내 입니다");
	gotoxyPrint(60, 13+frameCourY, "▩ 과목교시는 숫자와 ','이외의 문자는 입력되지 않습니다");
	gotoxyPrint(60, 14+frameCourY, "▩ 과목교시예시: '1,2,3' ");


	subjectCnt=0;
	fflush(stdin);

	/*----------과목명/교시 입력----------*/
	for( i = 0; i < 5; i++){

		strcpy(tmpSubject.dayOfWeek,dayOfWeek[i]);

		for(j=0; j <SubjectNumOfoneday[i] ; j++){

			/*----------과목명 입력----------*/
			inputCurY = j+StartCourYOfSubject;

			while(1) {

				fflush(stdin);
				gotoxy(73,inputCurY);
				fgets(tmpSubject.subjectName, 11, stdin);

				/*----------(키 입력이 5자(한글기준) 이내인 경우)----------*/
				if( (endPointer=strchr(tmpSubject.subjectName, '\n')) != NULL ) {
					*endPointer = '\0';


					//입력없이 Enter를 누른 경우
					if(tmpSubject.subjectName[0] == '\0'){
						strcpy(tmpSubject.subjectName,"");
						warning(72, inputCurY, "◀과목명을미입력했습니다", "                          ");
					}

					else if((tmpSubject.subjectName[0] == 'b'|| tmpSubject.subjectName[0] == 'B' )&& tmpSubject.subjectName[1] == '\0' ){

						gotoxyPrint(60, 12+frameCourY, "                                    ");
						gotoxyPrint(60, 13+frameCourY, "                                                       ");
						gotoxyPrint(60, 14+frameCourY, "                         ");
						gotoxyPrint(6, 34,"                                      ");
						gotoxyPrint(6, 35,"                                       ");
						return;
					}

					else if((tmpSubject.subjectName[0] == 'x'|| tmpSubject.subjectName[0] == 'X' )&& tmpSubject.subjectName[1] == '\0' ) exit(0);



					//과목명에 빈칸이 있는 경우
					else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
						strcpy(tmpSubject.subjectName,"");
						warning(72, inputCurY, "◀과목명에빈칸이있습니다", "                          ");

					}

					//과목명 조건에 만족하는 경우
					else {
						break;
					}
				}

				/*----------(키 입력이 5자 이상인 경우)----------*/
				else {
					strcpy(tmpSubject.subjectName,"");
					warning(72, inputCurY, "◀과목명5자를초과했습니다", "                          ");
				}

			}



			/*----------과목교시 입력----------*/
			while(1) {

				//과목교시 입력
				fflush(stdin);
				gotoxy(104,inputCurY);
				fgets(tmpSubject.subjectClass,sizeof(tmpSubject.subjectClass), stdin);

				/*----------(키 입력이 10자 이내인 경우)----------*/
				if( (endPointer=strchr(tmpSubject.subjectClass, '\n')) != NULL ) {
					*endPointer = '\0';


					if((tmpSubject.subjectClass[0] == 'b'|| tmpSubject.subjectClass[0] == 'B' )&& tmpSubject.subjectClass[1] == '\0' ){
						gotoxyPrint(60, 12+frameCourY, "                                    ");
						gotoxyPrint(60, 13+frameCourY, "                                                       ");
						gotoxyPrint(60, 14+frameCourY, "                         ");
						gotoxyPrint(6, 34,"                                      ");
						gotoxyPrint(6, 35,"                                       ");
						return;
					}

					else if((tmpSubject.subjectClass[0] == 'x'|| tmpSubject.subjectClass[0] == 'X' )&& tmpSubject.subjectClass[1] == '\0' ) exit(0);


					//숫자와','이외의 문자가 들어올때
					else if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
						warning(104, inputCurY, "◀','와숫자이외의문자", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}

					//교시를 입력하지 않고 Enter를 쳤을때
					else if(tmpSubject.subjectClass[0] == '\0') {
						warning(104, inputCurY, "◀교시를미입력했습니다", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}

					//교시를 중복되게 쳤을때
					else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
						warning(104, inputCurY, "◀교시가중복됩니다", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}

					//1~13교시 이외의 교시를 입력 했을때
					else if(checkNumInClass(tmpSubject.subjectClass) == 0){
						warning(104, inputCurY, "◀1~13이외교시입니다", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}
					//입력이 올바를 때
					else 
						break;



				}
				/*----------(키 입력이 10자 이상인 경우)----------*/
				else{
					warning(104, inputCurY, "◀교시글자수초과했습니다", "                       ");
					strcpy(tmpSubject.subjectClass,"");
				}
			}

			/*----------과목명/교시 입력후 동적할당한 변수에 저장 및 tmpSubject(변수)  초기화---------*/
			strcpy(subjectPointer[subjectCnt].subjectName,tmpSubject.subjectName);
			strcpy(subjectPointer[subjectCnt].subjectClass,tmpSubject.subjectClass);
			strcpy(tmpSubject.subjectName,"");
			strcpy(tmpSubject.subjectClass,"");


			/*----------다음 요일 시작 y좌표 계산---------*/
			if(j+1 == SubjectNumOfoneday[i]){
				StartCourYOfSubject = 3+inputCurY; 
			}

			//과목명/교시입력이 완료된 후 다음 과목명/교시입력을 위해 카운트 증가
			subjectCnt++;
		}
		printf("\n");
	}

	//입력된 시간표정보를 txt파일에 저장
	saveTimetalbe(subjectPointer,subjectTotalNum, s);

	free(subjectPointer);
	system("cls"); 


}


