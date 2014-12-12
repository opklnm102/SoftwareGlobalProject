#include"structHeader.h"

//�ܽð�ǥ �����޴�
void modifyMenu (structMember *s) {

	char choiceMenu[3];
	char *p;

	while(1) {
		
		listBorderDraw(3,12);
		timetableDraw(s);


		/*----------�ð�ǥ ���� �޴� ���----------*/
		gotoxyPrint(22, 15, "*�ð�ǥ �����޴�*");
		gotoxyPrint(17, 18, " 1 �ð�ǥ �������� ���� ");
		gotoxyPrint(17, 20, " 2 �ð�ǥ ���� �߰� ");
		gotoxyPrint(17, 22, " 3 �ð�ǥ ���� ���� ");
		gotoxyPrint(17, 24, " 4 �ð�ǥ �����޴� ������ ");
		gotoxyPrint(11, 27, "���ϴ� ���� �޴��� ���ڸ� �Է����ּ���");
		gotoxyPrint(10, 28, " >> ");

		/*----------�޴� ������ �Է�------------*/
		fflush(stdin);
		fgets(choiceMenu,sizeof(choiceMenu), stdin);
		
		/*----------(Ű �Է��� �� ������ ���)----------*/
		if( (p=strchr(choiceMenu, '\n')) != NULL ) {
			*p = '\0';

			
	    /*----------������ �޴� ����----------*/
			switch (choiceMenu[0]) {
			//�ð�ǥ�������
			case '1': modifySubjectInfo(s);  break; //�ð�ǥ �������� ����
			//�ð�ǥ�����߰�
			case '2': addSubject(s); break; //�ð�ǥ ���� �߰�
			//�ð�ǥ�������
			case '3': removeSubject(s); break; //�ð�ǥ ���� ����
			//�ð�ǥ�����޴�������
			case '4': return;
			//�� ���ڰ� �������� �������� ���� ������ ��
			case 'b': return;
			case 'B': return;
			case 'x': exit(0);
			case 'X': exit(0);
			default:
				{
					
				if(choiceMenu[0] == '\0') {
					gotoxyPrint(16, 30, "�ܸ޴��� �������� �ʾҽ��ϴ١�"); fflush(stdin); Sleep(1000);
				}
	
				gotoxyPrint(16, 30, "�ܸ޴������� �߸��Ǿ����ϴ١�"); fflush(stdin); Sleep(1000);
			
				}
			}
		}

		/*----------(Ű �Է��� �� ���� �̻��� ���)----------*/
		else{
			gotoxyPrint(16, 30, "�ܸ޴������� �߸��Ǿ����ϴ�.��");
			fflush(stdin);
			Sleep(1000);
		}
	}

}


//�ܽð�ǥ �������� ����
void modifySubjectInfo(structMember *s) {

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	FILE *fp;
	char fileName[30];
	structSubject* subjectPointer;
	structSubject tmpSubject;
	int subjectTotalNum;
	char modifyDay[15];
	int OrderOfSubject[5] ={0}; //int���������Ϻ���
	char modifySubject[5];
	int intModifySubjectNum;
	int i;
	int subjectCntOfModifyDay=0;
	int day;
	char *endP;
	int checkDay;
	int checkChoice;


	fflush(stdin);
	listBorderDraw(3,12);


	/*----------������� �ð�ǥ �ؽ�Ʈ ���� ����----------*/
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");


	/*----------(������� �ð�ǥ �ؽ�Ʈ ������ ���� ���)----------*/
	if(fp == NULL ) {
		gotoxyPrint(8, 20, "�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ����");
		Sleep(1500);
		return;
	}

	/*----------(������� �ð�ǥ �ؽ�Ʈ ������ �ִ� ���)----------*/
	else {

		/*----------������� �ð�ǥ �ؽ�Ʈ ���Ͽ� ����� �ð�ǥ �б�----------*/
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject) * subjectTotalNum);
		for(i=0; i<subjectTotalNum; i++) 
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		fclose(fp);


		gotoxyPrint(20, 14, "- �ð�ǥ ���� -");
		gotoxyPrint(7, 16, "������ ������ ���� : ");
		gotoxyPrint(5, 33, "�� ������ ������ ���Ͽ���: '��' �Ǵ� '������' ");
		

			/*----------������ ������ ���� �Է�----------*/
			while(1) {
				fflush(stdin);
				gotoxy(28, 16);
				fgets(modifyDay,8, stdin);

				/*----------(modify �迭 ũ�����Ϸ� �Է��� ���)----------*/
				if( (endP = strchr(modifyDay, '\n')) != NULL ) {
					*endP = '\0';

					checkDay = checkModifyDay(modifyDay);

					if((modifyDay[0] == 'b'|| modifyDay[0] == 'B' )&& modifyDay[1] == '\0' ){
						gotoxyPrint(5, 33, "                                              ");
						return;
					}
				
					else if((modifyDay[0] == 'x'|| modifyDay[0] == 'X' )&& modifyDay[1] == '\0' )  exit(0);

					/*----------(�Է��� ������ ����(��~��)�� �Է����� ���� ���)----------*/
					else if(checkDay == 0){
						warningModifyDay("�������ҿ������Է����ּ���");
						fflush(stdin);
						strcpy(modifyDay,"");
					}

					/*----------(������ �ΰ��̻� �Է��� ���)----------*/
					else if (checkDay == 2) {
						warningModifyDay("���������ϳ����Է����ּ���");
						fflush(stdin);
						strcpy(modifyDay,"");

					}

					

					/*----------(������ �Ѱ� �Է��� ���)----------*/
					else {


						/*----------������ �ش� ���� ������� ----------*/
						for(day=0; day<5; day++) {

							// ���� �������� üũ

								if(strstr(modifyDay, dayOfWeek[day])) {

									if(strstr(modifyDay,"����") || (strcmp(modifyDay,dayOfWeek[day]) == 0 )) {

								// ����� �ð�ǥ���� ����ڰ� �Է��� ���� ã��
								for(i=0; i<subjectTotalNum; i++) {

									// �ش� ���� �������
									if( strstr(dayOfWeek[day], subjectPointer[i].dayOfWeek) ) { 

										OrderOfSubject[subjectCntOfModifyDay] = i+1; //�ð�ǥ ���°�� ������ �ִ��� ����
										gotoxy(15, 19 + subjectCntOfModifyDay * 2 );
										printf("%d %s %s %s����", subjectCntOfModifyDay+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
										subjectCntOfModifyDay++;
									}
								}

								//������ ���Ͽ� ������ ���� ���
								if(OrderOfSubject[0] == 0) {
									gotoxyPrint(13, 22, "���ش� ���Ͽ� ������ �����ϴ١�");
									Sleep(1000);
									gotoxyPrint(13, 22, "                                ");
									gotoxyPrint(28, 16, "               ");
									strcpy(modifyDay,"");
									break;
								}
									}

									else{
										warningModifyDay("�������Է��� �߸��Ǿ����ϴ�");
						fflush(stdin);
						strcpy(modifyDay,"");
						break;


									}
								}


						}
						//������ ������ �������� ���
						if(OrderOfSubject[0] != 0) {
							break;
						}
					}
				}


				/*----------(modify �迭 ũ�� �̻����� �Է��� ���)----------*/
				else {
					warningModifyDay("�������Է����߸��߽��ϴ�");
					strstr(modifyDay,"");
					fflush(stdin);
				}

			}

			fflush(stdin);
			gotoxyPrint(10, 29, "������ ������ �ش� ���ڸ� �Է����ּ���");
			gotoxyPrint(10, 30, " >> ");
			
			

			/*----------������ ������ ���Ͽ��� ���� �����ϴ� while��----------*/
			while(1) {
				fflush(stdin);
				gotoxy(13,30);
				fgets(modifySubject, sizeof(modifySubject), stdin);


				if( (endP = strchr(modifySubject, '\n')) != NULL ) {
					*endP = '\0';

					checkChoice = checkChoiceOfSubject(modifySubject, subjectCntOfModifyDay);

					if((modifySubject[0] == 'b'|| modifySubject[0] == 'B' )&& modifySubject[1] == '\0' ){
						gotoxyPrint(5, 33, "                                              ");
						return;
					}
				
					else if((modifySubject[0] == 'x'|| modifySubject[0] == 'X' )&& modifySubject[1] == '\0' )  exit(0);

					else if(modifySubject[0] == '\0') {
						warningChoiceOfSubject("�������Ұ������������ּ���");
						strcpy(modifySubject,"");
					}

					else if( checkChoice == 0) {
						intModifySubjectNum = atoi(&modifySubject[0])-1;
						break;
					}
					else if(checkChoice == 1) {
						warningChoiceOfSubject("�����ڿ��ǹ��ڸ��Է��ϼ̽��ϴ�");
						strcpy(modifySubject,"");
					}
					else if(checkChoice == 2) {
						warningChoiceOfSubject("�������Ͻż��ڴ¼������������ϴ�");
						strcpy(modifySubject,"");
					}

					else {
						warningChoiceOfSubject("�����ڿ��ǹ��ڸ��Է��ϼ̽��ϴ�");
						strcpy(modifySubject,"");
					}


				}
				else {
					warningChoiceOfSubject("���Է��� �߸��Ǿ����ϴ�");
					strcpy(modifySubject,"");
				}


			}


			/*----------������ ���� (����) ���� ���----------*/
			listBorderDraw(3,12);
			gotoxyPrint(5, 33, "                                               ");
			gotoxyPrint(6, 14, "�������������������������磪��������������������");
			gotoxy(9, 16);
			printf("��  �� : %s",subjectPointer[OrderOfSubject[intModifySubjectNum]-1].dayOfWeek);
			gotoxy(9, 18);
			printf("����� : %s",subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectName);
			gotoxy(9, 20);
			printf("��  �� : %s",subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectClass);


			/*----------������������ Ʋ ���----------*/
			gotoxyPrint(6, 23, "������������������������������������������������");
			gotoxyPrint(9, 25, "��  �� :");
			gotoxyPrint(9, 27, "����� :");
			gotoxyPrint(9, 29, "��  �� :");

			gotoxyPrint(3, 34, "�� ������Ͽ���: '��' �Ǵ� '������'");
			gotoxyPrint(3, 35, "�� ������� ��ĭ���� 5���̳� �Դϴ�");
			gotoxyPrint(3, 36, "�� ���񱳽ô� ���ڿ� ','�̿��� ���ڴ� �Էµ��� �ʽ��ϴ�");
			gotoxyPrint(3, 37, "�� ���񱳽ÿ���: '1,2,3' ");
			
			
			strcpy(modifyDay,"");


			/*----------��������üũ----------*/
			while (1) {

				fflush(stdin);
				gotoxy(18, 25);
				fgets(modifyDay,8, stdin);

				if( (endP = strchr(modifyDay, '\n')) != NULL ) {
					*endP = '\0';

					checkDay = checkModifyDay(modifyDay);


					if((modifyDay[0] == 'b'|| modifyDay[0] == 'B' )&& modifyDay[1] == '\0' ) {
						gotoxyPrint(3, 34, "                                    ");
						gotoxyPrint(3, 35, "                                    ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                                    ");
						return;
					}
				
					else if((modifyDay[0] == 'x'|| modifyDay[0] == 'X' )&& modifyDay[1] == '\0' )  exit(0);

					else if(checkDay == 0){
						warningDayOfModifySubect("�������ҿ������Է����ּ���");
						fflush(stdin);
						strcpy(modifyDay,"");
					}

					/*----------(������ �ΰ��̻� �Է��� ���)----------*/
					else if (checkDay == 2) {
						warningDayOfModifySubect("���������ϳ����Է����ּ���");
						fflush(stdin);
						strcpy(modifyDay,"");

					}


					/*----------(������ �Ѱ� �Է��� ���)----------*/
					else {

						for(i =0; i<5; i++) {
							if(strstr(modifyDay, dayOfWeek[i]) ) {
									strcpy(tmpSubject.dayOfWeek, dayOfWeek[i]);
									break;
							}

						}

						break;

					}


				}
				else {
					warningDayOfModifySubect("���Է����߸��Ǿ����ϴ�");
					fflush(stdin);
					strcpy(modifyDay,"");

				}
							
			
			}


			/*----------��������� üũ----------*/
			while(1) {

				fflush(stdin);
				gotoxy(18, 27);
				fgets(tmpSubject.subjectName, 11, stdin);

				/*----------(Ű �Է��� 5��(�ѱ۱���) �̳��� ���)----------*/
				if( (endP=strchr(tmpSubject.subjectName, '\n')) != NULL ) {
					*endP = '\0';

					if((tmpSubject.subjectName[0] == 'b'|| tmpSubject.subjectName[0] == 'B' )&& tmpSubject.subjectName[1] == '\0' ) {
						gotoxyPrint(3, 34, "                                    ");
						gotoxyPrint(3, 35, "                                    ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                                    ");
						return;
					}
				
					else if((tmpSubject.subjectName[0] == 'x'|| tmpSubject.subjectName[0] == 'X' )&& tmpSubject.subjectName[1] == '\0' )  exit(0);

					//�Է¾��� Enter�� ���� ���
					else if(tmpSubject.subjectName[0] == '\0'){
						strcpy(tmpSubject.subjectName,"");
						warningNameOfModifySubect("������������Է��߽��ϴ�.");
					}


					//����� ��ĭ�� �ִ� ���
					else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
						strcpy(tmpSubject.subjectName,"");
						warningNameOfModifySubect("���������ĭ���ֽ��ϴ�.");

					}

					//����� ���ǿ� �����ϴ� ���
					else {
						break;
					}
				}

				/*----------(Ű �Է��� 5�� �̻��� ���)----------*/
				else {
					strcpy(tmpSubject.subjectName,"");
					warningNameOfModifySubect("�������5�ڸ��ʰ��߽��ϴ�.");
				}

				if(!strstr(tmpSubject.dayOfWeek,""))
							break;

			}




			/*----------�������񱳽� üũ----------*/
			while(1) {

				fflush(stdin);
				gotoxy(18, 29);
				fgets(tmpSubject.subjectClass,sizeof(tmpSubject.subjectClass), stdin);

				/*----------(Ű �Է��� 10�� �̳��� ���)----------*/
			if( (endP=strchr(tmpSubject.subjectClass, '\n')) != NULL ) {
				*endP = '\0';

				if((tmpSubject.subjectClass[0] == 'b'|| tmpSubject.subjectClass[0] == 'B' )&& tmpSubject.subjectClass[1] == '\0' ) {
						gotoxyPrint(3, 34, "                                    ");
						gotoxyPrint(3, 35, "                                    ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                                    ");
						return;
					}
				
				else if((tmpSubject.subjectClass[0] == 'x'|| tmpSubject.subjectClass[0] == 'X' )&& tmpSubject.subjectClass[1] == '\0' )  exit(0);

				//���ڿ�','�̿��� ���ڰ� ���ö�
				else if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
					warningClassOfModifySubect("��','�ͼ����̿��ǹ����Դϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}

				//���ø� �Է����� �ʰ� Enter�� ������
				else if(tmpSubject.subjectClass[0] == '\0') {
					warningClassOfModifySubect("�����ø����Է��߽��ϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}

				//���ø� �ߺ��ǰ� ������
				else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
					if(checkOverlappingInClass(&subjectPointer[OrderOfSubject[intModifySubjectNum]-1],tmpSubject,1) == 0) {
						break;
					}
					else {
						warningClassOfModifySubect("�����ð��ߺ��˴ϴ�");
						strcpy(tmpSubject.subjectClass,"");
					}
					
				}

				//1~13���� �̿��� ���ø� �Է� ������
				else if(checkNumInClass(tmpSubject.subjectClass) == 0){
					warningClassOfModifySubect("��1~13�ܱ̿����Դϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}
				//�Է��� �ùٸ� ��
				else 
					break;



			}
			/*----------(Ű �Է��� 10�� �̻��� ���)----------*/
			else{
				warningClassOfModifySubect("�����ñ��ڼ��ʰ��߽��ϴ�");
					strcpy(tmpSubject.subjectClass,"");
			}
		}

			strcpy(subjectPointer[OrderOfSubject[intModifySubjectNum]-1].dayOfWeek, tmpSubject.dayOfWeek);
			strcpy(subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectName, tmpSubject.subjectName);
			strcpy(subjectPointer[OrderOfSubject[intModifySubjectNum]-1].subjectClass, tmpSubject.subjectClass);

			sortTimetable(subjectPointer,subjectTotalNum,s);
			free(subjectPointer);

			gotoxyPrint(3, 34, "                                    ");
			gotoxyPrint(3, 35, "                                    ");
			gotoxyPrint(3, 36, "                                                      ");
			gotoxyPrint(3, 37, "                                    ");

		}

}


//�ܽð�ǥ ���� �߰�
void addSubject(structMember *s) {

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
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


	/*----------������� �ð�ǥ �ؽ�Ʈ ���� ����----------*/
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	/*----------(������� �ð�ǥ �ؽ�Ʈ ������ ���� ���)----------*/
	if(fp == NULL ) {
		gotoxyPrint(8, 20, "�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ����");
		Sleep(1500);
		return;
	}

	/*----------(������� �ð�ǥ �ؽ�Ʈ ������ �ִ� ���)----------*/
	else {
		/*----------������� �ð�ǥ �ؽ�Ʈ ���Ͽ� ����� �ð�ǥ �б�----------*/
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*(subjectTotalNum+1));

		for(i=0;i<subjectTotalNum;i++) 
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		fclose(fp);



		gotoxyPrint(9, 19,"��  �� :");
		gotoxyPrint(9, 21, "����� :");
		gotoxyPrint(9, 23, "��  �� :");
		gotoxyPrint(3, 34, "�� ������Ͽ���: '��' �Ǵ� '������' ");
		gotoxyPrint(3, 35, "�� ������� ��ĭ���� 5���̳� �Դϴ�");
		gotoxyPrint(3, 36, "�� ���񱳽ô� ���ڿ� ','�̿��� ���ڴ� �Էµ��� �ʽ��ϴ�");
		gotoxyPrint(3, 37, "�� ���񱳽ÿ���: '1,2,3' ");



		fflush(stdin);

		/*----------�߰�����üũ----------*/
		while (1) {

				fflush(stdin);
				gotoxy(18, 19);
				fgets(addDay,8, stdin);

				if( (endP = strchr(addDay, '\n')) != NULL ) {
					*endP = '\0';

					checkDay = checkModifyDay(addDay);

					if((addDay[0] == 'b'|| addDay[0] == 'B' )&& addDay[1] == '\0' ){
						gotoxyPrint(3, 34, "                                       ");
						gotoxyPrint(3, 35, "                                       ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                         ");
						return;
					}
				
			
					else if((addDay[0] == 'x'|| addDay[0] == 'X' )&& addDay[1] == '\0' )  exit(0);

					else if(checkDay == 0){
						warningDayOfAddSubect("���߰��ҿ������Է����ּ���");
						fflush(stdin);
						strcpy(addDay,"");
					}

					/*----------(������ �ΰ��̻� �Է��� ���)----------*/
					else if (checkDay == 2) {
						warningDayOfAddSubect("���������ϳ����Է����ּ���");
						fflush(stdin);
						strcpy(addDay,"");

					}


					/*----------(������ �Ѱ� �Է��� ���)----------*/
					else {

						for(i =0; i<5; i++) {
							if(strstr(addDay, dayOfWeek[i]) ) {
							
									strcpy(tmpSubject.dayOfWeek, dayOfWeek[i]);
									break;

							}
						}
						break;
					}

				}
				else {
					warningDayOfAddSubect("���Է����߸��Ǿ����ϴ�");
					fflush(stdin);
					strcpy(addDay,"");

				}
			} 



		/*----------�߰������ üũ----------*/
			while(1) {

				fflush(stdin);
				gotoxy(18, 21);
				fgets(tmpSubject.subjectName, 11, stdin);

				/*----------(Ű �Է��� 5��(�ѱ۱���) �̳��� ���)----------*/
				if( (endP=strchr(tmpSubject.subjectName, '\n')) != NULL ) {
					*endP = '\0';

					if((tmpSubject.subjectName[0] == 'b'|| tmpSubject.subjectName[0] == 'B' )&& tmpSubject.subjectName[1] == '\0' ){
						
						gotoxyPrint(3, 34, "                                       ");
						gotoxyPrint(3, 35, "                                       ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                         ");

						return;

					}
				
					else if((tmpSubject.subjectName[0] == 'x'|| tmpSubject.subjectName[0] == 'X' )&& tmpSubject.subjectName[1] == '\0' )  exit(0);

					//�Է¾��� Enter�� ���� ���
					else if(tmpSubject.subjectName[0] == '\0'){
						strcpy(tmpSubject.subjectName,"");
						warningNameOfAddSubect("������������Է��߽��ϴ�.");
					}


					//����� ��ĭ�� �ִ� ���
					else if (checkBlankOfSubjectName(tmpSubject.subjectName) == 0) {
						strcpy(tmpSubject.subjectName,"");
						warningNameOfAddSubect("���������ĭ���ֽ��ϴ�.");

					}

					//����� ���ǿ� �����ϴ� ���
					else {
						break;
					}
				}

				/*----------(Ű �Է��� 5�� �̻��� ���)----------*/
				else {
					strcpy(tmpSubject.subjectName,"");
					warningNameOfAddSubect("�������5�ڸ��ʰ��߽��ϴ�.");
				}

			}


			/*----------�߰����񱳽� üũ----------*/
			while(1) {

				fflush(stdin);
				gotoxy(18, 23);
				fgets(tmpSubject.subjectClass,sizeof(tmpSubject.subjectClass), stdin);

				/*----------(Ű �Է��� 10�� �̳��� ���)----------*/
			if( (endP=strchr(tmpSubject.subjectClass, '\n')) != NULL ) {
				*endP = '\0';

				if((tmpSubject.subjectClass[0] == 'b'|| tmpSubject.subjectClass[0] == 'B' )&& tmpSubject.subjectClass[1] == '\0' ){
						
						gotoxyPrint(3, 34, "                                       ");
						gotoxyPrint(3, 35, "                                       ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                         ");

						return;

					}
				
				else if((tmpSubject.subjectClass[0] == 'x'|| tmpSubject.subjectClass[0] == 'X' )&& tmpSubject.subjectClass[1] == '\0' )  exit(0);

				//���ڿ�','�̿��� ���ڰ� ���ö�
				else if(checkCharaterInClass(tmpSubject.subjectClass) == 0) {
					warningClassOfModifySubect("��','�ͼ����̿��ǹ����Դϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}

				//���ø� �Է����� �ʰ� Enter�� ������
				else if(tmpSubject.subjectClass[0] == '\0') {
					warningClassOfAddSubect("�����ø����Է��߽��ϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}

				//���ø� �ߺ��ǰ� ������
				else if (checkOverlappingInClass(subjectPointer,tmpSubject,subjectTotalNum) == 0){
						warningClassOfAddSubect("�����ð��ߺ��˴ϴ�");
						strcpy(tmpSubject.subjectClass,"");
				}

				//1~13���� �̿��� ���ø� �Է� ������
				else if(checkNumInClass(tmpSubject.subjectClass) == 0){
					warningClassOfAddSubect("��1~13�ܱ̿����Դϴ�");
					strcpy(tmpSubject.subjectClass,"");
				}
				//�Է��� �ùٸ� ��
				else 
					break;



			}
			/*----------(Ű �Է��� 10�� �̻��� ���)----------*/
			else{
				warningClassOfModifySubect("�����ñ��ڼ��ʰ��߽��ϴ�");
					strcpy(tmpSubject.subjectClass,"");
			}
		}



		strcpy(subjectPointer[subjectTotalNum].dayOfWeek, tmpSubject.dayOfWeek);
		strcpy(subjectPointer[subjectTotalNum].subjectName, tmpSubject.subjectName);
		strcpy(subjectPointer[subjectTotalNum].subjectClass, tmpSubject.subjectClass);

		sortTimetable(subjectPointer,subjectTotalNum+1,s);


		free(subjectPointer);
	}

	gotoxyPrint(3, 34, "                                       ");
						gotoxyPrint(3, 35, "                                       ");
						gotoxyPrint(3, 36, "                                                      ");
						gotoxyPrint(3, 37, "                         ");

}


//�ܰ������
void removeSubject(structMember *s) {

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	FILE *fp;
	structSubject* subjectPointer;
	char fileName[30];
	int subjectTotalNum;
	char removeDay[15]; 
	int OrderOfSubject[5] ={0}; //int���������Ϻ���
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


	//txt���Ͽ� ����� �ð�ǥ �о����
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");

	//timetable.txt�� ���� ���
	if(fp == NULL ) {
		gotoxyPrint(8, 20, "�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
		Sleep(1500);
	}

	else {
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalNum);
		for(i=0;i<subjectTotalNum;i++) {
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		}
		fclose(fp);


		gotoxyPrint(20, 14, "- �ð�ǥ ������� -");


		gotoxyPrint(5, 33, "�� ������ ������ ���Ͽ���: '��' �Ǵ� '������' ");
		gotoxyPrint(7, 16, "������ ������ ���� : ");
		/*----------������ ������ ���� �Է�----------*/
			while(1) {
				fflush(stdin);
				gotoxy(28, 16);
				fgets(removeDay,8, stdin);

				/*----------(modify �迭 ũ�����Ϸ� �Է��� ���)----------*/
				if( (endP = strchr(removeDay, '\n')) != NULL ) {
					*endP = '\0';

					checkDay = checkModifyDay(removeDay);

					if((removeDay[0] == 'b'|| removeDay[0] == 'B' )&& removeDay[1] == '\0' ){
						gotoxyPrint(5, 33, "                                              ");
						return;
					}
				
					else if((removeDay[0] == 'x'|| removeDay[0] == 'X' )&& removeDay[1] == '\0' )  exit(0);

					/*----------(�Է��� ������ ����(��~��)�� �Է����� ���� ���)----------*/
					else if(checkDay == 0){
						warningModifyDay("�������ҿ������Է����ּ���");
						fflush(stdin);
						strcpy(removeDay,"");
					}

					/*----------(������ �ΰ��̻� �Է��� ���)----------*/
					else if (checkDay == 2) {
						warningModifyDay("���������ϳ����Է����ּ���");
						fflush(stdin);
						strcpy(removeDay,"");

					}

					/*----------(������ �Ѱ� �Է��� ���)----------*/
					else {

						/*----------������ �ش� ���� ������� ----------*/
						for(day=0; day<5; day++) {

							// ���� �������� üũ
							if (strstr(removeDay, dayOfWeek[day])) { 
								if(strstr(removeDay,"����") || (strcmp(removeDay,dayOfWeek[day]) == 0 )) {

								// ����� �ð�ǥ���� ����ڰ� �Է��� ���� ã��
								for(i=0; i<subjectTotalNum; i++) {

									// �ش� ���� �������
									if( strstr(dayOfWeek[day], subjectPointer[i].dayOfWeek) ) { 

										OrderOfSubject[subjectCntOfModifyDay] = i+1; //�ð�ǥ ���°�� ������ �ִ��� ����
										gotoxy(15, 19 + subjectCntOfModifyDay * 2 );
										printf("%d) %s %s %s����", subjectCntOfModifyDay+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
										subjectCntOfModifyDay++;
									}
								}

								//������ ���Ͽ� ������ ���� ���
								if(OrderOfSubject[0] == 0) {
									gotoxyPrint(13, 22, "���ش� ���Ͽ� ������ �����ϴ�.��");
									Sleep(1000);
									gotoxyPrint(13, 22, "                                 ");
									gotoxyPrint(13, 16, "               ");
									strcpy(removeDay,"");
									break;
								}
								}


							}

						}
						//������ ������ �������� ���
						if(OrderOfSubject[0] != 0) {
							break;
						}
					}
				}


				/*----------(modify �迭 ũ�� �̻����� �Է��� ���)----------*/
				else {
					warningModifyDay("�������Է����߸��߽��ϴ�");
					strstr(removeDay,"");
					fflush(stdin);
				}

			}

			fflush(stdin);
			gotoxyPrint(10, 29, "������ ������ �ش� ���ڸ� �Է����ּ���");
			gotoxyPrint(10, 30, " >> ");


			/*----------������ ������ ���Ͽ��� ���� �����ϴ� while��----------*/
			while(1) {
				fflush(stdin);
				gotoxy(13,30);
				fgets(removeSubject, sizeof(removeSubject), stdin);


				if( (endP = strchr(removeSubject, '\n')) != NULL ) {
					*endP = '\0';

					checkChoice = checkChoiceOfSubject(removeSubject, subjectCntOfModifyDay);


					if((removeSubject[0] == 'b'|| removeSubject[0] == 'B' )&& removeSubject[1] == '\0' ){
						gotoxyPrint(5, 33, "                                              ");
						return;
					}
				
					else if((removeSubject[0] == 'x'|| removeSubject[0] == 'X' )&& removeSubject[1] == '\0' )  exit(0);

					else if( checkChoice == 0) {
						intRemoveSubjectNum = atoi(&removeSubject[0])-1;

						for(i=OrderOfSubject[intRemoveSubjectNum];i<subjectTotalNum;i++) {
			
							strcpy(subjectPointer[i-1].dayOfWeek, subjectPointer[i].dayOfWeek);
							strcpy(subjectPointer[i-1].subjectName, subjectPointer[i].subjectName);
							strcpy(subjectPointer[i-1].subjectClass, subjectPointer[i].subjectClass);
						}


						break;
					}

					else if(checkChoice == 1) {
						warningChoiceOfSubject("�����ڿ��ǹ��ڸ��Է��ϼ̽��ϴ�");
						strcpy(removeSubject,"");
					}
					else if(checkChoice == 2) {
						warningChoiceOfSubject("�������Ͻż��ڴ¼������������ϴ�");
						strcpy(removeSubject,"");
					}

					else if(removeSubject[0] == '\0') {
						warningChoiceOfSubject("�������Ұ������������ּ���");
						strcpy(removeSubject,"");
					}



					else {
						warningChoiceOfSubject("�����ڿ��ǹ��ڸ��Է��ϼ̽��ϴ�");
						strcpy(removeSubject,"");
					}
				}
				else {

					warningChoiceOfSubject("���Է��� �߸��Ǿ����ϴ�");
					strcpy(removeSubject,"");
				}


			}


		if(subjectTotalNum-1 == 0 ) {
			nResult = remove(fileName);
			if(nResult == 0) {
				gotoxyPrint(8, 28, "*�ð�ǥ�� ���������� �����Ǿ����ϴ�*");  //����� ����
				Sleep(1500);
				return;
			} else if (nResult == -1) {
				gotoxyPrint(20, 28, "*������ ���� ����, ������ �����߽��ϴ�*"); //����� ����
			}

			Sleep(10000);
		}
		else
			saveTimetalbe(subjectPointer,subjectTotalNum-1,s);
	}

	gotoxyPrint(5, 33, "                                              ");
}

int checkModifyDay(char* modifyDay) {


	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	int day;
	int dayCnt = 0;

	for(day = 0; day <5; day++ ){
	
		if(strstr(modifyDay, dayOfWeek[day])) 
			dayCnt++;

	}


	if(dayCnt == 0) 
		return 0;
	

	else if(dayCnt == 1)
		return 1;

	else 
		return 2;

}


void warningModifyDay(char* warning) {

	gotoxyPrint(28, 16, warning);
	Sleep(1000);
	gotoxyPrint(28, 16, "                          ");

}
void warningChoiceOfSubject(char* warning) {


	gotoxyPrint(13, 30, warning);
	Sleep(1000);
	gotoxyPrint(13, 30, "                                ");

}

void warningDayOfModifySubect(char* warning) {

	gotoxyPrint(18, 25, warning);
	Sleep(1000);
	gotoxyPrint(18, 25, "                          ");

}


void warningNameOfModifySubect(char* warning) {

	gotoxyPrint(18, 27, warning);
	Sleep(1000);
	gotoxyPrint(18, 27, "                          ");

}

void warningClassOfModifySubect(char* warning) {

	gotoxyPrint(18, 29, warning);
	Sleep(1000);
	gotoxyPrint(18, 29, "                          ");

}


void warningDayOfAddSubect(char* warning) {

	gotoxyPrint(18, 19, warning);
	Sleep(1000);
	gotoxyPrint(18, 19, "                          ");

}

void warningNameOfAddSubect(char* warning) {

	gotoxyPrint(18, 21, warning);
	Sleep(1000);
	gotoxyPrint(18, 21, "                          ");

}

void warningClassOfAddSubect(char* warning) {

	gotoxyPrint(18, 23, warning);
	Sleep(1000);
	gotoxyPrint(18, 23, "                          ");

}


int checkChoiceOfSubject(char* modifySubject, int subjectCntOfModifyDay) {

	int i;
	int tmpModifySubject = atoi(modifySubject);



		if( tmpModifySubject > 0 && tmpModifySubject <= subjectCntOfModifyDay) {

			return 0;
			

		}
		else{
			for(i= 0; modifySubject[i] != '\0'; i++) {

				if(modifySubject[i] >= '0' && modifySubject[i] < '9')
					return 2;


			}


		}
		
		return 1; //���ڿ��ǹ��ڸ��Է��ϼ̽��ϴ�


}