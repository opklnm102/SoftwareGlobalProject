#include"structHeader.h"
//�������Ϸ� ����� �� ���� ����� function.c �����ؼ� �۾��ؾ���
//extern char dayOfWeek[5][4];  ����� �ű� ������ ��

void promiseList(char *DBname){	// �α����� ȸ���� ��Ӹ���Ʈ�� �ҷ����� �Լ� , ��¸� �Ѵ�. ������� ���ٰ� ������ش�.
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
		printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return ;
	}
	while (!feof(fp)) {			//��Ӹ���Ʈ ��� ����Ʈ�� ������ ������ŭ �̸��� ��¥�� �о ����ϴ� �κ�
		printf("���� ���\n");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"��Ӹ���Ʈ")){
			fscanf(fp,"%d", &listCount);
			for(i=0; i<listCount; i++){
				fscanf(fp,"%s", promiseName);
				fgets(check,41,fp);
				fgets(check,41,fp);
				fgets(check,41,fp);
				fscanf(fp,"%s", promiseDate);
				fscanf(fp,"%s", check);
				fgets(check,41,fp);			//���� �ڸ� �߰�.
				fgets(check,41,fp);
				printf("�� %s ",promiseName);
				printf("/ %s\n",promiseDate);
			}
		}
	}
	fclose(fp);
}

void changeLocation( char* str ) {	//���ڿ� ó���Լ� ���پ� ����� �� �ڿ� ��������ϴ� �Լ�. 
	int len = strlen( str ); 
	int i;
	char temp = str[0]; 
	for( i=0; i<len; i++ )  
		str[ i ] = str[ i + 1]; 
	str[ len - 1 ] = '\0'; 
} 

int recordCombineTimetable(int CombineTimetable[5][13], char *DBname){		//���սð�ǥ�� ������ �߰��ϴ� �Լ�. ���սð�ǥ�� '�й�+�̸�' ���ڿ��� �μ��� �޾Ƽ� ó��.
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
	fp = fopen(openDB, "r");		//�ش� ȸ���� �ð�ǥ������ �о�´�.
	if(!fp){					//���� �ش� ȸ���� �ð�ǥ ������ ������� 1 ����. 
		return 1;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", &check);			//ù���� �ð�ǥ ����? �� �ǹ��Ѵٰ� �ؼ� �б⸸ �ϴ� ��. ���⼭ �Ⱦ��̴� ����
		while(!feof(fp)){					
			fscanf(fp,"%s", &dayWeek);		//������ �д´� �о ��ȭ����ݿ� �ش��ϴ� ������ �ڷ�� /ó��. 
			if(!strcmp(dayWeek,"��"))
				dayweek=0;
			else if(!strcmp(dayWeek,"ȭ"))
				dayweek=1;
			else if(!strcmp(dayWeek,"��"))
				dayweek=2;
			else if(!strcmp(dayWeek,"��"))
				dayweek=3;
			else if(!strcmp(dayWeek,"��"))
				dayweek=4;
			fscanf(fp,"%s", &check);		//������ �д´�. ���� ���սð�ǥ���� �Ⱦ��̴� �����̹Ƿ� �б⸸ �Ѵ�.
			fscanf(fp,"%s",&check);			//�ð��� �д´�.

			for(i=0;i<strlen(check);i++) {			//�ð� ���ڿ��� ���̸� �˾Ƴ��� for������ �Ѵܾ ����ó���� �Ѵ�.
				if(strncmp(check,comma,1)!=0){		//�ð����ڿ��� ù�ܾ "," �� �ƴϸ� 
					strncat(Time,check,1);			//Time�̶�� ���ڿ��� �ð����ڿ��� ù�ܾ ����. �����°� �ƴ϶� �ڿ� �����̴� �����̴�. 
					changeLocation(check);			//changeLocatioin �Լ��� ���. �ð����ڿ��� ù�ܾ ����� ��ĭ�� �����.
				}
				if(strncmp(check,comma,1)==0) {		//�ð����ڿ��� ù�ܾ "," �̸�
					changeLocation(check);			//�Լ��̿�. ","������ ��ĭ�� �����.
					time=atoi(Time);				//���ݱ��� ������ Time ���ڿ��� ������ time ������ ����
					CombineTimetable[dayweek][time-1]=1;		//������ ��ȯ���� ������ ���ϰ� �ð��� �̿�. ���սð�ǥ�� üũ
					length=strlen(Time);
					for(j=0; j<length; j++)
						Time[j]='\0';	
					}		
				}						
			time=atoi(check);					//�������ð��ڿ��� ","�� �Ⱥ����Ƿ� ���⼭ �ٽ��ѹ� ó��
			CombineTimetable[dayweek][time-1]=1;
			length=strlen(Time);
			for(j=0; j<length; j++)
				Time[j]='\0';
		}
	}			
	fclose(fp);
	return 0;		//���������� �о����� 0���� 
}

void setMajor(char ID[8],char Major[20])	{		//�й� 3,4�ڸ��� �������� �а� �˾Ƴ��� �Լ�
	char IDCopy[8];					
	char keyWord[3]={0};
	char major[20];
	char number[3];
	char noMajor[13];
	FILE *fp;

	strcpy(noMajor,"�а���������");		//�а������� ��ġ�ϴ°� ������ ������� ����
	strcpy(IDCopy,ID);
	changeLocation(IDCopy);
	changeLocation(IDCopy);
	strncpy(keyWord,IDCopy,2);
	fp=fopen("major.txt","r");			//major.txt ���⿡ �й�, �а� ������ ����Ǿ����� 
	
	while(!feof(fp)){					
		fscanf(fp,"%s %s",&number,&major);
		if(!strcmp(number,keyWord))	{			//��ġ�ϴ� �й��� ��� �а� ������ Major�� ����
			fclose(fp);
			strcpy(Major,major);
			return;
		}
	}
	fclose(fp);
	strcpy(Major,noMajor);		//������� "�а���������" �� Major�� ����		
}

int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13]){		//�̸��˻��Լ�.. (�˻����̸�, �Բ��ϴ�ȸ���� ����Ʈ�� �ȿö� ȸ����,����ӱ���ü,���սð�ǥ) �� ������ �޴´�.
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
	struct structMember friendID;		//�� ����ü�� �� �Լ����ο����� ����.. �� ȿ���� ���� �׳� char�ΰ� �� ����� �����Ƽ� �ẻ ����ü...
	FILE *fp;
	FILE *fp1;


	while(1){		
		char textFile[]=".txt";			//ȸ����� ������ ����.
		strcpy(openDB,"ȸ�����");
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");

		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &ID, &listName);	//��� ������ ���� �̸��� �й��� �д´�

			if(!strcmp(listName,name)){				//�˻��� �̸��� ���� �̸��̸�
				strcpy(openDB,ID);
				strcat(openDB,name);
				strcat(openDB,textFile);
				fp1 = fopen(openDB, "r");			//�й��� �̸��� �̿� �ش�ȸ������������ �д´�.

				if ( !fp1 ) {						//������ �극��ũ ó��.. �����ϳ� ȸ����Ͽ��� �ְ� ȸ�������� ���� ��츦 üũ��
					printf("%sȸ���� ������ �����ϴ�.",name );
					exist=1;
					break;
				}

				while (!feof(fp1)) {				//ȸ���������� �й��� �̸��� �о�� ����ü friendID�� �����Ѵ�.
					fscanf(fp1, "%s", &check);
					if(!strcmp(check,"ȸ������")){
						fscanf(fp1,"%s", friendID.ID);
						fscanf(fp1,"%s", friendID.name);
					}
				}
				setMajor(friendID.ID,major);		//setMajor�Լ� �̿�. �а������� �˾ƿͼ� major�� ����
				fclose(fp1);					//�׵� ȸ������������ �ݰ�
				printf("%d %s %s %s\n",overlap,major,friendID.ID,friendID.name);		//�ߺ������ ����ֱ� ���� ����� ���ش�. ���� �й��� �а��� �ٲٴ� �κ��� ������ �й��� �ι� ����ϰ� ���ִ�.
				overlap++;						//����Ʈ ��ȣ�� ������Ű�� �ݺ�...�ݺ��ؼ� ���� �̸��� ��� ã�Ƴ�����.
			}
		}
		fclose(fp);
		if(!strcmp(openDB,"ȸ�����.txt")){		//ȸ����Ͽ� ���� �̸��� �˻����� ��� ó��
			printf("%sȸ���� ������ �����ϴ�.",name);
			exist=1;							//exist�� 1�� ����. exist�� �� �̸��˻��Լ��� ���ϰ����� ����. �Լ��� �θ��� �ܰ迡�� �� ���ϰ��� ������ ȸ���̸��� �ִ��� �������� üũ�ؼ� /
			break;								//���� ����� �� �ο��� ���� ����Ʈ�� �ö� ȸ���� �ƴ� ���� ȸ������ �ľ�
		}

		printf("�� �̸���ȣ ���� : ");		//��� ����Ʈ�� ��µǸ� ����Ʈ��ȣ�� ���ù޴´�.
		limit=overlap-1;
		while(1) {						//����Ʈ ��ȣ ���� ���� ���� �Է¹ޱ�
			scanf("%s",select);
			overlap=atoi(select);	
			if(overlap>0&&overlap<=limit)
				break;
		}
		limit=1;
		strcpy(openDB,"ȸ�����");		//ȸ������� �ٽ� ����.
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");

		while (!feof(fp)) {					//��� ���� �Է¹��� ����Ʈ ��ȣ�� �ɶ����� �о��ָ� ���� ã�´�. ����Ʈ ������ ȸ����� ������ �����Ƿ� �̷��� ó���Ѵ�.
			fscanf(fp, "%s %s", &ID, &listName);
			if(!strcmp(listName,name)){
				if(overlap==limit)
					break;
				limit++;
			}
		}
		fclose(fp);
		strcpy(openDB,ID);					//���õ� ȸ���� �й��� �̸��� �ϳ��� ���ļ� ����
		strcat(openDB,name);
		if(recordCombineTimetable(CombineTimetable,openDB)==1)		//���սð�ǥ ����ϴ� �Լ� �θ�. 1�� ���ƿ��� �ش� ȸ���� �ð�ǥ ������ ���°�
			printf("%sȸ���� �ð�ǥ������ �����ϴ�.",name);
		for(i=0; i<5; i++) {										//����Ʈ���� ���õ� ȸ���� �й��� strcpy�� �̿� ����ü newPromise �� promiseFriendsName �� ����ٿ��ֱ� 
			if(!strcmp(newPromise.promiseFriendsName[i],"\0")){
				strcpy(newPromise.promiseFriendsName[i],ID);
				break;
			}
		}
		break;
	}	
	return exist;			//exist�� ���ϰ����� ������. �̸��˻��� ������ 0�� ����, ���� �̸��̸� ������ 1�� �����ϰ� ���ִ�.
}
int callendar(int Month) {		//�޷�����Լ�. ���� �μ��� �Ѱܹ޴´�. selectDate �Լ����� �Է¹��� ���� �Ѱܹ���.
	int last,th,year,day,date,x,z,y,m;
	time_t curr;

	struct tm *d;
	curr=time(NULL);
	d=localtime(&curr);
	year = d->tm_year;
	y=year+1900;			//���� �⵵�� ���.. 2014���� ����ȴ�. 
	m=Month;				//���� �μ��� �״�� �̿�
	if((m>=1)&&(m<=12))		//����� �� �޸��� 31��, 30��, 28��, 29�� �� �����ִ� �κ�
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
	printf(" �� �� ȭ �� �� �� ��\n");		//�Է¹��� �⵵�� ���� �޷��� ��¸� �ϴ� �Լ��̴�.
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

int weekday(int year, int month, int day) //�⵵, ��, �� �� �Է¹޾� ���� ã�� �Լ�. ���ϰ��� ����.
{
	int year_1 = year / 100;
	int year_2 = year - year_1 * 100;

	return (day + (month + 1) * 26 / 10 + year_2 + (year_2 / 4) + (year_1 / 4) - 2 * year_1 - 2) % 7;
}
int selectDate(int CombineTimetable[5][13],structPromise *newPromise){	//���� ����� ����, �ð�, ��¥ �Է¹޴� ������ �ϴ� �Լ� (���սð�ǥ, �й�+�̸� ���ڿ�, ����ӱ���ü)�� �μ��� �޴´�.

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

	system("cls");				//�� �Լ� �ٷ� ���ܰ迡�� ȭ�鿡 ��µ� ���ڵ��� �����ش�.
	printf("- ��� / ��¥ / �ð� -\n");
	printf("����� ������ ���� �Է��ϼ���.\n");
	printf("�޷��� ��Ÿ���� ���սð�ǥ�� �����ؼ� ����� ���� ��¥�� �Է��ϼ���.\n");
	printf("������ ��¥�Է¿� ���� �ڵ����� ���õ˴ϴ�.\n");
	printf("��¥�Է��� ������ ��ӽð�(����)�� �Է��ϼ���.\n");
	printf("��) 10��\n");
	printf("��) 30��\n");
	printf("��) 1\n");

	printf(" ��   ȭ   ��   ��   ��\n");
	for(j=0; j<13; j++) {		//���սð�ǥ�� ��� (�ӽ�). �ð�ǥ ����ϴ� �κа� �����ؼ� ����� ǥ�� ¥�� ����ؾ���
		for (i=0; i<5; i++){
			if(CombineTimetable[i][j]==1)
				printf("��� ",CombineTimetable[i][j]);
			if(CombineTimetable[i][j]==0)
				printf("��� ",CombineTimetable[i][j]);
		}
		printf("\n");
	}

	printf("����� ���� �� �Է�(ex 3��) :");	
	scanf("%s",&month);								//���� �Է��ϸ�
	length=strlen(month);
	for(i=0;i<length;i++) {
		if(strncmp(month,"��",1)!=0){

			strncat(temp,month,1);
			changeLocation(month);
		}
		if(strncmp(month,"��",1)==0) {				//'��'�̶�� �ܾ �����ϰ� ���ںκи� ����� ������ ���� Month�� ����  
			Month=atoi(temp);
			break;
		}		
	}
	strcpy(newPromise->Promisedate,temp);
	strcat(newPromise->Promisedate,"/");
	year=callendar(Month);							//�Է¹��� ���� ������ callendar�Լ����. ���� �޷��� ��� 
	printf("����� ���� ��¥ �Է�(ex 10��) :");		//���� �Է��ϸ�
	scanf("%s",&day);
	length=strlen(temp);
	for(i=0; i<length; i++)
		temp[i]='\0';
	length=strlen(day);
	for(i=0;i<length;i++) {
		if(strncmp(day,"��",1)!=0){
			strncat(temp,day,1);
			changeLocation(day);
		}
		if(strncmp(day,"��",1)==0) {				//'��'�̶�� �ܾ �����ϰ� ���ںκи� ����� ������ ���� Day�� ����  
			Day=atoi(temp);
			break;
		}		
	} 
	strcat(newPromise->Promisedate,temp);
	switch(weekday(year,Month,Day)){		//weekday�Լ����, �ش� ���� �� �Ͽ� �ش��ϴ� ������ ����ؼ� ����.
	case 0: strcpy(dayofweek,"��"); break;
	case 1: strcpy(dayofweek,"ȭ"); break;
	case 2: strcpy(dayofweek,"��"); break;
	case 3: strcpy(dayofweek,"��"); break;
	case 4: strcpy(dayofweek,"��"); break;
	case 5: strcpy(dayofweek,"��"); break;
	case 6: strcpy(dayofweek,"��"); break;
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

	printf("��ӽð��� �Է�(ex 3��)");
	scanf("%s",time);
		
	while(1){						//�ð��� ���սð�ǥ�� ��ġ�� �ð��̸� ���Է�. ����� �Է½� �ѱ�
		errorCheck=0;
		Time = atoi(time);
		printf("%d ",Time);
		if(CombineTimetable[dayofWeek][Time-1]==1){
			printf("%d %d",dayofWeek,Time-1);
			errorCheck=1;
		}					
		if(errorCheck==0)
			break;
		printf("�ش� �ð��� ������� �ʽ��ϴ�. ���� �ð�ǥ�� �ٽ� �ѹ� ���� ������ ��¥�� ��ð��� �Է��ϼ���: ");
		scanf("%s",&time);
	}
	strcpy(newPromise->promiseTime,time);			//�ڷ� ������ ���Ѻκ� �ӽ÷� ���⿡ ����. �ڿ� ���DB�� ��������� ����Լ��� ��������� �������� �ű� ����
	
}
void saveFriendsID(char ID[8], char *DB) {
	FILE *fp;
	char openDB[40];
	char listID[25]={0};
	char listName[13];
	int check=0;
	while(check!=1){		
								//ȸ����� ������ ����.
		strcpy(openDB,"ȸ�����.txt");
		fp = fopen(openDB, "r");

		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &listID, &listName);	//��� ������ ���� �̸��� �й��� �д´�

			if(!strcmp(listID,ID)){				//�˻��� �й��� ���� �й��� ã���� ���̸��� �й��ڿ� ����
				strcat(listID,listName);
				check=1;
				break;
			}
		}
	}
	fclose(fp);	
	strcpy(DB,listID);
}
void promiseCreatConsole(char *DBname) {	//��Ӹ���� �Լ�.����� ����µ� �ʿ��� �Լ����� ȣ��. 
	char Name[13];
	char select[3];
	char DB[25];
	struct structPromise newPromise;	//���ο� ����� ���� ����ü ���� newPromise
	int CombineTimetable[5][13]={0};
	int count,i;
	int dayofWeek;

	selectName(DBname,&newPromise);
	count=selectFriends(DBname,CombineTimetable,&newPromise);
	scanf("%s",&select);
	dayofWeek=selectDate(CombineTimetable,&newPromise);		//selectDate�Լ��� ȣ���Ѵ�. ��¥,����,�ð��� ���ϴ� �Լ�
	selectTime(CombineTimetable,&newPromise,dayofWeek);
	promisePlace(DBname,&newPromise);				//������ �����Լ� ���, (�й�+�̸�, newPromise ����ü)�� �μ��� �ѱ��.
	saveNewpromise(DBname,&newPromise);
	for(i=0; i<count; i++) {
		saveFriendsID(newPromise.promiseFriendsName[i],DB);
		saveNewpromise(DB,&newPromise);
	}

	for(i=0; i<count; i++)		//�����Ҵ� ����
		free(newPromise.promiseFriendsName[i]);
	free(newPromise.promiseFriendsName);

}
void selectName(char *DBname,struct structPromise *newPromise) {	//��Ӹ� �Լ�. (�й�+�̸�)�� �μ��� �޴´�.
	printf(" ��� ����� ");
	printf(" ��Ӹ� : ");
	scanf("%s",&newPromise->promiseName);
}
int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise) {	//��Ӹ���� �Լ�. ��Ӹ�, �ο���, �̸��˻�(�Լ�ȣ��)�� ���⼭ �Ѵ�. (�й�+�̸�)�� �μ��� �޴´�.
	int i,j;
	int Count=0;
	int CountCopy;
	char Name[13];
	char control[3]={0};
	char nameList[70]={0};

	printf(" �ο��� : ");
	scanf("%s",&newPromise->promiseFreindsCount);
	Count=atoi(newPromise->promiseFreindsCount);				//�ο����� int������ �ٲ��ְ� newPromise�� promiseFriendsCount �� �����Ҵ�
	CountCopy=Count;
	newPromise->promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	//��� +1�� �ϸ� ����.. �ֱ׷��� ���� ���˾Ƴ�.
	for(i=0; i<Count; i++){
		newPromise->promiseFriendsName[i]=(char *)malloc(sizeof(char)*20);
		for(j=0; j<13; j++)
			newPromise->promiseFriendsName[i][j]=NULL;
	}
	
	while(Count>0) {		//�ο�����ŭ �˻��Լ��� ������.
		printf(" �̸��˻� : ");
		scanf("%s",&Name);
		if(!searchName(Name,Count,*newPromise,CombineTimetable))	{	//�̸� �˻��Լ����� ���ϰ��� �޾ƿ´�. �޾ƿ� ���ϰ��� 1�̸� �̸��� ������ ����̹Ƿ� Count���� �������� �ʴ´�.
			Count--;
		strcat(nameList,Name);		
		printf("\n ��Ӹ��\n");		//����Ʈ�� ���� nameList ���ڿ��� �̸��˻��� ������ ȸ���� �̸��� �����Ѵ�.					
		printf("%s",nameList);	
		strcat(nameList," ");
		}
	}
	
	printf("\n");
	if(recordCombineTimetable(CombineTimetable,DBname)==1)		//���� �α��� �Ǿ��ִ� ȸ���� �ð�ǥ ������ ���սð�ǥ�� �߰�... ������ �˷��ִ� ���� ���
		printf("���! ������ �ð�ǥ������ �����ϴ�.\n"); 
	for(i=0;i<5;i++){
		for(j=0; j<13; j++)
			printf("%d",CombineTimetable[i][j]);
		printf("\n");
	}

	printf("\n ��Ӹ��");			//����Ʈ ��ºκ�
	printf("\n%s",nameList);		
	
	return CountCopy;
}

void showMenu() {				//��Ӹ���� ���� �޴�����Լ�.
	printf("�� ��� �޴� ��\n");
	printf("1. ��Ӹ����\n");
	printf("2. ��� ����\n");
	printf("3. ��� ����\n");	
	printf("�� �޴� ���� : ");
}

void promise(structMember *s){		//��Ӹ���� �����Լ�. (����α��ε��� ȸ������ü)�� ������ �޴´�.

	char logID[8];
	char logName[13];
	char menuControl;
	char DBname[20];

	strcpy(logID,s->ID);
	strcpy(logName,s->name);			
	strcpy(DBname,logID);
	strcat(DBname,logName);				//����ü���� �̸��� �й��� ������ �ϳ��� ���ڿ��� ���ļ� ����. '�й�+�̸�'
	showMenu();

	promiseList(DBname);				//���� �α��ε� ȸ���� ��Ӹ���Ʈ ���
	
	scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") ��� ȭ���� ����� �ٽ� ����ϰ� �ϴ� ��� <windows.h>�ʿ�
	case '1': system("cls"); promiseCreatConsole(DBname);  break;
	case '2': system("cls"); promiseChange(DBname); break;
	case '3': system("cls"); break;
	}

}
