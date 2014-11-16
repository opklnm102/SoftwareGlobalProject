#include"structHeader.h"


void pwFind(){

	char ID[8];  //학번
	char newPassword[14];  
	char backupPassword[14];  //고유코드
	char ask;  //저장 여부

	printf("-비밀번호 재설정-\n");
	printf("학번 : "); scanf("%s",ID);
	printf("고유코드 : "); scanf("%s",backupPassword);
	printf("새로운P  W : "); scanf("%s",newPassword);	
	

	
	printf("모든 입력이 끝났습니까? (Y/N)");
	scanf("%c",&ask);



}
