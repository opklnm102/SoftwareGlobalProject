#include"structHeader.h"

//�� �ð�ǥ�޴��Լ�
void timetableMenu(structMember *s) {	
	char choiceMenu[3];
	char *endP;

	screenBorderDraw() ;

	while(1) {

		listBorderDraw(3,12);
		timetableDraw(s);
		fflush(stdin);

		/*----------�޴� ���----------*/
		gotoxyPrint(20, 17, " 1 �ð�ǥ ����� ");
		gotoxyPrint(20, 19, " 2 �ð�ǥ ��  �� ");
		gotoxyPrint(20, 21, " 3 �ð�ǥ ��ü���� ");
		gotoxyPrint(20, 23, " 4 �ð�ǥ ������ ");
		gotoxyPrint(13, 26, "���ϴ� �޴��� ���ڸ� �Է����ּ���");
		gotoxyPrint(12, 27, " >> ");


		/*----------�޴� ������ �Է�------------*/
		fgets(choiceMenu,sizeof(choiceMenu), stdin);

		/*----------(Ű �Է��� �� ������ ���)----------*/
		if( (endP=strchr(choiceMenu, '\n')) != NULL ) {
			*endP = '\0';

			/*----------������ �޴� ����----------*/
			switch (choiceMenu[0]) {
				//�ð�ǥ �����
			case '1': makeTimetable(s);  break; 
				//�ð�ǥ ����
			case '2': modifyMenu(s); break;
				//�ð�ǥ ��ü����
			case '3': removeTimetable(s); break;
				//�ð�ǥ ����
			case '4': return;
			case 'b': return;
			case 'B': return;
			case 'x': exit(0);
			case 'X': exit(0);
				//�� ���ڰ� �������� �������� ���� ������ ��
			default: {

				if(choiceMenu[0] == '\0') {
					gotoxyPrint(16, 30, "�ܸ޴��� �������� �ʾҽ��ϴ١�"); fflush(stdin); Sleep(1000);
				}
				else{

					gotoxyPrint(16, 30, "�ܸ޴������� �߸��Ǿ����ϴ١�"); fflush(stdin); Sleep(1000);
				}

					 }
			}
		}

		/*----------(Ű �Է��� �� ���� �̻��� ���)----------*/
		else{
			gotoxyPrint(16, 30, "�ܸ޴������� �߸��Ǿ����ϴ١�");
			fflush(stdin);
			Sleep(1000);
		}
	}
}

//�� �ð�ǥ�׸����Լ�
void timetableDraw(structMember *s){ 

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	FILE *fp;
	char fileName[30];
	structSubject* subjectPointer;
	int subjectTotalNum;
	int tmpintClass[10]={0};
	int i,j,k;

	/*----------�ð�ǥ Ʋ �׸���----------*/
	gotoxyPrint(57, 7, "����������������������������������������������������������������������");
	gotoxyPrint(57, 8, "�� ���� ��    ��    ��    ȭ    ��    ��    ��    ��    ��    ��    ��");
	gotoxyPrint(57, 9, "����������������������������������������������������������������������");
	for(i=0; i<26; i+=2) { 
		gotoxy(57,10+i);
		printf("��  %2d  ��          ��          ��          ��          ��          ��",i/2+1);
		gotoxy(57,10+i+1);
		if(i!= 24)
			printf("����������������������������������������������������������������������");
	}
	gotoxyPrint(57, 35, "����������������������������������������������������������������������");


	/*----------����� �ؽ�Ʈ���� ����----------*/
	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"r");


	/*----------(����� �ؽ�Ʈ������ ���� ���)----------*/
	if(fp == NULL ) {
		gotoxyPrint(83, 20, "*�ð�ǥ�� ������ּ���*");
	}

	/*----------(����� �ؽ�Ʈ������ �ִ� ���)----------*/
	else {

		// �ؽ�Ʈ���Ͽ� �ִ� ���񰳼��� �о �����Ҵ�
		fscanf(fp, "%d", &subjectTotalNum);
		subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectTotalNum);
		for(i=0;i<subjectTotalNum;i++) 
			fscanf(fp,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);
		fclose(fp);

		/*----------�ؽ�Ʈ���Ͽ� �ִ� ���񱳽ø� �о �´� ��ġ�� �����̸� ���----------*/
		for(i=0;i<5;i++) {
			for(j=0;j<subjectTotalNum;j++) {

				/*----------(����� ������� ���ϰ� ��~�ݿ��� ��)----------*/
				if( strstr(subjectPointer[j].dayOfWeek, dayOfWeek[i]) ) {

					//�̹� ����� ������� char�����ø� int������ ��ȯ
					classAtoi(subjectPointer[j].subjectClass, tmpintClass);

					//���� ���� �ش��ϴ� ��ġ�� �����̸� ���
					for(k=0;k<10 ; k++) {

						if(tmpintClass[k] >= 1 && tmpintClass[k] <= 13) {
							gotoxy(67+12*i,8+tmpintClass[k]*2);
							printf("%s",subjectPointer[j].subjectName);
						}

						else
							break;
					}

					for(k=0;k<10; k++)
						tmpintClass[k] = 0;
				}
			}
		}
	}
}

//�� �ð�ǥ ������� �ؽ�Ʈ���Ϸ� �����ϴ� �Լ�
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalNum, structMember *s) {

	FILE *fp;
	char fileName[30];
	int i;

	strcpy(fileName ,getUserTextFileName(s));
	fp=fopen(fileName,"w");

	fprintf(fp,"%d\n",subjectTotalNum);

	for(i=0;i<subjectTotalNum; i++)
		fprintf(fp,"%s %s %s\n",subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);

	fclose(fp);
}

//�� ����� ��ĭ üũ�Լ�
int checkBlankOfSubjectName(char* subjectName) {

	int i;

	for(i=0; subjectName[i] !='\0'; i++) {

		if(subjectName[i] == ' ')
			return 0;
	}

	return 1;

}

//�� ���ÿ� ����� char���� ���ڸ� int���� ���ڷ� �ٲ���ִ� �Լ�.
void classAtoi(char *subjectClass, int *tmpIntClass) {

	int i, j=0, num=0;

	for(i=0; subjectClass[i] != '\0'; i++) {

		/*----------(���񱳽ÿ��� (char��)������ ���)----------*/
		if(subjectClass[i] == ' ' || subjectClass[i] == ',') {
			tmpIntClass[j]=num;
			num = 0;
			j++;
		}
		/*----------(���񱳽ÿ��� (char��)������ ���)----------*/
		else if (subjectClass[i] >= '0' && subjectClass[i] <= '9') {

			// (char��)���ڰ� ���� �ڸ��϶�
			if(num != 0) {

				num = num*10 + (subjectClass[i]-'0');

				if(subjectClass[i+1] == '\0')
					tmpIntClass[j] = num;
			}

			// (char��)���ڰ� ���� �ڸ��϶�
			else {
				num = (subjectClass[i]-'0');

				if(subjectClass[i+1] == '\0')
					tmpIntClass[j] = num;
			}
		}	
	}
}


//�� �ð�ǥ �����ߺ��˻� �Լ�
int checkOverlappingInClass(structSubject* subjectPointer, structSubject subject,int subjectTotalNum) {

	int savedClass[10]={0},puttingClass[10]={0};
	int i,j,k;


	//�Է����� ������ char�����ø� int������ ��ȯ
	classAtoi(subject.subjectClass,puttingClass);

	/*----------�Է����� ������ ���ÿ� ����� ����� ���ÿ� ��----------*/
	for(i=0; i<subjectTotalNum; i++) {

		/*----------(�Է����� ������ ����� ������� ���ϰ� ���� ���)----------*/
		if(strstr(subjectPointer[i].dayOfWeek, subject.dayOfWeek)){
			if(subjectPointer[i].subjectClass[0] >= '0' && subjectPointer[i].subjectClass[0] <= '9'){

				//�̹� ����� ������� char�����ø� int������ ��ȯ
				classAtoi(subjectPointer[i].subjectClass,savedClass);

				//�����ߺ��˻�
				for(j=0; puttingClass[j] != 0 ; j++){
					for(k=0; savedClass[k] != 0 ; k++) {

						//���ð� ������ 0 (false)
						if(puttingClass[j] == savedClass[k]){
							return 0;
						}
					}
				}
			}
		}
	}
	//���ð� ���� ������ 1 (true)
	return 1;
}

//�� �ð�ǥ ���ü��� �˻� �Լ�
int checkNumInClass(char* subjectClass) {

	int intSubjectClass[10];
	int i;

	classAtoi(subjectClass,intSubjectClass);

	for(i=0;i<10; i++) {

		//���ð� 13���ø� ������ return 0
		if(intSubjectClass[i] >13) {
			return 0;
		}
	}	
	return 1;
}

//�� �ð�ǥ ���� ���� �˻� �Լ�
int checkCharaterInClass(char* subjectClass) {

	int i;

	for(i=0; subjectClass[i] != '\0'; i++){

		//���ð� ���ڰ� �ƴҶ� ','���ڵ� �ƴϸ� return0
		if(subjectClass[i] <'0' || subjectClass[i] >'9' ){
			if(subjectClass[i] != ',') {
				return 0;

			}
		}
	}
	return 1;
}

//�� �ð�ǥ�����Լ�
void sortTimetable(structSubject* subjectPointer,int subjectTotalNum, structMember *s){

	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
	structSubject * tmpsubjectPointer;
	int i,j,k=0;

	tmpsubjectPointer = (structSubject *)malloc(sizeof(structSubject) * subjectTotalNum);

	/*----------�����Ϻ��� �ݿ��ϱ��� ������� ������� ���� ����----------*/
	for(i=0;i<5; i++ ) {
		for(j=0;j<subjectTotalNum; j++ ){
			if (strstr(dayOfWeek[i], subjectPointer[j].dayOfWeek)){
				strcpy(tmpsubjectPointer[k].dayOfWeek, subjectPointer[j].dayOfWeek);
				strcpy(tmpsubjectPointer[k].subjectClass, subjectPointer[j].subjectClass);
				strcpy(tmpsubjectPointer[k++].subjectName, subjectPointer[j].subjectName);
			}
		}
	}

	saveTimetalbe(tmpsubjectPointer,subjectTotalNum, s);
	gotoxyPrint(15, 31, "**�ð�ǥ�� ������ �Ϸ��Ͽ����ϴ�**");
	Sleep(1000);
}

//�� ������ؽ�Ʈ�����̸��� �������ִ� �Լ�
char* getUserTextFileName (structMember *s) {

	char fileName[30];

	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"timetable");
	strcat(fileName,".txt");

	return fileName;
}