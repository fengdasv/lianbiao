#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DL 3
#define STR(n) #n
#define DIGIT_LEN_STR(n) "%" STR(n) "d"

typedef int LTDataType;

// 双向链表节点结构
typedef struct ListNode {
    LTDataType data;
    struct ListNode* prev;
    struct ListNode* next;
} LTNode;

// 创建新节点
LTNode* BuyListNode(LTDataType x) {
    LTNode* node = (LTNode*)malloc(sizeof(LTNode));
    if (node == NULL) {
        printf("malloc fail\n");
        exit(-1);
    }
    node->data = x;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// 初始化链表（创建哨兵节点）
LTNode* ListInit() {
    LTNode* phead = BuyListNode(0); // 哨兵节点，不存储有效数据
    phead->next = phead;
    phead->prev = phead;
    return phead;
}

// 头部插入 - 使用您提供的方法
void ListPushFront(LTNode* phead, LTDataType x) {
    assert(phead);

    LTNode* newnode = BuyListNode(x);
    LTNode* next = phead->next;

    // 您提供的插入逻辑
    next->prev = newnode;  // 1
    newnode->next = next;  // 2
    newnode->prev = phead; // 3
    phead->next = newnode; // 4
}

// 尾部插入 - 使用您提供的方法
void ListPushBack(LTNode* phead, LTDataType x) {
    assert(phead);

    LTNode* newnode = BuyListNode(x);
    LTNode* tail = phead->prev;

    // 您提供的插入逻辑
    tail->next = newnode;      // 前一个节点指向新节点
    newnode->prev = tail;      // 新节点的prev指向上一个节点
    newnode->next = phead;     // 新节点存放的下一节点为头节点
    phead->prev = newnode;     // 头节点的prev存放新节点
}

// 在指定位置插入节点
void ListInsert(LTNode* pos, LTDataType x) {
    assert(pos);

    LTNode* newnode = BuyListNode(x);
    LTNode* prev = pos->prev;

    prev->next = newnode;
    newnode->prev = prev;
    newnode->next = pos;
    pos->prev = newnode;
}

// 头部删除
void ListPopFront(LTNode* phead) {
    assert(phead);
    assert(phead->next != phead); // 链表不能为空

    LTNode* first = phead->next;
    LTNode* second = first->next;

    phead->next = second;
    second->prev = phead;

    free(first);
}

// 尾部删除
void ListPopBack(LTNode* phead) {
    assert(phead);
    assert(phead->next != phead); // 链表不能为空

    LTNode* tail = phead->prev;
    LTNode* tailPrev = tail->prev;

    tailPrev->next = phead;
    phead->prev = tailPrev;

    free(tail);
}

// 查找节点
LTNode* ListFind(LTNode* phead, LTDataType x) {
    assert(phead);

    LTNode* cur = phead->next;
    while (cur != phead) {
        if (cur->data == x) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// 判断链表是否为空
int ListEmpty(LTNode* phead) {
    assert(phead);
    return phead->next == phead;
}

// 获取链表长度
int ListSize(LTNode* phead) {
    assert(phead);

    int size = 0;
    LTNode* cur = phead->next;
    while (cur != phead) {
        size++;
        cur = cur->next;
    }
    return size;
}

// 销毁链表
void ListDestroy(LTNode* phead) {
    assert(phead);

    LTNode* cur = phead->next;
    while (cur != phead) {
        LTNode* next = cur->next;
        free(cur);
        cur = next;
    }
    free(phead);
}

// 输出链表（增强版可视化）
void ListPrint(LTNode* phead) {
    assert(phead);

    printf("双向循环链表: ");

    if (ListEmpty(phead)) {
        printf("空链表\n\n");
        return;
    }

    // 输出索引
    int size = ListSize(phead);
    printf("Index:  ");
    for (int i = 0; i < size; i++) {
        printf(DIGIT_LEN_STR(DL), i);
        printf("    ");
    }
    printf("\n");

    // 正向输出
    printf("Forward: ");
    LTNode* cur = phead->next;
    while (cur != phead) {
        printf(DIGIT_LEN_STR(DL), cur->data);
        if (cur->next != phead) printf(" <-> ");
        cur = cur->next;
    }
    printf(" (循环)\n");

    // 反向输出
    printf("Reverse: ");
    cur = phead->prev;
    while (cur != phead) {
        printf(DIGIT_LEN_STR(DL), cur->data);
        if (cur->prev != phead) printf(" <-> ");
        cur = cur->prev;
    }
    printf(" (循环)\n\n");
}

// 查找并可视化显示
int FindAndShow(LTNode* phead, LTDataType x) {
    assert(phead);

    int pos = 0;
    LTNode* cur = phead->next;

    while (cur != phead) {
        if (cur->data == x) {
            ListPrint(phead);

            // 计算箭头位置
            int len = pos * (DL + 5); // 考虑" <-> "的长度
            for (int i = 0; i < len + 9; i++) printf(" "); // +9是"Forward: "的长度
            printf("^\n");
            for (int i = 0; i < len + 9; i++) printf(" ");
            printf("|\n");
            printf("在位置 %d 找到值 %d\n\n", pos, x);
            return 1;
        }
        pos++;
        cur = cur->next;
    }
    return 0;
}

// 测试函数
int main() {
    srand(time(0));
#define MAX_OP 10

    printf("=== 带哨兵节点的双向循环链表测试 ===\n\n");

    // 初始化链表
    LTNode* plist = ListInit();

    // 插入测试
    printf("1. 插入测试:\n");
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;

        if (i % 2 == 0) {
            printf("头部插入 %d:\n", val);
            ListPushFront(plist, val);
        }
        else {
            printf("尾部插入 %d:\n", val);
            ListPushBack(plist, val);
        }
        ListPrint(plist);
    }

    // 删除测试
    printf("2. 删除测试:\n");
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            printf("头部删除:\n");
            ListPopFront(plist);
        }
        else {
            printf("尾部删除:\n");
            ListPopBack(plist);
        }
        ListPrint(plist);
    }

    // 查找测试
    printf("3. 查找测试:\n");
    printf("当前链表: ");
    LTNode* cur = plist->next;
    while (cur != plist) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");

    printf("输入要查找的值: ");
    int val;
    while (scanf_s  ("%d", &val) == 1) {
        if (!FindAndShow(plist, val)) {
            printf("未找到值 %d\n\n", val);
        }
        printf("输入要查找的值 (Ctrl+C退出): ");
    }

    // 清理资源
    ListDestroy(plist);

    return 0;
}