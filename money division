#include<stdio.h> 
#include<windows.h> 
 
 
 void gotoxy(int x,int y) 
 {	 
 	COORD pos={x,y}; 
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  
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
	int i;
	char command;
	int command1;

	
	
	system("color F0");
	gotoxy(21,5); 
	printf("☆ 돈 나누기 ☆");
	gotoxy(23,7); 
	printf("1. 몰아주기");
	gotoxy(23,9); 
	printf("2. 적당히 나눠주기");
	list_border_draw(23,9,25,5);
	gotoxy(23,15); 
	printf("3. 공평하게 나눠주기");
	list_border_draw(23,15,25,5);
	gotoxy(26,12);
	printf("3000원           2000원           3000원");
	gotoxy(26,18);
	printf("2600원           2600원           2800원");
	gotoxy(23,21);
	printf("메뉴 선택 :");
	gotoxy(60,6); 
	printf("뒤로가기 B, 종료 X, 계속하기 S :");
	scanf("%c",&command);
	gotoxy(35,21);	
	scanf("%d",&command1);
	gotoxy(23,22);	
}
