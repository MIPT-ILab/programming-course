/**
		@file							main.cpp
		@author							Sergey Ivanychev, group 376, DCAM MIPT
		@mainpage

		@par							That program checks performance of different hashing algorithmes, building .csv files
										to build plots in Excel.
		
		@version						V 1.00

		@par							This is prototype of hash table, which can onlu include words and strings.
										Inputted file is 1984.txt, because WINDOWS CONSOLE IS SO SHIT
										
**/
#include <iostream>
#include <windows.h>
#include <process.h>
#include "errors.h"
#include "hash.h"

FILE* strerr = NULL;

const int MAXLEN = 100;

/**
		get_word						functions scans for the next word, which contain only russian or english words

		@param[out]		strin			input file stream
		@param[out]		save_to			the pointer where scan word will be saved if successful

		@return							size of scanned word
**/
int get_word(FILE* strin, char* save_to);

/**
		my_isalpha						analogue of isalpha function. Works with russian and english letters
			
		@param			c				analyzed character

		@return							-1 if EOF, 0 if not alphabetical, otherwise 1
**/
int my_isalpha(int c);

/**
		rus_toupper						converts russian or english capital character to lower register

		@param[out]		first_letter	pointer to analyzed character
**/
void rus_toupper(char* first_letter);

/**
		generate_stats					function scans the input text and uses hash functions to put unique word into hash table

		@param[out]		my_hash			pointer to current hash table
		@param[out]		name_file		file name of inputted text
		@param[out]		strin			input file stream
		@param[out]		h_function		used hash function

		@return							0
**/
int generate_stats(hash* my_hash, const char* name_file, FILE* strin, unsigned long long(*h_func)(char*));

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

#define RELOAD_HASH_															\
	hash_destruct(&my_hash);													\
	ret = hash_construct(&my_hash);												\
																				\
	if (ret == NULL)															\
	{																			\
		OUT("# MAIN ERROR: HASH CONSTRUCT ERROR\n# TERMINATING...\n");			\
		fclose(strerr);															\
		fclose(strin);															\
		return -1;																\
	}



int main(int argc, char* argv[])
{
	_wsetlocale(LC_ALL, L"Russian_Russia.ACP");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	strerr = fopen("log.txt", "w");
	assert(strerr);

	fprintf(stdout, "Hello, I'm creating the hash taable of words, containing in .txt file,\n"
		"print gystogram and build .csv file write in my dyrectory.\n"
		"I'm %s program, compiled in %s %s\n"
		"Please, type the name of inputting file\n"
		__FILE__, __TIME__, __DATE__);
	FILE* strin = fopen("1984.txt", "r");
	FILE* strout = stdout;

	if (strin == NULL)
	{
		fprintf(strerr, "ERROR: File for input hasn't been opened\n");
		fclose(strerr);
		return -1;
	}

	hash* my_hash = NULL;
	int ret = hash_construct(&my_hash);
	
	if (ret == NULL)
	{
		OUT("# MAIN ERROR: HASH CONSTRUCT ERROR\n# TERMINATING...\n");
		fclose(strerr);
		fclose(strin);
		return -1;
	}

	fputc('\n', strout);

	generate_stats(my_hash, "func_H0.csv", strin, my_hash->h0);
	fprintf(stdout, "1\n");
	RELOAD_HASH_;
	generate_stats(my_hash, "func_h_ascii_first.csv", strin, my_hash->h_ascii_first);
	fprintf(stdout, "2\n");
	RELOAD_HASH_;
	generate_stats(my_hash, "func_h_ascii_sum.csv", strin, my_hash->h_ascii_sum);
	fprintf(stdout, "3\n");
	RELOAD_HASH_;
	generate_stats(my_hash, "func_h_ascii_sum_over_num.csv", strin, my_hash->h_ascii_sum_over_num);
	fprintf(stdout, "4\n");
	RELOAD_HASH_;
	generate_stats(my_hash, "func_h_bits_move.csv", strin, my_hash->h_bits_move);
	fprintf(stdout, "5\n");
	RELOAD_HASH_;

	hash_destruct(&my_hash);
	fprintf(strout, "\n\nSuccessfully done\n");
	return 0;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int my_isalpha(int c)
{
	if (c == EOF) return -1;
	if ((isalpha(c) == 1) || ((c >= 192) && (c <= 255)) || (c == '-') || (c == '¸') || (c == '¨')) return 1;
	return 0;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


void rus_toupper(char* first_letter)
{ 
	if (((*first_letter >= 'À') && (*first_letter <= 'ß')) || ((*first_letter >= 'A') && (*first_letter <= 'Z'))) *first_letter += 32;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int get_word(FILE* strin, char* save_to)
{
	int word_size = 0;
	int c = 0;
	while (my_isalpha(c = fgetc(strin)) == 0);
	ungetc(c, strin);
	if (c == EOF) return 0;
	while ((my_isalpha(c = fgetc(strin)) == 1)&&(word_size < MAXLEN - 1)) save_to[word_size++] = c;
	save_to[word_size] = 0;

	rus_toupper(save_to);
	return word_size;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int generate_stats(hash* my_hash, const char* name_file, FILE* strin, unsigned long long(*h_func)(char*))
{
	FILE* strout = fopen(name_file, "w");
	assert(strout);
	char word[MAXLEN] = {};
	long i = 0;
	while (get_word(strin, word) > 0)
	{
		//printf("%d words\n", i++);
		i++;
		if (i % 1000 == 0) printf("%d\n", i);
		int hash = h_func(word) % my_hash->size;
		list_add(my_hash->table[hash], word);
	}
	for (int i = 0; i < HASH_SIZE; ++i) fprintf(strout, "%d;%d\n",i, my_hash->table[i]->len);
	fseek(strin, 0, SEEK_SET);
	return 0;
}