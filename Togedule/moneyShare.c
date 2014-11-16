#include"structHeader.h"

int* moneyShare(int beforeDivideMoney, int peopleCnt, int divisionNumber){
	/*
	54000원이 나왔다. 5명이다.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000원씩 나누어 갖게된다.
	이 때 restMoney = 4000원
	*/
	int finalMoney;
	int restMoney;
	int baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber))*divisionNumber;
	int i;
	int restPeople;

	int dp[5] = {}; //더치페이할 사람 숫자

	restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );
	
	if (restMoney == 0) {
		finalMoney = baseMoney	+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);

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
			dp[i] = (baseMoney + (restMoney %divisionNumber));
			
				

		}
	}

	return dp;

}

int main(void){
	int beforeDivideMoney;
	int finalMoney;
	int peopleCnt;
	int divisionNumber;
	int i;
	int *arrMoney;
	
	scanf("%d %d %d",&beforeDivideMoney , &peopleCnt, &divisionNumber);
	
	arrMoney = moneyShare(beforeDivideMoney, peopleCnt, divisionNumber);
	
	for(i=0;i<5;i++){ //for (i=0; i<peopleCnt; i++)
		printf("%d %d\n",arrMoney[i]);
	}
	/*finalMoney = moneyShare(beforeDivideMoney, peopleCnt, divisionNumber);*/

}