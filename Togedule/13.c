#include<stdio.h> 
#include<windows.h> 
 
void printMold();
void gotoxy(int x,int y);
//테두리 그리기(시작좌표(x,y), 크기(width X height), 그릴도형)
void border_draw(int x,int y,int width,int height,char figure[]);
void list_border_draw(int x,int y,int width,int height);

int main() {
	char appname[41],name[13];
	int command1,number;
	int x=85,y=28;

	system("mode con:cols=130 lines=46");  //가로 130, 세로 45 	
	printMold();
	list_border_draw(x-70,y-23,48,30);

	gotoxy(x-54,y-18);   
	printf("☆ 약속 만들기 ☆");
	gotoxy(x-52,y-16); 
	printf("약속명 :");
	gotoxy(x-22,y-16); 
	printf("인원수 :");
	gotoxy(x-52,y-14); 
	printf("이름검색 :");
	gotoxy(x-2,y-13); 
	printf("약속멤버");
	
	list_border_draw(x-53,y-12,25,10);
	list_border_draw(x-2,y-13,10,10);
	gotoxy(x-50,y-10); 
	printf("ex)");
	gotoxy(x-50,y-10);
	printf("① 컴퓨터공학과 13920 이설희");
	gotoxy(x-50,y-8); 
	printf("② 경제학과 13920 이설희");	
	gotoxy(x-50,y-4); 
	printf("→ 이름번호 선택 : ");
	gotoxy(x+2,y-11); 
	printf("ex)");	
	gotoxy(x+2,y-10); 
	printf("이정훈");	
	gotoxy(x+2,y-8); 
	printf("김동희");	
	gotoxy(x+2,y-6); 
	printf("김진삼");	
	gotoxy(x+3,y+13);    
	printf("뒤로가기 B, 종료 X, 계속하기 S :");	
	gotoxy(x-42,y-16);	
	scanf("%s",&appname);
	gotoxy(x-12,y-16);	
	scanf("%d",&number);
	gotoxy(x-41,y-14);	
	scanf("%s",&name);
	gotoxy(x-30,y-4);	
	scanf("%d",&command1);
	gotoxy(x-52,y-2);	
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
