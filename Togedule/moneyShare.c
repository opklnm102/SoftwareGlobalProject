#include "structHeader.h"

void moneyShare1(structMember *s){	
	FILE *fp;
	char fileName[30];
	char textFile[]=".txt";
	char check[41];
	struct structPromise *oldPromise;
	int listCount=0;
	int i,j,k,l=0;
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
	int CombineTimetable[5][13]={0};
	char friendNameCopy[8]={0};	
	char checkPlace[3]={0};
	int x=35,y=11;
	int peopleCnt=1;
	char controlList[3]={0};
	int beforeDivideMoney; // 나누기 전 돈
	int finalMoney; // 최종 돈
	int divisionNumber; // 나누는 수
	int arrMoney[5]={0, };
	int baseMoney;
	int restPeople;
	int restMoney;
	int menuseletion; //메뉴 선택하는 변수
	int randomPersonNumber; //랜덤으로 받은 시드값을 저장하는 변수 1,2,3,4,5 중 하나
	char waiting[20] = {'w','a','i','t',' ','p','l','e','a','s','e','.','.'};
	char buffer[70];
	int promiselistCount;
	int friendCount;
	structPromise *pl;

	screenBorderDraw();  //전체틀 그리기	
	gotoxy(56,6); printf("☆ 비용 ☆");
	gotoxy(54,8); printf("- 나의 약속리스트 -");
	listBorderDraw2(x,y);  //리스트메뉴틀 그리기

	//열기할 파일 이름 만들기
	getUserfileName(fileName,s,"PromiseList");

	fp = fopen(fileName, "r");  //내 약속리스트 파일 열기
	if ( fp == NULL ) {
		gotoxy(x+12,y+1); printf("현재 생성된 약속리스트가 없습니다.");
		Sleep(3000);
		return; //return 0;
	}
	while (!feof(fp)) {			//약속리스트 열어서 리스트에 적혀진 개수만큼 이름과 날짜를 읽어서 출력하는 부분

		gotoxy(x+8,y+1); printf("약속명                      약속날짜");
		fscanf(fp, "%s", &check);
		if(!strcmp(check,"약속리스트")){
			fscanf(fp,"%d", &listCount);

			oldPromise = (struct structPromise*)malloc(sizeof(struct structPromise)*listCount);		//읽어온 약속을 저장하기위한 약속구조체
			for(i=0; i<listCount; i++) {															
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

			cost=(char**)malloc(sizeof(char*)*listCount);												//비용은 약속수정에서 안쓰이는 정보이므로 그냥 읽어주기만 한다.. 필요없음
			for(i=0; i<listCount; i++) {													
				cost[i]=(char*)malloc(sizeof(char)*10);
				strcpy(cost[i],"\0");
				for(j=0; j<10; j++)
					strcpy(&cost[i][j],"\0");
			}

			for(i=0; i<listCount; i++) {																			//일단 약속리스트개수만큼 약속을 읽어와서 oldPromise구조체에 순서대로 저장
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
			}

			for(i=0; i<listCount; i++) {	
				if(i==5){
					gotoxy(35,10); printf("다음리스트를 보려면 >키를 입력하세요. 번호를 선택하려면 @키를 입력하세요.");
					while(1){
						gotoxy(110,10);scanf("%s",&controlList);
						if(!strcmp(controlList,"b")||!strcmp(controlList,"B")){
							for(i=0; i<listCount; i++) {											
								for(j=0; j<4; j++)
									free(oldPromise[i].promiseFriendsName[j]);
								free(oldPromise[i].promiseFriendsName);
							}
							free(oldPromise);
							for(i=0; i<listCount; i++)
								free(friendsName[i]);
							free(friendsName);
							for(i=0; i<listCount; i++)
								free(cost[i]);
							free(cost);
							return;  //return 0;
						}
						if(!strcmp(controlList,"@")||!strcmp(controlList,">"))
							break;
						gotoxy(110,10);printf("     ");
					}
					if(!strcmp(controlList,"@")){
						strcpy(controlList,"\0");
						break;							
					}
					else if(!strcmp(controlList,">")){
						listBorderDraw2(35,11);
						gotoxy(x+8,y+1); printf("약속명                      약속날짜");
						strcpy(controlList,"\0");
					}
					else
						scanf("%s",&controlList);
					gotoxy(35,10);printf("                                                                                  ");


				}
				else if(i!=0&&i!=5&&i%5==0&&i+1!=listCount){
					gotoxy(35,10);printf("이전리스트 <, 다음리스트 >, 번호를 선택하려면 @키를 입력하세요.");
					while(1){
						gotoxy(100,10);scanf("%s",&controlList);
						if(!strcmp(controlList,"b")||!strcmp(controlList,"B")){
							for(i=0; i<listCount; i++) {											
								for(j=0; j<4; j++)
									free(oldPromise[i].promiseFriendsName[j]);
								free(oldPromise[i].promiseFriendsName);
							}
							free(oldPromise);
							for(i=0; i<listCount; i++)
								free(friendsName[i]);
							free(friendsName);
							for(i=0; i<listCount; i++)
								free(cost[i]);
							free(cost);
							return; //return 0;
						}
						if(!strcmp(controlList,"@")||!strcmp(controlList,"<")||!strcmp(controlList,">"))
							break;

						gotoxy(100,10);printf("     ");
					}
					if(!strcmp(controlList,"@")){
						strcpy(controlList,"\0");
						break;
					}
					else if(!strcmp(controlList,">")){
						listBorderDraw2(35,11);
						gotoxy(x+8,y+1); printf("약속명                      약속날짜");
						strcpy(controlList,"\0");
					}
					else if(!strcmp(controlList,"<")){
						listBorderDraw2(35,11);
						gotoxy(x+8,y+1); printf("약속명                      약속날짜");
						i=i-10;
						numbering=numbering-10;
						strcpy(controlList,"\0");
					}
					else
						scanf("%s",&controlList);
					gotoxy(35,10);printf("                                                                                  ");
				}

				gotoxy(x+5,y+3+2*(i%5));printf("%d  %s ",numbering,oldPromise[i].promiseName);
				gotoxy(x+38,y+3+2*(i%5));printf("%s\n",oldPromise[i].Promisedate);
				numbering++;
				if(i+1==listCount&&listCount>5){
					gotoxy(35,10);printf("처음으로 돌아가려면 <키를 입력하세요.번호를 선택하려면 @키를 입력하세요.");
					while(1){
						gotoxy(110,10);scanf("%s",&controlList);
						if(!strcmp(controlList,"b")||!strcmp(controlList,"B")){
							for(i=0; i<listCount; i++) {											
								for(j=0; j<4; j++)
									free(oldPromise[i].promiseFriendsName[j]);
								free(oldPromise[i].promiseFriendsName);
							}
							free(oldPromise);
							for(i=0; i<listCount; i++)
								free(friendsName[i]);
							free(friendsName);
							for(i=0; i<listCount; i++)
								free(cost[i]);
							free(cost);
							return ;//return 0;
						}
						if(!strcmp(controlList,"@")||!strcmp(controlList,"<"))
							break;
						gotoxy(110,10);printf("     ");
					}
					if(!strcmp(controlList,"@")){
						strcpy(controlList,"\0");
						break;
					}
					else if(!strcmp(controlList,"<")){
						listBorderDraw2(35,11);	
						gotoxy(x+8,y+1); printf("약속명                      약속날짜");
						i=-1;
						numbering=1;
						strcpy(controlList,"\0");
					}

					gotoxy(35,10);printf("                                                                                  ");
				}
			}
		}
	}
	fclose(fp);
	gotoxy(35,10);printf("                                                                                     ");
	gotoxy(35,25);printf("→ 돈분배할 약속 : ");


	while(1) {						//리스트 번호 범위 내의 수만 입력받기
		gotoxy(56,25);scanf("%s",select);
		if(!strcmp(select,"b")||!strcmp(select,"B")){
			for(i=0; i<listCount; i++) {											
				for(j=0; j<4; j++)
					free(oldPromise[i].promiseFriendsName[j]);
				free(oldPromise[i].promiseFriendsName);
			}
			free(oldPromise);
			for(i=0; i<listCount; i++)
				free(friendsName[i]);
			free(friendsName);
			for(i=0; i<listCount; i++)
				free(cost[i]);
			free(cost);
			return ; //return 0;
		}
		listnumber=atoi(select);	
		if(listnumber>0&&listnumber<numbering)
			break;
		gotoxy(35,26);printf("리스트 내의 번호를 입력하세요");
		gotoxy(54,25);printf("       ");
	}
	listnumber--;

	length = strlen(friendsName[listnumber]);			
	//줄단위로 읽은 학번들을 7자씩 끊어서 미리 할당해놓은 promiseFriendsName에 하나씩 넣어주는 부분
	for(i=0; i<4; i++) {											
		//여기서도 굳이 회원수를 체크하려면 귀찮으니 4번 반복실행하도록 만듬, 자신포함 최대 5명이므로 저장되는 다른 회원정보는 4명
		strncpy(oldPromise[listnumber].promiseFriendsName[i],friendsName[listnumber],7);
		for(j=0; j<7; j++)
			changeLocation(friendsName[listnumber]);
		if(strncmp(friendsName[listnumber],",",1)==0)
			changeLocation(friendsName[listnumber]);
		else
			break;		
	}

	transName=(char**)malloc(sizeof(char*)*4+1);	
	//학번을 그냥 쓸수 없으니 이름으로 바꿀 문자배열을 또 동적할당 해준다.
	for(i=0; i<4; i++) {													
		transName[i]=(char*)malloc(sizeof(char)*13);
		strcpy(transName[i],"\0");
		for(j=0; j<13; j++)
			strcpy(&transName[i][j],"\0");
	}

	strcpy(fileName,"회원목록.txt");						
	
	//학번을 이름으로 바꿔준다. 회원목록 txt를 5번동안 열고 닫고 하며 반복... 회원 숫자를 계산하기 귀찮으므로 그냥 5번 반복
	for(i=0;i<4;i++){
		fp = fopen(fileName, "r");
		while (!feof(fp)) {	
			//학번과 이름을 한줄 읽는다.
			fscanf(fp, "%s %s", &ID, &listName);	

			//검색할 학번과 같은 학번이면
			if(!strcmp(ID,oldPromise[listnumber].promiseFriendsName[i])){		

				//transName 문자배열에 현재 읽은 이름을 복사
				strcpy(transName[i],listName);											
				
				break;
			}
		}
		fclose(fp);
	}

	j=0;
	for(i=0;i<4;i++){
		if(!strcmp(transName[i],"\0"))
			break;
		strcpy(fileName,oldPromise[listnumber].promiseFriendsName[i]);
		strcat(fileName,transName[i]);
		j++;
		k=recordCombineTimetable(CombineTimetable,fileName);

	}
	itoa(j,oldPromise[listnumber].promiseFreindsCount,10);
	oldPromise[listnumber].promisePlace[strlen(oldPromise[listnumber].promisePlace)-1]=blank[0];           //장소DB에서 읽어올때 \n 하나 들어있는거 없애서 자동줄바꿈 방지

	listBorderDraw2(35,26);

	gotoxy(38,28);printf("약속명 >>     %s",oldPromise[listnumber].promiseName);
	gotoxy(38,30);printf("장소   >>     %s",oldPromise[listnumber].promisePlace);
	gotoxy(38,32);printf("날짜   >>     %s",oldPromise[listnumber].Promisedate);
	gotoxy(38,34);printf("시간   >>     %s",oldPromise[listnumber].promiseTime);
	gotoxy(38,36);printf("함께할친구 >>   ");

	for(i=0; i<4; i++)
		printf("%s ",transName[i]);

	////-------------------------------알고리즘 시작----------------------------------------------------------//
	while(1) {
		peopleCnt = j+1; //j 사람 수를 peopleCnt에 저장
		gotoxy(37,40);	printf("나누기 전 돈, 절사할 최소 돈 >>");


		gotoxy(37,41);
		printf("예시) 16500 1000\n");
		gotoxy(69,40); 

		//하나라도 문자가 들어가는 경우, 음수가 들어가는 경우, 공백이 들어가는 경우 오류 처리
		do { 
			fflush(stdin);
			gotoxy(37,42);
			printf("절사할 돈을 작게하거나 양수를 입력하세요.");
			gotoxy(69,40);   printf("              ");
			gotoxy(69,40);
		} 
		while(scanf("%d %d", &beforeDivideMoney, &divisionNumber)!=2 || (beforeDivideMoney < 0) || (divisionNumber < 0) || (beforeDivideMoney < divisionNumber) || beforeDivideMoney == divisionNumber);
		
		system("cls");
		screenBorderDraw();
		listBorderDraw1(26,12);
		gotoxy(58,6);
		printf("☆ 돈 나누기 ☆");
		gotoxy(45, 15);
		printf("1.   공평하게 나누기");
		gotoxy(45, 18);
		printf("2.   한 명에게 몰아주기\n");
		gotoxy(50, 30);
		printf("메뉴를 선택해주세요 : ▶");
		scanf("%d", &menuseletion); fflush(stdin);

		while(1){
			if( menuseletion==1 || menuseletion==2 )
				break;
			else {
				gotoxy(50, 30);
				printf("메뉴 선택을 다시 해주세요.");
				scanf("%d", &menuseletion); fflush(stdin);
			}
			break;
		}
		break;
	}

	switch(menuseletion){

	case 1:
		//scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);

		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
		int arrMoney[5] = {0, 0, 0, 0, 0};*/

		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

		if (restMoney == 0) {
			finalMoney = baseMoney+ (restMoney / (peopleCnt * divisionNumber) * divisionNumber);

			for(i=0; i<peopleCnt; i++)
				arrMoney[i] = finalMoney;
		} 
		else {
			restPeople = ( restMoney / divisionNumber );
			finalMoney = baseMoney + divisionNumber;

			if (restMoney % divisionNumber == 0) {
				for(i = 0 ;i<restPeople;i++){
					arrMoney[i] = finalMoney;
				}
				for(i=restPeople;i<5;i++){
					arrMoney[i] = (baseMoney + (restMoney % divisionNumber));
				}
			} 
			else {
				if (restPeople != 0)
					for(i=0;i<restPeople;i++)
						arrMoney[i] = finalMoney;
				if (peopleCnt - restPeople - 1 != 0)
					for(i=restPeople;i<peopleCnt-1;i++)
						arrMoney[i] = baseMoney;
				arrMoney[i] = (baseMoney + (restMoney % divisionNumber));					
			}
		}

		for(i=0; i<peopleCnt-1; i++){
			gotoxy(53,32+i);
			printf("%d번째 사람 %s: %d원\n", i+1,transName[i],arrMoney[i]);
		}
		gotoxy(53,32+i);
		printf("%d번째 사람 %s: %d원\n", i+1,s->name,arrMoney[i]);

		getch(); break;

	case 2:
		//한 명한테 몰아주기
		srand((unsigned)time(NULL)); //랜덤 시드 생성
		fflush(stdin); 
		randomPersonNumber = ( rand()%peopleCnt );
		arrMoney[randomPersonNumber] = beforeDivideMoney;	

		for(i=0; i<peopleCnt-1; i++){ 
			gotoxy(53,32+i);
			printf("%d번째 사람 %s: %d원\n", i+1, transName[i], arrMoney[i]);
		}
		gotoxy(53,32+i);
		printf("%d번째 사람 %s: %d원\n", i+1, s->name, arrMoney[i]);

		gotoxy(53, 36);
		printf("%d번째 사람이 당첨!\n", randomPersonNumber+1);

		getch();
		break;
	}
	/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 끝ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ ㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/

	//열기할 파일 이름 만들기
	getUserfileName(fileName,s,"PromiseList");
	fp = fopen(fileName, "r");
	if ( fp == NULL ) {						//파일이 없을 경우
		gotoxy(20, 32);printf("현재 생성된 약속리스트가 없습니다.");
		return ;
	}
	while(!feof(fp)){
		fscanf(fp,"%s",buffer);
		if(!strcmp(buffer,"약속리스트")){
			fscanf(fp,"%d",&promiselistCount);
			pl=(structPromise *)malloc(sizeof(structPromise)*promiselistCount);
			for(i=0; i<promiselistCount; i++){// 리스트의 수만큼 파일안에 있는 정보 읽어서 저장
				for(j=0; j<70; j++)
					buffer[j]='\0';
				for(j=0; j<10; j++)
					pl[i].cost[j]='\0';

				fscanf(fp,"%s",pl[i].promiseName);  //약속명
				fseek(fp,2,SEEK_CUR);
				fgets(pl[i].promisePlace,40,fp);  //장소
				fscanf(fp,"%s",pl[i].promiseTime);  //시간
				fscanf(fp,"%s",pl[i].Promisedate);  //날짜
				fscanf(fp,"%s",buffer);  //친구들
				friendCount=1;
				k=0;
				for(j=0; buffer[j] != '\0'; j++){
					if(buffer[j] == ',')
						friendCount++;
				}			

				//친구들 학번 저장할곳 할당
				pl[i].promiseFriendsName=(char **)malloc(sizeof(char *)*friendCount); 
				for(j=0; j<friendCount; j++)
					pl[i].promiseFriendsName[j]=(char *)malloc(sizeof(char)*9);

				itoa(friendCount,pl[i].promiseFreindsCount,10);
				for(j=0; j<friendCount; j++){
					for(l=0; l<9; l++)
						pl[i].promiseFriendsName[j][l]='\0';
				}

				for(j=0,l=0; buffer[j] != '\0'; j++){
					if(buffer[j] == ','){
						pl[i].promiseFriendsName[k][l]='\0';
						k++;
						l=0;
					}
					else
						pl[i].promiseFriendsName[k][l++]=buffer[j];					
				}
				pl[i].promiseFriendsName[k][l]='\0';

				fseek(fp,2,SEEK_CUR);
				fgets(pl[i].cost,10,fp);				
			}
		}
	}
	fclose(fp);

	//자신의 파일에 비용 저장
	fp=fopen(fileName,"w");
	fprintf(fp,"%s\n","약속리스트");
	fprintf(fp,"%d\n",promiselistCount);
	for(i=0; i<promiselistCount; i++) {
		fprintf(fp,"%s\n",pl[i].promiseName);
		fprintf(fp,"%s",pl[i].promisePlace);
		fprintf(fp,"%s\n",pl[i].promiseTime);
		fprintf(fp,"%s\n",pl[i].Promisedate);

		friendCount=atoi(pl[i].promiseFreindsCount);
		for(j=0; j<friendCount; j++) {
			fprintf(fp,"%s",pl[i].promiseFriendsName[j]);
			if(j != friendCount-1)
				fprintf(fp,"%s",",");
			else if(j == friendCount-1)
				fprintf(fp,"%s","\n");
		}
		if(i == listnumber)
			fprintf(fp,"%d\n",arrMoney[friendCount]);  //수정 내돈은 arrMoney마지막에 있다.
		else if(pl[i].cost[0] == 10 || i == promiselistCount-1)
			fprintf(fp,"%s",pl[i].cost);
		else
			fprintf(fp,"%s",pl[i].cost);
	}
	fclose(fp);	

	//친구꺼 파일에 비용 저장
	for(k=0; k<peopleCnt-1; k++) {

		strcpy(fileName,pl[listnumber].promiseFriendsName[k]);  //학번복사
		strcat(fileName,transName[k]);
		strcat(fileName,"PromiseList.txt");

		friendSaveCost(pl,listnumber,fileName,arrMoney,k);
	}

	//동적할당 해제
	for(i=0; i<listCount; i++) {											
		for(j=0; j<4; j++)
			free(oldPromise[i].promiseFriendsName[j]);
		free(oldPromise[i].promiseFriendsName);
	}
	free(oldPromise);
	for(i=0; i<listCount; i++)
		free(friendsName[i]);
	free(friendsName);
	for(i=0; i<listCount; i++)
		free(cost[i]);
	free(cost);
	for(i=0; i<4; i++)
		free(transName[i]);
	free(transName);

	gotoxy(20,10); printf("메인 메뉴로 돌아가려면 B를 다른 약속을 상세보기하려면 B를 제외한 키를 입력하세요 : ");
	gotoxy(103,10); scanf("%s",&select); fflush(stdin);
	if(!strcmp(select,"b")||!strcmp(select,"B")) {  //뒤로가기
		return; //return 0;
	}
	else if(!strcmp(select,"x")||!strcmp(select,"X")) {  //종료
		gotoxy(90,45);
		exit(1);
	}
	else
		return; //return 1
}

//비용을 친구들.txt에 저장
void friendSaveCost(structPromise *loginpl,int listnumber,char *fileName,int *arrMoney,int friendnum) {
	FILE *fp;
	char buffer[70];
	int promiselistCount;
	int friendCount;
	structPromise *pl;
	int i,j,k,l;

	//친구꺼 읽기
	fp=fopen(fileName,"r");

	if ( fp == NULL ) {						//파일이 없을 경우
		gotoxy(20, 32);printf("현재 생성된 약속리스트가 없습니다.");
		return;
	}
	while(!feof(fp)){
		fscanf(fp,"%s",buffer);
		if(!strcmp(buffer,"약속리스트")){
			fscanf(fp,"%d",&promiselistCount);
			pl=(structPromise *)malloc(sizeof(structPromise)*promiselistCount);
			for(i=0; i<promiselistCount; i++){// 리스트의 수만큼 파일안에 있는 정보 읽어서 저장
				for(j=0; j<70; j++)
					buffer[j]='\0';
				for(j=0; j<10; j++)
					pl[i].cost[j]='\0';

				fscanf(fp,"%s",pl[i].promiseName);  //약속명
				fseek(fp,2,SEEK_CUR);
				fgets(pl[i].promisePlace, 40, fp);  //장소
				fscanf(fp,"%s", pl[i].promiseTime);  //시간
				fscanf(fp,"%s", pl[i].Promisedate);  //날짜
				fscanf(fp,"%s", buffer);  //친구들

				friendCount=1;
				k=0;
				for(j=0; buffer[j] != '\0'; j++){
					if(buffer[j] == ',')
						friendCount++;
				}	

				//친구들 학번 저장할곳 할당
				pl[i].promiseFriendsName=(char **)malloc(sizeof(char *)*friendCount); 
				for(j=0; j<friendCount; j++)
					pl[i].promiseFriendsName[j]=(char *)malloc(sizeof(char)*9);

				itoa(friendCount,pl[i].promiseFreindsCount,10);
				for(j=0; j<friendCount; j++){
					for(l=0; l<9; l++)
						pl[i].promiseFriendsName[j][l]='\0';
				}

				for(j=0,l=0; buffer[j] != '\0'; j++){
					if(buffer[j] == ','){
						pl[i].promiseFriendsName[k][l]='\0';
						k++;
						l=0;
					}
					else
						pl[i].promiseFriendsName[k][l++]=buffer[j];					
				}
				pl[i].promiseFriendsName[k][l]='\0';

				fseek(fp,2,SEEK_CUR);
				fgets(pl[i].cost,10,fp);				
			}
		}
	}
	fclose(fp);

	//친구꺼 파일에 비용 저장
	fp=fopen(fileName,"w");
	fprintf(fp,"%s\n","약속리스트");
	fprintf(fp,"%d\n",promiselistCount);

	for(i=0; i<promiselistCount; i++){
		fprintf(fp,"%s\n",pl[i].promiseName);
		fprintf(fp,"%s",pl[i].promisePlace);
		fprintf(fp,"%s\n",pl[i].promiseTime);
		fprintf(fp,"%s\n",pl[i].Promisedate);

		friendCount=atoi(pl[i].promiseFreindsCount);
		for(j=0; j<friendCount; j++){
			fprintf(fp,"%s",pl[i].promiseFriendsName[j]);
			if(j != friendCount-1)
				fprintf(fp,"%s",",");
			else if(j == friendCount-1)
				fprintf(fp,"%s","\n");
		}

		if(!strcmp(loginpl[listnumber].promiseName,pl[i].promiseName) && !strcmp(loginpl[listnumber].Promisedate,pl[i].Promisedate) && !strcmp(loginpl[listnumber].promiseTime,pl[i].promiseTime))
			fprintf(fp,"%d\n",arrMoney[friendnum]);  //수정 내돈은 arrMoney마지막에 있다.
		else if(pl[i].cost[0] == 10 || i == promiselistCount-1)
			fprintf(fp,"%s",pl[i].cost);
		else
			fprintf(fp,"%s",pl[i].cost);
	}
	fclose(fp);	
}