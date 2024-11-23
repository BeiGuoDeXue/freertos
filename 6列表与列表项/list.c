#include <stdio.h>
#include <stdlib.h>
#include "list.h"

ListStatus GetElement(LinkList *L, int i, ElemType *e) {
    int j;
    LinkList p;
    
    // 检查输入参数的合法性
    if (!L || !(*L) || !e || i < 1) {
        return LIST_ERROR; 
    }
    
    p = (*L)->next;
    j = 1;
    while(p && j<i) { /* p不为空，或者计数器不等于i时，继续循环 */
        p = p->next;
        ++j;
    }
    
    if (!p || j>i) {
        return LIST_ERROR;
    }
    *e = p->data;
    return LIST_OK;
}


ListStatus ListInsert(LinkList *L, int i, ElemType e) {
    int j = 1;
    LinkList p,s;
    p = *L;
    // 检查输入参数i的合法性
    if (i < 1) {
        return LIST_ERROR;
    }
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    if (!p || j>i) {
        return LIST_ERROR;
    }
    s = (LinkList)malloc(sizeof(Node));
    // 检查内存分配是否成功
    if (!s) {
        return LIST_ERROR;
    }
    s->data = e;
    s->next = p->next;
    p->next = s;
    return LIST_OK;
}


ListStatus ListDelete(LinkList *L, int i) {
    int j = 1;
    LinkList p,q;
    p = *L;

    while (p && j < i) {
        p = p->next;
        ++j;
    }
    // j是i的上一个节点，i是p->next，因此这里判断!(p->next)
    if (!p || !(p->next) || j > i) {
        return LIST_ERROR;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    return LIST_OK;
}



void CreateListHead(LinkList *L, int n) {
    int i;
    // *L这里解一层指针
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for (int j = 0; j < n; j++) {
        LinkList p = (LinkList)malloc(sizeof(Node));
        p->data = 0;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}


void CreateListTail(LinkList *L, int n) {
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    LinkList r = *L;
    for(int i = 0; i < n; i++) {
        LinkList p = (LinkList)malloc(sizeof(Node));
        p->data = i;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

