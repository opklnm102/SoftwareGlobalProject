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
	char promisePlace[30];  //��� �̸��� �𸣱� ������ ������ DB�� ���ڿ��� ����ų ���̴� //���DB ��ȹ�� ���� ��ü������ �ȳ��ͼ� �ϴ� �迭�� �й�.
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

/*-------------------------------����ü���� ��--------------------------------*/


extern char dayOfWeek[5][4]; // ��������.

/*-------------------------------�Լ���������--------------------------------*/
//�α��ΰ���
void login(structMember *s);  //�α���
void membership();  //ȸ������
void mainMenu(structMember *s);  //�α��� �� ���θ޴�
void pwFind();  //��й�ȣ ã��

//�ð�ǥ����
void timetableMenu(structMember *s); //�ð�ǥ�޴��Լ�->�ð�ǥ ����
void timetableDraw(); //�ð�ǥ�׸����Լ�
void saveTimetalbe(structSubject* subjectPointer, int subjectTotalCnt); //�ð�ǥ txt�� �����ϴ� �Լ�
void classAtoi(char *dayOfWeek, int *savedClass); //���ø� char->int���� �ٲپ��ִ� �Լ�
int checkOverlappingClass(structSubject* subjectPointer,structSubject subject,int subjectTotalCnt); //�ߺ�����üũ�Լ�
void InputSubjectCnt(); // �ð�ǥ����� - ��~�� ���񰹼� �Է� �Լ�
void InputSubjectNameAndClass( int* SubjectCntOfday, int subjectTotalCnt) ; // �ð�ǥ����� - �̸�/���� �Է��Լ�
void modifyMenu(); //�ð�ǥ�����޴��Լ�
void modifySubjectInfo(); // �ð�ǥ �������� �����Լ�
void addSubject(); //�ð�ǥ ���� �߰�
void removeSubject(); //�ð�ǥ ���� ����
void sortTimetable(structSubject* subjectPointer,int subjectTotalCnt); // �ð�ǥ (����)���� �Լ�
void removeTimetable(); //�ð�ǥ�����Լ�(�ð�ǥtxt���ϻ���)


//��Ӱ���
void promise(structMember *s);  //��� ����
void showMenu();  //��Ӹ޴��� ���
void promiseList(char *DBname);	// �α����� ȸ���� ��Ӹ���Ʈ�� �ҷ����� �Լ� , ��¸� �Ѵ�. ������� ���ٰ� ������ش�.
void changeLocation( char* str );

int selectChange(char *DBname, struct structPromise *old, int listnumber, char **name,int CombineTimetable[5][13]);
int recordCombineTimetable(int CombineTimetable[5][13], char *DBname);
int checkDateTime(int CombineTimetable[5][13], struct structPromise *old);
void changePromiseName(struct structPromise *old);
void promiseCreatConsole(char *DBname);	//��Ӹ���� �Լ� (��Ӹ�, �ο��� �Է�  .�̸� �˻��Լ� ���� ����. ��� ����Ʈ ���)
void promisePlace(char *DBname, struct structPromise *newPromise);  //������ ����
void setMajor(char ID[8], char Major[20]);
void promiseChange(char *DBname);					
int callendar(int Month);																	       //�޷�
int weekday(int year, int month, int day);															 //���� ã�� �Լ� ���� ����
void saveNewpromise(char *DBname,struct structPromise *newPromise);									//����� �����ؼ� txt ������ ����� �Լ�
void selectName(char *DBname,struct structPromise *newPromise);											//��Ӹ��� �Է¹޴� �Լ�
int searchName(char *name,int count,struct structPromise newPromise,int CombineTimetable[5][13]);		//�̸� �˻��ϴ� �Լ�
int selectFriends(char *DBname,int CombineTimetable[5][13],struct structPromise *newPromise);			//�Բ��� ȸ������ �Է��ϰ� �˻��Լ� ���ؼ� �˻��� �����ϴ� �Լ�
void selectTime(int CombineTimetable[5][13],structPromise *newPromise,int dayofWeek);		//  �ð� �Է¹޴� �Լ�
int selectDate(int CombineTimetable[5][13],structPromise *newPromise);  //  ��¥�Է¹޴� �Լ�


//������
void moneyShare1(structMember *s);  //�������ּ��� ����
void moneyShare2();  //�������� ��� ���� ���

//�������� ���̴� �͵�
void gotoxy(int x, int y);  //��ǥ����
void screenBorderDraw(); //��üȭ��Ʋ����Լ�
void listBorderDraw(int x, int y); //�޴�Ʋ����Լ�
void listBorderDraw1(int x, int y);  //��Ӹ���ƮƲ���
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