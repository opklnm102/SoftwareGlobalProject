#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

//테두리 그리기(시작좌표(x,y), 크기(width X height)) 
void list_border_draw(int x,int y,int width,int height){  
	int i,j;
	

	gotoxy(x,y);  //시작좌표	
	i=y;
	while(i<y+height){ //세로
		j=x;
		gotoxy(j,i+1);
		while(j<x+width){  //가로
			if(i==y && j==x)  //왼쪽위 구석
				printf("%s","┌");
			else if(i==y && j==x+width-1)  //오른쪽위 구석
				printf("%s","┐");
			else if(i==y+height-1 && j==x)  //왼쪽아래 구석
				printf("%s","└");
			else if(i==y+height-1 && j==x+width-1)  //오른쪽 아래 구석
				printf("%s","┘");
			else if(i==y || i==y+height-1)  //가로 그리기
				printf("%s","─");
			else if(j==x || j==x+width-1)  //세로 그리기
				printf("%s","│");
			else
				printf("  ");
			j++;
		}
		i++;
	}
}

//테두리 그리기(시작좌표(x,y), 크기(width X height), 그릴도형) 2비트짜리 도형
void border_draw(int x,int y,int width,int height,char figure[]){  
	int i,j;

	gotoxy(x,y);  //시작좌표	
	i=y;
	while(i<y+height){ //세로
		j=x;
		gotoxy(j,i+1);
		while(j<x+width){  //가로
			if(i==y || i==y+height-1 || j==x || j==x+width-1)
				printf("%c%c",figure[0],figure[1]);
			else
				printf("  ");
			j++;
		}
		i++;
	}
}

int main()
{	
	int x=10,y=3;  //시작 좌표
	int i,j;
	int place_category,place;  //장소리스트(P-1-7)
	int delete_promise;  //약속삭제(P-3)
	char delete_selection;  
	int division_money,money;  //돈분배(D)
	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 

	//장소선택(P-1-7)
	//list_border_draw(3,7,40,10);  //리스트테두리 그리기
	//gotoxy(3,3);
	//printf("약속장소");
	//gotoxy(35,6);
	//printf("장소리스트");
	//gotoxy(6,9);
	//printf("1.학습관련시설");
	//gotoxy(6,11);
	//printf("2.휴게시설");
	//gotoxy(6,13);
	//printf("3.기타시설");
	//gotoxy(3,19);
	//printf("원하는 장소>> "); scanf("%d",&place_category);	
	//
	//system("cls");		
	//
	//list_border_draw(3,7,40,10);  //리스트테두리 그리기
	//gotoxy(3,3);
	//printf("약속장소");
	//gotoxy(35,6);
	//printf("장소리스트");
	//gotoxy(6,9);
	//printf("1.탐구관 지하 매점");
	//gotoxy(6,11);
	//printf("2.컴공 자유실습실");
	//gotoxy(3,19);
	//printf("장소>> ");	scanf("%d",&place);	
	//
	//system("cls");

	//약속삭제(P-3)
	list_border_draw(3,6,40,10);  //리스트테두리 그리기
	gotoxy(3,3);
	printf("--나의 약속리스트--");
	gotoxy(6,8);
	printf("  약속명                 약속날짜");
	gotoxy(6,10);
	printf("1.홍대가기                11/28");
	gotoxy(6,12);
	printf("2.학교가기                11/17");

	list_border_draw(3,19,40,10);  //리스트테두리 그리기

	gotoxy(5,18);
	printf("삭제하실 약속>> "); scanf("%d",&delete_promise);

	gotoxy(6,21);
	printf(" 약속명            장소             날짜        시간        함께할친구");
	gotoxy(6,23);
	printf("학교가기        공학관(405)        11/14        2시          이정훈");
	
	gotoxy(5,30);
	printf("전체삭제됩니다. 삭제하시겠습니까?(Y/N)"); fflush(stdin);
	scanf("%c",&delete_selection);

	system("cls");

	list_border_draw(3,6,40,10);  //리스트테두리 그리기
	gotoxy(3,3);
	printf("--돈 나눠드릴께요!--");
	gotoxy(6,8);
	printf("  약속명                 약속날짜");
	gotoxy(6,10);
	printf("1.홍대가기                11/28");
	gotoxy(6,12);
	printf("2.학교가기                11/17");	
	
	list_border_draw(3,20,40,10);  //리스트테두리 그리기
	gotoxy(4,20);
	printf("<선택된 약속>");

	gotoxy(5,18);
	printf("돈 나눌 약속>> "); scanf("%d",&division_money);

	gotoxy(6,22);
	printf(" 약속명            장소             날짜        시간        함께할친구");
	gotoxy(6,24);
	printf("학교가기        공학관(405)        11/14        2시          이정훈");

	gotoxy(5,31);
	printf("나눌 금액 입력>> "); fflush(stdin);
	scanf("%d",&money);
}

