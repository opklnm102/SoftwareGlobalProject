#include "structHeader.h"

void moneyShare(){
	/*
	54000���� ���Դ�. 5���̴�.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000���� ������ ���Եȴ�.
	�� �� restMoney = 4000��
	*/

	//������ �� ��, ��� ��, ������ ��, ���� ��, ���� ��, i, �����ִ� ��� �����ϰ� ������
	int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
	int dp[5] = {0, 0, 0, 0, 0};
	
	printf("������ �� ��, ��� ����, ������ �ּ� ��\n");
	scanf("%d %d %d", &beforeDivideMoney, &peopleCnt, &divisionNumber);
	restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );
	baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber))*divisionNumber;
	



	/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ۤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�*/
	if (restMoney == 0) {
		finalMoney = baseMoney+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);

		for(i=0; i<5; i++)
			dp[i] = finalMoney;

	} 
	else {
		restPeople = ( restMoney / divisionNumber );
		finalMoney = baseMoney + divisionNumber;

		if (restMoney % divisionNumber == 0) {
			for(i = 0 ;i<restPeople;i++){
				dp[i] = finalMoney;
			}
			for(i=restPeople;i<5;i++){
				dp[i] = (baseMoney + (restMoney % divisionNumber));
			}
		} 
		else {
			if (restPeople != 0)
				for(i=0;i<restPeople;i++)
					dp[i] = finalMoney;
			if (peopleCnt - restPeople - 1 != 0)
				for(i=restPeople;i<peopleCnt-1;i++)
					dp[i] = baseMoney;
			dp[i] = (baseMoney + (restMoney % divisionNumber));
		}
	}
	
	/*�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѾ˰��� ���ѤѤѤѤѤѤѤѤѤ� �ѤѤѤѤѤѤѤѤ�*/

	for(i=0; i<5; i++){ //for (i=0; i<peopleCnt; i++)
		printf("%d", dp[i]);
	}
}


int main(void){

	moneyShare();


	return 0;
}