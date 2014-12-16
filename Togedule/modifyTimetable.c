#include"structHeader.h"

//●시간표 수정메뉴
void modifyMenu (structMember *s) {

	char cChoiceMenu[3];
	char *p;

	while(1) {

		listBorderDraw(3,12);
		timetableDraw(s);


		/*----------시간표 수정 메뉴 출력----------*/
		gotoxyPrint(22, 15, "*시간표 수정메뉴*");
		gotoxyPrint(17, 18, " 1 시간표 과목정보 수정 ");
		gotoxyPrint(17, 20, " 2 시간표 과목 추가 ");
		gotoxyPrint(17, 22, " 3 시간표 과목 삭제 ");
		gotoxyPrint(17, 24, " 4 시간표 수정메뉴 나가기 ");
		gotoxyPrint(11, 27, "원하는 선택 메뉴의 숫자를 입력해주세요");
		gotoxyPrint(10, 28, " >> ");

		/*----------메뉴 선택지 입력------------*/
		fflush(stdin);
		fgets(cChoiceMenu,sizeof(cChoiceMenu), stdin);

		/*----------(키 입력이 한 문자인 경우)----------*/
		if( (p=strchr(cChoiceMenu, '\n')) != NULL ) {
			*p = '\0';


			/*----------선택한 메뉴 실행----------*/
			switch (cChoiceMenu[0]) {
				//시간표과목수정
			case '1': modifySubjectInfo(s);  break; //시간표 과목정보 수정
				//시간표과목추가
			case '2': addSubject(s); break; //시간표 과목 추가
				//시간표과목삭제
			case '3': removeSubject(s); break; //시간표 과목 삭제
				//시간표수정메뉴나가기
			case '4': return;
				//한 문자가 들어왔지만 선택지에 없는 문자일 때
			case 'b': return;
			case 'B': return;
			case 'x': exit(0);
			case 'X': exit(0);
			default:
				{

					if(cChoiceMenu[0] == '\0') {
						gotoxyPrint(16, 30, "●메뉴를 선택하지 않았습니다●"); fflush(stdin); Sleep(1000);
					}

					gotoxyPrint(16, 30, "●메뉴선택이 잘못되었습니다●"); fflush(stdin); Sleep(1000);

				}
			}
		}

		/*----------(키 입력이 두 문자 이상인 경우)----------*/
		else{
			gotoxyPrint(16, 30, "●메뉴선택이 잘못되었습니다.●");
			fflush(stdin);
			Sleep(1000);
		}
	}

}


//●시간표 과목정보 수정
void modifySubjectInfo(structMember *s) {

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	FILE *fp;
	char fileName[30];
	structSubject* subjectPointer;
	structSubject tmpSubject;
	int subjectTotalNum;
	char modifyDay[15];
	int OrderOfSubject[5] ={0};
	char modifySubject[5];
	int intModifySubjectNum;
	int subjectCntOfModifyDay=0;
	int day, subjectCnt;
	char *endPointer;
	int checkDay;
	int checkChoice;


	fflush(stdin);
	listBorderDraw(3,12);


	/*----------사용자의 시간표 텍스트 파일 오픈----------*/
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");


	/*----------(사용자의 시간표 텍스트 파일이 없는 경우)----------*/
	if(fp == NULL ) {
		gotoxyPrint(8, 20, "●시간표가 없습니다. 시간표를 만들어주세요●");
		Sleep(1500);
		return;
	}

	/*----------(사용자의 시간표 텍스트 파일이 있는 경우)----------*/
	else {

		/*----------사용자의 시간표 텍스트 파일에 저장된 시간표 읽기----------*/
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject) * subjectTotalNum);
		for(subjectCnt=0; subjectCnt<subjectTotalNum; subjectCnt++) 
			fscanf(fp,"%s %s %s", subjectPointer[subjectCnt].dayOfWeek, subjectPointer[subjectCnt].subjectName, subjectPointer[subjectCnt].subjectClass);
		fclose(fp);


		gotoxyPrint(20, 14, "- 시간표 수정 -");
		gotoxyPrint(7, 16, "수정할 과목의 요일 : ");
		gotoxyPrint(5, 33, "▩ 수정할 과목의 요일예시: '월' 또는 '월요일' ");


		/*----------수정할 과목의 요일 입력----------*/
		while(1) {
			fflush(stdin);
			gotoxy(28, 16);
			fgets(modifyDay,8, stdin);

			/*----------(modify 배열 크기이하로 입력할 경우)----------*/
			if( (endPointer = strchr(modifyDay, '\n')) != NULL ) {
				*endPointer = '\0';

				checkDay = checkModifyDay(modifyDay);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((modifyDay[0] == 'b'|| modifyDay[0] == 'B' )&& modifyDay[1] == '\0' ){
					gotoxyPrint(5, 33, "                                              ");
					return;
				}
				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((modifyDay[0] == 'x'|| modifyDay[0] == 'X' )&& modifyDay[1] == '\0' )  exit(0);

				/*----------(입력이 있지만 요일(월~금)을 입력하지 않은 경우)----------*/
				else if(checkDay == 0){
					warning(28,16,"◀수정할요일을입력해주세요", "                          ");
					fflush(stdin);
					strcpy(modifyDay,"");
				}

				/*----------(요일을 두개이상 입력한 경우)----------*/
				else if (checkDay == 2) {
					warning(28,16,"◀요일을하나만입력해주세요", "                          ");
					fflush(stdin);
					strcpy(modifyDay,"");

				}



				/*----------(요일을 한개 입력한 경우)----------*/
				else {


					/*----------수정할 해당 요일 과목출력 ----------*/
					for(day=0; day<5; day++) {

						// 무슨 요일인지 체크
						if(strstr(modifyDay, dayOfWeek[day])) {

							// 요일 입력 제한 글자체크
							if(strstr(modifyDay,"요일") || (strcmp(modifyDay,dayOfWeek[day]) == 0 )) {

								// 사용자 시간표에서 사용자가 입력한 요일 찾기
								for(subjectCnt=0; subjectCnt<subjectTotalNum; subjectCnt++) {

									// 해당 요일 과목출력
									if( strstr(dayOfWeek[day], subjectPointer[subjectCnt].dayOfWeek) ) { 

										//시간표 몇번째에 과목이 있는지 저장
										OrderOfSubject[subjectCntOfModifyDay] = subjectCnt+1; 

										//해당 요일 과목 출력
										gotoxy(15, 19 + subjectCntOfModifyDay * 2 );
										printf("%d %s %s %s교시", subjectCntOfModifyDay+1, subjectPointer[subjectCnt].dayOfWeek, subjectPointer[subjectCnt].subjectName, subjectPointer[subjectCnt].subjectClass);
										subjectCntOfModifyDay++;
									}
								}

								//수정할 요일에 과목이 없는 경우
								if(OrderOfSubject[0] == 0) {
									gotoxyPrint(13, 22, "●해당 요일에 과목이 없습니다●");
									Sleep(1000);
									gotoxyPrint(13, 22, "                                ");
									gotoxyPrint(28, 16, "               ");
									strcpy(modifyDay,"");
									break;
								}
							}

							// 요일 형식이외의 입력을 했을 경우
							else{
								warning(28,16,"◀요일입력이 잘못되었습니다", "                          ");
								fflush(stdin);
								strcpy(modifyDay,"");
								break;


							}
						}


					}
					//수정할 과목을 선택했을 경우
					if(OrderOfSubject[0] != 0) {
						break;
					}
				}
			}


			/*----------(modify 배열 크기 이상으로 입력할 경우)----------*/
			else {
				warning(28, 16,"◀요일입력을잘못했습니다","                          ");
				strstr(modifyDay,"");
				fflush(stdin);
			}

		}

		fflush(stdin);
		gotoxyPrint(10, 29, "수정할 과목의 해당 숫자를 입력해주세요");
		gotoxyPrint(10, 30, " >> ");



		/*----------수정할 과목의 요일에서 과목 선택하는 while문----------*/
		while(1) {

			fflush(stdin);
			gotoxy(13,30);
			fgets(modifySubject, sizeof(modifySubject), stdin);

			/*----------(modifySubject 배열 크기이하로 입력할 경우)----------*/
			if( (endPointer = strchr(modifySubject, '\n')) != NULL ) {
				*endPointer = '\0';

				//수정할 과목 선택 입력 체크
				checkChoice = checkChoiceOfSubject(modifySubject, subjectCntOfModifyDay);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((modifySubject[0] == 'b'|| modifySubject[0] == 'B' )&& modifySubject[1] == '\0' ){
					gotoxyPrint(5, 33, "                                              ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((modifySubject[0] == 'x'|| modifySubject[0] == 'X' )&& modifySubject[1] == '\0' )  exit(0);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				else if(modifySubject[0] == '\0') {
					warning(13, 30, "◀수정할과목을선택해주세요", "                                ");
					strcpy(modifySubject,"");
				}

				/*----------(수정 과목 선택 입력이 정상적으로 입력된 경우)----------*/
				else if( checkChoice == 0) {
					intModifySubjectNum = atoi(&modifySubject[0])-1;
					break;
				}

				/*----------(수정 과목 선택 입력이 숫자이외의 문자가 들어왔을 경우)----------*/
				else if(checkChoice == 1) {
					warning(13, 30, "◀숫자외의문자를입력하셨습니다", "                                ");
					strcpy(modifySubject,"");
				}

				/*----------(선택한 숫자가 수정 과목 선택지에 없는 경우)----------*/
				else if(checkChoice == 2) {
					warning(13, 30, "◀선택하신숫자는선택지에없습니다", "                                ");
					strcpy(modifySubject,"");
				}

				/*----------(그외 나머지의 경우)----------*/
				else {
					warning(13, 30, "◀숫자외의문자를입력하셨습니다", "                                ");
					strcpy(modifySubject,"");
				}

			}

			/*----------(modifySubject 배열 크기 이상으로 입력할 경우)----------*/
			else {
				warning(13, 30, "◀입력이 잘못되었습니다", "                                ");
				strcpy(modifySubject,"");
			}

		}


		/*----------수정할 과목 (원래) 정보 출력----------*/
		listBorderDraw(3,12);
		gotoxyPrint(5, 33, "                                               ");
		gotoxyPrint(6, 14, "＊＊＊＊＊＊＊＊＊＊＊현재＊＊＊＊＊＊＊＊＊＊＊");
		gotoxy(9, 16);
		printf("요  일 : %s",subjectPointer[OrderOfSubject[intModifySubjectNum]-1].dayOfWeek);
		gotoxy(9, 18);
		printf("과목명 : %s",subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectName);
		gotoxy(9, 20);
		printf("교  시 : %s",subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectClass);


		/*----------수정과목정보 틀 출력----------*/
		gotoxyPrint(6, 23, "＊＊＊＊＊＊＊＊＊＊＊수정＊＊＊＊＊＊＊＊＊＊＊");
		gotoxyPrint(9, 25, "요  일 :");
		gotoxyPrint(9, 27, "과목명 :");
		gotoxyPrint(9, 29, "교  시 :");

		gotoxyPrint(3, 34, "▩ 과목요일예시: '월' 또는 '월요일'");
		gotoxyPrint(3, 35, "▩ 과목명은 빈칸없이 5자이내 입니다");
		gotoxyPrint(3, 36, "▩ 과목교시는 숫자와 ','이외의 문자는 입력되지 않습니다");
		gotoxyPrint(3, 37, "▩ 과목교시예시: '1,2,3' ");


		strcpy(modifyDay,"");


		/*-----------과목요일체크  while문----------*/
		while (1) {

			fflush(stdin);
			gotoxy(18, 25);
			fgets(modifyDay,8, stdin);

			/*----------(modifyDay 배열 크기이하로 입력할 경우)----------*/
			if( (endPointer = strchr(modifyDay, '\n')) != NULL ) {
				*endPointer = '\0';

				checkDay = checkModifyDay(modifyDay);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((modifyDay[0] == 'b'|| modifyDay[0] == 'B' )&& modifyDay[1] == '\0' ) {
					gotoxyPrint(3, 34, "                                    ");
					gotoxyPrint(3, 35, "                                    ");
					gotoxyPrint(3, 36, "                                                      ");
					gotoxyPrint(3, 37, "                                    ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((modifyDay[0] == 'x'|| modifyDay[0] == 'X' )&& modifyDay[1] == '\0' )  exit(0);

				/*----------(요일을 입력하지 않은 경우)----------*/
				else if(checkDay == 0){
					warning(18, 25,"◀수정할요일을입력해주세요","                          ");
					fflush(stdin);
					strcpy(modifyDay,"");
				}

				/*----------(요일을 두개이상 입력한 경우)----------*/
				else if (checkDay == 2) {
					warning(18, 25,"◀요일을하나만입력해주세요","                          ");
					fflush(stdin);
					strcpy(modifyDay,"");

				}


				/*----------(요일을 한개 입력한 경우)----------*/
				else {

					for(subjectCnt =0; subjectCnt<5; subjectCnt++) {
						if(strstr(modifyDay, dayOfWeek[subjectCnt]) ) {
							strcpy(tmpSubject.dayOfWeek, dayOfWeek[subjectCnt]);
							break;
						}

					}

					break;

				}


			}

			/*----------(modifyDay 배열 크기 이상으로 입력할 경우)----------*/
			else {
				warning(18, 25,"◀입력이잘못되었습니다","                          ");
				fflush(stdin);
				strcpy(modifyDay,"");
			}

		}



		/*----------수정과목명 체크----------*/
		while(1) {

			fflush(stdin);
			gotoxy(18, 27);
			fgets(tmpSubject.subjectName, 11, stdin);

			/*----------(키 입력이 5자(한글기준) 이내인 경우)----------*/
			if( (endPointer=strchr(tmpSubject.subjectName, '\n')) != NULL ) {
				*endPointer= '\0';

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((tmpSubject.subjectName[0] == 'b'|| tmpSubject.subjectName[0] == 'B' )&& tmpSubject.subjectName[1] == '\0' ) {
					gotoxyPrint(3, 34, "                                    ");
					gotoxyPrint(3, 35, "                                    ");
					gotoxyPrint(3, 36, "                                                      ");
					gotoxyPrint(3, 37, "                                    ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((tmpSubject.subjectName[0] == 'x'|| tmpSubject.subjectName[0] == 'X' )&& tmpSubject.subjectName[1] == '\0' )  exit(0);


				/*----------(과목명을 입력하지 않은 경우)----------*/
				else if(tmpSubject.subjectName[0] == '\0'){
					strcpy(tmpSubject.subjectName,"");
					warning(18, 27,"◀과목명을미입력했습니다.","                          ");
				}


				/*----------(과목명에 빈칸이 있는 경우)----------*/
				else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
					strcpy(tmpSubject.subjectName,"");
					warning(18, 27,"◀과목명에빈칸이있습니다.","                          ");
				}

				/*----------(과목명 조건에 만족하는 경우)----------*/
				else {
					break;
				}
			}

			/*----------(키 입력이 5자 이상인 경우)----------*/
			else {
				strcpy(tmpSubject.subjectName,"");
				warning(18, 27,"◀과목명5자를초과했습니다.","                          ");
			}

			if(!strstr(tmpSubject.dayOfWeek,""))
				break;

		}




		/*----------수정과목교시 체크 while문----------*/
		while(1) {

			fflush(stdin);
			gotoxy(18, 29);
			fgets(tmpSubject.subjectClass,sizeof(tmpSubject.subjectClass), stdin);

			/*----------(키 입력이 10자 이내인 경우)----------*/
			if( (endPointer=strchr(tmpSubject.subjectClass, '\n')) != NULL ) {
				*endPointer = '\0';

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((tmpSubject.subjectClass[0] == 'b'|| tmpSubject.subjectClass[0] == 'B' )&& tmpSubject.subjectClass[1] == '\0' ) {
					gotoxyPrint(3, 34, "                                    ");
					gotoxyPrint(3, 35, "                                    ");
					gotoxyPrint(3, 36, "                                                      ");
					gotoxyPrint(3, 37, "                                    ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((tmpSubject.subjectClass[0] == 'x'|| tmpSubject.subjectClass[0] == 'X' )&& tmpSubject.subjectClass[1] == '\0' )  exit(0);

				/*----------(숫자와','이외의 문자가 들어올 경우)----------*/
				else if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
					warning(18, 29,"◀','와숫자이외의문자입니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(교시를 입력하지 않고 Enter를 쳤을 경우)----------*/
				else if(tmpSubject.subjectClass[0] == '\0') {
					warning(18, 29,"◀교시를미입력했습니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(교시를 중복되게 쳤을 경우)----------*/
				else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
					
					//수정 전의 과목교시와 겹치는 경우
					if(checkOverlappingInClass(&subjectPointer[OrderOfSubject[intModifySubjectNum]-1],tmpSubject,1) == 0) {
						break;
					}

					//다른 과목교시와 겹치는 경우
					else {
						warning(18, 29,"◀교시가중복됩니다", "                          ");
						strcpy(tmpSubject.subjectClass,"");
					}

				}

				/*----------(1~13교시 이외의 교시를 입력 했을 경우)----------*/
				else if(checkNumInClass(tmpSubject.subjectClass) == 0){
					warning(18, 29,"◀1~13이외교시입니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(교시 입력이 올바를 경우)----------*/
				else 
					break;


			}
			/*----------(키 입력이 10자 이상인 경우)----------*/
			else{
				warning(18, 29,"◀교시글자수초과했습니다", "                          ");
				strcpy(tmpSubject.subjectClass,"");
			}
		}

		/*----------(수정한(재입력한) 과목요일, 과목명, 과목교시 시간표에 저장)----------*/
		strcpy(subjectPointer[OrderOfSubject[intModifySubjectNum]-1].dayOfWeek, tmpSubject.dayOfWeek);
		strcpy(subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectName, tmpSubject.subjectName);
		strcpy(subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectClass, tmpSubject.subjectClass);
		sortTimetable(subjectPointer,subjectTotalNum,s);

		free(subjectPointer);

		/*----------(화면에서 조건 글자 지우기)----------*/
		gotoxyPrint(3, 34, "                                    ");
		gotoxyPrint(3, 35, "                                    ");
		gotoxyPrint(3, 36, "                                                      ");
		gotoxyPrint(3, 37, "                                    ");

	}

}


//●시간표 과목 추가
void addSubject(structMember *s) {

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	FILE *fp;
	char fileName[30];
	structSubject* subjectPointer;
	structSubject tmpSubject;
	int subjectTotalNum;
	int i;
	char addDay[15];
	char *endP;
	int checkDay;


	fflush(stdin);
	listBorderDraw(3,12);


	/*----------사용자의 시간표 텍스트 파일 오픈----------*/
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	/*----------(사용자의 시간표 텍스트 파일이 없는 경우)----------*/
	if(fp == NULL ) {
		gotoxyPrint(8, 20, "●시간표가 없습니다. 시간표를 만들어주세요●");
		Sleep(1500);
		return;
	}

	/*----------(사용자의 시간표 텍스트 파일이 있는 경우)----------*/
	else {

		/*----------사용자의 시간표 텍스트 파일에 저장된 시간표 읽기----------*/
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*(subjectTotalNum+1));

		for(i=0;i<subjectTotalNum;i++) 
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		fclose(fp);


		/*----------과목 추가 틀 출력----------*/
		gotoxyPrint(9, 19,"요  일 :");
		gotoxyPrint(9, 21, "과목명 :");
		gotoxyPrint(9, 23, "교  시 :");
		gotoxyPrint(3, 34, "▩ 과목요일예시: '월' 또는 '월요일' ");
		gotoxyPrint(3, 35, "▩ 과목명은 빈칸없이 5자이내 입니다");
		gotoxyPrint(3, 36, "▩ 과목교시는 숫자와 ','이외의 문자는 입력되지 않습니다");
		gotoxyPrint(3, 37, "▩ 과목교시예시: '1,2,3' ");


		fflush(stdin);

		/*----------추가요일체크 while문----------*/
		while (1) {

			fflush(stdin);
			gotoxy(18, 19);
			fgets(addDay,8, stdin);

			/*----------(addDay 배열 크기이하로 입력할 경우)----------*/
			if( (endP = strchr(addDay, '\n')) != NULL ) {
				*endP = '\0';

				checkDay = checkModifyDay(addDay);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((addDay[0] == 'b'|| addDay[0] == 'B' )&& addDay[1] == '\0' ){
					gotoxyPrint(3, 34, "                                       ");
					gotoxyPrint(3, 35, "                                       ");
					gotoxyPrint(3, 36, "                                                      ");
					gotoxyPrint(3, 37, "                         ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((addDay[0] == 'x'|| addDay[0] == 'X' )&& addDay[1] == '\0' )  exit(0);


				/*----------(요일을 입력하지 않은 경우)----------*/
				else if(checkDay == 0){
					warning(18, 19,"◀추가할요일을입력해주세요", "                          ");
					fflush(stdin);
					strcpy(addDay,"");
				}

				/*----------(요일을 두개이상 입력한 경우)----------*/
				else if (checkDay == 2) {
					warning(18, 19,"◀요일을하나만입력해주세요", "                          ");
					fflush(stdin);
					strcpy(addDay,"");

				}


				/*----------(요일을 한개 입력한 경우)----------*/
				else {

					//구조체에 요일 저장
					for(i =0; i<5; i++) {
						if(strstr(addDay, dayOfWeek[i]) ) {

							strcpy(tmpSubject.dayOfWeek, dayOfWeek[i]);
							break;

						}
					}
					break;
				}

			}

			/*----------(addDay 배열 크기 이상으로 입력할 경우)----------*/
			else {
				warning(18, 19,"◀입력이잘못되었습니다", "                          ");
				fflush(stdin);
				strcpy(addDay,"");

			}
		} 



		/*----------추가과목명 체크----------*/
		while(1) {

			fflush(stdin);
			gotoxy(18, 21);
			fgets(tmpSubject.subjectName, 11, stdin);

			/*----------(키 입력이 5자(한글기준) 이내인 경우)----------*/
			if( (endP=strchr(tmpSubject.subjectName, '\n')) != NULL ) {
				*endP = '\0';

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((tmpSubject.subjectName[0] == 'b'|| tmpSubject.subjectName[0] == 'B' )&& tmpSubject.subjectName[1] == '\0' ){

					gotoxyPrint(3, 34, "                                       ");
					gotoxyPrint(3, 35, "                                       ");
					gotoxyPrint(3, 36, "                                                      ");
					gotoxyPrint(3, 37, "                         ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((tmpSubject.subjectName[0] == 'x'|| tmpSubject.subjectName[0] == 'X' )&& tmpSubject.subjectName[1] == '\0' )  exit(0);


				/*----------(과목명을 입력하지 않은 경우)----------*/
				else if(tmpSubject.subjectName[0] == '\0'){
					strcpy(tmpSubject.subjectName,"");
					warning(18, 21, "◀과목명을미입력했습니다.", "                          ");
				}


				/*----------(과목명에 빈칸이 있는 경우)----------*/
				else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
					strcpy(tmpSubject.subjectName,"");
					warning(18, 21, "◀과목명에빈칸이있습니다.", "                          ");

				}

				/*----------(과목명 조건에 만족하는 경우)----------*/
				else {
					break;
				}
			}

			/*----------(키 입력이 5자 이상인 경우)----------*/
			else {
				strcpy(tmpSubject.subjectName,"");
				warning(18, 21, "◀과목명5자를초과했습니다.", "                          ");
			}

		}


		/*----------추가과목교시 체크 while문----------*/
		while(1) {

			fflush(stdin);
			gotoxy(18, 23);
			fgets(tmpSubject.subjectClass,sizeof(tmpSubject.subjectClass), stdin);

			/*----------(키 입력이 10자 이내인 경우)----------*/
			if( (endP=strchr(tmpSubject.subjectClass, '\n')) != NULL ) {
				*endP = '\0';

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((tmpSubject.subjectClass[0] == 'b'|| tmpSubject.subjectClass[0] == 'B' )&& tmpSubject.subjectClass[1] == '\0' ){
					gotoxyPrint(3, 34, "                                       ");
					gotoxyPrint(3, 35, "                                       ");
					gotoxyPrint(3, 36, "                                                      ");
					gotoxyPrint(3, 37, "                         ");
					return;

				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((tmpSubject.subjectClass[0] == 'x'|| tmpSubject.subjectClass[0] == 'X' )&& tmpSubject.subjectClass[1] == '\0' )  exit(0);

				/*----------(숫자와','이외의 문자가 들어올 경우)----------*/
				else if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
					warning(18, 29,"◀','와숫자이외의문자입니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(교시를 입력하지 않고 Enter를 쳤을 경우)----------*/
				else if(tmpSubject.subjectClass[0] == '\0') {
					warning(18, 29,"◀교시를미입력했습니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(교시를 중복되게 쳤을 경우)----------*/
				else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
					warning(18, 23,"◀교시가중복됩니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(1~13교시 이외의 교시를 입력 했을 경우)----------*/
				else if(checkNumInClass(tmpSubject.subjectClass) == 0){
					warning(18, 23,"◀1~13이외교시입니다", "                          ");
					strcpy(tmpSubject.subjectClass,"");
				}

				/*----------(교시 입력이 올바를 경우)----------*/
				else 
					break;



			}
			/*----------(키 입력이 10자 이상인 경우)----------*/
			else{
				warning(18, 29,"◀교시글자수초과했습니다", "                          ");
				strcpy(tmpSubject.subjectClass,"");
			}
		}


		/*----------(수정한(재입력한) 과목요일, 과목명, 과목교시 시간표에 저장)----------*/
		strcpy(subjectPointer[subjectTotalNum].dayOfWeek, tmpSubject.dayOfWeek);
		strcpy(subjectPointer[subjectTotalNum].subjectName, tmpSubject.subjectName);
		strcpy(subjectPointer[subjectTotalNum].subjectClass, tmpSubject.subjectClass);

		sortTimetable(subjectPointer,subjectTotalNum+1,s);


		free(subjectPointer);
	}

	/*----------(화면에서 조건 글자 지우기)----------*/
	gotoxyPrint(3, 34, "                                       ");
	gotoxyPrint(3, 35, "                                       ");
	gotoxyPrint(3, 36, "                                                      ");
	gotoxyPrint(3, 37, "                         ");

}


//●과목삭제
void removeSubject(structMember *s) {

	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	FILE *fp;
	structSubject* subjectPointer;
	char fileName[30];
	int subjectTotalNum;
	char removeDay[15]; 
	int OrderOfSubject[5] ={0};
	int subjectCntOfModifyDay=0;
	int nResult;
	int i,j=0,k=0;
	char *endP;
	int checkDay;
	int day;
	int checkChoice;
	char removeSubject[5];
	int intRemoveSubjectNum;


	fflush(stdin);
	listBorderDraw(3,12);


	//txt파일에 저장된 시간표 읽어오기
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	//timetable.txt가 없는 경우
	if(fp == NULL ) {
		gotoxyPrint(8, 20, "●시간표가 없습니다. 시간표를 만들어주세요.●");
		Sleep(1500);

	}

	/*----------(사용자의 시간표 텍스트 파일이 있는 경우)----------*/
	else {

		/*----------사용자의 시간표 텍스트 파일에 저장된 시간표 읽기----------*/
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalNum);
		for(i=0;i<subjectTotalNum;i++) {
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		}
		fclose(fp);


		gotoxyPrint(20, 14, "- 시간표 과목삭제 -");
		gotoxyPrint(5, 33, "▩ 삭제할 과목의 요일예시: '월' 또는 '월요일' ");
		gotoxyPrint(7, 16, "삭제할 과목의 요일 : ");


		/*----------삭제할 과목의 요일 입력----------*/
		while(1) {
			fflush(stdin);
			gotoxy(28, 16);
			fgets(removeDay,8, stdin);

			/*----------(removeDay 배열 크기이하로 입력할 경우)----------*/
			if( (endP = strchr(removeDay, '\n')) != NULL ) {
				*endP = '\0';

				checkDay = checkModifyDay(removeDay);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((removeDay[0] == 'b'|| removeDay[0] == 'B' )&& removeDay[1] == '\0' ){
					gotoxyPrint(5, 33, "                                              ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((removeDay[0] == 'x'|| removeDay[0] == 'X' )&& removeDay[1] == '\0' )  exit(0);


				/*----------(입력이 있지만 요일(월~금)을 입력하지 않은 경우)----------*/
				else if(checkDay == 0){
					warning(28, 16,"◀삭제할요일을입력해주세요","                          ");
					fflush(stdin);
					strcpy(removeDay,"");
				}

				/*----------(요일을 두개이상 입력한 경우)----------*/
				else if (checkDay == 2) {
					warning(28, 16,"◀요일을하나만입력해주세요","                          ");
					fflush(stdin);
					strcpy(removeDay,"");

				}

				/*----------(요일을 한개 입력한 경우)----------*/
				else {

					/*----------수정할 해당 요일 과목출력 ----------*/
					for(day=0; day<5; day++) {

						// 무슨 요일인지 체크
						if (strstr(removeDay, dayOfWeek[day])) { 
							if(strstr(removeDay,"요일") || (strcmp(removeDay,dayOfWeek[day]) == 0 )) {

								// 사용자 시간표에서 사용자가 입력한 요일 찾기
								for(i=0; i<subjectTotalNum; i++) {

									// 해당 요일 과목출력
									if( strstr(dayOfWeek[day], subjectPointer[i].dayOfWeek) ) { 

										OrderOfSubject[subjectCntOfModifyDay] = i+1; //시간표 몇번째에 과목이 있는지 저장
										gotoxy(15, 19 + subjectCntOfModifyDay * 2 );
										printf("%d) %s %s %s교시", subjectCntOfModifyDay+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
										subjectCntOfModifyDay++;
									}
								}

								//수정할 요일에 과목이 없는 경우
								if(OrderOfSubject[0] == 0) {
									gotoxyPrint(13, 22, "●해당 요일에 과목이 없습니다.●");
									Sleep(1000);
									gotoxyPrint(13, 22, "                                 ");
									gotoxyPrint(13, 16, "               ");
									strcpy(removeDay,"");
									break;
								}
							}


						}

					}
					//수정할 과목을 선택했을 경우
					if(OrderOfSubject[0] != 0) {
						break;
					}
				}
			}


			/*----------(modify 배열 크기 이상으로 입력할 경우)----------*/
			else {
				warning(28, 16,"◀요일입력을잘못했습니다","                          ");
				strstr(removeDay,"");
				fflush(stdin);
			}

		}

		fflush(stdin);
		gotoxyPrint(10, 29, "삭제할 과목의 해당 숫자를 입력해주세요");
		gotoxyPrint(10, 30, " >> ");


		/*----------수정할 과목의 요일에서 과목 선택하는 while문----------*/
		while(1) {
			fflush(stdin);
			gotoxy(13,30);
			fgets(removeSubject, sizeof(removeSubject), stdin);

			/*----------(removeSubject 배열 크기이하로 입력할 경우)----------*/
			if( (endP = strchr(removeSubject, '\n')) != NULL ) {
				*endP = '\0';

				checkChoice = checkChoiceOfSubject(removeSubject, subjectCntOfModifyDay);

				/*----------('b'또는 'B'를 입력한 경우 ->뒤로가기)----------*/
				if((removeSubject[0] == 'b'|| removeSubject[0] == 'B' )&& removeSubject[1] == '\0' ){
					gotoxyPrint(5, 33, "                                              ");
					return;
				}

				/*----------('x'또는 'X'를 입력한 경우 ->프로그램 종료하기)----------*/
				else if((removeSubject[0] == 'x'|| removeSubject[0] == 'X' )&& removeSubject[1] == '\0' )  exit(0);

				/*----------(수정한 요일을 정상적으로 입력했을 경우)----------*/
				else if( checkChoice == 0) {
					intRemoveSubjectNum = atoi(&removeSubject[0])-1;

					for(i=OrderOfSubject[intRemoveSubjectNum];i<subjectTotalNum;i++) {
						strcpy(subjectPointer[i-1].dayOfWeek, subjectPointer[i].dayOfWeek);
						strcpy(subjectPointer[i-1].subjectName, subjectPointer[i].subjectName);
						strcpy(subjectPointer[i-1].subjectClass, subjectPointer[i].subjectClass);
					}
					break;
				}


				/*----------(숫자외의문자를입력한 경우)----------*/
				else if(checkChoice == 1) {
					warning(13, 30, "◀숫자외의문자를입력하셨습니다", "                                ");
					strcpy(removeSubject,"");
				}

				/*----------(선택한 숫자가 메뉴에 없는 경우)----------*/
				else if(checkChoice == 2) {
					warning(13, 30, "◀선택하신숫자는선택지에없습니다", "                                ");
					strcpy(removeSubject,"");
				}

				/*----------(입력을 하지 않고 Enter를 누른 경우)----------*/
				else if(removeSubject[0] == '\0') {
					warning(13, 30, "◀삭제할과목을선택해주세요", "                                ");
					strcpy(removeSubject,"");
				}

				/*----------(그외 나머지 경우)----------*/
				else {
					warning(13, 30, "◀숫자외의문자를입력하셨습니다", "                                ");
					strcpy(removeSubject,"");
				}
			}

			/*----------(removeSubject 배열 크기 이상으로 입력할 경우)----------*/
			else {
				warning(13, 30, "◀입력이 잘못되었습니다", "                                ");
				strcpy(removeSubject,"");
			}


		}

		/*----------(과목을 삭제한 다음 과목 개수가 0개가 되는 경우)----------*/
		if(subjectTotalNum-1 == 0 ) {
			nResult = remove(fileName);

			//시간표가 정상적으로 삭제된 경우
			if(nResult == 0) {
				gotoxyPrint(8, 28, "*시간표가 정상적으로 삭제되었습니다*");  //지우기 성공
				Sleep(1500);
				return;
			} 
			
			//시간표가 삭제되지 못한 경우
			else if (nResult == -1) {
				gotoxyPrint(20, 28, "*파일을 열지 못해, 삭제를 실패했습니다*"); //지우기 실패
			}

			Sleep(10000);
		}

		/*----------(과목을 삭제한 다음 삭제한 과목 개수가 0개가 아닌 경우)----------*/
		else
			saveTimetalbe(subjectPointer,subjectTotalNum-1,s);
	}

	gotoxyPrint(5, 33, "                                              ");
}


//●수정과목요일검사 함수
int checkModifyDay(char* modifyDay) {


	char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};
	int day;
	int dayCnt = 0;


	//입력문장에 요일개수 체크
	for(day = 0; day <5; day++ ){

		if(strstr(modifyDay, dayOfWeek[day])) 
			dayCnt++;

	}

	//수정요일을 입력하지 않은 경우
	if(dayCnt == 0) 
		return 0;

	//수정요일을 정상적으로 입력한 경우
	else if(dayCnt == 1)
		return 1;

	//수정요일이 두개입력 된 경우
	else 
		return 2;

}


//●수정과목 선택을 검사하는 함수
int checkChoiceOfSubject(char* modifySubject, int subjectCntOfModifyDay) {

	int i;
	int tmpModifySubject = atoi(modifySubject);


	//선택지내의 숫자를 입력한 경우
	if( tmpModifySubject > 0 && tmpModifySubject <= subjectCntOfModifyDay) {

		return 0;

	}

	//선택한 숫자가 메뉴에 없는 경우
	else{
		for(i= 0; modifySubject[i] != '\0'; i++) {

			if(modifySubject[i] >= '0' && modifySubject[i] < '9')
				return 2;

		}

	}

	 //숫자외의문자를 입력한 경우
	return 1;


}