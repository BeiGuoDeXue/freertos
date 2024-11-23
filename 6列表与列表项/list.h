#ifndef __LIST__
#define __LIST__

typedef int ElemType;

typedef struct Node {
    int data;           // 数据域
    struct Node* next;  // 指针域
} Node;

typedef enum {
    LIST_ERROR = 0,
    LIST_OK = 1,
} ListStatus;

typedef struct Node *LinkList;    /*定义LinkList*/

ListStatus GetElement(LinkList *L, int i, ElemType *e);
ListStatus ListInsert (LinkList *L, int i, ElemType e);
ListStatus ListDelete(LinkList *L, int i);
void CreateListHead(LinkList *L, int n);
void CreateListTail(LinkList *L, int n);

Node* findNode(Node* head, int data);
Node* reverseList(Node* head);
int getLength(Node* head);
int hasLoop(Node* head);
void printList(Node* head);
void freeList(Node* head);

#endif