#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



#define ASSERT_OK if ( !list_ok ( list ) )\
                  { list_dump ( list ); assert ( !"list_ok" ); }




/*int main()
{
    head_list* head = list_construct ();
    list_clear ( head );
    char str[20] = {} ;
    scanf ( "%s", str );
    list_add_after ( head, head->first, str );
    scanf ( "%s", str );
    list_add_after ( head, head->first, str );
    printf ("%x\n", list_find ( head, str ) );
    list_dump ( head );
    return 0;
}*/

head_list* list_construct ( )
{
    return (head_list*) calloc ( 1, sizeof ( head_list ) );
}

int list_ok ( head_list* list)
{
    if ( !list )
    {
        return 0;
    }
    else
    {
        int i = 1;
        elem_list_t* s = list->first;
        while ( i < list->size_list )
        {
            if ( s->next != NULL )
            {
                i++;
                s = s->next;
            }
            else
            {
                return 0;
            }
        }
        return 1;
    }
}

int list_dump ( head_list* list )
{
    printf ( "LIST DUMP\n" );
    if ( !list )
    {
        assert ( !"NULL list pointer\n" );
    }
    printf ( "size = %i pointer = %x\n", list->size_list, list );
    printf ( "first elem = %x last elem = %x\n", list->first, list->last );
    elem_list_t* s = list->first;
    if ( s!= NULL )
    {
        printf ( "ELEMENTS\n" );
    }
    while ( s != NULL )
    {
        printf ( "value = %s next = %x previous = %x pointer = %x\n" , s->str, s->next, s->previous, s );
        s = s->next;
    }
    return 0;
}

int list_add_after ( head_list* list, elem_list_t* elem, char* val )
{
    ASSERT_OK
    elem_list_t* s = (elem_list_t*) calloc ( 1, sizeof ( elem_list_t ) );
    strcpy ( s->str, val );
    if ( list->size_list == 0 )
    {
        list->first = s;
        list->last = s;
        s->next = NULL;
        s->previous = NULL;
    }
    else
    {
        if ( elem->next != NULL )
        {
            elem->next->previous = s;
        }
        else
        {
            list->last = s;
        }
        s->next = elem->next;
        elem->next = s;
        s->previous = elem;
    }
    list->size_list++;
    ASSERT_OK
    return 0;
}

int list_add_before ( head_list* list, elem_list_t* elem, char* val )
{
    ASSERT_OK
    elem_list_t* s = (elem_list_t*) calloc ( 1, sizeof ( elem_list_t ) );
    strcpy ( s->str, val );
    if ( list->size_list == 0 )
    {
        list->first = s;
        list->last = s;
        s->next = NULL;
        s->previous = NULL;
    }
    else
    {
        if ( elem->previous != NULL )
        {
            elem->previous->next = s;
        }
        else
        {
            list->first = s;
        }
        s->previous = elem->previous;
        s->next = elem;
        elem->previous = s;
    }
    list->size_list++;
    ASSERT_OK
    return 0;
}

int list_del ( head_list* list, elem_list_t* elem )
{
    ASSERT_OK
    if ( list->size_list == 0 )
    {
        assert ( !"DELETE FROM EMPTY LIST" );
    }
    else
        if ( list->size_list == 1 )
        {
            free ( list->first );
            list->size_list--;
        }
        else
            if ( elem->next == NULL)
            {
                list->last = elem->previous;
                elem->previous->next = NULL;
                list->size_list--;
            }
            else
                if ( elem->previous == NULL)
                {
                    list->first = elem->next;
                    elem->next->previous = NULL;
                    list->size_list--;
                }
                else
                {
                        elem->previous->next = elem->next;
                        elem->next->previous = elem->previous;
                        list->size_list--;
                }
    ASSERT_OK
    return 0;
}

int list_destruct ( head_list* list )
{
    ASSERT_OK
    elem_list_t* s = list->first;
    while ( s != NULL )
    {
        if ( s->next != NULL )
        {
            s = s->next;
            //strcpy ( s->previous->str, "Oh");
            free ( s->previous );
        }
        else
        {
            //strcpy ( s->str, "Oh");
            free ( s );
            s = NULL;
        }
    }
    list->size_list = 666;
    free ( list );
    return 0;
}

int list_clear ( head_list* list )
{
    ASSERT_OK
    elem_list_t* s = list->first;
    while ( s != NULL )
    {
        if ( s->next != NULL )
        {
            s = s->next;
            free ( s->previous );
        }
        else
        {
            free ( s );
            s = NULL;
        }
    }
    list->first = NULL;
    list->last = NULL;
    list->size_list = 0;
    return 0;
}

elem_list_t* list_find ( head_list* list, char* val )
{
    ASSERT_OK
    elem_list_t* s = list->first;
    while ( s != NULL )
    {
        if ( strcmp( s->str, val ) == 0 )
        {
            return s;
        }
        else
        {
            s = s->next;
        }
    }
    return NULL;
}
