#include"structHeader.h"

void changePlace(char *DBname, struct structPromise *old) {
	char blank[1]={0};
	promisePlace(DBname,old);
	old->promisePlace[strlen(old->promisePlace)-1]=blank[0];           //장소DB에서 읽어올때 \n 하나 들어있는거 없애서 자동줄바꿈 방지
}
// 이름수정과 수정된 멤버로 약속생성되있는게 가능한가, 약속장소 수정 까지 완료..
void changeTime(struct structPromise *old,int newCombineTimetable[5][13],int dayofweek) {
	int i,j;
	char dayofWeek[5];
	printf(" 월   화   수   목   금\n");
	for(j=0; j<13; j++) {		//통합시간표를 출력 (임시). 시간표 출력하는 부분과 연관해서 제대로 표를 짜서 출력해야함
		for (i=0; i<5; i++){
			if(newCombineTimetable[i][j]==1)
				printf("■■ ",newCombineTimetable[i][j]);
			if(newCombineTimetable[i][j]==0)
				printf("□□ ",newCombineTimetable[i][j]);
		}
		printf("\n");
	}
	switch(dayofweek){		//weekday함수사용, 해당 연도 월 일에 해당하는 요일을 계산해서 삽입.
	case 0: strcpy(dayofWeek,"월"); break;
	case 1: strcpy(dayofWeek,"화"); break;
	case 2: strcpy(dayofWeek,"수"); break;
	case 3: strcpy(dayofWeek,"목"); break;
	case 4: strcpy(dayofWeek,"금"); break;
	}
	printf("현재 약속요일>> %s\n",dayofWeek);
	printf("현재 약속시간>> %s\n",old->promiseTime);
	printf("%d",dayofweek);
	selectTime(newCombineTimetable,old,dayofweek);
}
int changeDate(struct structPromise *old,int newCombineTimetable[5][13]) {
	int dayofweek;
	int time;
	dayofweek=selectDate(newCombineTimetable,old);
	time=atoi(old->promiseTime);
	if(newCombineTimetable[dayofweek][time-1]==1) {
		printf("현재 정해진 시간에는 약속을 잡을 수 없습니다. 시간을 수정하겠습니다.\n");
		changeTime(old,newCombineTimetable,dayofweek);
	}
	return dayofweek;
}
void changePromiseName(struct structPromise *old){
	printf("수정할 약속명 입력 >> ");
	scanf("%s",&old->promiseName);
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
	printf("%s %s",month,date);
	Month=atoi(month);
	Day=atoi(date);
	dayofweek=weekday(year,Month,Day);
	strcpy(stime,old->promiseTime);
	Time=atoi(stime);
	if(CombineTimetable[dayofweek][Time-1]==1)
		return -1;
	return 0;
}
void changeName(char *DBname,int CombineTimetable[5][13],int newCombineTimetable[5][13] ,struct structPromise *old){
	char select[3];
	
	int i;
	int count;
	int check;
	count=selectFriends(DBname, newCombineTimetable,old);
	for(i=0; i<count; i++)
		printf("%s ",old->promiseFriendsName[i]);
	scanf("%s",&select);

	check=checkDateTime(newCombineTimetable,old);  //기존의 시간과 현재 바뀐 통합시간표와 비교시 약속시간이 가능한지 검사.....
	if(check!=0){
		printf("해당 멤버들의 시간표로는 현재 약속을 잡을 수 없습니다. 날짜와 시간을 수정하겠습니다.\n");
		changeDate(old,newCombineTimetable);
	}
	for(i=0; i<count; i++)		//동적할당 해제
		free(old->promiseFriendsName[i]);
	free(old->promiseFriendsName);
}

void selectChange(char *DBname, struct structPromise *old, int listnumber, char **name,int CombineTimetable[5][13]){
	int i,j;
	char select[3];
	char month[3]={0};
	int newCombineTimetable[5][13]={0};
	char date[3];
	int year;
	char Date[10];

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

	system("cls");
	for(i=0;i<5;i++){
		for(j=0; j<13; j++)
			printf("%d",CombineTimetable[i][j]);
		printf("\n");
	}
	printf("약속수정\n");
	printf("1. 약속명   : %s\n",old[listnumber].promiseName);
	printf("2. 약속장소 : %s\n",old[listnumber].promisePlace);
	printf("3. 약속날짜 : %s\n",old[listnumber].Promisedate);
	printf("4. 약속시간 : %s\n",old[listnumber].promiseTime);
	printf("5. 함께할 친구 : ");
	for(i=0; i<4; i++)
		printf("%s ",name[i]);
	printf("\n");
	while(1){
	printf("수정할 내용을 선택하세요.\n");
	scanf("%s",&select);
	if(!strcmp(select,"1"))
		changePromiseName(old);
	if(!strcmp(select,"2"))
		changePlace(DBname,old);
	if(!strcmp(select,"3"))
		dayofweek=changeDate(old,CombineTimetable);
	if(!strcmp(select,"4"))
		changeTime(old,CombineTimetable,dayofweek);
	if(!strcmp(select,"5"))
		changeName(DBname,CombineTimetable,newCombineTimetable,old);
	printf("1. 약속명   : %s\n",old[listnumber].promiseName);
	printf("2. 약속장소 : %s\n",old[listnumber].promisePlace);
	printf("3. 약속날짜 : %s\n",old[listnumber].Promisedate);
	printf("4. 약속시간 : %s\n",old[listnumber].promiseTime);
	printf("5. 함께할 친구 : ");
	for(i=0; i<4; i++)
		printf("%s ",name[i]);
	printf("\n");
	printf("수정을 완료했으면 y를 입력하세요. 계속하려면 다른키를 입력하세요.");
	scanf("%s",&select);
	if(!strcmp(select,"y"))
		break;
	}

}

void promiseChange(char *DBname){
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
	recordCombineTimetable(CombineTimetable,DBname);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		printf("현재 생성된 약속리스트가 없습니다.");
		return ;
	}
	while (!feof(fp)) {			//약속리스트 열어서 리스트에 적혀진 개수만큼 이름과 날짜를 읽어서 출력하는 부분
		printf("나의 약속리스트\n");
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
				printf("%d %s ",numbering,oldPromise[i].promiseName);
				printf("/ %s\n",oldPromise[i].Promisedate);
				numbering++;
			}
		}
	}
	fclose(fp);
	printf("→ 수정하실 약속 : ");
	while(1) {						//리스트 번호 범위 내의 수만 입력받기
		scanf("%s",select);
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<=numbering)
			break;
		printf("리스트 내의 번호를 입력하세요 : ");
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
	for(i=0;i<5;i++){
		for(j=0; j<13; j++)
			printf("%d",CombineTimetable[i][j]);
		printf("\n");
	}
	for(i=0;i<4;i++){
		if(!strcmp(transName[i],"\0"))
			break;
		strcpy(openDB,oldPromise[listnumber].promiseFriendsName[i]);
		strcat(openDB,transName[i]);
		
		k=recordCombineTimetable(CombineTimetable,openDB);

	}
	
	oldPromise[listnumber].promisePlace[strlen(oldPromise[listnumber].promisePlace)-1]=blank[0];           //장소DB에서 읽어올때 \n 하나 들어있는거 없애서 자동줄바꿈 방지
	printf("\n");
	printf("약속명      장소        날짜      시간      함께할친구\n");
	printf("%s    %s     %s     %s\n",oldPromise[listnumber].promiseName,oldPromise[listnumber].promisePlace,oldPromise[listnumber].promiseTime,oldPromise[listnumber].Promisedate);
	for(i=0; i<4; i++)
		printf("%s ",transName[i]);
	printf("\n");
	printf("수정하시겠습니까? <Y,N>");
	scanf("%s",&select);
	
	if(!strcmp(select,"y"))									//y나 Y일때 수정 단계로 넘어감
		selectChange(DBname,oldPromise,listnumber,transName,CombineTimetable);		//selectChange 함수사용, (현재읽어온 약속리스트정보구조체, 사용자가 선택한 약속리스트번호, 함께하는 회원 이름)을 인수로 넘겨준다.
	else if(!strcmp(select,"Y"))
		selectChange(DBname,oldPromise,listnumber,transName,CombineTimetable);

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