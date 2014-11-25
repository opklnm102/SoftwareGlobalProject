#include"structHeader.h"

void membership(){
	int x=32, y=7;
	structMember s;  //멤버 구조체	
	char txt[]=".txt";  //확장자
	char ask;  //저장 여부
	FILE *fp1,*fp2;	
	char fileName[30];
	int con=1;
	int backspace=0,i;
	char ch;

	//----------------------------UI그리기-----------------------------------------------

	while(con){
		screenBorderDraw();  //전체틀출력
		listBorderDraw(40,13);  //메뉴틀출력

		gotoxy(60,10); printf("-회원가입-\n");
		gotoxy(22+x,11+y); printf("학    번 : "); 
		gotoxy(22+x,13+y); printf("P      W : "); 
		gotoxy(22+x,15+y); printf("이    름 : "); 
		gotoxy(22+x,17+y); printf("고유코드 : ");

	//----------------------------회원가입정보입력-----------------------------------------------

		gotoxy(34+x,11+y); scanf("%s",s.ID);  fflush(stdin);
		gotoxy(34+x,13+y); 
		for(i=0; i<14; i++){  //비밀번호 입력시 ***로 출력부분
			ch=getch();		
			if(ch == 13){  //enter키(비밀번호입력끝부분) 확인
				s.password[i] = '\0';
				printf("\n"); break;
			}
			else if(ch == 8){  //키보드의 backspace동작
				if(i<1)
					backspace=0;
				if(backspace){
					i -= 2;
					printf("\b \b");  
					fflush(stdin);				
				}			
				else if(i>0)
					i -= 2;			
			}
			else{
				backspace=1;  //backspace인식 가능
				s.password[i] = ch;
				printf("*");
				fflush(stdin);
			}
		}			
		gotoxy(34+x,15+y); scanf("%s",s.name);  fflush(stdin);
		gotoxy(34+x,17+y); scanf("%s",s.backupPassword);  fflush(stdin);

		gotoxy(19+x,20+y); printf("모든 입력이 끝났습니까? (Y/N) ");
		scanf("%c",&ask); fflush(stdin);

	//---------------------------회원정보 txt에 저장-----------------------------------------------

		if(ask == 'y' || ask == 'Y'){
			strcpy(fileName,s.ID);			
			strcat(fileName,s.name);
			strcat(fileName,txt);
			fp1=fopen(fileName,"r");

			if(fp1 == NULL){  //파일이 없을 경우
				fp1=fopen(fileName,"w");
				fp2=fopen("회원목록.txt","a");		
				fprintf(fp1,"%s\n","회원정보");
				fprintf(fp1,"%s\n%s\n%s\n%s\n",s.ID,s.name,s.password,s.backupPassword);  //개인별 회원정보파일
				fprintf(fp2,"%s %s\n",s.ID,s.name);  //회원목록파일에 갱신
				con=0;
				fclose(fp1);
				fclose(fp2);
				gotoxy(60, 29); printf("회원 가입 완료!!!");
				getch();
			}
			else{  //파일이 있을 경우
				gotoxy(60, 29); printf("이미 회원가입하셨습니다.");
				getch();
				return;
			}
		}			
	}
}




