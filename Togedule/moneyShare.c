#include "structHeader.h"

//void moneyShare2(structMember *s){
//	/*-------------------------------���� �����ߴ�--------------------------------*/
//	FILE *fin;
//	int i;
//	char fileName[30];
//	char fileContents[600][100]={0};
//	int beforeDivideMoney; // ������ �� ��
//	int finalMoney; // ���� ��
//	int peopleCnt; // ��� ����
//	int divisionNumber; // ������ ��
//	int arrMoney[5]={0, };
//	int baseMoney ;
//	int restPeople;
//	int restMoney;
//	int promiseNumber;
//	int menuseletion; //�޴� �����ϴ� ����
//	int randomPersonNumber; //�������� ���� �õ尪�� �����ϴ� ���� 1,2,3,4,5 �� �ϳ�
//	int promiseCnt=0, contentsCnt=0, j=0;
//	//promiseList �Լ����� ���� �͡�
//	char buffer[41]; //���Ͽ��� �о���� ���� ���� �ӽ� �������
//	char promiseName[41];	//��� �̸��� ����
//	int listCount=0;		//����Ʈ ����
//	char promiseDate[10];	//��� ��¥�� ����
//	int x=35, y=6;	
//	/*--------------------------------���� ������---------------------------------*/
//	
//	/*
//	54000���� ���Դ�. 5���̴�.
//	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000���� ������ ���Եȴ�.
//	�� �� restMoney = 4000��
//	*/
//
//	//������ �� ��, ��� ��, ������ ��, ���� ��, ���� ��, i, �����ִ� ��� �����ϰ� ������
//
//	i=0;
//	system("cls");
//	strcpy(fileName,s->ID);
//	strcat(fileName,s->name);
//	strcat(fileName,"PromiseList.txt"); //1235039������PromiseList.txt
//	fin = fopen(fileName,"r"); // ���ϻ���
//
//	if ( fin == NULL ) {
//		printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
//		return;
//	}
//	
//	while (!feof(fin)) {			//��Ӹ���Ʈ ��� ����� �̸��� ��¥�� �о ���, �ִ� 10������ ���
//		gotoxy(55,4); printf("�� ���� ��Ӹ���Ʈ\n");
//		fscanf(fin, "%s", &buffer);
//		if(!strcmp(buffer,"��Ӹ���Ʈ")){
//			fscanf(fin,"%d", &listCount);
//			gotoxy(62, 25); printf("���� �����ִ� ��� ���� %d",listCount);
//			for(i=0; i<listCount; i++){
//				fscanf(fin,"%s", promiseName);
//				fgets(buffer,41,fin);
//				fgets(buffer,41,fin);
//				fgets(buffer,41,fin);
//				fscanf(fin,"%s", promiseDate);
//				fscanf(fin,"%s", buffer);
//				fgets(buffer,41,fin);	
//				fgets(buffer,41,fin);
//				gotoxy(x,y);printf("�� %s / %s",promiseName,promiseDate);
//				y=y+3;
//				if(x==35&&y==21){		//���ʿ� 5���� ������ ���ٷ� �̵��ؼ� �ٽ� 5�� ����(�ִ� 10��)
//					x=75;
//					y=6;
//				}
//				if(x==75&&y==21){		//10���� ��ä�� ���� ��� �˸����� ǥ��
//					gotoxy(53, 22);printf("���� ��Ӹ���Ʈ�� 10�������� ǥ�õ˴ϴ�.");
//					gotoxy(55, 23);printf("���� ����� ��� �޴��� ������.");
//					break;
//				}
//			}
//		}
//	}
//	fclose(fin);
//
//	strcpy(fileName,s->ID);
//	strcat(fileName,s->name);
//	strcat(fileName,"PromiseList.txt"); //1235039������PromiseList.txt
//	fin = fopen(fileName,"r"); // ���ϻ���
//
//	while(1) // ������ ������ ������ fileContents ������ ����
//	{
//		fgets(fileContents[contentsCnt], 100, fin); //fin���� 100��ŭ���� �ִ� �о fileContents[contentsCnt]�� ����
//		contentsCnt++;
//		if (feof(fin)) break;
//	}
//	//printf("��Ӹ���Ʈ\n");
//	//promiseCnt = (contentsCnt-2) / 6;
//	//for (i=0; i<promiseCnt; i++)
//	//{
//	//	printf("%d. %s", i+1, fileContents[(i*6)+2]);
//	//	/*
//	//		for (j=0; j<6; j++)
//	//		{
//	//			printf("%s", fileContents[(i*6)+2+j]);
//	//		}
//	//	*/
//	//} // ��� ����Ʈ���� �� 6���̹Ƿ� 6*i��°�� ���� ���
//
//	//�޴��� �����ض�
//	gotoxy(43,27);
//	printf("����� �����Ͻÿ� ��");
//	gotoxy(52,27);
//	scanf("%d", &promiseNumber);
//	gotoxy(43,28);
//	printf("<%s", fileContents[(promiseNumber-1)*6+2]);
//	gotoxy(55,28);
//	printf(">�� �����ϼ̽��ϴ�.\n");
//	//��� �ο��� ���ϱ�
//	peopleCnt=1;
//	if (fileContents[(promiseNumber-1)*6+4][0]==NULL) {
//		printf("�Է¿���!!!!");
//	}
//	else {
//		for (i=0; ; i++)
//		{ //�ش��ϴ� ��� ���ڸ� �ҷ��´�.
//			if (fileContents[(promiseNumber-1)*6+6][i]==',') {
//				peopleCnt++;
//			}
//			if (fileContents[(promiseNumber-1)*6+6][i]==NULL) {
//				peopleCnt++;
//				break;
//			}
//		}
//	}
//	fflush(stdin);


//	while(1) {
//		printf("1 : �����ϰ� ������, 2 : �� ���� �����ֱ�\n");
//		printf("�޴��� �������ּ��� : ��");
//		scanf("%d", &menuseletion); fflush(stdin);
//
//		if( menuseletion==1 || menuseletion==2)
//			break;
//		else printf("�޴� ������ �ٽ� ���ּ���.");
//	}
//
//	switch(menuseletion){
//	case 1:
//
//		printf("������ �� ��, ������ �ּ� ��\n");
//		printf("����) 16500 1000\n");
//
//		scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);
//
//		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
//		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
//		int arrMoney[5] = {0, 0, 0, 0, 0};*/
//
//		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );
//
//		/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ۤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�*/
//		if (restMoney == 0) {
//			finalMoney = baseMoney+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);
//
//			for(i=0; i<peopleCnt; i++)
//				arrMoney[i] = finalMoney;
//		} 
//		else {
//			restPeople = ( restMoney / divisionNumber );
//			finalMoney = baseMoney + divisionNumber;
//
//			if (restMoney % divisionNumber == 0) {
//				for(i = 0 ;i<restPeople;i++){
//					arrMoney[i] = finalMoney;
//				}
//				for(i=restPeople;i<5;i++){
//					arrMoney[i] = (baseMoney + (restMoney % divisionNumber));
//				}
//			} 
//			else {
//				if (restPeople != 0)
//					for(i=0;i<restPeople;i++)
//						arrMoney[i] = finalMoney;
//				if (peopleCnt - restPeople - 1 != 0)
//					for(i=restPeople;i<peopleCnt-1;i++)
//						arrMoney[i] = baseMoney;
//				arrMoney[i] = (baseMoney + (restMoney % divisionNumber));
//			}
//		}
//
//		/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ѤѤѤѤѤѤѤѤѤ� �ѤѤѤѤѤѤѤѤ�*/
//
//		for(i=0; i<peopleCnt; i++){ //for (i=0; i<peopleCnt; i++)
//			printf("%d��° ��� : %d��\n", i+1,arrMoney[i]);
//		}
//
//		getch(); break;
//
//	case 2: //�� ������ �����ֱ�
//		srand((unsigned)time(NULL));
//		fflush(stdin); 
//		randomPersonNumber = ( rand()%peopleCnt );
//
//		printf("���� ���� �����ּ��� : ��"); 
//		scanf("%d", &beforeDivideMoney);  fflush(stdin); 
//
//		printf("%d��° ����� ��÷!\n", randomPersonNumber+1);
//
//		arrMoney[randomPersonNumber] = beforeDivideMoney;
//
//		for(i=0; i<peopleCnt; i++){
//			printf("%d ", arrMoney[i]);
//		}
//		getch();
//		break;
//	}
//}

void moneyShare1(structMember *s){
	char DBname[20];
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
	int peopleCnt=1;
	char controlList[3]={0};
	int beforeDivideMoney; // ������ �� ��
	int finalMoney; // ���� ��
	int divisionNumber; // ������ ��
	int arrMoney[5]={0, };
	int baseMoney;
	int restPeople;
	int restMoney;
	int promiseNumber;
	int menuseletion; //�޴� �����ϴ� ����
	int randomPersonNumber; //�������� ���� �õ尪�� �����ϴ� ���� 1,2,3,4,5 �� �ϳ�
	char waiting[20] = {'w','a','i','t',' ','p','l','e','a','s','e','.','.'};


	strcpy(DBname,s->ID);
	strcat(DBname,s->name);

	screenBorderDraw();	
	gotoxy(56,6); printf("�� ��� ��");
	gotoxy(54,8); printf("- ���� ��Ӹ���Ʈ -");
	listBorderDraw2(x,y);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(x+12,y+1); printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		Sleep(3000);
		return; //return 0;
	}
	while (!feof(fp)) {			//��Ӹ���Ʈ ��� ����Ʈ�� ������ ������ŭ �̸��� ��¥�� �о ����ϴ� �κ�

		gotoxy(x+8,y+1); printf("��Ӹ�                      ��ӳ�¥");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"��Ӹ���Ʈ")){
			fscanf(fp,"%d", &listCount);

			oldPromise = (struct structPromise*)malloc(sizeof(struct structPromise)*listCount);		//�о�� ����� �����ϱ����� ��ӱ���ü
			for(i=0; i<listCount; i++) {															
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
						if(!strcmp(controlList,"b")||!strcmp(controlList,"B")){
							for(i=0; i<listCount; i++) {											
								for(j=0; j<4; j++)
									free(oldPromise[i].promiseFriendsName[j]);
								free(oldPromise[i].promiseFriendsName);
							}
							free(oldPromise);
							for(i=0; i<listCount; i++)
								free(friendsName[i]);
							free(friendsName);
							for(i=0; i<listCount; i++)
								free(cost[i]);
							free(cost);
							return;  //return 0;
						}
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
						if(!strcmp(controlList,"b")||!strcmp(controlList,"B")){
							for(i=0; i<listCount; i++) {											
								for(j=0; j<4; j++)
									free(oldPromise[i].promiseFriendsName[j]);
								free(oldPromise[i].promiseFriendsName);
							}
							free(oldPromise);
							for(i=0; i<listCount; i++)
								free(friendsName[i]);
							free(friendsName);
							for(i=0; i<listCount; i++)
								free(cost[i]);
							free(cost);
							return; //return 0;
						}
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
						if(!strcmp(controlList,"b")||!strcmp(controlList,"B")){
							for(i=0; i<listCount; i++) {											
								for(j=0; j<4; j++)
									free(oldPromise[i].promiseFriendsName[j]);
								free(oldPromise[i].promiseFriendsName);
							}
							free(oldPromise);
							for(i=0; i<listCount; i++)
								free(friendsName[i]);
							free(friendsName);
							for(i=0; i<listCount; i++)
								free(cost[i]);
							free(cost);
							return ;//return 0;
						}
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
	gotoxy(35,25);printf("�� ���й��� ��� : ");


	while(1) {						//����Ʈ ��ȣ ���� ���� ���� �Է¹ޱ�
		gotoxy(56,25);scanf("%s",select);
		if(!strcmp(select,"b")||!strcmp(select,"B")){
			for(i=0; i<listCount; i++) {											
				for(j=0; j<4; j++)
					free(oldPromise[i].promiseFriendsName[j]);
				free(oldPromise[i].promiseFriendsName);
			}
			free(oldPromise);
			for(i=0; i<listCount; i++)
				free(friendsName[i]);
			free(friendsName);
			for(i=0; i<listCount; i++)
				free(cost[i]);
			free(cost);
			return ; //return 0;
		}
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<numbering)
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

	transName=(char**)malloc(sizeof(char*)*4+1);	//�й��� �׳� ���� ������ �̸����� �ٲ� ���ڹ迭�� �� �����Ҵ� ���ش�.
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

	//moneyShare2(s,j,transName);  //�˰��� ȣ��

	////-------------------------------�˰��� ����----------------------------------------------------------//
	while(1) {
		peopleCnt = j+1; //j ��� ���� peopleCnt�� ����
		gotoxy(37,40);	printf("������ �� ��, ������ �ּ� �� >>");
		gotoxy(37,41);  printf("����) 16500 1000\n");
		gotoxy(69,40);  scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);

		system("cls");
		screenBorderDraw();
		listBorderDraw1(26,12);
		gotoxy(58,6);
		printf("�� �� ������ ��");
		gotoxy(45, 15);
		printf("1.   �����ϰ� ������");
		gotoxy(45, 18);
		printf("2.   �� ���� �����ֱ�\n");
		gotoxy(50, 30);
		printf("�޴��� �������ּ��� : ��");
		scanf("%d", &menuseletion); fflush(stdin);

		if( menuseletion==1 || menuseletion==2)
			break;
		else printf("�޴� ������ �ٽ� ���ּ���.");
	}

	switch(menuseletion){
	case 1:

		//scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);

		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
		int arrMoney[5] = {0, 0, 0, 0, 0};*/

		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

		if (restMoney == 0) {
			finalMoney = baseMoney+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);

			for(i=0; i<peopleCnt; i++)
				arrMoney[i] = finalMoney;
		} 
		else {
			restPeople = ( restMoney / divisionNumber );
			finalMoney = baseMoney + divisionNumber;

			if (restMoney % divisionNumber == 0) {
				for(i = 0 ;i<restPeople;i++){
					arrMoney[i] = finalMoney;
				}
				for(i=restPeople;i<5;i++){
					arrMoney[i] = (baseMoney + (restMoney % divisionNumber));
				}
			} 
			else {
				if (restPeople != 0)
					for(i=0;i<restPeople;i++)
						arrMoney[i] = finalMoney;
				if (peopleCnt - restPeople - 1 != 0)
					for(i=restPeople;i<peopleCnt-1;i++)
						arrMoney[i] = baseMoney;
				arrMoney[i] = (baseMoney + (restMoney % divisionNumber));					
			}
		}

		/*for(i=0; i<18; i++){
		gotoxy(53+i,32);
		printf("%c",waiting[i]);
		Sleep(350);
		}*/

		for(i=0; i<peopleCnt-1; i++){
			gotoxy(53,32+i);
			printf("%d��° ��� %s: %d��\n", i+1,transName[i],arrMoney[i]);
		}
		gotoxy(53,32+i);
		printf("%d��° ��� %s: %d��\n", i+1,s->name,arrMoney[i]);


		getch(); break;

	case 2:
		//�� ������ �����ֱ�
		srand((unsigned)time(NULL)); //���� �õ� ����
		fflush(stdin); 
		randomPersonNumber = ( rand()%peopleCnt );
		//scanf("%d", &beforeDivideMoney);  fflush(stdin); 
		arrMoney[randomPersonNumber] = beforeDivideMoney;

		/*for(i=0; i<18; i++){
		gotoxy(53+i,32);
		printf("%c",waiting[i]);
		Sleep(350);
		}*/


		for(i=0; i<peopleCnt-1; i++){ //for (i=0; i<peopleCnt; i++)
			gotoxy(53,32+i);
			printf("%d��° ��� %s: %d��\n", i+1, transName[i], arrMoney[i]);
		}
		gotoxy(53,32+i);
		printf("%d��° ��� %s: %d��\n", i+1, s->name, arrMoney[i]);

		gotoxy(53, 36);
		printf("%d��° ����� ��÷!\n", randomPersonNumber+1);

		getch();
		break;
	}
	/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ѤѤѤѤѤѤѤѤѤ� �ѤѤѤѤѤѤѤѤ�*/


	strcpy(openDB,DBname);  //�Ű������� ���� '�й�+�̸�'�� PromiseList.txt�� ���� �̸��� ���� ��Ӹ���Ʈ�� �б���� ����
	strcat(openDB,"PromiseList.txt");
	fp = fopen(openDB, "r");

	if ( fp == NULL ) {						//������ ���� ���
		gotoxy(20, 32);printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return ;
	}














	//�����Ҵ� ����
	for(i=0; i<listCount; i++) {											
		for(j=0; j<4; j++)
			free(oldPromise[i].promiseFriendsName[j]);
		free(oldPromise[i].promiseFriendsName);
	}
	free(oldPromise);
	for(i=0; i<listCount; i++)
		free(friendsName[i]);
	free(friendsName);
	for(i=0; i<listCount; i++)
		free(cost[i]);
	free(cost);
	for(i=0; i<4; i++)
		free(transName[i]);
	free(transName);

	gotoxy(20,10);printf("���� �޴��� ���ư����� B�� �ٸ� ����� �󼼺����Ϸ��� B�� ������ Ű�� �Է��ϼ��� : ");
	gotoxy(103,10);scanf("%s",&select);
	if(!strcmp(select,"b")||!strcmp(select,"B"))
		return; //return 0;
	else if(!strcmp(select,"x")||!strcmp(select,"X")){
		gotoxy(90,45);
		exit(1);
	}
	else
		return; //return 1
}
//
////����ü,�����,�̸��鸦 ���ڷ�
//void moneyShare2(structMember *s,int peopleCnt,char **transName){
//	int beforeDivideMoney; // ������ �� ��
//	int finalMoney; // ���� ��
//	int divisionNumber; // ������ ��
//	int arrMoney[5]={0, };
//	int baseMoney;
//	int restPeople;
//	int restMoney;
//	//int promiseNumber;
//	int menuseletion; //�޴� �����ϴ� ����
//	int randomPersonNumber; //�������� ���� �õ尪�� �����ϴ� ���� 1,2,3,4,5 �� �ϳ�
//	char waiting[20] = {'w','a','i','t',' ','p','l','e','a','s','e','.','.'};
//	int i;
//
//	while(1) {
//		gotoxy(37,40);	printf("������ �� ��, ������ �ּ� �� >>");
//		gotoxy(37,41);  printf("����) 16500 1000\n");
//		gotoxy(69,40);  scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);
//
//		system("cls");
//		screenBorderDraw();
//		listBorderDraw1(26,12);
//		gotoxy(58,6);
//		printf("�� �� ������ ��");
//		gotoxy(45, 15);
//		printf("1.   �����ϰ� ������");
//		gotoxy(45, 18);
//		printf("2.   �� ���� �����ֱ�\n");
//		gotoxy(50, 30);
//		printf("�޴��� �������ּ��� : ��");
//		scanf("%d", &menuseletion); fflush(stdin);
//
//		if( menuseletion==1 || menuseletion==2)
//			break;
//		else printf("�޴� ������ �ٽ� ���ּ���.");
//	}
//
//	switch(menuseletion){
//	case 1:
//		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
//		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );
//
//		if (restMoney == 0) {
//			finalMoney = baseMoney+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);
//
//			for(i=0; i<peopleCnt; i++)
//				arrMoney[i] = finalMoney;
//		} 
//		else {
//			restPeople = ( restMoney / divisionNumber );
//			finalMoney = baseMoney + divisionNumber;
//
//			if (restMoney % divisionNumber == 0) {
//				for(i = 0 ;i<restPeople;i++){
//					arrMoney[i] = finalMoney;
//				}
//				for(i=restPeople;i<5;i++){
//					arrMoney[i] = (baseMoney + (restMoney % divisionNumber));
//				}
//			} 
//			else {
//				if (restPeople != 0)
//					for(i=0;i<restPeople;i++)
//						arrMoney[i] = finalMoney;
//				if (peopleCnt - restPeople - 1 != 0)
//					for(i=restPeople;i<peopleCnt-1;i++)
//						arrMoney[i] = baseMoney;
//				arrMoney[i] = (baseMoney + (restMoney % divisionNumber));
//			}
//		}
//
//		/*for(i=0; i<18; i++){
//			gotoxy(53+i,32);
//			printf("%c",waiting[i]);
//			Sleep(350);
//		}*/
//
//
//		for(i=0; i<peopleCnt; i++){ //for (i=0; i<peopleCnt; i++)
//			gotoxy(53,32+i);
//			printf("%d��° ��� %s: %d��\n", i+1,transName[i],arrMoney[i]);
//		}
//
//		getch(); break;
//
//	case 2:
//		//�� ������ �����ֱ�
//		srand((unsigned)time(NULL)); //���� �õ� ����
//		fflush(stdin); 
//		randomPersonNumber = ( rand()%peopleCnt );
//		//scanf("%d", &beforeDivideMoney);  fflush(stdin); 
//		arrMoney[randomPersonNumber] = beforeDivideMoney;
//
//		for(i=0; i<16; i++){
//			gotoxy(53+i,32);
//			printf("%c",waiting[i]);
//			Sleep(100);
//		}
//
//		for(i=0; i<peopleCnt; i++){ //for (i=0; i<peopleCnt; i++)
//			gotoxy(53,32+i);
//			printf("%d��° ��� %s: %d��\n", i+1, transName[i], arrMoney[i]);
//		}
//		gotoxy(53, 36);
//		printf("%d��° ����� ��÷!\n", randomPersonNumber+1);
//		getch();
//		break;
//	}
//}



