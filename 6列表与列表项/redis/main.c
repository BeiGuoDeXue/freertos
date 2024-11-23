// 参考：https://github.com/redis/redis/blob/unstable/src/adlist.c
#include <stdio.h>
#include <string.h>
#include "adlist.h"

// 自定义的打印函数，用于遍历时打印节点值
void printNode(void *value) {
    printf("%s\n", (char*)value);
}

// 自定义的复制函数
void *dupString(void *ptr) {
    char *str = (char*)ptr;
    char *dup = strdup(str);  // 注意：实际使用时需要检查strdup的返回值
    return dup;
}

// 自定义的释放函数
void freeString(void *ptr) {
    free(ptr);
}

// 自定义的匹配函数
int matchString(void *ptr, void *key) {
    return strcmp((char*)ptr, (char*)key) == 0;
}

int main() {
    // 1. 创建链表
    printf("Creating list...\n");
    list *mylist = listCreate();
    if (!mylist) {
        printf("Failed to create list!\n");
        return 1;
    }

    // 设置自定义函数
    listSetDupMethod(mylist, dupString);
    listSetFreeMethod(mylist, freeString);
    listSetMatchMethod(mylist, matchString);

    // 2. 添加节点
    printf("\nAdding nodes...\n");
    listAddNodeTail(mylist, "Hello");
    listAddNodeTail(mylist, "World");
    listAddNodeHead(mylist, "First");
    printf("List length: %lu\n", listLength(mylist));

    // 3. 正向遍历
    printf("\nForward traversal:\n");
    listIter *iter = listGetIterator(mylist, AL_START_HEAD);
    listNode *node;
    while ((node = listNext(iter)) != NULL) {
        printNode(listNodeValue(node));
    }
    listReleaseIterator(iter);

    // 4. 反向遍历
    printf("\nBackward traversal:\n");
    iter = listGetIterator(mylist, AL_START_TAIL);
    while ((node = listNext(iter)) != NULL) {
        printNode(listNodeValue(node));
    }
    listReleaseIterator(iter);

    // 5. 查找节点
    printf("\nSearching for node 'World':\n");
    node = listSearchKey(mylist, "World");
    if (node) {
        printf("Found node: %s\n", (char*)listNodeValue(node));
    }

    // 6. 按索引访问
    printf("\nAccessing node by index:\n");
    node = listIndex(mylist, 1);  // 获取第二个节点
    if (node) {
        printf("Node at index 1: %s\n", (char*)listNodeValue(node));
    }

    // 7. 旋转操作
    printf("\nPerforming rotation (tail->head):\n");
    listRotateTailToHead(mylist);
    iter = listGetIterator(mylist, AL_START_HEAD);
    while ((node = listNext(iter)) != NULL) {
        printNode(listNodeValue(node));
    }
    listReleaseIterator(iter);

    // 8. 复制链表
    printf("\nDuplicating list:\n");
    list *copylist = listDup(mylist);
    if (copylist) {
        printf("Duplicated list length: %lu\n", listLength(copylist));
        listRelease(copylist);
    }

    // 9. 清空链表
    printf("\nEmptying list...\n");
    listEmpty(mylist);
    printf("List length after emptying: %lu\n", listLength(mylist));

    // 10. 释放链表
    printf("\nReleasing list...\n");
    listRelease(mylist);
    printf("Test completed!\n");

    return 0;
}
