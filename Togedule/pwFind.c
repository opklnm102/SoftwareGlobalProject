#include"structHeader.h"

void pwFind(){
	structMember s;  //멤버 구조체	
	char id[8];  //학번
	char fid[8],fname[13];  //파일에서 불러온 학번,이름
	char newPassword[14];  
	char backupPassword[14];  //고유코드
	char ask;  //저장 여부
	FILE *fp1,*fp2=NULL;  //fp1은 회원목록, fp2는 개인파일
	char txt[]=".txt";  //확장자
	char fileName[20];  //열기할 파일이름
	int con=1;  
	int x=34, y=3;  //좌표
	int backspace=0,i;
	char ch;

	while(con){

		//----------------------------UI그리기-----------------------------------------------
		screenBorderDraw();  //전체틀출력
		listBorderDraw(40,13);  //메뉴틀출력
		gotoxy(56,10);	printf("-비밀번호 재설정-");
		gotoxy(20+x, 15+y); printf("학    번  : ");   
		gotoxy(20+x, 18+y); printf("고유코드  : ");
		gotoxy(20+x, 21+y); printf("새로운 PW : ");

		gotoxy(34+x,15+y); scanf("%s",id); fflush(stdin);
		gotoxy(34+x,18+y); scanf("%s",backupPassword); fflush(stdin);
		gotoxy(34+x,21+y); 
		for(i=0; i<14; i++){  //비밀번호 입력시 ***로 출력부분
			ch=getch();		
			if(ch == 13){  //enter키(비밀번호입력끝부분) 확인
				newPassword[i] = '\0';
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
				newPassword[i] = ch;
				printf("*");
				fflush(stdin);
			}
		}

		fp1=fopen("회원목록.txt","r");  //회원목록 열고

		while(!feof(fp1)){  //파일끝까지 확인
			fscanf(fp1,"%s %s",fid,fname);  
			if(!strcmp(id,fid)){  //목록에서 해당id를 찾았을 경우 파일을 열고 나가가고
				strcpy(fileName,fid);
				strcat(fileName,fname);
				strcat(fileName,txt);
				fp2=fopen(fileName,"r");  //회원가입되어있다.
				fclose(fp1);  //회원목록파일 닫고
				break;  
			}
		}		

		gotoxy(17+x,24+y); printf("모든 입력이 끝났습니까? (Y/N) ");
		scanf("%c",&ask);

		//정보변경
		if(ask == 'y' || ask == 'Y'){

			if(fp2 == NULL){  //개인별 회원정보파일을 못열었을 경우(회원가입안되어있을경우)
				gotoxy(56, 29); printf("회원가입하세요"); 
				getch();
				return;
			}

			//회원정보입력
			fseek(fp2,10,SEEK_CUR);  //파일의 첫 "회원정보"때문에 커서 이동
			fscanf(fp2,"%s %s %s %s",s.ID,s.name,s.password,s.backupPassword);  //개인별 회원정보입력	

			fclose(fp2);
			fp2=NULL;

			if(!strcmp(backupPassword,s.backupPassword)) {  //고유코드가 같을경우 비밀번호 재설정 아닐 경우 반복
				fp2=fopen(fileName,"w");
				fprintf(fp2,"%s\n","회원정보");
				fprintf(fp2,"%s\n%s\n%s\n%s\n",s.ID,s.name,newPassword,s.backupPassword);  //개인별 회원정보파일 갱신
				con=0;
				fclose(fp2);
				gotoxy(56, 29); printf("비밀번호 재설정 완료!!!");
				getch();
			}	
			else{
				gotoxy(56, 29); printf("비밀번호 재설정 실패!!!");
				getch();
			}
		}
		else{
			gotoxy(56, 29); printf("처음부터 다시 입력하세요.");
			getch();
		}
	}
}
