#include <stdio.h>
#include <stdlib.h>
#include "node.h"

#define TRUE 1

Node *sort_nodes(Node *head) {
	Node *new_head; /* Pointer to new list of ordered nodes */
	Node *list = head; /* Temporary pointer to head */
	Node *greatest; /* Holds the node with the greatest value */
	Node *nxt; /* Use to traverse linked list */
	Node *temp; /* Temporaray node placeholder */
	int i, x; /* Integers to control loops */

	/* Despite not getting small cases, put handling in anways */
	if(head == NULL) return NULL;
	if(head->next == NULL) return head;

	/* Find greatest in list */
	greatest = list;
	nxt = list->next;

	while(nxt != NULL) {
		if(greatest < nxt) greatest = nxt;
		nxt = nxt->next;
	}

	new_head = greatest;

	/* Move greatest to beginning of the list */
	swap_nodes(list, greatest);

	/* Sort the rest of the list */
	while(TRUE) {
		temp = new_head;
		for(i = 0; i < x; i++) temp = temp->next;
		x++;

		if(temp != NULL) {
			greatest = temp;

			nxt = temp->next;
			while(nxt != NULL) {
				if(greatest < nxt) greatest = nxt;
				nxt = nxt->next;
			}
		}
		else break;

		swap_nodes(temp, greatest);
	}

	return new_head;
}

/* Swap two nodes in the list */
void swap_nodes(Node *a, Node *b) {
	/* Swap the next values of the nodes */
	Node *temp = a->next;

	a->next = b->next;
	b->next = temp;

	/* Check to see if either of the nodes is the last in the list.
	 * If they are not, update the prev value of next, which is the node. */
	if(a->next != NULL) a->next->prev = a;
	if(b->next != NULL) b->next->prev = b;

	/* Swap the prev values of the nodes */
	temp = a->prev;
	a->prev = b->prev;
	b->prev = temp;

	/* Check to see if either of the nodes is the first in the list.
	 * If they are not, update the next values of the previous, which is the node */
	if(a->prev != NULL) a->prev->next = a;
	if(b->prev != NULL) b->prev->next = b;
}

/* main function to test sort of various nodes */
/*int main() {
	Node node2, node1, node4, node3;
	Node *node5 = (Node *) malloc (sizeof(Node));
	Node *node6 = (Node *) malloc (sizeof(Node));

	node1 = (Node) { .next = &node2, .prev = NULL };
	node2 = (Node) { .next = &node3, .prev = &node1 };
	node3 = (Node) { .next = &node4, .prev = &node2 };
	node4 = (Node) { .next = node5, .prev = &node3 };

	node5->next = node6;
	node5->prev = &node4;

	node6->next = NULL;
	node6->prev = node5;

	printf("%p %p %p %p %p %p\n", &node1, &node2, &node3, &node4, node5, node6);

	Node *list = sort_nodes(&node1);

	printf("previous = %p, current = %p, next = %p\n", list->prev, list, list->next);

	while(list->next != NULL) {
		list = list->next;
		printf("previous = %p, current = %p, next = %p\n", list->prev, list, list->next);
	}

	return 0;
}*/
