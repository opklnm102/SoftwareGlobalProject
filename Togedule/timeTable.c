
#include"structHeader.h"

char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};


//�ð�ǥ�޴��Լ�
void timetableMenu(structMember *s) {
	int choiceMenu;
	while(1) {
		screenBorderDraw() ;
		listBorderDraw(3,10);
		timetableDraw();

		gotoxy(20, 18);
		printf(" 1. �ð�ǥ ����� ");
		gotoxy(20,20);
		printf(" 2. �ð�ǥ ��  �� ");
		gotoxy(20,22);
		printf(" 3. �ð�ǥ ��  �� ");
		gotoxy(20,24);
		printf(">> ");
		scanf("%d", &choiceMenu);
		switch (choiceMenu) {
		case 1: InputSubjectCnt();  break; // �ð�ǥ��������
		case 2: modifyMenu(); break; //�ð�ǥ����
		case 3: removeTimetable(); break; //�ð�ǥ����
		}

	}
}
//�ð�ǥ�׸����Լ�
void timetableDraw(){ 

	FILE *fp1;
	int i,j,k;
	int Subjectcnt;
	structSubject* subjectPointer;
	int tmpClassCnt[10]={0};
	int b=0;

	gotoxy(57,7); 
	printf("����������������������������������������������������������������������");
	gotoxy(57,8);
	printf("�� ���� ��    ��    ��    ȭ    ��    ��    ��    ��    ��    ��    ��"); 
	gotoxy(57,9);
	printf("����������������������������������������������������������������������");
	for(i=0; i<26; i+=2) { 
		gotoxy(57,10+i);
		printf("��  %2d  ��          ��          ��          ��          ��          ��",i/2+1);
		gotoxy(57,10+i+1);
		if(i!= 24)
			printf("����������������������������������������������������������������������");
	}
	gotoxy(57,35);
	printf("����������������������������������������������������������������������");
	fp1=fopen("timetable.txt","r");

	//timetable.txt�� ���� ���
	if(fp1 == NULL ) {
		gotoxy(83,20);
		printf("*�ð�ǥ�� ������ּ���*");
	}
	//timetable.txt�� �ִ� ���
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
//�ð�ǥ txt�� �����ϴ� �Լ�
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



//���ÿ� ����� char���� ���ڸ� int���� ���ڷ� �ٲ���ִ� �Լ�.
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


///�ð�ǥ �����ߺ��˻� �Լ�
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

//�ð�ǥ ��~�� ���񰹼� �Է� �Լ�
void InputSubjectCnt() {

	int i, subjectTotalCnt=0;
	int SubjectCntOfday[5]={0};


	screenBorderDraw() ;
	listBorderDraw(3,10);


	gotoxy(6, 31);
	printf("** �Ϸ� �ִ���� ������ 5������.");
	gotoxy(6, 32);
	printf("**  �� �ִ���� ������ 13�� ����.");

	while (1) {
		gotoxy(20,15);
		printf("- �ð�ǥ ����� -");

		for(i=0;i<5;i++){
			gotoxy(10, 18+i*2);
			printf(" %s���� ���� ���� : ", dayOfWeek[i]);
		}

		for(i=0;i<5;i++){
			gotoxy(30,18+i*2);
			scanf("%d", &SubjectCntOfday[i]);

			//�Ϸ���񰹼��� �ʰ��� ���
			if(SubjectCntOfday[i] > 5 ) {
				gotoxy(30, 18+i*2);
				printf(" ���Ϸ��ִ���񰹼��ʰ�!");
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
		//�Ѱ��񰹼��� �ʰ��� ���
		if(subjectTotalCnt > 13 ){

			for(i=0;i<5;i++){
				gotoxy(35, 18+i*2);
				printf("    ");
			}

			gotoxy(8, 28);
			printf(" �� �� �ִ� �����(13��)�� �ʰ��ϼ̽��ϴ�. ��\n");
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

// �̸�/���� �Է��Լ�
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
			printf("*����������������������- %s���� -������������*����������\n", dayOfWeek[i]);

			for(j=0; j <SubjectCntOfday[i] ; j++){
				// ���� ����ü�� �ð�ǥ ���� �Է�
				strcpy(subjectPointer[k].dayOfWeek,dayOfWeek[i]);
				k++;
				y++;
				gotoxy(65,10+y);
				printf(" %d. ����� :                       ���� :       \n",j+1);
			}
			y++;
			gotoxy(65,10+y);
			printf("\n");
		}
	}

	//�̸�/���� �Է� ���ǹ�
	gotoxy(65, 31);
	printf("** ������� 5���̳�.");
	gotoxy(65, 32);
	printf("** ex) ���� : 1,2,3 ���� �Է�.");

	k=0;
	//���� �̸�/���� �Է�
	for( i = 0; i < 5; i++){

		strcpy(tmpSubject.dayOfWeek,dayOfWeek[i]);

		for(j=0; j <SubjectCntOfday[i] ; j++){

			y = j+tmp;
			//�����̸�
			gotoxy(78,y);
			scanf("%s",&tmpSubject.subjectName);

			//���񱳽� ��
			while(1) {
				gotoxy(107,y);
				scanf("%s",&tmpSubject.subjectClass);

				//�����ߺ����� �˻�
				if (checkOverlappingClass(subjectPointer,tmpSubject,subjectTotalCnt) == 0){
					gotoxy(107,y);
					printf("�������ߺ�!");
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

//�ð�ǥ �����޴�
void modifyMenu () {

	int choiceMenu;

	fflush(stdin);
	listBorderDraw(3,10);

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
	int subjectTotalCnt; //�����Ѱ���
	char charModifyDay[15]; //char���������Ϻ��� 
	int intModifyDay[5] ={0}; //int���������Ϻ���
	char charModifySubjectNum[5]={0}; //���������ȣ
	int intModifySubjectNum;
	int i,j=0,k=0;


	fflush(stdin);
	listBorderDraw(3,10);


	gotoxy(20,12);
	printf("- �ð�ǥ ���� -");
	gotoxy(15, 14);
	printf("������ ���� ���� : ");
	gotoxy(33, 14);
	gets(charModifyDay);

	//txt���Ͽ� ����� �ð�ǥ �о����
	fp=fopen("timetable.txt","r");
	fscanf(fp, "%d", &subjectTotalCnt);
	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);


	for(i=0;i<subjectTotalCnt;i++) {
		fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
	}

	fclose(fp);

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
			break;
		}
	}


	gotoxy(15,26);
	printf(">> ");
	gotoxy(18,26);
	scanf("%s", &charModifySubjectNum);
	intModifySubjectNum = atoi(charModifySubjectNum)-1;


	//�ش������������
	listBorderDraw(3,10);

	gotoxy(6, 12);
	printf("�������������������������磪��������������������");
	gotoxy(9, 14);
	printf("��  �� : %s",subjectPointer[intModifyDay[intModifySubjectNum]].dayOfWeek);
	gotoxy(9, 16);
	printf("����� : %s", subjectPointer[intModifyDay[intModifySubjectNum]].subjectName);
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

			gotoxy(18, 27);
			printf("�������ߺ�!");
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

//�ð�ǥ ���� �߰�
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

//�������
void removeSubject() {

	FILE *fp;
	structSubject* subjectPointer;//�ð�ǥ������
	int subjectTotalCnt; //�����Ѱ���
	char charRemoveDay[15]; //char���������Ϻ��� 
	int intRemoveDay[5] ={0}; //int���������Ϻ���
	char charRemoveSubjectNum[5]={0}; //���������ȣ
	int intRemoveSubjectNum;
	int i,j=0,k=0;


	fflush(stdin);
	listBorderDraw(3,10);


	gotoxy(20,12);
	printf("- �ð�ǥ ������� -");
	gotoxy(15, 14);
	printf("������ ���� ���� : ");
	gotoxy(33, 14);
	gets(charRemoveDay);

	//txt���Ͽ� ����� �ð�ǥ �о����
	fp=fopen("timetable.txt","r");
	fscanf(fp, "%d", &subjectTotalCnt);
	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalCnt);

	for(i=0;i<subjectTotalCnt;i++) {
		fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
	}

	fclose(fp);

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


//�ð�ǥ�����Լ�
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
	printf("**�ð�ǥ�� ������ �Ϸ��Ͽ����ϴ�**");
	Sleep(1000);
}


void removeTimetable() {

	int nResult;
	char answer;

	listBorderDraw(3,10);

	gotoxy(8,22);
	printf("�� �ð�ǥ ��ü ������ �˴ϴ�. �����Ͻðڽ��ϱ�?(y/n)");
	gotoxy(8,24);
	printf(">>");
	gotoxy(12,24);
	scanf("%c",&answer);

	if(answer == 'y' || answer == 'Y') {
		nResult = remove("timetable");
		if(nResult == 0) {
			gotoxy(20,26);
			printf("*�ð�ǥ�� ���������� �����Ǿ����ϴ�*");  //����� ����
		} else if (nResult == -1) {
			gotoxy(20,26);
			printf("fail");  //����� ����
		}

		Sleep(10000);
	}
}
