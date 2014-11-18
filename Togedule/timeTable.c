#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

//���� ����ü
typedef struct Subject{
	char dayOfWeek[4]; //����
	char subjectName[15]; //�̸�
	char subjectClass[10]; //����
}Subject;

void gotoxy(int x, int y);
void timetableMenu(); //�ð�ǥ�޴��Լ�
void timetableDraw(); //�ð�ǥ�׸����Լ�
void saveTimetalbe(Subject* subjectPointer, int subjectSum); //�ð�ǥ txt�� �����ϴ� �Լ�
void InputSubjectCnt(); //��~�� ���񰹼� �Է� �Լ�
void InputSubjectNameAndClass( int* SubjectCntOfday, int subjectSum) ; // �̸�/���� �Է��Լ�
void modifyTimetable(); //�ð�ǥ�����Լ�
void screenBorderDraw(); // ��üȭ��Ʋ����Լ�
void listBorderDraw(); //�޴�Ʋ����Լ�

char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};


int main() {

	system("mode con:cols=130 lines=46");  //���� 130, ���� 45 
	timetableMenu();
	gotoxy(50,50);
}

void gotoxy(int x, int y) { 
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

//�ð�ǥ�޴��Լ�
void timetableMenu() {

	int i;
	int choiceMenu;

	while(1) {
		screenBorderDraw() ;
		listBorderDraw();
		timetableDraw();
		/*
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
		case 2: modifyTimetable(); break; //�ð�ǥ����
			//  case 3: break;

		}
		*/
	}
}

//�ð�ǥ�׸����Լ�
void timetableDraw(){  


	FILE *fp1;
	int i,j,stringCnt=0;
	int Subjectcnt;
	Subject* subjectPointer;
	int tmpClassCnt;
	int b=0;
	

	

	gotoxy(57,10); 
	printf("����������������������������������������������������������������������");
	gotoxy(57,11);
	printf("�� ���� ��    ��    ��    ȭ    ��    ��    ��    ��    ��    ��    ��"); 
	gotoxy(57,12);
	printf("����������������������������������������������������������������������");
	for(i=0; i<18; i++) { 
		gotoxy(57,13+i);
		printf("��  %2d  ��                                                          ��",i+1);
	}
	gotoxy(57,30);
	printf("����������������������������������������������������������������������");

	

	//timetable.txt�� �ִ� ���

	fp1=fopen("timetable.txt","r");
	fscanf(fp1, "%d", &Subjectcnt);

	subjectPointer = (Subject*)malloc(sizeof(Subject)*Subjectcnt);

	for(i=0;i<Subjectcnt;i++) 
	fscanf(fp1,"%s %s %s", subjectPointer[i].dayOfWeek, subjectPointer[i].subjectName, subjectPointer[i].subjectClass);



	//58,13
	for(j=0;j<5;j++) {
		for(i=0;i<Subjectcnt;i++) {
			if( strstr(subjectPointer[i].dayOfWeek, dayOfWeek[j]) ) {

				/*for(k=1;k<=13; k++ ) {
					
				}*/

				while( subjectPointer[i].dayOfWeek[stringCnt++] != '\0' ) {
					if(subjectPointer[i].subjectClass[stringCnt] >= '0' && subjectPointer[i].subjectClass[stringCnt] <='9'){
						tmpClassCnt =  subjectPointer[i].subjectClass[stringCnt] - 48;
					}

					gotoxy(58,13+b);
					b++;
					printf("%s",subjectPointer[i].subjectName);
				}
				
			}

		}
	}
	

	



}

//�ð�ǥ txt�� �����ϴ� �Լ�
void saveTimetalbe(Subject* subjectPointer, int subjectSum) {

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
void InputSubjectCnt() {

	int i, subjectSum=0;
	int SubjectCntOfday[5]={0};

	screenBorderDraw() ;
	listBorderDraw();

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
	InputSubjectNameAndClass(SubjectCntOfday,subjectSum) ;

}

// �̸�/���� �Է��Լ�
void InputSubjectNameAndClass(int* SubjectCntOfday, int subjectSum) {

	int i, j, k=0, l;
	Subject* subjectPointer; 
	int cnt=0 ,tmp=12;
	int y=0;

	subjectPointer = (Subject*)malloc(sizeof(Subject)*subjectSum);


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

	saveTimetalbe(subjectPointer,subjectSum);

	free(subjectPointer);
	system("cls");  

}


//�ð�ǥ ����
void modifyTimetable() {

	char tmp[100];
	int modifyDay[5] ={0};
	int modifySubjectN[5]={0};
	int i,j=0,cnt=0;

	fflush(stdin);

	screenBorderDraw() ;
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


	InputSubjectNameAndClass(modifySubjectN,cnt);

}



//Ʋ ���
void screenBorderDraw(){

	int i;

	printf("������������������������������������������������������������������");

	for(i=0;i<44;i++){
		gotoxy(0,i+1);
		printf("��                                                                                                                              ��");
	}

	gotoxy(0,44);
	printf("������������������������������������������������������������������");

	gotoxy(88,41);
	printf("�ڷΰ��� B, ���� X, ����ϱ� S");


}

void listBorderDraw(){  

	int i;   

	gotoxy(3,10);
	printf("������������������������������������������������������");

	for(i=0; i<20; i++) { 
		gotoxy(3,11+i);
		printf("��                                                  ��");
	}

	gotoxy(3,30);
	printf("������������������������������������������������������");
}

