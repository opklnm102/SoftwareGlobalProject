#include"structHeader.h"

void mystatus(structMember *s){
	char DBname[20];  //파일명

	strcpy(DBname,s->ID);
	strcat(DBname,s->name);	


	screenBorderDraw() ;  //화면그리기
	promiselistBorderDraw(3,7);  //약속리스트 틀

	gotoxy(20,5);
	printf("--나의 약속리스트--");
	gotoxy(85,5);
	printf("--현재시간표--");
	timetableDraw(s);  //시간표 출력
	mystatus_promiseList(DBname);  //약속리스트 출력

	getch();
}

void promiselistBorderDraw(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("┌─────────────────────────┐");

	for(i=0; i<27; i++){ 
		gotoxy(x,y+1+i);
		printf("│                                                  │");
	}

	gotoxy(x,y+28);
	printf("└─────────────────────────┘");
}

void mystatus_promiseList(char *DBname){
	FILE *fp;
	char textFile[]=".txt";
	char promiseName[41];
	char openDB[30];
	char check[41];
	int listCount=0;
	int x=10, y=9;
	int i;

	strcpy(openDB,DBname);  //약속리스트 파일 open
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(13,20);
		printf("현재 생성된 약속리스트가 없습니다.");
	}
	else{
		while (!feof(fp)) {	
			fscanf(fp, "%s", &check);
			if(!strcmp(check,"약속리스트")){
				fscanf(fp,"%d", &listCount);
				for(i=0; i<listCount; i++){
					fscanf(fp,"%s", promiseName);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fscanf(fp,"%s", check);
					fgets(check,41,fp);			//비용들어갈 자리 추가.
					fgets(check,41,fp);
					gotoxy(x,y);printf("%d. %-12s",i+1,promiseName);  //약속이름,날짜출력
					y=y+3;  //줄바꿈
				}
			}
		}
		fclose(fp);
	}
}




