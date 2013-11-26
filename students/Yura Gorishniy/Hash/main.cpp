#define _CRT_SECURE_NO_WARNINGS
#include "Hash.h"

int get_word (FILE* file, char* word);
FILE* the_log  = fopen ("the_log.txt", "w");

int main ()
{
	FILE* the_log  = fopen ("the_log.txt", "w");
	FILE* the_table = fopen ("the_table.csv", "w");
	FILE* the_text = fopen ("the_text.txt", "r");

	assert (the_log);
	assert (the_table);
	assert (the_text);

	hash* the_hash = Hash_NEW();
	assert (the_hash);

	char word[MAXLEN] = {};
	int nWords = 0;
	typedef unsigned int (*hash_funcs) (const char* my_key);
	hash_funcs hf[5] = {hf0, hf1, hf2, hf3, hf4};
	int func_num = 0;
	char text_description[2 * MAXLEN] = {};
	strcpy (text_description, "Bradbury's novel \"Fahrenheit 451\"");

	OUT printf ("# This program allows to use hash-functions for sorting\n"
				"# words in %s\n"
                "# The developer:     Yura Gorishniy     <strausmg@gmail.com>\n"
                "# Version 1.00\n"
                "# The file: %s\n"
                "# The compilation time: %s, %s\n\n", text_description, strrchr (__FILE__, '\\'), __DATE__, __TIME__);

	printf ("# You can use 5 hash-functions to analyse the novel:\n"
			"# Function [1]	hash = 0\n"
			"# Function [2]	hash = the ASCII code of the first letter of the word\n"
			"# Function [3]	hash = the sum of ASCII codes of all letters of the word\n"
			"# Function [4]	hash = the average ASCII code of all letters of the word\n"
			"# Function [5]	hash = the number, which we get after right cyclic shift\n"
			"# P.S. All the hashes you get will be counted by module %d\n\n", HASH_SIZE);

	printf ("# Please, enter the number of function you want to use\n");
	if (!scanf ("%d", &func_num))
	{
		printf ("Incorrect input, try again");
		abort ();
	}

	the_hash -> func = hf[func_num - 1];

	while (1)
	{
		if (get_word (the_text, word) == 0) break;
		nWords++;
		int hash = the_hash -> func (word) % the_hash -> size;
		elem* new_elem = NULL;
		List_Elem_Find_Key (the_hash -> table[hash], word, &new_elem);
		if (!new_elem) List_Elem_Add (the_hash -> table[hash], word, 1);
	}

	for (int i = 0; i < HASH_SIZE; ++i) fprintf (the_table, "%d\n", the_hash -> table[i] -> length);

	Hash_Dump (the_hash);
	Hash_Delete (the_hash);

	fclose (the_text);
	fclose (the_table);
	fclose (the_log);

	printf ("\nThe job is done! \nYou can use the_table.csv in Microsoft Excel to get a nice diagram\nGoodbye!");
return 0;
}

int get_word (FILE* file, char* word)
{
	int word_size = 0;
	int c = 0;
	while (isalpha (c = fgetc (file)) == 0 && c != EOF);
	if (c == EOF) return 0;
	ungetc (c, file);
	while (isalpha (c = fgetc(file)) && word_size < MAXLEN - 1) word[word_size++] = c;
	word[word_size] = 0;
	toupper (word[0]);
return word_size;
}