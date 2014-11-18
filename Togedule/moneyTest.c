#include "structHeader.h"

void moneyShare(){
	/*
	54000원이 나왔다. 5명이다.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000원씩 나누어 갖게된다.
	이 때 restMoney = 4000원
	*/

	//나누기 전 돈, 사람 수, 나누는 수, 최종 돈, 남는 돈, i, 몰아주는 사람 제외하고 나머지
	int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
	int dp[5] = {0, 0, 0, 0, 0};
	
	printf("나누기 전 돈, 사람 숫자, 절사할 최소 돈\n");
	scanf("%d %d %d", &beforeDivideMoney, &peopleCnt, &divisionNumber);
	restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );
	baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber))*divisionNumber;
	



	/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 시작ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/
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
	
	/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 끝ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ ㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/

	for(i=0; i<5; i++){ //for (i=0; i<peopleCnt; i++)
		printf("%d", dp[i]);
	}
}


int main(void){

	moneyShare();


	return 0;
}