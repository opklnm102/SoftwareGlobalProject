#include"structHeader.h"

void mainMenu(structMember *s){
	char menuSelect;
	system("cls");

	printf("%s님 안녕하세요!\n",s->name);
	printf("1. 내 상태보기\n"); 
	printf("2. 시간표 만들기\n");
	printf("3. 약속 잡아주세요\n"); 
	printf("4. 돈 나줘누세요\n"); 
	printf("5. 나갈래요\n"); 
	scanf("%c",&menuSelect); fflush(stdin);

	switch(menuSelect){
	case '1' :  //내 상태보기
		break;
	case '2' :  //시간표 만들기
		timetableMenu(s);
		break;
	case '3' :  //약속 잡아주세요
		promise(s);
		break;
	case '4' :  //돈 나눠주세요
		moneyShare(); break;
	case '5' :  //나갈래요
		exit(1);
	}
}

