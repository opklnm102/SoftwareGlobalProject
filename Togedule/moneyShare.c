#include"structHeader.h"

void moneyShare(int beforeDivideMoney, int peopleCnt, int divisionNumber,int dp[]){
   /*
   54000���� ���Դ�. 5���̴�.
   (54000 / (5 * 1000))*1000 = 50000 / 5 = 10000���� ������ ���Եȴ�.
   �� �� restMoney = 4000��
   */
   int finalMoney;
   int restMoney;
   int baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber))*divisionNumber;
   int i;
   int restPeople;


   restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

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
            for(i=restPeople; i< peopleCnt-1; i++)
               dp[i] = baseMoney;
         dp[i] = (baseMoney + (restMoney %divisionNumber));
         }
   }


}

int main(void){
   int beforeDivideMoney; // ������ �� ��
   int finalMoney; // ���� ��
   int peopleCnt; // ��� ����
   int divisionNumber; // ������ ��
   int i;
   int arrMoney[5]={0};

   printf("������ �� ��, ��� ����, 1000");


   scanf("%d %d %d",&beforeDivideMoney , &peopleCnt, &divisionNumber);

   moneyShare(beforeDivideMoney, peopleCnt, divisionNumber,arrMoney);

   for(i=0;i<5;i++){ //for (i=0; i<peopleCnt; i++)
      printf("%d %d\n",arrMoney[i]);
   }
   /*finalMoney = moneyShare(beforeDivideMoney, peopleCnt, divisionNumber);*/
}