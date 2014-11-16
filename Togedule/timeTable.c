#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

void gotoxy(int x, int y);
void screenBorderDraw();
void listBorderDraw();
void timetableDraw();
void timetableMenu();
void makeTimetable_SubjectOfNumInput();
void makeTimetable_SubjectOfNameClass( int* SubjectCntOfday, int subjectSum) ;
void modifyTimetable();
void saveTimetalbe(Subject* subjectPointer);

char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};

typedef struct Subject{
	char dayOfWeek[4];
	char subjectName[15];
	char subjectClass[10];
}Subject;

/*//�ð�ǥ ����ü
typedef struct structTimetable{  //13���� -> 13�� �Է��ϱ� ������ 2��
   Subject timetable[5][13];  
}structTimetable;
*/
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

//�ð�ǥ�޴�

void timetableMenu() {

	int i;
	int choiceMenu;

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

	  case 1: makeTimetable_SubjectOfNumInput();  break; // �ð�ǥ��������
	  case 2: modifyTimetable(); break; //�ð�ǥ����
	//  case 3: break;

	  }
}


//�ð�ǥ����� -���񰹼��Է�
void makeTimetable_SubjectOfNumInput() {

	int i, subjectSum=0;
	int SubjectCntOfday[5]={0};


	screenBorderDraw() ;
	listBorderDraw();

	while (1) {
		gotoxy(30,15);
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
		if(subjectSum > 12 ){
			for(i=0;i<5;i++){
		
				gotoxy(35, 18+i*2);
				printf("    ");
			}
			gotoxy(15, 28);
			printf(" �� �ִ� �����(12��)�� �ʰ��ϼ̽��ϴ�. ��\n");
			Sleep(1000);
			gotoxy(15, 28);
			printf("                                          ");
			subjectSum =0;
		}
		else {
			break;
		}
	}
	makeTimetable_SubjectOfNameClass(SubjectCntOfday,subjectSum) ;

}

//�ð�ǥ�����-�����̸�/����
void makeTimetable_SubjectOfNameClass( int* SubjectCntOfday, int subjectSum) {

   int i, j, k=0;
   Subject* subjectPointer; 
   int cnt=0 ,tmp=12;
   int y;

   subjectPointer = (Subject*)malloc(sizeof(Subject)*subjectSum);

   for( i = 0; i < 5; i++){

      if( SubjectCntOfday[i] != 0 ) {
		  k++;
		  gotoxy(70,10+k);
         printf("����������������������- %s���� -����������������������\n", dayOfWeek[i]);
		 
         for(j=0; j <SubjectCntOfday[i] ; j++){
			 k++;
			 gotoxy(70,10+k);
            printf(" %d. ����� :                       ���� :       \n",j+1);
         }

		 k++;
		 gotoxy(70,10+k);
         printf("\n");
      }
   }


   for( i = 0; i < 5; i++){

      for(j=0; j <SubjectCntOfday[i] ; j++){

         y = j+tmp;

         gotoxy(83,y);
         scanf("%s",&subjectPointer[i].subjectName);

         gotoxy(112,y);
         scanf("%s",&subjectPointer[i].subjectClass);

         if(j+1 == SubjectCntOfday[i]){
				 tmp = 3+y;
		 }
	  }
       printf("\n");
   }


   saveTimetalbe(subjectPointer);


      system("cls");   
}


//�ð�ǥ ����
void modifyTimetable() {

   char tmp[100];
   int modifyDay[5] ={0};
   int modifySubjectN[5]={0};
   int i,j=0;

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
      if ( strstr(tmp, dayOfWeek[i]) ) {
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
      }
   }
 
  // makeTimetable_SubjectOfNameClass(modifySubjectN);

}

void saveTimetalbe(Subject* subjectPointer) {

	char txt[]="timetable.txt";  //Ȯ����

   char ask;  //���� ����
   FILE *fp1,*fp2;   
   char fileName[30];
   int con=1;

    strcpy(fileName,s.ID);         
         strcat(fileName,s.name);
         strcat(fileName,txt);
         fp1=fopen(fileName,"r");

		 if(fp1 == NULL){  //������ ���� ���
            fp1=fopen(fileName,"w");
            fp2=fopen("ȸ�����.txt","a");      
            fprintf(fp1,"%s\n","ȸ������");
            fprintf(fp1,"%s\n%s\n%s\n%s\n",s.ID,s.name,s.password,s.backupPassword);  //���κ� ȸ����������
            fprintf(fp2,"%s %s\n",s.ID,s.name);  //ȸ��������Ͽ� ����
            con=0;
            fclose(fp1);
            fclose(fp2);
         }
         else{  //������ ���� ���
            printf("�̹� ȸ�������ϼ̽��ϴ�.\n");
         }

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

   gotoxy(5,10);
    printf("������������������������������������������������������������");

   for(i=0; i<20; i++) { 
	   gotoxy(5,11+i);
	   printf("��                                                        ��");
   }

   gotoxy(5,30);
   printf("������������������������������������������������������������");
}

void timetableDraw(){  

   int i;   
   
   gotoxy(65,10);
    printf("��������������������������������������������������������������");
	gotoxy(65,11);
	 printf("��  ����  ��   ��   ��   ȭ   ��   ��   ��   ��   ��   ��   ��"); 
	 gotoxy(65,12);
	  printf("��������������������������������������������������������������");
  /* for(i=0; i<20; i++) { 
	   gotoxy(65,11+i);
	   printf("��                                                          ��");
   }*/

   gotoxy(65,30);
   printf("��������������������������������������������������������������");
}