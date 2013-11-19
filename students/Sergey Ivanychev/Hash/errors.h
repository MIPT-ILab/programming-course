enum extra_conditions
{
	LIST_ELEM_INTRPT_BAD				= 2001,
	LIST_ELEM_INTRPT_OK					= 2002,
	LIST_INTRPT_OK						= 2003,
	LIST_INTRPT_BAD						= 2003,
};

enum list_elem_errors
{
	ELEM_OK								= 1000,
	ELEM_CONSTR_PTR_NULL				= 1001,
	ELEM_CONSTR_CALLOC_FAILED			= 1002,
	ELEM_DEST_PTR_NULL					= 1003,
	ELEM_DEL_PTR_NULL					= 1004,
	ELEM_CHECK_OK						= 1005,
	ELEM_DEL_NEXT_BROKEN				= 1006,
	ELEM_DEL_PREV_BROKEN				= 1007,
	ELEM_CHECK_PTR_NULL					= 1008,
	ELEM_CONSTR_VAL_OUT_OF_RANGE		= 1009,
	LIST_ELEM_PTR_NULL					= 1010,
	HASH_DUMP_ARG_NULL					= 1011,
	ELEM_CONSTR_VAL_NULL				= 1012,

	ELEM_DEL_DESTR_FAILED				= 1013,

};


const char* const list_elem_err_msgs[] =
{
	"",																//1000
	"ELEM CONSTRUCT ERROR: Argumented pointer is null\n",			//1001
	"ELEM CONSTRUCT ERROR: Calloc failed",							//1002
	"ELEM DESTRUCT ERROR: Argumented pointer is null\n",			//1003
	"ELEM DELETE ERROR: Argumented pointer is null\n",				//1004
	"",																//1005
	"ELEM DELETE ERROR: Next element exist and broken\n",			//1006
	"ELEM DELETE ERROR: Previous element exist and broken\n",		//1007
	"ELEM CHECK ERROR: Argumented pointer is null\n",				//1008
	"ELEM CONSTRUCT ERROR: Argumented string is out of range\n",	//1009
	"LIST ELEM ERROR: Argumented pointer of list_elem is NULL",		//1010
	"",																//1011
	"ELEM DELETE ERROR: destruction failed\n"	,					//1012
};

enum list_errors
{
	LIST_OK									= 1200,
	LIST_CHECK_PTR_NULL						= 1201,
	LIST_CHECK_LEN_BROKEN					= 1202,
	LIST_CHECK_HEAD_NULL					= 1203,
	LIST_CHECK_TAIL_NULL					= 1204,
	LIST_CHECK_REAL_SIZE_LOWER				= 1205,
	LIST_CHECK_REAL_SIZE_HIGHER				= 1206,
	LIST_CHECK_BROKEN_STRUCTURE				= 1207,
	LIST_CHECK_OK							= 1208,
	LIST_DESTR_INVALID_LIST					= 1209,
	LIST_DESTR_ELEM_DESTR_FAILED			= 1210,
	LIST_ADD_PTR_NULL						= 1211,
	LIST_ADD_VALUE_PTR_NULL					= 1212,
	LIST_ADD_CONSTR_FAILED					= 1213,
	LIST_BAD								= 1214,
	LIST_DELETE_OUT_OF_RANGE				= 1215,
	LIST_CONSTR_PTR_NULL					= 1216,
	LIST_DELWORD_NO_SUCH					= 1217,
	LIST_SEARCH_FOUND						= 1218,
	LIST_SEARCH_NO_SUCH						= 1219,
	LIST_OC_CHANGE_OUT_OF_RANGE				= 1220,

	LIST_CONSTR_CALLOC_FAILED				= 1221,		
};

const char* const list_error_msgs[] =
{
	"",
	"LIST CHECK ERROR: Argumented list pointer is null\n",
	"LIST CHECK ERROR: Length of list is broken\n",
	"LIST CHECK ERROR: HEAD is NULL, while LEN is not zero\n",
	"LIST CHECK ERROR: TAIL is NULL, while LEN is not zero\n",
	"LIST CHECK ERROR: Size of list is lower than expected\n",
	"LIST CHECK ERROR: Size of list is higher than expected\n",
	"LIST CHECK ERROR: Structure of list is broken\n",
	"",
	"LIST DESTROY ERROR: Invalid list\n",
	"LIST DESTROY ERROR: Some of elements hasn't been destroyed\n",
	"LIST ADD ERROR: Argumented list pointer is null\n",
	"LIST ADD ERROR: Argumented value pointer is null\n",
	"LIST ADD ERROR: Construction of element failed\n",
	"LIST ERROR: List checker found out error\n",
	"LIST DELETE ERROR: Index out of range",
	"LIST CONSTRUCT ERROR: Argumented pointer is NULL\n",
	"LIST DELETE WORD: No such element in list\n",
	"",
	"LIST SEARCH: No such element in list\n",
	"LIST OCCUR CHANGE: Argumented number of element of list is out of range\n",
	"LIST CONSTRUCT ERROR: Calloc returned NULL\n",
};


enum hash_errors
{
	HASH_ERRORS_BEGIN					= 1300,
	HASH_OK								= 1301,
	HASH_CONST_ARG_ERRORS				= 1302,
	HASH_CALLOC_FAIL					= 1303,
	HASH_LIST_CONSTR_FAIL				= 1304,
	HASH_CHECK_ARG_NULL					= 1305,
	HASH_CHECK_BAD						= 1306,
	HASH_CHECK_OK						= 1307,
	HASH_DEST_ARG_ERRORS				= 1308,
	HASH_DEST_LIST_DEST_ERROR			= 1309,
	HASH_CONSTR_BROKEN_CREATED			= 1310,
	HASH_ERRORS_END						= 1311,

};