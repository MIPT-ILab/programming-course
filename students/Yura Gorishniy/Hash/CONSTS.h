const int POiSON = 228;
const int HAPPY = 777;
const int SAD = -777;
const char STR_POiSON = 'Z';
const int KEY_SIZE = 10;
const int HASH_SIZE = 100;
const int MAXLEN = 30;

enum ELEM_ERROR
{
	ERR_ELEM_NULL = -1100,
	ERR_ELEM_PREV,
	ERR_ELEM_NEXT,
};

enum LIST_ERROR
{
	ERR_LIST_FIRST_LAST_POINTERS = -2100,
	ERR_LIST_WRONG_FIRST_LAST,
	ERR_LIST_LEN,
	ERR_LIST_BAD_ELEM,
	ERR_LIST_NULL,
};

enum HASH_ERROR
{
	ERR_HASH_BAD_LIST = -3000,
};
