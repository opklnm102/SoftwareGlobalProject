#include"structHeader.h"



void login(){
	char id[8],password[14],fid[8],fname[13];  //fid,fname ���Ͽ��� �ҷ��� �й�,�̸�
	structMember s;  //��� ����ü	
	FILE *fp1,*fp2=NULL;
	char txt[]=".txt";  //Ȯ����
	char fileName[20];  //������ �����̸�
	int loginCount;  //�α��� Ƚ��

	printf("*togedule*\n");
	printf("-Login-\n");
	//�α��� ���� �Է�
	printf("�й� : "); scanf("%s",id);  
	printf("P  W : "); scanf("%s",password);

	//ȸ�����Կ��� Ȯ��	
	fp1=fopen("ȸ�����.txt","r");  //ȸ����� ����

	while(!feof(fp1)){  //���ϳ����� Ȯ��
		fscanf(fp1,"%s %s",fid,fname);  
		if(!strcmp(id,fid)){  //��Ͽ��� �ش�id�� ã���� ��� ������ ���� ��������
			strcpy(fileName,fid);
			strcat(fileName,fname);
			strcat(fileName,txt);
			fp2=fopen(fileName,"r");  //ȸ�����ԵǾ��ִ�.
			fclose(fp1);  //ȸ��������� �ݰ�
			fp1=NULL;
			break;  
		}
	}
	if(fp2 == NULL){  //���κ� ȸ������������ �������� ���(ȸ�����ԾȵǾ��������)
		printf("ȸ�������ϼ���\n");
		return;
	}
	//ȸ�������Է�
	fseek(fp2,10,SEEK_CUR);  //������ ù "ȸ������"������ Ŀ�� �̵�
	fscanf(fp2,"%s %s %s %s",s.ID,s.name,s.password,s.backupPassword);  //���κ� ȸ�������Է�

	fclose(fp2);
	fp2=NULL;
	loginCount=0;
	while(loginCount<4){  //�α��� Ƚ�� 5�� ���� ��� �����ڵ�� �ʱ�ȭ
		if(strcmp(password,s.password)==0) //�α���		
			mainMenu();
		else{  //�α��� ����
			loginCount++;
			printf("�α��� ����\nPW���Է� : "); scanf("%s",password); fflush(stdin);
		}
	}

	//PW�� �����ڵ�� ����->����
	printf("PW �����ڵ�� �ʱ�ȭ\n");
	fp2=fopen(fileName,"a");
	fseek(fp2,0,SEEK_SET);
	while(!feof(fp2)){  //���ϳ����� Ȯ��
		fscanf(fp2,"%s",fname);  //��й�ȣ�� �ִ� Ŀ���� ��ġ�� ã�´�. 
		if(!strcmp(s.name,fname))  
			fprintf(fp2,"%s",s.backupPassword);
	}
	fclose(fp2);
	//getch();
}




