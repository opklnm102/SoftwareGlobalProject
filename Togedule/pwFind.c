#include"structHeader.h"

void pwFind(){
	structMember s;  //��� ����ü	
	char id[8];  //�й�
	char fid[8],fname[13];  //���Ͽ��� �ҷ��� �й�,�̸�
	char newPassword[14];  
	char backupPassword[14];  //�����ڵ�
	char ask;  //���� ����
	FILE *fp1,*fp2=NULL;  //fp1�� ȸ�����, fp2�� ��������
	char txt[]=".txt";  //Ȯ����
	char fileName[20];  //������ �����̸�
	int con=1;  
	int x=34, y=3;  //��ǥ

	while(con){

		//----------------------------UI�׸���-----------------------------------------------
		screenBorderDraw();  //��üƲ���
		listBorderDraw(40,13);  //�޴�Ʋ���
		gotoxy(56,10);	printf("-��й�ȣ �缳��-\n");
		gotoxy(20+x, 15+y); printf("��    ��  : ");   
		gotoxy(20+x, 18+y); printf("�����ڵ�  : ");
		gotoxy(20+x, 21+y); printf("���ο� PW : ");

		gotoxy(34+x,15+y); scanf("%s",id); fflush(stdin);
		gotoxy(34+x,18+y); scanf("%s",backupPassword); fflush(stdin);
		gotoxy(34+x,21+y); scanf("%s",newPassword); fflush(stdin);

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
			gotoxy(56, 29); printf("ȸ�������ϼ���"); 
			Sleep(2000);
			return;
		}
		//ȸ�������Է�
		fseek(fp2,10,SEEK_CUR);  //������ ù "ȸ������"������ Ŀ�� �̵�
		fscanf(fp2,"%s %s %s %s",s.ID,s.name,s.password,s.backupPassword);  //���κ� ȸ�������Է�	

		gotoxy(17+x,24+y); printf("��� �Է��� �������ϱ�? (Y/N) ");
		scanf("%c",&ask);
		fclose(fp2);
		fp2=NULL;

		//��������
		if(ask == 'y' || ask == 'Y'){
			if(!strcmp(backupPassword,s.backupPassword)) {  //�����ڵ尡 ������� ��й�ȣ �缳�� �ƴ� ��� �ݺ�
				fp2=fopen(fileName,"w");
				fprintf(fp2,"%s\n","ȸ������");
				fprintf(fp2,"%s\n%s\n%s\n%s\n",s.ID,s.name,newPassword,s.backupPassword);  //���κ� ȸ���������� ����
				con=0;
				fclose(fp2);
				gotoxy(56, 29); printf("��й�ȣ �缳�� �Ϸ�!!!");
				Sleep(2000);
			}	
			else{
			gotoxy(56, 29); printf("��й�ȣ �缳�� ����!!!");
			Sleep(2000);
			}
		}
		else{
			gotoxy(56, 29); printf("�ٽ��Է��Ͻñ�ٶ��ϴ�.");
			Sleep(2000);
		}
	}
}
