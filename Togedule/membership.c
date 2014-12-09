#include"structHeader.h"

void membership(){
	int x=32, y=7;
	structMember s;  //멤버 구조체	
	char txt[]=".txt";  //확장자
	char ask;  //저장 여부
	FILE *fp1,*fp2;	
	char fileName[20]="\0";
	int con=1;
	int backspace=0,i,j;
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
		//학번입력
		while(1){
			for(j=0; j<8; j++)  //초기화
				s.ID[j]='\0';
			gotoxy(34+x,11+y); 
			scanf("%s",s.ID); fflush(stdin);  
			if(!strcmp(s.ID,"b") || !strcmp(s.ID,"B"))  //뒤로가기
				return;
			else if(!strcmp(s.ID,"x") || !strcmp(s.ID,"X")){  //종료
				gotoxy(90,45);
				exit(1);
			}
			if(stringLengthcheck(s.ID,7)){  //문자열의 길이 체크
				gotoxy(21+x,21+y);  printf("학번을 7자리내로 입력하세요.");
			}  
			else if(numberErrorcheck(s.ID)){  //숫자이외의 값 체크
				gotoxy(21+x,21+y);  printf("                          ");  //오류메시지 라인클리어
				gotoxy(24+x,21+y);  printf("학번을 숫자만 입력하세요.   ");			
			}  			
			else{  //오류 없을시		  
				gotoxy(21+x,21+y);  printf("                          ");  //오류메시지 라인클리어
				break;  
			}
			gotoxy(34+x,11+y);  printf("                         ");  //학번입력라인 클리어			
		}

		//비밀번호입력
		for(j=0; j<20; j++)  //초기화
			s.password[j]='\0';
		gotoxy(34+x,13+y); 
		for(i=0; i<20; i++){  //비밀번호 입력시 ***로 출력부분
			ch=getch();		
			if(ch == 'x' || ch == 'X'){  //종료
				getch();
				gotoxy(90,45);
				exit(1);
			}
			else if(ch == 'B' || ch == 'b'){  //뒤로가기
				getch();
				return;
			}
			if(ch == 13){  //enter키(비밀번호입력끝부분) 확인
				if(i<4 || i>13){  //길이 오류
					i=-1;
					for(j=0; j<20; j++)  //초기화
						s.password[j]='\0';
					gotoxy(20+x,21+y); printf("패스워드는 4~13자리로 입력하세요.");
					gotoxy(34+x,13+y); printf("                      ");  //패스워드입력 라인클리어
					gotoxy(34+x,13+y);
				}
				else if(numberErrorcheck(s.password)){  //숫자이외의 값이 들어오는 오류
					i=-1;
					for(j=0; j<20; j++)  //초기화
						s.password[j]='\0';
					gotoxy(20+x,21+y); printf("패스워드는 숫자만 입력하세요.    ");
					gotoxy(34+x,13+y); printf("                      ");  //패스워드입력 라인클리어 
					gotoxy(34+x,13+y); 
				}
				else{  //오류없을시
					s.password[i] = '\0';
					gotoxy(20+x,21+y);   printf("                                 ");  //오류메시지 라인클리어 
					printf("\n"); break; 
				}
			}
			else if(ch == 8){  //키보드의 backspace동작
				if(i<1)
					backspace=0;  //backspace동작 안함
				if(backspace){  //backspace동작 함  
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

		//이름입력
		while(1){
			for(j=0; j<13; j++)  //초기화
				s.name[j]='\0';
			gotoxy(34+x,15+y); scanf("%s",s.name);  fflush(stdin);  //이름 입력 
			if(!strcmp(s.name,"b") || !strcmp(s.name,"B"))  //뒤로가기
				return;
			else if(!strcmp(s.name,"x") || !strcmp(s.name,"X")){  //종료
				gotoxy(90,45);
				exit(1);
			}
			if(stringLengthcheck(s.name,12)){  //문자열의 길이 체크
				gotoxy(23+x,21+y);  printf("이름은 6자내로 입력하세요.");	
			}  
			else if(hanErrorcheck(s.name)){   //한글이외의 값 체크	
				gotoxy(23+x,21+y);  printf("이름은 한글만 입력하세요. ");	
			} 		
			else{  //오류 없을시		  
				gotoxy(23+x,21+y);  printf("                          ");  //오류메시지 라인클리어
				break;			    
			}			
			gotoxy(34+x,15+y);  printf("                 ");  //이름입력라인 클리어			
		}

		//고유코드입력
		while(1){
			for(j=0; j<14; j++)  //초기화
				s.backupPassword[j]='\0';
			gotoxy(34+x,17+y); scanf("%s",s.backupPassword); fflush(stdin);  //고유코드 입력 
			if(!strcmp(s.backupPassword,"b") || !strcmp(s.backupPassword,"B"))  //뒤로가기
				return;
			else if(!strcmp(s.backupPassword,"x") || !strcmp(s.backupPassword,"X")){  //종료
				gotoxy(90,45);
				exit(1);
			}
			if(strlen(s.backupPassword)<4 || stringLengthcheck(s.backupPassword,13)){  //문자열의 길이 체크
				gotoxy(20+x,21+y);  printf("고유코드는 4~13자리로 입력하세요.");				
			}  
			else if(numberErrorcheck(s.backupPassword)){  //숫자이외의 값 체크
				gotoxy(21+x,21+y); printf("                                  ");  //오류메시지 라인클리어
				gotoxy(23+x,21+y);  printf("고유코드는 숫자만 입력하세요.");
			}  			
			else{  //오류 없을시		  
				gotoxy(21+x,21+y); printf("                                  ");  //오류메시지 라인클리어
				break;  
			}		
			gotoxy(34+x,17+y);  printf("                         ");  //고유코드입력라인 클리어			
		}

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
				gotoxy(60, 29); printf("회원 가입 완료!!!    ");
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




