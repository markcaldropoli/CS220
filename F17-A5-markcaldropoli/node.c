#include "node.h"
#include <stdio.h>

Node *my_reverse(Node *head) {
	Node *p, *t;

	if(head->ptr != NULL) {
		t = (head->ptr) - 8;
		head->ptr = NULL;
		p = head;
		head = t;
	}

	while(head->ptr != NULL) {
		t = (head->ptr) - 8;
		head->ptr = &(p->ptr);
		p = head;
		head = t;
	}

	head->ptr = &(p->ptr);
	p = head;

	return p;
}
