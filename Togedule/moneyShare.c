#include "structHeader.h"

void moneyShare2(){
	/*
	54000���� ���Դ�. 5���̴�.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000���� ������ ���Եȴ�.
	�� �� restMoney = 4000��
	*/

	//������ �� ��, ��� ��, ������ ��, ���� ��, ���� ��, i, �����ִ� ��� �����ϰ� ������

	/*-------------------------------���� �����ߴ�--------------------------------*/
	int beforeDivideMoney; // ������ �� ��
	int finalMoney; // ���� ��
	int peopleCnt; // ��� ����
	int divisionNumber; // ������ ��
	int i;
	int arrMoney[5]={0, };
	int baseMoney ;
	int restPeople;
	int restMoney;
	int menuseletion; //�޴� �����ϴ� ����
	int randomPersonNumber; //�������� ���� �õ尪�� �����ϴ� ���� 1,2,3,4,5 �� �ϳ�
	/*--------------------------------���� ������---------------------------------*/

	//�޴��� �����ض�
	while(1) {
		printf("1 : �����ϰ� ������, 2 : �� ���� �����ֱ�\n");
		printf("�޴��� �������ּ��� : ��");
		scanf("%d", &menuseletion); fflush(stdin);

		if( menuseletion==1 || menuseletion==2 || menuseletion==3 )
			break;
		else printf("�޴� ������ �ٽ� ���ּ���.");
	}

	switch(menuseletion){
	case 1:

		printf("������ �� ��, ��� ����, ������ �ּ� ��\n");
		printf("����) 16500 5 1000\n");
		printf("�ִ� 5����� ������ �� �ֽ��ϴ�.\n");

		scanf("%d %d %d", &beforeDivideMoney , &peopleCnt, &divisionNumber); fflush(stdin);

		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
		int arrMoney[5] = {0, 0, 0, 0, 0};*/

		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

		/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ۤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�*/
		if (restMoney == 0) {
			finalMoney = baseMoney+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);

			for(i=0; i<5; i++)
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

		for(i=0; i<5; i++){ //for (i=0; i<peopleCnt; i++)
			printf("%d\n", arrMoney[i]);
		}

		getch(); break;

	case 2: //�� ������ �����ֱ�
		srand((unsigned)time(NULL));
		printf("��� ���� �Է����ּ��� :��"); scanf("%d",&peopleCnt); fflush(stdin); 
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
