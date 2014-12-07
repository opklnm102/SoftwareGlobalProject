#include"structHeader.h"
//개인파일로 만들시 꼭 위의 헤더랑 function.c 포함해서 작업해야함

void promiseList(char *DBname){			// 회원의 '학번+이름'을 매개변수로 받아와서 해당 회원의 약속리스트를 불러오는 함수,10개까지 간략하게 출력한다.
	FILE *fp;				//파일 포인터
	char openDB[35];		//오픈시킬 파일명
	char buffer[41];		//파일에서 읽어들인 값이 들어가는 임시 저장공간
	char promiseName[41];	//약속 이름을 저장		--> 약속이름과 날짜만 보여주는 함수이므로 이외의 정보들은 필요하지 않음
	char promiseDate[10];	//약속 날짜를 저장
	int listCount=0;		//리스트 개수
	int i;					//루프를 위한 변수
	int x=20, y=17;			//좌표 설정을 용이하게 만든 변수

	strcpy(openDB,DBname);					//매개변수로 받은 '학번+이름'에 PromiseList.txt를 붙인 이름을 가진 약속리스트를 읽기모드로 오픈
	strcat(openDB,"PromiseList.txt");
	fp = fopen(openDB, "r");

	if ( fp == NULL ) {						//파일이 없을 경우
		gotoxy(20, 32);printf("현재 생성된 약속리스트가 없습니다.");
		return ;
	}
	while (!feof(fp)) {			//약속리스트 열어서 약속의 이름과 날짜를 읽어서 출력, 최대 10개까지 출력
		gotoxy(16,13); printf("▷ 나의 약속리스트\n");
		fscanf(fp, "%s", &buffer);
		if(!strcmp(buffer,"약속리스트")){
			fscanf(fp,"%d", &listCount);
			gotoxy(20, 32); printf("현재 잡혀있는 약속 개수 %d",listCount);
			for(i=0; i<listCount; i++){
				fscanf(fp,"%s", promiseName);
				fgets(buffer,41,fp);
				fgets(buffer,41,fp);
				fgets(buffer,41,fp);
				fscanf(fp,"%s", promiseDate);
				fscanf(fp,"%s", buffer);
				fgets(buffer,41,fp);	
				fgets(buffer,41,fp);
				gotoxy(x,y);printf("○ %s / %s",promiseName,promiseDate);
				y=y+3;
				if(x==20&&y==32){		//한쪽에 5개를 찍은뒤 옆줄로 이동해서 다시 5개 찍음(최대 10개)
					x=44;
					y=17;
				}
				if(x==44&&y==32){		//10개를 꽉채워 찍은 경우 알림문구 표시
					gotoxy(17, 35);printf("나의 약속리스트는 10개까지만 표시됩니다.");
					gotoxy(17, 36);printf("상세한 약속을 보려면 약속보기를 선택하세요.");
					break;
				}
			}
		}
	}
	fclose(fp);
}

void changeLocation( char* str ) {		//문자열 처리함수. 한칸씩 떙기고 맨 뒤에 "\0"을 삽입하는 함수. 
	int len = strlen( str ); 
	int i;
	char temp = str[0]; 
	for( i=0; i<len; i++ )  
		str[ i ] = str[ i + 1]; 
	str[ len - 1 ] = '\0'; 
} 

int recordCombineTimetable(int CombineTimetable[5][13], char *DBname){		//통합시간표와 '학번+이름'문자열을 매개변수로 받아 통합시간표에 정보를 추가하는 함수. 0과1을 반환한다.
	FILE *fp;				//파일 포인터
	char openDB[40];		//오픈시킬 파일명
	char buffer[30];		//임시 저장공간
	char dayWeek[10];		//요일을 읽어올 문자열
	char Time[5]={0};		//시간이 들어갈 문자열
	char comma[1]={','};	//읽어올 timetable.txt에는 시간구분을 3,4,5 이런식으로 ','를 이용해 처리했으므로 문자열 처리를 위해 필요한 변수
	int dayweek,time,i,j;	//통합시간표 int형 이차원배열에 요일과 시간에 대한 정보를 넣기위해 필요한 변수들 dayweek에는 요일에 대한 정보가 time에는 시간에 대한 정보가 들어간다.	
	int length;				//문자열길이에 대한 값을 넣을 변수
	
	strcpy(openDB,DBname);			//매개변수로 받은 '학번+이름'에 timetable.txt를 붙인 이름을 가진 시간표정보를 읽기모드로 오픈
	strcat(openDB,"timetable.txt");		
	fp = fopen(openDB, "r");		

	if(!fp){						//만약 해당 회원의 시간표 정보가 없을 경우 1을 리턴. 
		return 1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s", &buffer);				//첫줄은 시간표 개수를 의미. 읽기만 하는 값. 필요없는 정보
		while(!feof(fp)){					
			fscanf(fp,"%s", &dayWeek);			//요일을 읽어온뒤 월,화,수,목,금 을 0,1,2,3,4 로 대응시켜 dayweek변수에 저장 
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
			fscanf(fp,"%s", &buffer);			//과목을 읽는다. 과목도 통합시간표를 만들때 불필요한 정보
			fscanf(fp,"%s",&buffer);			//시간을 읽는다.

			for(i=0;i<strlen(buffer);i++) {			//읽어들인 시간 문자열의 길이만큼 for문으로 한단어씩 개별처리를 한다.
				if(strncmp(buffer,comma,1)!=0){		//현재 시간문자열의 첫단어가 "," 가 아니면 
					strncat(Time,buffer,1);			//Time문자열에 시간문자열의 첫문자를 덧붙여서 삽입 
					changeLocation(buffer);			//changeLocatioin 함수를 사용. 시간문자열의 첫단어를 지우고 한칸씩 앞으로 땡겨준다.
				}
				if(strncmp(buffer,comma,1)==0) {		//현재 시간문자열의 첫단어가 "," 이면
					changeLocation(buffer);				//changeLocatioin 함수를 사용 ","삭제후 한칸씩 땡긴다.
					time=atoi(Time);					//Time 문자열을 변환시켜 정수형 time 변수에 삽입
					CombineTimetable[dayweek][time-1]=1;		//dayweek,time 변수를 이용. 통합시간표에서 해당하는 위치를 1로 변경
					length=strlen(Time);				
					for(j=0; j<length; j++)				//Time문자열 초기화
						Time[j]='\0';	
				}		
			}
			//길이만큼 for문을 돌리고 나오면 마지막 ','뒤의 자료처리가 남아있다. 
			time=atoi(buffer);					
			CombineTimetable[dayweek][time-1]=1;
			length=strlen(Time);
			for(j=0; j<length; j++)
				Time[j]='\0';
		}
	}			
	fclose(fp);

	return 0;				//정상적으로 파일을 읽어 처리했으면 0을 리턴 
}

void setMajor(char ID[8],char Major[20])	{		//학번7자리와 학과정보가 들어갈 문자열을 매개변수로 받고 학번 3,4번째자리의 숫자를 바탕으로 학과를 알아내는 함수
	FILE *fp;					//파일 포인터
	char IDCopy[8];				//문자열 처리를 간단하게 하기위해 학번복사본을 저장할 문자열
	char keyWord[3]={0};		//학과를 알아내는데 필요한 핵심정보인 학번의 3,4번째 숫자가 들어갈 문자열
	char number[3];				//텍스트 파일에서 읽어올 학과번호 정보를 저장할 문자열
	char major[20];				//텍스트 파일에서 읽어올 학과이름 정보를 저장할 문자열
	char noMajor[13];			//일치하는 학과 정보가 없을경우 처리를 위한 문자열
	
	strcpy(noMajor,"학과정보없음");		//학과정보와 일치하는게 없을때 출력해줄 문장

	strcpy(IDCopy,ID);			//학번을 복사본에 저장 이후 학번은 복사본문자열을 통해서 처리
	changeLocation(IDCopy);		//changeLocation함수를 이용해서 학번문자열의 첫번째 자리를 삭제하고 한칸씩 땡겨준다.
	changeLocation(IDCopy);		//두번반복을 통해 원래 학번 문자열의 3번째 자리가 맨앞에 오도록 변경되었다.
	strncpy(keyWord,IDCopy,2);	//현재 학번문자열의 1,2번째에 해당하는 문자 ,즉 원래 학번의 3,4번째에 해당하는 두 문자를 keyWord에 저장

	fp=fopen("major.txt","r");			//major.txt 여기에 학번, 학과 정보가 저장되어있음 
	
	if(fp == NULL){
		printf("학과정보 파일 오픈 불가");
		return;
	}
	while(!feof(fp)){					
		fscanf(fp,"%s %s",&number,&major);		//학과번호 정보와 학과정보를 읽는다.
		if(!strcmp(number,keyWord))	{			//학과번호와 keyWord가 일치하면 학과정보를 Major에 저장
			fclose(fp);							//파일을 닫고
			strcpy(Major,major);				//매개변수로 받은 Major문자열에 정보를 저장한뒤
			return;								//리턴
		}
	}
	fclose(fp);
	strcpy(Major,noMajor);		//일치하는 학과정보가 없었을경우 "학과정보없음"을 Major에 저장		
}

int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13],char *MyDB,char IDList[4][13]){		//이름검색함수.. (검색할이름, 함께하는회원중 리스트에 안올라간 회원수,새약속구조체,통합시간표,'학번+이름'문자열,현재 저장된 회원리스트) 를 변수로 받는다.
	FILE *fp;				//파일포인터
	FILE *fp1;
	char openDB[40];		//오픈시킬 파일명
	char buffer[30];
	char Time[5]={0};
	char select[2];
	char ID[8];
	char listName[13];
	char major[20]={0};
	int overlap=1;
	int limit=0;
	int i;
	int exist=0;
	char comma[1]={','};
	struct structMember friendID;		//이 구조체는 이 함수내부에서만 쓰임.. 별 효용은 없고 그냥 char두개 또 만들기 귀찮아서 써본 구조체...

	int x=32, y=22;
	listBorderDraw2(26,19);
	gotoxy(x+20,33);printf("           ");
	gotoxy(x,35);printf("                                                 ");
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
				if(strcmp(openDB,MyDB)&&strcmp(ID,IDList[0])&&strcmp(ID,IDList[1])&&strcmp(ID,IDList[2])&&strcmp(ID,IDList[3])){
					strcat(openDB,textFile);
					fp1 = fopen(openDB, "r");			//학번과 이름을 이용 해당회원정보파일을 읽는다.

					if ( !fp1 ) {						//없으면 브레이크 처리.. 만에하나 회원목록에는 있고 회원정보가 없는 경우를 체크함
						gotoxy(x,y);printf("%s회원의 정보가 없습니다.",name );
						exist=1;
						break;
					}

					while (!feof(fp1)) {				//회원정보에서 학번과 이름을 읽어와 구조체 friendID에 저장한다.
						fscanf(fp1, "%s", &buffer);
						if(!strcmp(buffer,"회원정보")){
							fscanf(fp1,"%s", friendID.ID);
							fscanf(fp1,"%s", friendID.name);
						}
					}
					setMajor(friendID.ID,major);		//setMajor함수 이용. 학과정보를 알아와서 major에 저장
					fclose(fp1);					//그뒤 회원정보파일을 닫고
					gotoxy(x,y);printf("%d  %s  %s  %s\n",overlap,major,friendID.ID,friendID.name);		//중복목록을 띄워주기 위해 출력을 해준다. 현재 학번을 학과로 바꾸는 부분이 빠져서 학번을 두번 출력하게 되있다.
					y=y+2;
					overlap++;						//리스트 번호를 증가시키고 반복...반복해서 같은 이름을 계속 찾아나간다.
				}
				
			}
			strcpy(ID,"\0");
			strcpy(listName,"\0");
				
		}
		fclose(fp);

		if(overlap==1){
				gotoxy(x,y);printf("%s회원의 정보가 없습니다.",name );	
				exist=1;
				break;
		}
		if(!strcmp(openDB,"회원목록.txt")){		//회원목록에 없는 이름을 검색했을 경우 처리
			gotoxy(x,y);printf("%s회원의 정보가 없습니다.",name);
			exist=1;							//exist를 1로 리턴. exist는 이 이름검색함수의 리턴값으로 쓰임. 함수를 부르는 단계에서 이 리턴값을 가지고 회원이름이 있는지 없는지를 체크해서 /
			break;								//같이 약속을 할 인원중 현재 리스트에 올라간 회원이 아닌 남은 회원수를 파악
		}

		gotoxy(x,33);printf("→ 이름번호 선택 : ");		//모든 리스트가 출력되면 리스트번호를 선택받는다.
		limit=overlap-1;
		while(1) {						//리스트 번호 범위 내의 수만 입력받기
			gotoxy(x+20,33);scanf("%s",select);
			if(!strcmp(select,"b")||!strcmp(select,"B"))
				return -1;
			overlap=atoi(select);	
			if(overlap>0&&overlap<=limit)
				break;
			gotoxy(x+20,33);printf("     ");
		}
		limit=1;
		strcpy(openDB,"회원목록");		//회원목록을 다시 연다.
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");

		while (!feof(fp)) {					//열어서 위에 입력받은 리스트 번호가 될때까지 읽어주며 값을 찾는다. 리스트 순서는 회원목록 순서와 같으므로 이렇게 처리한다.
			fscanf(fp, "%s %s", &ID, &listName);
			if(!strcmp(listName,name)&&strcmp(ID,IDList[0])&&strcmp(ID,IDList[1])&&strcmp(ID,IDList[2])&&strcmp(ID,IDList[3])){
				strcpy(openDB,ID);
				strcat(openDB,listName);
				if(strcmp(openDB,MyDB)){
					if(overlap==limit)
						break;
					limit++;
				}
			}
		}
		fclose(fp);
		strcpy(openDB,ID);					//선택된 회원의 학번과 이름을 하나로 합쳐서 저장
		strcat(openDB,name);
		if(recordCombineTimetable(CombineTimetable,openDB)==1){		//통합시간표 기록하는 함수 부름. 1이 돌아오면 해당 회원의 시간표 정보가 없는것
			gotoxy(x,35);printf("%s회원의 시간표정보가 없습니다.",name);
		}
		for(i=0; i<5; i++) {										//리스트에서 선택된 회원의 학번을 strcpy를 이용 구조체 newPromise 의 promiseFriendsName 에 복사붙여넣기 
			if(!strcmp(newPromise.promiseFriendsName[i],"\0")){
				strcpy(newPromise.promiseFriendsName[i],ID);

				break;
			}
		}

		strcpy(IDList[count-1],ID);
		break;
	}	
	return exist;			//exist를 리턴값으로 가진다. 이름검색이 됬으면 0이 리턴, 없는 이름이면 위에서 1을 리턴하게 되있다. 리스트번호 입력시 B,b키 입력시 -1리턴 
}

int callendar(int Month) {		//달력출력함수. 월을 인수로 넘겨받는다. selectDate 함수에서 입력받은 달을 넘겨받음.
	int last,th,year,day,date,x,z,y,m;
	time_t curr;
	int i=0;
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
	gotoxy(26,18);printf(" 일 월 화 수 목 금 토");		//입력받은 년도와 월의 달력을 출력만 하는 함수이다.
	gotoxy(26,19);printf(" --------------------");
	date=1;
	for(x=0;x<=6;x++)
	{	
		
		gotoxy(26,20+i);
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
		if(x==0)
		    i++;
		

	}

}

int weekday(int year, int month, int day) //년도, 월, 일 을 입력받아 요일 찾는 함수. 리턴값은 정수.
{
	int year_1 = year / 100;
	int year_2 = year - year_1 * 100;

	return (day + (month + 1) * 26 / 10 + year_2 + (year_2 / 4) + (year_1 / 4) - 2 * year_1 - 2) % 7;
}

int selectDate(int CombineTimetable[5][13],structPromise *newPromise){	//만들 약속의 날짜 입력받는 함수


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
	int x=26,y=12;

	system("cls");//이 함수 바로 전단계에서 화면에 출력된 문자들을 지워준다.
	screenBorderDraw();		
	gotoxy(56,8); printf("☆ 약속 만들기 ☆");
	gotoxy(x,y); printf("약속을 생성할 달을 입력하세요.");
	gotoxy(x,y+1); printf("달력이 나타나면 통합시간표를 참고해서 약속을 정할");
	gotoxy(x,y+2); printf("날짜를 입력하세요.");

	//통합시간표를 출력
	gotoxy(x+60,y-5);
	printf("┌─┬──┬──┬──┬──┬──┐");
	gotoxy(x+60,y-4); 
	printf("│  │ 월 │ 화 │ 수 │ 목 │ 금 │"); 
	gotoxy(x+60,y-3);
	printf("├─┼──┼──┼──┼──┼──┤");
	for(i=0; i<26; i+=2) { 
		gotoxy(x+60,y-2+i);
		printf("│%2d│    │    │    │    │    │",i/2+1);
		gotoxy(x+60,y-1+i);
		if(i!= 24)
			printf("├─┼──┼──┼──┼──┼──┤");
	}
	gotoxy(x+60,y+23);
	printf("└─┴──┴──┴──┴──┴──┘");

	for (i=0; i<5; i++) {  //통합시간표를 출력(겹치는 부분 붉은색)	
		for(j=0; j<13; j++){
			if(CombineTimetable[i][j]==1){				
				gotoxy(92+6*i,10+j*2);
				setcolor(4,4);
				printf("    ",CombineTimetable[i][j]);
				//setcolor(7,0);
			}			
		}
	}
	setcolor(0,15);  //글자색 복귀 글자(흑),배경(백)

	gotoxy(x,y+4); printf("약속을 잡을 달 입력(ex 3월) :");	
	gotoxy(x+30,y+4); scanf("%s",&month);								//월을 입력하면
	if(!strcmp(month,"b")||!strcmp(month,"B"))
		return -1;
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
	
	
	
	gotoxy(x,y+15);printf("요일은 날짜입력에 따라 자동으로 선택됩니다.");
	gotoxy(x,y+16);printf("날짜입력이 끝나면 약속시간(교시)을 입력하세요.");
	while(1){
		gotoxy(x,y+18);printf("약속을 잡을 날짜 입력(ex 10일) :");		//일을 입력하면
		gotoxy(x+34,y+18);scanf("%s",&day);
		if(!strcmp(day,"b")||!strcmp(day,"B"))
			return -1;
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
		dayofWeek=weekday(year,Month,Day);
		if(dayofWeek==0||dayofWeek==1||dayofWeek==2||dayofWeek==3||dayofWeek==4)
			break;
		gotoxy(x,y+19);printf("약속은 주중에만 잡을 수 있습니다.");
		gotoxy(x+34,y+18);printf("      ");
	}
	return dayofWeek;
}

void selectTime(int CombineTimetable[5][13],structPromise *newPromise,int dayofWeek){
	int errorCheck;
	char time[27];
	char timeCopy[27];
	char temp[10]={0};
	int i;
	int Time;
	int length;
	int x=26, y=31;
	strcpy(newPromise->promiseTime,"\0");	//B,b 입력 체크를 위해 초기화
	gotoxy(x,y);printf("약속시간을 입력(ex 3시) :");
	gotoxy(x+27,y);scanf("%s",&time);
	if(!strcmp(time,"b")||!strcmp(time,"B"))
		return;
	strcpy(timeCopy,time);
	length=strlen(temp);
	for(i=0; i<length; i++)
		temp[i]='\0';
	length=strlen(time);
	for(i=0;i<length;i++) {
		if(strncmp(time,"시",1)!=0){

			strncat(temp,time,1);
			changeLocation(time);
		}
		if(strncmp(time,"시",1)==0) {				//'월'이라는 단어를 제외하고 숫자부분만 떼내어서 정수형 변수 Month에 저장  
			Time=atoi(temp);
			break;
		}		
	}	
	while(1){						//시간이 통합시간표에 겹치는 시간이면 재입력. 제대로 입력시 넘김
		errorCheck=0;
		if(CombineTimetable[dayofWeek][Time-1]==1){
			errorCheck=1;
		}					
		if(errorCheck==0)
			break;
		gotoxy(x+27,y);printf("        ");
		gotoxy(x,y+1);printf("해당 시간은 비어있지 않습니다."); 
		gotoxy(x,y+2);printf("통합 시간표를 참고해서 선택한 날짜의 빈시간을 입력하세요");
		
		gotoxy(x+27,y);scanf("%s",&time);
		if(!strcmp(time,"b")||!strcmp(time,"B"))
			break;
		strcpy(timeCopy,time);
		length=strlen(temp);
		for(i=0; i<length; i++)
			temp[i]='\0';
		length=strlen(time);
		for(i=0;i<length;i++) {
			if(strncmp(time,"시",1)!=0){
				strncat(temp,time,1);
				changeLocation(time);
			}
			if(strncmp(time,"시",1)==0) {				//'월'이라는 단어를 제외하고 숫자부분만 떼내어서 정수형 변수 Month에 저장  
				Time=atoi(temp);
				break;
			}		
		}
	}
	if(!strcmp(time,"b")||!strcmp(time,"B"))
			return;
	strcpy(newPromise->promiseTime,timeCopy);			//자료 저장을 위한부분 임시로 여기에 삽입. 뒤에 장소DB가 만들어지고 장소함수도 만들어지면 그쪽으로 옮길 예정	
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

void promiseCreatConsole(char *DBname, char *logID) {	//약속만들기 함수.약속을 만드는데 필요함 함수들을 호출. 

	char DB[25];
	char friendNameCopy[8]={0};		
	struct structPromise newPromise;	//새로운 약속을 위한 구조체 생성 newPromise
	int CombineTimetable[5][13]={0};
	int count,i;
	int dayofWeek;
	int x=26,y=12;
	system("cls");
	screenBorderDraw();	
	
	gotoxy(56,8); printf("☆ 약속 만들기 ☆");
	gotoxy(x,y); printf(" 약속명 : ");
	gotoxy(x+50,y); printf(" 인원수 : ");
	gotoxy(x,y+4);printf(" 이름검색 : ");
	gotoxy(x+60,y+3);printf("▷ 약속멤버");
	listBorderDraw2(x,y+7);
	listBorderDraw3(x+60,y+4);
	selectName(DBname,&newPromise);
	if(!strcmp(newPromise.promiseName,"B")||!strcmp(newPromise.promiseName,"b"))
		return;
	count=selectFriends(DBname,CombineTimetable,&newPromise);
	if(count==0)
		return;
	gotoxy(128,44);Sleep(1000);	//자동으로 넘어가게
	dayofWeek=selectDate(CombineTimetable,&newPromise);		//selectDate함수를 호출한다. 날짜,요일,시간을 정하는 함수
	if(dayofWeek==-1){
		for(i=0;i<count;i++)
			free(newPromise.promiseFriendsName[i]);
		free(newPromise.promiseFriendsName);		
		return;
	}
	selectTime(CombineTimetable,&newPromise,dayofWeek);
	if(!strcmp(newPromise.promiseTime,"\0")) {
		for(i=0;i<count;i++)
			free(newPromise.promiseFriendsName[i]);
		free(newPromise.promiseFriendsName);		
		return;
	}
	Sleep(1000);
	promisePlace(DBname,&newPromise);				//약속장소 선택함수 사용, (학번+이름, newPromise 구조체)를 인수로 넘긴다.
	if(!strcmp(newPromise.promisePlace,"\0")){
		for(i=0;i<count;i++)
			free(newPromise.promiseFriendsName[i]);
		free(newPromise.promiseFriendsName);	
		return;
	}
	saveNewpromise(DBname,&newPromise);
	for(i=0; i<count; i++) {		//약속을 함께할 회원들의 개개인의 약속 리스트에 현재 약속정보를 저장하는 부분 
		saveFriendsID(newPromise.promiseFriendsName[i],DB);			//ex) a,b,c,d가 약속을 잡았다. a가 지금 로그인해서 약속을 만든 회원. a회원의 리스트에는 b,c,d가 저장되어있음
		strcpy(friendNameCopy,newPromise.promiseFriendsName[i]);	//지금 로그인 되어있는 회원의 아이디와 for문으로 선택된 함께 약속을 할 회원들중 하나의 아이디를 바꿔치기 해서 저장한다. 
		strcpy(newPromise.promiseFriendsName[i],logID);					//ex) b회원의 약속리스트에는 a,c,d || c회원의 약속리스트에는 b,a,d || d회원의 약속리스트에는 b,c,a 라는 정보가 저장된다.
		saveNewpromise(DB,&newPromise);
		strcpy(newPromise.promiseFriendsName[i],friendNameCopy);		
	}

	for(i=0; i<count; i++)		//동적할당 해제
		free(newPromise.promiseFriendsName[i]);
	free(newPromise.promiseFriendsName);

}

void selectName(char *DBname,struct structPromise *newPromise) {	//약속명 함수. (학번+이름)을 인수로 받는다.
	int x=26,y=12;
	gotoxy(x+10,y);scanf("%s",&newPromise->promiseName);  //@@@약속명 입력
	
}

int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise) {	//약속만들기 함수. 약속명, 인원수, 이름검색(함수호출)을 여기서 한다. (학번+이름)을 인수로 받는다.
	int i,j;
	int Count=0;
	int CountCopy;
	int check=0;
	char Name[13];
	char control[3]={0};
	char nameList[4][13]={0};
	char selectedNameList[4][13]={0};
	int x=26, y=12;
	
	gotoxy(x+60,y);scanf("%s",&newPromise->promiseFreindsCount); //@@@인원수 입력
	if(!strcmp(newPromise->promiseFreindsCount,"b")||!strcmp(newPromise->promiseFreindsCount,"B"))
		return 0;
	Count=atoi(newPromise->promiseFreindsCount);				//인원수를 int형으로 바꿔주고 newPromise의 promiseFriendsCount 에 동적할당
	CountCopy=Count;
	newPromise->promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	
	for(i=0; i<Count; i++){
		newPromise->promiseFriendsName[i]=(char *)malloc(sizeof(char)*20);
		for(j=0; j<13; j++)
			newPromise->promiseFriendsName[i][j]=NULL;
	}
	i=0;
	while(Count>0) {		//인원수만큼 검색함수를 돌린다.
		gotoxy(x+12,y+4);printf("                              ");
		gotoxy(x+12,y+4);scanf("%s",&Name);  //@@@검색할 이름 입력
		if(!strcmp(Name,"b")||!strcmp(Name,"B"))			
			break;
		check=searchName(Name,Count,*newPromise,CombineTimetable,DBname,selectedNameList);
		if(check==0)	{			//이름 검색함수에서 리턴값을 받아온다. 0이면 검색결과가 있었던 경우 ,받아온 리턴값이 1또는 -1이면 이름이 없었던 경우이거나 B,b키를 입력한것이므로 Count값을 감소하지 않는다.
			Count--;
			
			strcpy(nameList[i],Name);		
				
			gotoxy(x+64,y+6);printf("%s",nameList[0]);	//@@@이름리스트 출력
			gotoxy(x+64,y+8);printf("%s",nameList[1]);	//@@@이름리스트 출력
			gotoxy(x+64,y+10);printf("%s",nameList[2]);	//@@@이름리스트 출력
			gotoxy(x+64,y+12);printf("%s",nameList[3]);	//@@@이름리스트 출력
			i++;
		}
		else if(check==-1){
			for(i=0; i<Count; i++)
				free(newPromise->promiseFriendsName[i]);
			free(newPromise->promiseFriendsName);
			return 0;
		}
		
	}
	if(!strcmp(Name,"b")||!strcmp(Name,"B")){
		for(i=0; i<Count; i++)
			free(newPromise->promiseFriendsName[i]);
		free(newPromise->promiseFriendsName);	
		return 0;
	}
	if(recordCombineTimetable(CombineTimetable,DBname)==1)	{	//현재 로그인 되어있는 회원의 시간표 정보를 통합시간표에 추가... 없으면 알려주는 문구 출력
		gotoxy(32,35); printf("경고! 본인의 시간표정보가 없습니다."); 
	}
	
	return CountCopy;
}

void showMenu() {			//약속만들기 메인 메뉴출력함수.
	
	int x=80,y=32;	
	system("cls");
	 
	screenBorderDraw();	
	listBorderDraw(15,14);  //밖의 테두리

	gotoxy(x-23,y-24); printf("☆ 약속 메뉴 ☆");
	gotoxy(x,y-17); printf("1. 약속만들기");
	gotoxy(x,y-14); printf("2. 약속 수정");
	gotoxy(x,y-11); printf("3. 약속 삭제");	
	gotoxy(x,y-8); printf("4. 약속 상세보기");	
	gotoxy(x,y-5); printf("5. 나가기");	
	gotoxy(x,y);printf("▷ 메뉴 선택 : ");
}

int promise(structMember *s){		//약속만들기 메인함수. (현재로그인되한 회원구조체)를 변수로 받는다.

	char logID[8];
	char logName[13];
	char menuControl;
	char DBname[20];
	int check=1;
	
	strcpy(logID,s->ID);
	strcpy(logName,s->name);			
	strcpy(DBname,logID);
	strcat(DBname,logName);				//구조체에서 이름과 학번을 가져와 하나의 문자열에 합쳐서 저장. '학번+이름'
	showMenu();

	promiseList(DBname);				//현재 로그인된 회원의 약속리스트 출력
	
	gotoxy(96,32);scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") 요건 화면을 지우고 다시 출력하게 하는 명령 <windows.h>필요
	case '1':  promiseCreatConsole(DBname,logID);  break;
	case '2': while(check){system("cls"); check=promiseChange(DBname,logID); }break;
	case '3': while(check){system("cls"); check=deleteAllPromise(DBname,logID);} break;
	case '4': while(check){system("cls"); check=ViewAllPromise(DBname,logID);} break;
	}
	if(menuControl=='5'||menuControl =='B'||menuControl =='b')
		return 0;
	if(menuControl=='x'||menuControl =='X'){
		gotoxy(90,45);
		exit(0);
	}
	return 1;
}