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
	int backspace=0,i,j;
	char ch;

	while(con){

		//----------------------------UI�׸���-----------------------------------------------
		screenBorderDraw();  //��üƲ���
		listBorderDraw(40,13);  //�޴�Ʋ���
		gotoxy(56,10);	printf("-��й�ȣ �缳��-");
		gotoxy(20+x, 15+y); printf("��    ��  : ");   
		gotoxy(20+x, 18+y); printf("�����ڵ�  : ");
		gotoxy(20+x, 21+y); printf("���ο� PW : ");

		while(1){
			for(j=0; j<8; j++)  //�ʱ�ȭ
				s.ID[j]='\0';
			gotoxy(34+x,15+y); scanf("%s",s.ID); fflush(stdin);
			if(!strcmp(s.ID,"b") || !strcmp(s.ID,"B"))  //�ڷΰ���
				return;
			else if(!strcmp(s.ID,"x") || !strcmp(s.ID,"X")){  //����
				gotoxy(90,45);
				exit(1);
			}
			if(stringLengthcheck(s.ID,7)){  //���ڿ��� ���� üũ
				gotoxy(20+x,25+y);  printf("�й��� 7�ڸ����� �Է��ϼ���.");
			}  
			else if(numberErrorcheck(s.ID)){  //�����̿��� �� üũ
				gotoxy(20+x,25+y);  printf("                             ");  //�����޽��� ����Ŭ����
				gotoxy(22+x,25+y);  printf("�й��� ���ڸ� �Է��ϼ���.   ");			
			}  			
			else{  //���� ������		  
				gotoxy(20+x,25+y);  printf("                             ");  //�����޽��� ����Ŭ����
				break;  
			}
			gotoxy(34+x,15+y);  printf("                       ");  //�й��Է¶��� Ŭ����			
		}		

		//�����ڵ��Է�
		while(1){
			for(j=0; j<14; j++)  //�ʱ�ȭ
				s.backupPassword[j]='\0';
			gotoxy(34+x,18+y); scanf("%s",s.backupPassword); fflush(stdin);  //�����ڵ� �Է�
			if(!strcmp(s.backupPassword,"b") || !strcmp(s.backupPassword,"B"))  //�ڷΰ���
				return;
			else if(!strcmp(s.backupPassword,"x") || !strcmp(s.backupPassword,"X")){  //����
				gotoxy(90,45);
				exit(1);
			}
			if(strlen(s.backupPassword)<4 || stringLengthcheck(s.backupPassword,13)){  //���ڿ��� ���� üũ
				gotoxy(18+x,25+y);  printf("�����ڵ�� 4~13�ڸ��� �Է��ϼ���.");				
			}  
			else if(numberErrorcheck(s.backupPassword)){  //�����̿��� �� üũ
				gotoxy(18+x,25+y); printf("                                  ");  //�����޽��� ����Ŭ����
				gotoxy(22+x,25+y);  printf("�����ڵ�� ���ڸ� �Է��ϼ���.");
			}  			
			else{  //���� ������		  
				gotoxy(22+x,25+y); printf("                                  ");  //�����޽��� ����Ŭ����
				break;  
			}		
			gotoxy(34+x,18+y);  printf("                    ");  //�����ڵ��Է¶��� Ŭ����			
		}

		for(j=0; j<20; j++)  //�ʱ�ȭ
			s.password[j]='\0';
		gotoxy(34+x,21+y);  //��й�ȣ�Է�
		for(i=0; i<20; i++){  //��й�ȣ �Է½� ***�� ��ºκ�
			ch=getch();	
			if(ch == 'x' || ch == 'X'){  //����

				gotoxy(90,45);
				getch();
				exit(1);
			}
			else if(ch == 'B' || ch == 'b'){  //�ڷΰ���
				getch();
				return;
			}
			if(ch == 13){  //enterŰ(��й�ȣ�Է³��κ�) Ȯ��
				if(i<4 || i>13){  //���� ����
					i=-1;
					for(j=0; j<20; j++)  //�ʱ�ȭ
						s.password[j]='\0';
					gotoxy(18+x,25+y); printf("�н������ 4~13�ڸ��� �Է��ϼ���.");
					gotoxy(34+x,21+y); printf("                    ");  //�н������Է� ����Ŭ����
					gotoxy(34+x,21+y);
				}
				else if(numberErrorcheck(s.password)){  //�����̿��� ���� ������ ����
					i=-1;
					for(j=0; j<20; j++)  //�ʱ�ȭ
						s.password[j]='\0';
					gotoxy(18+x,25+y);  printf("                                 ");  //�����޽��� ����Ŭ����
					gotoxy(20+x,25+y); printf("�н������ ���ڸ� �Է��ϼ���.    ");
					gotoxy(34+x,21+y); printf("                       ");  //�н������Է� ����Ŭ���� 
					gotoxy(34+x,21+y);
				}
				else{  //����������
					s.password[i] = '\0';
					gotoxy(18+x,25+y);  printf("                                 ");  //�����޽��� ����Ŭ���� 
					printf("\n"); break;
				}
			}
			else if(ch == 8){  //Ű������ backspace����
				if(i<1)
					backspace=0;  //backspace���� ����
				if(backspace){  //backspace���� ��  
					i -= 2;
					printf("\b \b");  
					fflush(stdin);				
				}			
				else if(i>0)
					i -= 2;			
			}
			else{
				backspace=1;  //backspace�ν� ����
				s.password[i] = ch;
				printf("*");
				fflush(stdin);
			}
		}

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

		gotoxy(17+x,24+y); printf("��� �Է��� �������ϱ�? (Y/N) ");
		scanf("%c",&ask);

		//��������
		if(ask == 'y' || ask == 'Y'){

			if(fp2 == NULL){  //���κ� ȸ������������ �������� ���(ȸ�����ԾȵǾ��������)
				gotoxy(56, 29); printf("ȸ�������ϼ���"); 
				getch();
				return;
			}

			//ȸ�������Է�
			fseek(fp2,10,SEEK_CUR);  //������ ù "ȸ������"������ Ŀ�� �̵�
			fscanf(fp2,"%s %s %s %s",s.ID,s.name,s.password,s.backupPassword);  //���κ� ȸ�������Է�	

			fclose(fp2);
			fp2=NULL;

			if(!strcmp(backupPassword,s.backupPassword)) {  //�����ڵ尡 ������� ��й�ȣ �缳�� �ƴ� ��� �ݺ�
				fp2=fopen(fileName,"w");
				fprintf(fp2,"%s\n","ȸ������");
				fprintf(fp2,"%s\n%s\n%s\n%s\n",s.ID,s.name,newPassword,s.backupPassword);  //���κ� ȸ���������� ����
				con=0;
				fclose(fp2);
				gotoxy(56, 29); printf("��й�ȣ �缳�� �Ϸ�!!!");
				getch();
			}	
			else{
				gotoxy(56, 29); printf("��й�ȣ �缳�� ����!!!");
				getch();
			}
		}
		else{
			gotoxy(56, 29); printf("ó������ �ٽ� �Է��ϼ���.");
			getch();
		}
	}
}
