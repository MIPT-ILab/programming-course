#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree_t.h"
#include "defines.h"

struct tree_elem_t *node_constructor ()
{
    OUT ("# called node_constructor()\n");
    struct tree_elem_t *new_node = (struct tree_elem_t*)calloc (1, sizeof (struct tree_elem_t));
    assert (new_node != NULL);

    new_node -> data = (char*)calloc (255, sizeof(char));

    new_node -> link = (struct tree_elem_t**)calloc (2, sizeof (struct tree_elem_t*));
    assert (new_node -> link != NULL);

    new_node -> link[0] = NULL;
    new_node -> link[1] = NULL;

    return new_node;
}

void tree_destructor (struct tree_elem_t *tree)
{
    OUT ("# called tree_destructor([%p])\n", tree);
    assert (tree != NULL);

    if (tree -> link [0] != NULL) tree_destructor (tree -> link [0]);
    if (tree -> link [1] != NULL) tree_destructor (tree -> link [1]);

    tree -> link[0] = NULL;
    tree -> link[1] = NULL;
    free (tree -> link);

    tree -> link = NULL;
    if (tree -> data != NULL) free (tree->data);
    tree->data = NULL;

    free (tree);
    tree = NULL;
}

struct tree_elem_t *tree_add_lr (struct tree_elem_t *tree, struct tree_elem_t *addon, char add_right)
{
    OUT ("# called tree_add_left()\n");
    assert (tree != NULL);
    assert (addon != NULL);
    assert (add_right == 0 || add_right == 1);
    struct tree_elem_t *old = NULL;
    if (tree->link[add_right] != NULL) old=tree->link[add_right];
    tree->link[add_right] = addon;
    return old;
}

void tree_print (const struct tree_elem_t *tree, FILE *target_source, const char mode)
{
    OUT ("# called tree_print([%p], [%p], mode=%d)\n", tree, target_source, mode);

    assert (tree != NULL);
    assert (target_source != NULL);
    assert (mode == PRE_ORDER || mode == IN_ORDER || mode == POST_ORDER );

    fprintf (target_source, "(");
    if (mode == PRE_ORDER) fprintf (target_source, " %s ", tree->data);
    if (tree->link[0] != NULL) tree_print (tree->link[0], target_source, mode); else fprintf (target_source, " nil ");
    if (mode == IN_ORDER) fprintf (target_source, " %s ", tree->data);
    if (tree->link[1] != NULL) tree_print (tree->link[1], target_source,mode); else fprintf (target_source, " nil ");
    if (mode == POST_ORDER) fprintf (target_source, " %s ", tree->data);
    fprintf (target_source, ")");
}

struct tree_elem_t *tree_read (const char info[], unsigned *index, const char mode)
{
    OUT ("# called tree_read([%p], [%p]=%u)", info, index, *index);

    assert (info != NULL);
    assert (index != NULL);
    assert (mode == PRE_ORDER || mode == IN_ORDER || mode == POST_ORDER );

    while (info[*index] == ' ' || info[*index] == ')') (*index)++;
    OUT ("# cure char is %c", info[*index]);

    if (info[*index] == '(')
    {
        OUT ("# finded (\n");
        (*index)++;
        struct tree_elem_t *ret_node = node_constructor ();
        assert (ret_node != NULL);

        switch (mode)
        {
            #define READ_DATA                                                       \
            unsigned i = 0;                                                         \
            while (info[*index] == ' ' || info[*index] == ')') (*index)++;          \
            while (info[*index] != ' ') ret_node->data[i++] = info[(*index)++];     \
            ret_node->data[i]='\0';                                                 \
            OUT ("# readed value %s\n", ret_node->data);

            case 0:
            {
                READ_DATA;
                ret_node->link[0] = tree_read (info, index, mode);
                ret_node->link[1] = tree_read (info, index, mode);
                break;
            }
            case 1:
            {
                ret_node->link[0] = tree_read (info, index, mode);
                READ_DATA;
                ret_node->link[1] = tree_read (info, index, mode);
                break;
            }
            case 2:
            {
                ret_node->link[0] = tree_read (info, index, mode);
                ret_node->link[1] = tree_read (info, index, mode);
                READ_DATA;
                break;
            }

            #define READ_DATA
        }
        OUT ("# BUILDED [%p]!\n", ret_node);
        return ret_node;

    } else
        if (info[*index] == 'n')
            {
                OUT ("# find n <> nil?\n ret nil\n");
                (*index)+=3;
                return NULL;
            } else
                {
                    printf ("BAD TREE!\n");
                    exit (1);
                }

}
