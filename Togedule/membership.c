#include"structHeader.h"

void membership(){
	int x=32, y=7;
	structMember s;  //��� ����ü	
	char txt[]=".txt";  //Ȯ����
	char ask;  //���� ����
	FILE *fp1,*fp2;	
	char fileName[30];
	int con=1;

	//----------------------------UI�׸���-----------------------------------------------
	screenBorderDraw();  //��üƲ���
	listBorderDraw(40,13);  //�޴�Ʋ���

	gotoxy(60,10); printf("-ȸ������-\n");

	while(con){
		gotoxy(22+x,11+y); printf("��    �� : "); 
		gotoxy(22+x,13+y); printf("P      W : "); 
	    gotoxy(22+x,15+y); printf("��    �� : "); 
	    gotoxy(22+x,17+y); printf("�����ڵ� : ");

		gotoxy(34+x,11+y); scanf("%s",s.ID);  fflush(stdin);
		gotoxy(34+x,13+y); scanf("%s",s.password);  fflush(stdin);
		gotoxy(34+x,15+y); scanf("%s",s.name);  fflush(stdin);
		gotoxy(34+x,17+y); scanf("%s",s.backupPassword);  fflush(stdin);

		gotoxy(19+x,20+y); printf("��� �Է��� �������ϱ�? (Y/N) ");
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
				gotoxy(60, 29); printf("ȸ�� ���� �Ϸ�!!!");
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




