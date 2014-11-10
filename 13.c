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
	char appname[41],name[13];
	int command1,number;

	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 	

	gotoxy(21,5); 
	printf("☆ 약속 만들기 ☆");
	gotoxy(23,7); 
	printf("약속명 :");
	gotoxy(53,7); 
	printf("인원수 :");
	gotoxy(23,9); 
	printf("이름검색 :");
	gotoxy(73,10); 
	printf("약속멤버");

	list_border_draw(22,10,25,10);
	list_border_draw(73,10,10,10);
	gotoxy(25,12); 
	printf("ex)");
	gotoxy(25,13);
	printf("① 컴퓨터공학과 13920 이설희");
	gotoxy(25,15); 
	printf("② 경제학과 13920 이설희");	
	gotoxy(25,19); 
	printf("→ 이름번호 선택 : ");
	gotoxy(77,12); 
	printf("ex)");	
	gotoxy(77,13); 
	printf("이정훈");	
	gotoxy(77,15); 
	printf("김동희");	
	gotoxy(77,17); 
	printf("김진삼");	
	gotoxy(60,6); 
	printf("뒤로가기 B, 종료 X, 계속하기 S :");
	scanf("%c",&command);	
	gotoxy(33,7);	
	scanf("%s",&appname);
	gotoxy(63,7);	
	scanf("%d",&number);
	gotoxy(34,9);	
	scanf("%s",&name);
	gotoxy(45,19);	
	scanf("%d",&command1);
	gotoxy(23,21);	
}
