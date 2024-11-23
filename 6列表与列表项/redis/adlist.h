/* adlist.h - A generic doubly linked list implementation
 *
 * Copyright (c) 2006-Present, Redis Ltd.
 * All rights reserved.
 *
 * Licensed under your choice of the Redis Source Available License 2.0
 * (RSALv2) or the Server Side Public License v1 (SSPLv1).
 */

#ifndef __ADLIST_H__
#define __ADLIST_H__

/* 基础数据结构定义 */

// 链表节点结构
typedef struct listNode {
    struct listNode *prev;   // 前置节点
    struct listNode *next;   // 后继节点
    void *value;            // 节点值指针，可以指向任意类型的数据
} listNode;

// 链表迭代器结构
typedef struct listIter {
    listNode *next;         // 下一个要访问的节点
    int direction;          // 迭代方向
} listIter;

// 链表结构
typedef struct list {
    listNode *head;         // 表头节点
    listNode *tail;         // 表尾节点
    void *(*dup)(void *ptr);    // 节点值复制函数
    void (*free)(void *ptr);    // 节点值释放函数
    int (*match)(void *ptr, void *key);  // 节点值比较函数
    unsigned long len;      // 链表长度
} list;

/* 宏函数定义 */
// 返回链表长度
#define listLength(l) ((l)->len)
// 返回链表头节点
#define listFirst(l) ((l)->head)
// 返回链表尾节点
#define listLast(l) ((l)->tail)
// 返回节点的前置节点
#define listPrevNode(n) ((n)->prev)
// 返回节点的后继节点
#define listNextNode(n) ((n)->next)
// 返回节点的值
#define listNodeValue(n) ((n)->value)

// 设置链表节点值复制函数
#define listSetDupMethod(l,m) ((l)->dup = (m))
// 设置链表节点值释放函数
#define listSetFreeMethod(l,m) ((l)->free = (m))
// 设置链表节点值比较函数
#define listSetMatchMethod(l,m) ((l)->match = (m))

// 获取链表节点值复制函数
#define listGetDupMethod(l) ((l)->dup)
// 获取链表节点值释放函数
#define listGetFreeMethod(l) ((l)->free)
// 获取链表节点值比较函数
#define listGetMatchMethod(l) ((l)->match)

/* 函数原型 */
// 创建一个新的链表
list *listCreate(void);
// 释放整个链表
void listRelease(list *list);
// 清空链表中的所有节点
void listEmpty(list *list);
// 在链表头部添加节点
list *listAddNodeHead(list *list, void *value);
// 在链表尾部添加节点
list *listAddNodeTail(list *list, void *value);
// 在指定节点的前或后插入新节点
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
// 删除链表中的指定节点
void listDelNode(list *list, listNode *node);
// 获取链表迭代器
listIter *listGetIterator(list *list, int direction);
// 通过迭代器返回下一个节点
listNode *listNext(listIter *iter);
// 释放链表迭代器
void listReleaseIterator(listIter *iter);
// 复制整个链表
list *listDup(list *orig);
// 查找链表中匹配给定key的节点
listNode *listSearchKey(list *list, void *key);
// 返回链表在给定索引上的节点
listNode *listIndex(list *list, long index);
// 将迭代器的方向设置为从头到尾
void listRewind(list *list, listIter *li);
// 将迭代器的方向设置为从尾到头
void listRewindTail(list *list, listIter *li);
// 将链表的尾节点移动到头部
void listRotateTailToHead(list *list);
// 将链表的头节点移动到尾部
void listRotateHeadToTail(list *list);
// 将链表o接合到链表l的尾部
void listJoin(list *l, list *o);
// 初始化节点的值和指针
void listInitNode(listNode *node, void *value);
// 将已分配的节点链接到链表头部
void listLinkNodeHead(list *list, listNode *node);
// 将已分配的节点链接到链表尾部
void listLinkNodeTail(list *list, listNode *node);
// 从链表中解除节点链接（不释放节点）
void listUnlinkNode(list *list, listNode *node);

/* 迭代器方向常量 */
#define AL_START_HEAD 0     // 从头到尾的迭代方向
#define AL_START_TAIL 1     // 从尾到头的迭代方向

#endif /* __ADLIST_H__ */