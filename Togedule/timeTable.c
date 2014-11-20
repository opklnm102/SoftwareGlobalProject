#include"structHeader.h"
//�������Ϸ� ����� �� ���� ����� function.c �����ؼ� �۾��ؾ���
char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};  //��������

//int main() {
//
//	system("mode con:cols=130 lines=46");  //���� 130, ���� 45  //�������� 
//	timetableMenu();
//	gotoxy(50,50);
//}

//void gotoxy(int x, int y) { 
//	COORD Cur;
//	Cur.X=x;
//	Cur.Y=y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
//}

//�ð�ǥ�޴��Լ�
void timetableMenu(structMember *s) {

	int i;
	int choiceMenu;

	while(1) {
		screenBorderDraw() ;
		listBorderDraw();
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

		case 1: InputSubjectCnt(s);  break; // �ð�ǥ��������
		case 2: modifyTimetable(s); break; //�ð�ǥ����
		case 3: removeTimetable(s); break; //�ð�ǥ����

		}
		
	}
}

//�ð�ǥ�׸����Լ�
void timetableDraw(){  


	FILE *fp1;
	int i,j,stringCnt=0;
	int Subjectcnt;
	structSubject* subjectPointer;
	int tmpClassCnt;
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



	//58,13
	for(j=0;j<5;j++) {
		for(i=0;i<Subjectcnt;i++) {
			if( strstr(subjectPointer[i].dayOfWeek, dayOfWeek[j]) ) {

				/*for(k=1;k<=13; k++ ) {
					
				}*/

				while( subjectPointer[i].subjectClass[stringCnt] != '\0' ) {
					if(subjectPointer[i].subjectClass[stringCnt] >= '0' && subjectPointer[i].subjectClass[stringCnt] <='9'){
						tmpClassCnt =  subjectPointer[i].subjectClass[stringCnt] - '0';
					}

					gotoxy(67+12*j,8+tmpClassCnt*2); //67+6*j, 12+tmpClassCnt
					printf("%s",subjectPointer[i].subjectName);
				stringCnt++;
				}
				stringCnt = 0;
			}

		}
	}
	}
	
}

//�ð�ǥ txt�� �����ϴ� �Լ�
void saveTimetalbe(structSubject* subjectPointer, int subjectSum) {

	FILE *fp1,*fp2;   
	char fileName[30];
	int i;


	fp1=fopen("timetable.txt","w");

	fprintf(fp1,"%d\n",subjectSum);
	for(i=0;i<subjectSum; i++) {
		fprintf(fp1,"%s ",subjectPointer[i].dayOfWeek);
		fprintf(fp1,"%s ",subjectPointer[i].subjectName);
		fprintf(fp1,"%s\n", subjectPointer[i].subjectClass);
	}
	fclose(fp1);

}



//�ð�ǥ ��~�� ���񰹼� �Է� �Լ�
void InputSubjectCnt(structMember *s) {

	int i, subjectSum=0;
	int SubjectCntOfday[5]={0};

	screenBorderDraw();  //��üȭ��Ʋ����Լ�
	listBorderDraw();  //�޴�Ʋ����Լ�

	gotoxy(6, 31);
	printf("** �Ϸ� �ִ���� ������ 5������.");
	gotoxy(6, 32);
	printf("**  �� �ִ���� ������ 13�� ����.");

	while (1) {
		gotoxy(20,15);
		printf("- �ð�ǥ ����� -");

		for(i=0;i<5;i++){
			gotoxy(15, 18+i*2);
			printf(" %s���� ���� ���� : ", dayOfWeek[i]);
		}

		for(i=0;i<5;i++){
			gotoxy(35,18+i*2);
			scanf("%d", &SubjectCntOfday[i]);

			//�Ϸ���񰹼��� �ʰ��� ���
			if(SubjectCntOfday[i] > 5 ) {
				gotoxy(38, 18+i*2);
				printf(" ���Ϸ��ִ���񰹼��ʰ�!");
				Sleep(1000);
				gotoxy(38, 18+i*2);
				printf("                        ");
				gotoxy(35, 18+i*2);
				printf("   ");
				i--;
			}
			else {
				subjectSum += SubjectCntOfday[i];
			}
		}

		//�Ѱ��񰹼��� �ʰ��� ���
		if(subjectSum > 13 ){
			for(i=0;i<5;i++){

				gotoxy(35, 18+i*2);
				printf("    ");
			}
			gotoxy(15, 28);
			printf(" �� �� �ִ� �����(13��)�� �ʰ��ϼ̽��ϴ�. ��\n");
			Sleep(1000);
			gotoxy(15, 28);
			printf("                                          ");
			subjectSum =0;
		}
		else {
			break;
		}
	}
	InputSubjectNameAndClass(s,SubjectCntOfday,subjectSum) ;

}

// �̸�/���� �Է��Լ�
void InputSubjectNameAndClass(structMember *s,int* SubjectCntOfday, int subjectSum) {

	int i, j, k=0, l;
	structSubject* subjectPointer; 
	int cnt=0 ,tmp=12;
	int y=0;

	subjectPointer = (structSubject*)malloc(sizeof(structSubject)*subjectSum);


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
		for(j=0; j <SubjectCntOfday[i] ; j++){


			y = j+tmp;

			gotoxy(78,y);
			scanf("%s",&subjectPointer[k].subjectName);

			gotoxy(107,y);
			scanf("%s",&subjectPointer[k].subjectClass);

			if(j+1 == SubjectCntOfday[i]){
				tmp = 3+y; 
			}

			k++;
		}
		printf("\n");
	}

	saveTimetalbe(s,subjectPointer,subjectSum);

	free(subjectPointer);
	system("cls");  

}


//�ð�ǥ ����
void modifyTimetable(structMember *s) {

	char tmp[100];
	int modifyDay[5] ={0};
	int modifySubjectN[5]={0};
	int i,j=0,cnt=0;

	fflush(stdin);

	screenBorderDraw();
	listBorderDraw();

	gotoxy(30,15);
	printf("- �ð�ǥ ���� -");

	gotoxy(15, 17);
	printf("�����Ͻ� ���� : ");

	gotoxy(30, 17);
	gets(tmp);

	for(i=0; i<5; i++) {
		if ( strstr(tmp, dayOfWeek[i]) ) { // �Է¹��� ���������� ��~�ݱ��� ���ؼ� �ش���� ���� ���� ���� �ޱ�
			gotoxy(18, 19+j*2);
			printf("%s���� ���� ���� : \n", dayOfWeek[i]);
			modifyDay[i] = i+1; //�������� 0���� ����
			j++;
		}
	}


	j=0;

	for(i=0; i<5; i++) {

		if(modifyDay[i] != 0 ) {
			gotoxy(37, 19+j*2);
			scanf("%d", &modifySubjectN[modifyDay[i]-1]);
			j++;
			cnt++;
		}
	}


	InputSubjectNameAndClass(s,modifySubjectN,cnt);

}


void removeTimetable(structMember *s) {
     

	 int nResult = remove("timetable.txt"); //�ش� ������ �����.
 
	screenBorderDraw() ;

	gotoxy(30,30);
 
 if(nResult == 0)
 {
  printf("succes");  //����� ����
 } else if (nResult == -1)
 {
  printf("fail");  //����� ����
 }


	Sleep(10000);

}