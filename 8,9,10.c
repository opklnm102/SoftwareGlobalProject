#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

void gotoxy(int x, int y);
void printMold();
void makeTimetable_SubjectOfNumInput();
void makeTimetable_SubjectOfNameClass( int* SubjectOfday) ;
void modifyTimetable();
void list_border_draw(int x,int y,int width,int height);
char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};

int main() {


   system("mode con:cols=130 lines=46");  //가로 130, 세로 45 
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
   int x=71,y=23;
   

   printMold() ;
   list_border_draw(x-36,y-12,30,20);

   gotoxy(58,15);
   printf("- 시간표 만들기 -");

   for(i=0;i<5;i++){
      gotoxy(50, 19+i*2);
      printf(" %s요일 과목 갯수 : ", dayOfWeek[i]);
   }

   for(i=0;i<5;i++){
      gotoxy(70,19+i*2);
      scanf("%d", &SubjectCntOfday[i]);
   }

   system("cls");
   makeTimetable_SubjectOfNameClass(SubjectCntOfday) ;


}

//시간표만들기-과목이름/교시
void makeTimetable_SubjectOfNameClass( int* SubjectCntOfday) {

   int i, j, k=0;
   char subjectName[15];
   char subjectClass[10];
   int cnt=0 ,tmp=12;
   int y;

   printMold() ;

   for( i = 0; i < 5; i++){

      if( SubjectCntOfday[i] != 0 ) {
		  k++;
		  gotoxy(40,10+k);
         printf("＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊＊＊＊＊＊\n", dayOfWeek[i]);
		 
         for(j=0; j <SubjectCntOfday[i] ; j++){
			 k++;
			 gotoxy(40,10+k);
            printf(" %d. 과목명 :                       교시 :       \n",j+1);

         }
		 k++;
		 gotoxy(40,10+k);
         printf("\n");
      }
   }


   for( i = 0; i < 5; i++){

      for(j=0; j <SubjectCntOfday[i] ; j++){

         y = j+tmp;

		  
         gotoxy(54,y);
         scanf("%s",&subjectName);

         gotoxy(82,y);
         scanf("%s",&subjectClass);


         if(j+1 == SubjectCntOfday[i]){
           
				 tmp = 3+y;
		 }
		
	  }
       printf("\n");

   }

      system("cls");   
}


//시간표 수정
void modifyTimetable() {

   char tmp[100];
   int modifyDay[5] ={0};
   int modifySubjectN[5]={0};
   int i,j=0;
   int x=71,y=23;


   fflush(stdin);

   printMold() ;
   printMold() ;
   list_border_draw(x-36,y-12,30,20);

   gotoxy(58,15);
   printf("- 시간표 수정 -");

   gotoxy(42, 19);
   printf("수정하실 요일 : ");

   gotoxy(58, 19);
   gets(tmp);

   for(i=0; i<5; i++) {
      if ( strstr(tmp, dayOfWeek[i]) ) {
          gotoxy(44, 21+j*2);
         printf("%s요일 과목 갯수 : \n", dayOfWeek[i]);
         modifyDay[i] = i;
         j++;

      }
   }

   j=0;

   for(i=0; i<5; i++) {

      if(modifyDay[i] != 0 ) {
         gotoxy(63, 21+j*2);
         scanf("%d", &modifySubjectN[modifyDay[i]]);
         j++;
      }
   }

   system("cls");   
   makeTimetable_SubjectOfNameClass(modifySubjectN);

}


//틀 출력
void printMold() {

	int i;

	

	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	
	for(i=0;i<44;i++){
		gotoxy(0,i+1);
		printf("■                                                                                                                              ■");
	}

	gotoxy(0,44);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(88,41);
   printf("뒤로가기 B, 종료 X, 계속하기 S");


}

void list_border_draw(int x,int y,int width,int height){  
   int i,j;   

   gotoxy(x,y);  //시작좌표   
   i=y;
   while(i<y+height){ //세로
      j=x;
      gotoxy(j,i+1);
      while(j<x+width){  //가로
         if(i==y && j==x)  //왼쪽위 구석
            printf("%s","┌");
         else if(i==y && j==x+width-1)  //오른쪽위 구석
            printf("%s","┐");
         else if(i==y+height-1 && j==x)  //왼쪽아래 구석
            printf("%s","└");
         else if(i==y+height-1 && j==x+width-1)  //오른쪽 아래 구석
            printf("%s","┘");
         else if(i==y || i==y+height-1)  //가로 그리기
            printf("%s","─");
         else if(j==x || j==x+width-1)  //세로 그리기
            printf("%s","│");
         else
            printf("  ");
         j++;
      }
      i++;
   }
}
