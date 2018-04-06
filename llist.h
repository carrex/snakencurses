#ifndef LLIST_H
#define LLIST_H

#include <stdlib.h>

/* Basic linked list for snake.c */

struct Node {
	struct Node* next;
	short data[2];
};

typedef struct Node* LList;

LList llist_new(short data[2]);
void llist_push(LList head, short data[2]);
void llist_pop(LList head);
void llist_free(LList head);

LList llist_new(short data[2])
{
	LList head = malloc(sizeof(struct Node));
	if (!head) {
		printf("Malloc for linked list failed.");
		return NULL;
	}
	head->data[0] = data[0];
	head->data[1] = data[1];
	head->next    = NULL;

	return head;
}

/* Add a new node to the end of the list */
void llist_push(LList head, short data[2])
{
	struct Node* node = llist_new(data);
	struct Node* n = head;
	while (n->next) n = n->next;
	n->next = node;
}

void llist_pop(LList head)
{
	struct Node* n = head;
	while (n->next->next) n = n->next; // Realistically need a check for head->next == NULL
	
	free(n->next);
	n->next = NULL;
}

void llist_free(LList head)
{
	struct Node* tmp;
	do {
		tmp  = head;
		head = head->next;
		free(tmp);
	} while(head);
}

#endif
