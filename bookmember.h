#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

struct bookmember
{
        char name[15];        // 이름
        char ID[30];         // 아이디
        char sex[10]; //성별
        char age[10];//나이				
       


          struct bookmember *m_next; // 다음노드 가리킴                             < 출력화면 > - 리스트4개 삽입후 출력
};

struct bookmember *root=0;  // 헤드

struct bookinfo{//책정보 구조체

char title[41];//제목
char auth[31];//저자
char pub[31];//출판사
int status;//도서상태 식별
int booknum;//도서번호

};
void memberset();
void setting();
