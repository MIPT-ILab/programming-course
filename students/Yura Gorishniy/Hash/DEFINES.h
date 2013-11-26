#define DEBUG

#ifdef DEBUG

    #define ASSERT_LIST_OK( my_list )							\
	if (List_OK (my_list) != HAPPY)								\
	{															\
		List_OK (my_list);										\
		abort();												\
	}															\

    #define ASSERT_HASH_OK( my_hash )							\
	if (Hash_OK (my_hash) != HAPPY)								\
	{															\
		Hash_OK (my_hash);										\
		abort();												\
	}															\

#else

    #define ASSERT(cond)
    #define ASSERT_CPU_OK( my_list )
    #define ASSERT_HASH_OK( my_hash )

#endif //DEBUG


//#define _EJC

#ifdef  _EJC
    #define OUT if (0)

#else
    #define OUT
#endif // _EJC

#define PRINT_ERROR( error )													\
printf ("\nERROR: %s \nWatch the_log.txt to get more information\n", #error);	\
fprintf (the_log, "\nERROR: %s    \n", #error)									\

/*#define CASE_ERR( err )													        \
    case ERR_##err:															    \
        printf ("\n" "There is an error: ERR_%s\nWatch the_log.txt to get more information\n", #err);		\
		fprintf (the_log, "\nThere is an error [ERR_%s]\n", #err);				\
        break																	\

#define CHOOSE_ERR						\
    CASE_ERR (ELEM_NULL);				\
    CASE_ERR (ELEM_PREV);				\
    CASE_ERR (ELEM_NEXT);				\
    CASE_ERR (LIST_FIRST_LAST_POINTERS);\
    CASE_ERR (LIST_WRONG_FIRST_LAST);	\
    CASE_ERR (LIST_LEN)*/