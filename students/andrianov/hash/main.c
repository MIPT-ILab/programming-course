#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <math.h>

#define HASH_SIZE 101
#define STR_SIZE 50

head_list* hash_construct ( );
int hash_find ( head_list* hash_array, char* str, unsigned int (*fun) ( char* ) );
int hash_destruct ( head_list*  );
int hash_dump ( head_list* hash_array );
unsigned int hash_fun1 ( char* str );
unsigned int hash_fun2 ( char* str );
unsigned int hash_fun3 ( char* str );
unsigned int hash_fun4 ( char* str );
unsigned int hash_fun5 ( char* str );
int hash_excel ( head_list* hash_array, FILE* fexcel );
int hash_clear ( head_list* hash_array );
int do_hash_fun_using_file ( FILE* fread, FILE* out, head_list* hash_array, unsigned int (*fun) ( char* ) );

int main()
{
    head_list* head_array = hash_construct ( );
    FILE* fexcel = fopen ( "extable.csv", "w" );
    FILE* fread = fopen ( "manywords.txt", "r" );
    assert ( fexcel );
    assert ( fread );
    do_hash_fun_using_file ( fread, fexcel, head_array, hash_fun1 );
    do_hash_fun_using_file ( fread, fexcel, head_array, hash_fun2 );
    do_hash_fun_using_file ( fread, fexcel, head_array, hash_fun3 );
    do_hash_fun_using_file ( fread, fexcel, head_array, hash_fun4 );
    do_hash_fun_using_file ( fread, fexcel, head_array, hash_fun5 );
    fclose ( fexcel );
    fclose ( fread );
    return 0;
}

 head_list* hash_construct ( )
 {
     head_list* s = (head_list *) calloc ( HASH_SIZE, sizeof ( head_list ) );
     for ( int i = 0; i < HASH_SIZE; i++ )
     {
         list_construct ( s[i] );
     }
     return s;
 }

 int hash_destruct ( head_list* hash_array )
 {
     for ( int i = 0; i < HASH_SIZE; i++ )
     {
        list_destruct ( &hash_array[i] );
     }
     return 0;
 }

int hash_dump ( head_list* hash_array )
{
    for ( int i = 0; i < HASH_SIZE; i++ )
    {
        printf ( "LIST NUMBER %i\n", i );
        list_dump ( &hash_array[i] );
        printf ( "\n" );
    }
    return 0;
}

int hash_find ( head_list* hash_array, char* str, unsigned int (*fun) ( char* ) )
{
    assert ( str );
    assert ( hash_array );
    assert ( fun );
    int i = (*fun) ( str ) % HASH_SIZE;
    assert ( 0 <= i && i < HASH_SIZE );
    elem_list_t* s = list_find ( &hash_array[i], str);
    if ( s == NULL )
    {
        list_add_after ( &hash_array[i], hash_array[i].last, str );
    }
    return 0;
}

unsigned int hash_fun1 ( char* str )
{
    assert ( str );
    return 0;
}

unsigned int hash_fun2 ( char* str )
{
    assert ( str );
    //printf ( "%i\n", (int)str[0] );
    return abs ( (int) str[0] );
}

unsigned int hash_fun3 ( char* str )
{
    assert ( str );
    int length = strlen ( str );
    int sum = 0;
    for ( int i = 0; i < length; i++ )
    {
        sum = sum + (int) str[i];
    }
    return abs ( sum );
}

unsigned int hash_fun4 ( char* str )
{
    assert ( str );
    int length = strlen ( str );
    int sum = 0;
    for ( int i = 0; i < length; i++ )
    {
        sum = sum + (int) str[i];
    }
    float s = sum / length;
    //printf ( "%i\n", (int)s );
    return abs ( (int) s );
}

unsigned int hash_fun5 ( char* str )
{
    assert ( str );
    int i = 0;
    char h = str[0];
    i++;
    while ( str[i] != '\0' )
    {
        h = ( ( h << 31) || ( h >> 1) ) ^ str[i];
        i++;
    }
    //printf ( "%i", h );
    return abs ( (int) h );
}

int hash_excel ( head_list* hash_array, FILE* fexcel )
{
    assert ( hash_array );
    assert ( fexcel );
    for ( int i = 0; i < HASH_SIZE; i++ )
    {
        //fprintf ( fexcel, " \n " );
        fprintf ( fexcel, " %d; \n", hash_array[i].size_list );
        //fprintf ( fexcel, " \n " );
    }
    return 0;
}

int hash_clear ( head_list* hash_array )
{
    assert ( hash_array );
    for ( int i = 0; i < HASH_SIZE; i++ )
    {
        list_clear ( &hash_array[i] );
    }
    return 0;
}

int do_hash_fun_using_file ( FILE* fread, FILE* out, head_list* hash_array, unsigned int (*fun) ( char* ) )
{
    assert ( fread );
    char str[STR_SIZE] = {};
    while ( fscanf ( fread, " %s", str ) != -1 )
    {
        hash_find ( hash_array, str, fun );
        //printf ( "%i", hash_fun2 ( str ) );
    }
    rewind ( fread );
    hash_excel ( hash_array, out );
    hash_clear ( hash_array );
    return 0;
}
