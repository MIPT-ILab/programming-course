
//***************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree_t.h"
#include "defines.h"
//***************************************************************************************************

//***************************************************************************************************
extern unsigned left_indent;
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *node_constructor (double info, char info_type)
{

    OUT ("# called node_constructor(/ %lg / -> ' %c ' || / %d /)\n", info, (char)info, info_type);
    assert (info_type >= 0); assert (info_type < 5);

    struct tree_elem_t *new_node = (struct tree_elem_t*)calloc (1, sizeof (struct tree_elem_t));
    assert (new_node != NULL);

    new_node -> data.info_type = info_type;
    switch (info_type)
    {
        case INFO_TYPE_ACTION:
            new_node -> data.info = (char)(info);
            break;
        case INFO_TYPE_NUMBER:
            new_node -> data.info = info;
            break;
    }

    new_node -> link[0] = NULL;
    new_node -> link[1] = NULL;

    return new_node;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *tree_clone (struct tree_elem_t *tree)
{
    assert (tree != NULL);
    OUT ("# called tree_clone([%p])\n", tree);
    left_indent++;

    struct tree_elem_t *ret_value = NULL;

    ret_value = node_constructor ((double)tree->data.info, tree->data.info_type);

    if (tree->link[0] != NULL) ret_value->link[0] = tree_clone (tree->link[0]);
    if (tree->link[1] != NULL) ret_value->link[1] = tree_clone (tree->link[1]);

    left_indent--;

    OUT ("# end tree_clone(); will return [%p]\n", ret_value);
    return ret_value;
}
//***************************************************************************************************

//***************************************************************************************************
void tree_destructor (struct tree_elem_t *tree)
{

    OUT ("# called tree_destructor([%p])\n", tree);
    assert (tree != NULL);

    if (tree -> link [0] != NULL) tree_destructor (tree -> link [0]);
    if (tree -> link [1] != NULL) tree_destructor (tree -> link [1]);

    tree -> link[0] = NULL;
    tree -> link[1] = NULL;

    tree -> data.info      = -666;
    tree -> data.info_type = 0;

    free (tree);
    tree = NULL;
}
//***************************************************************************************************

//***************************************************************************************************
void tree_print (const struct tree_elem_t *tree, FILE *target_source, const char mode)
{

    //OUT ("# called tree_print([%p] >>[%p]<< mode=%d)\n", tree, target_source, mode);

    assert (tree != NULL);
    assert (target_source != NULL);
    assert (mode == PRE_ORDER || mode == IN_ORDER || mode == POST_ORDER );

    fprintf (target_source, "(");
    //OUT (">> hello ales, wir haben info double = // %lg //, char = // %d //\n", (double)tree->data.info, (char)tree->data.info);

    #define DO_PRINT                                                                        \
    if (tree->data.info_type == INFO_TYPE_NUMBER)                                           \
        fprintf (target_source, " %lg ", (double)tree->data.info);   else                   \
            fprintf (target_source, " %c ", (char)tree->data.info);                         \


    if (mode == PRE_ORDER) {DO_PRINT;}

    if (tree->link[0] != NULL) tree_print (tree->link[0], target_source, mode); else fprintf (target_source, " nil ");

    if (mode == IN_ORDER) {DO_PRINT;}

    if (tree->link[1] != NULL) tree_print (tree->link[1], target_source,mode); else fprintf (target_source, " nil ");

    if (mode == POST_ORDER) {DO_PRINT;}

    #undef DO_PRINT
    fprintf (target_source, ")");
}
//***************************************************************************************************

////***************************************************************************************************
//struct tree_elem_t *tree_read (const char info[], unsigned *index, const char mode)
//{
//    OUT ("# called tree_read([%p], [%p]=%u)", info, index, *index);
//    assert (info != NULL);
//    assert (index != NULL);
//    assert (mode == PRE_ORDER || mode == IN_ORDER || mode == POST_ORDER );

//    while (info[*index] == ' ' || info[*index] == ')') (*index)++;
//    OUT ("# cure char is %c", info[*index]);

//    if (info[*index] == '(')
//    {
//        OUT ("# finded (\n");
//        (*index)++;
//        struct tree_elem_t *ret_node = node_constructor (0, 0);
//        assert (ret_node != NULL);

//        switch (mode)
//        {
//            #define READ_DATA                                                       \
//            unsigned i = 0;                                                         \
//            while (info[*index] == ' ' || info[*index] == ')') (*index)++;          \
//            while (info[*index] != ' ') ret_node->data[i++] = info[(*index)++];     \
//            ret_node->data[i]='\0';                                                 \
//            OUT ("# readed value %s\n", ret_node->data);

//            case 0:
//            {
//                READ_DATA;
//                ret_node->link[0] = tree_read (info, index, mode);
//                ret_node->link[1] = tree_read (info, index, mode);
//                break;
//            }
//            case 1:
//            {
//                ret_node->link[0] = tree_read (info, index, mode);
//                READ_DATA;
//                ret_node->link[1] = tree_read (info, index, mode);
//                break;
//            }
//            case 2:
//            {
//                ret_node->link[0] = tree_read (info, index, mode);
//                ret_node->link[1] = tree_read (info, index, mode);
//                READ_DATA;
//                break;
//            }
//        }
//        OUT ("# BUILDED [%p]!\n", ret_node);
//        return ret_node;

//    } else
//        if (info[*index] == 'n')
//            {
//                OUT ("# find n <> nil?\n ret nil\n");
//                (*index)+=3;
//                return NULL;
//            } else
//                {
//                    printf ("BAD TREE!\n");
//                    exit (1);
//                }
//}
////***************************************************************************************************
