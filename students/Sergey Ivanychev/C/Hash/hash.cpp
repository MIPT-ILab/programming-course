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
			hash_ctor				constructs hash for your need and saves pointer to the inputted pointer

			@param[out]		my_hash		pointer to save-to location

			@return						HASH_CONST_ARG_ERRORS		-	argumented pointer is NULL
										HASH_CALLOC_FAIL			-	calloc failed to establish memory
										HASH_LIST_CONSTR_FAIL		-	error while constructing list
										HASH_OK						-	OK
										HASH_CONSTR_BROKEN_CREATED	-	created broken hash
**/

int hash_ctor(hash** my_hash);





//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int hash_dump(hash* my_hash)
{
	OUT_DEB("\n#!#!#!##!#!#!#!#!!#! HASH DUMP BEGIN #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n");
	OUT_DEB("#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n\n");
	
	PRECOND(my_hash == NULL, HASH_DUMP_ARG_NULL, "# HASH DUMP ERROR: Argumented pointer is NULL\n\n#!#!#!##!#!#!#!#!!#!  HASH DUMP END  "
	"#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n\n");
	/*
	if (my_hash == NULL)
	{
		OUT_DEB("# HASH DUMP ERROR: Argumented pointer is NULL\n");
		OUT_DEB("\n#!#!#!##!#!#!#!#!!#! HASH DUMP END   #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n");
		OUT_DEB("#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!\n\n");
		return HASH_DUMP_ARG_NULL;
	}
	*/
	OUT_DEB("# Pointers of methods:\n",
			"# hash dunction \t\t\t\t= [%08x]\n",
			my_hash->hash_func);

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
	//if (my_hash == NULL) return HASH_CHECK_ARG_NULL;
	PRECOND(my_hash == NULL, HASH_CHECK_ARG_NULL, ""); 
	for (int i = 0; i < HASH_SIZE; ++i) 
		if (list_check(my_hash->table[i]) != LIST_CHECK_OK)
		{
			//list_dump(my_hash->table[i]);
			return HASH_CHECK_BAD;
		};
	
	return HASH_CHECK_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int hash_destruct(hash** my_hash)
{
	OUT_DEB("### HASH DESTRUCT BEGIN ###\n");
	
	PRECOND(my_hash == NULL, HASH_DEST_ARG_ERRORS, "# HASH DESTRUCT ERROR: Argumented pointer is NULL\n");
	/*
	if (my_hash == NULL)
	{
		OUT_DEB("# HASH DESTRUCT ERROR: Argumented pointer is NULL\n");
		return HASH_DEST_ARG_ERRORS;
	}
	*/
	OUT_DEB("# Calling hash_check()...");

	int ret = hash_check(*my_hash);

	if (ret != HASH_CHECK_OK) OUT_DEB("BAD!!\nTrying do destruct lists...\n");
	else OUT_DEB("OK\n");

	(*my_hash) -> hash_func = NULL;

	(*my_hash)->size = POISON;

	OUT_DEB("# Destructing lists...\n\n");
	
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		OUT_DEB("# Destructing %d'th list... ");
		ret = list_destruct((*my_hash)->table[i]);
		VERIFY(ret != LIST_OK, HASH_DEST_LIST_DEST_ERROR, "# FAILED!!!\n\nDESTRUCTION OF %d'TH LIST FAILED\n" );
		/*
		if (ret != LIST_OK)
		{
			OUT_DEB("FAILED!!!\n\nDESTRUCTION OF %d'TH LIST FAILED\n");
			return HASH_DEST_LIST_DEST_ERROR;
		}
		*/
		OUT_DEB("OK\n");
	}
	free(*my_hash);
	*my_hash = NULL;
	OUT_DEB("# Sucessfully destructed\n### HASH DESTRUCT FINISHED ###\n");
	return HASH_OK;	
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int hash_ctor(hash** my_hash)
{
	OUT_DEB("### HASH CONSTRUCT BEGIN ###\n");
	PRECOND(my_hash == NULL, HASH_CONST_ARG_ERRORS, "# HASH CONSTRUCT ERROR: Argumented pointer is NULL\n");
	/*
	if (my_hash == NULL)
	{
		OUT_DEB("# HASH CONSTRUCT ERROR: Argumented pointer is NULL\n");
		return HASH_CONST_ARG_ERRORS;
	}
	*/
	(*my_hash) = (hash*)calloc(1, sizeof(hash));
	OUT_DEB("# Memory received...\n");
	
	VERIFY((*my_hash) == NULL, HASH_CALLOC_FAIL,"# HASH CONSTRUCT ERROR: Calloc failed\n"); 
	/*
	if ((*my_hash) == NULL)
	{
		OUT_DEB("# HASH CONSTRUCT ERROR: Calloc failed\n");
		return HASH_CALLOC_FAIL;
	}
	*/
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		int ret = list_ctor(&((*my_hash)->table[i]));
		VERIFY(ret != LIST_OK, HASH_LIST_CONSTR_FAIL, "# HASH CONSTRUCT ERROR: %d'th list hasn't been constructed\n");
		/*
		if (ret != LIST_OK)
		{
			OUT_DEB("# HASH CONSTRUCT ERROR: %d'th list hasn't been constructed\n");
			return HASH_LIST_CONSTR_FAIL;
		}
		*/
		OUT_DEB("# %d'th list successfully constructed\n");
	}
	OUT_DEB("# Saving pointers of hash functions...\n");
	(*my_hash) -> hash_func	= hash_func_bits_move;			//the best is default
	(*my_hash)->size = HASH_SIZE;

	int ret = hash_check(*my_hash);

	POSTCOND(ret != HASH_CHECK_OK, HASH_CONSTR_BROKEN_CREATED,"\n# FAILED TO CONSTRUCT\n### HASH CONSTRUCT FINISHED ###\n"); 
	
	OUT_DEB("\n# Everything has been constructed successfully!\n");
	OUT_DEB("### HASH CONSTRUCT FINISHED ###");
	return HASH_OK;
	
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

/**
		@par			here you can find several hash functions, which are used by hash. DO NOT DELETE THEM.
**/

unsigned long long hash_func_zero(const char* word)
{
	assert(word);
	return 0;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

unsigned long long hash_func_first_ascii(const char* word)
{
	assert(word);
	return (unsigned long long)word[0];
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


unsigned long long hash_func_sum_ascii(const char* word)
{
	assert(word);
	int i = 0;
	unsigned long long sum = 0;
	while ((word[i] != 0) && (i < HASH_SIZE)) sum += word[i++];
	return sum;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


unsigned long long hash_func_average_ascii(const char* word)
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


unsigned long long hash_func_bits_move(const char* word)
{
	unsigned long long ret = 0;
	int i = 0;
	while ((word[i] != 0) && (i < HASH_SIZE)) 	ret = ((ret << sizeof(ret)* BITSPERBYTE - 1) | (ret >> 1)) ^ ((long long) word[i++]);
	return ret;
}

int hash_set_function(hash* my_hash, unsigned long long (*hash_func)(const char* word))
{
	/*
	if (my_hash == NULL)
	{
		OUT_DEB("# HASH SET FUNCTION ERROR: argumented hash table pointer is NULL\n");
		return HASH_BAD;
	}
	*/
	PRECOND(my_hash == NULL, HASH_BAD, "# HASH SET FUNCTION ERROR: argumented hash table pointer is NULL\n");
	PRECOND(hash_func == NULL, HASH_BAD, "# HASH SET FUNCTION ERROR: argumented function pointer is NULL\n");
	/*
	if (hash_func == NULL)
	{
		OUT_DEB("# HASH SET FUNCTION ERROR: argumented function pointer is NULL\n");
		return HASH_BAD;
	}
	*/
	if (hash_check(my_hash) != HASH_CHECK_OK) return HASH_BAD;

	my_hash -> hash_func = hash_func;

	if (hash_check(my_hash) != HASH_CHECK_OK) return HASH_BAD;

	return HASH_OK;
}