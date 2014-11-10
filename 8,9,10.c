#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

void gotoxy(int x, int y);
void printMold();
void makeTimetable_SubjectOfNumInput();
void makeTimetable_SubjectOfNameClass( int* SubjectOfday) ;
void modifyTimetable(); 
char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};

int main() {

   

   system("mode con:cols=130 lines=45");  //가로 130, 세로 45 
   //printMold() ; //틀그리기
   makeTimetable_SubjectOfNumInput(); // 시간표만들기시작
   //printMold() ;
   modifyTimetable(); //시간표수정

   

   gotoxy(50,50);
}

void gotoxy(int x, int y) { 
   COORD Cur;
   Cur.X=x;
   Cur.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

//시간표만들기 -과목갯수입력
void makeTimetable_SubjectOfNumInput() {

   int i;
   int SubjectCntOfday[5]={0};

   printMold() ;

   gotoxy(32,12);
   printf("- 시간표 만들기 -");

   for(i=0;i<5;i++){
      gotoxy(20, 15+i*2);
      printf(" %s요일 과목 갯수 : ", dayOfWeek[i]);
   }

   for(i=0;i<5;i++){
      gotoxy(40,15+i*2);
      scanf("%d", &SubjectCntOfday[i]);
   }

   system("cls");
   makeTimetable_SubjectOfNameClass(SubjectCntOfday) ;


}

//시간표만들기-과목이름/교시
void makeTimetable_SubjectOfNameClass( int* SubjectCntOfday) {

   int i, j;
   char subjectName[15];
   char subjectClass[10];
   int cnt=0 ,tmp=0;
   int y;

   for( i = 0; i < 5; i++){

      if( SubjectCntOfday[i] != 0 ) {

         printf("＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊＊＊＊＊＊\n", dayOfWeek[i]);

         for(j=0; j <SubjectCntOfday[i] ; j++){
            printf(" %d. 과목명 :                 교시 :       \n",j+1);

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

//틀 출력
void printMold() {

   int i;

   for(i=0; i<30; i++){
      gotoxy(10+i*2, 10);
      printf("■");
   }

   for(i=0;i <15; i++){
      gotoxy(10, 10+i);
      printf("■");
   }

   for(i=0;i <30; i++){
      gotoxy(10+i*2, 25);
      printf("■");
   }

   for(i=0;i <15; i++){
      gotoxy(68, 10+i);
      printf("■");
   }
}

//시간표 수정
void modifyTimetable() {

   char tmp[100];
   int modifyDay[5] ={0};
   int modifySubjectN[5]={0};
   int i,j=0;


   fflush(stdin);

   printMold() ;

   gotoxy(32,12);
   printf("- 시간표 수정 -");

   gotoxy(15, 14);
   printf("수정하실 요일 : ");

   gotoxy(31, 14);
   gets(tmp);

   for(i=0; i<5; i++) {
      if ( strstr(tmp, dayOfWeek[i]) ) {
         gotoxy(20, 16+j*2);
         printf("%s요일 과목 갯수 : \n", dayOfWeek[i]);
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
