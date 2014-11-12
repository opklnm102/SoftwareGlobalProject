#include<stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
	 COORD Cur;
	 Cur.X=x;
	 Cur.Y=y;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
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
   gotoxy(43,13);
	printf("┌");
	gotoxy(87,13);
	printf("┐");
	for(i=0;i<13;i++){
		gotoxy(43,i+14);
		printf("│                                          │");
	}
	gotoxy(43,27);
	printf("└");
	gotoxy(87,27);
	printf("┘");
	gotoxy(45,13);
	printf("─────────────────────");
	gotoxy(45,27);
	printf("─────────────────────");


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
int main(){
	int x=26, y=1;
	int i;
	int studentN, pw, originC;
	char command;
	system("mode con:cols=130 lines=46");  //가로 130, 세로 45 
	printMold();
	gotoxy(56,10);	
	printf("-비밀번호 재설정-");

	gotoxy(88,41);
	printf("뒤로가기 : B 종료 : X 유지 : S");	
	gotoxy(20+x, 15+y);
	printf("학   번    :"); 
	gotoxy(20+x, 18+y);
	printf("고유코드   :"); 
	gotoxy(20+x, 21+y);
	printf("새로운 PW  :"); 
	gotoxy(120,41);
	scanf("%c",&command);
	gotoxy(34+x,15+y);
	scanf("%d",&studentN);
	gotoxy(34+x,18+y);
	scanf("%d",&pw);
	gotoxy(34+x,21+y);
	scanf("%d",&originC);
	
	gotoxy(0,40);  //마지막 줄 위치변경
}
