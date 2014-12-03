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
	char openDB[30];
	char check[41];
	int listCount=0;
	int x=5, y=9;
	int i;
	int numbering=1;
	char controlList[3]={0};
	structPromise *Promise;  //약속리스트를 읽을 구조체

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
			gotoxy(x+11,y+1); printf("약속명      ");
			fscanf(fp, "%s", &check);  //약속리스트인지 check
			if(!strcmp(check,"약속리스트")){
				fscanf(fp,"%d", &listCount);  //리스트의 갯수 읽기
				Promise=(structPromise*)malloc(sizeof(structPromise)*listCount);  //리스트 수만큼 할당

				for(i=0; i<listCount; i++){  //약속명 읽기
					fscanf(fp,"%s", Promise[i].promiseName);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fscanf(fp,"%s", check);
					fgets(check,41,fp);			//비용들어갈 자리 추가.
					fgets(check,41,fp);
				}
			}
		}

		for(i=0; i<listCount; i++) {	
				if(i==10){
						gotoxy(8,36); printf("다음리스트를 보려면 >키를 입력하세요.");
						while(1){
							gotoxy(46,36);scanf("%s",&controlList);
							if(!strcmp(controlList,">"))
								break;
							gotoxy(46,36);printf("     ");
						}
						if(!strcmp(controlList,">")){
							promiselistBorderDraw(3,7);  //약속리스트 틀
							gotoxy(x+11,y+1); printf("약속명      ");
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(8,36);printf("                                               ");						

					}
					else if(i!=0&&i!=5&&i%10==0&&i+1!=listCount){
						gotoxy(8,36);printf("이전리스트 <, 다음리스트 >");
						while(1){
							gotoxy(46,36);scanf("%s",&controlList);
							if(!strcmp(controlList,"<")||!strcmp(controlList,">"))
								break;
							
							gotoxy(46,36);printf("     ");
						}
						if(!strcmp(controlList,">")){
							promiselistBorderDraw(3,7);  //약속리스트 틀
							gotoxy(x+11,y+1); printf("약속명      ");
							strcpy(controlList,"\0");
						}
						else if(!strcmp(controlList,"<")){
							promiselistBorderDraw(3,7);  //약속리스트 틀
						gotoxy(x+11,y+1); printf("약속명      ");
							i=i-20;
							numbering=numbering-10;
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(8,36);printf("                                               ");
					}
					
					gotoxy(x+5,y+3+2*(i%10));printf("%2d     %-20s ",numbering,Promise[i].promiseName);
					numbering++;
					if(i+1==listCount&&listCount>5){
						gotoxy(8,36);printf("처음으로 돌아가려면 <키를 입력하세요.");
						while(1){
							gotoxy(46,36);scanf("%s",&controlList);
							if(!strcmp(controlList,"<"))
								break;
							gotoxy(46,36);printf("     ");
						}						
						if(!strcmp(controlList,"<")){
							promiselistBorderDraw(3,7);  //약속리스트 틀(35,11);	
							gotoxy(x+11,y+1); printf("약속명      ");
							i=-1;
							numbering=1;
							strcpy(controlList,"\0");
						}
						
						gotoxy(8,36);printf("                                               ");
					}
				}






		fclose(fp);
	}
}




