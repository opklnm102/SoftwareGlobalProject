#include"structHeader.h"

void selectChange(struct structPromise *old, int listnumber, char **name){
	int i;
	char select[3];

	system("cls");
	printf("약속수정\n");
	printf("1. 약속명   : %s\n",old[listnumber].promiseName);
	printf("2. 약속장소 : %s\n",old[listnumber].promisePlace);
	printf("3. 약속날짜 : %s\n",old[listnumber].Promisedate);
	printf("4. 약속시간 : %s\n",old[listnumber].promiseTime);
	printf("5. 함께할 친구 : ");
	for(i=0; i<4; i++)
		printf("%s ",name[i]);
	printf("\n");
	printf("수정할 내용을 선택하세요.\n");
	scanf("%s",&select);

	/*여기서부터 이제 선택한 번호에 따라 직접 수정에 들어가야함...오랜시간이 걸릴듯해서 아직 손못댐...
	어떤식으로 짜야할지 생각해보면..
	약속명 같은경우 그냥 이자리에서 수정하게 하고
	장소부터는 함수를 이동시켜야하는데 ... 그럴경우 기존 정보들은 어떻게 유지한채로 그리로 넘어갈지 이해불가...
	저번에 이야기한걸 기억해보면 해당 정보에 맞는 함수를 불르면 된다고 했었는데..
	예를들어 지금   조별과제
					학생식당(창의관 지하1층)
					4시
					11/3
					1092011,2344010,3434324
					이런 약속리스트 정보에서 장소를 수정한다고 가정하면
					promisePlace 함수로 이동하게 되는데 void promisePlace(char *DBname,struct structPromise *newPromise) 이것이 현재 함수형태...
					이런경우 약속이름, 시간, 날짜, 학번 정보가 들어간 현재 old라는 약속구조체를 넘겨버리면 새로운 약속을 만들어버리는게 되어버림...
					기존약속과 중복처리는 없으므로...덮어씌워지는게 아니라 새로운 약속리스트로 추가됨... 그럴경우 수정이 끝난후
					다시 약속리스트를 읽어 수정되기전 약속을 찾아내서 그걸 지우고 나머지 약속들을 떙겨서 써줘야하는 상황...
					그걸 약속을 공유하는 모든 회원들의 약속리스트에 반복해야함...
					함수들이 지금 따로따로 분리가 완벽하게 되있지 않고 서로 연결하듯이 되어있어서 날짜같은것을 고치려면 어떻게 해야할지 감도 안잡히는 상태
					
					함수들을 싹 정리해서 이쪽으로 나갈지 아니면 새로 함수를 짜는게 빠를지 고민중..

	새로 함수를 짠다고 쳐도 애초 계획대로 화면 이동이 되는 형식으로 사용자가 약속정보를 쉽게 바꾼다는 조건을 만족시키려면 
	기존에 있던 함수들과 똑같은 인터페이스로 화면 출력이 되야하기때문에 거의 복사하듯이 하나를 만들어야함.. 이쪽도 난항이 예상됨...
	예상을 해보면
					약속명은 따로 출력할 정보가 필요없으므로 여기서 고칠수 있음.
					장소는 장소분류를 출력하는 함수가 필요 거기서 선택을 받고 바로 여기로 되돌아와야함.
					날짜는 바꿀경우 시간을 다시 설정해줘야 하는경우가 생기므로 달력만 출력하고 날짜만 따로 입력받는 경우는 있을수 없음..
					통합시간표도 출력하고 시간도 재입력 받게 만들어야함.. 그리고 시간까지 입력받으면 여기로 바로 되돌아와야함
					시간은 바꿀경우 통합시간표만 출력해주고 다시 선택받게만 하고 이 창으로 돌아와야함
					함께할 친구.......
					회원수를 입력받고 다시 이름 검색 함수를 불러서 이름을 선택받고 선택받은 회원의 학번정보를 읽어와 이창으로 돌아와야함.. 그런뒤 학번을 이름으로 변경해서 바뀐이름을 출력해주고
					바뀐 회원들과 기존에 겹치는 회원이 있는지 체크하고 겹치는 회원이 없으면 기존회원들의 약속리스트에서 해당 약속을 전부 삭제... 바뀐회원들의 약속리스트에는 약속추가...

	일단 기존 함수들을 정리하는 방향으로 나갈계획인데 누군가 더 좋은 방법이 있으면 꼭 알려주길...
	*/
}

void promiseChange(char *DBname){
	FILE *fp;
	char openDB[30];
	char textFile[]=".txt";
	char check[41];
	struct structPromise *oldPromise;
	int listCount=0;
	int i,j,k;
	int numbering=1;
	char **friendsName;
	char **cost;
	char select[3]={0};
	int listnumber=0;
	int length;
	char **transName;
	char ID[8];
	char listName[13];
	char blank[1]={0};

	strcpy(openDB,DBname);
	strcat(openDB,"PromiseList");
	strcat(openDB,textFile);
	fp = fopen(openDB, "r");
	if ( fp == NULL ) {
		printf("현재 생성된 약속리스트가 없습니다.");
		return ;
	}
	while (!feof(fp)) {			//약속리스트 열어서 리스트에 적혀진 개수만큼 이름과 날짜를 읽어서 출력하는 부분
		printf("나의 약속리스트\n");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"약속리스트")){
			fscanf(fp,"%d", &listCount);

			oldPromise=(struct structPromise*)malloc(sizeof(struct structPromise)*listCount);		//읽어온 약속을 저장하기위한 약속구조체
			for(i=0; i<listCount; i++) {															//약속저장을 할때와는 달리 이번에는 학번도 하나씩 다 읽어서 현재 이 약속을 공유하는 회원파일을 각각 처리해야함으로 
				oldPromise[i].promiseFriendsName=(char**)malloc(sizeof(char*)*4+1);					//동적할당을 promiseFriendsName에도 해준다. 
					for(j=0; j<4; j++) {													
						oldPromise[i].promiseFriendsName[j]=(char*)malloc(sizeof(char)*8);
						strcpy(oldPromise[i].promiseFriendsName[j],"\0");
						for(k=0; k<8; k++)
							strcpy(&oldPromise[i].promiseFriendsName[j][k],"\0");
					}
			}


			friendsName=(char**)malloc(sizeof(char*)*listCount);									//일단 학번이 한줄단위로 줄줄이 써있으니 그것을 읽어오는 문자열을 하나 동적할당한다.
			for(i=0; i<listCount; i++) {
				friendsName[i]=(char*)malloc(sizeof(char)*60);
				strcpy(friendsName[i],"\0");
					for(j=0; j<60; j++)
						strcpy(&friendsName[i][j],"\0");
			}

			cost=(char**)malloc(sizeof(char*)*listCount);						//비용은 약속수정에서 안쓰이는 정보이므로 그냥 읽어주기만 한다.. 필요없음
			for(i=0; i<listCount; i++) {													
				cost[i]=(char*)malloc(sizeof(char)*10);
				strcpy(cost[i],"\0");
					for(j=0; j<10; j++)
						strcpy(&cost[i][j],"\0");
			}

			for(i=0; i<listCount; i++) {								//일단 약속리스트개수만큼 약속을 읽어와서 oldPromise구조체에 순서대로 저장
				fscanf(fp,"%s",&oldPromise[i].promiseName);
				fflush(stdin);
				fgets(check,40,fp);						
				fgets(check,40,fp);					
				strcpy(oldPromise[i].promisePlace,check);						
				fscanf(fp,"%s",&oldPromise[i].promiseTime);
				fscanf(fp,"%s",&oldPromise[i].Promisedate);
				fscanf(fp,"%s",&check);
				strcpy(friendsName[i],check);
				fgets(check,40,fp);
				fgets(check,40,fp);
				strcpy(cost[i],check);
				printf("%d %s ",numbering,oldPromise[i].promiseName);
				printf("/ %s\n",oldPromise[i].Promisedate);
				numbering++;
			}
		}
	}
	fclose(fp);
	printf("→ 수정하실 약속 : ");
	while(1) {						//리스트 번호 범위 내의 수만 입력받기
		scanf("%s",select);
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<=numbering)
			break;
		printf("리스트 내의 번호를 입력하세요 : ");
	}
	listnumber--;

	length=strlen(friendsName[listnumber]);			//줄단위로 읽은 학번들을 7자씩 끊어서 미리 할당해놓은 promiseFriendsName에 하나씩 넣어주는 부분
	for(i=0; i<4; i++) {							//여기서도 굳이 회원수를 체크하려면 귀찮으니 4번 반복실행하도록 만듬, 자신포함 최대 5명이므로 저장되는 다른 회원정보는 4명
		strncpy(oldPromise[listnumber].promiseFriendsName[i],friendsName[listnumber],7);
		for(j=0; j<7; j++)
			changeLocation(friendsName[listnumber]);
		if(strncmp(friendsName[listnumber],",",1)==0)
			changeLocation(friendsName[listnumber]);
		else
			break;		
	}
	
	transName=(char**)malloc(sizeof(char*)*4+1);					//학번을 그냥 쓸수 없으니 이름으로 바꿀 문자배열을 또 동적할당 해준다.
	for(i=0; i<4; i++) {													
		transName[i]=(char*)malloc(sizeof(char)*13);
		strcpy(transName[i],"\0");
		for(j=0; j<13; j++)
			strcpy(&transName[i][j],"\0");
	}

	strcpy(openDB,"회원목록.txt");						//학번을 이름으로 바꿔준다. 회원목록 txt를 5번동안 열고 닫고 하며 반복... 회원 숫자를 계산하기 귀찮으므로 그냥 5번 반복
	for(i=0;i<4;i++){
		fp = fopen(openDB, "r");
		while (!feof(fp)) {		
			fscanf(fp, "%s %s", &ID, &listName);										//학번과 이름을 한줄 읽는다.
			if(!strcmp(ID,oldPromise[listnumber].promiseFriendsName[i])){				//검색할 학번과 같은 학번이면
				strcpy(transName[i],listName);											//transName 문자배열에 현재 읽은 이름을 복사
				break;
			}
		}
		fclose(fp);
	}
	
	oldPromise[listnumber].promisePlace[strlen(oldPromise[listnumber].promisePlace)-1]=blank[0];           //장소DB에서 읽어올때 \n 하나 들어있는거 없애서 자동줄바꿈 방지
	printf("\n");
	printf("약속명      장소        날짜      시간      함께할친구\n");
	printf("%s    %s     %s     %s\n",oldPromise[listnumber].promiseName,oldPromise[listnumber].promisePlace,oldPromise[listnumber].promiseTime,oldPromise[listnumber].Promisedate);
	for(i=0; i<4; i++)
		printf("%s ",transName[i]);
	printf("\n");
	printf("수정하시겠습니까? <Y,N>");
	scanf("%s",&select);
	
	if(!strcmp(select,"y"))									//y나 Y일때 수정 단계로 넘어감
		selectChange(oldPromise,listnumber,transName);		//selectChange 함수사용, (현재읽어온 약속리스트정보구조체, 사용자가 선택한 약속리스트번호, 함께하는 회원 이름)을 인수로 넘겨준다.
	else if(!strcmp(select,"Y"))
		selectChange(oldPromise,listnumber,transName);

	for(i=0;i<listCount; i++)			//동적할당 해제
		free(friendsName[i]);				
	free(friendsName);

	for(i=0; i<4; i++)			
		free(transName[i]);				
	free(transName);

	for(i=0;i<listCount; i++){
		for(j=0; j<4; j++)
			free(oldPromise[i].promiseFriendsName[j]);				
		free(oldPromise[i].promiseFriendsName);
	}
		
	for(i=0;i<listCount; i++)			
		free(cost[i]);				
	free(cost);
	free(oldPromise);
	
	
}