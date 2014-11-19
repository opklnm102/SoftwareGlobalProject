#include"structHeader.h"

//약속장소 고르기 함수
void promisePlace(){
	FILE *fp1;
	structPromise sp;  //구조체 넘겨줄꺼면 지워야함
	char place[20],DBplace[30];
	int placeSelect;  //장소선택
	int placeCount;  //소분류의 수
	char **subcategory;  //소분류 저장공간
	int i,len;
	
	fp1=fopen("place.txt","r");  //장소리스트DB 열고

	if(fp1 == NULL){
		printf("can not file open\n");
		return;
	}

	printf("약속장소\n");
	printf("--장소리스트--\n");

	//장소리스트 대분류
	printf("1. 학습관련시설\n");
	printf("2. 휴게시설\n");
	printf("3. 기타시설\n");
	printf("4. 건강,문화시설\n");
	printf("대분류 선택>> "); scanf("%d",&placeSelect); fflush(stdin);

	switch(placeSelect){  //장소리스트 대분류 선택
	case 1 :
		strcpy(place,"학습관련시설");		
		break;
	case 2 :
		strcpy(place,"휴게시설");		
		break;
	case 3 :
		strcpy(place,"기타시설");		
		break;
	case 4 :
		strcpy(place,"건강,문화시설");		
		break;
	}

	len=strlen(place);
	place[len++]=10;
	place[len]='\0';	

	while(!feof(fp1)){  //파일끝까지 확인
		fgets(DBplace,30,fp1); 
		//fseek(fp1,3,SEEK_CUR);
		if(!strcmp(DBplace,place)){  //대분류를 찾고
			fscanf(fp1,"%d",&placeCount);  //대분류에 속해 있는 소분류의 개수입력
			break;
		}
		for(i=0;i<30;i++) DBplace[i]=-52;
	}

	subcategory = (char **)malloc(sizeof(char*) *placeCount);  //소분류만큼 동적할당
	for(i=0; i<placeCount; i++){
		subcategory[i] = (char *)malloc(sizeof(char)*30);
		fgets(subcategory[i],30,fp1);  //소분류의 내용들 저장
	}

	for(i=0; i<placeCount; i++)  //소분류 출력
		printf("%d. %s",i+1,subcategory[i]);

	printf("소분류 선택>>"); scanf("%d",&placeSelect); fflush(stdin);

	strcpy(sp.promisePlace,subcategory[placeSelect]);  //구조체에 저장

	printf("%s",sp.promisePlace);  //어떤게 저장되었나 확인->지워도 됨

	for(i=0; i<placeCount; i++)
		free(subcategory[i]);
	free(subcategory);

	fclose(fp1);	
}





