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
	char promiseName[41];
	char openDB[30];
	char check[41];
	int listCount=0;
	int x=10, y=9;
	int i;

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
			fscanf(fp, "%s", &check);
			if(!strcmp(check,"��Ӹ���Ʈ")){
				fscanf(fp,"%d", &listCount);
				for(i=0; i<listCount; i++){
					fscanf(fp,"%s", promiseName);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fgets(check,41,fp);
					fscanf(fp,"%s", check);
					fgets(check,41,fp);			//���� �ڸ� �߰�.
					fgets(check,41,fp);
					gotoxy(x,y);printf("%d. %-12s",i+1,promiseName);  //����̸�,��¥���
					y=y+3;  //�ٹٲ�
				}
			}
		}
		fclose(fp);
	}
}




