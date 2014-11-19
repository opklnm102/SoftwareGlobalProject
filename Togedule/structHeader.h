#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include <time.h>
#include<malloc.h>
#include <windows.h>

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

//char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"}; // ��������.

extern char dayOfWeek[5][4]; // ��������.

/*-------------------------------�Լ���������--------------------------------*/
//�α��ΰ���
void login(structMember *s);  //�α���
void membership();  //ȸ������
void mainMenu(char *loginName);  //�α��� �� ���θ޴�
void pwFind();  //��й�ȣ ã��

//�ð�ǥ����
void timetableMenu(); //�ð�ǥ�޴��Լ�->�ð�ǥ ����
void timetableDraw(); //�ð�ǥ�׸����Լ�
void saveTimetalbe(structSubject* subjectPointer, int subjectSum); //�ð�ǥ txt�� �����ϴ� �Լ�
void InputSubjectCnt(); //��~�� ���񰹼� �Է� �Լ�
void InputSubjectNameAndClass( int* SubjectCntOfday, int subjectSum) ; // �̸�/���� �Է��Լ�
void modifyTimetable(); //�ð�ǥ�����Լ�
void removeTimetable(); //�ð�ǥ�����Լ�(�ð�ǥtxt���ϻ���)

//��Ӱ���
void promise(char *loginName);  //��� ����

//������
void moneyShare();  //�������ּ��� ����

//�������� ���̴� �͵�
void gotoxy(int x, int y);  //��ǥ����
void screenBorderDraw(); //��üȭ��Ʋ����Լ�
void listBorderDraw(); //�޴�Ʋ����Լ�


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