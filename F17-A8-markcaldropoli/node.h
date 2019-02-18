#ifndef _NODE_H
#define _NODE_H

struct _NODE {
	struct _NODE *next;
	struct _NODE *prev;
};
typedef struct _NODE Node;

Node *sort_nodes(Node *head);
void swap_nodes(Node *a, Node *b);

#endif
