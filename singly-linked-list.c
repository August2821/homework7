/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);//초기화
int freeList(headNode* h);//list 동적할당 해제

int insertFirst(headNode* h, int key);//list의 맨 앞쪽에 노드 추가
int insertNode(headNode* h, int key);//노드 추가
int insertLast(headNode* h, int key);//list의 맨 뒤쪽에 노드 추가

int deleteFirst(headNode* h);//첫 번째 노드 삭제
int deleteNode(headNode* h, int key);//노드 하나 삭제
int deleteLast(headNode* h);//마지막 노드 삭제
int invertList(headNode* h);//list를 역순으로 배열

void printList(headNode* h);//현재 list 상태

int main()
{
	char command;
	int key;
	headNode* headnode=NULL; //headnode는 null로 초기화

	do{
		printf("\n[----- [김민경] [2023041054] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
	//q나 Q가 입력되면 종료

	return 0;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	//node들 동적할당 해제 후 headnode 동적할당 해제
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
    int i,count=0;

	//어디에 node를 삽입하든 node에 key 값을 넣어줘야 함
    node->key=key;

	//h->first가 NULL이면 list에 node가 없음
	//첫 번째 노드 추가
    if(h->first==NULL){
        h->first=node;
        node->link=NULL;
        return 0; //node를 추가했기 때문에 함수가 끝나야 함
    }
    
	//h->first가 NULL이 아니면
	listNode* p;
	p = h->first;
	
	for(i=0;p!=NULL;i++){
		//p->key가 key보다 작거나 같으면
        if(p->key<=key){
			//p->key가 key와 같고 p가 첫 번째 노드라면
			if(p->key==key && i==0){
				//첫 번째 노드 바로 뒤에 노드 삽입
                node->link=p->link;
				p->link=node;
				return 0; //노드가 삽입 됐으므로 함수 종료
			}
			//p가 이동하다가 마지막 node가 되면
			//p->link가 NULL이고 p->key가 key보다 작거나 같으면
            if(p->link==NULL){
				//마지막 노드 뒤에 노드 삽입
                p->link=node;
                node->link=NULL;
				//삽입 된 노드가 마지막 노드이므로 node->link에 NULL 넣음
                return 0; //노드가 정상적으로 추가 됐으므로 함수 종료
            }
			//위에 조건에 해당하지 않으면 다음 노드로 이동
            p = p->link;
        }else{
		//p->key가 key보다 크면
            if(i==0){
				//p->key가 key보다 크고 첫 번째 노드라면
				//h->first가 node를 가리킴, 첫 번째 노드 변경
				//node는 p를 가리켜서 다음 노드를 가리킬 수 있도록
                h->first=node;
                node->link=p;
                return 0;
            }
			//p->key가 key보다 크고 첫 번째 노드가 아니면 count는 입력받은 key보다 큰값이 나오는 노드 바로 앞
			//입력받은 key보다 큰값이 나오는 노드 바로 앞을 찾았기 때문에 for문은 멈춰야 됨
            count=i-1;
            break;
        }
		
	}

	//p를 첫 번째 노드를 가리키도록 변경
	//이거 안 하면 입력받은 key보다 큰값이 나오는 노드 바로 앞을 찾을 수 없음
	p = h->first;
	for(i=0;p!=NULL;i++){
		//count는 입력받은 key보다 큰값이 나오는 노드 바로 앞을 알려줌
		//p가 count번째 있는 노드라면
		if(count==i){
			//입력받은 key보다 큰값이 나오는 노드 바로 앞에 node 추가
			node->link=p->link;
			p->link=node;
			return 0;
		}else{
			//if 조건에 해당하지 않으면 p는 다음 노드로
			//이거 없으면 제대로 동작하지 않음, 다음 노드로 이동을 안 하기 때문
			p = p->link;
		}
	}
    
    	
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	//노드 추가 해야 되므로 노드 하나 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	int i;

	//노드에 key값 넣기
	node->key=key;

	//노드가 없으면 첫 번째에 노드 추가
    if(h->first==NULL){
        h->first=node;
        node->link=NULL;
        return 0;
    }

	//headnode 값은 바뀌면 안되기 때문에 p를 이용하여 노드에 접근함
	p = h->first;
	//p가 null이 될 때까지 반복
	for(i=0;p!=NULL;i++){
		//마지막에 노드 추가하므로 마지막 노드 찾기
		//마지막 노드 link에는 null이 들어있음
		if(p->link==NULL){
			//p는 마지막 노드, node는 p 뒤에 추가할 노드
			p->link=node;
			node->link=NULL;
			return 0;
		}
		//다음 노드로 이동
		p=p->link;
	}
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p=h->first;
	listNode* prev = NULL;

	//h->first가 null이면 삭제할 값이 없으므로 에러 출력
	if(h->first==NULL) {
		printf("\n====에러====\n");
		return 0;
	}

	//첫 번째 노드 link가 null이면
	if(p->link==NULL) {
		//h->first는 null이어야 함
		//노드가 없기 때문
		h->first=NULL;
		//p 동적할당 해제
		free(p);
		return 0;
	}

	//위에 조건에 모두 해당하지 않으면
	//prev는 첫 번째 노드
	prev = p;
	//p는 다음 노드로 이동
	p=p->link;
	//동적할당 해제
	free(prev);
	//첫 번째 노드를 해제 했기 때문에 h->first가 그 다음 노드를 가리키도록
	h->first=p;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* prev = h->first;
	listNode* p = h->first;
	int i,count=0;

	//삭제할 노드가 없으면 에러
	if(h->first==NULL) {
		printf("\n====에러====\n");
		return 0;
	}

	//첫 번째 노드가 null이면
	if(prev->link==NULL) {
		//h->first를 null로, 노드가 없기 때문
		h->first=NULL;

		//첫 번째 노드 동적할당 해제
		free(prev);
		return 0;
	}

	//key 값을 가지고 있는 노드 바로 앞 노드를 찾아야 함
	//삭제할 노드 찾기
	for(i=0;prev!=NULL;i++){
		if(prev->key==key){
			//삭제할 노드 바로 앞 노드를 찾기 위해 i=삭제할 노드, i-1=삭제할 노드 바로 앞 노드
			//삭제할 노드 바로 앞 노드와 뒤 노드를 이어야 되기 때문에
			//삭제할 노드 바로 앞 노드를 찾는 것
			count=i-1;
			break;
			//찾으면 멈춰야 함
		}
		//찾을 때 까지 계속 다음 노드로 이동
		prev=prev->link;
	}

	//prev=삭제할 노드
	//p=삭제할 노드 바로 앞 노드
	for(i=0;p!=NULL;i++){
		if(count==i){
			//삭제할 노드 바로 앞 노드 link에
			//삭제할 노드 바로 뒤 노드 주소 넣음, 다음 노드를 가리킬 수 있도록
			//null이어도 null값이 삭제할 노드 바로 앞 노드 link에 들어감
			p->link=prev->link;

			//그런 다음 삭제할 노드 동적할당 해제
			free(prev);
			return 0;	
		}
		//다음 노드로
		p=p->link;
	}
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* prev = h->first;
	int i,count=0;
	
	//삭제할 노드가 없다면 에러
	if(h->first==NULL) {
		printf("\n====에러====\n");
		return 0;
	}

	//첫 번째 노드의 link가 null이면 노드가 하나 라는 것
	if(prev->link==NULL) {
		//h->first는 null이어야 함
		//노드가 없기 때문
		h->first=NULL;

		//삭제할 노드 동적할당 해제
		//free 안 하면 더 이상 prev에 접근할 수 없음
		free(prev);
		return 0;
	}

	//마지막(삭제할) 노드 찾기
	for(i=0;prev!=NULL;i++){
		if(prev->link==NULL){
			count=i-1;
		}
		prev=prev->link;
	}
	//동적할당 해제해서 삭제
	free(prev);

	//삭제된 노드 바로 앞 노드를 찾아서 link를 NULL로 바꿔줘야 함
	//마지막 노드가 삭제되서 삭제된 노드 바로 앞 노드가 마지막 노드가 됨
	prev=h->first;
	for(i=0;prev!=NULL;i++){
		if(count==i){
			prev->link=NULL;	
			return 0;	
		}
		prev=prev->link;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* a;
	listNode* b;
	listNode* c;

	a=h->first;
	b=NULL;
	c=NULL;

	//a가 null이 될 때까지 반복
	while (a!=NULL){
		//a는 계속 다음 노드로 넘어가게 됨
		//그래서 a가 null이면 모든 노드를 재배치(역순) 되었단 의미
		c=b;
		b=a;
		a=a->link;
		b->link=c;
	}
	//h->first에 마지막 노드인 b를 연결하면 역순 완료
	h->first=b;
	
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	//h가 null이면 노드가 없음
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;
	//모든 노드 출력
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		
		//다음 노드로 이동
		p = p->link;
		i++;
	}
	//현재 노드들 개수 i 출력
	printf("  items = %d\n", i);
}

