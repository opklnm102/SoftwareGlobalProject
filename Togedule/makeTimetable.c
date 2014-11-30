#include"structHeader.h"


//�ð�ǥ ��~�� ���񰹼� �Է� �Լ�
void InputSubjectCnt() {

	int i, subjectTotalCnt=0;
	int SubjectCntOfday[5]={0};
	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};


	screenBorderDraw() ;
	listBorderDraw(3,12);


	gotoxy(6, 31);
	printf("** �Ϸ� �ִ���� ������ 5������.");
	gotoxy(6, 32);
	printf("**  �� �ִ���� ������ 13�� ����.");

	while (1) {
		gotoxy(20,15);
		printf("- �ð�ǥ ����� -");

		for(i=0;i<5;i++){
			gotoxy(7, 18+i*2);
			printf(" %s���� ���� ���� : ", dayOfWeek[i]);
		}

		for(i=0;i<5;i++){
			gotoxy(27,18+i*2);
			scanf("%d", &SubjectCntOfday[i]);

			//�Ϸ���񰹼��� �ʰ��� ���
			if(SubjectCntOfday[i] > 5 ) {
				gotoxy(27, 18+i*2);
				printf(" ���Ϸ��ִ���񰳼�(5��)�ʰ�!");
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
		//�Ѱ��񰹼��� �ʰ��� ���
		if(subjectTotalCnt > 13 ){

			for(i=0;i<5;i++){
				gotoxy(27, 18+i*2);
				printf("    ");
			}

			gotoxy(12, 28);
			printf(" �� �� �ִ� �����(13��)�� �ʰ�. ��\n");
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
	char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};
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
	fflush(stdin);
	//���� �̸�/���� �Է�
	for( i = 0; i < 5; i++){

		strcpy(tmpSubject.dayOfWeek,dayOfWeek[i]);

		for(j=0; j <SubjectCntOfday[i] ; j++){

			y = j+tmp;
			//�����̸�
			gotoxy(78,y);
			gets(tmpSubject.subjectName);

			//���񱳽�
			while(1) {
				gotoxy(107,y);
				gets(tmpSubject.subjectClass);

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