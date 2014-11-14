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

