#include "structHeader.h"

void changePlace(char *DBname, struct structPromise *old) {

	char blank[1]={0};
	promisePlace(DBname,old);

}

void changeTime(struct structPromise *old,int newCombineTimetable[5][13],int dayofweek) {
	int i,j;
	char dayofWeek[5];
	int x=-34,y=10;
	system("cls");
	screenBorderDraw();
	gotoxy(53,8); printf("☆ 약속 시간수정 ☆");
	gotoxy(x+60,y+3);printf(" 월   화   수   목   금");
	for(j=0; j<13; j++) {		//통합시간표를 출력 (임시). 시간표 출력하는 부분과 연관해서 제대로 표를 짜서 출력해야함
		for (i=0; i<5; i++){
			if(newCombineTimetable[i][j]==1){
				gotoxy(x+60+(5*i),y+4+j);printf("■■ ",newCombineTimetable[i][j]);
			}
			if(newCombineTimetable[i][j]==0){
				gotoxy(x+60+(5*i),y+4+j);printf("□□ ",newCombineTimetable[i][j]);
			}
		}
	}
	switch(dayofweek){		//weekday함수사용, 해당 연도 월 일에 해당하는 요일을 계산해서 삽입.
	case 0: strcpy(dayofWeek,"월"); break;
	case 1: strcpy(dayofWeek,"화"); break;
	case 2: strcpy(dayofWeek,"수"); break;
	case 3: strcpy(dayofWeek,"목"); break;
	case 4: strcpy(dayofWeek,"금"); break;
	}
	gotoxy(x+60,y+18);printf("현재 저장된 약속요일>> %s\n",dayofWeek);
	gotoxy(x+60,y+19);printf("현재 저장된 약속시간>> %s\n",old->promiseTime);
	selectTime(newCombineTimetable,old,dayofweek);
}

int changeDate(struct structPromise *old,int newCombineTimetable[5][13]) {
	int dayofweek;
	int time;
	dayofweek=selectDate(newCombineTimetable,old);
	time=atoi(old->promiseTime);
	if(newCombineTimetable[dayofweek][time-1]==1) {
		gotoxy(26,34);printf("현재 정해진 시간에는 약속을 잡을 수 없습니다. 시간을 수정하겠습니다.\n");
		Sleep(2000);
		changeTime(old,newCombineTimetable,dayofweek);
	}
	return dayofweek;
}

void changePromiseName(struct structPromise *old){
	gotoxy(61,26);printf("                               ");
	gotoxy(61,26);scanf("%s",&old->promiseName);
}

int checkDateTime(int CombineTimetable[5][13], struct structPromise *old){
	char month[3]={0};
	char date[3];
	int i;
	char Date[10];
	char stime[10];
	char slash[1]={'/'};
	int year;
	int Month,Day,Time;
	int dayofweek;
	time_t curr;

	struct tm *d;
	curr=time(NULL);
	d=localtime(&curr);
	year = d->tm_year;
	year=year+1900;

	strcpy(Date,old->Promisedate);
	for(i=0;i<strlen(Date);i++) {			
		if(strncmp(Date,slash,1)!=0){		
			strncat(month,Date,1);			
			changeLocation(Date);			
		}
		if(strncmp(Date,slash,1)==0) {		
			changeLocation(Date);			
			strcpy(date,Date);
		}		
	}						
	
	Month=atoi(month);
	Day=atoi(date);
	dayofweek=weekday(year,Month,Day);
	strcpy(stime,old->promiseTime);
	Time=atoi(stime);

	if(CombineTimetable[dayofweek][Time-1]==1)
		return -1;
	return 0;
}

int changeName(char *DBname,int CombineTimetable[5][13],int newCombineTimetable[5][13] ,struct structPromise *old){
	int count;
	int check;
	int x=26,y=12;
	system("cls");
	screenBorderDraw();
	gotoxy(53,8); printf("☆ 약속 멤버수정 ☆");
	gotoxy(x+50,y); printf(" 인원수 : ");
	gotoxy(x,y+4);printf(" 이름검색 : ");
	gotoxy(x+60,y+3);printf("▷ 약속멤버");
	listBorderDraw2(x,y+7);
	listBorderDraw3(x+60,y+4);
	count=selectFriends(DBname, newCombineTimetable,old);
	
	check=checkDateTime(newCombineTimetable,old);  //기존의 시간과 현재 바뀐 통합시간표와 비교시 약속시간이 가능한지 검사.....
	if(check!=0){
		gotoxy(x,y+24);printf("해당 멤버들의 시간표로는 현재 약속을 잡을 수 없습니다. 날짜와 시간을 수정하겠습니다.\n");
		Sleep(2000);
		changeDate(old,newCombineTimetable);
	}
	return count;
}

void showBG(char copyPromiseName[41],char copyPromisePlace[40],char copyPromisedate[10],char copyPromiseTime[6],char copyName[50]){
		system("cls");
		screenBorderDraw();
		gotoxy(56,8); printf("☆ 약속수정 ☆");
		gotoxy(42,13);printf("1. 약속명       : %s",copyPromiseName);
		gotoxy(42,15);printf("2. 약속장소     : %s",copyPromisePlace);
		gotoxy(42,17);printf("3. 약속날짜     : %s",copyPromisedate);
		gotoxy(42,19);printf("4. 약속시간     : %s",copyPromiseTime);
		gotoxy(42,21);printf("5. 함께할 친구  : %s",copyName);
		
		listBorderDraw2(39,24);
}

int selectChange(char *DBname, struct structPromise *old, int listnumber, char **name,int CombineTimetable[5][13],char checkPlace[3]){
	FILE *fp;
	char DB[20];
	int i;
	char select[3];
	char month[3]={0};
	char ID[8]={0};
	char listName[13]={0};
	int newCombineTimetable[5][13]={0};
	char date[3];
	int year;
	char Date[10];
	int check=0;
	int friendsCount=0;
	char copyPromiseName[41]={0};
	char copyPromisePlace[40]={0};
	char copyPromisedate[10]={0};
	char copyPromiseTime[6]={0};
	char copyName[50]={0};
	char slash[1]={'/'};
	int Month,Day;
	int dayofweek;
	time_t curr;

	struct tm *d;
	curr=time(NULL);
	d=localtime(&curr);
	year = d->tm_year;
	year=year+1900;

	strcpy(Date,old->Promisedate);
	for(i=0;i<strlen(Date);i++) {			
		if(strncmp(Date,slash,1)!=0){		
			strncat(month,Date,1);			
			changeLocation(Date);			
		}
		if(strncmp(Date,slash,1)==0) {		
			changeLocation(Date);			
			strcpy(date,Date);
		}		
	}						
	Month=atoi(month);
	Day=atoi(date);
	dayofweek=weekday(year,Month,Day);

	strcpy(copyPromiseName,old->promiseName);
	strcpy(copyPromisePlace,old->promisePlace);
	strcpy(copyPromisedate,old->Promisedate);
	strcpy(copyPromiseTime,old->promiseTime);
	
	strcpy(copyName,name[0]);
	for(i=0; i<4; i++){
		if(i!=0){
			strcat(copyName,"  ");
			strcat(copyName,name[i]);
		}
	}

	
	while(1){
		showBG(copyPromiseName,copyPromisePlace,copyPromisedate,copyPromiseTime,copyName);
		gotoxy(42,26);printf("1. 약속명       : %s",old->promiseName);
		gotoxy(42,28);printf("2. 약속장소     : %s",old->promisePlace);
		gotoxy(42,30);printf("3. 약속날짜     : %s",old->Promisedate);
		gotoxy(42,32);printf("4. 약속시간     : %s",old->promiseTime);
		gotoxy(42,34);printf("5. 함께할 친구  : ");
		strcpy(copyName,name[0]);
		for(i=0; i<4; i++){
			printf("%s  ",name[i]);
		}
		
		gotoxy(42,11);printf("수정할 내용을 선택하세요 :");
		gotoxy(69,11);scanf("%s",&select);
		if(!strcmp(select,"1"))
			changePromiseName(old);
		if(!strcmp(select,"2")){
			changePlace(DBname,old);
			strcpy(checkPlace,"1");
			showBG(copyPromiseName,copyPromisePlace,copyPromisedate,copyPromiseTime,copyName);
		}
		if(!strcmp(select,"3")){
			dayofweek=changeDate(old,CombineTimetable);
			showBG(copyPromiseName,copyPromisePlace,copyPromisedate,copyPromiseTime,copyName);
		}
		if(!strcmp(select,"4")){
			changeTime(old,CombineTimetable,dayofweek);
			showBG(copyPromiseName,copyPromisePlace,copyPromisedate,copyPromiseTime,copyName);
		}
		if(!strcmp(select,"5")){
			friendsCount=changeName(DBname,CombineTimetable,newCombineTimetable,old);
			check=1;
			strcpy(DB,"회원목록.txt");						//학번을 이름으로 바꿔준다. 회원목록 txt를 5번동안 열고 닫고 하며 반복... 회원 숫자를 계산하기 귀찮으므로 그냥 5번 반복
			for(i=0;i<4;i++)
				strcpy(name[i],"\0");
			for(i=0;i<friendsCount;i++){
				fp = fopen(DB, "r");
				while (!feof(fp)) {		
					fscanf(fp, "%s %s", &ID, &listName);										//학번과 이름을 한줄 읽는다.
					if(!strcmp(ID,old->promiseFriendsName[i])){				//검색할 학번과 같은 학번이면
						strcpy(name[i],listName);											//transName 문자배열에 현재 읽은 이름을 복사
						break;
					}
				}
				fclose(fp);
			}
			showBG(copyPromiseName,copyPromisePlace,copyPromisedate,copyPromiseTime,copyName);
		}
		gotoxy(42,26);printf("1. 약속명       : %s",old->promiseName);
		gotoxy(42,28);printf("2. 약속장소     : %s",old->promisePlace);
		gotoxy(42,30);printf("3. 약속날짜     : %s",old->Promisedate);
		gotoxy(42,32);printf("4. 약속시간     : %s",old->promiseTime);
		gotoxy(42,34);printf("5. 함께할 친구  : ");
		strcpy(copyName,name[0]);
		for(i=0; i<4; i++){
			printf("%s  ",name[i]);
		}
		
		gotoxy(40,38);printf("수정을 완료했으면 y를 입력하세요. 계속하려면 다른키를 입력하세요 :");
		gotoxy(107,38);scanf("%s",&select);
		if(!strcmp(select,"y"))
			break;	
		gotoxy(69,11);printf("         ");
		gotoxy(40,38);printf("                                                                           ");	
		}
		return check;	//check 값을 리턴 check가 1이면 이름변경이 이루어진것, 0이면 이름변경이 없었던것
		
}

void promiseChange(char *DBname,char *logID){
	FILE *fp;
	char openDB[30];
	char textFile[]=".txt";
	char check[41];
	struct structPromise *oldPromise;
	struct structPromise changePromise;
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
	int Check;
	char DB[25];
	char friendNameCopy[8]={0};	
	char checkPlace[3]={0};
	int friendsCount;
	int x=35,y=11;
	char controlList[3]={0};
	screenBorderDraw();	
	gotoxy(56,6); printf("☆ 약속수정 ☆");
	gotoxy(54,8); printf("- 나의 약속리스트 -");
	listBorderDraw2(x,y);
	recordCombineTimetable(CombineTimetable,DBname);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(x+12,y+1);printf("현재 생성된 약속리스트가 없습니다.");
		return ;
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
						gotoxy(35,10); printf("다음리스트를 보려면 >키를 입력하세요. 번호를 선택하려면 ~키를 입력하세요.");
						while(1){
							gotoxy(110,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"~")||!strcmp(controlList,">"))
								break;
							gotoxy(110,10);printf("     ");
						}
						if(!strcmp(controlList,"~")){
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
						gotoxy(35,10);printf("이전리스트 <, 다음리스트 >, 번호를 선택하려면 ~키를 입력하세요.");
						while(1){
							gotoxy(100,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"~")||!strcmp(controlList,"<")||!strcmp(controlList,">"))
								break;
							
							gotoxy(100,10);printf("     ");
						}
						if(!strcmp(controlList,"~")){
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
						gotoxy(35,10);printf("처음으로 돌아가려면 <키를 입력하세요.번호를 선택하려면 ~키를 입력하세요.");
						while(1){
							gotoxy(110,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"~")||!strcmp(controlList,"<"))
								break;
							gotoxy(110,10);printf("     ");
						}
						if(!strcmp(controlList,"~")){
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
	gotoxy(35,25);printf("→ 수정하실 약속 : ");
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
	gotoxy(38,40);printf("수정하시겠습니까? <Y,N>");
	gotoxy(63,40);scanf("%s",&select);
	changePromise.promiseFriendsName=(char**)malloc(sizeof(char*)*j+1);
	for(i=0; i<j; i++) {
		changePromise.promiseFriendsName[i]=(char*)malloc(sizeof(char)*8);
			strcpy(changePromise.promiseFriendsName[i],"\0");
				for(k=0; k<8; k++)
					strcpy(&changePromise.promiseFriendsName[i][k],"\0");
	}
	//changePromise 구조체에 수정하기로 선택된 약속의 정보만 빼서 저장
	strcpy(changePromise.promiseName,oldPromise[listnumber].promiseName);
	strcpy(changePromise.promisePlace,oldPromise[listnumber].promisePlace);
	strcpy(changePromise.promiseTime,oldPromise[listnumber].promiseTime);
	strcpy(changePromise.Promisedate,oldPromise[listnumber].Promisedate);
	for(i=0; i<j; i++) {
		strcpy(changePromise.promiseFriendsName[i],oldPromise[listnumber].promiseFriendsName[i]);
	}
	
	if(!strcmp(select,"y"))									//y나 Y일때 수정 단계로 넘어감
		Check=selectChange(DBname,&changePromise,listnumber,transName,CombineTimetable,checkPlace);		//selectChange 함수사용, (현재읽어온 약속리스트정보구조체, 사용자가 선택한 약속리스트번호, 함께하는 회원 이름)을 인수로 넘겨준다.
	else if(!strcmp(select,"Y"))
		Check=selectChange(DBname,&changePromise,listnumber,transName,CombineTimetable,checkPlace);
	
	friendsCount=atoi(oldPromise[listnumber].promiseFreindsCount);
	if(Check==1) {	
		strcpy(cost[listnumber],"\n");
		friendsCount=atoi(changePromise.promiseFreindsCount);//함께할 친구이름들이 수정되었을 경우 그 수를 int형으로 바꿔 저장한다.
		strcpy(oldPromise[listnumber].promiseFreindsCount,changePromise.promiseFreindsCount);//함께할 친구 이름이 수정되었을 경우
		if(strcmp(checkPlace,"1"))
			strcat(changePromise.promisePlace,"\n");
		for(i=0;i<j; i++){
			deletePromise(oldPromise[listnumber].promiseFriendsName[i],oldPromise[listnumber].promiseName,oldPromise[listnumber].Promisedate,oldPromise[listnumber].promiseTime);
			strcpy(oldPromise[listnumber].promiseFriendsName[i],"\0");			
		}
		for(i=0; i<friendsCount; i++) {
			strcpy(oldPromise[listnumber].promiseFriendsName[i],changePromise.promiseFriendsName[i]);
		}	
		for(i=0; i<friendsCount; i++) {		//약속을 함께할 회원들의 개개인의 약속 리스트에 현재 약속정보를 저장하는 부분 
			saveFriendsID(changePromise.promiseFriendsName[i],DB);			//ex) a,b,c,d가 약속을 잡았다. a가 지금 로그인해서 약속을 만든 회원. a회원의 리스트에는 b,c,d가 저장되어있음
			strcpy(friendNameCopy,changePromise.promiseFriendsName[i]);	//지금 로그인 되어있는 회원의 아이디와 for문으로 선택된 함께 약속을 할 회원들중 하나의 아이디를 바꿔치기 해서 저장한다. 
			strcpy(changePromise.promiseFriendsName[i],logID);					//ex) b회원의 약속리스트에는 a,c,d || c회원의 약속리스트에는 b,a,d || d회원의 약속리스트에는 b,c,a 라는 정보가 저장된다.
			saveNewpromise(DB,&changePromise);
			strcpy(changePromise.promiseFriendsName[i],friendNameCopy);		
		}//여기서 이름이 바뀐경우 실행되는 함수가 있어야한다. 예전회원의 약속리스트에서 해당 약속을 삭제하는 함수가 필요하다. 요약하면 무조건 지우고 루프를 벗어나면 새로운 약속회원들한테 약속을 추가한다.
	}			// 기존리스트와 새로정한 친구리스트간에 중복되는 이름이 있어도 그걸 처리하는게 더 힘드므로 그냥 무조건 기존애들을 지우고 새로운 애들한테 추가한다.
	//여기서는 로그인되어있는 본인과 같이 약속을 잡기로 지정되있는 회원들의 약속리스트에 수정된 약속을 쓴다. 즉 기존 약속리스트를 다 날리고 복사되있는 정보에 수정을 가한 정보를 추가해서 기록한다.
	strcpy(oldPromise[listnumber].promiseName,changePromise.promiseName);	//수정이 완료되었으므로 changePromise구조체의 정보를 원래 약속리스트 해당부분에 덮어씌운다.
		strcpy(oldPromise[listnumber].promisePlace,changePromise.promisePlace);
		strcpy(oldPromise[listnumber].promiseTime,changePromise.promiseTime);
		strcpy(oldPromise[listnumber].Promisedate,changePromise.Promisedate);
		saveMyPromiseList(oldPromise, DBname,listCount,friendsName,cost,listnumber);
	if(Check==0){
		
		for(i=0; i<friendsCount; i++) {		//약속을 함께할 회원들의 개개인의 약속 리스트에 현재 약속정보를 저장하는 부분 
			saveFriendsID(oldPromise[listnumber].promiseFriendsName[i],DB);			//ex) a,b,c,d가 약속을 잡았다. a가 지금 로그인해서 약속을 만든 회원. a회원의 리스트에는 b,c,d가 저장되어있음
			strcpy(friendNameCopy,oldPromise[listnumber].promiseFriendsName[i]);	//지금 로그인 되어있는 회원의 아이디와 for문으로 선택된 함께 약속을 할 회원들중 하나의 아이디를 바꿔치기 해서 저장한다. 
			strcpy(oldPromise[listnumber].promiseFriendsName[i],logID);					//ex) b회원의 약속리스트에는 a,c,d || c회원의 약속리스트에는 b,a,d || d회원의 약속리스트에는 b,c,a 라는 정보가 저장된다.
			saveMyPromiseList(oldPromise, DB,listCount,friendsName,cost,listnumber);
			strcpy(oldPromise[listnumber].promiseFriendsName[i],friendNameCopy);		
		}
	}
	for(i=0;i<listCount; i++)			//동적할당 해제
		free(friendsName[i]);				
	free(friendsName);
	for(i=0; i<4; i++)			
		free(transName[i]);				
	free(transName);
	/*for(i=0;i<listCount; i++){			위에서 해제해줌
		for(j=0; j<4; j++)
			free(oldPromise[i].promiseFriendsName[j]);				
		free(oldPromise[i].promiseFriendsName);
	}*/		
	for(i=0;i<listCount; i++)			
		free(cost[i]);				
	free(cost);
	free(oldPromise);	
}
//친구들한테 약속 저장
void saveMyPromiseList(struct structPromise *promiseList, char *DBname, int listCount,char **friendsName,char **cost,int listnumber) {
	FILE *fp;
	char DB[40]={0};
	int i,j;
	int friendsCount=0;
	friendsCount=atoi(promiseList[listnumber].promiseFreindsCount);
	strcpy(DB,DBname);
	strcat(DB,"PromiseList.txt");
	fp = fopen(DB,"w");
	fprintf(fp,"약속리스트\n");
	fprintf(fp,"%d\n",listCount);
	for(i=0; i<listCount; i++) {
		if(i!=listnumber){
			fprintf(fp,"%s\n",promiseList[i].promiseName);
			fprintf(fp,"%s",promiseList[i].promisePlace);			
			fprintf(fp,"%s\n",promiseList[i].promiseTime);
			fprintf(fp,"%s\n",promiseList[i].Promisedate);			
			fprintf(fp,"%s\n",friendsName[i]);
			if((i==listCount-1)&&(!strcmp(cost[i],"\n"))){
				break;
			}
			fprintf(fp,"%s",cost[i]);
		}
		if(i==listnumber){
			fprintf(fp,"%s\n",promiseList[i].promiseName);
			fprintf(fp,"%s",promiseList[i].promisePlace);			
			fprintf(fp,"%s\n",promiseList[i].promiseTime);
			fprintf(fp,"%s\n",promiseList[i].Promisedate);			
			for(j=0;j<friendsCount;j++){
				fprintf(fp,"%s",promiseList[i].promiseFriendsName[j]);
				if(j!=friendsCount-1)
					fprintf(fp,",");
			}
			fprintf(fp,"\n");
			if((i==listCount-1)&&(!strcmp(cost[i],"\n"))){
				break;
			}
			fprintf(fp,"%s",cost[i]);
		}
	}

	fclose(fp);	
}

void deletePromise(char *friendID,char *promiseName, char *promiseDate, char *promiseTime){
	FILE *fp;
	char DB[40]={0};
	char check[40];
	char **friendsName;	
	char **cost;
	int promiseCount=0;
	int i,j;
	int nResult;
	struct structPromise *oldPromise;

	saveFriendsID(friendID,DB);
	strcat(DB,"PromiseList.txt");
	fp=fopen(DB,"r");
	while (!feof(fp)) {	
		fscanf(fp, "%s", &check);					//첫줄을 읽어 혹시나 약속리스트가 아닌경우를 대비
		if(!strcmp(check,"약속리스트")){ 

			fscanf(fp,"%d", &promiseCount);		//둘째줄을 읽어 promiseCount에 저장. 약속리스트의 개수를 의미.
			oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*promiseCount);
			friendsName=(char**)malloc(sizeof(char*)*promiseCount);					
			for(i=0; i<promiseCount; i++) {
				friendsName[i]=(char*)malloc(sizeof(char)*60);
				strcpy(friendsName[i],"\0");
				for(j=0; j<60; j++)
					strcpy(&friendsName[i][j],"\0");
			}

			cost=(char**)malloc(sizeof(char*)*promiseCount);						//장소가 띄어쓰기 포함이기 때문에 structPromise구조체의 장소멤버 사용하기 힘드므로 
			for(i=0; i<promiseCount; i++) {													//그냥 이중포인터 문자배열 사용
				cost[i]=(char*)malloc(sizeof(char)*10);
				strcpy(cost[i],"\0");
				for(j=0; j<10; j++)
					strcpy(&cost[i][j],"\0");
			}
			for(i=0; i<promiseCount; i++) {								//일단 약속리스트개수만큼 약속을 읽어와서 oldPromise구조체에 순서대로 저장
				fscanf(fp,"%s",&oldPromise[i].promiseName);
				fflush(stdin);
				fgets(check,40,fp);						//요건 꼭 두번씩 넣어줘야 제대로 읽음... 포인터위치때문인것 같지만 
				fgets(check,40,fp);						//포인터 위치를 셋하려면 이 부분이 리스트 수만큼 for문을 돌기에 귀찮을듯...그냥 두번읽으면 되니 넘어감... 
				strcpy(oldPromise[i].promisePlace,check);						
				fscanf(fp,"%s",&oldPromise[i].promiseTime);
				fscanf(fp,"%s",&oldPromise[i].Promisedate);
				fscanf(fp,"%s",&check);
				strcpy(friendsName[i],check);
				fgets(check,40,fp);
				fgets(check,40,fp);
				strcpy(cost[i],check);
			}
		}
	}	
	fclose(fp);
	if(promiseCount>1){
	fp=fopen(DB,"w");												//w버전으로 약속리스트를 다시 열어 기존 파일을 날리고 새로 작성한다.
		fprintf(fp,"약속리스트\n");
		fprintf(fp,"%d\n",promiseCount-1);
		for(i=0; i<promiseCount; i++) {
			if((!strcmp(oldPromise[i].promiseName,promiseName))&&(!strcmp(oldPromise[i].Promisedate,promiseDate))&&(!strcmp(oldPromise[i].promiseTime,promiseTime))) {
				if(i==promiseCount-1)
					promiseCount--;
			}
		}
		for(i=0; i<promiseCount; i++) {
			if((!strcmp(oldPromise[i].promiseName,promiseName))&&(!strcmp(oldPromise[i].Promisedate,promiseDate))&&(!strcmp(oldPromise[i].promiseTime,promiseTime))) {
				i++;
			}
			if(i==promiseCount)
				break;
			fprintf(fp,"%s\n",oldPromise[i].promiseName);
			fprintf(fp,"%s",oldPromise[i].promisePlace);			
			fprintf(fp,"%s\n",oldPromise[i].promiseTime);
			fprintf(fp,"%s\n",oldPromise[i].Promisedate);
			fprintf(fp,"%s\n",friendsName[i]);
			
			if((i==promiseCount-1)&&(!strcmp(cost[i],"\n"))){
				break;
			}
			fprintf(fp,"%s",cost[i]);
		}
			
	fclose(fp);	
	}
	else {
		nResult = remove(DB); //해당 파일을 지운다.
		if(nResult == 0) {
			printf("succes");  //지우기 성공
		} 
		else if (nResult == -1)	{
			printf("fail");  //지우기 실패
		}
	}

}