#include"structHeader.h"


void pwFind(){
	structMember s;  //��� ����ü	
	char id[8];  //�й�
	char fid[8],fname[13];  //���Ͽ��� �ҷ��� �й�,�̸�
	char newPassword[14];  
	char backupPassword[14];  //�����ڵ�
	char ask;  //���� ����
	FILE *fp1,*fp2;
	char txt[]=".txt";  //Ȯ����
	char fileName[20];  //������ �����̸�


	printf("-��й�ȣ �缳��-\n");
	printf("�й� : "); scanf("%s",id); fflush(stdin);
	printf("�����ڵ� : "); scanf("%s",backupPassword); fflush(stdin);
	printf("���ο�P  W : "); scanf("%s",newPassword); fflush(stdin);

	fp1=fopen("ȸ�����.txt","r");  //ȸ����� ����

	while(!feof(fp1)){  //���ϳ����� Ȯ��
		fscanf(fp1,"%s %s",fid,fname);  
		if(!strcmp(id,fid)){  //��Ͽ��� �ش�id�� ã���� ��� ������ ���� ��������
			strcpy(fileName,fid);
			strcat(fileName,fname);
			strcat(fileName,txt);
			fp2=fopen(fileName,"r");  //ȸ�����ԵǾ��ִ�.
			fclose(fp1);  //ȸ��������� �ݰ�
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

	
	printf("��� �Է��� �������ϱ�? (Y/N)");
	scanf("%c",&ask);

	//��������



}
