#include"structHeader.h"

//������ ���� �Լ�
void promisePlace(char *DBname,struct structPromise *newPromise){
	FILE *fp1;
	FILE *fp;
	int promiseCount=0;
	char promisecount[5];
	char openDB[40];
	char check[40];
	char place[20],DBplace[30];
	int placeSelect;  //��Ҽ���
	int placeCount;  //�Һз��� ��
	char **subcategory;  //�Һз� �������
	int i,j,len;
	char **oldPromisePlace;
	char **friendsName;		//ģ���̸� ������� ����ü��� friendsName�� �Ⱦ��� ������ ���� �׷��ʿ���� �׳� ������°�� �о �ӽ÷� ���常 �ϴ� ������ �ʿ��ϹǷ�...
	struct structPromise *oldPromise;		//���� ��Ӹ���Ʈ������ ������ ����ü


	fp1=fopen("place.txt","r");  //��Ҹ���ƮDB ����

	if(fp1 == NULL){
		printf("can not file open\n");
		return;
	}

	while(1){
		printf("������\n");
		printf("--��Ҹ���Ʈ--\n");

		//��Ҹ���Ʈ ��з�
		printf("1. �н����ýü�\n");
		printf("2. �ްԽü�\n");
		printf("3. ��Ÿ�ü�\n");
		printf("4. �ǰ�,��ȭ�ü�\n");
		printf("��з� ����>> "); scanf("%d",&placeSelect); fflush(stdin);
		if(1 <= placeSelect && placeSelect <= 4) break;
		printf("����Ʈ�� �ִ� ���߿� ���ÿ�\n");
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
		subcategory[i] = (char *)malloc(sizeof(char)*30);
		fgets(subcategory[i],30,fp1);  //�Һз��� ����� ����
	}

	while(1){
		system("cls");
		for(i=0; i<placeCount; i++)  //�Һз� ���
			printf("%d. %s",i+1,subcategory[i]);

		printf("�Һз� ����>>"); scanf("%d",&placeSelect); fflush(stdin);

		if(1 <= placeSelect && placeSelect <= placeCount-1) break;
		printf("����Ʈ�� �ִ� ���߿� ���ÿ�\n");
		getch();
	}
	strcpy(newPromise->promisePlace,subcategory[placeSelect]);  //����ü�� ����
	printf("%s",newPromise->promisePlace);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList.txt");				//�й�+�̸�+PromiseList.txt �� �� ȸ���� ��Ӹ���Ʈ����
	fp=fopen(openDB,"r");							//�б�������� �켱 ����.

	if(!fp) {										//��Ӹ���Ʈ�� ������ 
		fp=fopen(openDB,"w");						//����������� ��� ���� ��Ӹ���Ʈ�� �����.
		fprintf(fp,"��Ӹ���Ʈ\n");
		fprintf(fp,"1\n");
		fprintf(fp,newPromise->promiseName);
		fprintf(fp,"\n");
		fprintf(fp,newPromise->promisePlace);						//�̰� ������ ��Ҵ� ���� �����Ƿ� ������ '�ӽ����'�� ���Ͽ� ����ϰ���
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
					oldPromisePlace=(char**)malloc(sizeof(char*)*promiseCount);						//�����Ҵ� ���� �ذ�. char�ڿ� ������ ǥ�� ������....
					for(i=0; i<promiseCount; i++) {
						oldPromisePlace[i]=(char*)malloc(sizeof(char)*60);
						strcpy(oldPromisePlace[i],"\0");
						for(j=0; j<60; j++)
							strcpy(&oldPromisePlace[i][j],"\0");
					}
					for(i=0; i<promiseCount; i++) {								//�ϴ� ��Ӹ���Ʈ������ŭ ����� �о�ͼ� oldPromise����ü�� ������� ����
						fscanf(fp,"%s",&oldPromise[i].promiseName);
						fflush(stdin);
						fgets(check,40,fp);
						fgets(check,40,fp);
						strcpy(oldPromisePlace[i],check);
						
						fscanf(fp,"%s",&oldPromise[i].promiseTime);
						fscanf(fp,"%s",&oldPromise[i].Promisedate);
						fscanf(fp,"%s",&check);
						strcpy(friendsName[i],check);
					}
				}
		}
		fclose(fp);
		fp=fopen(openDB,"w");												//w�������� ��Ӹ���Ʈ�� �ٽ� ���� ���� ������ ������ ���� �ۼ��Ѵ�.
		fprintf(fp,"��Ӹ���Ʈ\n");
		itoa(promiseCount+1,promisecount,10);
		fprintf(fp,"%s\n",promisecount);
		for(i=0; i<promiseCount; i++) {			
			fprintf(fp,"%s\n",oldPromise[i].promiseName);
			fprintf(fp,"%s",oldPromisePlace[i]);
			fprintf(fp,"%s\n",oldPromise[i].promiseTime);
			fprintf(fp,"%s\n",oldPromise[i].Promisedate);
			fprintf(fp,"%s\n",friendsName[i]);
		}
		fprintf(fp,"%s\n",newPromise->promiseName);
		fprintf(fp,"%s",newPromise->promisePlace);				//���� �����ϰ� �� �� �ڸ�. ���� ��Ұ� �����Ƿ� '�ӽ����'�� ���
		fprintf(fp,"%s��\n",newPromise->promiseTime);
		fprintf(fp,"%s\n",newPromise->Promisedate);
		promiseCount=atoi(newPromise->promiseFreindsCount);
		for(i=0; i<promiseCount; i++) {		
			if(strcmp(newPromise->promiseFriendsName[i],"\0")){
				fprintf(fp,"%s",newPromise->promiseFriendsName[i]);				
				}
			if(i!=promiseCount-1)
				fprintf(fp,",");
		}
		fclose(fp);	
		for(i=0;i<promiseCount; i++)			//�����Ҵ� ����
			free(friendsName[i]);				
		free(friendsName);
		for(i=0;i<promiseCount; i++)			//�����Ҵ� ����
			free(oldPromisePlace[i]);				
		free(oldPromisePlace);
		free(oldPromise);
	}


	for(i=0; i<placeCount; i++)
		free(subcategory[i]);
	free(subcategory);

	fclose(fp1);	
}