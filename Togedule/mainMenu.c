#include"structHeader.h"

void mainMenu(){
	char menuSelect;

	printf("  님 안녕하세요!\n");
	printf("1. 내 상태보기\n"); 
	printf("2. 시간표 만들기\n");
	printf("3. 약속 잡아주세요\n"); 
	printf("4. 돈 나줘누세요\n"); 
	printf("5. 나갈래요\n"); 
	scanf("%c",&menuSelect);

	switch(menuSelect){
	case '1' :  //내 상태보기
		break;
	case '2' :  //시간표 만들기
		break;
	case '3' :  //약속 잡아주세요
		break;
	case '4' :  //돈 나눠주세요
		break;
	case '5' :  //나갈래요
		exit(1);
	}




}

