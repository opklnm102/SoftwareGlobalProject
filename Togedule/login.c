#include"structHeader.h"

void login(structMember *s){
	char id[8],password[14],fid[8],fname[13];  //fid,fname 파일에서 불러온 학번,이름
	//structMember s;  //멤버 구조체	
	FILE *fp1,*fp2=NULL;
	char txt[]=".txt";  //확장자
	char fileName[20];  //열기할 파일이름
	int loginCount;  //로그인 횟수	
	char ch;
	int i=0;

	printf("*togedule*\n");
	printf("-Login-\n");
	//로그인 정보 입력
	printf("학번 : "); scanf("%s",id); fflush(stdin);    
	printf("P  W : "); 

	for(i=0; i<14; i++){  //비밀번호 입력시 ***로 출력부분
		ch=getch();		
		if(ch == 13){  //enter키(비밀번호입력끝부분) 확인
			password[i] = '\0';
			printf("\n"); break;
		}
		else if(ch == 8){
			i -= 2;
			fflush(stdin);  //좌표설정해서 printf("*");로 backspace처럼 지울수있게 좌표 x로 -1한다음에 거기서부터공백1칸출력
		}
		else{
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
		printf("회원가입하세요\n");
		return;
	}
	//회원정보입력
	fseek(fp2,10,SEEK_CUR);  //파일의 첫 "회원정보"때문에 커서 이동
	fscanf(fp2,"%s %s %s %s",s->ID,s->name,s->password,s->backupPassword);  //개인별 회원정보입력

	fclose(fp2);
	fp2=NULL;

	loginCount=0;
	while(loginCount<4){  //로그인 횟수 5가 넘을 경우 고유코드로 초기화
		if(strcmp(password,s->password)==0) //로그인		
			mainMenu(s);
		else{  //로그인 실패
			loginCount++;
			printf("로그인 실패\nPW재입력 : "); 
			for(i=0; i<14; i++){  //비밀번호 입력시 ***로 출력부분
				ch=getch();
				checkInput();
				if(ch == 13){  //enter키(비밀번호입력끝부분) 확인 
					password[i] = '\0';
					printf("\n"); break;
				}
				password[i] = ch;
				printf("*");
				fflush(stdin);   
			}			
		}
	}

	//PW를 고유코드로 설정->에러->파일에 출력시 널값은 출력안되게.. 수정바람
	printf("PW 고유코드로 초기화\n");
	fp2=fopen(fileName,"w");
	fprintf(fp2,"%s\n","회원정보");
	fprintf(fp2,"%s\n%s\n%s\n%s\n",s->ID,s->name,s->backupPassword,s->backupPassword);  //개인별 회원정보파일 갱신
	fclose(fp2);	
	getch();

}