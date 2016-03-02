#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LL_OK 0
#define LL_NOTOK 1

typedef struct ll_node {
	void* value;
	struct ll_node* next;
} ll_node;

typedef struct llist {
	struct ll_node* start;
} llist;

typedef int LL_ERR;

ll_node* ll_get(llist* list, int index);
void     ll_add(llist* list, ll_node* new_node);
LL_ERR   ll_insert(llist* list, ll_node* new_node, int index);
ll_node* ll_remove(llist* list, int index);
int      ll_size(llist* list);

ll_node* ll_get(llist* list, int index) {
	ll_node* curr = list->start;
	while(curr != NULL && index > 0) {
		curr = curr->next;
		index--;
	}

	if (index > 0) {
		return NULL;
	}

	return curr;
}

void ll_add(llist* list, ll_node* new_node) {
	if (list->start == NULL) {
		list->start = new_node;
		return;
	}

	ll_node* curr = list->start;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_node;
}

int ll_insert(llist* list, ll_node* new_node, int index) {
	ll_node* prev = NULL;
	ll_node* curr = list->start;
	while (curr != NULL && index > 0) {
		prev = curr;
		curr = curr->next;
		index--;
	}

	if (index > 0) {
		return LL_NOTOK;
	}

	if (prev == NULL) {
		// We are at the beginning of the list
		new_node->next = list->start;
		list->start = new_node;
		return LL_OK;
	} else {
		prev->next = new_node;
		new_node->next = curr;
		return LL_OK;
	}
}

ll_node* ll_remove(llist* list, int index) {
	ll_node* prev = NULL;
	ll_node* curr = list->start;

	while (curr != NULL && index > 0) {
		prev = curr;
		curr = curr->next;
		index--;
	}

	if (index > 0) {
		return NULL;
	}

	if (prev == NULL) {
		list->start = curr->next;
		return curr;
	} else {
		prev->next = curr->next;
		return curr;
	}
}

int ll_size(llist* list) {
	int size = 0;
	ll_node* curr = list->start;
	while (curr != NULL) {
		curr = curr->next;
		size++;
	}
	return size;
}

int main(int argc, char** argv) {
	llist* list = calloc(1, sizeof(llist));
	ll_node* n1 = calloc(1, sizeof(ll_node));
	n1->value = (void*) 1;

	ll_add(list, n1);

	assert(ll_get(list, 0)->value == (void*) 1);
	assert(ll_size(list) == 1);

	ll_node* n2 = calloc(1, sizeof(ll_node));
	n2->value = (void*) 3;

	ll_add(list, n2);

	assert(ll_get(list, 1)->value == (void*) 3);
	assert(ll_size(list) == 2);
	
	free(n2);
	free(n1);
	free(list);
	return 0;
}
