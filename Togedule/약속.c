#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
 
char dayOfWeek[5][4] = {"월","화","수","목","금"};
 
struct structMember{
	char name [13];   //회원이름          
	char ID [8];           // 학번
	char password [14];
	char backupPassword [14];    //고유코드
};
 
struct structSubject{
	char subjectName[15];     //과목이름
	char subjectClass[10];     //입력받는 과목교시  ->1,2,3 ->함수로 처리해야함.
};
 
 
struct structPromise {
	char promiseName [41];    // 내가 입력할 이름
	char promisePlace[30];         //장소 이름을 모르기 때문에 포인터 DB의 문자열을 가리킬 것이다 //장소DB 계획이 아직 구체적으로 안나와서 일단 배열로 분배.
	char promiseTime[5];
	char Promisedate [6];
	char promiseFreindsCount[2];//추가
	char **promiseFriendsName; //인원수의 입력을 받아 {“김동희”, “이설희”}
};
 
struct structTimetable{
	struct structSubject timetable[5][13];
};
 
struct structCost{
	char cost;  
};
 
int login(char *name,struct structMember *loginID) {		// 로그인한 회원의 정보를 읽어올수 있게 만드는 함수	,name에 현재 로그인한 회원의 이름을 채워넣으면 된다.
	FILE *fp;
	char openDB[22];										// 이름을 토대로 txt 파일을 불러와서 정보를 읽는다.
	char textFile[]=".txt";
	char ID[8];
	char listName[13];
	char check[30];
	int listCount=0;
	int i;
	//int j,k;
	struct structPromise *promiseList;
	strcpy(openDB,"회원목록");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( !fp ) {
			printf("ERROR : %s cannot open!\n",openDB );
			return -1;
		}
	while (!feof(fp)) {
		fscanf(fp, "%s %s", &ID, &listName);
		if(!strcmp(listName,name)){
			break;
		}
	}
	fclose(fp);
	strcpy(openDB,ID);
	strcat(openDB,name);
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
			printf("ERROR : %s cannot open!\n",openDB );
			return -1;
		}
	while (!feof(fp)) {
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"회원정보")){
			fscanf(fp,"%s", loginID->ID);
			fscanf(fp,"%s", loginID->name);
			fscanf(fp,"%s", loginID->password);
			fscanf(fp,"%s", loginID->backupPassword);
		}
	
	
		if(!strcmp(check,"약속리스트")){
			fscanf(fp,"%d", &listCount);
			promiseList=(struct structPromise*)malloc(sizeof(struct structPromise)*listCount);
			
			for(i=0; i<listCount; i++){
				fscanf(fp,"%s", promiseList[i].promiseName);
				fscanf(fp,"%s", promiseList[i].promisePlace);
				fscanf(fp,"%s", promiseList[i].promiseTime);
				fscanf(fp,"%s", promiseList[i].Promisedate);
				promiseList[i].promiseFriendsName=(char **)malloc(sizeof(char)*5);
				fgets(check,2,fp);
				fgets(check,30,fp);
				//printf("%s",check);
 
				/*for(j=0; j<5; j++){
					fgets(check,30,fp);
					promiseList[i].promiseFriendsName[j]=(char *)malloc(sizeof(char)*13);
					for(k=0; k<13; k++)
						promiseList[i].promiseFriendsName[i][k]=NULL;
				}
				for(j=0;j<5;j++){
					fscanf(fp,"%s", promiseList[i].promiseFriendsName[j]);
					printf("%s", promiseList[i].promiseFriendsName[j]);
				}*/
			}
		}
	}
	/*printf("1 %s",loginID->ID);
	printf("2 %s",loginID->name);
	printf("3 %s",loginID->password);
	printf("4 %s",loginID->backupPassword);*/
	printf("나의 약속\n");
	for(i=0; i<listCount; i++){
		printf("○ %s ",promiseList[i].promiseName);
		printf("/ %s\n",promiseList[i].Promisedate);
	}
	fclose(fp);
	for(i=0; i<listCount; i++)
		free(promiseList[i].promiseFriendsName);
	free(promiseList);
}
 
 void changeLocation( char* str ) 
{ 
	int len = strlen( str ); 
    int i;
	char temp = str[0]; 
	for( i = 0; i < len; i++ ) 
    { 
		str[ i ] = str[ i + 1]; 
	} 
   str[ len - 1 ] = '\0'; 
} 


int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13]){		//이름 검색함수. txt파일의 중복이름은 김진삼.txt 김진삼1.txt 김진삼2.txt 이런형태로 가정해서 풀어나감.
	int exist=0;
	char openDB[40];
	char check[30];
	char Time[5]={0};
	char select[2];
	char dayWeek[30];
	char ID[8];
	char listName[13];
	int overlap=1;
	int limit=0;
	int i,j;
	int dayweek,time;
	char comma[1]={','};
	struct structMember friendID;	//여기서 굳이 structMember를 만든 이유는 나중에 자료저장부분에서 혹시 쓰일까 해서...
 
	FILE *fp;
	FILE *fp1;
	
 
	while(1){		//이름중복이 있는지 확인하고 있으면 파일을 열어 이름을 가져오는 반복문 (바깥 루프)
		char textFile[]=".txt";
		strcpy(openDB,"회원목록");
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");
		
		while (!feof(fp)) {
			fscanf(fp, "%s %s", &ID, &listName);
 
			if(!strcmp(listName,name)){
				strcpy(openDB,ID);
				strcat(openDB,name);
				strcat(openDB,textFile);
	
				fp1 = fopen(openDB, "r");
				if ( !fp1 ) {         
					printf("%s회원의 정보가 없습니다.",name );
					exist=1;
					break;
				}
				
				while (!feof(fp1)) {			//이름이 있으면(중복검사하기전. 그냥 김진삼.txt 가 있는경우 정보를 읽어옴
					fscanf(fp1, "%s", &check);
					if(!strcmp(check,"회원정보")){
						fscanf(fp1,"%s", friendID.ID);
						fscanf(fp1,"%s", friendID.name);
						
					}
				}
				fclose(fp1);
				printf("%d %s %s %s\n",overlap,friendID.ID,friendID.ID,friendID.name);
				overlap++;
			}
		}
		fclose(fp);
		if(!strcmp(openDB,"회원목록.txt")){
			printf("%s회원의 정보가 없습니다.",name);
			exist=1;
			break;
		}
		printf("→ 이름번호 선택 : ");		//모든 리스트가 출력되면 리스트번호를 선택받는다.
		limit=overlap-1;
		while(1) {						//리스트 번호 범위 내의 수만 입력받기
			scanf("%s",select);
			overlap=atoi(select);	
			if(overlap>0&&overlap<=limit)
				break;
		}
		limit=1;
		strcpy(openDB,"회원목록");
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");
		
		while (!feof(fp)) {
			fscanf(fp, "%s %s", &ID, &listName);
			if(!strcmp(listName,name)){
				if(overlap==limit)
					break;
				limit++;
			}
		}
		fclose(fp);
		strcpy(openDB,ID);
		strcat(openDB,name);		//이 부분을 만든 이유는 나중에 각 회원의 txt파일에 정보를 저장하기 위해서 또 통합시간표 생성을 위해...
		strcat(openDB,textFile);	//뒤에 장소선택까지 끝마치고 txt파일에 저장하는 부분은 아직 구현안함 그떄 여길 손봐서 해당회원txt파일을 뒤로 넘겨주던가 여기 코드를 복사해서 쓰면 될듯
		
		fp = fopen(openDB, "r");
		while (!feof(fp)) {
				fscanf(fp, "%s", &check);
				if(!strcmp(check,"회원정보")){
					fscanf(fp,"%s", friendID.ID);
					fscanf(fp,"%s", friendID.name);
				}
				if(!strcmp(check,"시간표")){ 
					while(strcmp(dayWeek,"약속리스트")){
						fscanf(fp,"%s", &dayWeek);
						if(!strcmp(dayWeek,"약속리스트"))
							break;
						if(!strcmp(dayWeek,"월"))
							dayweek=0;
						else if(!strcmp(dayWeek,"화"))
							dayweek=1;
						else if(!strcmp(dayWeek,"수"))
							dayweek=2;
						else if(!strcmp(dayWeek,"목"))
							dayweek=3;
						else if(!strcmp(dayWeek,"금"))
							dayweek=4;
						fscanf(fp,"%s", &check);
						fscanf(fp,"%s",&check);
						for(i=0;i<strlen(check);i++) {
							if(strncmp(check,comma,1)!=0){
								strncat(Time,check,1);
								changeLocation(check);
							}
							if(strncmp(check,comma,1)==0) {	
								changeLocation(check);
								time=atoi(Time);
								CombineTimetable[dayweek][time-1]=1;
								for(j=0; j<strlen(Time); j++)
									Time[j]='\0';	
							}		
						}						
						time=atoi(check);
						CombineTimetable[dayweek][time-1]=1;
						for(j=0; j<strlen(Time); j++)
							Time[j]='\0';
						
					}
				}
			}			
			fclose(fp);
 
		
		
		for(i=0; i<5; i++) {		//읽어왔으면 회원 이름을 strcpy를 이용 구조체 nwePromise 의 promiseFriendsName 에 복사붙여넣기 
			if(*newPromise.promiseFriendsName[i] == NULL){
				strcpy(newPromise.promiseFriendsName[i],friendID.name);
				break;
			}
		}
		break;
	}	
	return exist;
}
void callendar() {
	int last,th,year,day,date,x,z,y,m;
	printf("년도를 입력하세요 : ");
	scanf("%d",&y);
	printf("월을 입력하세요 : ");
	scanf("%d",&m);
	if((m>=1)&&(m<=12))
	{
		if((m==1)||(m==3)||(m==5)||(m==7)||(m==8)||(m==10)||(m==12))
		{
			last=31;
		}
		else if((m==4)||(m==6)||(m==9)||(m==11))
		{
			last=30;
		}
		if((m==2))
		{
			last=28;
		}
		if((m==2)&&(y%4==0)&&(y%100!=0)||(y%400==0))
		{
			last=29;
		}
		if(m<3)
		{
			y=y-1;
			m=m+12;
		}
	}
	printf(" 일 월 화 수 목 금 토\n");
	printf(" -----------------------\n");
	date=1;
	for(x=0;x<=6;x++)
	{
		th=y/100;
		year=y%100;
		day=((21*th/4)+(5*year/4)+(26*(m+1)/10)+date-1)%7;
		for(z=0;z<7;z++)
		{
			if(x=1 && z<day)
			{
				printf("   ");
			}
			else
			{
				if(z>=day&&date<10)
				{
					printf(" %2d",date);
				}
				else if(z>=day&&date>=10)
				{
					printf(" %2d",date);
				}
				if(date<last)
				{
					date=date+1;
				}
				else if(date>=last)
				{
					printf("\n");
					return;
				}
			}
		}
		printf("\n");
		
	}
}
void selectDate(int CombineTimetable[5][13]){	//요일, 시간, 날짜 입력받는 함수
	
	char dayofweek[3];
	char time[27];
	char date[10];
	int dayofWeek;
	int Time;
	int Date;
	int i,j;
	int errorCheck;
	char dayOfWeek[5][4] = {"월","화","수","목","금"};
	system("cls");
	printf("- 약속 / 날짜 / 시간 -\n");
	printf("약속을 지정할 요일과 시간을 정하고\n");
	printf("날짜를 기입해주세요.\n");
	printf("예) 월요일, 월, 화\n");
	printf("예) 5, 6, 7\n");
	printf("예) 10월 30일\n");
	
	callendar();
	for (i=0; i<5; i++) {
		for(j=0; j<13; j++)
			printf("%d ",CombineTimetable[i][j]);
	printf("\n");
	}
	printf("요일");
	scanf("%s",dayofweek);
	printf("시간");
	scanf("%s",time);
	printf("날짜");
	scanf("%s",date);
	if(!strcmp(dayofweek,dayOfWeek[0]))
		dayofWeek=0;
	else if(!strcmp(dayofweek,dayOfWeek[1]))
		dayofWeek=1;
	else if(!strcmp(dayofweek,dayOfWeek[2]))
		dayofWeek=2;
	else if(!strcmp(dayofweek,dayOfWeek[3]))
		dayofWeek=3;
	else if(!strcmp(dayofweek,dayOfWeek[4]))
		dayofWeek=4;
	while(1){
		errorCheck=0;
		Time = atoi(time);
		printf("%d",Time);
		if(CombineTimetable[dayofWeek][Time-1]==1){
			errorCheck=1;
		}					
		if(errorCheck==0)
			break;
		printf("시간재입력");
		scanf("%s",time);
	}
}
 
void promiseCreatConsole() {	//약속만들기 함수 (약속명, 인원수 입력  .이름 검색함수 내부 포함. 약속 리스트 출력)
	char Name[13];
	int i,j;
	int Count=0;
	struct structPromise newPromise;	//새로운 약속을 위한 구조체 생성 newPromise
	int CombineTimetable[5][13]={0};
	char control[3]={0};
 
	printf(" 약속 만들기 ");
	printf(" 약속명 : ");
	scanf("%s",&newPromise.promiseName);
	printf(" 인원수 : ");
	scanf("%s",&newPromise.promiseFreindsCount);
 
	Count=atoi(newPromise.promiseFreindsCount);		//인원수를 int형으로 바꿔주고 newPromise의 promiseFriendsCount 에 동적할당
	newPromise.promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	//요건 +1로 하면 오류.. 왜그런지 이유 못알아냄.
	for(i=0; i<Count; i++){
		newPromise.promiseFriendsName[i]=(char *)malloc(sizeof(char)*13);
		for(j=0; j<13; j++)
			newPromise.promiseFriendsName[i][j]=NULL;
	}
	while(Count>0) {		//인원수만큼 검색함수를 돌린다.
		printf(" 이름검색 : ");
		scanf("%s",&Name);
		if(!searchName(Name,Count,newPromise,CombineTimetable))		//이름 검색함수에서 리턴값을 받아온다. 받아온 리턴값이 1이면 이름이 없었던 경우이므로 Count값을 감소하지 않는다.
			Count--;
	}
	printf("\n");
	for(i=0;i<5;i++){
		for(j=0; j<13; j++)
			printf("%d",CombineTimetable[i][j]);
			printf("\n");
	}
 
	printf("\n 약속멤버");			//리스트 출력부분
	Count=atoi(newPromise.promiseFreindsCount);			//Count를 위에서 0으로 만들었으므로 다시 int형으로 재배치.
	for(i=0; i<Count; i++) {		
			printf("\n%s",newPromise.promiseFriendsName[i]);
		}
	printf("다음장으로");
	scanf("%s",control);
	if(control)
		selectDate(CombineTimetable);
	
 
	for(i=0; i<Count; i++)		//동적할당 해제
	free(newPromise.promiseFriendsName[i]);
	free(newPromise.promiseFriendsName);
 
}
 
 
void showMenu() {
	printf("☆ 약속 메뉴 ☆\n");
	printf("1. 약속만들기\n");
	printf("2. 약속 수정\n");
	printf("3. 약속 삭제\n");	
	printf("▷ 메뉴 선택 : ");
}
 
int main() {
	char logID[8];
	struct structMember loginID;		//현재 회원정보를 가져올 구조체 생성
	char menuControl;
	strcpy(logID,"김진삼");				//이름을 기반으로 txt파일을 찾는 형식. 이름을 logID에 복사해준다.
 
	showMenu();
 
	login(logID,&loginID);				//현재회원정보 함수 실행
	
	scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") 요건 화면을 지우고 다시 출력하게 하는 명령 <windows.h>필요
	case '1': system("cls"); promiseCreatConsole(); break;
	case '2': system("cls"); break;
	case '3': system("cls"); break;
	}
 
 
}