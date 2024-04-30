#include<stdio.h>
#include<stdlib.h>

typedef struct listNode* link;
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;

headNode* initialize(headNode* h);
int insertNode(headNode* h, int key);
void printList(headNode* h);

int main(){
    headNode *headnode=NULL;
    headnode = initialize(headnode);
    
    insertNode(headnode,5);
    printList(headnode);

    insertNode(headnode,4);
    printList(headnode);

    insertNode(headnode,4);
    printList(headnode);

    insertNode(headnode,8);
    printList(headnode);

    insertNode(headnode,3);
    printList(headnode);

    free(headnode);
    
}

headNode* initialize(headNode* h) {
	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    int i,count=0;

    node->key=key;
    if(h->first==NULL){
        h->first=node;
        node->link=NULL;
        return 0;
    }
    
	listNode* p;
	p = h->first;
	
	for(i=0;p!=NULL;i++){
        if(p->key<=key){
            if(p->link==NULL){
                p->link=node;
                node->link=NULL;
                return 0;
            }
            p = p->link;
        }else{
            if(i==0){
                h->first=node;
                node->link=p;
                return 0;
            }
            count=i-1;
            break;
        }
		
	}

	p = h->first;
	for(i=0;p!=NULL;i++){
		if(count==i){
			node->link=p->link;
			p->link=node;
			return 0;
		}else{
			p = p->link;
		}
	}
    
    	
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