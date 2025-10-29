#include <stdio.h>
#include <stdlib.h>
#include<time.h>
typedef struct vector{
	int *data;
	int size;
}vector;
vector* initvector(int n) {
	vector* v = (vector*)malloc(sizeof(vector));
	v->data = (int*)malloc(sizeof(int) * n);
	return v;
}
void* clearvector(vector* v) {
	if (v == NULL)return;
	free(v->data);
	free(v);
	return;
}
int vectorseek(vector* v,int pos) {
	if (pos < 0 || pos >= v->size)return -1;
	return v->data[pos];

}
int insertvector(vector* v, int pos, int val) {
	if (pos < 0 || pos >= v->size)return 0;
	v->data[pos] = val;
	return 1;
}
typedef struct Queue{
	vector* data;
	int size, head, tail, count;

}Queue;
Queue* initQueue(int n) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = initvector(n);
	q->size = n;
	q->head = q->tail = q->count = 0;
	return q;
};
int empty(Queue* q) {
	return q->count == 0;
};
int push(Queue *q, int val) {
	if (q->count == q->size)return 0;
	insertvector(q->data, q->tail, val);
		q->count += 1;
		if (q->tail == q->size)q->tail = 0;
		q->count += 1;
		return 1;
};
int front(Queue *q){
	return vectorseek(q->data,q->head);
}
int pop(Queue *q){
	if (empty(q))return 0;
	q->head += 1;
	q->count -= 1;
	return 1;

}
void clearQueue(Queue* q) {
	if (q == NULL)	
		return;
	clearvector(q->data);
	free(q);
	return;
};



int main(int argc, char const* argv[]) {
	srand(time(0));
#define MAX_OP 10
	//¶ÓÁĞ²âÊÔ´úÂë
	for(int i=0;i<MAX_OP;i++)

	return 0;
}