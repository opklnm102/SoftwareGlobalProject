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
	char command,command1;
	int number;

	
	
	system("color FC");
	gotoxy(21,5); 
	printf("☆ 약속 수정 ☆");
	gotoxy(23,7); 
	printf("내 약속 리스트");
	
	list_border_draw(22,7,35,10);
	list_border_draw(23,20,35,10);
	gotoxy(25,9);
	printf("           약속명              |             약속날짜");
	gotoxy(24,10);
	printf("─────────────────────────────────");
	gotoxy(24,11); 
	printf("①");
	gotoxy(35,11); 
	printf("조별과제");
	gotoxy(71,11); 
	printf("11/9");
	gotoxy(24,13); 
	printf("②");
	gotoxy(30,13); 
	printf("소프트글로벌 프로젝트");
	gotoxy(71,13); 
	printf("11/11");
	gotoxy(23,19);
	printf("수정할 약속 선택 :");
	gotoxy(26,23); 
	printf("▷ 약속명 : ");
	gotoxy(40,23); 
	printf("소프트글로벌 프로젝트 ");
	gotoxy(26,25); 
	printf("▷ 약속날짜 : ");
	gotoxy(40,25); 
	printf("11/11 ");
	gotoxy(26,27); 
	printf("▷ 약속시간 : ");
	gotoxy(40,27); 
	printf("3~4교시 ");
	gotoxy(26,29); 
	printf("▷ 약속멤버 : ");
	gotoxy(40,29); 
	printf("김동희, 이정훈, 이설희, 김진삼 ");
	gotoxy(25,32);
	printf("→ 수정하시겠습니까? (Y/N) ");
	
	gotoxy(60,6); 
	printf("뒤로가기 B, 종료 X, 계속하기 S :");
	scanf("%c",&command);	
	
	gotoxy(43,19);	
	scanf("%d",&number);
	gotoxy(53,32);	
	scanf("%d",&command1);
	gotoxy(23,34);	
}
