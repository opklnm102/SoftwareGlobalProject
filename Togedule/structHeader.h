#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//B(�ڷΰ���), X(����)�� �Է��ؾ��ϱ� ������ ���� char ������ �Է��� �޾ƾ��Ѵ�.

//ȸ�� ����ü
typedef struct structMember{  
	char name[13];  //ȸ���̸�
	char ID[7];  //�й�
	char password[13];  
	char backupPassword[13];  //�����ڵ�
}structMember;

//��� ����ü
typedef struct structPromise{ 
	char name [41];  //��Ӹ�
	char *promisePlace;  //������ �̸��� �𸣱� ������ DB�� ���ڿ��� ����Ų��
    char promiseTime[6];  //��ӽð�
	char Promisedate[10];  //��ӳ�¥
	char **promiseFriendsName;  //�ο����� �Է��� �޾� �����Ҵ� {���赿��, ���̼���}
	//��� ������ ��������
}structMember;

//���� ����ü
typedef struct structSubject{  
	char subjectName[15];  //�����̸�
	char subjectClass[10];  //�Է¹޴� ���񱳽�  ->1,2,3 ->�Լ��� ó���ؾ���.
}structSubject;

//�ð�ǥ ����ü
typedef struct structTimetable{  //13���� -> 13�� �Է��ϱ� ������ 2��
	structSubject timetable[5][13];  
}structTimetable;

//��� ����ü
typedef struct structCost{
	char cost;
}structCost;

char dayOfWeek[5][4] = {"��", "ȭ", "��", "��", "��"}; // ��������.
