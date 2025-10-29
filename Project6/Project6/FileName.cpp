#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define DL 3
#define STR(n) #n
#define DIGIT_LEN_STR(n) "%"STR(n) "d"
typedef struct Node {
	int data;
	struct  Node* next;
}Node;
Node* getnewNode(int val)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = val;
	p->next = NULL;
	return p;
}
Node* insert(Node* head, int pos, int val) {
	if (pos == 0) {
		Node* p = getnewNode(val);
		p->next = head;
		return p;
	}
	Node* p = head;
	for (int i = 1; i < pos; i++) p = p->next;
	Node* node = getnewNode(val);
	node->next = p->next;
	p->next = node;
	return head;
}


void clear(Node* head) {
	if (head == NULL) return;
	for (Node* p = head, *q; p; p = q) {
		p = q->next;
		free(p);
		return;
	}
}
int main(int argc, char const* argv[]) {
	return 0;
}