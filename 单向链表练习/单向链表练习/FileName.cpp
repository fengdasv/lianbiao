#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DL 3
#define STR(n) #n
#define DIGIT_LEN_STR(n) "%" STR(n) "d"

typedef int LTDataType;

// ˫������ڵ�ṹ
typedef struct ListNode {
    LTDataType data;
    struct ListNode* prev;
    struct ListNode* next;
} LTNode;

// �����½ڵ�
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

// ��ʼ�����������ڱ��ڵ㣩
LTNode* ListInit() {
    LTNode* phead = BuyListNode(0); // �ڱ��ڵ㣬���洢��Ч����
    phead->next = phead;
    phead->prev = phead;
    return phead;
}

// ͷ������ - ʹ�����ṩ�ķ���
void ListPushFront(LTNode* phead, LTDataType x) {
    assert(phead);

    LTNode* newnode = BuyListNode(x);
    LTNode* next = phead->next;

    // ���ṩ�Ĳ����߼�
    next->prev = newnode;  // 1
    newnode->next = next;  // 2
    newnode->prev = phead; // 3
    phead->next = newnode; // 4
}

// β������ - ʹ�����ṩ�ķ���
void ListPushBack(LTNode* phead, LTDataType x) {
    assert(phead);

    LTNode* newnode = BuyListNode(x);
    LTNode* tail = phead->prev;

    // ���ṩ�Ĳ����߼�
    tail->next = newnode;      // ǰһ���ڵ�ָ���½ڵ�
    newnode->prev = tail;      // �½ڵ��prevָ����һ���ڵ�
    newnode->next = phead;     // �½ڵ��ŵ���һ�ڵ�Ϊͷ�ڵ�
    phead->prev = newnode;     // ͷ�ڵ��prev����½ڵ�
}

// ��ָ��λ�ò���ڵ�
void ListInsert(LTNode* pos, LTDataType x) {
    assert(pos);

    LTNode* newnode = BuyListNode(x);
    LTNode* prev = pos->prev;

    prev->next = newnode;
    newnode->prev = prev;
    newnode->next = pos;
    pos->prev = newnode;
}

// ͷ��ɾ��
void ListPopFront(LTNode* phead) {
    assert(phead);
    assert(phead->next != phead); // ������Ϊ��

    LTNode* first = phead->next;
    LTNode* second = first->next;

    phead->next = second;
    second->prev = phead;

    free(first);
}

// β��ɾ��
void ListPopBack(LTNode* phead) {
    assert(phead);
    assert(phead->next != phead); // ������Ϊ��

    LTNode* tail = phead->prev;
    LTNode* tailPrev = tail->prev;

    tailPrev->next = phead;
    phead->prev = tailPrev;

    free(tail);
}

// ���ҽڵ�
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

// �ж������Ƿ�Ϊ��
int ListEmpty(LTNode* phead) {
    assert(phead);
    return phead->next == phead;
}

// ��ȡ������
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

// ��������
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

// ���������ǿ����ӻ���
void ListPrint(LTNode* phead) {
    assert(phead);

    printf("˫��ѭ������: ");

    if (ListEmpty(phead)) {
        printf("������\n\n");
        return;
    }

    // �������
    int size = ListSize(phead);
    printf("Index:  ");
    for (int i = 0; i < size; i++) {
        printf(DIGIT_LEN_STR(DL), i);
        printf("    ");
    }
    printf("\n");

    // �������
    printf("Forward: ");
    LTNode* cur = phead->next;
    while (cur != phead) {
        printf(DIGIT_LEN_STR(DL), cur->data);
        if (cur->next != phead) printf(" <-> ");
        cur = cur->next;
    }
    printf(" (ѭ��)\n");

    // �������
    printf("Reverse: ");
    cur = phead->prev;
    while (cur != phead) {
        printf(DIGIT_LEN_STR(DL), cur->data);
        if (cur->prev != phead) printf(" <-> ");
        cur = cur->prev;
    }
    printf(" (ѭ��)\n\n");
}

// ���Ҳ����ӻ���ʾ
int FindAndShow(LTNode* phead, LTDataType x) {
    assert(phead);

    int pos = 0;
    LTNode* cur = phead->next;

    while (cur != phead) {
        if (cur->data == x) {
            ListPrint(phead);

            // �����ͷλ��
            int len = pos * (DL + 5); // ����" <-> "�ĳ���
            for (int i = 0; i < len + 9; i++) printf(" "); // +9��"Forward: "�ĳ���
            printf("^\n");
            for (int i = 0; i < len + 9; i++) printf(" ");
            printf("|\n");
            printf("��λ�� %d �ҵ�ֵ %d\n\n", pos, x);
            return 1;
        }
        pos++;
        cur = cur->next;
    }
    return 0;
}

// ���Ժ���
int main() {
    srand(time(0));
#define MAX_OP 10

    printf("=== ���ڱ��ڵ��˫��ѭ��������� ===\n\n");

    // ��ʼ������
    LTNode* plist = ListInit();

    // �������
    printf("1. �������:\n");
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;

        if (i % 2 == 0) {
            printf("ͷ������ %d:\n", val);
            ListPushFront(plist, val);
        }
        else {
            printf("β������ %d:\n", val);
            ListPushBack(plist, val);
        }
        ListPrint(plist);
    }

    // ɾ������
    printf("2. ɾ������:\n");
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            printf("ͷ��ɾ��:\n");
            ListPopFront(plist);
        }
        else {
            printf("β��ɾ��:\n");
            ListPopBack(plist);
        }
        ListPrint(plist);
    }

    // ���Ҳ���
    printf("3. ���Ҳ���:\n");
    printf("��ǰ����: ");
    LTNode* cur = plist->next;
    while (cur != plist) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");

    printf("����Ҫ���ҵ�ֵ: ");
    int val;
    while (scanf_s  ("%d", &val) == 1) {
        if (!FindAndShow(plist, val)) {
            printf("δ�ҵ�ֵ %d\n\n", val);
        }
        printf("����Ҫ���ҵ�ֵ (Ctrl+C�˳�): ");
    }

    // ������Դ
    ListDestroy(plist);

    return 0;
}