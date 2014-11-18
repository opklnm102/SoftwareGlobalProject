#include "structHeader.h"

void moneyShare(){
	/*
	54000원이 나왔다. 5명이다.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000원씩 나누어 갖게된다.
	이 때 restMoney = 4000원
	*/

	//나누기 전 돈, 사람 수, 나누는 수, 최종 돈, 남는 돈, i, 몰아주는 사람 제외하고 나머지




	/*-------------------------------변수 시작했다--------------------------------*/
	int beforeDivideMoney; // 나누기 전 돈
	int finalMoney; // 최종 돈
	int peopleCnt; // 사람 숫자
	int divisionNumber; // 나누는 수
	int i;
	int arrMoney[5]={0, };
	int baseMoney ;
	int restPeople;
	int restMoney;
	int menuseletion; //메뉴 선택하는 변수
	int randomPersonNumber; //랜덤으로 받은 시드값을 저장하는 변수 1,2,3,4,5 중 하나
	/*--------------------------------변수 끝났다---------------------------------*/


	//메뉴를 선택해라
	while(1) {
		printf("1 : 공평하게 나누기, 2 : 한 명에게 몰아주기\n");
		printf("메뉴를 선택해주세요 : ▶");
		scanf("%d", &menuseletion); fflush(stdin);

		if( menuseletion==1 || menuseletion==2 || menuseletion==3 )
			break;
		else printf("메뉴 선택을 다시 해주세요.");
	}

	switch(menuseletion){
	case 1:

		printf("나누기 전 돈, 사람 숫자, 절사할 최소 돈\n");
		printf("예시) 16500 5 1000\n");
		printf("최대 5명까지 지정할 수 있습니다.\n");

		scanf("%d %d %d", &beforeDivideMoney , &peopleCnt, &divisionNumber); fflush(stdin);

		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
		int arrMoney[5] = {0, 0, 0, 0, 0};*/


		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

		/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 시작ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/
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

		/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 끝ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ ㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/

		for(i=0; i<5; i++){ //for (i=0; i<peopleCnt; i++)
			printf("%d\n", arrMoney[i]);
		}
		break;

	case 2: //한 명한테 몰아주기
		srand((unsigned)time(NULL));
		randomPersonNumber = ( rand()%5 );
		beforeDivideMoney = 0;
		printf("%d", randomPersonNumber);
		printf("나눌 돈을 적어주세요 : ▶"); fflush(stdin);
		scanf("%d", &beforeDivideMoney); 
		printf("사람 수를 입력해주세요 :▶");
		
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