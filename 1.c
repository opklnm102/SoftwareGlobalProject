#include<stdio.h>
#include<Windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void printMold() {

	int i;

	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	
	for(i=0;i<44;i++){
		gotoxy(0,i+1);
		printf("■                                                                                                                              ■");
	}

	gotoxy(0,44);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

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

int main() 
{

	int tmp;
	int x=71,y=23;

	
	system("mode con:cols=130 lines=46");  //가로 130, 세로 46 

	printMold();
	list_border_draw(x-36,y-12,30,20);

	gotoxy(60,14);
	printf("*Togedule*");

	

	gotoxy(45, 18);
	printf("1. 로  그  인");
	gotoxy(45, 21);
	printf("2. 회 원 가 입");
	gotoxy(45, 24);
	printf("3. 비밀번호찾기");

	gotoxy(73,28);
	printf("메뉴선택 : ");
	gotoxy(84,28);
	scanf("%d",&tmp);

	gotoxy(100,100);
}
