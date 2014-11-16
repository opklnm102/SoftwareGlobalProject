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

char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};

typedef struct Subject{
	char dayOfWeek[4];
	char subjectName[15];
	char subjectClass[10];
}Subject;

/*//시간표 구조체
typedef struct structTimetable{  //13교시 -> 13을 입력하기 때문에 2개
   Subject timetable[5][13];  
}structTimetable;
*/
int main() {

   system("mode con:cols=130 lines=46");  //가로 130, 세로 45 
   timetableMenu();
   gotoxy(50,50);
}

void gotoxy(int x, int y) { 
   COORD Cur;
   Cur.X=x;
   Cur.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

//시간표메뉴

void timetableMenu() {

	int i;
	int choiceMenu;

   screenBorderDraw() ;
   listBorderDraw();
   timetableDraw();

      gotoxy(20, 18);
      printf(" 1. 시간표 만들기 ");
	  gotoxy(20,20);
	  printf(" 2. 시간표 수  정 ");
	  gotoxy(20,22);
	  printf(" 3. 시간표 삭  제 ");
	   gotoxy(20,24);
	  printf(">> ");
	  scanf("%d", &choiceMenu);

	  switch (choiceMenu) {

	  case 1: makeTimetable_SubjectOfNumInput();  break; // 시간표만들기시작
	  case 2: modifyTimetable(); break; //시간표수정
	//  case 3: break;

	  }
}


//시간표만들기 -과목갯수입력
void makeTimetable_SubjectOfNumInput() {

	int i, subjectSum=0;
	int SubjectCntOfday[5]={0};


	screenBorderDraw() ;
	listBorderDraw();

	while (1) {
		gotoxy(30,15);
		printf("- 시간표 만들기 -");

		for(i=0;i<5;i++){
			gotoxy(15, 18+i*2);
			printf(" %s요일 과목 갯수 : ", dayOfWeek[i]);
		}

		for(i=0;i<5;i++){
			gotoxy(35,18+i*2);
			scanf("%d", &SubjectCntOfday[i]);

			//하루과목갯수가 초과할 경우
			if(SubjectCntOfday[i] > 5 ) {
				gotoxy(38, 18+i*2);
				printf(" ◀하루최대과목갯수초과!");
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
		
		//총과목갯수가 초과할 경우
		if(subjectSum > 12 ){
			for(i=0;i<5;i++){
		
				gotoxy(35, 18+i*2);
				printf("    ");
			}
			gotoxy(15, 28);
			printf(" ※ 최대 과목수(12개)를 초과하셨습니다. ※\n");
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

//시간표만들기-과목이름/교시
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
         printf("＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊＊＊＊＊＊\n", dayOfWeek[i]);
		 
         for(j=0; j <SubjectCntOfday[i] ; j++){
			 k++;
			 gotoxy(70,10+k);
            printf(" %d. 과목명 :                       교시 :       \n",j+1);
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


//시간표 수정
void modifyTimetable() {

   char tmp[100];
   int modifyDay[5] ={0};
   int modifySubjectN[5]={0};
   int i,j=0;

   fflush(stdin);

   screenBorderDraw() ;
   listBorderDraw();

   gotoxy(30,15);
   printf("- 시간표 수정 -");

   gotoxy(15, 17);
   printf("수정하실 요일 : ");

   gotoxy(30, 17);
   gets(tmp);

   for(i=0; i<5; i++) {
      if ( strstr(tmp, dayOfWeek[i]) ) {
          gotoxy(18, 19+j*2);
         printf("%s요일 과목 갯수 : \n", dayOfWeek[i]);
         modifyDay[i] = i+1; //월요일이 0부터 시작
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

	char txt[]="timetable.txt";  //확장자

   char ask;  //저장 여부
   FILE *fp1,*fp2;   
   char fileName[30];
   int con=1;

    strcpy(fileName,s.ID);         
         strcat(fileName,s.name);
         strcat(fileName,txt);
         fp1=fopen(fileName,"r");

		 if(fp1 == NULL){  //파일이 없을 경우
            fp1=fopen(fileName,"w");
            fp2=fopen("회원목록.txt","a");      
            fprintf(fp1,"%s\n","회원정보");
            fprintf(fp1,"%s\n%s\n%s\n%s\n",s.ID,s.name,s.password,s.backupPassword);  //개인별 회원정보파일
            fprintf(fp2,"%s %s\n",s.ID,s.name);  //회원목록파일에 갱신
            con=0;
            fclose(fp1);
            fclose(fp2);
         }
         else{  //파일이 있을 경우
            printf("이미 회원가입하셨습니다.\n");
         }

}

//틀 출력
void screenBorderDraw(){

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

void listBorderDraw(){  

   int i;   

   gotoxy(5,10);
    printf("┌────────────────────────────┐");

   for(i=0; i<20; i++) { 
	   gotoxy(5,11+i);
	   printf("│                                                        │");
   }

   gotoxy(5,30);
   printf("└────────────────────────────┘");
}

void timetableDraw(){  

   int i;   
   
   gotoxy(65,10);
    printf("┌─────────────────────────────┐");
	gotoxy(65,11);
	 printf("│  교시  │   월   │   화   │   수   │   목   │   금   │"); 
	 gotoxy(65,12);
	  printf("└─────────────────────────────┘");
  /* for(i=0; i<20; i++) { 
	   gotoxy(65,11+i);
	   printf("│                                                          │");
   }*/

   gotoxy(65,30);
   printf("└─────────────────────────────┘");
}