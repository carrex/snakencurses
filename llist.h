#ifndef LLIST_H
#define LLIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* Basic linked list for snake.c */

struct Node {
	struct Node* next;
	uint8_t data[2];
} Node;

typedef struct Node LList;

LList* llist_new(uint8_t* data);
void llist_push(LList* head, uint8_t* data);
void llist_pop(LList* head);
void llist_free(LList* head);

LList* llist_new(uint8_t* data)
{
	LList* head = malloc(sizeof(struct Node));
	if (!head) {
		printf("Malloc for new linked list failed.");
		return NULL;
	}
	head->data[0] = data[0];
	head->data[1] = data[1];
	head->next    = NULL;

	return head;
}

void llist_push(LList* head, uint8_t* data)
{
	struct Node* node = llist_new(data);
	/* Add the new node to the end of the list */
	struct Node* n = head;
	while (n->next) n = n->next;
	n->next = node;
}

void llist_pop(LList* head)
{
	/* Find the end of the list */
	struct Node* n = head;
	while (n->next->next) n = n->next; // Need a check for head->next == NULL
	
	free(n->next);
	n->next = NULL;
}

void llist_free(LList* head)
{
	struct Node* tmp;
	do {
		tmp  = head;
		head = head->next;
		free(tmp);
	} while(head);
}

#endif
