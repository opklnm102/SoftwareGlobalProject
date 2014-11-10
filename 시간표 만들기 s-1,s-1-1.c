#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y);
void printMold();
void timetableMake_SubjectOfNumInput();
void timetableMake_SubjectOfName( int* SubjectOfday) ;
char dayOfWeek[5][4] = {"월", "화", "수", "목", "금"};

int main() {

	

	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 
	gotoxy(32,12);
	printf("- 시간표 만들기 -");
	 printMold() ;
	 timetableMake_SubjectOfNumInput();
	

	gotoxy(50,50);
}

void gotoxy(int x, int y) { 
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur); 
}

void timetableMake_SubjectOfNumInput() {

	int i;
	int SubjectOfday[5];

	for(i=0;i<5;i++){
		gotoxy(20, 15+i*2);
		printf(" %s요일 과목 갯수 : ", dayOfWeek[i]);
	}

	for(i=0;i<5;i++){
		gotoxy(40,15+i*2);
		scanf("%d", &SubjectOfday[i]);
	}

	system("cls");
	timetableMake_SubjectOfName(SubjectOfday) ;


}

void timetableMake_SubjectOfName( int* SubjectOfday) {

	int i, j;
	int SumSubject;
	char subjectName[15];
	char subjectClass[5];
	int cnt=0 ,tmp=0;
	int y;

	for( i = 0; i < 5; i++){

		printf("＊＊＊＊＊＊＊＊＊＊＊- %s요일 -＊＊＊＊＊＊＊＊＊＊＊\n", dayOfWeek[i]);

		for(j=0; j <SubjectOfday[i] ; j++){
			printf(" %d. 과목명 :			        교시 :       \n",j+1);

		}
		printf("\n");
	}



	for( i = 0; i < 5; i++){

		/*if(cnt != 0){
			if (cnt == 1) tmp = 3;
			else tmp = 4;
		}
		*/
		//cnt=0;

		for(j=0; j <SubjectOfday[i] ; j++){

			y = j+1+tmp;

			gotoxy(14,y);
			scanf("%s",&subjectName);

			gotoxy(48,y);
			scanf("%s",&subjectClass);
			//cnt++;

			if(j+1 == SubjectOfday[i]){
				tmp = y+2;
			}

		}
		printf("\n");
	}




}

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
