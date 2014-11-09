#include <stdio.h>
#include <Windows.h>
//
//void gotoxy(int x,int y)
//{	
//	COORD pos={x,y};
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
//}
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
	
	int i, j, k, m, n, q;
	
	gotoxy( 6, 6 );
	printf("   수정할 내용을 선택하세요: \n\n");
	gotoxy( 6, 8 );
	printf("1. 약속명      : \n");
	gotoxy( 6, 9 );
	printf("2. 약속장소    : \n");
	gotoxy( 6, 10);
	printf("3. 약속날짜    : \n");
	gotoxy( 6, 11 );
	printf("4. 약속시간    : \n");
	gotoxy( 6, 12 );
	printf("5. 함께할 친구 : \n");

	
	list_border_draw(7,13,25,15);
	gotoxy( 34, 6  );
	scanf("%d", &i );
	gotoxy( 23, 8  );
	scanf("%d", &j );
	gotoxy( 23, 9  );
	scanf("%d", &k );
	gotoxy( 23, 10 );
	scanf("%d", &m );
	gotoxy( 23, 11 );
	scanf("%d", &n );
	gotoxy( 23, 12 );
	scanf("%d", &q );
	printf("\n");
	gotoxy( 23, 30 );
}
