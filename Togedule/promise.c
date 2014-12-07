#include"structHeader.h"
//�������Ϸ� ����� �� ���� ����� function.c �����ؼ� �۾��ؾ���

void promiseList(char *DBname){			// ȸ���� '�й�+�̸�'�� �Ű������� �޾ƿͼ� �ش� ȸ���� ��Ӹ���Ʈ�� �ҷ����� �Լ�,10������ �����ϰ� ����Ѵ�.
	FILE *fp;				//���� ������
	char openDB[35];		//���½�ų ���ϸ�
	char buffer[41];		//���Ͽ��� �о���� ���� ���� �ӽ� �������
	char promiseName[41];	//��� �̸��� ����		--> ����̸��� ��¥�� �����ִ� �Լ��̹Ƿ� �̿��� �������� �ʿ����� ����
	char promiseDate[10];	//��� ��¥�� ����
	int listCount=0;		//����Ʈ ����
	int i;					//������ ���� ����
	int x=20, y=17;			//��ǥ ������ �����ϰ� ���� ����

	strcpy(openDB,DBname);					//�Ű������� ���� '�й�+�̸�'�� PromiseList.txt�� ���� �̸��� ���� ��Ӹ���Ʈ�� �б���� ����
	strcat(openDB,"PromiseList.txt");
	fp = fopen(openDB, "r");

	if ( fp == NULL ) {						//������ ���� ���
		gotoxy(20, 32);printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return ;
	}
	while (!feof(fp)) {			//��Ӹ���Ʈ ��� ����� �̸��� ��¥�� �о ���, �ִ� 10������ ���
		gotoxy(16,13); printf("�� ���� ��Ӹ���Ʈ\n");
		fscanf(fp, "%s", &buffer);
		if(!strcmp(buffer,"��Ӹ���Ʈ")){
			fscanf(fp,"%d", &listCount);
			gotoxy(20, 32); printf("���� �����ִ� ��� ���� %d",listCount);
			for(i=0; i<listCount; i++){
				fscanf(fp,"%s", promiseName);
				fgets(buffer,41,fp);
				fgets(buffer,41,fp);
				fgets(buffer,41,fp);
				fscanf(fp,"%s", promiseDate);
				fscanf(fp,"%s", buffer);
				fgets(buffer,41,fp);	
				fgets(buffer,41,fp);
				gotoxy(x,y);printf("�� %s / %s",promiseName,promiseDate);
				y=y+3;
				if(x==20&&y==32){		//���ʿ� 5���� ������ ���ٷ� �̵��ؼ� �ٽ� 5�� ����(�ִ� 10��)
					x=44;
					y=17;
				}
				if(x==44&&y==32){		//10���� ��ä�� ���� ��� �˸����� ǥ��
					gotoxy(17, 35);printf("���� ��Ӹ���Ʈ�� 10�������� ǥ�õ˴ϴ�.");
					gotoxy(17, 36);printf("���� ����� ������ ��Ӻ��⸦ �����ϼ���.");
					break;
				}
			}
		}
	}
	fclose(fp);
}

void changeLocation( char* str ) {		//���ڿ� ó���Լ�. ��ĭ�� ����� �� �ڿ� "\0"�� �����ϴ� �Լ�. 
	int len = strlen( str ); 
	int i;
	char temp = str[0]; 
	for( i=0; i<len; i++ )  
		str[ i ] = str[ i + 1]; 
	str[ len - 1 ] = '\0'; 
} 

int recordCombineTimetable(int CombineTimetable[5][13], char *DBname){		//���սð�ǥ�� '�й�+�̸�'���ڿ��� �Ű������� �޾� ���սð�ǥ�� ������ �߰��ϴ� �Լ�. 0��1�� ��ȯ�Ѵ�.
	FILE *fp;				//���� ������
	char openDB[40];		//���½�ų ���ϸ�
	char buffer[30];		//�ӽ� �������
	char dayWeek[10];		//������ �о�� ���ڿ�
	char Time[5]={0};		//�ð��� �� ���ڿ�
	char comma[1]={','};	//�о�� timetable.txt���� �ð������� 3,4,5 �̷������� ','�� �̿��� ó�������Ƿ� ���ڿ� ó���� ���� �ʿ��� ����
	int dayweek,time,i,j;	//���սð�ǥ int�� �������迭�� ���ϰ� �ð��� ���� ������ �ֱ����� �ʿ��� ������ dayweek���� ���Ͽ� ���� ������ time���� �ð��� ���� ������ ����.	
	int length;				//���ڿ����̿� ���� ���� ���� ����
	
	strcpy(openDB,DBname);			//�Ű������� ���� '�й�+�̸�'�� timetable.txt�� ���� �̸��� ���� �ð�ǥ������ �б���� ����
	strcat(openDB,"timetable.txt");		
	fp = fopen(openDB, "r");		

	if(!fp){						//���� �ش� ȸ���� �ð�ǥ ������ ���� ��� 1�� ����. 
		return 1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s", &buffer);				//ù���� �ð�ǥ ������ �ǹ�. �б⸸ �ϴ� ��. �ʿ���� ����
		while(!feof(fp)){					
			fscanf(fp,"%s", &dayWeek);			//������ �о�µ� ��,ȭ,��,��,�� �� 0,1,2,3,4 �� �������� dayweek������ ���� 
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
			fscanf(fp,"%s", &buffer);			//������ �д´�. ���� ���սð�ǥ�� ���鶧 ���ʿ��� ����
			fscanf(fp,"%s",&buffer);			//�ð��� �д´�.

			for(i=0;i<strlen(buffer);i++) {			//�о���� �ð� ���ڿ��� ���̸�ŭ for������ �Ѵܾ ����ó���� �Ѵ�.
				if(strncmp(buffer,comma,1)!=0){		//���� �ð����ڿ��� ù�ܾ "," �� �ƴϸ� 
					strncat(Time,buffer,1);			//Time���ڿ��� �ð����ڿ��� ù���ڸ� ���ٿ��� ���� 
					changeLocation(buffer);			//changeLocatioin �Լ��� ���. �ð����ڿ��� ù�ܾ ����� ��ĭ�� ������ �����ش�.
				}
				if(strncmp(buffer,comma,1)==0) {		//���� �ð����ڿ��� ù�ܾ "," �̸�
					changeLocation(buffer);				//changeLocatioin �Լ��� ��� ","������ ��ĭ�� �����.
					time=atoi(Time);					//Time ���ڿ��� ��ȯ���� ������ time ������ ����
					CombineTimetable[dayweek][time-1]=1;		//dayweek,time ������ �̿�. ���սð�ǥ���� �ش��ϴ� ��ġ�� 1�� ����
					length=strlen(Time);				
					for(j=0; j<length; j++)				//Time���ڿ� �ʱ�ȭ
						Time[j]='\0';	
				}		
			}
			//���̸�ŭ for���� ������ ������ ������ ','���� �ڷ�ó���� �����ִ�. 
			time=atoi(buffer);					
			CombineTimetable[dayweek][time-1]=1;
			length=strlen(Time);
			for(j=0; j<length; j++)
				Time[j]='\0';
		}
	}			
	fclose(fp);

	return 0;				//���������� ������ �о� ó�������� 0�� ���� 
}

void setMajor(char ID[8],char Major[20])	{		//�й�7�ڸ��� �а������� �� ���ڿ��� �Ű������� �ް� �й� 3,4��°�ڸ��� ���ڸ� �������� �а��� �˾Ƴ��� �Լ�
	FILE *fp;					//���� ������
	char IDCopy[8];				//���ڿ� ó���� �����ϰ� �ϱ����� �й����纻�� ������ ���ڿ�
	char keyWord[3]={0};		//�а��� �˾Ƴ��µ� �ʿ��� �ٽ������� �й��� 3,4��° ���ڰ� �� ���ڿ�
	char number[3];				//�ؽ�Ʈ ���Ͽ��� �о�� �а���ȣ ������ ������ ���ڿ�
	char major[20];				//�ؽ�Ʈ ���Ͽ��� �о�� �а��̸� ������ ������ ���ڿ�
	char noMajor[13];			//��ġ�ϴ� �а� ������ ������� ó���� ���� ���ڿ�
	
	strcpy(noMajor,"�а���������");		//�а������� ��ġ�ϴ°� ������ ������� ����

	strcpy(IDCopy,ID);			//�й��� ���纻�� ���� ���� �й��� ���纻���ڿ��� ���ؼ� ó��
	changeLocation(IDCopy);		//changeLocation�Լ��� �̿��ؼ� �й����ڿ��� ù��° �ڸ��� �����ϰ� ��ĭ�� �����ش�.
	changeLocation(IDCopy);		//�ι��ݺ��� ���� ���� �й� ���ڿ��� 3��° �ڸ��� �Ǿտ� ������ ����Ǿ���.
	strncpy(keyWord,IDCopy,2);	//���� �й����ڿ��� 1,2��°�� �ش��ϴ� ���� ,�� ���� �й��� 3,4��°�� �ش��ϴ� �� ���ڸ� keyWord�� ����

	fp=fopen("major.txt","r");			//major.txt ���⿡ �й�, �а� ������ ����Ǿ����� 
	
	if(fp == NULL){
		printf("�а����� ���� ���� �Ұ�");
		return;
	}
	while(!feof(fp)){					
		fscanf(fp,"%s %s",&number,&major);		//�а���ȣ ������ �а������� �д´�.
		if(!strcmp(number,keyWord))	{			//�а���ȣ�� keyWord�� ��ġ�ϸ� �а������� Major�� ����
			fclose(fp);							//������ �ݰ�
			strcpy(Major,major);				//�Ű������� ���� Major���ڿ��� ������ �����ѵ�
			return;								//����
		}
	}
	fclose(fp);
	strcpy(Major,noMajor);		//��ġ�ϴ� �а������� ��������� "�а���������"�� Major�� ����		
}

int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13],char *MyDB,char IDList[4][13]){		//�̸��˻��Լ�.. (�˻����̸�, �Բ��ϴ�ȸ���� ����Ʈ�� �ȿö� ȸ����,����ӱ���ü,���սð�ǥ,'�й�+�̸�'���ڿ�,���� ����� ȸ������Ʈ) �� ������ �޴´�.
	FILE *fp;				//����������
	FILE *fp1;
	char openDB[40];		//���½�ų ���ϸ�
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
	struct structMember friendID;		//�� ����ü�� �� �Լ����ο����� ����.. �� ȿ���� ���� �׳� char�ΰ� �� ����� �����Ƽ� �ẻ ����ü...

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
				if(strcmp(openDB,MyDB)&&strcmp(ID,IDList[0])&&strcmp(ID,IDList[1])&&strcmp(ID,IDList[2])&&strcmp(ID,IDList[3])){
					strcat(openDB,textFile);
					fp1 = fopen(openDB, "r");			//�й��� �̸��� �̿� �ش�ȸ������������ �д´�.

					if ( !fp1 ) {						//������ �극��ũ ó��.. �����ϳ� ȸ����Ͽ��� �ְ� ȸ�������� ���� ��츦 üũ��
						gotoxy(x,y);printf("%sȸ���� ������ �����ϴ�.",name );
						exist=1;
						break;
					}

					while (!feof(fp1)) {				//ȸ���������� �й��� �̸��� �о�� ����ü friendID�� �����Ѵ�.
						fscanf(fp1, "%s", &buffer);
						if(!strcmp(buffer,"ȸ������")){
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
			strcpy(ID,"\0");
			strcpy(listName,"\0");
				
		}
		fclose(fp);

		if(overlap==1){
				gotoxy(x,y);printf("%sȸ���� ������ �����ϴ�.",name );	
				exist=1;
				break;
		}
		if(!strcmp(openDB,"ȸ�����.txt")){		//ȸ����Ͽ� ���� �̸��� �˻����� ��� ó��
			gotoxy(x,y);printf("%sȸ���� ������ �����ϴ�.",name);
			exist=1;							//exist�� 1�� ����. exist�� �� �̸��˻��Լ��� ���ϰ����� ����. �Լ��� �θ��� �ܰ迡�� �� ���ϰ��� ������ ȸ���̸��� �ִ��� �������� üũ�ؼ� /
			break;								//���� ����� �� �ο��� ���� ����Ʈ�� �ö� ȸ���� �ƴ� ���� ȸ������ �ľ�
		}

		gotoxy(x,33);printf("�� �̸���ȣ ���� : ");		//��� ����Ʈ�� ��µǸ� ����Ʈ��ȣ�� ���ù޴´�.
		limit=overlap-1;
		while(1) {						//����Ʈ ��ȣ ���� ���� ���� �Է¹ޱ�
			gotoxy(x+20,33);scanf("%s",select);
			if(!strcmp(select,"b")||!strcmp(select,"B"))
				return -1;
			overlap=atoi(select);	
			if(overlap>0&&overlap<=limit)
				break;
			gotoxy(x+20,33);printf("     ");
		}
		limit=1;
		strcpy(openDB,"ȸ�����");		//ȸ������� �ٽ� ����.
		strcat(openDB,textFile);
		fp = fopen(openDB, "r");

		while (!feof(fp)) {					//��� ���� �Է¹��� ����Ʈ ��ȣ�� �ɶ����� �о��ָ� ���� ã�´�. ����Ʈ ������ ȸ����� ������ �����Ƿ� �̷��� ó���Ѵ�.
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

		strcpy(IDList[count-1],ID);
		break;
	}	
	return exist;			//exist�� ���ϰ����� ������. �̸��˻��� ������ 0�� ����, ���� �̸��̸� ������ 1�� �����ϰ� ���ִ�. ����Ʈ��ȣ �Է½� B,bŰ �Է½� -1���� 
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
	gotoxy(26,18);printf(" �� �� ȭ �� �� �� ��");		//�Է¹��� �⵵�� ���� �޷��� ��¸� �ϴ� �Լ��̴�.
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
	gotoxy(x,y+1); printf("�޷��� ��Ÿ���� ���սð�ǥ�� �����ؼ� ����� ����");
	gotoxy(x,y+2); printf("��¥�� �Է��ϼ���.");

	//���սð�ǥ�� ���
	gotoxy(x+60,y-5);
	printf("������������������������������������");
	gotoxy(x+60,y-4); 
	printf("��  �� �� �� ȭ �� �� �� �� �� �� ��"); 
	gotoxy(x+60,y-3);
	printf("������������������������������������");
	for(i=0; i<26; i+=2) { 
		gotoxy(x+60,y-2+i);
		printf("��%2d��    ��    ��    ��    ��    ��",i/2+1);
		gotoxy(x+60,y-1+i);
		if(i!= 24)
			printf("������������������������������������");
	}
	gotoxy(x+60,y+23);
	printf("������������������������������������");

	for (i=0; i<5; i++) {  //���սð�ǥ�� ���(��ġ�� �κ� ������)	
		for(j=0; j<13; j++){
			if(CombineTimetable[i][j]==1){				
				gotoxy(92+6*i,10+j*2);
				setcolor(4,4);
				printf("    ",CombineTimetable[i][j]);
				//setcolor(7,0);
			}			
		}
	}
	setcolor(0,15);  //���ڻ� ���� ����(��),���(��)

	gotoxy(x,y+4); printf("����� ���� �� �Է�(ex 3��) :");	
	gotoxy(x+30,y+4); scanf("%s",&month);								//���� �Է��ϸ�
	if(!strcmp(month,"b")||!strcmp(month,"B"))
		return -1;
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
	
	
	
	gotoxy(x,y+15);printf("������ ��¥�Է¿� ���� �ڵ����� ���õ˴ϴ�.");
	gotoxy(x,y+16);printf("��¥�Է��� ������ ��ӽð�(����)�� �Է��ϼ���.");
	while(1){
		gotoxy(x,y+18);printf("����� ���� ��¥ �Է�(ex 10��) :");		//���� �Է��ϸ�
		gotoxy(x+34,y+18);scanf("%s",&day);
		if(!strcmp(day,"b")||!strcmp(day,"B"))
			return -1;
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
		if(dayofWeek==0||dayofWeek==1||dayofWeek==2||dayofWeek==3||dayofWeek==4)
			break;
		gotoxy(x,y+19);printf("����� ���߿��� ���� �� �ֽ��ϴ�.");
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
	strcpy(newPromise->promiseTime,"\0");	//B,b �Է� üũ�� ���� �ʱ�ȭ
	gotoxy(x,y);printf("��ӽð��� �Է�(ex 3��) :");
	gotoxy(x+27,y);scanf("%s",&time);
	if(!strcmp(time,"b")||!strcmp(time,"B"))
		return;
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
		gotoxy(x,y+1);printf("�ش� �ð��� ������� �ʽ��ϴ�."); 
		gotoxy(x,y+2);printf("���� �ð�ǥ�� �����ؼ� ������ ��¥�� ��ð��� �Է��ϼ���");
		
		gotoxy(x+27,y);scanf("%s",&time);
		if(!strcmp(time,"b")||!strcmp(time,"B"))
			break;
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
	if(!strcmp(time,"b")||!strcmp(time,"B"))
			return;
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
	if(!strcmp(newPromise.promiseName,"B")||!strcmp(newPromise.promiseName,"b"))
		return;
	count=selectFriends(DBname,CombineTimetable,&newPromise);
	if(count==0)
		return;
	gotoxy(128,44);Sleep(1000);	//�ڵ����� �Ѿ��
	dayofWeek=selectDate(CombineTimetable,&newPromise);		//selectDate�Լ��� ȣ���Ѵ�. ��¥,����,�ð��� ���ϴ� �Լ�
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
	promisePlace(DBname,&newPromise);				//������ �����Լ� ���, (�й�+�̸�, newPromise ����ü)�� �μ��� �ѱ��.
	if(!strcmp(newPromise.promisePlace,"\0")){
		for(i=0;i<count;i++)
			free(newPromise.promiseFriendsName[i]);
		free(newPromise.promiseFriendsName);	
		return;
	}
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
	int check=0;
	char Name[13];
	char control[3]={0};
	char nameList[4][13]={0};
	char selectedNameList[4][13]={0};
	int x=26, y=12;
	
	gotoxy(x+60,y);scanf("%s",&newPromise->promiseFreindsCount); //@@@�ο��� �Է�
	if(!strcmp(newPromise->promiseFreindsCount,"b")||!strcmp(newPromise->promiseFreindsCount,"B"))
		return 0;
	Count=atoi(newPromise->promiseFreindsCount);				//�ο����� int������ �ٲ��ְ� newPromise�� promiseFriendsCount �� �����Ҵ�
	CountCopy=Count;
	newPromise->promiseFriendsName=(char **)malloc(sizeof(char*)*Count+2);	
	for(i=0; i<Count; i++){
		newPromise->promiseFriendsName[i]=(char *)malloc(sizeof(char)*20);
		for(j=0; j<13; j++)
			newPromise->promiseFriendsName[i][j]=NULL;
	}
	i=0;
	while(Count>0) {		//�ο�����ŭ �˻��Լ��� ������.
		gotoxy(x+12,y+4);printf("                              ");
		gotoxy(x+12,y+4);scanf("%s",&Name);  //@@@�˻��� �̸� �Է�
		if(!strcmp(Name,"b")||!strcmp(Name,"B"))			
			break;
		check=searchName(Name,Count,*newPromise,CombineTimetable,DBname,selectedNameList);
		if(check==0)	{			//�̸� �˻��Լ����� ���ϰ��� �޾ƿ´�. 0�̸� �˻������ �־��� ��� ,�޾ƿ� ���ϰ��� 1�Ǵ� -1�̸� �̸��� ������ ����̰ų� B,bŰ�� �Է��Ѱ��̹Ƿ� Count���� �������� �ʴ´�.
			Count--;
			
			strcpy(nameList[i],Name);		
				
			gotoxy(x+64,y+6);printf("%s",nameList[0]);	//@@@�̸�����Ʈ ���
			gotoxy(x+64,y+8);printf("%s",nameList[1]);	//@@@�̸�����Ʈ ���
			gotoxy(x+64,y+10);printf("%s",nameList[2]);	//@@@�̸�����Ʈ ���
			gotoxy(x+64,y+12);printf("%s",nameList[3]);	//@@@�̸�����Ʈ ���
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
	gotoxy(x,y-8); printf("4. ��� �󼼺���");	
	gotoxy(x,y-5); printf("5. ������");	
	gotoxy(x,y);printf("�� �޴� ���� : ");
}

int promise(structMember *s){		//��Ӹ���� �����Լ�. (����α��ε��� ȸ������ü)�� ������ �޴´�.

	char logID[8];
	char logName[13];
	char menuControl;
	char DBname[20];
	int check=1;
	
	strcpy(logID,s->ID);
	strcpy(logName,s->name);			
	strcpy(DBname,logID);
	strcat(DBname,logName);				//����ü���� �̸��� �й��� ������ �ϳ��� ���ڿ��� ���ļ� ����. '�й�+�̸�'
	showMenu();

	promiseList(DBname);				//���� �α��ε� ȸ���� ��Ӹ���Ʈ ���
	
	gotoxy(96,32);scanf("%c",&menuControl);
	switch(menuControl) {		//system("cls") ��� ȭ���� ����� �ٽ� ����ϰ� �ϴ� ��� <windows.h>�ʿ�
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