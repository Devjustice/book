#include <stdio.h>
#include <string.h>

 

//추후 유지보수를 편히 하기위해 100이란 숫자를
//MAX_num으로 설정, 100을 200으로 바꾸면
//MAX_num은 200이 됨
#define MAX_num 200

 

//사용자의 정보를 저장하는 구조체
typedef struct{
     char name[100];
     char auther[100];
     char publisher[100];
     char genre[100];
     char loan[10];
}BOOK;

 
 

int saveFile(BOOK* ptr, int* num);
int openFile(BOOK* ptr, int* num);
void insert(BOOK* ptr, int* num);
int deleted(BOOK* ptr, int* num);
int search(BOOK* ptr, int* num);
void printAll(BOOK* ptr, int* num);

 

int main(void){
     int input;
     BOOK BOOK[MAX_num]; //사용자 정보를 저장할 구조체 배열
     int books = 0; //저장된 BOOK수

 

     openFile(BOOK, &books);//저장된 데이터를 불러오는 함수

 

     //메뉴 선택
     while (1){
          printf("*****도서관리***** \n");
          printf("1. 책등록 \n");
          printf("2. 책삭제 \n");
          printf("3. 검색 \n");
          printf("4. 목록확인 \n");
          printf("5. 저장 후 종료하기 \n");

          printf("번호를 입력하세요: ");
          scanf("%d", &input);

 
 

          if (input == 1){
               printf("\n[책등록] \n");
               insert(BOOK, &books);
          }
          else if (input == 2){
               printf("\n[책삭제] \n");
               deleted(BOOK, &books);
          }
          else if (input == 3){
               printf("\n[검색] \n");
               search(BOOK, &books);
          }
          else if (input == 4){
               printf("\n[목록확인] \n");
               printAll(BOOK, &books);
          }
          else if (input == 5){
               saveFile(BOOK, &books);
               return 0;
          }
          else
               printf("\n잘못된 입력! \n\n");
         }

return 0;

}

 

//데이터를 파일에 저장하는 함수
int saveFile(BOOK* ptr, int* num){

     if (*num > 0){
          int i, state;
          FILE* fp = fopen("BOOKInfo.txt", "wt");

 
 

          /* fopen함수는 오류발생시 NULL을 리턴하므로
          파일 개방 중 오류발생시 프로그램을 종료 */
          if (fp == NULL){
               printf("File Open Error!\n");
               return 1;
          }

 

          //구조체 배열에 저장된 데이터를 파일에 저장
          //줄바꿈으로 구분하여 저장
          for (i = 0; i < *num; i++){
               fprintf(fp, "%s %s %s %s", ptr[i].name, ptr[i].auther,ptr[i].publisher,ptr[i].genre);
               fputc('\n', fp);
          }

 

          /* fclose함수는 종료시 오류가 발생하면
          0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
          안내후 프로그램을 종료 */
          state = fclose(fp);
          if (state != 0){
               printf("파일 입력이 닫히지 않음!\n");
               return 1;
          }
          printf("\n  입력한 값이 저장됩니다. \n");
          return 0;
     }

 
     else{
          printf("\n 종료됩니다. \n");
          return 0;
     }
}

 

//파일로부터 데이터를 불러오는 함수
int openFile(BOOK* ptr, int* num){
     int state;
     char temp;
     FILE* fp = fopen("BOOKInfo.txt", "rt");

 

     if (fp == NULL){
          printf("파일이 열리지 않습니다!\n");
          return 1;
     }

 

     //파일에 저장된 데이터를 구조체 배열에 저장
     while (1){
          fscanf(fp, "%s %s %s %s", ptr[*num].name, ptr[*num].auther,ptr[*num].publisher,ptr[*num].genre);
          if (feof(fp) != 0)
               break;
          (*num)++;
     }

 

     /* fclose함수는 종료시 오류가 발생하면
     0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
     안내후 프로그램을 종료 */
     state = fclose(fp);
     if (state != 0){
         printf("파일 입력이 닫히지 않음!\n");
          return 1;
     }

     return 0;
}

 

//사용자의 정보를 삽입하는 함수
void insert(BOOK* ptr, int* num){

     //유저정보가 꽉 차지 않으면
     if (*num < MAX_num){
          printf("책이름을 입력해주세요: ");
          scanf("%s", ptr[*num].name);
          printf("저자이름을 입력해주세요: ");
          scanf("%s", ptr[*num].auther);
          printf("출간사를 입력해주세요: ");
          scanf("%s", ptr[*num].publisher);
          printf("장르를 입력해주세요: ");
          scanf("%s",ptr[*num].genre);
 
          (*num)++;
          printf("  정보가 입력되었습니다.\n\n");
     }
     //유저 정보가 꽉 차면
     else
          printf("  모든데이터가 차있습니다. 삭제해주세요 \n\n");
    }

 

//사용자의 정보를 삭제하는 함수
int deleted(BOOK* ptr, int* num){
     char name[30];
     int i, j;

 

     //유저 정보가 한개라도 남아있으면
     if (*num > 0){
          printf("삭제할 책 제목을 입력해주세요: ");
          scanf("%s", name);

 

          for (i = 0; i < MAX_num; i++){
           //문자열이므로 비교하기위해 strcmp사용
               if (strcmp(name, ptr[i].name) == 0){

                    (*num)--;
                    printf("  책이 제거 되었습니다. \n\n");

                    //데이터가 가득 차지 않았다면
                    if (i != MAX_num - 1){
                         for (j = i; j < MAX_num; j++){
                              //문자열이므로 strcpy를 사용하여 데이터 복사
                              strcpy(ptr[j].name, ptr[j + 1].name);
                              strcpy(ptr[j].auther, ptr[j + 1].auther);
                              strcpy(ptr[j].publisher, ptr[j + 1].publisher);               
                              strcpy(ptr[j].genre, ptr[j + 1].genre);
                         }
                         //구조체 배열의 마지막을 NULL로 바꿈
                         *ptr[MAX_num - 1].name = NULL;
                         *ptr[MAX_num - 1].auther = NULL;
                         *ptr[MAX_num - 1].publisher = NULL;
                         *ptr[MAX_num - 1].genre = NULL;
                    }


                        //데이터가 가득 찼다면
                    else{
                         //구조체 배열의 마지막을 NULL로 바꿈
                         *ptr[MAX_num - 1].name = NULL;
                         *ptr[MAX_num - 1].auther = NULL;
                         *ptr[MAX_num - 1].publisher = NULL;
                         *ptr[MAX_num - 1].genre = NULL;
                    


}
               return 0;
               }
          }
          printf("발견되지 않았습니다. \n\n");
          return 0;
     }


     //저장된 유저 정보가 없다면
     else{
          printf("  그런 책은 없습니다. \n\n");
          return 0;
     }
}

 

//사용자의 정보를 검색하는 함수
int search(BOOK* ptr, int* num){
     char name[30];
     int i;

 

     //저장된 데이터가 있다면
     if (*num > 0){
          printf("조회하실 책을 입력해주세요: ");
          scanf("%s", name);

 
 

          for (i = 0; i < MAX_num; i++){
               //strcmp는 문자열이 일치할때 0을 반환
               //0은 C언어에서 거짓을 의미
               //그러므로 ! 을 붙여 참으로 변경하여 실행
               if (!strcmp(name, ptr[i].name)){

                    printf("책제목 : %3s\n", ptr[i].name);
                    printf("저자 : %3s\n", ptr[i].auther);
                    printf("출간사 : %3s\n", ptr[i].publisher);
                    printf("장르 : %3s\n", ptr[i].genre);
                    printf("  책이 발견됨 \n\n");
                    return 0;
               }
          }
      printf("발견되지 않았습니다. \n\n");
      return 0;
     }
     else{
         printf("  그런 책은 없습니다. \n\n");
          return 0;
     }
}

 

//저장된 모든 이름과 전화번호 정보를 출력하는 함수
void printAll(BOOK* ptr, int* num){
     int i = 0;

     if (*num > 0){
          for (i = 0; i < *num; i++){
               printf("책제목 : %s\t\t", ptr[i].name);
               printf("저자 : %s\t\t", ptr[i].auther);
               printf("출간사 : %s\t\t", ptr[i].publisher);
               printf("장르 : %s\n", ptr[i].genre);



          }
          printf("  모든 정보를 리스트로 불러왔습니다. \n\n");
     }
     else
          printf("  책장이 비어있습니다. \n\n");
}


