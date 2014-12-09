#include"structHeader.h"

int main()
{
	char menuSelect[20];
	int menu;
	structMember s;  //다른 메뉴로 회원정보를 넘겨준다.
	setcolor(0,15);  //글자색,글자배경색 변경(검정,흰)
	system("mode con:cols=130 lines=46");  //가로 130, 세로 45 


	while(1){
		screenBorderDraw();  //전체화면틀출력
		listBorderDraw(40,13);  //메뉴틀출력
		//----------------------------UI그리기-----------------------------------------------
		gotoxy(60,10);
		printf("*Togedule*");
		gotoxy(50, 18); printf("1. 로그인");
		gotoxy(50, 21); printf("2. 회원가입");
		gotoxy(50, 24); printf("3. 비밀번호재설정");
		gotoxy(73,27); printf("메뉴선택 >> "); 
		while(1){
			gotoxy(85,27); scanf("%s",menuSelect); fflush(stdin);
			if(!strcmp(menuSelect,"1") || !strcmp(menuSelect,"2") || !strcmp(menuSelect,"3"))
			{
				menu=atoi(menuSelect);
				gotoxy(50,30);
				switch(menu){
				case 1 :  //로그인
					login(&s);			
					break;
				case 2 :  //회원가입
					membership();
					break;
				case 3 :  //비밀번호재설정
					pwFind();
					break;
				}
			}
			else{
				gotoxy(65,29); printf("1~3만 입력");
				gotoxy(85,27); printf("       ");
			}
		}
		system("cls");
	}
}