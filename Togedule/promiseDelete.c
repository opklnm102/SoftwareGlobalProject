#include "structHeader.h"

int deleteAllPromise(char *DBname,char *logID) {
	FILE *fp;
	char openDB[30];
	char textFile[]=".txt";
	char check[41];
	struct structPromise *oldPromise;
	int listCount=0;
	int i,j,k;
	int numbering=1;
	char **friendsName;
	char **cost;
	char select[3]={0};
	int listnumber=0;
	int length;
	char **transName;
	char ID[8];
	char listName[13];
	char blank[1]={0};
	int CombineTimetable[5][13]={0};
	char friendNameCopy[8]={0};	
	char checkPlace[3]={0};
	int x=35,y=11;
	char controlList[3]={0};
	screenBorderDraw();	
	gotoxy(56,6); printf("☆ 약속삭제 ☆");
	gotoxy(54,8); printf("- 나의 약속리스트 -");
	listBorderDraw2(x,y);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(x+12,y+1); printf("현재 생성된 약속리스트가 없습니다.");
		Sleep(1000);
		return 0;
	}
	while (!feof(fp)) {			//약속리스트 열어서 리스트에 적혀진 개수만큼 이름과 날짜를 읽어서 출력하는 부분
		
		gotoxy(x+8,y+1); printf("약속명                      약속날짜");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"약속리스트")){
			fscanf(fp,"%d", &listCount);

			oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*listCount);		//읽어온 약속을 저장하기위한 약속구조체
			for(i=0; i<listCount; i++) {															//약속저장을 할때와는 달리 이번에는 학번도 하나씩 다 읽어서 현재 이 약속을 공유하는 회원파일을 각각 처리해야함으로 
				oldPromise[i].promiseFriendsName=(char**)malloc(sizeof(char*)*4+1);					//동적할당을 promiseFriendsName에도 해준다. 
					for(j=0; j<4; j++) {													
						oldPromise[i].promiseFriendsName[j]=(char*)malloc(sizeof(char)*8);
						strcpy(oldPromise[i].promiseFriendsName[j],"\0");
						for(k=0; k<8; k++)
							strcpy(&oldPromise[i].promiseFriendsName[j][k],"\0");
					}
			}


			friendsName=(char**)malloc(sizeof(char*)*listCount);									//일단 학번이 한줄단위로 줄줄이 써있으니 그것을 읽어오는 문자열을 하나 동적할당한다.
			for(i=0; i<listCount; i++) {
				friendsName[i]=(char*)malloc(sizeof(char)*60);
				strcpy(friendsName[i],"\0");
					for(j=0; j<60; j++)
						strcpy(&friendsName[i][j],"\0");
			}

			cost=(char**)malloc(sizeof(char*)*listCount);						//비용은 약속수정에서 안쓰이는 정보이므로 그냥 읽어주기만 한다.. 필요없음
			for(i=0; i<listCount; i++) {													
				cost[i]=(char*)malloc(sizeof(char)*10);
				strcpy(cost[i],"\0");
					for(j=0; j<10; j++)
						strcpy(&cost[i][j],"\0");
			}

			for(i=0; i<listCount; i++) {								//일단 약속리스트개수만큼 약속을 읽어와서 oldPromise구조체에 순서대로 저장
				fscanf(fp,"%s",&oldPromise[i].promiseName);
				fflush(stdin);
				fgets(check,40,fp);						
				fgets(check,40,fp);					
				strcpy(oldPromise[i].promisePlace,check);						
				fscanf(fp,"%s",&oldPromise[i].promiseTime);
				fscanf(fp,"%s",&oldPromise[i].Promisedate);
				fscanf(fp,"%s",&check);
				strcpy(friendsName[i],check);
				fgets(check,40,fp);
				fgets(check,40,fp);
				strcpy(cost[i],check);
			}
			for(i=0; i<listCount; i++) {	
				if(i==5){
						gotoxy(35,10); printf("다음리스트를 보려면 >키를 입력하세요. 번호를 선택하려면 @키를 입력하세요.");
						while(1){
							gotoxy(110,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"@")||!strcmp(controlList,">"))
								break;
							gotoxy(110,10);printf("     ");
						}
						if(!strcmp(controlList,"@")){
							strcpy(controlList,"\0");
							break;							
						}
						else if(!strcmp(controlList,">")){
							listBorderDraw2(35,11);
							gotoxy(x+8,y+1); printf("약속명                      약속날짜");
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(35,10);printf("                                                                                  ");
						

					}
					else if(i!=0&&i!=5&&i%5==0&&i+1!=listCount){
						gotoxy(35,10);printf("이전리스트 <, 다음리스트 >, 번호를 선택하려면 @키를 입력하세요.");
						while(1){
							gotoxy(100,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"@")||!strcmp(controlList,"<")||!strcmp(controlList,">"))
								break;
							
							gotoxy(100,10);printf("     ");
						}
						if(!strcmp(controlList,"@")){
							strcpy(controlList,"\0");
							break;
						}
						else if(!strcmp(controlList,">")){
							listBorderDraw2(35,11);
							gotoxy(x+8,y+1); printf("약속명                      약속날짜");
							strcpy(controlList,"\0");
						}
						else if(!strcmp(controlList,"<")){
							listBorderDraw2(35,11);
							gotoxy(x+8,y+1); printf("약속명                      약속날짜");
							i=i-10;
							numbering=numbering-10;
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(35,10);printf("                                                                                  ");
					}
					
					gotoxy(x+5,y+3+2*(i%5));printf("%d  %s ",numbering,oldPromise[i].promiseName);
					gotoxy(x+38,y+3+2*(i%5));printf("%s\n",oldPromise[i].Promisedate);
					numbering++;
					if(i+1==listCount&&listCount>5){
						gotoxy(35,10);printf("처음으로 돌아가려면 <키를 입력하세요.번호를 선택하려면 @키를 입력하세요.");
						while(1){
							gotoxy(110,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"@")||!strcmp(controlList,"<"))
								break;
							gotoxy(110,10);printf("     ");
						}
						if(!strcmp(controlList,"@")){
							strcpy(controlList,"\0");
							break;
						}
						else if(!strcmp(controlList,"<")){
							listBorderDraw2(35,11);	
							gotoxy(x+8,y+1); printf("약속명                      약속날짜");
							i=-1;
							numbering=1;
							strcpy(controlList,"\0");
						}
						
						gotoxy(35,10);printf("                                                                                  ");
					}
				}
		}
	}
	fclose(fp);
	gotoxy(35,10);printf("                                                                                     ");
	gotoxy(35,25);printf("→ 삭제하실 약속 : ");
	while(1) {						//리스트 번호 범위 내의 수만 입력받기
		gotoxy(54,25);scanf("%s",select);
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<=numbering)
			break;
		gotoxy(35,26);printf("리스트 내의 번호를 입력하세요");
		gotoxy(54,25);printf("       ");
	}
	listnumber--;

	length=strlen(friendsName[listnumber]);			//줄단위로 읽은 학번들을 7자씩 끊어서 미리 할당해놓은 promiseFriendsName에 하나씩 넣어주는 부분
	for(i=0; i<4; i++) {							//여기서도 굳이 회원수를 체크하려면 귀찮으니 4번 반복실행하도록 만듬, 자신포함 최대 5명이므로 저장되는 다른 회원정보는 4명
		strncpy(oldPromise[listnumber].promiseFriendsName[i],friendsName[listnumber],7);
		for(j=0; j<7; j++)
			changeLocation(friendsName[listnumber]);
		if(strncmp(friendsName[listnumber],",",1)==0)
			changeLocation(friendsName[listnumber]);
		else
			break;		
	}
	
	transName=(char**)malloc(sizeof(char*)*4+1);					//학번을 그냥 쓸수 없으니 이름으로 바꿀 문자배열을 또 동적할당 해준다.
	for(i=0; i<4; i++) {													
		transName[i]=(char*)malloc(sizeof(char)*13);
		strcpy(transName[i],"\0");
		for(j=0; j<13; j++)
			strcpy(&transName[i][j],"\0");
	}

	strcpy(openDB,"회원목록.txt");						//학번을 이름으로 바꿔준다. 회원목록 txt를 5번동안 열고 닫고 하며 반복... 회원 숫자를 계산하기 귀찮으므로 그냥 5번 반복
	for(i=0;i<4;i++){
		fp = fopen(openDB, "r");
		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &ID, &listName);										//학번과 이름을 한줄 읽는다.
			if(!strcmp(ID,oldPromise[listnumber].promiseFriendsName[i])){				//검색할 학번과 같은 학번이면
				strcpy(transName[i],listName);											//transName 문자배열에 현재 읽은 이름을 복사
				break;
			}
		}
		fclose(fp);
	}
	
	j=0;
	for(i=0;i<4;i++){
		if(!strcmp(transName[i],"\0"))
			break;
		strcpy(openDB,oldPromise[listnumber].promiseFriendsName[i]);
		strcat(openDB,transName[i]);
		j++;
		k=recordCombineTimetable(CombineTimetable,openDB);

	}
	itoa(j,oldPromise[listnumber].promiseFreindsCount,10);
	oldPromise[listnumber].promisePlace[strlen(oldPromise[listnumber].promisePlace)-1]=blank[0];           //장소DB에서 읽어올때 \n 하나 들어있는거 없애서 자동줄바꿈 방지

	listBorderDraw2(35,26);

	gotoxy(38,28);printf("약속명 >>     %s",oldPromise[listnumber].promiseName);
	gotoxy(38,30);printf("장소   >>     %s",oldPromise[listnumber].promisePlace);
	gotoxy(38,32);printf("날짜   >>     %s",oldPromise[listnumber].Promisedate);
	gotoxy(38,34);printf("시간   >>     %s",oldPromise[listnumber].promiseTime);
	gotoxy(38,36);printf("함께할친구 >>   ");

	for(i=0; i<4; i++)
		printf("%s ",transName[i]);
	gotoxy(38,40);printf("정말 삭제하시겠습니까? <Y,N>");
	gotoxy(67,40);scanf("%s",&select);
	
	for(i=0; i<j; i++) {
		deletePromise(oldPromise[listnumber].promiseFriendsName[i],oldPromise[listnumber].promiseName,oldPromise[listnumber].Promisedate,oldPromise[listnumber].promiseTime);
	}
	deletePromise(logID,oldPromise[listnumber].promiseName,oldPromise[listnumber].Promisedate,oldPromise[listnumber].promiseTime);
	return 1;
}