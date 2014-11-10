#include <stdio.h>
#include <windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

//테두리 그리기(시작좌표(x,y), 크기(width X height), 그릴도형)
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

int main() {
	int i;
	char command;
	char name[10]={' '};

	system("mode con:cols=130 lines=45");  //가로 130, 세로 45 

	border_draw(60,5,22,16,"━");
	gotoxy(60,6);
	printf("┏");
	gotoxy(102,6);
	printf("┓");
	gotoxy(60,21);
	printf("┗");
	gotoxy(102,21);
	printf("┛");
	for(i=0;i <14; i++){
	  gotoxy(60, 7+i);
	 printf("┃");
	}
	for(i=0;i <14; i++){
	  gotoxy(102, 7+i);
	 printf("┃");
	}	
	gotoxy(60,5);
	printf("나의 약속");	
	gotoxy(20,5); 
	printf("☆ 약속 메뉴 ☆");
	gotoxy(23,7); 
	printf("1. 약속만들기");
	gotoxy(23,9); 
	printf("2. 약속 수정");
	gotoxy(23,11); 
	printf("3. 약속 삭제");
	gotoxy(23,13); 
	printf("4. 약속 잡아보기");
	gotoxy(25,16);
	printf("▷ 메뉴 선택 :"); 
	
	gotoxy(65,8);
	printf("º팀프로젝트     / (11/9)");
	gotoxy(65,11);
	printf("º팀프로젝트2    / (11/11)");
	gotoxy(65,14);
	printf("º조별과제       / (11/18)");
	gotoxy(40,16);
	scanf("%c",&command);	
	gotoxy(22,23);

	
}
