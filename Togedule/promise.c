#include"structHeader.h"
//개인파일로 만들시 꼭 위의 헤더랑 function.c 포함해서 작업해야함
//extern char dayOfWeek[5][4];  헤더로 옮김 지워도 됨

void promiseList(char *DBname){	// 로그인한 회원의 약속리스트를 불러오는 함수 , 출력만 한다. 없을경우 없다고 출력해준다.
	FILE *fp;
	char openDB[30];
	char textFile[]=".txt";
	char check[41];
	char promiseName[41];
	char promiseDate[10];
	int listCount=0;
	int i;
	
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		printf("현재 생성된 약속리스트가 없습니다.");
		return ;
	}
	while (!feof(fp)) {			//약속리스트 열어서 리스트에 적혀진 개수만큼 이름과 날짜를 읽어서 출력하는 부분
		printf("나의 약속\n");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"약속리스트")){
			fscanf(fp,"%d", &listCount);
			for(i=0; i<listCount; i++){
				fscanf(fp,"%s", promiseName);
				fgets(check,41,fp);
				fgets(check,41,fp);
				fgets(check,41,fp);
				fscanf(fp,"%s", promiseDate);
				fscanf(fp,"%s", check);
				fgets(check,41,fp);			//비용들어갈 자리 추가.
				fgets(check,41,fp);
				printf("○ %s ",promiseName);
				printf("/ %s\n",promiseDate);
			}
		}
	}
	fclose(fp);
}

void changeLocation( char* str ) {	//문자열 처리함수 한줄씩 떙기고 맨 뒤에 공백삽입하는 함수. 
	int len = strlen( str ); 
	int i;
	char temp = str[0]; 
	for( i=0; i<len; i++ )  
		str[ i ] = str[ i + 1]; 
	str[ len - 1 ] = '\0'; 
} 

int recordCombineTimetable(int CombineTimetable[5][13], char *DBname){		//통합시간표에 정보를 추가하는 함수. 통합시간표와 '학번+이름' 문자열을 인수로 받아서 처리.
	char openDB[40];
	char check[30];
	char dayWeek[30];
	char Time[5]={0};
	int dayweek,time,i,j;
	char comma[1]={','};
	int length;
	FILE *fp;
	strcpy(openDB,DBname);
	strcat(openDB,"timetable.txt");		
	fp = fopen(openDB, "r");		//해당 회원의 시간표정보를 읽어온다.
	if(!fp){					//만약 해당 회원의 시간표 정보가 없을경우 1 리턴. 
		return 1;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", &check);			//첫줄은 시간표 개수? 를 의미한다고 해서 읽기만 하는 값. 여기서 안쓰이는 변수
		while(!feof(fp)){					
			fscanf(fp,"%s", &dayWeek);		//요일을 읽는다 읽어서 월화수목금에 해당하는 정수형 자료로 /처리. 
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
			fscanf(fp,"%s", &check);		//과목을 읽는다. 과목도 통합시간표에서 안쓰이는 변수이므로 읽기만 한다.
			fscanf(fp,"%s",&check);			//시간을 읽는다.

			for(i=0;i<strlen(check);i++) {			//시간 문자열의 길이를 알아내서 for문으로 한단어씩 개별처리를 한다.
				if(strncmp(check,comma,1)!=0){		//시간문자열의 첫단어가 "," 가 아니면 
					strncat(Time,check,1);			//Time이라는 문자열에 시간문자열의 첫단어를 삽입. 덮어씌우는게 아니라 뒤에 덧붙이는 삽입이다. 
					changeLocation(check);			//changeLocatioin 함수를 사용. 시간문자열은 첫단어를 지우고 한칸씩 땡긴다.
				}
				if(strncmp(check,comma,1)==0) {		//시간문자열의 첫단어가 "," 이면
					changeLocation(check);			//함수이용. ","삭제후 한칸씩 땡긴다.
					time=atoi(Time);				//지금까지 삽입한 Time 문자열을 정수형 time 변수에 삽입
					CombineTimetable[dayweek][time-1]=1;		//위에서 변환해준 정수형 요일과 시간을 이용. 통합시간표에 체크
					length=strlen(Time);
					for(j=0; j<length; j++)
						Time[j]='\0';	
					}		
				}						
			time=atoi(check);					//마지막시간뒤에는 ","가 안붙으므로 여기서 다시한번 처리
			CombineTimetable[dayweek][time-1]=1;
			length=strlen(Time);
			for(j=0; j<length; j++)
				Time[j]='\0';
		}
	}			
	fclose(fp);
	return 0;		//정상적으로 읽었으면 0리턴 
}

void setMajor(char ID[8],char Major[20])	{		//학번 3,4자리를 바탕으로 학과 알아내는 함수
	char IDCopy[8];					
	char keyWord[3]={0};
	char major[20];
	char number[3];
	char noMajor[13];
	FILE *fp;

	strcpy(noMajor,"학과정보없음");		//학과정보와 일치하는게 없을때 출력해줄 문장
	strcpy(IDCopy,ID);
	changeLocation(IDCopy);
	changeLocation(IDCopy);
	strncpy(keyWord,IDCopy,2);
	fp=fopen("major.txt","r");			//major.txt 여기에 학번, 학과 정보가 저장되어있음 
	
	while(!feof(fp)){					
		fscanf(fp,"%s %s",&number,&major);
		if(!strcmp(number,keyWord))	{			//일치하는 학번일 경우 학과 정보를 Major에 저장
			fclose(fp);
			strcpy(Major,major);
			return;
		}
	}
	fclose(fp);
	strcpy(Major,noMajor);		//없을경우 "학과정보없음" 을 Major에 저장		
}

int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13]){		//이름검색함수.. (검색할이름, 함께하는회원중 리스트에 안올라간 회원수,새약속구조체,통합시간표) 를 변수로 받는다.
	int exist=0;
	char openDB[40];
	char check[30];
	char Time[5]={0};
	char select[2];
	char ID[8];
	char listName[13];
	char major[20]={0};
	int overlap=1;
	int limit=0;
	int i;
	char comma[1]={','};
	struct structMember friendID;		//이 구조체는 이 함수내부에서만 쓰임.. 별 효용은 없고 그냥 char두개 또 만들기 귀찮아서 써본 구조체...
	FILE *fp;
	FILE *fp1;


	while(1){		
		char textFile[]=".txt";			//회원목록 파일을 연다.
		strcpy(openDB,"회원목록");
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");

		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &ID, &listName);	//열어서 변수로 받은 이름과 학번을 읽는다

			if(!strcmp(listName,name)){				//검색할 이름과 같은 이름이면
				strcpy(openDB,ID);
				strcat(openDB,name);
				strcat(openDB,textFile);
				fp1 = fopen(openDB, "r");			//학번과 이름을 이용 해당회원정보파일을 읽는다.

				if ( !fp1 ) {						//없으면 브레이크 처리.. 만에하나 회원목록에는 있고 회원정보가 없는 경우를 체크함
					printf("%s회원의 정보가 없습니다.",name );
					exist=1;
					break;
				}

				while (!feof(fp1)) {				//회원정보에서 학번과 이름을 읽어와 구조체 friendID에 저장한다.
					fscanf(fp1, "%s", &check);
					if(!strcmp(check,"회원정보")){
						fscanf(fp1,"%s", friendID.ID);
						fscanf(fp1,"%s", friendID.name);
					}
				}
				setMajor(friendID.ID,major);		//setMajor함수 이용. 학과정보를 알아와서 major에 저장
				fclose(fp1);					//그뒤 회원정보파일을 닫고
				printf("%d %s %s %s\n",overlap,major,friendID.ID,friendID.name);		//중복목록을 띄워주기 위해 출력을 해준다. 현재 학번을 학과로 바꾸는 부분이 빠져서 학번을 두번 출력하게 되있다.
				overlap++;						//리스트 번호를 증가시키고 반복...반복해서 같은 이름을 계속 찾아나간다.
			}
		}
		fclose(fp);
		if(!strcmp(openDB,"회원목록.txt")){		//회원목록에 없는 이름을 검색했을 경우 처리
			printf("%s회원의 정보가 없습니다.",name);
			exist=1;							//exist를 1로 리턴. exist는 이 이름검색함수의 리턴값으로 쓰임. 함수를 부르는 단계에서 이 리턴값을 가지고 회원이름이 있는지 없는지를 체크해서 /
			break;								//같이 약속을 할 인원중 현재 리스트에 올라간 회원이 아닌 남은 회원수를 파악
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
		strcpy(openDB,"회원목록");		//회원목록을 다시 연다.
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");

		while (!feof(fp)) {					//열어서 위에 입력받은 리스트 번호가 될때까지 읽어주며 값을 찾는다. 리스트 순서는 회원목록 순서와 같으므로 이렇게 처리한다.
			fscanf(fp, "%s %s", &ID, &listName);
			if(!strcmp(listName,name)){
				if(overlap==limit)
					break;
				limit++;
			}
		}
		fclose(fp);
		strcpy(openDB,ID);					//선택된 회원의 학번과 이름을 하나로 합쳐서 저장
		strcat(openDB,name);
		if(recordCombineTimetable(CombineTimetable,openDB)==1)		//통합시간표 기록하는 함수 부름. 1이 돌아오면 해당 회원의 시간표 정보가 없는것
			printf("%s회원의 시간표정보가 없습니다.",name);
		for(i=0; i<5; i++) {										//리스트에서 선택된 회원의 학번을 strcpy를 이용 구조체 newPromise 의 promiseFriendsName 에 복사붙여넣기 
			if(!strcmp(newPromise.promiseFriendsName[i],"\0")){
				strcpy(newPromise.promiseFriendsName[i],ID);
				break;
			}
		}
		break;
	}	
	return exist;			//exist를 리턴값으로 가진다. 이름검색이 됬으면 0이 리턴, 없는 이름이면 위에서 1을 리턴하게 되있다.
}
int callendar(int Month) {		//달력출력함수. 월을 인수로 넘겨받는다. selectDate 함수에서 입력받은 달을 넘겨받음.
	int last,th,year,day,date,x,z,y,m;
	time_t curr;

	struct tm *d;
	curr=time(NULL);
	d=localtime(&curr);
	year = d->tm_year;
	y=year+1900;			//현재 년도를 계산.. 2014년이 저장된다. 
	m=Month;				//월은 인수를 그대로 이용
	if((m>=1)&&(m<=12))		//여기는 각 달마다 31일, 30일, 28일, 29일 을 나눠주는 부분
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
	printf(" 일 월 화 수 목 금 토\n");		//입력받은 년도와 월의 달력을 출력만 하는 함수이다.
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

					return y;
				}
			}
		}
		printf("\n");

	}

}

int weekday(int year, int month, int day) //년도, 월, 일 을 입력받아 요일 찾는 함수. 리턴값은 정수.
{
	int year_1 = year / 100;
	int year_2 = year - year_1 * 100;

	return (day + (month + 1) * 26 / 10 + year_2 + (year_2 / 4) + (year_1 / 4) - 2 * year_1 - 2) % 7;
}
int selectDate(int CombineTimetable[5][13],structPromise *newPromise){	//만들 약속의 요일, 시간, 날짜 입력받는 역할을 하는 함수 (통합시간표, 학번+이름 문자열, 새약속구조체)를 인수로 받는다.

	char dayofweek[3];
	char month[10];
	char day[10];
	char temp[10]={0};
	int dayofWeek;
	int Day;
	int Month;
	int year;
	int i,j;
	int promiseCount=0;
	int length;

	system("cls");				//이 함수 바로 전단계에서 화면에 출력된 문자들을 지워준다.
	printf("- 약속 / 날짜 / 시간 -\n");
	printf("약속을 생성할 달을 입력하세요.\n");
	printf("달력이 나타나면 통합시간표를 참고해서 약속을 정할 날짜를 입력하세요.\n");
	printf("요일은 날짜입력에 따라 자동으로 선택됩니다.\n");
	printf("날짜입력이 끝나면 약속시간(교시)을 입력하세요.\n");
	printf("예) 10월\n");
	printf("예) 30일\n");
	printf("예) 1\n");

	printf(" 월   화   수   목   금\n");
	for(j=0; j<13; j++) {		//통합시간표를 출력 (임시). 시간표 출력하는 부분과 연관해서 제대로 표를 짜서 출력해야함
		for (i=0; i<5; i++){
			if(CombineTimetable[i][j]==1)
				printf("■■ ",CombineTimetable[i][j]);
			if(CombineTimetable[i][j]==0)
				printf("□□ ",CombineTimetable[i][j]);
		}
		printf("\n");
	}

	printf("약속을 잡을 달 입력(ex 3월) :");	
	scanf("%s",&month);								//월을 입력하면
	length=strlen(month);
	for(i=0;i<length;i++) {
		if(strncmp(month,"월",1)!=0){

			strncat(temp,month,1);
			changeLocation(month);
		}
		if(strncmp(month,"월",1)==0) {				//'월'이라는 단어를 제외하고 숫자부분만 떼내어서 정수형 변수 Month에 저장  
			Month=atoi(temp);
			break;
		}		
	}
	strcpy(newPromise->Promisedate,temp);
	strcat(newPromise->Promisedate,"/");
	year=callendar(Month);							//입력받은 월을 가지고 callendar함수사용. 올해 달력을 출력 
	printf("약속을 잡을 날짜 입력(ex 10일) :");		//일을 입력하면
	scanf("%s",&day);
	length=strlen(temp);
	for(i=0; i<length; i++)
		temp[i]='\0';
	length=strlen(day);
	for(i=0;i<length;i++) {
		if(strncmp(day,"일",1)!=0){
			strncat(temp,day,1);
			changeLocation(day);
		}
		if(strncmp(day,"일",1)==0) {				//'일'이라는 단어를 제외하고 숫자부분만 떼내어서 정수형 변수 Day에 저장  
			Day=atoi(temp);
			break;
		}		
	} 
	strcat(newPromise->Promisedate,temp);
	switch(weekday(year,Month,Day)){		//weekday함수사용, 해당 연도 월 일에 해당하는 요일을 계산해서 삽입.
	case 0: strcpy(dayofweek,"월"); break;
	case 1: strcpy(dayofweek,"화"); break;
	case 2: strcpy(dayofweek,"수"); break;
	case 3: strcpy(dayofweek,"목"); break;
	case 4: strcpy(dayofweek,"금"); break;
	case 5: strcpy(dayofweek,"토"); break;
	case 6: strcpy(dayofweek,"일"); break;
	}
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

	return dayofWeek;
}
void selectTime(int CombineTimetable[5][13],structPromise *newPromise,int dayofWeek){
	int errorCheck;
	char time[27];
	int Time;

	printf("약속시간을 입력(ex 3시)");
	scanf("%s",time);
		
	while(1){						//시간이 통합시간표에 겹치는 시간이면 재입력. 제대로 입력시 넘김
		errorCheck=0;
		Time = atoi(time);
		printf("%d ",Time);
		if(CombineTimetable[dayofWeek][Time-1]==1){
			printf("%d %d",dayofWeek,Time-1);
			errorCheck=1;
		}					
		if(errorCheck==0)
			break;
		printf("해당 시간은 비어있지 않습니다. 통합 시간표를 다시 한번 보고 선택한 날짜의 빈시간을 입력하세요: ");
		scanf("%s",&time);
	}
	strcpy(newPromise->promiseTime,time);			//자료 저장을 위한부분 임시로 여기에 삽입. 뒤에 장소DB가 만들어지고 장소함수도 만들어지면 그쪽으로 옮길 예정
	
}
void saveFriendsID(char ID[8], char *DB) {
	FILE *fp;
	char openDB[40];
	char listID[25]={0};
	char listName[13];
	int check=0;
	while(check!=1){		
								//회원목록 파일을 연다.
		strcpy(openDB,"회원목록.txt");
		fp = fopen(openDB, "r");

		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &listID, &listName);	//열어서 변수로 받은 이름과 학번을 읽는다

			if(!strcmp(listID,ID)){				//검색할 학번과 같은 학번을 찾으면 그이름을 학번뒤에 저장
				strcat(listID,listName);
				check=1;
				break;
			}
		}
	}
	fclose(fp);	
	strcpy(DB,listID);
}
void promiseCreatConsole(char *DBname) {	//약속만들기 함수.약속을 만드는데 필요함 함수들을 호출. 
	char Name[13];
	char select[3];
	char DB[25];
	struct structPromise newPromise;	//새로운 약속을 위한 구조체 생성 newPromise
	int CombineTimetable[5][13]={0};
	int count,i;
	int dayofWeek;

	selectName(DBname,&newPromise);
	count=selectFriends(DBname,CombineTimetable,&newPromise);
	scanf("%s",&select);
	dayofWeek=selectDate(CombineTimetable,&newPromise);		//selectDate함수를 호출한다. 날짜,요일,시간을 정하는 함수
	selectTime(CombineTimetable,&newPromise,dayofWeek);
	promisePlace(DBname,&newPromise);				//약속장소 선택함수 사용, (학번+이름, newPromise 구조체)를 인수로 넘긴다.
	saveNewpromise(DBname,&newPromise);
	for(i=0; i<count; i++) {
		saveFriendsID(newPromise.promiseFriendsName[i],DB);
		saveNewpromise(DB,&newPromise);
	}

	for(i=0; i<count; i++)		//동적할당 해제
		free(newPromise.promiseFriendsName[i]);
	free(newPromise.promiseFriendsName);

}
void selectName(char *DBname,struct structPromise *newPromise) {	//약속명 함수. (학번+이름)을 인수로 받는다.
	printf(" 약속 만들기 ");
	printf(" 약속명 : ");
	scanf("%s",&newPromise->promiseName);
}
int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise) {	//약속만들기 함수. 약속명, 인원수, 이름검색(함수호출)을 여기서 한다. (학번+이름)을 인수로 받는다.
	int i,j;
	int Count=0;
	int CountCopy;
	char Name[13];
	char control[3]={0};
	char nameList[70]={0};

	printf(" 인원수 : ");
	scanf("%s",&newPromise->promiseFreindsCount);
	Count=atoi(newPromise->promiseFreindsCount);				//인원수를 int형으로 바꿔주고 newPromise의 promiseFriendsCount 에 동적할당
	CountCopy=Count;
	newPromise->promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	//요건 +1로 하면 오류.. 왜그런지 이유 못알아냄.
	for(i=0; i<Count; i++){
		newPromise->promiseFriendsName[i]=(char *)malloc(sizeof(char)*20);
		for(j=0; j<13; j++)
			newPromise->promiseFriendsName[i][j]=NULL;
	}
	
	while(Count>0) {		//인원수만큼 검색함수를 돌린다.
		printf(" 이름검색 : ");
		scanf("%s",&Name);
		if(!searchName(Name,Count,*newPromise,CombineTimetable))	{	//이름 검색함수에서 리턴값을 받아온다. 받아온 리턴값이 1이면 이름이 없었던 경우이므로 Count값을 감소하지 않는다.
			Count--;
		strcat(nameList,Name);		
		printf("\n 약속멤버\n");		//리스트을 위해 nameList 문자열에 이름검색에 성공한 회원의 이름을 저장한다.					
		printf("%s",nameList);	
		strcat(nameList," ");
		}
	}
	
	printf("\n");
	if(recordCombineTimetable(CombineTimetable,DBname)==1)		//현재 로그인 되어있는 회원의 시간표 정보를 통합시간표에 추가... 없으면 알려주는 문구 출력
		printf("경고! 본인의 시간표정보가 없습니다.\n"); 
	for(i=0;i<5;i++){
		for(j=0; j<13; j++)
			printf("%d",CombineTimetable[i][j]);
		printf("\n");
	}

	printf("\n 약속멤버");			//리스트 출력부분
	printf("\n%s",nameList);		
	
	return CountCopy;
}

void showMenu() {				//약속만들기 메인 메뉴출력함수.
	printf("☆ 약속 메뉴 ☆\n");
	printf("1. 약속만들기\n");
	printf("2. 약속 수정\n");
	printf("3. 약속 삭제\n");	
	printf("▷ 메뉴 선택 : ");
}

void promise(structMember *s){		//약속만들기 메인함수. (현재로그인되한 회원구조체)를 변수로 받는다.

	char logID[8];
	char logName[13];
	char menuControl;
	char DBname[20];

	strcpy(logID,s->ID);
	strcpy(logName,s->name);			
	strcpy(DBname,logID);
	strcat(DBname,logName);				//구조체에서 이름과 학번을 가져와 하나의 문자열에 합쳐서 저장. '학번+이름'
	showMenu();

	promiseList(DBname);				//현재 로그인된 회원의 약속리스트 출력
	
	scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") 요건 화면을 지우고 다시 출력하게 하는 명령 <windows.h>필요
	case '1': system("cls"); promiseCreatConsole(DBname);  break;
	case '2': system("cls"); promiseChange(DBname); break;
	case '3': system("cls"); break;
	}

}
