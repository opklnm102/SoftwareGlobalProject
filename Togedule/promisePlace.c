#include"structHeader.h"

//������ ���� �Լ�
void promisePlace(){
	FILE *fp1;
	structPromise sp;  //����ü �Ѱ��ٲ��� ��������
	char place[20],DBplace[30];
	int placeSelect;  //��Ҽ���
	int placeCount;  //�Һз��� ��
	char **subcategory;  //�Һз� �������
	int i,len;
	
	fp1=fopen("place.txt","r");  //��Ҹ���ƮDB ����

	if(fp1 == NULL){
		printf("can not file open\n");
		return;
	}

	printf("������\n");
	printf("--��Ҹ���Ʈ--\n");

	//��Ҹ���Ʈ ��з�
	printf("1. �н����ýü�\n");
	printf("2. �ްԽü�\n");
	printf("3. ��Ÿ�ü�\n");
	printf("4. �ǰ�,��ȭ�ü�\n");
	printf("��з� ����>> "); scanf("%d",&placeSelect); fflush(stdin);

	switch(placeSelect){  //��Ҹ���Ʈ ��з� ����
	case 1 :
		strcpy(place,"�н����ýü�");		
		break;
	case 2 :
		strcpy(place,"�ްԽü�");		
		break;
	case 3 :
		strcpy(place,"��Ÿ�ü�");		
		break;
	case 4 :
		strcpy(place,"�ǰ�,��ȭ�ü�");		
		break;
	}

	len=strlen(place);
	place[len++]=10;
	place[len]='\0';	

	while(!feof(fp1)){  //���ϳ����� Ȯ��
		fgets(DBplace,30,fp1); 
		//fseek(fp1,3,SEEK_CUR);
		if(!strcmp(DBplace,place)){  //��з��� ã��
			fscanf(fp1,"%d",&placeCount);  //��з��� ���� �ִ� �Һз��� �����Է�
			break;
		}
		for(i=0;i<30;i++) DBplace[i]=-52;
	}

	subcategory = (char **)malloc(sizeof(char*) *placeCount);  //�Һз���ŭ �����Ҵ�
	for(i=0; i<placeCount; i++){
		subcategory[i] = (char *)malloc(sizeof(char)*30);
		fgets(subcategory[i],30,fp1);  //�Һз��� ����� ����
	}

	for(i=0; i<placeCount; i++)  //�Һз� ���
		printf("%d. %s",i+1,subcategory[i]);

	printf("�Һз� ����>>"); scanf("%d",&placeSelect); fflush(stdin);

	strcpy(sp.promisePlace,subcategory[placeSelect]);  //����ü�� ����

	printf("%s",sp.promisePlace);  //��� ����Ǿ��� Ȯ��->������ ��

	for(i=0; i<placeCount; i++)
		free(subcategory[i]);
	free(subcategory);

	fclose(fp1);	
}





