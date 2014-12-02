#include"structHeader.h"
//�������Ϸ� ����� �� ���� ����� function.c �����ؼ� �۾��ؾ���
char dayOfWeek[5][4];

void promiseList(char *DBname){	// �α����� ȸ���� ��Ӹ���Ʈ�� �ҷ����� �Լ� , ��¸� �Ѵ�. ������� ���ٰ� ������ش�.
	FILE *fp;
	char openDB[30];
	char textFile[]=".txt";
	char check[41];
	char promiseName[41];
	char promiseDate[10];
	int listCount=0;
	int i;
	int x=20, y=17;
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(20, 32);printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return ;
	}
	while (!feof(fp)) {			//��Ӹ���Ʈ ��� ����Ʈ�� ������ ������ŭ �̸��� ��¥�� �о ����ϴ� �κ�
		gotoxy(16,13); printf("�� ���� ��Ӹ���Ʈ\n");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"��Ӹ���Ʈ")){
			fscanf(fp,"%d", &listCount);
			gotoxy(20, 32); printf("���� �����ִ� ��� ���� %d",listCount);
			for(i=0; i<listCount; i++){
				fscanf(fp,"%s", promiseName);
				fgets(check,41,fp);
				fgets(check,41,fp);
				fgets(check,41,fp);
				fscanf(fp,"%s", promiseDate);
				fscanf(fp,"%s", check);
				fgets(check,41,fp);			//���� �ڸ� �߰�.
				fgets(check,41,fp);
				gotoxy(x,y);printf("�� %s / %s",promiseName,promiseDate);
				y=y+3;
				if(x==20&&y==32){
					x=44;
					y=17;
				}
				if(x==44&&y==32){
					gotoxy(17, 35);printf("���� ��Ӹ���Ʈ�� 10�������� ǥ�õ˴ϴ�.");
					gotoxy(17, 36);printf("���� ����� ������ ��Ӻ��⸦ �����ϼ���.");
					break;
				}
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

int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13],char *MyDB){		//�̸��˻��Լ�.. (�˻����̸�, �Բ��ϴ�ȸ���� ����Ʈ�� �ȿö� ȸ����,����ӱ���ü,���սð�ǥ) �� ������ �޴´�.
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
	int x=32, y=22;
	listBorderDraw2(26,19);
	gotoxy(x+20,33);printf("           ");
	gotoxy(x,35);printf("                                                 ");
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
				if(strcmp(openDB,MyDB)){
					strcat(openDB,textFile);
					fp1 = fopen(openDB, "r");			//�й��� �̸��� �̿� �ش�ȸ������������ �д´�.

					if ( !fp1 ) {						//������ �극��ũ ó��.. �����ϳ� ȸ����Ͽ��� �ְ� ȸ�������� ���� ��츦 üũ��
						gotoxy(x,y);printf("%sȸ���� ������ �����ϴ�.",name );
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
					gotoxy(x,y);printf("%d  %s  %s  %s\n",overlap,major,friendID.ID,friendID.name);		//�ߺ������ ����ֱ� ���� ����� ���ش�. ���� �й��� �а��� �ٲٴ� �κ��� ������ �й��� �ι� ����ϰ� ���ִ�.
					y=y+2;
					overlap++;						//����Ʈ ��ȣ�� ������Ű�� �ݺ�...�ݺ��ؼ� ���� �̸��� ��� ã�Ƴ�����.
				}
			}
		}
		fclose(fp);
		if(!strcmp(openDB,"ȸ�����.txt")){		//ȸ����Ͽ� ���� �̸��� �˻����� ��� ó��
			gotoxy(x,y);printf("%sȸ���� ������ �����ϴ�.",name);
			exist=1;							//exist�� 1�� ����. exist�� �� �̸��˻��Լ��� ���ϰ����� ����. �Լ��� �θ��� �ܰ迡�� �� ���ϰ��� ������ ȸ���̸��� �ִ��� �������� üũ�ؼ� /
			break;								//���� ����� �� �ο��� ���� ����Ʈ�� �ö� ȸ���� �ƴ� ���� ȸ������ �ľ�
		}

		gotoxy(x,33);printf("�� �̸���ȣ ���� : ");		//��� ����Ʈ�� ��µǸ� ����Ʈ��ȣ�� ���ù޴´�.
		limit=overlap-1;
		while(1) {						//����Ʈ ��ȣ ���� ���� ���� �Է¹ޱ�
			gotoxy(x+20,33);scanf("%s",select);
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
		strcpy(openDB,ID);					//���õ� ȸ���� �й��� �̸��� �ϳ��� ���ļ� ����
		strcat(openDB,name);
		if(recordCombineTimetable(CombineTimetable,openDB)==1){		//���սð�ǥ ����ϴ� �Լ� �θ�. 1�� ���ƿ��� �ش� ȸ���� �ð�ǥ ������ ���°�
			gotoxy(x,35);printf("%sȸ���� �ð�ǥ������ �����ϴ�.",name);
		}
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
	int i=0;
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
	gotoxy(26,17);printf(" �� �� ȭ �� �� �� ��");		//�Է¹��� �⵵�� ���� �޷��� ��¸� �ϴ� �Լ��̴�.
	gotoxy(26,18);printf(" --------------------");
	date=1;
	for(x=0;x<=6;x++)
	{	
		
		gotoxy(26,19+i);
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

int weekday(int year, int month, int day) //�⵵, ��, �� �� �Է¹޾� ���� ã�� �Լ�. ���ϰ��� ����.
{
	int year_1 = year / 100;
	int year_2 = year - year_1 * 100;

	return (day + (month + 1) * 26 / 10 + year_2 + (year_2 / 4) + (year_1 / 4) - 2 * year_1 - 2) % 7;
}

int selectDate(int CombineTimetable[5][13],structPromise *newPromise){	//���� ����� ��¥ �Է¹޴� �Լ�


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

	system("cls");//�� �Լ� �ٷ� ���ܰ迡�� ȭ�鿡 ��µ� ���ڵ��� �����ش�.
	screenBorderDraw();		
	gotoxy(56,8); printf("�� ��� ����� ��");
	gotoxy(x,y); printf("����� ������ ���� �Է��ϼ���.");
	gotoxy(x,y+1); printf("�޷��� ��Ÿ���� ���սð�ǥ�� �����ؼ� ����� ���� ��¥�� �Է��ϼ���.");


	gotoxy(x,y+3); printf("����� ���� �� �Է�(ex 3��) :");	
	gotoxy(x+30,y+3); scanf("%s",&month);								//���� �Է��ϸ�
	length=strlen(month);
	gotoxy(x+60,y+3);printf(" ��   ȭ   ��   ��   ��");
	for(j=0; j<13; j++) {		//���սð�ǥ�� ��� (�ӽ�). �ð�ǥ ����ϴ� �κа� �����ؼ� ����� ǥ�� ¥�� ����ؾ���
		for (i=0; i<5; i++){
			if(CombineTimetable[i][j]==1){
				gotoxy(x+60+(5*i),y+4+j);printf("��� ",CombineTimetable[i][j]);
			}
			if(CombineTimetable[i][j]==0){
				gotoxy(x+60+(5*i),y+4+j);printf("��� ",CombineTimetable[i][j]);
			}
		}
	}

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
	
	
	
	gotoxy(x,y+14);printf("������ ��¥�Է¿� ���� �ڵ����� ���õ˴ϴ�.");
	gotoxy(x,y+15);printf("��¥�Է��� ������ ��ӽð�(����)�� �Է��ϼ���.");
	
	gotoxy(x,y+17);printf("����� ���� ��¥ �Է�(ex 10��) :");		//���� �Է��ϸ�
	gotoxy(x+34,y+17);scanf("%s",&day);
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
	dayofWeek=weekday(year,Month,Day);
	
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
	int x=26, y=30;

	gotoxy(x,y);printf("��ӽð��� �Է�(ex 3��) :");
	gotoxy(x+27,y);scanf("%s",&time);
	strcpy(timeCopy,time);
	length=strlen(temp);
	for(i=0; i<length; i++)
		temp[i]='\0';
	length=strlen(time);
	for(i=0;i<length;i++) {
		if(strncmp(time,"��",1)!=0){

			strncat(temp,time,1);
			changeLocation(time);
		}
		if(strncmp(time,"��",1)==0) {				//'��'�̶�� �ܾ �����ϰ� ���ںκи� ����� ������ ���� Month�� ����  
			Time=atoi(temp);
			break;
		}		
	}	
	while(1){						//�ð��� ���սð�ǥ�� ��ġ�� �ð��̸� ���Է�. ����� �Է½� �ѱ�
		errorCheck=0;
		if(CombineTimetable[dayofWeek][Time-1]==1){
			errorCheck=1;
		}					
		if(errorCheck==0)
			break;
		gotoxy(x+27,y);printf("        ");
		gotoxy(x,y+1);printf("�ش� �ð��� ������� �ʽ��ϴ�. ���� �ð�ǥ�� �ٽ� �ѹ� ���� ������ ��¥�� ��ð��� �Է��ϼ���");
		
		gotoxy(x+27,y);scanf("%s",&time);
		strcpy(timeCopy,time);
		length=strlen(temp);
		for(i=0; i<length; i++)
			temp[i]='\0';
		length=strlen(time);
		for(i=0;i<length;i++) {
			if(strncmp(time,"��",1)!=0){
				strncat(temp,time,1);
				changeLocation(time);
			}
			if(strncmp(time,"��",1)==0) {				//'��'�̶�� �ܾ �����ϰ� ���ںκи� ����� ������ ���� Month�� ����  
				Time=atoi(temp);
				break;
			}		
		}
	}
	strcpy(newPromise->promiseTime,timeCopy);			//�ڷ� ������ ���Ѻκ� �ӽ÷� ���⿡ ����. �ڿ� ���DB�� ��������� ����Լ��� ��������� �������� �ű� ����
	
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

void promiseCreatConsole(char *DBname, char *logID) {	//��Ӹ���� �Լ�.����� ����µ� �ʿ��� �Լ����� ȣ��. 

	char DB[25];
	char friendNameCopy[8]={0};		
	struct structPromise newPromise;	//���ο� ����� ���� ����ü ���� newPromise
	int CombineTimetable[5][13]={0};
	int count,i;
	int dayofWeek;
	int x=26,y=12;
	system("cls");
	screenBorderDraw();	
	
	gotoxy(56,8); printf("�� ��� ����� ��");
	gotoxy(x,y); printf(" ��Ӹ� : ");
	gotoxy(x+50,y); printf(" �ο��� : ");
	gotoxy(x,y+4);printf(" �̸��˻� : ");
	gotoxy(x+60,y+3);printf("�� ��Ӹ��");
	listBorderDraw2(x,y+7);
	listBorderDraw3(x+60,y+4);
	selectName(DBname,&newPromise);
	count=selectFriends(DBname,CombineTimetable,&newPromise);
	Sleep(1000);	//�ڵ����� �Ѿ��
	dayofWeek=selectDate(CombineTimetable,&newPromise);		//selectDate�Լ��� ȣ���Ѵ�. ��¥,����,�ð��� ���ϴ� �Լ�
	selectTime(CombineTimetable,&newPromise,dayofWeek);
	Sleep(1000);
	promisePlace(DBname,&newPromise);				//������ �����Լ� ���, (�й�+�̸�, newPromise ����ü)�� �μ��� �ѱ��.
	saveNewpromise(DBname,&newPromise);
	for(i=0; i<count; i++) {		//����� �Բ��� ȸ������ �������� ��� ����Ʈ�� ���� ��������� �����ϴ� �κ� 
		saveFriendsID(newPromise.promiseFriendsName[i],DB);			//ex) a,b,c,d�� ����� ��Ҵ�. a�� ���� �α����ؼ� ����� ���� ȸ��. aȸ���� ����Ʈ���� b,c,d�� ����Ǿ�����
		strcpy(friendNameCopy,newPromise.promiseFriendsName[i]);	//���� �α��� �Ǿ��ִ� ȸ���� ���̵�� for������ ���õ� �Բ� ����� �� ȸ������ �ϳ��� ���̵� �ٲ�ġ�� �ؼ� �����Ѵ�. 
		strcpy(newPromise.promiseFriendsName[i],logID);					//ex) bȸ���� ��Ӹ���Ʈ���� a,c,d || cȸ���� ��Ӹ���Ʈ���� b,a,d || dȸ���� ��Ӹ���Ʈ���� b,c,a ��� ������ ����ȴ�.
		saveNewpromise(DB,&newPromise);
		strcpy(newPromise.promiseFriendsName[i],friendNameCopy);		
	}

	for(i=0; i<count; i++)		//�����Ҵ� ����
		free(newPromise.promiseFriendsName[i]);
	free(newPromise.promiseFriendsName);

}

void selectName(char *DBname,struct structPromise *newPromise) {	//��Ӹ� �Լ�. (�й�+�̸�)�� �μ��� �޴´�.
	int x=26,y=12;
	gotoxy(x+10,y);scanf("%s",&newPromise->promiseName);  //@@@��Ӹ� �Է�
}

int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise) {	//��Ӹ���� �Լ�. ��Ӹ�, �ο���, �̸��˻�(�Լ�ȣ��)�� ���⼭ �Ѵ�. (�й�+�̸�)�� �μ��� �޴´�.
	int i,j;
	int Count=0;
	int CountCopy;
	char Name[13];
	char control[3]={0};
	char nameList[4][13]={0};
	int x=26, y=12;

	gotoxy(x+60,y);scanf("%s",&newPromise->promiseFreindsCount); //@@@�ο��� �Է�
	Count=atoi(newPromise->promiseFreindsCount);				//�ο����� int������ �ٲ��ְ� newPromise�� promiseFriendsCount �� �����Ҵ�
	CountCopy=Count;
	newPromise->promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	//��� +1�� �ϸ� ����.. �ֱ׷��� ���� ���˾Ƴ�.
	for(i=0; i<Count; i++){
		newPromise->promiseFriendsName[i]=(char *)malloc(sizeof(char)*20);
		for(j=0; j<13; j++)
			newPromise->promiseFriendsName[i][j]=NULL;
	}
	i=0;
	while(Count>0) {		//�ο�����ŭ �˻��Լ��� ������.
		gotoxy(x+12,y+4);printf("                              ");
		gotoxy(x+12,y+4);scanf("%s",&Name);  //@@@�˻��� �̸� �Է�
		
		if(!searchName(Name,Count,*newPromise,CombineTimetable,DBname))	{	//�̸� �˻��Լ����� ���ϰ��� �޾ƿ´�. �޾ƿ� ���ϰ��� 1�̸� �̸��� ������ ����̹Ƿ� Count���� �������� �ʴ´�.
			Count--;
			
			strcpy(nameList[i],Name);		
				//����Ʈ�� ���� nameList ���ڿ��� �̸��˻��� ������ ȸ���� �̸��� �����Ѵ�.					
			gotoxy(x+64,y+6);printf("%s",nameList[0]);	//@@@�̸�����Ʈ ���
			gotoxy(x+64,y+8);printf("%s",nameList[1]);	//@@@�̸�����Ʈ ���
			gotoxy(x+64,y+10);printf("%s",nameList[2]);	//@@@�̸�����Ʈ ���
			gotoxy(x+64,y+12);printf("%s",nameList[3]);	//@@@�̸�����Ʈ ���
			i++;
		}
		
	}
	
	printf("\n");
	if(recordCombineTimetable(CombineTimetable,DBname)==1)	{	//���� �α��� �Ǿ��ִ� ȸ���� �ð�ǥ ������ ���սð�ǥ�� �߰�... ������ �˷��ִ� ���� ���
		gotoxy(32,35); printf("���! ������ �ð�ǥ������ �����ϴ�."); 
	}
	
	return CountCopy;
}

void showMenu() {			//��Ӹ���� ���� �޴�����Լ�.
	
	int x=80,y=32;	
	system("cls");
	 
	screenBorderDraw();	
	listBorderDraw(15,14);  //���� �׵θ�

	gotoxy(x-23,y-24); printf("�� ��� �޴� ��");
	gotoxy(x,y-17); printf("1. ��Ӹ����");
	gotoxy(x,y-14); printf("2. ��� ����");
	gotoxy(x,y-11); printf("3. ��� ����");	
	gotoxy(x,y-8); printf("4. ��� ����");	
	gotoxy(x,y);printf("�� �޴� ���� : ");
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
	
	gotoxy(96,32);scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") ��� ȭ���� ����� �ٽ� ����ϰ� �ϴ� ��� <windows.h>�ʿ�
	case '1':  promiseCreatConsole(DBname,logID);  break;
	case '2': system("cls"); promiseChange(DBname,logID); break;
	case '3': system("cls"); break;
	}

}