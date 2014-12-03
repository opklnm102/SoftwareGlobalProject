#include"structHeader.h"

//������ ���� �Լ�
void promisePlace(char *DBname,struct structPromise *newPromise){
	FILE *fp1;
	char place[20],DBplace[40];
	int placeSelect;  //��Ҽ���
	int placeCount;  //�Һз��� ��
	char **subcategory;  //�Һз� �������
	int i,len;
	int x=56,y=8;
	system("cls");
	screenBorderDraw();	
	listBorderDraw2(36,15);
	gotoxy(x,y); printf("�� ��� ����� ��");
	fp1=fopen("place.txt","r");  //��Ҹ���ƮDB ����

	if(fp1 == NULL){
		printf("can not file open\n");
		return;
	}

	while(1){
		gotoxy(x+1,y+5);printf("--��Ҹ���Ʈ--");

		//��Ҹ���Ʈ ��з�
		gotoxy(x-15,y+9);printf("1. �н����ýü�");
		gotoxy(x-15,y+12);printf("2. �ްԽü�");
		gotoxy(x-15,y+15);printf("3. ��Ÿ�ü�");
		gotoxy(x-15,y+18);printf("4. �ǰ�,��ȭ�ü�");
		gotoxy(x-15,y+21);printf("��з� ����>>"); 
		gotoxy(x+1,y+21);scanf("%d",&placeSelect); fflush(stdin);
		if(1 <= placeSelect && placeSelect <= 4) break;
		gotoxy(x-15,y+22);printf("����Ʈ�� �ִ� ���߿� ���ÿ�");
		getch();
		system("cls");
	}

	switch(placeSelect){  //��Ҹ���Ʈ ��з� ����
	case 1 :
		strcpy(place,"�н����ýü�");		
		break;
	case 2 :
		strcpy(place,"�ްԽü�");		
		break;
	case 3 :
		strcpy(place,"��Ÿ�ü�");		
		break;
	case 4 :
		strcpy(place,"�ǰ�,��ȭ�ü�");		
		break;
	}

	len=strlen(place);
	place[len++]=10;
	place[len]='\0';	

	while(!feof(fp1)){  //���ϳ����� Ȯ��
		fgets(DBplace,30,fp1); 

		if(!strcmp(DBplace,place)){  //��з��� ã��
			fscanf(fp1,"%d",&placeCount);  //��з��� ���� �ִ� �Һз��� �����Է�
			fseek(fp1,2,SEEK_CUR);
			break;
		}
		for(i=0;i<30;i++) DBplace[i]=-52;
	}

	subcategory = (char **)malloc(sizeof(char*) *placeCount);  //�Һз���ŭ �����Ҵ�
	for(i=0; i<placeCount; i++){
		subcategory[i] = (char *)malloc(sizeof(char)*40);
		fgets(subcategory[i],40,fp1);  //�Һз��� ����� ����
		len=strlen(subcategory[i]);
		subcategory[i][len-1]='\0';		
	}
	
		system("cls");
		screenBorderDraw();	
		listBorderDraw(37,12);
		gotoxy(x,y); printf("�� ��� ����� ��");
		gotoxy(x+1,y+3);printf("--��Ҹ���Ʈ--");
		for(i=0; i<placeCount; i++)  //�Һз� ���
		{
			gotoxy(x-13,y+6+(i*1));printf("%d. %s",i+1,subcategory[i]);
		}
		gotoxy(x-13,y+25);printf("�Һз� ����>>");
	while(1){
		 gotoxy(x+2,y+25);scanf("%d",&placeSelect); fflush(stdin);
		if(1 <= placeSelect && placeSelect <= placeCount) break;
		gotoxy(x,y+25);printf("       ");
		gotoxy(x-13,y+26);printf("����Ʈ�� �ִ� ���߿� ���ÿ�\n");
	}
	strcpy(newPromise->promisePlace,subcategory[placeSelect-1]);  //������ �ٸ� ����������� ������ִ� newPromise ����ü�� ��� ������ ����
	

	for(i=0; i<placeCount; i++)
		free(subcategory[i]);
	free(subcategory);

	fclose(fp1);	

}
//���������
void saveNewpromise(char *DBname,struct structPromise *newPromise) {		//������Ӹ���Ʈ�� �� ����� �߰��ϴ� �Լ�
	char openDB[40];
	FILE *fp;
	int friendCount=0;
	int promiseCount=0;
	char check[40];
	char **oldPromisePlace;
	char **friendsName;		//ģ���̸� ������� ����ü��� friendsName�� �Ⱦ��� ������ ���� �׷��ʿ���� �׳� ������°�� �о �ӽ÷� ���常 �ϴ� ������ �ʿ��ϹǷ�...
	struct structPromise *oldPromise;		//���� ��Ӹ���Ʈ������ ������ ����ü
	char **cost;
	int i,j;
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList.txt");				//�й�+�̸�+PromiseList.txt �� �� ȸ���� ��Ӹ���Ʈ����
	fp=fopen(openDB,"r");							//�б�������� �켱 ����.

	if(!fp) {										//��Ӹ���Ʈ�� ������ 
		fp=fopen(openDB,"w");						//����������� ��� ���� ��Ӹ���Ʈ�� �����.
		fprintf(fp,"��Ӹ���Ʈ\n");
		fprintf(fp,"1\n");
		fprintf(fp,newPromise->promiseName);
		fprintf(fp,"\n");
		fprintf(fp,newPromise->promisePlace);	
		fprintf(fp,"\n");
		fprintf(fp,newPromise->promiseTime);
		fprintf(fp,"\n");
		fprintf(fp,newPromise->Promisedate);
		fprintf(fp,"\n");
		promiseCount=atoi(newPromise->promiseFreindsCount);			//serchName�Լ����� ������ �̸��˻��� �� ȸ���� �й��� �ϳ��� ����.  
		for(i=0; i<promiseCount; i++) {
			if(strcmp(newPromise->promiseFriendsName[i],"\0")){
				fprintf(fp,newPromise->promiseFriendsName[i]);				
			}
			if(i!=promiseCount-1)
				fprintf(fp,",");									//","�� ����ش�.���� ���� ��ǥ�� ����
		}
		fprintf(fp,"\n");								//������ �κ� ���� ����
		fclose(fp);
		
	}		
	else{												//��Ӹ���Ʈ�� ������
		while (!feof(fp)) {	

			fscanf(fp, "%s", &check);					//ù���� �о� Ȥ�ó� ��Ӹ���Ʈ�� �ƴѰ�츦 ���
				if(!strcmp(check,"��Ӹ���Ʈ")){ 

					fscanf(fp,"%d", &promiseCount);		//��°���� �о� promiseCount�� ����. ��Ӹ���Ʈ�� ������ �ǹ�.
					oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*promiseCount);
					friendsName=(char**)malloc(sizeof(char*)*promiseCount);						//�����Ҵ� ���� �ذ�. char�ڿ� ������ ǥ�� ������....
					for(i=0; i<promiseCount; i++) {
						friendsName[i]=(char*)malloc(sizeof(char)*60);
						strcpy(friendsName[i],"\0");
						for(j=0; j<60; j++)
							strcpy(&friendsName[i][j],"\0");
					}
					oldPromisePlace=(char**)malloc(sizeof(char*)*promiseCount);						//��Ұ� ���� �����̱� ������ structPromise����ü�� ��Ҹ�� ����ϱ� ����Ƿ� 
					for(i=0; i<promiseCount; i++) {													//�׳� ���������� ���ڹ迭 ���
						oldPromisePlace[i]=(char*)malloc(sizeof(char)*60);
						strcpy(oldPromisePlace[i],"\0");
						for(j=0; j<60; j++)
							strcpy(&oldPromisePlace[i][j],"\0");
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
						strcpy(oldPromisePlace[i],check);						
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
		fp=fopen(openDB,"w");												//w�������� ��Ӹ���Ʈ�� �ٽ� ���� ���� ������ ������ ���� �ۼ��Ѵ�.
		fprintf(fp,"��Ӹ���Ʈ\n");
		fprintf(fp,"%d\n",promiseCount+1);
		for(i=0; i<promiseCount; i++) {			
			fprintf(fp,"%s\n",oldPromise[i].promiseName);
			fprintf(fp,"%s",oldPromisePlace[i]);			//���DB���� �о�ö� �ǵڿ� null�� �ϳ� ���ԵǼ� �о���� ���.. �׷��� ���⿣ null�� ���� �ȴ�.
			fprintf(fp,"%s\n",oldPromise[i].promiseTime);
			fprintf(fp,"%s\n",oldPromise[i].Promisedate);
			fprintf(fp,"%s\n",friendsName[i]);
			fprintf(fp,"%s",cost[i]);
		}
		if(strlen(cost[i-1])!=1&&i-1!=0)
			fprintf(fp,"\n");
		fprintf(fp,"%s\n",newPromise->promiseName);
		fprintf(fp,"%s\n",newPromise->promisePlace);				//���������� null������.
		fprintf(fp,"%s\n",newPromise->promiseTime);
		fprintf(fp,"%s\n",newPromise->Promisedate);
		friendCount=atoi(newPromise->promiseFreindsCount);
		for(i=0; i<friendCount; i++) {		
			if(strcmp(newPromise->promiseFriendsName[i],"\0")){
				fprintf(fp,"%s",newPromise->promiseFriendsName[i]);				
				}
			if(i!=friendCount-1)
				fprintf(fp,",");
		}
		fprintf(fp,"\n");
		fclose(fp);	
		for(i=0;i<promiseCount; i++)			//�����Ҵ� ����
			free(friendsName[i]);				
		free(friendsName);
		for(i=0;i<promiseCount; i++)			//�����Ҵ� ����
			free(oldPromisePlace[i]);				
		free(oldPromisePlace);
		for(i=0;i<promiseCount; i++)			//�����Ҵ� ����
			free(cost[i]);				
		free(cost);
		free(oldPromise);
	}
}