#include "structHeader.h"

void moneyShare2(structMember *s){
	/*-------------------------------변수 시작했다--------------------------------*/
	FILE *fin;
	int i;
	char fileName[30];
	char fileContents[600][100]={0};
	int beforeDivideMoney; // 나누기 전 돈
	int finalMoney; // 최종 돈
	int peopleCnt; // 사람 숫자
	int divisionNumber; // 나누는 수
	int arrMoney[5]={0, };
	int baseMoney ;
	int restPeople;
	int restMoney;
	int promiseNumber;
	int menuseletion; //메뉴 선택하는 변수
	int randomPersonNumber; //랜덤으로 받은 시드값을 저장하는 변수 1,2,3,4,5 중 하나
	int promiseCnt=0, contentsCnt=0, j=0;
	//promiseList 함수에서 따온 것↓
	char buffer[41]; //파일에서 읽어들인 값이 들어가는 임시 저장공간
	char promiseName[41];	//약속 이름을 저장
	int listCount=0;		//리스트 개수
	char promiseDate[10];	//약속 날짜를 저장
	int x=35, y=6;	
	/*--------------------------------변수 끝났다---------------------------------*/
	
	/*
	54000원이 나왔다. 5명이다.
	(54000 / (5 * 1000))*1000 = 50000 / 5 = 10000원씩 나누어 갖게된다.
	이 때 restMoney = 4000원
	*/

	//나누기 전 돈, 사람 수, 나누는 수, 최종 돈, 남는 돈, i, 몰아주는 사람 제외하고 나머지

	i=0;
	system("cls");
	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"PromiseList.txt"); //1235039이정훈PromiseList.txt
	fin = fopen(fileName,"r"); // 파일생성

	if ( fin == NULL ) {
		printf("현재 생성된 약속리스트가 없습니다.");
		return;
	}
	
	while (!feof(fin)) {			//약속리스트 열어서 약속의 이름과 날짜를 읽어서 출력, 최대 10개까지 출력
		gotoxy(55,4); printf("▷ 나의 약속리스트\n");
		fscanf(fin, "%s", &buffer);
		if(!strcmp(buffer,"약속리스트")){
			fscanf(fin,"%d", &listCount);
			gotoxy(62, 25); printf("현재 잡혀있는 약속 개수 %d",listCount);
			for(i=0; i<listCount; i++){
				fscanf(fin,"%s", promiseName);
				fgets(buffer,41,fin);
				fgets(buffer,41,fin);
				fgets(buffer,41,fin);
				fscanf(fin,"%s", promiseDate);
				fscanf(fin,"%s", buffer);
				fgets(buffer,41,fin);	
				fgets(buffer,41,fin);
				gotoxy(x,y);printf("○ %s / %s",promiseName,promiseDate);
				y=y+3;
				if(x==35&&y==21){		//한쪽에 5개를 찍은뒤 옆줄로 이동해서 다시 5개 찍음(최대 10개)
					x=75;
					y=6;
				}
				if(x==75&&y==21){		//10개를 꽉채워 찍은 경우 알림문구 표시
					gotoxy(53, 22);printf("나의 약속리스트는 10개까지만 표시됩니다.");
					gotoxy(55, 23);printf("상세한 약속은 약속 메뉴로 들어가세요.");
					break;
				}
			}
		}
	}
	fclose(fin);

	strcpy(fileName,s->ID);
	strcat(fileName,s->name);
	strcat(fileName,"PromiseList.txt"); //1235039이정훈PromiseList.txt
	fin = fopen(fileName,"r"); // 파일생성

	while(1) // 파일의 끝까지 내용을 fileContents 변수에 저장
	{
		fgets(fileContents[contentsCnt], 100, fin); //fin에서 100만큼까지 최대 읽어서 fileContents[contentsCnt]에 저장
		contentsCnt++;
		if (feof(fin)) break;
	}
	//printf("약속리스트\n");
	//promiseCnt = (contentsCnt-2) / 6;
	//for (i=0; i<promiseCnt; i++)
	//{
	//	printf("%d. %s", i+1, fileContents[(i*6)+2]);
	//	/*
	//		for (j=0; j<6; j++)
	//		{
	//			printf("%s", fileContents[(i*6)+2+j]);
	//		}
	//	*/
	//} // 약속 리스트들이 총 6줄이므로 6*i번째의 제목만 출력

	//메뉴를 선택해라
	gotoxy(43,27);
	printf("약속을 선택하시오 ▶");
	gotoxy(52,27);
	scanf("%d", &promiseNumber);
	gotoxy(43,28);
	printf("<%s", fileContents[(promiseNumber-1)*6+2]);
	gotoxy(55,28);
	printf(">을 선택하셨습니다.\n");
	//사람 인원수 구하기
	peopleCnt=1;
	if (fileContents[(promiseNumber-1)*6+4][0]==NULL) {
		printf("입력오류!!!!");
	}
	else {
		for (i=0; ; i++)
		{ //해당하는 사람 숫자를 불러온다.
			if (fileContents[(promiseNumber-1)*6+6][i]==',') {
				peopleCnt++;
			}
			if (fileContents[(promiseNumber-1)*6+6][i]==NULL) {
				peopleCnt++;
				break;
			}
		}
	}
	fflush(stdin);
	while(1) {
		printf("1 : 공평하게 나누기, 2 : 한 명에게 몰아주기\n");
		printf("메뉴를 선택해주세요 : ▶");
		scanf("%d", &menuseletion); fflush(stdin);

		if( menuseletion==1 || menuseletion==2)
			break;
		else printf("메뉴 선택을 다시 해주세요.");
	}

	switch(menuseletion){
	case 1:

		printf("나누기 전 돈, 절사할 최소 돈\n");
		printf("예시) 16500 1000\n");

		scanf("%d %d", &beforeDivideMoney , &divisionNumber); fflush(stdin);

		baseMoney = (beforeDivideMoney / (peopleCnt * divisionNumber)) * divisionNumber;
		/*int beforeDivideMoney, peopleCnt=0, divisionNumber, baseMoney = 0, finalMoney, restMoney, i, restPeople;
		int arrMoney[5] = {0, 0, 0, 0, 0};*/

		restMoney = beforeDivideMoney - ( baseMoney * peopleCnt );

		/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 시작ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/
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

		/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ알고리즘 끝ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ ㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/

		for(i=0; i<peopleCnt; i++){ //for (i=0; i<peopleCnt; i++)
			printf("%d번째 사람 : %d원\n", i+1,arrMoney[i]);
		}

		getch(); break;

	case 2: //한 명한테 몰아주기
		srand((unsigned)time(NULL));
		fflush(stdin); 
		randomPersonNumber = ( rand()%peopleCnt );

		printf("나눌 돈을 적어주세요 : ▶"); 
		scanf("%d", &beforeDivideMoney);  fflush(stdin); 

		printf("%d번째 사람이 당첨!\n", randomPersonNumber+1);

		arrMoney[randomPersonNumber] = beforeDivideMoney;

		for(i=0; i<peopleCnt; i++){
			printf("%d ", arrMoney[i]);
		}
		getch();
		break;
	}
}

void moneyShare1(structMember *s){
	int x=24, y=4;
	char DBname[20];
	char logID[8];
	char logName[13];
	int command;
	char command1,command2;


	strcpy(logID,s->ID);
	strcpy(logName,s->name);			
	strcpy(DBname,logID);
	strcat(DBname,logName);	

	screenBorderDraw();
	listBorderDraw1(26,12);
	listBorderDraw1(26,25);

	gotoxy(58,10);
	printf("--나의 약속 리스트--");
	gotoxy( 6+x, 10+y );
	printf("   약속명                 약속날짜 \n");


	/*  gotoxy( 6+x, 12+y );
	printf("1. 홍대가기                11/28\n");
	gotoxy( 6+x, 14+y);
	printf("2. 학교가기                11/12\n");*/

	promiseList(DBname);

	gotoxy( 6+x, 20+y );
	printf("수정하실 약속>> ");
	gotoxy( 6+x, 23+y );
	printf(" 약속명          장소          날짜       시간       함께할친구");
	gotoxy( 6+x, 25+y );
	printf("학교가기      공학관(405)      11/4        2시         이정훈");
	gotoxy( 5+x,32+y );
	printf("수정하시겠습니까?(Y/N)");

	gotoxy( 120, 41 );
	scanf("%c", &command1 );

	gotoxy( 47, 24);
	scanf("%d", &command );
	fflush(stdin);
	gotoxy( 54, 36);
	scanf("%c", &command2 );
	gotoxy( 23, 38 );



}
