#include"structHeader.h"

void mystatus(structMember *s){
	char DBname[20];  //���ϸ�

	strcpy(DBname,s->ID);
	strcat(DBname,s->name);	


	screenBorderDraw() ;  //ȭ��׸���
	promiselistBorderDraw(3,7);  //��Ӹ���Ʈ Ʋ

	gotoxy(20,5);
	printf("--���� ��Ӹ���Ʈ--");
	gotoxy(85,5);
	printf("--����ð�ǥ--");
	timetableDraw(s);  //�ð�ǥ ���
	mystatus_promiseList(DBname);  //��Ӹ���Ʈ ���

	getch();
}

void promiselistBorderDraw(int x, int y){  
	int i;   

	gotoxy(x,y);
	printf("������������������������������������������������������");

	for(i=0; i<27; i++){ 
		gotoxy(x,y+1+i);
		printf("��                                                  ��");
	}

	gotoxy(x,y+28);
	printf("������������������������������������������������������");
}

void mystatus_promiseList(char *DBname){
	FILE *fp;
	char textFile[]=".txt";
	char openDB[30];
	char check[41];
	int listCount=0;
	int x=5, y=9;
	int i;
	int numbering=1;
	char controlList[3]={0};
	structPromise *Promise;  //��Ӹ���Ʈ�� ���� ����ü

	strcpy(openDB,DBname);  //��Ӹ���Ʈ ���� open
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		gotoxy(13,20);
		printf("���� ������ ��Ӹ���Ʈ�� �����ϴ�.");
	}
	else{
		while (!feof(fp)) {	
			gotoxy(x+11,y+1); printf("��Ӹ�      ");
			fscanf(fp, "%s", &check);  //��Ӹ���Ʈ���� check
			if(!strcmp(check,"��Ӹ���Ʈ")){
				fscanf(fp,"%d", &listCount);  //����Ʈ�� ���� �б�
				Promise=(structPromise*)malloc(sizeof(structPromise)*listCount);  //����Ʈ ����ŭ �Ҵ�

				for(i=0; i<listCount; i++){  //��Ӹ� �б�
					fscanf(fp,"%s", Promise[i].promiseName);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fscanf(fp,"%s", check);
					fgets(check,41,fp);			//���� �ڸ� �߰�.
					fgets(check,41,fp);
				}
			}
		}

		for(i=0; i<listCount; i++) {	
				if(i==10){
						gotoxy(8,36); printf("��������Ʈ�� ������ >Ű�� �Է��ϼ���.");
						while(1){
							gotoxy(46,36);scanf("%s",&controlList);
							if(!strcmp(controlList,">"))
								break;
							gotoxy(46,36);printf("     ");
						}
						if(!strcmp(controlList,">")){
							promiselistBorderDraw(3,7);  //��Ӹ���Ʈ Ʋ
							gotoxy(x+11,y+1); printf("��Ӹ�      ");
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(8,36);printf("                                               ");						

					}
					else if(i!=0&&i!=5&&i%10==0&&i+1!=listCount){
						gotoxy(8,36);printf("��������Ʈ <, ��������Ʈ >");
						while(1){
							gotoxy(46,36);scanf("%s",&controlList);
							if(!strcmp(controlList,"<")||!strcmp(controlList,">"))
								break;
							
							gotoxy(46,36);printf("     ");
						}
						if(!strcmp(controlList,">")){
							promiselistBorderDraw(3,7);  //��Ӹ���Ʈ Ʋ
							gotoxy(x+11,y+1); printf("��Ӹ�      ");
							strcpy(controlList,"\0");
						}
						else if(!strcmp(controlList,"<")){
							promiselistBorderDraw(3,7);  //��Ӹ���Ʈ Ʋ
						gotoxy(x+11,y+1); printf("��Ӹ�      ");
							i=i-20;
							numbering=numbering-10;
							strcpy(controlList,"\0");
						}
						else
							scanf("%s",&controlList);
						gotoxy(8,36);printf("                                               ");
					}
					
					gotoxy(x+5,y+3+2*(i%10));printf("%2d     %-20s ",numbering,Promise[i].promiseName);
					numbering++;
					if(i+1==listCount&&listCount>5){
						gotoxy(8,36);printf("ó������ ���ư����� <Ű�� �Է��ϼ���.");
						while(1){
							gotoxy(46,36);scanf("%s",&controlList);
							if(!strcmp(controlList,"<"))
								break;
							gotoxy(46,36);printf("     ");
						}						
						if(!strcmp(controlList,"<")){
							promiselistBorderDraw(3,7);  //��Ӹ���Ʈ Ʋ(35,11);	
							gotoxy(x+11,y+1); printf("��Ӹ�      ");
							i=-1;
							numbering=1;
							strcpy(controlList,"\0");
						}
						
						gotoxy(8,36);printf("                                               ");
					}
				}






		fclose(fp);
	}
}




