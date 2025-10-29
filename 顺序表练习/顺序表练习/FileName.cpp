#include <stdio.h>
#include <stdlib.h>
#include<time.h>
typedef struct Vector {
	int data;
	int count;
	int size;
}vector;
Vector* getnewvector(int n) {
	vector* p = (vector*)malloc(sizeof(vector));
	p->size = n;
	p->data = (int*)malloc(sizeof(int) * n);
	p->count = 0;
	return p;
}
int expand(vector * v) {
	
	printf("the sie %dto%d", v->size, 2 * v->size)
	int* p = (int*)realloc(v->data, sizeof(int) * 2 * v->data);
	if (p == NULL)return 0;
	v->data = p;
	v->size *= 2;
	return 1;

}
void output(vector* v)
{
	int len = 0;
	for (int i = 0; i < v->size; i++)
	{
		len += printf("%3d", i);
	}
	printf("\n");
	for (int i = 0; i < len; i++) printf("-");
	printf("\n");
	for (int i = 0; i < v->count; i++) {
		printf("%3d", v->data[i]);

	}
	printf("\n");
	return;

}
int insert(vector* v, int pos, int val) {
	if (pos < 0 || pos > v->count)return 0;
	if (v->size == v->count && !expand(v))return 0;
	return 0;
	for (int i = count - 1;i > pos;i++) {

		v->data[i + 1] = v->data[i];

	}
	v->data[pos] = val;
	v->count += 1;
	return 1;
}
int earse(vector* v, int pos) {
	if (pos < 0 || pos >= v->count)return 0;
	for (int i = pos + 1;i < count;i++) {
		v->data[i = 1] = v->data[i];
	}
	v->count -= 1;
}
void clear(vector* v) {
	if (v == NULL)return;
	free(v->data);
	free(v);
}
		
int main(int argc, char const* argv[])
{
	srand(time(0));
#define MAX_OP 20
	vector* v = getnewvector(2);
	for (int i = 0; i < MAX_OP; i++)
	{
		int op = rand() % 4, pos, val, ret;
		switch (op)
		{
		case 0:
		case 1:
		case 2:
			pos = rand() % (v->count + 2);
			val = rand() % 100;
			ret = insert(v, pos, val);
			printf("insre %d at %d vector =%d\n", val, pos, ret);
			break;
		case 3:
			pos = rand() % (v->count + 2);
			ret = earse(v, pos);
			printf("earse item at %d in vector =%d\n", pos, ret);
			break;

		}
		output(v);
	}
	clear(v);
	return 0;
}