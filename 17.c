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
int main() {
   int x=24, y=4;
   int command;
   char command1,command2;
   system("mode con:cols=130 lines=46");  //가로 130, 세로 45 
   printMold();
   list_border_draw(26,12,40,10);
   list_border_draw(26,25,40,10);
   gotoxy(58,10);
   printf("--나의 약속 리스트--");
   gotoxy( 6+x, 10+y );
   printf("   약속명                 약속날짜 \n");
   gotoxy( 6+x, 12+y );
   printf("1. 홍대가기                11/28\n");
   gotoxy( 6+x, 14+y);
   printf("2. 학교가기                11/12\n");
   gotoxy( 6+x, 20+y );
   printf("수정하실 약속>> ");
   gotoxy( 6+x, 23+y );
   printf(" 약속명          장소          날짜       시간       함께할친구");
   gotoxy( 6+x, 25+y );
   printf("학교가기      공학관(405)      11/4        2시         이정훈");
   gotoxy( 5+x,32+y );
   printf("수정하시겠습니까?(Y/N)");
   gotoxy(88,41);
   printf("뒤로가기 : B 종료 : X 유지 : S");         
   gotoxy( 120, 41 );
   scanf("%c", &command1 );
   
   gotoxy( 47, 24);
   scanf("%d", &command );
   fflush(stdin);
   gotoxy( 54, 36);
   scanf("%c", &command2 );
   gotoxy( 23, 38 );
}
