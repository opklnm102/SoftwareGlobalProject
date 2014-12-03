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
	gotoxy(53,8); printf("�� ��� �ð����� ��");
	gotoxy(x+60,y+3);printf(" ��   ȭ   ��   ��   ��");
	for(j=0; j<13; j++) {		//���սð�ǥ�� ��� (�ӽ�). �ð�ǥ ����ϴ� �κа� �����ؼ� ����� ǥ�� ¥�� ����ؾ���
		for (i=0; i<5; i++){
			if(newCombineTimetable[i][j]==1){
				gotoxy(x+60+(5*i),y+4+j);printf("��� ",newCombineTimetable[i][j]);
			}
			if(newCombineTimetable[i][j]==0){
				gotoxy(x+60+(5*i),y+4+j);printf("��� ",newCombineTimetable[i][j]);
			}
		}
	}
	switch(dayofweek){		//weekday�Լ����, �ش� ���� �� �Ͽ� �ش��ϴ� ������ ����ؼ� ����.
	case 0: strcpy(dayofWeek,"��"); break;
	case 1: strcpy(dayofWeek,"ȭ"); break;
	case 2: strcpy(dayofWeek,"��"); break;
	case 3: strcpy(dayofWeek,"��"); break;
	case 4: strcpy(dayofWeek,"��"); break;
	}
	gotoxy(x+60,y+18);printf("���� ����� ��ӿ���>> %s\n",dayofWeek);
	gotoxy(x+60,y+19);printf("���� ����� ��ӽð�>> %s\n",old->promiseTime);
	selectTime(newCombineTimetable,old,dayofweek);
}

int changeDate(struct structPromise *old,int newCombineTimetable[5][13]) {
	int dayofweek;
	int time;
	dayofweek=selectDate(newCombineTimetable,old);
	time=atoi(old->promiseTime);
	if(newCombineTimetable[dayofweek][time-1]==1) {
		gotoxy(26,34);printf("���� ������ �ð����� ����� ���� �� �����ϴ�. �ð��� �����ϰڽ��ϴ�.\n");
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
	gotoxy(53,8); printf("�� ��� ������� ��");
	gotoxy(x+50,y); printf(" �ο��� : ");
	gotoxy(x,y+4);printf(" �̸��˻� : ");
	gotoxy(x+60,y+3);printf("�� ��Ӹ��");
	listBorderDraw2(x,y+7);
	listBorderDraw3(x+60,y+4);
	count=selectFriends(DBname, newCombineTimetable,old);
	
	check=checkDateTime(newCombineTimetable,old);  //������ �ð��� ���� �ٲ� ���սð�ǥ�� �񱳽� ��ӽð��� �������� �˻�.....
	if(check!=0){
		gotoxy(x,y+24);printf("�ش� ������� �ð�ǥ�δ� ���� ����� ���� �� �����ϴ�. ��¥�� �ð��� �����ϰڽ��ϴ�.\n");
		Sleep(2000);
		changeDate(old,newCombineTimetable);
	}
	return count;
}

void showBG(char copyPromiseName[41],char copyPromisePlace[40],char copyPromisedate[10],char copyPromiseTime[6],char copyName[50]){
		system("cls");
		screenBorderDraw();
		gotoxy(56,8); printf("�� ��Ӽ��� ��");
		gotoxy(42,13);printf("1. ��Ӹ�       : %s",copyPromiseName);
		gotoxy(42,15);printf("2. ������     : %s",copyPromisePlace);
		gotoxy(42,17);printf("3. ��ӳ�¥     : %s",copyPromisedate);
		gotoxy(42,19);printf("4. ��ӽð�     : %s",copyPromiseTime);
		gotoxy(42,21);printf("5. �Բ��� ģ��  : %s",copyName);
		
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
		gotoxy(42,26);printf("1. ��Ӹ�       : %s",old->promiseName);
		gotoxy(42,28);printf("2. ������     : %s",old->promisePlace);
		gotoxy(42,30);printf("3. ��ӳ�¥     : %s",old->Promisedate);
		gotoxy(42,32);printf("4. ��ӽð�     : %s",old->promiseTime);
		gotoxy(42,34);printf("5. �Բ��� ģ��  : ");
		strcpy(copyName,name[0]);
		for(i=0; i<4; i++){
			printf("%s  ",name[i]);
		}
		
		gotoxy(42,11);printf("������ ������ �����ϼ��� :");
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
			strcpy(DB,"ȸ�����.txt");						//�й��� �̸����� �ٲ��ش�. ȸ����� txt�� 5������ ���� �ݰ� �ϸ� �ݺ�... ȸ�� ���ڸ� ����ϱ� �������Ƿ� �׳� 5�� �ݺ�
			for(i=0;i<4;i++)
				strcpy(name[i],"\0");
			for(i=0;i<friendsCount;i++){
				fp = fopen(DB, "r");
				while (!feof(fp)) {		
					fscanf(fp, "%s %s", &ID, &listName);										//�й��� �̸��� ���� �д´�.
					if(!strcmp(ID,old->promiseFriendsName[i])){				//�˻��� �й��� ���� �й��̸�
						strcpy(name[i],listName);											//transName ���ڹ迭�� ���� ���� �̸��� ����
						break;
					}
				}
				fclose(fp);
			}
			showBG(copyPromiseName,copyPromisePlace,copyPromisedate,copyPromiseTime,copyName);
		}
		gotoxy(42,26);printf("1. ��Ӹ�       : %s",old->promiseName);
		gotoxy(42,28);printf("2. ������     : %s",old->promisePlace);
		gotoxy(42,30);printf("3. ��ӳ�¥     : %s",old->Promisedate);
		gotoxy(42,32);printf("4. ��ӽð�     : %s",old->promiseTime);
		gotoxy(42,34);printf("5. �Բ��� ģ��  : ");
		strcpy(copyName,name[0]);
		for(i=0; i<4; i++){
			printf("%s  ",name[i]);
		}
		
		gotoxy(40,38);printf("������ �Ϸ������� y�� �Է��ϼ���. ����Ϸ��� �ٸ�Ű�� �Է��ϼ��� :");
		gotoxy(107,38);scanf("%s",&select);
		if(!strcmp(select,"y"))
			break;	
		gotoxy(69,11);printf("         ");
		gotoxy(40,38);printf("                                                                           ");	
		}
		return check;	//check ���� ���� check�� 1�̸� �̸������� �̷������, 0�̸� �̸������� ��������
		
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
	gotoxy(56,6); printf("�� ��Ӽ��� ��");
	gotoxy(54,8); printf("- ���� ��Ӹ���Ʈ -");
	listBorderDraw2(x,y);
	recordCombineTimetable(CombineTimetable,DBname);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(x+12,y+1);printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return ;
	}
	while (!feof(fp)) {			//��Ӹ���Ʈ ��� ����Ʈ�� ������ ������ŭ �̸��� ��¥�� �о ����ϴ� �κ�
		
		gotoxy(x+8,y+1); printf("��Ӹ�                      ��ӳ�¥");
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
			}
			for(i=0; i<listCount; i++) {	
				if(i==5){
						gotoxy(35,10); printf("��������Ʈ�� ������ >Ű�� �Է��ϼ���. ��ȣ�� �����Ϸ��� ~Ű�� �Է��ϼ���.");
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
							gotoxy(x+8,y+1); printf("��Ӹ�                      ��ӳ�¥");
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(35,10);printf("                                                                                  ");
						

					}
					else if(i!=0&&i!=5&&i%5==0&&i+1!=listCount){
						gotoxy(35,10);printf("��������Ʈ <, ��������Ʈ >, ��ȣ�� �����Ϸ��� ~Ű�� �Է��ϼ���.");
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
							gotoxy(x+8,y+1); printf("��Ӹ�                      ��ӳ�¥");
							strcpy(controlList,"\0");
						}
						else if(!strcmp(controlList,"<")){
							listBorderDraw2(35,11);
							gotoxy(x+8,y+1); printf("��Ӹ�                      ��ӳ�¥");
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
						gotoxy(35,10);printf("ó������ ���ư����� <Ű�� �Է��ϼ���.��ȣ�� �����Ϸ��� ~Ű�� �Է��ϼ���.");
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
							gotoxy(x+8,y+1); printf("��Ӹ�                      ��ӳ�¥");
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
	gotoxy(35,25);printf("�� �����Ͻ� ��� : ");
	while(1) {						//����Ʈ ��ȣ ���� ���� ���� �Է¹ޱ�
		gotoxy(54,25);scanf("%s",select);
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<=numbering)
			break;
		gotoxy(35,26);printf("����Ʈ ���� ��ȣ�� �Է��ϼ���");
		gotoxy(54,25);printf("       ");
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
	oldPromise[listnumber].promisePlace[strlen(oldPromise[listnumber].promisePlace)-1]=blank[0];           //���DB���� �о�ö� \n �ϳ� ����ִ°� ���ּ� �ڵ��ٹٲ� ����

	listBorderDraw2(35,26);

	gotoxy(38,28);printf("��Ӹ� >>     %s",oldPromise[listnumber].promiseName);
	gotoxy(38,30);printf("���   >>     %s",oldPromise[listnumber].promisePlace);
	gotoxy(38,32);printf("��¥   >>     %s",oldPromise[listnumber].Promisedate);
	gotoxy(38,34);printf("�ð�   >>     %s",oldPromise[listnumber].promiseTime);
	gotoxy(38,36);printf("�Բ���ģ�� >>   ");

	for(i=0; i<4; i++)
		printf("%s ",transName[i]);
	gotoxy(38,40);printf("�����Ͻðڽ��ϱ�? <Y,N>");
	gotoxy(63,40);scanf("%s",&select);
	changePromise.promiseFriendsName=(char**)malloc(sizeof(char*)*j+1);
	for(i=0; i<j; i++) {
		changePromise.promiseFriendsName[i]=(char*)malloc(sizeof(char)*8);
			strcpy(changePromise.promiseFriendsName[i],"\0");
				for(k=0; k<8; k++)
					strcpy(&changePromise.promiseFriendsName[i][k],"\0");
	}
	//changePromise ����ü�� �����ϱ�� ���õ� ����� ������ ���� ����
	strcpy(changePromise.promiseName,oldPromise[listnumber].promiseName);
	strcpy(changePromise.promisePlace,oldPromise[listnumber].promisePlace);
	strcpy(changePromise.promiseTime,oldPromise[listnumber].promiseTime);
	strcpy(changePromise.Promisedate,oldPromise[listnumber].Promisedate);
	for(i=0; i<j; i++) {
		strcpy(changePromise.promiseFriendsName[i],oldPromise[listnumber].promiseFriendsName[i]);
	}
	
	if(!strcmp(select,"y"))									//y�� Y�϶� ���� �ܰ�� �Ѿ
		Check=selectChange(DBname,&changePromise,listnumber,transName,CombineTimetable,checkPlace);		//selectChange �Լ����, (�����о�� ��Ӹ���Ʈ��������ü, ����ڰ� ������ ��Ӹ���Ʈ��ȣ, �Բ��ϴ� ȸ�� �̸�)�� �μ��� �Ѱ��ش�.
	else if(!strcmp(select,"Y"))
		Check=selectChange(DBname,&changePromise,listnumber,transName,CombineTimetable,checkPlace);
	
	friendsCount=atoi(oldPromise[listnumber].promiseFreindsCount);
	if(Check==1) {	
		strcpy(cost[listnumber],"\n");
		friendsCount=atoi(changePromise.promiseFreindsCount);//�Բ��� ģ���̸����� �����Ǿ��� ��� �� ���� int������ �ٲ� �����Ѵ�.
		strcpy(oldPromise[listnumber].promiseFreindsCount,changePromise.promiseFreindsCount);//�Բ��� ģ�� �̸��� �����Ǿ��� ���
		if(strcmp(checkPlace,"1"))
			strcat(changePromise.promisePlace,"\n");
		for(i=0;i<j; i++){
			deletePromise(oldPromise[listnumber].promiseFriendsName[i],oldPromise[listnumber].promiseName,oldPromise[listnumber].Promisedate,oldPromise[listnumber].promiseTime);
			strcpy(oldPromise[listnumber].promiseFriendsName[i],"\0");			
		}
		for(i=0; i<friendsCount; i++) {
			strcpy(oldPromise[listnumber].promiseFriendsName[i],changePromise.promiseFriendsName[i]);
		}	
		for(i=0; i<friendsCount; i++) {		//����� �Բ��� ȸ������ �������� ��� ����Ʈ�� ���� ��������� �����ϴ� �κ� 
			saveFriendsID(changePromise.promiseFriendsName[i],DB);			//ex) a,b,c,d�� ����� ��Ҵ�. a�� ���� �α����ؼ� ����� ���� ȸ��. aȸ���� ����Ʈ���� b,c,d�� ����Ǿ�����
			strcpy(friendNameCopy,changePromise.promiseFriendsName[i]);	//���� �α��� �Ǿ��ִ� ȸ���� ���̵�� for������ ���õ� �Բ� ����� �� ȸ������ �ϳ��� ���̵� �ٲ�ġ�� �ؼ� �����Ѵ�. 
			strcpy(changePromise.promiseFriendsName[i],logID);					//ex) bȸ���� ��Ӹ���Ʈ���� a,c,d || cȸ���� ��Ӹ���Ʈ���� b,a,d || dȸ���� ��Ӹ���Ʈ���� b,c,a ��� ������ ����ȴ�.
			saveNewpromise(DB,&changePromise);
			strcpy(changePromise.promiseFriendsName[i],friendNameCopy);		
		}//���⼭ �̸��� �ٲ��� ����Ǵ� �Լ��� �־���Ѵ�. ����ȸ���� ��Ӹ���Ʈ���� �ش� ����� �����ϴ� �Լ��� �ʿ��ϴ�. ����ϸ� ������ ����� ������ ����� ���ο� ���ȸ�������� ����� �߰��Ѵ�.
	}			// ��������Ʈ�� �������� ģ������Ʈ���� �ߺ��Ǵ� �̸��� �־ �װ� ó���ϴ°� �� ����Ƿ� �׳� ������ �����ֵ��� ����� ���ο� �ֵ����� �߰��Ѵ�.
	//���⼭�� �α��εǾ��ִ� ���ΰ� ���� ����� ���� �������ִ� ȸ������ ��Ӹ���Ʈ�� ������ ����� ����. �� ���� ��Ӹ���Ʈ�� �� ������ ������ִ� ������ ������ ���� ������ �߰��ؼ� ����Ѵ�.
	strcpy(oldPromise[listnumber].promiseName,changePromise.promiseName);	//������ �Ϸ�Ǿ����Ƿ� changePromise����ü�� ������ ���� ��Ӹ���Ʈ �ش�κп� ������.
		strcpy(oldPromise[listnumber].promisePlace,changePromise.promisePlace);
		strcpy(oldPromise[listnumber].promiseTime,changePromise.promiseTime);
		strcpy(oldPromise[listnumber].Promisedate,changePromise.Promisedate);
		saveMyPromiseList(oldPromise, DBname,listCount,friendsName,cost,listnumber);
	if(Check==0){
		
		for(i=0; i<friendsCount; i++) {		//����� �Բ��� ȸ������ �������� ��� ����Ʈ�� ���� ��������� �����ϴ� �κ� 
			saveFriendsID(oldPromise[listnumber].promiseFriendsName[i],DB);			//ex) a,b,c,d�� ����� ��Ҵ�. a�� ���� �α����ؼ� ����� ���� ȸ��. aȸ���� ����Ʈ���� b,c,d�� ����Ǿ�����
			strcpy(friendNameCopy,oldPromise[listnumber].promiseFriendsName[i]);	//���� �α��� �Ǿ��ִ� ȸ���� ���̵�� for������ ���õ� �Բ� ����� �� ȸ������ �ϳ��� ���̵� �ٲ�ġ�� �ؼ� �����Ѵ�. 
			strcpy(oldPromise[listnumber].promiseFriendsName[i],logID);					//ex) bȸ���� ��Ӹ���Ʈ���� a,c,d || cȸ���� ��Ӹ���Ʈ���� b,a,d || dȸ���� ��Ӹ���Ʈ���� b,c,a ��� ������ ����ȴ�.
			saveMyPromiseList(oldPromise, DB,listCount,friendsName,cost,listnumber);
			strcpy(oldPromise[listnumber].promiseFriendsName[i],friendNameCopy);		
		}
	}
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
//ģ�������� ��� ����
void saveMyPromiseList(struct structPromise *promiseList, char *DBname, int listCount,char **friendsName,char **cost,int listnumber) {
	FILE *fp;
	char DB[40]={0};
	int i,j;
	int friendsCount=0;
	friendsCount=atoi(promiseList[listnumber].promiseFreindsCount);
	strcpy(DB,DBname);
	strcat(DB,"PromiseList.txt");
	fp = fopen(DB,"w");
	fprintf(fp,"��Ӹ���Ʈ\n");
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
		fscanf(fp, "%s", &check);					//ù���� �о� Ȥ�ó� ��Ӹ���Ʈ�� �ƴѰ�츦 ���
		if(!strcmp(check,"��Ӹ���Ʈ")){ 

			fscanf(fp,"%d", &promiseCount);		//��°���� �о� promiseCount�� ����. ��Ӹ���Ʈ�� ������ �ǹ�.
			oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*promiseCount);
			friendsName=(char**)malloc(sizeof(char*)*promiseCount);					
			for(i=0; i<promiseCount; i++) {
				friendsName[i]=(char*)malloc(sizeof(char)*60);
				strcpy(friendsName[i],"\0");
				for(j=0; j<60; j++)
					strcpy(&friendsName[i][j],"\0");
			}

			cost=(char**)malloc(sizeof(char*)*promiseCount);						//��Ұ� ���� �����̱� ������ structPromise����ü�� ��Ҹ�� ����ϱ� ����Ƿ� 
			for(i=0; i<promiseCount; i++) {													//�׳� ���������� ���ڹ迭 ���
				cost[i]=(char*)malloc(sizeof(char)*10);
				strcpy(cost[i],"\0");
				for(j=0; j<10; j++)
					strcpy(&cost[i][j],"\0");
			}
			for(i=0; i<promiseCount; i++) {								//�ϴ� ��Ӹ���Ʈ������ŭ ����� �о�ͼ� oldPromise����ü�� ������� ����
				fscanf(fp,"%s",&oldPromise[i].promiseName);
				fflush(stdin);
				fgets(check,40,fp);						//��� �� �ι��� �־���� ����� ����... ��������ġ�����ΰ� ������ 
				fgets(check,40,fp);						//������ ��ġ�� ���Ϸ��� �� �κ��� ����Ʈ ����ŭ for���� ���⿡ ��������...�׳� �ι������� �Ǵ� �Ѿ... 
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
	fp=fopen(DB,"w");												//w�������� ��Ӹ���Ʈ�� �ٽ� ���� ���� ������ ������ ���� �ۼ��Ѵ�.
		fprintf(fp,"��Ӹ���Ʈ\n");
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
		nResult = remove(DB); //�ش� ������ �����.
		if(nResult == 0) {
			printf("succes");  //����� ����
		} 
		else if (nResult == -1)	{
			printf("fail");  //����� ����
		}
	}

}