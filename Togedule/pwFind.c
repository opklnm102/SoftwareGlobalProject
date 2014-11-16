#include"structHeader.h"


void pwFind(){
	structMember s;  //멤버 구조체	
	char id[8];  //학번
	char fid[8],fname[13];  //파일에서 불러온 학번,이름
	char newPassword[14];  
	char backupPassword[14];  //고유코드
	char ask;  //저장 여부
	FILE *fp1,*fp2;
	char txt[]=".txt";  //확장자
	char fileName[20];  //열기할 파일이름


	printf("-비밀번호 재설정-\n");
	printf("학번 : "); scanf("%s",id); fflush(stdin);
	printf("고유코드 : "); scanf("%s",backupPassword); fflush(stdin);
	printf("새로운P  W : "); scanf("%s",newPassword); fflush(stdin);

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
	if(fp2 == NULL){  //개인별 회원정보파일을 못열었을 경우(회원가입안되어있을경우)
		printf("회원가입하세요\n");
		return;
	}
	//회원정보입력
	fseek(fp2,10,SEEK_CUR);  //파일의 첫 "회원정보"때문에 커서 이동
	fscanf(fp2,"%s %s %s %s",s.ID,s.name,s.password,s.backupPassword);  //개인별 회원정보입력	

	
	printf("모든 입력이 끝났습니까? (Y/N)");
	scanf("%c",&ask);

	//정보변경



}
