#include"structHeader.h"

void membership(){

	structMember s;  //��� ����ü	
	char txt[]=".txt";  //Ȯ����
	char ask;  //���� ����
	FILE *fp1,*fp2;	
	char fileName[30];
	int con=1;

	printf("-ȸ������-\n");

	while(con){
		printf("�й� : "); scanf("%s",s.ID);  fflush(stdin);
		printf("P  W : "); scanf("%s",s.password);  fflush(stdin);
		printf("�̸� : "); scanf("%s",s.name);  fflush(stdin);
		printf("�����ڵ� : "); scanf("%s",s.backupPassword);  fflush(stdin);

		printf("��� �Է��� �������ϱ�? (Y/N)");
		scanf("%c",&ask); fflush(stdin);

		if(ask == 'y' || ask == 'Y'){
			strcpy(fileName,s.ID);			
			strcat(fileName,s.name);
			strcat(fileName,txt);
			fp1=fopen(fileName,"r");

			if(fp1 == NULL){  //������ ���� ���
				fp1=fopen(fileName,"w");
				fp2=fopen("ȸ�����.txt","a");		
				fprintf(fp1,"%s\n","ȸ������");
				fprintf(fp1,"%s\n%s\n%s\n%s\n",s.ID,s.name,s.password,s.backupPassword);  //���κ� ȸ����������
				fprintf(fp2,"%s %s\n",s.ID,s.name);  //ȸ��������Ͽ� ����
				con=0;
				fclose(fp1);
				fclose(fp2);
				printf("ȸ�� ���� �Ϸ�!!! \n");
			}
			else{  //������ ���� ���
				printf("�̹� ȸ�������ϼ̽��ϴ�.\n");
				getch();
				return;
			}
		}
	}
}




