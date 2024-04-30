/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);//�ʱ�ȭ
int freeList(headNode* h);//list �����Ҵ� ����

int insertFirst(headNode* h, int key);//list�� �� ���ʿ� ��� �߰�
int insertNode(headNode* h, int key);//��� �߰�
int insertLast(headNode* h, int key);//list�� �� ���ʿ� ��� �߰�

int deleteFirst(headNode* h);//ù ��° ��� ����
int deleteNode(headNode* h, int key);//��� �ϳ� ����
int deleteLast(headNode* h);//������ ��� ����
int invertList(headNode* h);//list�� �������� �迭

void printList(headNode* h);//���� list ����

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("\n[----- [��ΰ�] [2023041054] -----]\n");
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

	return 0;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
    int i,count=0;

	//��� node�� �����ϵ� node�� key ���� �־���� ��
    node->key=key;

	//h->first�� NULL�̸� list�� node�� ����
	//ù ��° ��� �߰�
    if(h->first==NULL){
        h->first=node;
        node->link=NULL;
        return 0; //node�� �߰��߱� ������ �Լ��� ������ ��
    }
    
	//h->first�� NULL�� �ƴϸ�
	listNode* p;
	p = h->first;
	
	for(i=0;p!=NULL;i++){
		//p->key�� key���� �۰ų� ������
        if(p->key<=key){
			//p->key�� key�� ���� p�� ù ��° �����
			if(p->key==key && i==0){
				printf("\n2\n");
				//ù ��° ��� �ٷ� �ڿ� ��� ����
                node->link=p->link;
				p->link=node;
				return 0; //��尡 ���� �����Ƿ� �Լ� ����
			}
			//p�� �̵��ϴٰ� ������ node�� �Ǹ�
			//p->link�� NULL�̰� p->key�� key���� �۰ų� ������
            if(p->link==NULL){
				printf("\n1\n");
				//������ ��� �ڿ� ��� ����
                p->link=node;
                node->link=NULL;
				//���� �� ��尡 ������ ����̹Ƿ� node->link�� NULL ����
                return 0; //��尡 ���������� �߰� �����Ƿ� �Լ� ����
            }
			//���� ���ǿ� �ش����� ������ ���� ���� �̵�
            p = p->link;
        }else{
		//p->key�� key���� ũ��
            if(i==0){
				//p->key�� key���� ũ�� ù ��° �����
				//h->first�� node�� ����Ŵ, ù ��° ��� ����
				//node�� p�� �����Ѽ� ���� ��带 ����ų �� �ֵ���
                h->first=node;
                node->link=p;
                return 0;
            }
			//p->key�� key���� ũ�� ù ��° ��尡 �ƴϸ� count�� �Է¹��� key���� ū���� ������ ��� �ٷ� ��
            count=i-1;
            break;
        }
		
	}

	//p�� ù ��° ��带 ����Ű���� ����
	//�̰� �� �ϸ� �Է¹��� key���� ū���� ������ ��� �ٷ� ���� ã�� �� ����
	p = h->first;
	for(i=0;p!=NULL;i++){
		//count�� �Է¹��� key���� ū���� ������ ��� �ٷ� ���� �˷���
		//p�� count��° �ִ� �����
		if(count==i){
			//�Է¹��� key���� ū���� ������ ��� �ٷ� �տ� node �߰�
			node->link=p->link;
			p->link=node;
			return 0;
		}else{
			//if ���ǿ� �ش����� ������ p�� ���� ����
			p = p->link;
		}
	}
    
    	
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	//��� �߰� �ؾ� �ǹǷ� ��� �ϳ� �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	int i;

	//��忡 key�� �ֱ�
	node->key=key;

	//��尡 ������ ù ��°�� ��� �߰�
    if(h->first==NULL){
        h->first=node;
        node->link=NULL;
        return 0;
    }

	//headnode ���� �ٲ�� �ȵǱ� ������ p�� �̿��Ͽ� ��忡 ������
	p = h->first;
	//p�� null�� �� ������ �ݺ�
	for(i=0;p!=NULL;i++){
		//�������� ��� �߰��ϹǷ� ������ ��� ã��
		//������ ��� link���� null�� �������
		if(p->link==NULL){
			//p�� ������ ���, node�� p �ڿ� �߰��� ���
			p->link=node;
			node->link=NULL;
			return 0;
		}
		//���� ���� �̵�
		p=p->link;
	}
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* p=h->first;
	listNode* prev = NULL;

	if(h->first==NULL) {
		printf("\n====����====\n");
		return 0;
	}

	if(p->link==NULL) {
		h->first=NULL;
		return 0;
	}

	prev = p;
	p=p->link;
	free(prev);
	h->first=p;

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* prev = h->first;
	listNode* p = h->first;
	int i,count=0;

	if(h->first==NULL) {
		printf("\n====����====\n");
		return 0;
	}

	if(prev->link==NULL) {
		h->first=NULL;
		return 0;
	}

	//������ ��� ã��
	for(i=0;prev!=NULL;i++){
		if(prev->key==key){
			//������ ��� �ٷ� �� ��带 ã�� ���� i=������ ���, i-1=������ ��� �ٷ� �� ���
			count=i-1;
			break;
		}
		prev=prev->link;
	}

	//prev=������ ���
	//p=������ ��� �ٷ� �� ���
	for(i=0;p!=NULL;i++){
		if(count==i){
			p->link=prev->link;
			free(prev);
			return 0;	
		}
		p=p->link;
	}
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* prev = h->first;
	int i,count=0;
	
	//list�� ����ִٸ� ����
	if(h->first==NULL) {
		printf("\n====����====\n");
		return 0;
	}

	//ù ��° ����� link�� null�̸� �� �̻� ��尡 ���ٴ� ��
	//���̽��� ���� ���� ó��
	if(prev->link==NULL) {
		h->first=NULL;
		return 0;
	}

	//������(������) ��� ã��
	for(i=0;prev!=NULL;i++){
		if(prev->link==NULL){
			count=i-1;
		}
		prev=prev->link;
	}
	//�����Ҵ� �����ؼ� ����
	free(prev);

	//������ ��� �ٷ� �� ��带 ã�Ƽ� link�� NULL�� �ٲ���� ��
	//������ ��尡 �����Ǽ� ������ ��� �ٷ� �� ��尡 ������ ��尡 ��
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
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* a;
	listNode* b;
	listNode* c;

	a=h->first;
	b=NULL;
	c=NULL;

	while (a!=NULL){
		c=b;
		b=a;
		a=a->link;
		b->link=c;
	}
	h->first=b;
	
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

