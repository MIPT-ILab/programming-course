/** ***************************************************************************
 * @file    Hash_functions.cpp
 *
 * @ingroup hash
******************************************************************************/

#include "Hash.h"

int hash_1 (const char* key, int* hash)
{
    KEY_CHECK_ (key);

    *hash = 0;

    return HT_OK;
}

int hash_2 (const char* key, int* hash)
{
    KEY_CHECK_ (key);

    *hash = key[0];

    return HT_OK;
}

int hash_3 (const char* key, int* hash)
{
    KEY_CHECK_ (key);

    long long sum = 0;

    register unsigned int i = 0;
    for (i = 0; i < strlen (key); i++)
    {
        sum += key[i];
    }

    *hash = sum;

    return HT_OK;
}

int hash_4 (const char* key, int* hash)
{
    KEY_CHECK_ (key);

    int sum = 0;

    register unsigned int i = 0;
    for (i = 0; i < strlen (key); i++)
    {
        sum += key[i];
    }

    sum /= strlen (key);

    *hash = sum;

    return HT_OK;
}

int hash_5 (const char* key, int* hash)
{
    KEY_CHECK_ (key);

    int sum = 0;

    register unsigned int i = 0;
    for (i = 0; i < strlen (key); i++)
    {
        sum = sum ^ ROL ((int) key[i], 1);
    }

    *hash = sum;

    return HT_OK;
}

int hash_6 (const char* key, int* hash)
{
    KEY_CHECK_ (key);

    int sum = 0;

    register unsigned int i = 0;
    for (i = 0; i < strlen (key); i++)
    {
        sum += sum ^ ROL ((int) key[i], 1);
        sum = sum ^ key[i];
    }

    sum /= strlen (key);

    *hash = sum;

    return HT_OK;
}
