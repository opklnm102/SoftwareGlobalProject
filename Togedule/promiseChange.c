#include"structHeader.h"

void selectChange(struct structPromise *old, int listnumber, char **name){
	int i;
	char select[3];

	system("cls");
	printf("��Ӽ���\n");
	printf("1. ��Ӹ�   : %s\n",old[listnumber].promiseName);
	printf("2. ������ : %s\n",old[listnumber].promisePlace);
	printf("3. ��ӳ�¥ : %s\n",old[listnumber].Promisedate);
	printf("4. ��ӽð� : %s\n",old[listnumber].promiseTime);
	printf("5. �Բ��� ģ�� : ");
	for(i=0; i<4; i++)
		printf("%s ",name[i]);
	printf("\n");
	printf("������ ������ �����ϼ���.\n");
	scanf("%s",&select);

	/*���⼭���� ���� ������ ��ȣ�� ���� ���� ������ ������...�����ð��� �ɸ����ؼ� ���� �ո���...
	������� ¥������ �����غ���..
	��Ӹ� ������� �׳� ���ڸ����� �����ϰ� �ϰ�
	��Һ��ʹ� �Լ��� �̵����Ѿ��ϴµ� ... �׷���� ���� �������� ��� ������ä�� �׸��� �Ѿ�� ���غҰ�...
	������ �̾߱��Ѱ� ����غ��� �ش� ������ �´� �Լ��� �Ҹ��� �ȴٰ� �߾��µ�..
	������� ����   ��������
					�л��Ĵ�(â�ǰ� ����1��)
					4��
					11/3
					1092011,2344010,3434324
					�̷� ��Ӹ���Ʈ �������� ��Ҹ� �����Ѵٰ� �����ϸ�
					promisePlace �Լ��� �̵��ϰ� �Ǵµ� void promisePlace(char *DBname,struct structPromise *newPromise) �̰��� ���� �Լ�����...
					�̷���� ����̸�, �ð�, ��¥, �й� ������ �� ���� old��� ��ӱ���ü�� �Ѱܹ����� ���ο� ����� ���������°� �Ǿ����...
					������Ӱ� �ߺ�ó���� �����Ƿ�...��������°� �ƴ϶� ���ο� ��Ӹ���Ʈ�� �߰���... �׷���� ������ ������
					�ٽ� ��Ӹ���Ʈ�� �о� �����Ǳ��� ����� ã�Ƴ��� �װ� ����� ������ ��ӵ��� ���ܼ� ������ϴ� ��Ȳ...
					�װ� ����� �����ϴ� ��� ȸ������ ��Ӹ���Ʈ�� �ݺ��ؾ���...
					�Լ����� ���� ���ε��� �и��� �Ϻ��ϰ� ������ �ʰ� ���� �����ϵ��� �Ǿ��־ ��¥�������� ��ġ���� ��� �ؾ����� ���� �������� ����
					
					�Լ����� �� �����ؼ� �������� ������ �ƴϸ� ���� �Լ��� ¥�°� ������ �����..

	���� �Լ��� §�ٰ� �ĵ� ���� ��ȹ��� ȭ�� �̵��� �Ǵ� �������� ����ڰ� ��������� ���� �ٲ۴ٴ� ������ ������Ű���� 
	������ �ִ� �Լ���� �Ȱ��� �������̽��� ȭ�� ����� �Ǿ��ϱ⶧���� ���� �����ϵ��� �ϳ��� ��������.. ���ʵ� ������ �����...
	������ �غ���
					��Ӹ��� ���� ����� ������ �ʿ�����Ƿ� ���⼭ ��ĥ�� ����.
					��Ҵ� ��Һз��� ����ϴ� �Լ��� �ʿ� �ű⼭ ������ �ް� �ٷ� ����� �ǵ��ƿ;���.
					��¥�� �ٲܰ�� �ð��� �ٽ� ��������� �ϴ°�찡 ����Ƿ� �޷¸� ����ϰ� ��¥�� ���� �Է¹޴� ���� ������ ����..
					���սð�ǥ�� ����ϰ� �ð��� ���Է� �ް� ��������.. �׸��� �ð����� �Է¹����� ����� �ٷ� �ǵ��ƿ;���
					�ð��� �ٲܰ�� ���սð�ǥ�� ������ְ� �ٽ� ���ùްԸ� �ϰ� �� â���� ���ƿ;���
					�Բ��� ģ��.......
					ȸ������ �Է¹ް� �ٽ� �̸� �˻� �Լ��� �ҷ��� �̸��� ���ùް� ���ù��� ȸ���� �й������� �о�� ��â���� ���ƿ;���.. �׷��� �й��� �̸����� �����ؼ� �ٲ��̸��� ������ְ�
					�ٲ� ȸ����� ������ ��ġ�� ȸ���� �ִ��� üũ�ϰ� ��ġ�� ȸ���� ������ ����ȸ������ ��Ӹ���Ʈ���� �ش� ����� ���� ����... �ٲ�ȸ������ ��Ӹ���Ʈ���� ����߰�...

	�ϴ� ���� �Լ����� �����ϴ� �������� ������ȹ�ε� ������ �� ���� ����� ������ �� �˷��ֱ�...
	*/
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
		selectChange(oldPromise,listnumber,transName);		//selectChange �Լ����, (�����о�� ��Ӹ���Ʈ��������ü, ����ڰ� ������ ��Ӹ���Ʈ��ȣ, �Բ��ϴ� ȸ�� �̸�)�� �μ��� �Ѱ��ش�.
	else if(!strcmp(select,"Y"))
		selectChange(oldPromise,listnumber,transName);

	for(i=0;i<listCount; i++)			//�����Ҵ� ����
		free(friendsName[i]);				
	free(friendsName);

	for(i=0; i<4; i++)			
		free(transName[i]);				
	free(transName);

	for(i=0;i<listCount; i++){
		for(j=0; j<4; j++)
			free(oldPromise[i].promiseFriendsName[j]);				
		free(oldPromise[i].promiseFriendsName);
	}
		
	for(i=0;i<listCount; i++)			
		free(cost[i]);				
	free(cost);
	free(oldPromise);
	
	
}