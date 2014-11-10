#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

void gotoxy(int x, int y);
void printMold();
void makeTimetable_SubjectOfNumInput();
void makeTimetable_SubjectOfNameClass( int* SubjectOfday) ;
void modifyTimetable(); 
char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"};

int main() {

   

   system("mode con:cols=130 lines=45");  //���� 130, ���� 45 
   //printMold() ; //Ʋ�׸���
   makeTimetable_SubjectOfNumInput(); // �ð�ǥ��������
   //printMold() ;
   modifyTimetable(); //�ð�ǥ����

   

   gotoxy(50,50);
}

void gotoxy(int x, int y) { 
   COORD Cur;
   Cur.X=x;
   Cur.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

//�ð�ǥ����� -���񰹼��Է�
void makeTimetable_SubjectOfNumInput() {

   int i;
   int SubjectCntOfday[5]={0};

   printMold() ;

   gotoxy(32,12);
   printf("- �ð�ǥ ����� -");

   for(i=0;i<5;i++){
      gotoxy(20, 15+i*2);
      printf(" %s���� ���� ���� : ", dayOfWeek[i]);
   }

   for(i=0;i<5;i++){
      gotoxy(40,15+i*2);
      scanf("%d", &SubjectCntOfday[i]);
   }

   system("cls");
   makeTimetable_SubjectOfNameClass(SubjectCntOfday) ;


}

//�ð�ǥ�����-�����̸�/����
void makeTimetable_SubjectOfNameClass( int* SubjectCntOfday) {

   int i, j;
   char subjectName[15];
   char subjectClass[10];
   int cnt=0 ,tmp=0;
   int y;

   for( i = 0; i < 5; i++){

      if( SubjectCntOfday[i] != 0 ) {

         printf("����������������������- %s���� -����������������������\n", dayOfWeek[i]);

         for(j=0; j <SubjectCntOfday[i] ; j++){
            printf(" %d. ����� :                 ���� :       \n",j+1);

         }
         printf("\n");
      }
   }



   for( i = 0; i < 5; i++){

      for(j=0; j <SubjectCntOfday[i] ; j++){

         y = j+1+tmp;

         gotoxy(14,y);
         scanf("%s",&subjectName);

         gotoxy(48,y);
         scanf("%s",&subjectClass);


         if(j+1 == SubjectCntOfday[i]){
            tmp = y+2;
         }

      }
      printf("\n");
   }

      system("cls");   
}

//Ʋ ���
void printMold() {

   int i;

   for(i=0; i<30; i++){
      gotoxy(10+i*2, 10);
      printf("��");
   }

   for(i=0;i <15; i++){
      gotoxy(10, 10+i);
      printf("��");
   }

   for(i=0;i <30; i++){
      gotoxy(10+i*2, 25);
      printf("��");
   }

   for(i=0;i <15; i++){
      gotoxy(68, 10+i);
      printf("��");
   }
}

//�ð�ǥ ����
void modifyTimetable() {

   char tmp[100];
   int modifyDay[5] ={0};
   int modifySubjectN[5]={0};
   int i,j=0;


   fflush(stdin);

   printMold() ;

   gotoxy(32,12);
   printf("- �ð�ǥ ���� -");

   gotoxy(15, 14);
   printf("�����Ͻ� ���� : ");

   gotoxy(31, 14);
   gets(tmp);

   for(i=0; i<5; i++) {
      if ( strstr(tmp, dayOfWeek[i]) ) {
         gotoxy(20, 16+j*2);
         printf("%s���� ���� ���� : \n", dayOfWeek[i]);
         modifyDay[i] = i;
         j++;
      }
   }

   j=0;

   for(i=0; i<5; i++) {

      if(modifyDay[i] != 0 ) {
         gotoxy(40, 16+j*2);
         scanf("%d", &modifySubjectN[modifyDay[i]]);
         j++;
      }
   }

   system("cls");   
   makeTimetable_SubjectOfNameClass(modifySubjectN);

}
