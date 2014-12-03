#include "structHeader.h"

int deleteAllPromise(char *DBname,char *logID) {
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
	char friendNameCopy[8]={0};	
	char checkPlace[3]={0};
	int x=35,y=11;
	char controlList[3]={0};
	screenBorderDraw();	
	gotoxy(56,6); printf("�� ��ӻ��� ��");
	gotoxy(54,8); printf("- ���� ��Ӹ���Ʈ -");
	listBorderDraw2(x,y);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(x+12,y+1); printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		Sleep(1000);
		return 0;
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
						gotoxy(35,10); printf("��������Ʈ�� ������ >Ű�� �Է��ϼ���. ��ȣ�� �����Ϸ��� @Ű�� �Է��ϼ���.");
						while(1){
							gotoxy(110,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"@")||!strcmp(controlList,">"))
								break;
							gotoxy(110,10);printf("     ");
						}
						if(!strcmp(controlList,"@")){
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
						gotoxy(35,10);printf("��������Ʈ <, ��������Ʈ >, ��ȣ�� �����Ϸ��� @Ű�� �Է��ϼ���.");
						while(1){
							gotoxy(100,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"@")||!strcmp(controlList,"<")||!strcmp(controlList,">"))
								break;
							
							gotoxy(100,10);printf("     ");
						}
						if(!strcmp(controlList,"@")){
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
						gotoxy(35,10);printf("ó������ ���ư����� <Ű�� �Է��ϼ���.��ȣ�� �����Ϸ��� @Ű�� �Է��ϼ���.");
						while(1){
							gotoxy(110,10);scanf("%s",&controlList);
							if(!strcmp(controlList,"@")||!strcmp(controlList,"<"))
								break;
							gotoxy(110,10);printf("     ");
						}
						if(!strcmp(controlList,"@")){
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
	gotoxy(38,40);printf("���� �����Ͻðڽ��ϱ�? <Y,N>");
	gotoxy(67,40);scanf("%s",&select);
	
	for(i=0; i<j; i++) {
		deletePromise(oldPromise[listnumber].promiseFriendsName[i],oldPromise[listnumber].promiseName,oldPromise[listnumber].Promisedate,oldPromise[listnumber].promiseTime);
	}
	deletePromise(logID,oldPromise[listnumber].promiseName,oldPromise[listnumber].Promisedate,oldPromise[listnumber].promiseTime);
	return 1;
}