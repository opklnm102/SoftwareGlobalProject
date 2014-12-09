#include"structHeader.h"
//���񰳼����޿���
void makeTimetable(structMember *s) {

	int SubjectNumOfoneday[5]={0}, subjectTotalNum=0;

	InputSubjectNum(SubjectNumOfoneday,&subjectTotalNum, s);
	InputSubjectNameAndClass(SubjectNumOfoneday,subjectTotalNum, s);
}


//�� �ð�ǥ ��~�� ���񰹼� �Է� �Լ�
void InputSubjectNum(int* SubjectNumOfoneday, int* subjectTotalNum, structMember *s) {

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	char tmpSubjectNum[3];
	char *endP;
	int i;


	screenBorderDraw() ;
	listBorderDraw(3,12);
	fflush(stdin);

	/*----------���� ���� ���ѹ� ���----------*/
	gotoxyPrint(6, 29,"�� �Ϸ� �ִ���� ������ 5�� �����Դϴ�.");
	gotoxyPrint(6, 30,"�� �� �ִ���� ������ 13�� �����Դϴ�.");

	/*----------���� ���� ���� ���� �Է¹޴� while��----------*/
	while (1) {

		/*----------���� ���� �Է¹޴� Ʋ ���----------*/
		gotoxyPrint(20, 15,"- �ð�ǥ ����� -");

		for(i=0;i<5;i++){
			gotoxy(7, 18+i*2);
			printf(" %s���� ���� ���� : ", dayOfWeek[i]);
		}

		/*----------���� ���� ���� ���� �Է� �ޱ�----------*/
		for(i=0;i<5;i++){

			fflush(stdin);

			//���Ϻ��� ���� ���� �Է�
			gotoxy(27,18+i*2);
			fgets(tmpSubjectNum,sizeof(tmpSubjectNum), stdin);
			if( (endP=strchr(tmpSubjectNum, '\n')) != NULL ) {
				*endP = '\0';

				/*----------(Ű �Է��� �� ������ ���)----------*/

				//�Ϸ���񰳼��� 5�̻� 9������ ��� (���ڸ� ����)
				if(tmpSubjectNum[0] > '5' && tmpSubjectNum[0] <= '9') {
					warningSubjectNumOfOneday(i,"���Ϸ��ִ���񰳼�(5��)�ʰ�");
					i--;
				}

				//�Է°��� ������ ���
				else if((tmpSubjectNum[0] < '0' || tmpSubjectNum[0] > '9') && tmpSubjectNum[0] != '\0') {
					warningSubjectNumOfOneday(i,"�����ڸ� �Է����ּ���");
					i--;
				}

				//�Է� ���� Enter�� ���� ���
				else if(tmpSubjectNum[0] == '\0') {
					warningSubjectNumOfOneday(i,"�����񰳼��� �Է����ּ���");
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
					warningSubjectNumOfOneday(i,"������� �Է����ּ���");
					i--;
				}
				//���ڸ��̻��� ���ڸ� �Է��� ���
				else if((tmpSubjectNum[0] > '0' && tmpSubjectNum[0] <= '9') ) {


					if(tmpSubjectNum[1] < '0' || tmpSubjectNum[1] > '9') {
						warningSubjectNumOfOneday(i,"�����ڸ� �Է����ּ���");
						i--;
					}
					else {
						warningSubjectNumOfOneday(i,"���Ϸ��ִ���񰳼�(5��)�ʰ�");
						i--;
					}



				}
				//���ڰ� �Էµ� ���
				else if((tmpSubjectNum[0] < '0' || tmpSubjectNum[0] > '9' )) {

					warningSubjectNumOfOneday(i,"�����ڸ� �Է����ּ���");
					i--;
				}
				//�׿� �������� ���
				else {
					warningSubjectNumOfOneday(i,"���Է��� �߸��Ǿ����ϴ�.");
					i--;
				}

			}

		}

		/*----------(�ð�ǥ�� �� ���񰳼��� �ʰ��� ���)----------*/
		if(*subjectTotalNum > 13 ){

			// ��ũ���� �Է��� �����͸� ����� ��� ��� �� while���� �ٽ� �ݺ�
			for(i=0;i<5;i++)
				gotoxyPrint(27, 18+i*2, "    ");
			
			gotoxyPrint(12, 28, " �� �� �ִ� �����(13��)�� �ʰ�. ��\n");
			Sleep(1000);
			gotoxyPrint(8, 28, "                                              ");
			*subjectTotalNum =0;
		}

		/*----------(�ð�ǥ�� �� ���񰳼��� �ʰ����� �ʴ� ���)----------*/
		else {

			//while�� ����
			break;
		}
	}
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
	gotoxyPrint(60, 12+frameCourY, "�� ������� ��ĭ���� 5���̳� �Դϴ�.");
	gotoxyPrint(60, 13+frameCourY, "�� ���񱳽ô� 1,2,3 ���� �Է� ���ּ���.");
	gotoxyPrint(60, 14+frameCourY, "�� ���񱳽ô� ���ڿ� ','�̿��� ���ڴ� �Էµ��� �ʽ��ϴ�.");

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
						warningSubjectName(inputCurY,"������������Է��߽��ϴ�.");
					}

					//����� ��ĭ�� �ִ� ���
					else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
						strcpy(tmpSubject.subjectName,"");
						warningSubjectName(inputCurY,"���������ĭ���ֽ��ϴ�.");

					}

					//����� ���ǿ� �����ϴ� ���
					else {
						break;
					}
				}

				/*----------(Ű �Է��� 5�� �̻��� ���)----------*/
				else {
					strcpy(tmpSubject.subjectName,"");
					warningSubjectName(inputCurY,"�������5�ڸ��ʰ��߽��ϴ�.");
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

				//���ڿ�','�̿��� ���ڰ� ���ö�
				if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
					warningSubjectClass( inputCurY,"��','�ͼ����̿��ǹ���");
					strcpy(tmpSubject.subjectClass,"");
				}

				//���ø� �Է����� �ʰ� Enter�� ������
				else if(tmpSubject.subjectClass[0] == '\0') {
					warningSubjectClass( inputCurY,"�����ø����Է��߽��ϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}

				//���ø� �ߺ��ǰ� ������
				else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
					warningSubjectClass( inputCurY,"�����ð��ߺ��˴ϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}

				//1~13���� �̿��� ���ø� �Է� ������
				else if(checkNumInClass(tmpSubject.subjectClass) == 0){
					warningSubjectClass( inputCurY,"��1~13�ܱ̿����Դϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}
				//�Է��� �ùٸ� ��
				else 
					break;



			}
			/*----------(Ű �Է��� 10�� �̻��� ���)----------*/
			else{
				warningSubjectClass(inputCurY,"�����ñ��ڼ��ʰ��߽��ϴ�");
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

void warningSubjectNumOfOneday(int y, char* warning) {


	gotoxyPrint(27, 18+y*2, warning);
	Sleep(1000);
	gotoxyPrint(27, 18+y*2, "                           ");

}

void warningSubjectName(int y, char* warning) {


	gotoxyPrint(72,y, warning);
	Sleep(1500);
	gotoxyPrint(72,y, "                          ");

}

void warningSubjectClass(int y, char* warning) {


	gotoxyPrint(104,y, warning);
	Sleep(1000);
	gotoxyPrint(104,y, "                       ");

}
