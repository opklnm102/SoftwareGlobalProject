#include "structHeader.h"

void moneyShare(){
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
		break;

	case 2: //�� ������ �����ֱ�
		srand((unsigned)time(NULL));
		randomPersonNumber = ( rand()%5 );
		beforeDivideMoney = 0;
		printf("%d", randomPersonNumber);
		printf("���� ���� �����ּ��� : ��"); fflush(stdin);
		scanf("%d", &beforeDivideMoney); 
		printf("��� ���� �Է����ּ��� :��");
		
		arrMoney[randomPersonNumber] = beforeDivideMoney;

		for(i=0; i<5; i++){
			printf("%d ", arrMoney[i]);
		}

		break;

	}


}

	int main(void){

		moneyShare();

		return 0;
	}