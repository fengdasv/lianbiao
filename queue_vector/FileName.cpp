#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vector {
    int* data;
    int size;
} vector;

vector* initvector(int n) {
    vector* v = (vector*)malloc(sizeof(vector));
    v->data = (int*)malloc(sizeof(int) * n);
    v->size = n;  // ���size��ʼ��
    return v;
   
}

void clearvector(vector* v) {  // �Ƴ�void*����ֵ����
    if (v == NULL) return;
    free(v->data);
    free(v);
}

int vectorseek(vector* v, int pos) {
    if (pos < 0 || pos >= v->size) return -1;
    return v->data[pos];
}

int insertvector(vector* v, int pos, int val) {
    if (pos < 0 || pos >= v->size) return 0;
    v->data[pos] = val;
    return 1;
}

typedef struct Queue {
    vector* data;
    int size, head, tail, count;
} Queue;

Queue* initQueue(int n) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = initvector(n);
    q->size = n;
    q->head = q->tail = q->count = 0;
    return q;
}

int empty(Queue* q) {
    return q->count == 0;
}

int push(Queue* q, int val) {
    if (q->count == q->size) return 0;

    insertvector(q->data, q->tail, val);
    q->tail= (q->tail + 1) % q->size;  // ������ѭ������tail
    q->count += 1;  // ������ֻ����һ��count
    return 1;
}

int front(Queue* q) {
    if (empty(q)) return -1;  // ��ӿն��м��
    return vectorseek(q->data, q->head);
}

int pop(Queue* q) {
    if (empty(q)) return 0;
    q->head = (q->head + 1) % q->size;  // ������ѭ������head
    q->count -= 1;
    return 1;
}

void clearQueue(Queue* q) {
    if (q == NULL) return;
    clearvector(q->data);
    free(q);
}

void outputqueue(Queue* q) {  // ����������ƴд����
    printf("queue: ");
    for (int i = 0; i < q->count; i++) {
        printf("%4d", vectorseek(q->data, (q->head + i) % q->size));
    }
    printf("\n");
}

int main(int argc, char const* argv[]) {
    srand(time(0));  // ��������ȷ��ʼ�����������

#define MAX_OP 10
    Queue* q = initQueue(5);

    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 5;
        int val = rand() % 100;  // �������ֵ

        switch (op) {
        case 0:
            if (!empty(q)) {
                printf("front of queue: %d\n", front(q));
                pop(q);
            }
            else {
                printf("queue is empty, cannot pop\n");
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            if (push(q, val)) {
                printf("push %d to queue\n", val);
            }
            else {
                printf("queue is full, cannot push %d\n", val);
            }
            break;
        }
        outputqueue(q);
    }

    clearQueue(q);
    return 0;
}