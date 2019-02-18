#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "node.h"

extern Node* reverse_asm(Node *head, unsigned int offset);

#define NUM_NODES 1000000

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void timeval_print(char *str, struct timeval *tv)
{
    printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec, tv->tv_usec);
}

Node *get_head(void *p)
{
	return p == NULL ? 
		NULL : 
		((Node *)((char *)(p)-(unsigned long)(&((Node *)0)->ptr)));
}

Node *gen_rand_list(unsigned int count)
{
	Node *head, *tail, *curr;
	void *p;
	unsigned int i;

	head = tail = curr = NULL;
	srand(time(NULL));
	for(i = 0; i < count; i++) {
		curr = (Node *) malloc (sizeof(Node));
		memset(curr, 0, sizeof(Node));
		curr->var = curr->val.n = rand() % 1000;
		if(head == NULL) {
			head = tail = curr;
		} else {
			tail->ptr = &(curr->ptr);
			tail = curr;
		}
	}
	return head;
}

void print_node(Node *node)
{
	printf("%d", node->var);
}

void print_list(Node *head)
{
	while(head) {
		print_node(head);
		printf(" -> ");
		head = get_head(head->ptr);
	}
	printf(" NULL\n");
}

Node *reverse_C(Node *head)
{
	void *headptr, *nextptr, *new_headptr;

	headptr = nextptr = new_headptr = NULL;
	if(head == NULL) return NULL;
	headptr = &(head->ptr);
	while (headptr) {
		nextptr = (void *)(*((unsigned long *)headptr));
		*(unsigned long *)headptr = (unsigned long) new_headptr;
		new_headptr = headptr;
		headptr = nextptr;
	}
	return get_head(new_headptr);
}

int main()
{
	struct timeval tvDiff, tvStart, tvEnd;
	Node *head, *revhead;
	
	/* This is the offset from base of node structure to the ptr field */
	unsigned int offset; 
	
	/* We ask the compiler: "If 0 were the address of a Node, what is the address of ptr field?" */
	offset = (unsigned int)(&((Node *)0)->ptr);
	
	head = gen_rand_list(NUM_NODES);
	print_list(head);
	revhead = reverse_asm(head, offset);
	printf("****REV****\n");
	print_list(revhead);

	gettimeofday(&tvStart, NULL);
	revhead = reverse_asm(head, offset);
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("ASM: ", &tvDiff);

	gettimeofday(&tvStart, NULL);
	head = reverse_C(revhead);
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("C: ", &tvDiff);
	return 0; 
}
