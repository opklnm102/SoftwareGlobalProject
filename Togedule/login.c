#include"structHeader.h"



void login(){
	char id[8],password[14],fid[8],fname[13];  //fid,fname 파일에서 불러온 학번,이름
	structMember s;  //멤버 구조체	
	FILE *fp1,*fp2=NULL;
	char txt[]=".txt";  //확장자
	char fileName[20];  //열기할 파일이름
	int loginCount;  //로그인 횟수

	printf("*togedule*\n");
	printf("-Login-\n");
	//로그인 정보 입력
	printf("학번 : "); scanf("%s",id);  
	printf("P  W : "); scanf("%s",password);

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
	fscanf(fp2,"%s %s %s %s",s.ID,s.name,s.password,s.backupPassword);  //개인별 회원정보입력

	fclose(fp2);
	fp2=NULL;
	loginCount=0;
	while(loginCount<4){  //로그인 횟수 5가 넘을 경우 고유코드로 초기화
		if(strcmp(password,s.password)==0) //로그인		
			mainMenu();
		else{  //로그인 실패
			loginCount++;
			printf("로그인 실패\nPW재입력 : "); scanf("%s",password); fflush(stdin);
		}
	}

	//PW를 고유코드로 설정->에러
	printf("PW 고유코드로 초기화\n");
	fp2=fopen(fileName,"a");
	fseek(fp2,0,SEEK_SET);
	while(!feof(fp2)){  //파일끝까지 확인
		fscanf(fp2,"%s",fname);  //비밀번호가 있는 커서의 위치를 찾는다. 
		if(!strcmp(s.name,fname))  
			fprintf(fp2,"%s",s.backupPassword);
	}
	fclose(fp2);
	//getch();
}




