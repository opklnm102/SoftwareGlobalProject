#include"structHeader.h"

void membership(){

	structMember s;  //멤버 구조체	
	char txt[]=".txt";  //확장자
	char ask;  //저장 여부
	FILE *fp1,*fp2;	
	char fileName[30];
	int con=1;

	printf("-회원가입-\n");

	while(con){
		printf("학번 : "); scanf("%s",s.ID);  fflush(stdin);
		printf("P  W : "); scanf("%s",s.password);  fflush(stdin);
		printf("이름 : "); scanf("%s",s.name);  fflush(stdin);
		printf("고유코드 : "); scanf("%s",s.backupPassword);  fflush(stdin);

		printf("모든 입력이 끝났습니까? (Y/N)");
		scanf("%c",&ask); fflush(stdin);

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
				printf("회원 가입 완료!!! \n");
			}
			else{  //파일이 있을 경우
				printf("이미 회원가입하셨습니다.\n");
				getch();
				return;
			}
		}
	}
}




