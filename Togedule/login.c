#include"structHeader.h"

void login(structMember *s){
	char id[8],password[14],fid[8],fname[13];  //fid,fname 파일에서 불러온 학번,이름
	//structMember s;  //멤버 구조체	
	FILE *fp1,*fp2=NULL;
	char txt[]=".txt";  //확장자
	char fileName[20];  //열기할 파일이름
	int loginCount;  //로그인 횟수	
	char ch;
	int backspace=0,i=0;

	//----------------------------UI그리기-----------------------------------------------
	screenBorderDraw();  //전체틀출력
	listBorderDraw(40,13);  //메뉴틀출력
	gotoxy(60,10); printf("*Togedule*");
	gotoxy(63,18);   printf("-Login-");
	//로그인 정보 입력
	gotoxy(54, 21); printf("학     번 : "); 
	gotoxy(54, 23); printf("P       W : "); 

	gotoxy(66, 21); scanf("%s",id); fflush(stdin);  //학번입력
	gotoxy(66, 23);  //비밀번호입력
	for(i=0; i<14; i++){  //비밀번호 입력시 ***로 출력부분
		ch=getch();		
		if(ch == 13){  //enter키(비밀번호입력끝부분) 확인

			password[i] = '\0';
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
			password[i] = ch;
			printf("*");
			fflush(stdin);
		}
	}		

	//회원가입여부 확인	
	fp1=fopen("회원목록.txt","r");  //회원목록 열고

	while(!feof(fp1)){  //파일끝까지 확인
		fscanf(fp1,"%s %s",fid,fname);  
		if(!strcmp(id,fid)){  //목록에서 해당id를 찾았을 경우 파일을 열고 나가가고
			strcpy(fileName,fid);
			strcat(fileName,fname);
			strcat(fileName,txt);
			fp2=fopen(fileName,"r");  //회원가입되어있다.
			fclose(fp1);  //회원목록파일 닫고
			fp1=NULL;
			break;  
		}
	}
	if(fp2 == NULL){  //개인별 회원정보파일을 못열었을 경우(회원가입안되어있을경우)
		gotoxy(60, 27); printf("회원가입하세요....        ");
		getch();
		return;
	}
	//회원정보입력
	fseek(fp2,10,SEEK_CUR);  //파일의 첫 "회원정보"때문에 커서 이동
	fscanf(fp2,"%s %s %s %s",s->ID,s->name,s->password,s->backupPassword);  //개인별 회원정보입력

	fclose(fp2);
	fp2=NULL;

	loginCount=0;
	while(loginCount<4){  //로그인 횟수 5가 넘을 경우 고유코드로 초기화
		if(strcmp(password,s->password)==0){ //로그인	
			gotoxy(60, 27); printf("환영합니다!!!          ",loginCount); 
			getch();
			mainMenu(s);
		}
		else{  //로그인 실패
			loginCount++;
			gotoxy(60, 27); printf("로그인 %d회 실패",loginCount); 
			gotoxy(54, 23); printf("P       W : ");
			gotoxy(66, 23); printf("                         ");  //전시도의 *를 지우기위해
			gotoxy(66, 23); 
			for(i=0; i<14; i++){  //비밀번호 입력시 ***로 출력부분
				ch=getch();		
				if(ch == 13){  //enter키(비밀번호입력끝부분) 확인
					password[i] = '\0';
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
					password[i] = ch;
					printf("*");
					fflush(stdin);
				}
			}
		}
	}
	
	//PW를 고유코드로 설정->에러->파일에 출력시 널값은 출력안되게.. 수정바람
	gotoxy(58, 27); printf("PW 고유코드로 초기화");
	fp2=fopen(fileName,"w");
	fprintf(fp2,"%s\n","회원정보");
	fprintf(fp2,"%s\n%s\n%s\n%s\n",s->ID,s->name,s->backupPassword,s->backupPassword);  //개인별 회원정보파일 갱신
	fclose(fp2);	
	getch();
}
