#include <stdio.h>
#include <windows.h>

void printMold();
void gotoxy(int x,int y);
//테두리 그리기(시작좌표(x,y), 크기(width X height), 그릴도형)
void border_draw(int x,int y,int width,int height,char figure[]);
void list_border_draw(int x,int y,int width,int height);

int main() {
	char command;
	char name[10]={' '};
	int x=80,y=32;

	system("mode con:cols=130 lines=46");  //가로 130, 세로 46
	
	printMold();		
	list_border_draw(x-62,y-25,48,30);  //밖의 테두리
	list_border_draw(x-15,y-18,22,16);  //안의 테두리
	gotoxy(x-15,y-18);    
	printf("나의 약속");	
	gotoxy(x-55,y-18);    
	printf("☆ 약속 메뉴 ☆");
	gotoxy(x-52,y-16); 
	printf("1. 약속만들기");
	gotoxy(x-52,y-14); 
	printf("2. 약속 수정");
	gotoxy(x-52,y-12); 
	printf("3. 약속 삭제");
	gotoxy(x-52,y-10); 
	printf("4. 약속 잡아보기");
	gotoxy(x-40,y-7);  
	printf("▷ 메뉴 선택 :"); 
	
	gotoxy(x-10,y-15);
	printf("º팀프로젝트     / (11/9)");
	gotoxy(x-10,y-12);
	printf("º팀프로젝트2    / (11/11)");
	gotoxy(x-10,y-9);
	printf("º조별과제       / (11/18)");
	gotoxy(x-25,y-7);
	scanf("%c",&command);	
	gotoxy(x-53,y);	
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
