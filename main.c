#include"bookmember.h"

int main(){
int ipt=0;
char pw[10]={"admin"};
char a[10];
printf("도서관에 오신것을 환영합니다\n");
printf("책의 정보를 불어오는 중입니다.\n");
printf("관리자모드는 1번.\n");
//printf("도서조회는 2번.\n");
scanf("%d",&ipt);
switch(ipt){
case 1: 
printf("비밀번호를 입력하세요\n");
scanf("%s",a);
if(strcmp(a,pw) == 0){printf("0");


memberset();}else{

puts("비밀번호 오류");
break;}


//case 2: 
default :break;
}

return 0;
}






// 이름과 아이디 입력받는 함수
int input(char *pname, char *pid,char *psex,char *page)  // 이름과 아이디를 입력받음
{
        printf("\n이름 : ");
        scanf("%s", pname);
        printf("\n아이디: ");
        scanf("%s", pid);
        printf("\n성별: ");
        scanf("%s", psex);
        printf("\n나이: ");
        scanf("%s", page);
        
        return 0;
}


// 추가
void add(char *pname, char *pid,char *psex,char *page) // 인자로 이름과 아이디 받음
{
        struct bookmember *p;   // 임의의 p노드를 만들어서 p노드가 헤드를 가리키게함
        struct bookmember *pnew;  // 추가할 새노드만듬
        p=root;
 
        while(p->m_next)    // p노드가 하나씩 다음 노드로 이동 하면서 끝에서 멈춤
         p=p->m_next;    
               // 현제 p노드는 노드의 끝

        pnew=(struct bookmember*)malloc(sizeof(struct bookmember)); // 동적할당 으로 새 노드메모리 할당

        strcpy(pnew->name, pname);       // 새노드에 이름복사
        strcpy(pnew->ID, pid);               // 새노드에 아이디 복사
        strcpy(pnew->sex, psex);       // 새노드에 이름복사
        strcpy(pnew->age, page);               // 새노드에 아이디 복사

        pnew->m_next=NULL;                    // 새노드다음은 끝을 의미하는 NULL 
        p->m_next=pnew;                          // 현제 끝을 가리키는 p노드 다음에 새노드 연결
}

 

// 검색
void find()
{
        struct bookmember *p;   // 임의의 노드 p생성
        char fname[15];    // 찾을 이름을 받을 변수

        printf("찾을 이름 입력 : ");
        scanf("%s", fname);

        p=root;      // 임의의 노드p가 헤드를 가리킴
      
        while(1)     // 무한루프
        {
                if(strcmp(p->name, fname)==0) // 임의의노드가 가리키는 노드의 이름과 입력한 이름이 같으면
                {
                        printf("같은이름발견\n");
                        printf("이름 : %s, 아이디 : %s\n", p->name, p->ID);
                        return;      // 찾고 종료

                }
  
                else if(p->m_next==NULL)   // p노드가 끝에 다으면
                {
                        printf("찾는 이름이 없습니다.\n"); 
                        return;      // 않 찾고 종료
                }
                p=p->m_next;      // p노드를 계속 이동 시킴.
    
        }

        printf("\n");
}


//삭제
void del()
{                                       // ex) bef   p   
        struct bookmember *p ,*temp, *before;  // [ ]->[ ]->[ ] 
        char dname[15];      // 삭제할 이름

        printf("삭제할 이름 입력 : ");
        scanf("%s", dname);

        p=root;        // 임의의 노드 p는 헤드
        p=p->m_next;       // 임의의 노드 p는 헤드다음.
        before = root;      // before 헤드
        while(p!=0)
        {
                if(strcmp(p->name, dname)==0)
                {
                        temp=p;      
                        before->m_next = p->m_next;  // p노드를 지우기위해 p노드의 다음노드 정보를 before노드 다음으로
                        p = before;     // 지운노드 전노드가 p가 됨
                        free(temp);     // p 의 동적할당 해제
                        printf("%s : 삭제함", dname);
                        return;
                }
                before = p;      // p가 다시 before가 되고
                p = p->m_next;     // before 남기구 p는 다시 다음노드로
        }
}

 

// 출력
void display()
{
        struct bookmember *p;
        p=root;
        p=p->m_next;

        while(p!=0)   // 임이의 p노드를 이동시키면서 연결된 노드 전부 출력
        {
                printf("\n이름: %s 아이디: %s\n성별:%s  \t나이:%s ", p->name, p->ID,p->sex,p->age);
                p=p->m_next;
        }
        printf("\n");
}

 

// 정렬
void sort(char *pname, char *pid,char *psex,char *page)
{
        struct bookmember *p;   // 임의의 p노드를 만들어서 p노드가 헤드를 가리키게함
        struct bookmember *pnew;  // 추가할 새노드만듬
        struct bookmember *before;

        p=root->m_next;      // p를 루트다음.
        before = root;      // before 를 루트
 
        pnew=(struct bookmember*)malloc(sizeof(struct bookmember)); // 동적할당 으로 새노드 메모리영역 만듬 
        strcpy(pnew->name, pname);       // 새노드에 이름복사
        strcpy(pnew->ID, pid);        // 새노드에 아이디 복사
        strcpy(pnew->name, psex);       // 새노드에 성별복사
        strcpy(pnew->ID, page);        // 새노드에 나이 복사
        if(root->m_next == NULL)     // 노드가 없으면 ( 루트다음이 널이면)
        {
                // 머리다음에 새 노드넣음
                root->m_next = pnew;
                pnew->m_next = NULL;
                return;
        }

        while(1)   
        {
                if(strcmp(pnew->name,p->name) < 0 )  // 새노드의 이름이 임의의노드보다 작으면
                {
                        pnew->m_next = p;      // 그 임의의 노드 p와 before노드 사이에 새노드 끼움
                        before->m_next = pnew;
                        return;
                }

                if(p->m_next==NULL)
                {        // NULL앞에 ( 노드끝에 ) 새노드 끼움
                        pnew->m_next = NULL;      
                        p->m_next = pnew;
                        return;
                }
                before = p;      // p가 다시 before가 되고
                p = p->m_next;     // before 남기구 p는 다시 다음노드로
        }
}

 

void memberset()
{
        // 변수
        int menu;   // 메뉴
        char name[15];  // 이름
        char ID[30];  // 번호
        char sex[10]; //성별
        char age[10];//나이			



 // 초기화
        root=(struct bookmember*)malloc(sizeof(struct bookmember)); // 루트노드(헤드)
        strcpy(root->name, "ROOT");      // 헤드의 이름은 루트
        strcpy(root->ID, "ROOT");      // 루트의 아이디도 루트
        strcpy(root->sex, "ROOT");      // 헤드의 성별은 루트
        strcpy(root->age, "ROOT");      // 루트의 나이도 루트


        root->m_next=NULL;        // 루트의 다음은 NULL

        while(1)
        {
        	//관리자랑 회원으로 들어갈 선택문 만들기

        	//회원모드에 ID랑 비번 입력란 만들기

        	//이거는 관리자모드에 들어갈 사항
        	     printf("\n");
                printf("--------------\n");
                printf("-  1. 회원등록   -\n");
                printf("-  2. 회원삭제   -\n");
                printf("-  3. 회원검색   -\n");
                printf("-  4. 회원출력   -\n");
                printf("-  5. 회원정렬   -\n");
                printf("-  6. 종료   -\n");
                printf("--------------\n");
                printf("선택 : ");
                scanf("%d", &menu);

                if(menu==6){main();}
                switch(menu)
                {
                       case 1:  // 삽입
                               input(name, ID,sex,age);
                               add(name, ID,sex,age);
                               break;
                       case 2:  //삭제 
                               del();
                               break;
                       case 3:  // 검색
                               find();
                               break;
                       case 4:  // 출력
                               display();
                               break; 
                       case 5:  // 정렬
                               input(name, ID,sex,age);
                               sort(name,ID,sex,age);
                               break;
                      
                              default:
                               puts("잘못된 입력!");
                               break;
                }
        }

 
}
