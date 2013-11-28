#include <stdio.h>
#include <stdlib.h>
#include "../debug_defines.h"

struct tree_elem_t
{
    double data;
    struct tree_elem_t **link;
};

struct tree_elem_t *node_constructor (void)
{
    struct tree_elem_t *new_node = (struct tree_elem_t*)calloc (1, sizeof (struct tree_elem_t));
    RETURN_ASSERT (new_node != NULL, NULL);

    new_node -> data = 0;

    new_node -> link = (struct tree_elem_t**)calloc (2, sizeof (struct tree_elem_t*));
    RETURN_ASSERT (new_node -> link != NULL, NULL);

    new_node -> link[0] = NULL;
    new_node -> link[1] = NULL;

    return new_node;
}

short int tree_destructor (struct tree_elem_t *tree)
{

    RETURN_ASSERT (tree != NULL, -1);

    if (tree -> link [0] != NULL) tree_destructor (tree -> link [0]);
    if (tree -> link [1] != NULL) tree_destructor (tree -> link [1]);

    const int POISON = -666;

    tree -> link[0] = NULL;
    tree -> link[1] = NULL;
    free (tree -> link);
    tree -> link = NULL;
    tree -> data = POISON;
    free (tree);
    tree = NULL;

    return 0;
}

short int print_tree  (const struct tree_elem_t *tree, FILE *target_source)
{
    RETURN_ASSERT (tree != NULL, -1);
    fprintf (target_source, "(");
    if (tree->link[0] != NULL) print_tree (tree->link[0], target_source); else fprintf (target_source, "nil");
    fprintf (target_source, " %lg ", tree->data);
    if (tree->link[1] != NULL) print_tree (tree->link[1], target_source); else fprintf (target_source, "nil");
    fprintf (target_source, ")");
    return 0;
}

int main()
{
    struct tree_elem_t *root = node_constructor();
    root -> data = 5;
        root -> link [0] = node_constructor();
        root -> link [0] -> data = 1;
            root -> link [0] -> link [0] = node_constructor();
            root -> link [0] -> link [0] -> data = 0;
            root -> link [0] -> link [1] = node_constructor();
            root -> link [0] -> link [1] -> data = 3;
        root -> link [1] = node_constructor();
        root -> link [1] -> data = 8;
            root -> link [1] -> link [0] = node_constructor();
            root -> link [1] -> link [0] -> data = 6;
            root -> link [1] -> link [1] = node_constructor();
            root -> link [1] -> link [1] -> data = 7;

    print_tree (root, stdout);
    tree_destructor (root);

    return 0;
}
