#include"structHeader.h"

//�� �ð�ǥ ����� �Լ�
void makeTimetable(structMember *s) {

	int SubjectNumOfoneday[5]={0}, subjectTotalNum=0;

	if(InputSubjectNum(SubjectNumOfoneday,&subjectTotalNum, s) == 1) 
		InputSubjectNameAndClass(SubjectNumOfoneday,subjectTotalNum, s);
}


//�� �ð�ǥ ��~�� ���񰹼� �Է� �Լ�
int InputSubjectNum(int* SubjectNumOfoneday, int* subjectTotalNum, structMember *s) {

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	char tmpSubjectNum[3];
	char *endP;
	int i;


	screenBorderDraw() ;
	listBorderDraw(3,12);
	fflush(stdin);

	/*----------���� ���� ���ѹ� ���----------*/
	gotoxyPrint(6, 34,"�� �Ϸ� �ִ���� ������ 5�� �����Դϴ�");
	gotoxyPrint(6, 35,"�� �� �ִ���� ������ 13�� �����Դϴ�");

	/*----------���� ���� ���� ���� �Է¹޴� while��----------*/
	while (1) {

		/*----------���� ���� �Է¹޴� Ʋ ���----------*/
		gotoxyPrint(20, 15,"- �ð�ǥ ����� -");

		for(i=0;i<5;i++){
			gotoxy(7, 19+i*2);
			printf(" %s���� ���� ���� : ", dayOfWeek[i]);
		}

		/*----------���� ���� ���� ���� �Է� �ޱ�----------*/
		for(i=0;i<5;i++){

			fflush(stdin);

			//���Ϻ��� ���� ���� �Է�
			gotoxy(27,19+i*2);
			fgets(tmpSubjectNum,sizeof(tmpSubjectNum), stdin);
			if( (endP=strchr(tmpSubjectNum, '\n')) != NULL ) {
				*endP = '\0';

				/*----------(Ű �Է��� �� ������ ���)----------*/

				//�Ϸ���񰳼��� 5�̻� 9������ ��� (���ڸ� ����)
				if(tmpSubjectNum[0] > '5' && tmpSubjectNum[0] <= '9') {
					warning(27,19+i*2,"���Ϸ��ִ���񰳼�(5��)�ʰ�","                           ");
					i--;
				}

				//�Է°��� ������ ���
				else if((tmpSubjectNum[0] == 'b'|| tmpSubjectNum[0] == 'B' )&& tmpSubjectNum[1] == '\0' ){

					gotoxyPrint(6, 34,"                                      ");
					gotoxyPrint(6, 35,"                                       ");
					return 0;
				}

				else if((tmpSubjectNum[0] == 'x'|| tmpSubjectNum[0] == 'X' )&& tmpSubjectNum[1] == '\0' )exit(0);

				//�Է°��� ������ ���
				else if((tmpSubjectNum[0] < '0' || tmpSubjectNum[0] > '9') && tmpSubjectNum[0] != '\0') {
					warning(27,19+i*2,"�����ڸ� �Է����ּ���","                           ");
					i--;
				}

				//�Է� ���� Enter�� ���� ���
				else if(tmpSubjectNum[0] == '\0') {
					warning(27,19+i*2,"�����񰳼��� �Է����ּ���","                           ");
					i--;
				}
				//���� ���� �Է��� �ùٸ� ���
				else {
					SubjectNumOfoneday[i] = tmpSubjectNum[0] - '0';
					*subjectTotalNum += SubjectNumOfoneday[i];
				}
			}

			/*----------(Ű �Է��� �� ���� �̻��� ���)----------*/
			else{

				//���񰳼��� ������ �Է��� ���
				if(tmpSubjectNum[0] == '-') {
					warning(27,19+i*2,"������� �Է����ּ���","                           ");
					i--;
				}
				//���ڸ��̻��� ���ڸ� �Է��� ���
				else if((tmpSubjectNum[0] > '0' && tmpSubjectNum[0] <= '9') ) {


					if(tmpSubjectNum[1] < '0' || tmpSubjectNum[1] > '9') {
						warning(27,19+i*2,"�����ڸ� �Է����ּ���","                           ");
						i--;
					}
					else {
						warning(27,19+i*2,"���Ϸ��ִ���񰳼�(5��)�ʰ�","                           ");
						i--;
					}



				}
				//���ڰ� �Էµ� ���
				else if((tmpSubjectNum[0] < '0' || tmpSubjectNum[0] > '9' )) {
					warning(27,19+i*2,"�����ڸ� �Է����ּ���","                           ");
					i--;
				}
				//�׿� �������� ���
				else {
					warning(27,19+i*2,"���Է��� �߸��Ǿ����ϴ�.","                           ");
					i--;
				}

			}

		}

		/*----------(�ð�ǥ�� �� ���񰳼��� �ʰ��� ���)----------*/
		if(*subjectTotalNum > 13 ){

			// ��ũ���� �Է��� �����͸� ����� ��� ��� �� while���� �ٽ� �ݺ�
			for(i=0;i<5;i++)
				gotoxyPrint(27, 19+i*2, "    ");

			gotoxyPrint(12, 29, " �� �� �ִ� �����(13��)�� �ʰ�. ��\n");
			Sleep(1000);
			gotoxyPrint(8, 29, "                                              ");
			*subjectTotalNum =0;
		}

		/*----------(�ð�ǥ�� �� ���񰳼��� �ʰ����� �ʴ� ���)----------*/
		else {
			//while�� ����
			break;
		}
	}

	return 1;
}

//�� �����/���� �Է��Լ�
void InputSubjectNameAndClass(int* SubjectNumOfoneday, int subjectTotalNum, structMember *s) {

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	structSubject* subjectPointer;
	structSubject tmpSubject;
	char *endPointer;
	int StartCourYOfSubject=12;
	int frameCourY=0, inputCurY=0;
	int subjectCnt=0;
	int i, j;

	/*----------���� �� ������ŭ �����Ҵ�----------*/
	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalNum);

	/*----------���Ϻ� ���� �̸�/���� �Է� Ʋ ���----------*/
	for( i = 0; i < 5; i++){

		/*----------(���� ���� ���� ������ 0���� �ƴ� ���)----------*/
		if( SubjectNumOfoneday[i] != 0 ) {
			frameCourY++;
			gotoxy(59,10+frameCourY);
			printf("����������������������������- %s���� -������������������������������\n", dayOfWeek[i]);

			//�ش� ������ �Ϸ�� ���� ������ŭ �����/���� Ʋ ���
			for(j=0; j <SubjectNumOfoneday[i] ; j++){
				strcpy(subjectPointer[subjectCnt++].dayOfWeek,dayOfWeek[i]);
				frameCourY++;
				gotoxy(60,10+frameCourY);
				printf(" %d. ����� :                          ���� :       \n",j+1);
			}
			frameCourY++;
			gotoxyPrint(60,10+frameCourY, "\n");
		}
	}

	/*----------�����/���� �Է� ���ѹ� ���----------*/
	gotoxyPrint(60, 12+frameCourY, "�� ������� ��ĭ���� 5���̳� �Դϴ�");
	gotoxyPrint(60, 13+frameCourY, "�� ���񱳽ô� ���ڿ� ','�̿��� ���ڴ� �Էµ��� �ʽ��ϴ�");
	gotoxyPrint(60, 14+frameCourY, "�� ���񱳽ÿ���: '1,2,3' ");


	subjectCnt=0;
	fflush(stdin);

	/*----------�����/���� �Է�----------*/
	for( i = 0; i < 5; i++){

		strcpy(tmpSubject.dayOfWeek,dayOfWeek[i]);

		for(j=0; j <SubjectNumOfoneday[i] ; j++){

			/*----------����� �Է�----------*/
			inputCurY = j+StartCourYOfSubject;

			while(1) {

				fflush(stdin);
				gotoxy(73,inputCurY);
				fgets(tmpSubject.subjectName, 11, stdin);

				/*----------(Ű �Է��� 5��(�ѱ۱���) �̳��� ���)----------*/
				if( (endPointer=strchr(tmpSubject.subjectName, '\n')) != NULL ) {
					*endPointer = '\0';


					//�Է¾��� Enter�� ���� ���
					if(tmpSubject.subjectName[0] == '\0'){
						strcpy(tmpSubject.subjectName,"");
						warning(72, inputCurY, "������������Է��߽��ϴ�", "                          ");
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



					//����� ��ĭ�� �ִ� ���
					else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
						strcpy(tmpSubject.subjectName,"");
						warning(72, inputCurY, "���������ĭ���ֽ��ϴ�", "                          ");

					}

					//����� ���ǿ� �����ϴ� ���
					else {
						break;
					}
				}

				/*----------(Ű �Է��� 5�� �̻��� ���)----------*/
				else {
					strcpy(tmpSubject.subjectName,"");
					warning(72, inputCurY, "�������5�ڸ��ʰ��߽��ϴ�", "                          ");
				}

			}



			/*----------���񱳽� �Է�----------*/
			while(1) {

				//���񱳽� �Է�
				fflush(stdin);
				gotoxy(104,inputCurY);
				fgets(tmpSubject.subjectClass,sizeof(tmpSubject.subjectClass), stdin);

				/*----------(Ű �Է��� 10�� �̳��� ���)----------*/
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


					//���ڿ�','�̿��� ���ڰ� ���ö�
					else if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
						warning(104, inputCurY, "��','�ͼ����̿��ǹ���", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}

					//���ø� �Է����� �ʰ� Enter�� ������
					else if(tmpSubject.subjectClass[0] == '\0') {
						warning(104, inputCurY, "�����ø����Է��߽��ϴ�", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}

					//���ø� �ߺ��ǰ� ������
					else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
						warning(104, inputCurY, "�����ð��ߺ��˴ϴ�", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}

					//1~13���� �̿��� ���ø� �Է� ������
					else if(checkNumInClass(tmpSubject.subjectClass) == 0){
						warning(104, inputCurY, "��1~13�ܱ̿����Դϴ�", "                       ");
						strcpy(tmpSubject.subjectClass,"");
					}
					//�Է��� �ùٸ� ��
					else 
						break;



				}
				/*----------(Ű �Է��� 10�� �̻��� ���)----------*/
				else{
					warning(104, inputCurY, "�����ñ��ڼ��ʰ��߽��ϴ�", "                       ");
					strcpy(tmpSubject.subjectClass,"");
				}
			}

			/*----------�����/���� �Է��� �����Ҵ��� ������ ���� �� tmpSubject(����)  �ʱ�ȭ---------*/
			strcpy(subjectPointer[subjectCnt].subjectName,tmpSubject.subjectName);
			strcpy(subjectPointer[subjectCnt].subjectClass,tmpSubject.subjectClass);
			strcpy(tmpSubject.subjectName,"");
			strcpy(tmpSubject.subjectClass,"");


			/*----------���� ���� ���� y��ǥ ���---------*/
			if(j+1 == SubjectNumOfoneday[i]){
				StartCourYOfSubject = 3+inputCurY; 
			}

			//�����/�����Է��� �Ϸ�� �� ���� �����/�����Է��� ���� ī��Ʈ ����
			subjectCnt++;
		}
		printf("\n");
	}

	//�Էµ� �ð�ǥ������ txt���Ͽ� ����
	saveTimetalbe(subjectPointer,subjectTotalNum, s);

	free(subjectPointer);
	system("cls"); 


}


