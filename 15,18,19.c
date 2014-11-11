#include <stdio.h>
#include <Windows.h>

void gotoxy(int x,int y)
{	
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void printMold() {

	int i;
	gotoxy(0,0);
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
	int stdX = 34, stdY = 6;
	int i, j, k, m, n, q;
	system("mode con:cols=130 lines=46");  //가로 130, 세로 45 
	
	printMold();
	gotoxy( stdX+16, stdY+5 );
	printf("   수정할 내용을 선택하세요: \n\n");
	gotoxy( stdX+5, stdY+7 );
	printf("1. 약속명      : \n");
	gotoxy( stdX+5, stdY+8 );
	printf("2. 약속장소    : \n");
	gotoxy( stdX+5, stdY+9 );
	printf("3. 약속날짜    : \n");
	gotoxy( stdX+5, stdY+10 );
	printf("4. 약속시간    : \n");
	gotoxy( stdX+5, stdY+11 );
	printf("5. 함께할 친구 : \n");
	gotoxy( 80 , 40 );
	printf("뒤로가기 B, 종료 X, 계속하기 S :");
	
	list_border_draw(stdX+6,stdY+12,25,15);
	gotoxy( stdX+44, stdY+5  );
	scanf("%d", &i );
	gotoxy( stdX+22, stdY+7  );
	scanf("%d", &j );
	gotoxy( stdX+22, stdY+8  );
	scanf("%d", &k );
	gotoxy( stdX+22, stdY+9 );
	scanf("%d", &m );
	gotoxy( stdX+22, stdY+10 );
	scanf("%d", &n );
	gotoxy( stdX+22, stdY+11 );
	scanf("%d", &q );
	printf("\n");
	gotoxy( stdX+22, stdY+30 );
}
