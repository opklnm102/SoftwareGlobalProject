#include "structHeader.h"

void moneyShare2(structMember *s){
	/*-------------------------------���� �����ߴ�--------------------------------*/
	FILE *fin;
	int i;
	char fileName[30];
	char fileContents[600][100]={0};
	int beforeDivideMoney; // ������ �� ��
	int finalMoney; // ���� ��
	int peopleCnt; // ��� ����
	int divisionNumber; // ������ ��
	int arrMoney[5]={0, };
	int baseMoney ;
	int restPeople;
	int restMoney;
	int promiseNumber;
	int menuseletion; //�޴� �����ϴ� ����
	int randomPersonNumber; //�������� ���� �õ尪�� �����ϴ� ���� 1,2,3,4,5 �� �ϳ�
	int promiseCnt=0, contentsCnt=0, j=0;
	//promiseList �Լ����� ���� �͡�
	char buffer[41]; //���Ͽ��� �о���� ���� ���� �ӽ� �������
	char promiseName[41];	//��� �̸��� ����
	int listCount=0;		//����Ʈ ����
	char promiseDate[10];	//��� ��¥�� ����
	int x=35, y=6;	
	/*--------------------------------���� ������---------------------------------*/
	
	/*
	54000���� ���Դ�. 5���̴�.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000���� ������ ���Եȴ�.
	�� �� restMoney = 4000��
	*/

	//������ �� ��, ��� ��, ������ ��, ���� ��, ���� ��, i, �����ִ� ��� �����ϰ� ������

	i=0;
	system("cls");
	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"PromiseList.txt"); //1235039������PromiseList.txt
	fin = fopen(fileName,"r"); // ���ϻ���

	if ( fin == NULL ) {
		printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
		return;
	}
	
	while (!feof(fin)) {			//��Ӹ���Ʈ ��� ����� �̸��� ��¥�� �о ���, �ִ� 10������ ���
		gotoxy(55,4); printf("�� ���� ��Ӹ���Ʈ\n");
		fscanf(fin, "%s", &buffer);
		if(!strcmp(buffer,"��Ӹ���Ʈ")){
			fscanf(fin,"%d", &listCount);
			gotoxy(62, 25); printf("���� �����ִ� ��� ���� %d",listCount);
			for(i=0; i<listCount; i++){
				fscanf(fin,"%s", promiseName);
				fgets(buffer,41,fin);
				fgets(buffer,41,fin);
				fgets(buffer,41,fin);
				fscanf(fin,"%s", promiseDate);
				fscanf(fin,"%s", buffer);
				fgets(buffer,41,fin);	
				fgets(buffer,41,fin);
				gotoxy(x,y);printf("�� %s / %s",promiseName,promiseDate);
				y=y+3;
				if(x==35&&y==21){		//���ʿ� 5���� ������ ���ٷ� �̵��ؼ� �ٽ� 5�� ����(�ִ� 10��)
					x=75;
					y=6;
				}
				if(x==75&&y==21){		//10���� ��ä�� ���� ��� �˸����� ǥ��
					gotoxy(53, 22);printf("���� ��Ӹ���Ʈ�� 10�������� ǥ�õ˴ϴ�.");
					gotoxy(55, 23);printf("���� ����� ��� �޴��� ������.");
					break;
				}
			}
		}
	}
	fclose(fin);

	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"PromiseList.txt"); //1235039������PromiseList.txt
	fin = fopen(fileName,"r"); // ���ϻ���

	while(1) // ������ ������ ������ fileContents ������ ����
	{
		fgets(fileContents[contentsCnt], 100, fin); //fin���� 100��ŭ���� �ִ� �о fileContents[contentsCnt]�� ����
		contentsCnt++;
		if (feof(fin)) break;
	}
	//printf("��Ӹ���Ʈ\n");
	//promiseCnt = (contentsCnt-2) / 6;
	//for (i=0; i<promiseCnt; i++)
	//{
	//	printf("%d. %s", i+1, fileContents[(i*6)+2]);
	//	/*
	//		for (j=0; j<6; j++)
	//		{
	//			printf("%s", fileContents[(i*6)+2+j]);
	//		}
	//	*/
	//} // ��� ����Ʈ���� �� 6���̹Ƿ� 6*i��°�� ���� ���

	//�޴��� �����ض�
	gotoxy(43,27);
	printf("����� �����Ͻÿ� ��");
	gotoxy(52,27);
	scanf("%d", &promiseNumber);
	gotoxy(43,28);
	printf("<%s", fileContents[(promiseNumber-1)*6+2]);
	gotoxy(55,28);
	printf(">�� �����ϼ̽��ϴ�.\n");
	//��� �ο��� ���ϱ�
	peopleCnt=1;
	if (fileContents[(promiseNumber-1)*6+4][0]==NULL) {
		printf("�Է¿���!!!!");
	}
	else {
		for (i=0; ; i++)
		{ //�ش��ϴ� ��� ���ڸ� �ҷ��´�.
			if (fileContents[(promiseNumber-1)*6+6][i]==',') {
				peopleCnt++;
			}
			if (fileContents[(promiseNumber-1)*6+6][i]==NULL) {
				peopleCnt++;
				break;
			}
		}
	}
	fflush(stdin);
	while(1) {
		printf("1 : �����ϰ� ������, 2 : �� ���� �����ֱ�\n");
		printf("�޴��� �������ּ��� : ��");
		scanf("%d", &menuseletion); fflush(stdin);

		if( menuseletion==1 || menuseletion==2)
			break;
		else printf("�޴� ������ �ٽ� ���ּ���.");
	}

	switch(menuseletion){
	case 1:

		printf("������ �� ��, ������ �ּ� ��\n");
		printf("����) 16500 1000\n");

		scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);

		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
		int arrMoney[5] = {0, 0, 0, 0, 0};*/

		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

		/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ۤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�*/
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

		/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ѤѤѤѤѤѤѤѤѤ� �ѤѤѤѤѤѤѤѤ�*/

		for(i=0; i<peopleCnt; i++){ //for (i=0; i<peopleCnt; i++)
			printf("%d��° ��� : %d��\n", i+1,arrMoney[i]);
		}

		getch(); break;

	case 2: //�� ������ �����ֱ�
		srand((unsigned)time(NULL));
		fflush(stdin); 
		randomPersonNumber = ( rand()%peopleCnt );

		printf("���� ���� �����ּ��� : ��"); 
		scanf("%d", &beforeDivideMoney);  fflush(stdin); 

		printf("%d��° ����� ��÷!\n", randomPersonNumber+1);

		arrMoney[randomPersonNumber] = beforeDivideMoney;

		for(i=0; i<peopleCnt; i++){
			printf("%d ", arrMoney[i]);
		}
		getch();
		break;
	}
}

void moneyShare1(structMember *s){
	int x=24, y=4;
	char DBname[20];
	char logID[8];
	char logName[13];
	int command;
	char command1,command2;


	strcpy(logID,s->ID);
	strcpy(logName,s->name);			
	strcpy(DBname,logID);
	strcat(DBname,logName);	

	screenBorderDraw();
	listBorderDraw1(26,12);
	listBorderDraw1(26,25);

	gotoxy(58,10);
	printf("--���� ��� ����Ʈ--");
	gotoxy( 6+x, 10+y );
	printf("   ��Ӹ�                 ��ӳ�¥ \n");


	/*  gotoxy( 6+x, 12+y );
	printf("1. ȫ�밡��                11/28\n");
	gotoxy( 6+x, 14+y);
	printf("2. �б�����                11/12\n");*/

	promiseList(DBname);

	gotoxy( 6+x, 20+y );
	printf("�����Ͻ� ���>> ");
	gotoxy( 6+x, 23+y );
	printf(" ��Ӹ�          ���          ��¥       �ð�       �Բ���ģ��");
	gotoxy( 6+x, 25+y );
	printf("�б�����      ���а�(405)      11/4        2��         ������");
	gotoxy( 5+x,32+y );
	printf("�����Ͻðڽ��ϱ�?(Y/N)");

	gotoxy( 120, 41 );
	scanf("%c", &command1 );

	gotoxy( 47, 24);
	scanf("%d", &command );
	fflush(stdin);
	gotoxy( 54, 36);
	scanf("%c", &command2 );
	gotoxy( 23, 38 );



}
