#include"structHeader.h"

void membership(){
	int x=32, y=7;
	structMember s;  //��� ����ü	
	char txt[]=".txt";  //Ȯ����
	char ask;  //���� ����
	FILE *fp1,*fp2;	
	char fileName[20]="\0";
	int con=1;
	int backspace=0,i,j;
	char ch;

	//----------------------------UI�׸���-----------------------------------------------

	while(con){
		screenBorderDraw();  //��üƲ���
		listBorderDraw(40,13);  //�޴�Ʋ���

		gotoxy(60,10); printf("-ȸ������-\n");
		gotoxy(22+x,11+y); printf("��    �� : "); 
		gotoxy(22+x,13+y); printf("P      W : "); 
		gotoxy(22+x,15+y); printf("��    �� : "); 
		gotoxy(22+x,17+y); printf("�����ڵ� : ");

		//----------------------------ȸ�����������Է�-----------------------------------------------
		//�й��Է�
		while(1){
			for(j=0; j<8; j++)  //�ʱ�ȭ
				s.ID[j]='\0';
			gotoxy(34+x,11+y); scanf("%s",s.ID); fflush(stdin);  
			if(stringLengthcheck(s.ID,7)){}  //���ڿ��� ���� üũ
			else if(numberErrorcheck(s.ID)){}  //�����̿��� �� üũ			
			else{  //���� ������		  
				gotoxy(28+x,21+y);  printf("              ");  //�����޽��� ����Ŭ����
				break;  
			}
			gotoxy(28+x,21+y);  printf("�й� �Է� ����");
			gotoxy(34+x,11+y);  printf("              ");  //�й��Է¶��� Ŭ����			
		}

		//��й�ȣ�Է�
		for(j=0; j<20; j++)  //�ʱ�ȭ
						s.password[j]='\0';
		gotoxy(34+x,13+y); 
		for(i=0; i<20; i++){  //��й�ȣ �Է½� ***�� ��ºκ�
			ch=getch();		
			if(ch == 13){  //enterŰ(��й�ȣ�Է³��κ�) Ȯ��
				if(i<4 || i>13){  //���� ����
					i=-1;
					for(j=0; j<20; j++)  //�ʱ�ȭ
						s.password[j]='\0';
					gotoxy(28+x,21+y); printf("�н����� �Է� ����");
					gotoxy(34+x,13+y); printf("                ");  //�����޽��� ����Ŭ����
					gotoxy(34+x,13+y);
				}
				else if(numberErrorcheck(s.password)){  //�����̿��� ���� ������ ����
					i=-1;
					for(j=0; j<20; j++)  //�ʱ�ȭ
						s.password[j]='\0';
					gotoxy(28+x,21+y); printf("�н����� �Է� ����");
					gotoxy(34+x,13+y); printf("                  ");  //�����޽��� ����Ŭ���� 
					gotoxy(34+x,13+y);
				}
				else{  //����������
					s.password[i] = '\0';
					gotoxy(28+x,21+y); printf("                  ");  //�����޽��� ����Ŭ���� 
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

		//�̸��Է�
		while(1){
			for(j=0; j<13; j++)  //�ʱ�ȭ
				s.name[j]='\0';
			gotoxy(34+x,15+y); scanf("%s",s.name);  fflush(stdin);  //�̸� �Է�  
			if(stringLengthcheck(s.name,12)){}  //���ڿ��� ���� üũ
			else if(hanErrorcheck(s.name)){}  //�ѱ��̿��� �� üũ			
			else{  //���� ������		  
				gotoxy(28+x,21+y);  printf("              ");  //�����޽��� ����Ŭ����
				break;  
			}
			gotoxy(28+x,21+y);  printf("�̸� �Է� ����");
			gotoxy(34+x,15+y);  printf("              ");  //�̸��Է¶��� Ŭ����			
		}

		//�����ڵ��Է�
		while(1){
			for(j=0; j<14; j++)  //�ʱ�ȭ
				s.backupPassword[j]='\0';
			gotoxy(34+x,17+y); scanf("%s",s.backupPassword); fflush(stdin);  //�����ڵ� �Է� 
			if(strlen(s.backupPassword)<4 || stringLengthcheck(s.backupPassword,13)){}  //���ڿ��� ���� üũ
			else if(numberErrorcheck(s.backupPassword)){}  //�����̿��� �� üũ			
			else{  //���� ������		  
				gotoxy(28+x,21+y); printf("                  ");  //�����޽��� ����Ŭ����
				break;  
			}
			gotoxy(28+x,21+y);  printf("�����ڵ� �Է� ����");
			gotoxy(34+x,17+y);  printf("                  ");  //�����ڵ��Է¶��� Ŭ����			
		}

		gotoxy(19+x,20+y); printf("��� �Է��� �������ϱ�? (Y/N) ");
		scanf("%c",&ask); fflush(stdin);

		//---------------------------ȸ������ txt�� ����-----------------------------------------------

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
				gotoxy(60, 29); printf("ȸ�� ���� �Ϸ�!!!    ");
				getch();
			}
			else{  //������ ���� ���
				gotoxy(60, 29); printf("�̹� ȸ�������ϼ̽��ϴ�.");
				getch();
				return;
			}
		}			
	}
}




