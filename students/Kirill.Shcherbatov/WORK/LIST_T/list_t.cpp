#include <stdio.h>
#include <stdlib.h>	
#include <assert.h>
#include "list_t.h"

void list_stick_value_to (double data_value, struct list_t **target_list)
{
	struct list_t *new_node = (struct list_t*)calloc (1, sizeof (struct list_t));
	assert (new_node != NULL);
	
	new_node->next = NULL;
	new_node->data = data_value;
	
	if (target_list == NULL)
	{
		*target_list = new_node;
	} else
	{
		struct list_t *temp = *target_list;
		*target_list = new_node;
		new_node->next = temp;
	}
}

void list_destructor (struct list_t *root_node)
{
    assert (root_node != NULL);
    if (root_node -> next != NULL) list_destructor (root_node -> next);
    const int POISON = -666;
    root_node -> data = POISON;
    root_node -> next = NULL;
    free (root_node);
    root_node = NULL;
}

struct list_t* remove_elems (struct list_t *root_node, double value)
{
    assert (root_node != NULL);
	if (root_node->data == value)
	{
		struct list_t* temp = root_node->next;
		free (root_node);
		return remove_elems (temp, value);
	} else
	{
		root_node->next = remove_elems (root_node->next, value);
		return root_node;
	}
}

void print_list (const struct list_t *root_node)
{
	if (root_node == NULL) return;
	printf ("%lg", root_node->data);
    if (root_node->next != NULL)
    {
		printf (", ");
		print_list (root_node->next);
	} else printf(";\n");
}

struct list_t *create_list_from_integers_1_to_n (unsigned int n)
{
	assert (n>0);
    struct list_t *new_list = (struct list_t*) calloc(1, sizeof(struct list_t));
    assert (new_list != NULL);
    for (register unsigned int i = 1; i <= n; i++)
        list_stick_value_to (i, &new_list);
    return new_list;
}

