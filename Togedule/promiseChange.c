#include"structHeader.h"

void changePlace(char *DBname, struct structPromise *old) {
	char blank[1]={0};
	promisePlace(DBname,old);
	old->promisePlace[strlen(old->promisePlace)-1]=blank[0];           //���DB���� �о�ö� \n �ϳ� ����ִ°� ���ּ� �ڵ��ٹٲ� ����
}
// �̸������� ������ ����� ��ӻ������ִ°� �����Ѱ�, ������ ���� ���� �Ϸ�..
void changeTime(struct structPromise *old,int newCombineTimetable[5][13],int dayofweek) {
	int i,j;
	char dayofWeek[5];
	printf(" ��   ȭ   ��   ��   ��\n");
	for(j=0; j<13; j++) {		//���սð�ǥ�� ��� (�ӽ�). �ð�ǥ ����ϴ� �κа� �����ؼ� ����� ǥ�� ¥�� ����ؾ���
		for (i=0; i<5; i++){
			if(newCombineTimetable[i][j]==1)
				printf("��� ",newCombineTimetable[i][j]);
			if(newCombineTimetable[i][j]==0)
				printf("��� ",newCombineTimetable[i][j]);
		}
		printf("\n");
	}
	switch(dayofweek){		//weekday�Լ����, �ش� ���� �� �Ͽ� �ش��ϴ� ������ ����ؼ� ����.
	case 0: strcpy(dayofWeek,"��"); break;
	case 1: strcpy(dayofWeek,"ȭ"); break;
	case 2: strcpy(dayofWeek,"��"); break;
	case 3: strcpy(dayofWeek,"��"); break;
	case 4: strcpy(dayofWeek,"��"); break;
	}
	printf("���� ��ӿ���>> %s\n",dayofWeek);
	printf("���� ��ӽð�>> %s\n",old->promiseTime);
	printf("%d",dayofweek);
	selectTime(newCombineTimetable,old,dayofweek);
}
int changeDate(struct structPromise *old,int newCombineTimetable[5][13]) {
	int dayofweek;
	int time;
	dayofweek=selectDate(newCombineTimetable,old);
	time=atoi(old->promiseTime);
	if(newCombineTimetable[dayofweek][time-1]==1) {
		printf("���� ������ �ð����� ����� ���� �� �����ϴ�. �ð��� �����ϰڽ��ϴ�.\n");
		changeTime(old,newCombineTimetable,dayofweek);
	}
	return dayofweek;
}
void changePromiseName(struct structPromise *old){
	printf("������ ��Ӹ� �Է� >> ");
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

	check=checkDateTime(newCombineTimetable,old);  //������ �ð��� ���� �ٲ� ���սð�ǥ�� �񱳽� ��ӽð��� �������� �˻�.....
	if(check!=0){
		printf("�ش� ������� �ð�ǥ�δ� ���� ����� ���� �� �����ϴ�. ��¥�� �ð��� �����ϰڽ��ϴ�.\n");
		changeDate(old,newCombineTimetable);
	}
	for(i=0; i<count; i++)		//�����Ҵ� ����
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
	printf("��Ӽ���\n");
	printf("1. ��Ӹ�   : %s\n",old[listnumber].promiseName);
	printf("2. ������ : %s\n",old[listnumber].promisePlace);
	printf("3. ��ӳ�¥ : %s\n",old[listnumber].Promisedate);
	printf("4. ��ӽð� : %s\n",old[listnumber].promiseTime);
	printf("5. �Բ��� ģ�� : ");
	for(i=0; i<4; i++)
		printf("%s ",name[i]);
	printf("\n");
	while(1){
	printf("������ ������ �����ϼ���.\n");
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
	printf("1. ��Ӹ�   : %s\n",old[listnumber].promiseName);
	printf("2. ������ : %s\n",old[listnumber].promisePlace);
	printf("3. ��ӳ�¥ : %s\n",old[listnumber].Promisedate);
	printf("4. ��ӽð� : %s\n",old[listnumber].promiseTime);
	printf("5. �Բ��� ģ�� : ");
	for(i=0; i<4; i++)
		printf("%s ",name[i]);
	printf("\n");
	printf("������ �Ϸ������� y�� �Է��ϼ���. ����Ϸ��� �ٸ�Ű�� �Է��ϼ���.");
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
		printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return ;
	}
	while (!feof(fp)) {			//��Ӹ���Ʈ ��� ����Ʈ�� ������ ������ŭ �̸��� ��¥�� �о ����ϴ� �κ�
		printf("���� ��Ӹ���Ʈ\n");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"��Ӹ���Ʈ")){
			fscanf(fp,"%d", &listCount);

			oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*listCount);		//�о�� ����� �����ϱ����� ��ӱ���ü
			for(i=0; i<listCount; i++) {															//��������� �Ҷ��ʹ� �޸� �̹����� �й��� �ϳ��� �� �о ���� �� ����� �����ϴ� ȸ�������� ���� ó���ؾ������� 
				oldPromise[i].promiseFriendsName=(char**)malloc(sizeof(char*)*4+1);					//�����Ҵ��� promiseFriendsName���� ���ش�. 
					for(j=0; j<4; j++) {													
						oldPromise[i].promiseFriendsName[j]=(char*)malloc(sizeof(char)*8);
						strcpy(oldPromise[i].promiseFriendsName[j],"\0");
						for(k=0; k<8; k++)
							strcpy(&oldPromise[i].promiseFriendsName[j][k],"\0");
					}
			}


			friendsName=(char**)malloc(sizeof(char*)*listCount);									//�ϴ� �й��� ���ٴ����� ������ �������� �װ��� �о���� ���ڿ��� �ϳ� �����Ҵ��Ѵ�.
			for(i=0; i<listCount; i++) {
				friendsName[i]=(char*)malloc(sizeof(char)*60);
				strcpy(friendsName[i],"\0");
					for(j=0; j<60; j++)
						strcpy(&friendsName[i][j],"\0");
			}

			cost=(char**)malloc(sizeof(char*)*listCount);						//����� ��Ӽ������� �Ⱦ��̴� �����̹Ƿ� �׳� �о��ֱ⸸ �Ѵ�.. �ʿ����
			for(i=0; i<listCount; i++) {													
				cost[i]=(char*)malloc(sizeof(char)*10);
				strcpy(cost[i],"\0");
					for(j=0; j<10; j++)
						strcpy(&cost[i][j],"\0");
			}

			for(i=0; i<listCount; i++) {								//�ϴ� ��Ӹ���Ʈ������ŭ ����� �о�ͼ� oldPromise����ü�� ������� ����
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
	printf("�� �����Ͻ� ��� : ");
	while(1) {						//����Ʈ ��ȣ ���� ���� ���� �Է¹ޱ�
		scanf("%s",select);
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<=numbering)
			break;
		printf("����Ʈ ���� ��ȣ�� �Է��ϼ��� : ");
	}
	listnumber--;

	length=strlen(friendsName[listnumber]);			//�ٴ����� ���� �й����� 7�ھ� ��� �̸� �Ҵ��س��� promiseFriendsName�� �ϳ��� �־��ִ� �κ�
	for(i=0; i<4; i++) {							//���⼭�� ���� ȸ������ üũ�Ϸ��� �������� 4�� �ݺ������ϵ��� ����, �ڽ����� �ִ� 5���̹Ƿ� ����Ǵ� �ٸ� ȸ�������� 4��
		strncpy(oldPromise[listnumber].promiseFriendsName[i],friendsName[listnumber],7);
		for(j=0; j<7; j++)
			changeLocation(friendsName[listnumber]);
		if(strncmp(friendsName[listnumber],",",1)==0)
			changeLocation(friendsName[listnumber]);
		else
			break;		
	}
	
	transName=(char**)malloc(sizeof(char*)*4+1);					//�й��� �׳� ���� ������ �̸����� �ٲ� ���ڹ迭�� �� �����Ҵ� ���ش�.
	for(i=0; i<4; i++) {													
		transName[i]=(char*)malloc(sizeof(char)*13);
		strcpy(transName[i],"\0");
		for(j=0; j<13; j++)
			strcpy(&transName[i][j],"\0");
	}

	strcpy(openDB,"ȸ�����.txt");						//�й��� �̸����� �ٲ��ش�. ȸ����� txt�� 5������ ���� �ݰ� �ϸ� �ݺ�... ȸ�� ���ڸ� ����ϱ� �������Ƿ� �׳� 5�� �ݺ�
	for(i=0;i<4;i++){
		fp = fopen(openDB, "r");
		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &ID, &listName);										//�й��� �̸��� ���� �д´�.
			if(!strcmp(ID,oldPromise[listnumber].promiseFriendsName[i])){				//�˻��� �й��� ���� �й��̸�
				strcpy(transName[i],listName);											//transName ���ڹ迭�� ���� ���� �̸��� ����
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
	
	oldPromise[listnumber].promisePlace[strlen(oldPromise[listnumber].promisePlace)-1]=blank[0];           //���DB���� �о�ö� \n �ϳ� ����ִ°� ���ּ� �ڵ��ٹٲ� ����
	printf("\n");
	printf("��Ӹ�      ���        ��¥      �ð�      �Բ���ģ��\n");
	printf("%s    %s     %s     %s\n",oldPromise[listnumber].promiseName,oldPromise[listnumber].promisePlace,oldPromise[listnumber].promiseTime,oldPromise[listnumber].Promisedate);
	for(i=0; i<4; i++)
		printf("%s ",transName[i]);
	printf("\n");
	printf("�����Ͻðڽ��ϱ�? <Y,N>");
	scanf("%s",&select);
	
	if(!strcmp(select,"y"))									//y�� Y�϶� ���� �ܰ�� �Ѿ
		selectChange(DBname,oldPromise,listnumber,transName,CombineTimetable);		//selectChange �Լ����, (�����о�� ��Ӹ���Ʈ��������ü, ����ڰ� ������ ��Ӹ���Ʈ��ȣ, �Բ��ϴ� ȸ�� �̸�)�� �μ��� �Ѱ��ش�.
	else if(!strcmp(select,"Y"))
		selectChange(DBname,oldPromise,listnumber,transName,CombineTimetable);

	for(i=0;i<listCount; i++)			//�����Ҵ� ����
		free(friendsName[i]);				
	free(friendsName);
	for(i=0; i<4; i++)			
		free(transName[i]);				
	free(transName);
	/*for(i=0;i<listCount; i++){			������ ��������
		for(j=0; j<4; j++)
			free(oldPromise[i].promiseFriendsName[j]);				
		free(oldPromise[i].promiseFriendsName);
	}*/		
	for(i=0;i<listCount; i++)			
		free(cost[i]);				
	free(cost);
	free(oldPromise);	
}