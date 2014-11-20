#include"structHeader.h"

//약속장소 고르기 함수
void promisePlace(char *DBname,struct structPromise *newPromise){
	FILE *fp1;
	FILE *fp;
	int promiseCount=0;
	char promisecount[5];
	char openDB[40];
	char check[40];
	char place[20],DBplace[30];
	int placeSelect;  //장소선택
	int placeCount;  //소분류의 수
	char **subcategory;  //소분류 저장공간
	int i,j,len;
	char **oldPromisePlace;
	char **friendsName;		//친구이름 저장공간 구조체멤버 friendsName을 안쓰는 이유는 굳이 그럴필요없이 그냥 한줄통째로 읽어서 임시로 저장만 하는 공간이 필요하므로...
	struct structPromise *oldPromise;		//기존 약속리스트정보를 저장할 구조체


	fp1=fopen("place.txt","r");  //장소리스트DB 열고

	if(fp1 == NULL){
		printf("can not file open\n");
		return;
	}

	while(1){
		printf("약속장소\n");
		printf("--장소리스트--\n");

		//장소리스트 대분류
		printf("1. 학습관련시설\n");
		printf("2. 휴게시설\n");
		printf("3. 기타시설\n");
		printf("4. 건강,문화시설\n");
		printf("대분류 선택>> "); scanf("%d",&placeSelect); fflush(stdin);
		if(1 <= placeSelect && placeSelect <= 4) break;
		printf("리스트에 있는 것중에 고르시오\n");
		getch();
		system("cls");
	}

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

		if(!strcmp(DBplace,place)){  //대분류를 찾고
			fscanf(fp1,"%d",&placeCount);  //대분류에 속해 있는 소분류의 개수입력
			fseek(fp1,2,SEEK_CUR);
			break;
		}
		for(i=0;i<30;i++) DBplace[i]=-52;
	}

	subcategory = (char **)malloc(sizeof(char*) *placeCount);  //소분류만큼 동적할당
	for(i=0; i<placeCount; i++){
		subcategory[i] = (char *)malloc(sizeof(char)*30);
		fgets(subcategory[i],30,fp1);  //소분류의 내용들 저장
	}

	while(1){
		system("cls");
		for(i=0; i<placeCount; i++)  //소분류 출력
			printf("%d. %s",i+1,subcategory[i]);

		printf("소분류 선택>>"); scanf("%d",&placeSelect); fflush(stdin);

		if(1 <= placeSelect && placeSelect <= placeCount-1) break;
		printf("리스트에 있는 것중에 고르시오\n");
		getch();
	}
	strcpy(newPromise->promisePlace,subcategory[placeSelect]);  //구조체에 저장
	printf("%s",newPromise->promisePlace);
	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList.txt");				//학번+이름+PromiseList.txt 가 각 회원의 약속리스트파일
	fp=fopen(openDB,"r");							//읽기버전으로 우선 연다.

	if(!fp) {										//약속리스트가 없으면 
		fp=fopen(openDB,"w");						//쓰기버전으로 열어서 새로 약속리스트를 만든다.
		fprintf(fp,"약속리스트\n");
		fprintf(fp,"1\n");
		fprintf(fp,newPromise->promiseName);
		fprintf(fp,"\n");
		fprintf(fp,newPromise->promisePlace);						//이게 들어가야함 장소는 아직 없으므로 빼놓고 '임시장소'를 파일에 출력하게함
		fprintf(fp,newPromise->promiseTime);
		fprintf(fp,"\n");
		fprintf(fp,newPromise->Promisedate);
		fprintf(fp,"\n");
		promiseCount=atoi(newPromise->promiseFreindsCount);			//serchName함수에서 저장한 이름검색이 된 회원의 학번을 하나씩 삽입.  
		for(i=0; i<promiseCount; i++) {
			if(strcmp(newPromise->promiseFriendsName[i],"\0")){
				fprintf(fp,newPromise->promiseFriendsName[i]);				
			}
			if(i!=promiseCount-1)
				fprintf(fp,",");									//","도 찍어준다.띄어쓰기 없이 쉼표로 구분
		}
		fclose(fp);
		
	}		
	else{												//약속리스트가 있으면
		while (!feof(fp)) {	

			fscanf(fp, "%s", &check);					//첫줄을 읽어 혹시나 약속리스트가 아닌경우를 대비
				if(!strcmp(check,"약속리스트")){ 

					fscanf(fp,"%d", &promiseCount);		//둘째줄을 읽어 promiseCount에 저장. 약속리스트의 개수를 의미.
					oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*promiseCount);
					friendsName=(char**)malloc(sizeof(char*)*promiseCount);						//동적할당 오류 해결. char뒤에 포인터 표시 빼먹음....
					for(i=0; i<promiseCount; i++) {
						friendsName[i]=(char*)malloc(sizeof(char)*60);
						strcpy(friendsName[i],"\0");
						for(j=0; j<60; j++)
							strcpy(&friendsName[i][j],"\0");
					}
					oldPromisePlace=(char**)malloc(sizeof(char*)*promiseCount);						//동적할당 오류 해결. char뒤에 포인터 표시 빼먹음....
					for(i=0; i<promiseCount; i++) {
						oldPromisePlace[i]=(char*)malloc(sizeof(char)*60);
						strcpy(oldPromisePlace[i],"\0");
						for(j=0; j<60; j++)
							strcpy(&oldPromisePlace[i][j],"\0");
					}
					for(i=0; i<promiseCount; i++) {								//일단 약속리스트개수만큼 약속을 읽어와서 oldPromise구조체에 순서대로 저장
						fscanf(fp,"%s",&oldPromise[i].promiseName);
						fflush(stdin);
						fgets(check,40,fp);
						fgets(check,40,fp);
						strcpy(oldPromisePlace[i],check);
						
						fscanf(fp,"%s",&oldPromise[i].promiseTime);
						fscanf(fp,"%s",&oldPromise[i].Promisedate);
						fscanf(fp,"%s",&check);
						strcpy(friendsName[i],check);
					}
				}
		}
		fclose(fp);
		fp=fopen(openDB,"w");												//w버전으로 약속리스트를 다시 열어 기존 파일을 날리고 새로 작성한다.
		fprintf(fp,"약속리스트\n");
		itoa(promiseCount+1,promisecount,10);
		fprintf(fp,"%s\n",promisecount);
		for(i=0; i<promiseCount; i++) {			
			fprintf(fp,"%s\n",oldPromise[i].promiseName);
			fprintf(fp,"%s",oldPromisePlace[i]);
			fprintf(fp,"%s\n",oldPromise[i].promiseTime);
			fprintf(fp,"%s\n",oldPromise[i].Promisedate);
			fprintf(fp,"%s\n",friendsName[i]);
		}
		fprintf(fp,"%s\n",newPromise->promiseName);
		fprintf(fp,"%s",newPromise->promisePlace);				//위와 동일하게 가 들어갈 자리. 아직 장소가 없으므로 '임시장소'로 출력
		fprintf(fp,"%s시\n",newPromise->promiseTime);
		fprintf(fp,"%s\n",newPromise->Promisedate);
		promiseCount=atoi(newPromise->promiseFreindsCount);
		for(i=0; i<promiseCount; i++) {		
			if(strcmp(newPromise->promiseFriendsName[i],"\0")){
				fprintf(fp,"%s",newPromise->promiseFriendsName[i]);				
				}
			if(i!=promiseCount-1)
				fprintf(fp,",");
		}
		fclose(fp);	
		for(i=0;i<promiseCount; i++)			//동적할당 해제
			free(friendsName[i]);				
		free(friendsName);
		for(i=0;i<promiseCount; i++)			//동적할당 해제
			free(oldPromisePlace[i]);				
		free(oldPromisePlace);
		free(oldPromise);
	}


	for(i=0; i<placeCount; i++)
		free(subcategory[i]);
	free(subcategory);

	fclose(fp1);	
}