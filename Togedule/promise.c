#include"structHeader.h"
//�������Ϸ� ����� �� ���� ����� function.c �����ؼ� �۾��ؾ���
//extern char dayOfWeek[5][4];  ����� �ű� ������ ��

int login1(char *name,struct structMember *loginID){	// �α����� ȸ���� ������ �о�ü� �ְ� ����� �Լ�	,name�� ���� �α����� ȸ���� �̸��� ä�������� �ȴ�.
	FILE *fp;
	char openDB[30];		//�̸��� ���� txt ������ �ҷ��ͼ� ������ �д´�.
	char textFile[]=".txt";
	char ID[8];
	char listName[13];
	char check[30];
	int listCount=0;
	int i;
	//int j,k;
	structPromise *promiseList;
	strcpy(openDB,"ȸ�����");
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
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		printf("ERROR : %s cannot open!\n",openDB );
		return -1;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"ȸ������")){
			fscanf(fp,"%s", loginID->ID);
			fscanf(fp,"%s", loginID->name);
			fscanf(fp,"%s", loginID->password);
			fscanf(fp,"%s", loginID->backupPassword);
		}


		if(!strcmp(check,"��Ӹ���Ʈ")){
			fscanf(fp,"%d", &listCount);
			promiseList=(structPromise*)malloc(sizeof(structPromise)*listCount);

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
	printf("���� ���\n");
	for(i=0; i<listCount; i++){
		printf("�� %s ",promiseList[i].promiseName);
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


int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13]){		//�̸� �˻��Լ�. txt������ �ߺ��̸��� ������.txt ������1.txt ������2.txt �̷����·� �����ؼ� Ǯ���.
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
	struct structMember friendID;	//���⼭ ���� structMember�� ���� ������ ���߿� �ڷ�����κп��� Ȥ�� ���ϱ� �ؼ�...

	FILE *fp;
	FILE *fp1;


	while(1){		//�̸��ߺ��� �ִ��� Ȯ���ϰ� ������ ������ ���� �̸��� �������� �ݺ��� (�ٱ� ����)
		char textFile[]=".txt";
		strcpy(openDB,"ȸ�����");
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
					printf("%sȸ���� ������ �����ϴ�.",name );
					exist=1;
					break;
				}

				while (!feof(fp1)) {			//�̸��� ������(�ߺ��˻��ϱ���. �׳� ������.txt �� �ִ°�� ������ �о��
					fscanf(fp1, "%s", &check);
					if(!strcmp(check,"ȸ������")){
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
		if(!strcmp(openDB,"ȸ�����.txt")){
			printf("%sȸ���� ������ �����ϴ�.",name);
			exist=1;
			break;
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
		strcpy(openDB,"ȸ�����");
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
		strcat(openDB,name);		//�� �κ��� ���� ������ ���߿� �� ȸ���� txt���Ͽ� ������ �����ϱ� ���ؼ� �� ���սð�ǥ ������ ����...
		strcat(openDB,"timetable");
		strcat(openDB,textFile);	//�ڿ� ��Ҽ��ñ��� ����ġ�� txt���Ͽ� �����ϴ� �κ��� ���� �������� �׋� ���� �պ��� �ش�ȸ��txt������ �ڷ� �Ѱ��ִ��� ���� �ڵ带 �����ؼ� ���� �ɵ�
		fp = fopen(openDB, "r");
		while (!feof(fp)) {
			fscanf(fp, "%s", &check);
			if(!strcmp(check,"�ð�ǥ")){  //8 �ð�ǥ ������ �ٲ������
				while(!feof(fp)){
					fscanf(fp,"%s", &dayWeek);
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



		for(i=0; i<5; i++) {		//�о������ ȸ�� �̸��� strcpy�� �̿� ����ü nwePromise �� promiseFriendsName �� ����ٿ��ֱ� 
			if(*newPromise.promiseFriendsName[i] == NULL){
				strcpy(newPromise.promiseFriendsName[i],friendID.name);
				break;
			}
		}
		break;
	}	
	return exist;
}
int callendar(int Month) {
	int last,th,year,day,date,x,z,y,m;
	time_t curr;

	struct tm *d;
	curr=time(NULL);
	d=localtime(&curr);
	year = d->tm_year;
	y=year+1900;
	m=Month;
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
	printf(" �� �� ȭ �� �� �� ��\n");
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

int weekday(int year, int month, int day) //���� ã�� �Լ� ���� ����
{
	int year_1 = year / 100;
	int year_2 = year - year_1 * 100;

	return (day + (month + 1) * 26 / 10 + year_2 + (year_2 / 4) + (year_1 / 4) - 2 * year_1 - 2) % 7;
}
void selectDate(int CombineTimetable[5][13]){	//����, �ð�, ��¥ �Է¹޴� �Լ�

	char dayofweek[3];
	char time[27];
	char month[10];
	char day[10];
	char temp[10]={0};
	int dayofWeek;
	int Time;
	int Day;
	int Month;
	int year;
	int i,j;
	int errorCheck;
	char dayOfWeek[5][4] = {"��","ȭ","��","��","��"};
	system("cls");
	printf("- ��� / ��¥ / �ð� -\n");
	printf("����� ������ ���ϰ� �ð��� ���ϰ�\n");
	printf("��¥�� �������ּ���.\n");
	printf("��) ������, ��, ȭ\n");
	printf("��) 5, 6, 7\n");
	printf("��) 10�� 30��\n");


	for (i=0; i<5; i++) {
		for(j=0; j<13; j++)
			printf("%d ",CombineTimetable[i][j]);
		printf("\n");
	}


	printf("����� ���� �� �Է�");		//���� �Է��ϸ� �ڵ����� ���� ���� �ش� ���� �޷� ���
	scanf("%s",&month);

	for(i=0;i<strlen(month);i++) {
		if(strncmp(month,"��",1)!=0){

			strncat(temp,month,1);
			changeLocation(month);
		}
		if(strncmp(month,"��",1)==0) {	
			Month=atoi(temp);
			break;
		}		
	}
	year=callendar(Month);			
	printf("����� ���� �� �Է�");		//���� �Է��ϸ�
	scanf("%s",&day);
	for(i=0; i<strlen(temp); i++)
		temp[i]='\0';
	for(i=0;i<strlen(day);i++) {
		if(strncmp(day,"��",1)!=0){
			strncat(temp,day,1);
			changeLocation(day);
		}
		if(strncmp(day,"��",1)==0) {
			Day=atoi(temp);
			break;
		}		
	} 
	switch(weekday(year,Month,Day)){		//�ش� ���� �� �Ͽ� �ش��ϴ� ������ ����ؼ� ����.
	case 0: strcpy(dayofweek,"��"); break;
	case 1: strcpy(dayofweek,"ȭ"); break;
	case 2: strcpy(dayofweek,"��"); break;
	case 3: strcpy(dayofweek,"��"); break;
	case 4: strcpy(dayofweek,"��"); break;
	case 5: strcpy(dayofweek,"��"); break;
	case 6: strcpy(dayofweek,"��"); break;
	}

	printf("�ð�");
	scanf("%s",time);

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
	while(1){		//�ð��� ���սð�ǥ�� ��ġ�� �ð��̸� ���Է�. ����� �Է½� �ѱ�
		errorCheck=0;
		Time = atoi(time);		
		if(CombineTimetable[dayofWeek][Time-1]==1){
			errorCheck=1;
		}					
		if(errorCheck==0)
			break;
		printf("���� �ð�ǥ�� ���� �Է��� ������ ��ð��� �Է��ϼ���: ");
		scanf("%s",&time);
	}
	printf("���������� �Ѿ�ϴ�.\n");
}

void promiseCreatConsole() {	//��Ӹ���� �Լ� (��Ӹ�, �ο��� �Է�  .�̸� �˻��Լ� ���� ����. ��� ����Ʈ ���)
	char Name[13];
	int i,j;
	int Count=0;
	struct structPromise newPromise;	//���ο� ����� ���� ����ü ���� newPromise
	int CombineTimetable[5][13]={0};
	char control[3]={0};

	printf(" ��� ����� ");
	printf(" ��Ӹ� : ");
	scanf("%s",&newPromise.promiseName);
	printf(" �ο��� : ");
	scanf("%s",&newPromise.promiseFreindsCount);

	Count=atoi(newPromise.promiseFreindsCount);		//�ο����� int������ �ٲ��ְ� newPromise�� promiseFriendsCount �� �����Ҵ�
	newPromise.promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	//��� +1�� �ϸ� ����.. �ֱ׷��� ���� ���˾Ƴ�.
	for(i=0; i<Count; i++){
		newPromise.promiseFriendsName[i]=(char *)malloc(sizeof(char)*13);
		for(j=0; j<13; j++)
			newPromise.promiseFriendsName[i][j]=NULL;
	}
	while(Count>0) {		//�ο�����ŭ �˻��Լ��� ������.
		printf(" �̸��˻� : ");
		scanf("%s",&Name);
		if(!searchName(Name,Count,newPromise,CombineTimetable))		//�̸� �˻��Լ����� ���ϰ��� �޾ƿ´�. �޾ƿ� ���ϰ��� 1�̸� �̸��� ������ ����̹Ƿ� Count���� �������� �ʴ´�.
			Count--;
	}
	printf("\n");
	for(i=0;i<5;i++){
		for(j=0; j<13; j++)
			printf("%d",CombineTimetable[i][j]);
		printf("\n");
	}

	printf("\n ��Ӹ��");			//����Ʈ ��ºκ�
	Count=atoi(newPromise.promiseFreindsCount);			//Count�� ������ 0���� ��������Ƿ� �ٽ� int������ ���ġ.
	for(i=0; i<Count; i++) {		
		printf("\n%s",newPromise.promiseFriendsName[i]);
	}
	printf("����������");
	scanf("%s",control);
	if(control)
		selectDate(CombineTimetable);


	for(i=0; i<Count; i++)		//�����Ҵ� ����
		free(newPromise.promiseFriendsName[i]);
	free(newPromise.promiseFriendsName);

}

void showMenu() {
	printf("�� ��� �޴� ��\n");
	printf("1. ��Ӹ����\n");
	printf("2. ��� ����\n");
	printf("3. ��� ����\n");	
	printf("�� �޴� ���� : ");
}

void promise(){

	char logID[8];
	struct structMember loginID;		//���� ȸ�������� ������ ����ü ����
	char menuControl;
	strcpy(logID,"������");				//�̸��� ������� txt������ ã�� ����. �̸��� logID�� �������ش�.

	showMenu();

	login1(logID,&loginID);				//����ȸ������ �Լ� ����

	scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") ��� ȭ���� ����� �ٽ� ����ϰ� �ϴ� ��� <windows.h>�ʿ�
	case '1': system("cls"); promiseCreatConsole(); break;
	case '2': system("cls"); break;
	case '3': system("cls"); break;
	}

}


//int main() {
//	char logID[8];
//	struct structMember loginID;		//���� ȸ�������� ������ ����ü ����
//	char menuControl;
//	strcpy(logID,"������");				//�̸��� ������� txt������ ã�� ����. �̸��� logID�� �������ش�.
//
//	showMenu();
//
//	login(logID,&loginID);				//����ȸ������ �Լ� ����
//
//	scanf("%c",&menuControl);
//	switch(menuControl) {		//system("cls") ��� ȭ���� ����� �ٽ� ����ϰ� �ϴ� ��� <windows.h>�ʿ�
//	case '1': system("cls"); promiseCreatConsole(); break;
//	case '2': system("cls"); break;
//	case '3': system("cls"); break;
//	}
//
//}