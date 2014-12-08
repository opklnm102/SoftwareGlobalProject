#include"structHeader.h"

void login(structMember *s){
	char id[8]="\0",password[20]="\0";  //fid,fname ���Ͽ��� �ҷ��� �й�,�̸�
	FILE *fp1,*fp2=NULL;	
	char fileName[20]="\0";  //������ �����̸�
	int loginCount;  //�α��� Ƚ��	
	char ch;
	int backspace=0,i=0,j;

	//----------------------------UI�׸���-----------------------------------------------
	screenBorderDraw();  //��üƲ���
	listBorderDraw(40,13);  //�޴�Ʋ���
	gotoxy(60,10); printf("*Togedule*");
	gotoxy(63,18);   printf("-Login-");
	//�α��� ���� �Է�
	gotoxy(54, 21); printf("��     �� : "); 
	gotoxy(54, 23); printf("P       W : "); 

	while(1){
		gotoxy(66, 21); scanf("%s",id); fflush(stdin);  //�й��Է�
		if(stringLengthcheck(id,7)){}  //���ڿ��� ���� üũ
		else if(numberErrorcheck(id)){}  //�����̿��� �� üũ			
		else{		
			gotoxy(60, 27); printf("              "); break;
		}
		gotoxy(60, 27); printf("�й� �Է� ����");
		gotoxy(66, 21); printf("              ");
	}

	gotoxy(66, 23);  //��й�ȣ�Է�
	for(i=0; i<20; i++){  //��й�ȣ �Է½� ***�� ��ºκ�
		ch=getch();		
		if(ch == 13){  //enterŰ(��й�ȣ�Է³��κ�) Ȯ��
			if(i<4 || i>13){  //���� ����
				i=-1;
				for(j=0; j<20; j++)
					password[j]='\0';
				gotoxy(60, 27); printf("�н����� �Է� ����");
				gotoxy(66, 23); printf("                "); 
				gotoxy(66, 23);
			}
			else if(numberErrorcheck(password)){
				i=-1;
				for(j=0; j<20; j++)
					password[j]='\0';
				gotoxy(60, 27); printf("�н����� �Է� ����");
				gotoxy(66, 23); printf("                  "); 
				gotoxy(66, 23);
			}
			else{
				password[i] = '\0';
				gotoxy(60, 27); printf("                ");
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
			password[i] = ch;
			printf("*");
			fflush(stdin);
		}
	}		

	//ȸ�����Կ��� Ȯ��	
	fp1=fopen("ȸ�����.txt","r");  //ȸ����� ����

	while(!feof(fp1)){  //���ϳ����� Ȯ��
		fscanf(fp1,"%s %s",s->ID,s->name);  
		if(!strcmp(id,s->ID)){  //��Ͽ��� �ش�id�� ã���� ��� ������ ���� ������

			getUserfileName(fileName,s,"\0");  //open�� �����̸����			
			fp2=fopen(fileName,"r");  //ȸ�����ԵǾ��ִ�.
			fclose(fp1);  //ȸ��������� �ݰ�
			fp1=NULL;
			break;  
		}
	}
	if(fp2 == NULL){  //���κ� ȸ������������ �������� ���(ȸ�����ԾȵǾ��������)
		gotoxy(60, 27); printf("ȸ�������ϼ���....        ");
		getch();
		return;
	}
	//ȸ�������Է�
	fseek(fp2,10,SEEK_CUR);  //������ ù "ȸ������"������ Ŀ�� �̵�
	fscanf(fp2,"%s %s %s %s",s->ID,s->name,s->password,s->backupPassword);  //���κ� ȸ�������Է�

	fclose(fp2);
	fp2=NULL;

	loginCount=0;
	while(loginCount<4){  //�α��� Ƚ�� 5�� ���� ��� �����ڵ�� �ʱ�ȭ
		if(strcmp(password,s->password)==0){ //�α���	
			gotoxy(60, 27); printf("ȯ���մϴ�!!!          ",loginCount); 
			getch();
			mainMenu(s);
		}
		else{  //�α��� ����
			loginCount++;
			gotoxy(60, 27); printf("�α��� %dȸ ����     ",loginCount); 
			gotoxy(54, 23); printf("P       W : ");
			gotoxy(66, 23); printf("                         ");  //���õ��� *�� ���������

			gotoxy(66, 23);  //��й�ȣ �Է� 		
			for(i=0; i<20; i++){  //��й�ȣ �Է½� ***�� ��ºκ�
				ch=getch();		
				if(ch == 13){  //enterŰ(��й�ȣ�Է³��κ�) Ȯ��
					if(i<4 || i>13){  //���� ����
						i=-1;
						for(j=0; j<20; j++)
							password[j]='\0';
						gotoxy(60, 27); printf("�н����� �Է� ����");
						gotoxy(66, 23); printf("                "); 
						gotoxy(66, 23);
					}
					else if(numberErrorcheck(password)){
						i=-1;
						for(j=0; j<20; j++)
							password[j]='\0';
						gotoxy(60, 27); printf("�н����� �Է� ����");
						gotoxy(66, 23); printf("                  "); 
						gotoxy(66, 23);
					}
					else{
						password[i] = '\0';
						gotoxy(60, 27); printf("                ");
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
					password[i] = ch;
					printf("*");
					fflush(stdin);
				}
			}
		}
	}

	//PW�� �����ڵ�� ����->����->���Ͽ� ��½� �ΰ��� ��¾ȵǰ�.. �����ٶ�
	gotoxy(58, 27); printf("PW �����ڵ�� �ʱ�ȭ");
	fp2=fopen(fileName,"w");
	fprintf(fp2,"%s\n","ȸ������");
	fprintf(fp2,"%s\n%s\n%s\n%s\n",s->ID,s->name,s->backupPassword,s->backupPassword);  //���κ� ȸ���������� ����
	fclose(fp2);	
	getch();
}
