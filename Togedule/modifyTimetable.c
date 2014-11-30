#include"structHeader.h"


//�ð�ǥ �����޴�
void modifyMenu () {

	int choiceMenu;

	fflush(stdin);
	listBorderDraw(3,12);

	gotoxy(22,15);
	printf("*�ð�ǥ �����޴�*");


	gotoxy(17, 18);
	printf(" 1. �ð�ǥ �������� ���� ");
	gotoxy(17,20);
	printf(" 2. �ð�ǥ ���� �߰� ");
	gotoxy(17,22);
	printf(" 3. �ð�ǥ ���� ���� ");
	gotoxy(17,24);
	printf(">> ");
	scanf("%d", &choiceMenu);

	switch (choiceMenu) {
	case 1: modifySubjectInfo();  break; //�ð�ǥ �������� ����
	case 2: addSubject(); break; //�ð�ǥ ���� �߰�
	case 3: removeSubject(); break; //�ð�ǥ ���� ����
	}

}

//�ð�ǥ �������� ����
void modifySubjectInfo() {

	FILE *fp;
	structSubject* subjectPointer;//�ð�ǥ������
	structSubject tmpSubject;
	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	int subjectTotalCnt; //�����Ѱ���
	char charModifyDay[15]; //char���������Ϻ��� 
	int intModifyDay[5] ={0}; //int���������Ϻ���
	char charModifySubjectNum[5]={0}; //���������ȣ
	int intModifySubjectNum;
	int i,j=0,k=0;


	fflush(stdin);
	listBorderDraw(3,12);


	//txt���Ͽ� ����� �ð�ǥ �о����
	fp=fopen("timetable.txt","r");

	//timetable.txt�� ���� ���
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
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
	printf("- �ð�ǥ ���� -");

	
	gotoxy(15, 14);
	printf("������ ���� ���� : ");

	while(1) {
	gotoxy(33, 14);
	gets(charModifyDay);

		//������ �ش� ���� ������� 
		for(k=0; k<5; k++) {
			if ( strstr(charModifyDay, dayOfWeek[k]) ) { //� �������� üũ
				for(i=0;i<subjectTotalCnt;i++) {
					if(strstr(dayOfWeek[k],subjectPointer[i].dayOfWeek)) { //�Էµ� �ð�ǥ���� ���������� ã�� �ش� ���� �������
						intModifyDay[j] = i; //�ð�ǥ ���°�� ������ �ִ��� ����
						gotoxy(15, 17+j*2);
						printf("%d) %s %s %s����", j+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
						j++;
					}
				}
				if(intModifyDay[0] == 0 ) {
					gotoxy(13,20);
					printf("���ش� ���Ͽ� ������ �����ϴ�.��");
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


		//�ش������������
		listBorderDraw(3,12);

		gotoxy(6, 12);
		printf("�������������������������磪��������������������");
		gotoxy(9, 14);
		printf("��  �� : %s",subjectPointer[intModifyDay[intModifySubjectNum]].dayOfWeek);
		gotoxy(9, 16);
		printf("����� : %s",subjectPointer[intModifyDay[intModifySubjectNum]].subjectName);
		gotoxy(9, 18);
		printf("��  �� : %s",subjectPointer[intModifyDay[intModifySubjectNum]].subjectClass);

		gotoxy(6, 21);
		printf("������������������������������������������������");
		gotoxy(9, 23);
		printf("��  �� :");
		gotoxy(9, 25);
		printf("����� :");
		gotoxy(9, 27);
		printf("��  �� :");

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
				printf("�������ߺ�!");
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

//�ð�ǥ ���� �߰�
void addSubject() {

	FILE *fp;
	structSubject* subjectPointer;
	structSubject tmpSubject;

	int subjectTotalCnt;
	int i;

	fflush(stdin);
	listBorderDraw(3,12);


	//txt���Ͽ� ����� �ð�ǥ �о����
	fp=fopen("timetable.txt","r");

	//timetable.txt�� ���� ���
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
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
		printf("��  �� :");
		gotoxy(9, 19);
		printf("����� :");
		gotoxy(9, 21);
		printf("��  �� :");

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
				printf("�������ߺ�!");
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

//�������
void removeSubject() {

	FILE *fp;
	structSubject* subjectPointer;//�ð�ǥ������
	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	int subjectTotalCnt; //�����Ѱ���
	char charRemoveDay[15]; //char���������Ϻ��� 
	int intRemoveDay[5] ={0}; //int���������Ϻ���
	char charRemoveSubjectNum[5]={0}; //���������ȣ
	int intRemoveSubjectNum;
	int nResult;
	int i,j=0,k=0;

	fflush(stdin);
	listBorderDraw(3,12);


	//txt���Ͽ� ����� �ð�ǥ �о����
	fp=fopen("timetable.txt","r");

	//timetable.txt�� ���� ���
	if(fp == NULL ) {
		gotoxy(8,20);
		printf("�ܽð�ǥ�� �����ϴ�. �ð�ǥ�� ������ּ���.��");
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
		printf("- �ð�ǥ ������� -");

		while(1) {
		gotoxy(15, 14);
		printf("������ ���� ���� : ");
		gotoxy(33, 14);
		gets(charRemoveDay);

		//������ �ش� ���� ������� 
		for(k=0; k<5; k++) {
			if ( strstr(charRemoveDay, dayOfWeek[k]) ) { //� �������� üũ
				for(i=0;i<subjectTotalCnt;i++) {
					if(strstr(dayOfWeek[k],subjectPointer[i].dayOfWeek)) { //�Էµ� �ð�ǥ���� ���������� ã�� �ش� ���� �������
						intRemoveDay[j] = i; //�ð�ǥ ���°�� ������ �ִ��� ����
						gotoxy(15, 17+j*2);
						printf("%d) %s %s %s����", j+1, subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
						j++;
					}
				}
					if(intRemoveDay[0] == 0 ) {
					gotoxy(13,20);
					printf("���ش� ���Ͽ� ������ �����ϴ�.��");
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
			printf("*�ð�ǥ�� ���������� �����Ǿ����ϴ�*");  //����� ����
			Sleep(1500);
			return;
		} else if (nResult == -1) {
			gotoxy(20,26);
			printf("*������ ���� ����, ������ �����߽��ϴ�*");  //����� ����
		}

		Sleep(10000);
		}
		else
		saveTimetalbe(subjectPointer,subjectTotalCnt-1);


	}
}