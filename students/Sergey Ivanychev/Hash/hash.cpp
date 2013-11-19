#include "hash.h"
#include "errors.h"

/**
			hash_dump					makes dump print of the whole hash
			
			@param[out]		my_hash		argumented hash

			@return						HASH_DUMP_ARG_NULL			-	argumented pointer of hash is NULL
										HASH_OK						-	OK
										
**/

int hash_dump(hash* my_hash);

/**
			hash_check					verifies condition of argumented hash

			@param[out]		my_hash		argumented hash

			@return						HASH_CHECK_ARG_NULL			-	argumented pointer is NULL
										HASH_CHECK_BAD				-	one of lists is broken
										HASH_CHECK_OK				-	OK
**/

int hash_check(hash* my_hash);

/**
			hash_destruct				destructs hash to the ground!

			@param[out]		my_hash		argumented hash

			@return						HASH_DEST_ARG_ERRORS		-	argumented pointer is NULL
										HASH_DEST_LIST_DEST_ERROR	-	error while destructing lists
										HASH_OK						-	OK
**/


int hash_destruct(hash** my_hash);

/**
			hash_construct				constructs hash for your need and saves pointer to the inputted pointer

			@param[out]		my_hash		pointer to save-to location

			@return						HASH_CONST_ARG_ERRORS		-	argumented pointer is NULL
										HASH_CALLOC_FAIL			-	calloc failed to establish memory
										HASH_LIST_CONSTR_FAIL		-	error while constructing list
										HASH_OK						-	OK
										HASH_CONSTR_BROKEN_CREATED	-	created broken hash
**/

int hash_construct(hash** my_hash);





//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int hash_dump(hash* my_hash)
{
	OUT_DEB("\n#!#!#!##!#!#!#!#!!#! HASH DUMP BEGIN #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n");
	OUT_DEB("#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n\n");
	if (my_hash == NULL)
	{
		OUT_DEB("# HASH DUMP ERROR: Argumented pointer is NULL\n");
		OUT_DEB("\n#!#!#!##!#!#!#!#!!#! HASH DUMP END   #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n");
		OUT_DEB("#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n\n");
		return HASH_DUMP_ARG_NULL;
	}

	OUT_DEB("# Pointers of methods:\n",
			"# h0 \t\t\t\t= [%08x]\n",
			"# h_ascii_first\t\t=[%08x]\n",
			"# h_ascii_sum\t\t\t=[%08x]\n",
			"# h_ascii_sum_over_num\t=[%08x]\n"
			"# h_bits_move\t\t=[%08x]\n\n",
			my_hash->h0,
			my_hash->h_ascii_first,
			my_hash->h_ascii_sum,
			my_hash->h_ascii_sum_over_num,
			my_hash->h_bits_move);
	OUT_DEB("# Calling dumps of lists...\n\n");
	if (my_hash->table == NULL) OUT_DEB("# TABLE pointer is NULL\n");
	else
	for (int i = 0; i < my_hash->size; ++i)
	{
		OUT_DEB("# %d'th list...\n");
		int ret = list_dump(my_hash->table[i]);
		
		if (ret != LIST_OK) OUT_DEB("# There were errors\n");
		else OUT_DEB("# Well done\n");
	}
	return HASH_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int hash_check(hash* my_hash)
{
	if (my_hash == NULL) return HASH_CHECK_ARG_NULL;
	for (int i = 0; i < HASH_SIZE; ++i) 
		if (list_check(my_hash->table[i]) != LIST_CHECK_OK)
		{
			list_dump(my_hash->table[i]);
			return HASH_CHECK_BAD;
		};
	
	return HASH_CHECK_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int hash_destruct(hash** my_hash)
{
	OUT_DEB("### HASH DESTRUCT BEGIN ###\n");
	if (my_hash == NULL)
	{
		OUT_DEB("# HASH DESTRUCT ERROR: Argumented pointer is NULL\n");
		return HASH_DEST_ARG_ERRORS;
	}
	OUT_DEB("# Calling hash_check()...");

	int ret = hash_check(*my_hash);

	if (ret != HASH_CHECK_OK) OUT_DEB("BAD!!\nTrying do destruct lists...\n");
	else OUT_DEB("OK\n");

	(*my_hash) -> h0							= NULL;
	(*my_hash) -> h_ascii_first				= NULL;
	(*my_hash) -> h_ascii_sum				= NULL;
	(*my_hash) -> h_ascii_sum_over_num		= NULL;
	(*my_hash) -> h_bits_move				= NULL;

	(*my_hash)->size = POISON;

	OUT_DEB("# Destructing lists...\n\n");
	
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		OUT_DEB("# Destructing %d'th list... ");
		ret = list_destruct((*my_hash)->table[i]);
		if (ret != LIST_OK)
		{
			OUT_DEB("FAILED!!!\n\nDESTRUCTION OF %d'TH LIST FAILED\n");
			return HASH_DEST_LIST_DEST_ERROR;
		}
		OUT_DEB("OK\n");
	}
	free(*my_hash);
	*my_hash = NULL;
	OUT_DEB("# Sucessfully destructed\n### HASH DESTRUCT FINISHED ###\n");
	return HASH_OK;	
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int hash_construct(hash** my_hash)
{
	OUT_DEB("### HASH CONSTRUCT BEGIN ###\n");

	if (my_hash == NULL)
	{
		OUT_DEB("# HASH CONSTRUCT ERROR: Argumented pointer is NULL\n");
		return HASH_CONST_ARG_ERRORS;
	}
	(*my_hash) = (hash*)calloc(1, sizeof(hash));
	OUT_DEB("# Memory received...\n");
	if ((*my_hash) == NULL)
	{
		OUT_DEB("# HASH CONSTRUCT ERROR: Calloc failed\n");
		return HASH_CALLOC_FAIL;
	}
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		int ret = list_construct(&((*my_hash)->table[i]));
		if (ret != LIST_OK)
		{
			OUT_DEB("# HASH CONSTRUCT ERROR: %d'th list hasn't been constructed\n");
			return HASH_LIST_CONSTR_FAIL;
		}
		OUT_DEB("# %d'th list successfully constructed\n");
	}
	OUT_DEB("# Saving pointers of hash functions...\n");
	(*my_hash) -> h0						= &hash_func1;
	(*my_hash) -> h_ascii_first			= &hash_func2;
	(*my_hash) -> h_ascii_sum			= &hash_func3;
	(*my_hash) -> h_ascii_sum_over_num	= &hash_func4;
	(*my_hash) -> h_bits_move			= &hash_func5;

	(*my_hash)->size = HASH_SIZE;

	int ret = hash_check(*my_hash);


	if (ret == HASH_CHECK_OK)
	{
		OUT_DEB("\n# Everything has been constructed successfully!\n");
		OUT_DEB("### HASH CONSTRUCT FINISHED ###");
		return HASH_OK;
	}
	else
	{
		OUT_DEB("\n# FAILED TO CONSTRUCT\n### HASH CONSTRUCT FINISHED ###\n");
		return HASH_CONSTR_BROKEN_CREATED;
	}
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

/**
		@par			here you can find several hash functions, which are used by hash. DO NOT DELETE THEM.
**/

unsigned long long hash_func1(char* word)
{
	assert(word);
	return 0;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

unsigned long long hash_func2(char* word)
{
	assert(word);
	return (unsigned long long)word[0];
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


unsigned long long hash_func3(char* word)
{
	assert(word);
	int i = 0;
	unsigned long long sum = 0;
	while ((word[i] != 0) && (i < HASH_SIZE)) sum += word[i++];
	return sum;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


unsigned long long hash_func4(char* word)
{
	assert(word);
	unsigned long long sum = 0;
	int i = 0;
	while ((word[i] != 0) && (i < HASH_SIZE)) sum += word[i++];
	if (i != 0) sum /= i;
	return sum;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


unsigned long long hash_func5(char* word)
{
	unsigned long long ret = 0;
	int i = 0;
	while ((word[i] != 0) && (i < HASH_SIZE)) 	ret = ((ret << sizeof(ret)* 8 - 1) | (ret >> 1)) ^ ((long long) word[i++]);
	return ret;
}