#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include <time.h>
#include<malloc.h>
#include <windows.h>
#pragma warning (disable:4996)

//B(�ڷΰ���), X(����)�� �Է��ؾ��ϱ� ������ ���� char ������ �Է��� �޾ƾ��Ѵ�.

/*-------------------------------����ü����--------------------------------*/
//ȸ�� ����ü
typedef struct structMember{  
	char name[13];  //ȸ���̸�
	char ID[8];  //�й�
	char password[14];  //��й�ȣ  
	char backupPassword[14];  //�����ڵ�
}structMember;

//��� ����ü
typedef struct structPromise{ 
	char promiseName [41];  //��Ӹ�
	char promisePlace[40];  //��� �̸��� �𸣱� ������ ������ DB�� ���ڿ��� ����ų ���̴� //���DB ��ȹ�� ���� ��ü������ �ȳ��ͼ� �ϴ� �迭�� �й�.
    char promiseTime[6];  //��ӽð�
	char Promisedate[10];  //��ӳ�¥
	char promiseFreindsCount[2];//�߰�
	char **promiseFriendsName;  //�ο����� �Է��� �޾� �����Ҵ� {���赿��, ���̼���}
	//��� ������ ��������
}structPromise;

//���� ����ü
typedef struct Subject{
	char dayOfWeek[4]; //����
	char subjectName[15]; //�����̸�
	char subjectClass[10]; //����
}structSubject;

//�ð�ǥ ����ü
typedef struct structTimetable{  //13���� -> 13�� �Է��ϱ� ������ 2��
	structSubject timetable[5][13];  
}structTimetable;

//��� ����ü
typedef struct structCost{
	char cost;
}structCost;

/*-------------------------------����ü���� ��--------------------------------*

/*-------------------------------�Լ���������--------------------------------*/
//�α��ΰ���
void login(structMember *s);  //�α���
void membership();  //ȸ������
void mainMenu(structMember *s);  //�α��� �� ���θ޴�
void pwFind();  //��й�ȣ ã��

//�����º���
void mystatus(structMember *s);  //���º������
void mystatus_promiseList(char *DBname);  //�� ���º��� ��Ӹ���Ʈ ���

//�ð�ǥ����
void timetableMenu(structMember *s); //�ð�ǥ�޴��Լ�
void timetableDraw(structMember *s); //�ð�ǥ�׸����Լ�
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalCnt, structMember *s); //�ð�ǥ txt�� �����ϴ� �Լ�
void classAtoi(char *dayOfWeek, int *savedClass); //���ø� char->int���� �ٲپ��ִ� �Լ�
int checkOverlappingClass(structSubject* subjectPointer,structSubject subject,int subjectTotalCnt); //�ߺ�����üũ�Լ�
void InputSubjectCnt(structMember *s); // �ð�ǥ����� - ��~�� ���񰹼� �Է� �Լ�
void InputSubjectNameAndClass( int* SubjectCntOfday, int subjectTotalCnt, structMember *s) ; // �ð�ǥ����� - �̸�/���� �Է��Լ�
void modifyMenu(structMember *s); //�ð�ǥ�����޴��Լ�
void modifySubjectInfo(structMember *s); // �ð�ǥ �������� �����Լ�
void addSubject(structMember *s); //�ð�ǥ ���� �߰�
void removeSubject(structMember *s); //�ð�ǥ ���� ����
void sortTimetable(structSubject* subjectPointer,int subjectTotalCnt, structMember *s); // �ð�ǥ (����)���� �Լ�
void removeTimetable(structMember *s); //�ð�ǥ�����Լ�(�ð�ǥtxt���ϻ���)

//��Ӱ���

void promiseChange(char *DBname,char *logID);   //��Ӽ��� ����-> ����Ʈ ���-> ����Ʈ ����-> ��Ӽ����׸� �����Լ� ȣ��-> ��������Լ��� ȣ�� �ϴ� �Լ�
int selectChange(char *DBname, struct structPromise *old, int listnumber, char **name,int CombineTimetable[5][13],char checkPlace[3]);    //��Ӽ����׸� ����
void changePromiseName(struct structPromise *old);   //��Ӽ���-> ��Ӹ� ����
void changePlace(char *DBname, struct structPromise *old);  //��Ӽ���-> ������ ����
int changeDate(struct structPromise *old,int newCombineTimetable[5][13]);    //��Ӽ���-> ��ӳ�¥ ����
void changeTime(struct structPromise *old,int newCombineTimetable[5][13],int dayofweek);   //��Ӽ���-> ��ӽð� ����
int changeName(char *DBname,int CombineTimetable[5][13],int newCombineTimetable[5][13] ,struct structPromise *old);    //��Ӽ���-> ����� �������� ȸ���� �̸� ����
int checkDateTime(int CombineTimetable[5][13], struct structPromise *old);   //��Ӽ���-> ���� ����� �������� üũ. �̸��� ���������� �ҷ��� �ٲ� ���սð�ǥ�� �ٰŷ� üũ
void saveMyPromiseList(struct structPromise *promiseList, char *DBname, int listCount,char **friendsName,char **cost,int listnumber);   //��Ӹ���Ʈ �����κ��� �´� ��ġ�� �����ϴ� �Լ�
void deletePromise(char *friendID,char *promiseName, char *promiseDate, char *promiseTime);    //��Ӹ���Ʈ�� �а� �Ű������� �־��� ����̸�, ��ӳ�¥, ��ӽð��� ���� ����׸��� ã�� �����ϴ� �Լ� ����� �װ� �ϳ��� �־��� ���� ������ ������.
void showBG(char copyPromiseName[41],char copyPromisePlace[40],char copyPromisedate[10],char copyPromiseTime[6],char copyName[50]);    //��Ӽ��� UI����� ���� ȭ���� �����ϰ� ������ ������ ����ϴ� �κ��� �ʿ��ؼ� ���� �Լ�
void saveFriendPromiseList(struct structPromise *promiseList, char *DBname,char **friendsName,char **cost,int listnumber,struct structPromise *newPromise);
//��� �󼼺��� �κ�
int ViewAllPromise(char *DBname,char *logID);
//��� �����κ�
int deleteAllPromise(char *DBname,char *logID) ;
//�����Ұ���,����κ�
void promisePlace(char *DBname,struct structPromise *newPromise);   //��� ��� ���� �Լ�
void saveNewpromise(char *DBname,struct structPromise *newPromise);   //���� ��Ӹ���Ʈ�� �� ����� �߰��ϴ� �Լ�
//��Ӹ����κ�
int promise(structMember *s);   //��Ӹ���� �����Լ�. �޴������� �Է¹޴´�.
void showMenu();    //��Ӹ���� ���θ޴�����Լ�
void promiseList(char *DBname);   //ȸ���� ��Ӹ���Ʈ�� ����ϴ� �Լ�
void promiseCreatConsole(char *DBname, char *logID);    //��Ӹ���� �Լ�. �Է¹޴� ��� �Լ��� ȣ��, �����ϴ� �Լ��� ȣ��
void selectName(char *DBname,struct structPromise *newPromise);   //��Ӹ��� �Է¹޴� �Լ�
int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise);    //ȸ������ �Է¹ް� ȸ������ŭ �̸��� �Է¹޾� �̸��˻��Լ��� ȣ���ϴ� �Լ�
int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13],char *MyDB,char IDList[4][13]);   //�̸��˻��Լ� (�˻����̸�, �Բ��ϴ�ȸ���� ����Ʈ�� �ȿö� ȸ����,����ӱ���ü,���սð�ǥ) �� �Ű������� �޴´�
void setMajor(char ID[8],char Major[20]);   //�й� 3��°,4��° �ڸ��� �������� �а������� �˾Ƴ��� �Լ�
int recordCombineTimetable(int CombineTimetable[5][13], char *DBname);   //���սð�ǥ�� ������ �߰��ϴ� �Լ�, ���սð�ǥ�� '�й�+�̸�' ���ڿ��� �Ű������� �޾Ƽ� ó��
int selectDate(int CombineTimetable[5][13],structPromise *newPromise);    //���� ����� ��¥ �Է¹޴� �Լ�
int callendar(int Month);    //�޷�����Լ�. ���� �Ű������� �Ѱܹ޴´�. selectDate �Լ����� �Է¹��� ���� �Ѱܹ���.
int weekday(int year, int month, int day);   //�⵵, ��, �� �� �Ű������� �޾� ���� ã�� �Լ�. ���ϰ��� ��������
void selectTime(int CombineTimetable[5][13],structPromise *newPromise,int dayofWeek);    //���� ����� �ð��� �Է¹޴� �Լ�
void saveFriendsID(char ID[8], char *DB);    //�й��� �Ű������� �޾� �й�+�̸��� �˾Ƴ��� �Լ�
void changeLocation( char* str );    //���ڿ� ó���Լ� �� ���� ���ڸ� ���ְ� �ѱ��ھ� ����� �Լ�

//������
void moneyShare1(structMember *s);  //�������ּ��� ����
void moneyShare2();  //�������� ��� ���� ���

//�������� ���̴� �͵�
void gotoxy(int x, int y);  //��ǥ����
void screenBorderDraw(); //��üȭ��Ʋ����Լ�
void listBorderDraw(int x, int y); //�޴�Ʋ����Լ�
void promiselistBorderDraw(int x, int y);  ////��Ӹ���ƮƲ���(������)
void listBorderDraw1(int x, int y);  //��Ӹ���ƮƲ���(������)
void listBorderDraw2(int x, int y);	//�̸��˻�����ƮƲ���
void listBorderDraw3(int x, int y);	//����Բ���ȸ������ƮƲ���
void checkInput();  //���ۿ� �����ִ°� üũ
void setcolor(int color, int bgcolor);  //���ڻ�,���ڹ��� ����

/*-------------------------------�Լ��������� ��--------------------------------*/














//��������� ��� 
//r - �б���
//������ ������ �����߻�
//
//r+ - �б�,������. 
//������ ������ ����
//
//w - ������
//(�̸��� ���� ���� ������ ������ �� ����... �ٵ� ���ǹٶ�.�����޴������ſ� ���뾲������)
//(�� �׷��� ������....�̷�������� �̱��� ����...)
//������ ������ ���θ���� ������ ������ ������ �� ������ ������ �������� 
//������ ó������ ����.
//�̸��δ� ���� ������ ����������.
//
//w+ - �б�,������. 
//������ ������ ���� ����� ������ ������ ������ �� ������ ������ �������� 
//������ ó������ ����.
//
//a - �߰����� ���
//������ ������ ���θ����.
//���������� ������ �������� ���� �ں��� ���Ͽ� �߰�
//
//a+ - �߰�������
//������ ������ ���� �����, ������ ������������ �������� ���� �ں��� �߰��Ѵ�.
//������ ��� ���̳� �б�� �����ϳ� ����� ���ϳ��� �߰������θ� �����ϴ�.