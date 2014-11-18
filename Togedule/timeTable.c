#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

//과목 구조체
typedef struct Subject{
	char dayOfWeek[4]; //요일
	char subjectName[15]; //이름
	char subjectClass[10]; //교시
}Subject;

void gotoxy(int x, int y);
void timetableMenu(); //시간표메뉴함수
void timetableDraw(); //시간표그리기함수
void saveTimetalbe(Subject* subjectPointer, int subjectSum); //시간표 txt로 저장하는 함수
void InputSubjectCnt(); //월~금 과목갯수 입력 함수
void InputSubjectNameAndClass( int* SubjectCntOfday, int subjectSum) ; // 이름/교시 입력함수
void modifyTimetable(); //시간표수정함수
void removeTimetable(); //시간표삭제함수(시간표txt파일삭제)
void screenBorderDraw(); // 전체화면틀출력함수
void listBorderDraw(); //메뉴틀출력함수

char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};


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

//시간표메뉴함수
void timetableMenu() {

	int i;
	int choiceMenu;

	while(1) {
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

		case 1: InputSubjectCnt();  break; // 시간표만들기시작
		case 2: modifyTimetable(); break; //시간표수정
		case 3: removeTimetable(); break; //시간표삭제

		}
		
	}
}

//시간표그리기함수
void timetableDraw(){  


	FILE *fp1;
	int i,j,stringCnt=0;
	int Subjectcnt;
	Subject* subjectPointer;
	int tmpClassCnt;
	int b=0;
	

	gotoxy(57,7); 
	printf("┌───┬─────┬─────┬─────┬─────┬─────┐");
	gotoxy(57,8);
	printf("│ 교시 │    월    │    화    │    수    │    목    │    금    │"); 
	gotoxy(57,9);
	printf("├───┼─────┼─────┼─────┼─────┼─────┤");
	for(i=0; i<26; i+=2) { 
		gotoxy(57,10+i);
		printf("│  %2d  │          │          │          │          │          │",i/2+1);
		gotoxy(57,10+i+1);
		if(i!= 24)
		printf("├───┼─────┼─────┼─────┼─────┼─────┤");
	}
	gotoxy(57,35);
	printf("└───┴─────┴─────┴─────┴─────┴─────┘");

	fp1=fopen("timetable.txt","r");

	if(fp1 == NULL ) {
		gotoxy(83,20);
		printf("*시간표를 만들어주세요*");
	}
	//timetable.txt가 있는 경우
	else {
	
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

//시간표 txt로 저장하는 함수
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



//시간표 월~금 과목갯수 입력 함수
void InputSubjectCnt() {

	int i, subjectSum=0;
	int SubjectCntOfday[5]={0};

	screenBorderDraw() ;
	listBorderDraw();

	gotoxy(6, 31);
	printf("** 하루 최대과목 갯수는 5개이하.");
	gotoxy(6, 32);
	printf("**  총 최대과목 갯수는 13개 이하.");

	while (1) {
		gotoxy(20,15);
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
		if(subjectSum > 13 ){
			for(i=0;i<5;i++){

				gotoxy(35, 18+i*2);
				printf("    ");
			}
			gotoxy(15, 28);
			printf(" ※ 총 최대 과목수(13개)를 초과하셨습니다. ※\n");
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

// 이름/교시 입력함수
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
			printf("*＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊*＊＊＊＊＊\n", dayOfWeek[i]);


			for(j=0; j <SubjectCntOfday[i] ; j++){
				// 과목 구조체에 시간표 요일 입력
				strcpy(subjectPointer[k].dayOfWeek,dayOfWeek[i]);
				k++;

				y++;
				gotoxy(65,10+y);
				printf(" %d. 과목명 :                       교시 :       \n",j+1);
			}

			y++;
			gotoxy(65,10+y);
			printf("\n");
		}
	}

	//이름/교시 입력 조건문
	gotoxy(65, 31);
	printf("** 과목명은 5자이내.");
	gotoxy(65, 32);
	printf("** ex) 교시 : 1,2,3 으로 입력.");

	k=0;

	//과목 이름/교시 입력
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


//시간표 수정
void modifyTimetable() {

	char tmp[100];
	int modifyDay[5] ={0};
	int modifySubjectN[5]={0};
	int i,j=0,cnt=0;

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
		if ( strstr(tmp, dayOfWeek[i]) ) { // 입력받은 수정요일을 월~금까지 비교해서 해당요일 별로 과목 갯수 받기
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
			cnt++;
		}
	}


	InputSubjectNameAndClass(modifySubjectN,cnt);

}


void removeTimetable() {
     

	 int nResult = remove("timetable.txt"); //해당 파일을 지운다.
 
	screenBorderDraw() ;

	gotoxy(30,30);
 
 if(nResult == 0)
 {
  printf("succes");  //지우기 성공
 } else if (nResult == -1)
 {
  printf("fail");  //지우기 실패
 }


	Sleep(10000);

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

	gotoxy(3,10);
	printf("┌─────────────────────────┐");

	for(i=0; i<20; i++) { 
		gotoxy(3,11+i);
		printf("│                                                  │");
	}

	gotoxy(3,30);
	printf("└─────────────────────────┘");
}

