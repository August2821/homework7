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
    
    insertNode(headnode,1);
    printList(headnode);

    insertNode(headnode,2);
    printList(headnode);

    insertNode(headnode,4);
    printList(headnode);

    insertNode(headnode,8);
    printList(headnode);

    // insertNode(headnode,3);
    // printList(headnode);

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
    link* x;
    if(h->first==NULL){
        h->first=node;
        node->key=key;
        node->link=NULL;
    }
    else{
        node->key=key;
        listNode* p;
        p = h->first;
        int max=p->key;
        
        while(p != NULL) {
            if(p->link==NULL){
                p->link=node;
                node->link=NULL;
                return 0;
            }else{
                if(p->key==2){
                    node->link=p->link;
                    p->link=node;
                    
                    return 0;
                }else{
                    p = p->link;
                }
            }
	    }
    }
    
    	
}

// int insertFirst(headNode* h, int key) {

// 	listNode* node = (listNode*)malloc(sizeof(listNode));
// 	node->key = key;

// 	node->link = h->first;
// 	h->first = node;

// 	return 0;
// }

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