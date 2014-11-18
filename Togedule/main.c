#include"structHeader.h"

int main()
{

	char menuSelect;

	system("mode con:cols=130 lines=46");  //가로 130, 세로 45 

	while(1){

		printf("*togedule*\n");
		printf("1. 로그인\n");
		printf("2. 회원가입\n");
		printf("3. 비밀번호재설정\n");
		printf("메뉴선택 >> "); scanf("%c",&menuSelect); fflush(stdin);
		
		switch(menuSelect){
		case '1' :  //로그인
			login();
			
			break;
		case '2' :  //회원가입
			membership();
			break;
		case '3' :  //비밀번호재설정
			pwFind();
			break;
		}
		system("cls");
	}
}