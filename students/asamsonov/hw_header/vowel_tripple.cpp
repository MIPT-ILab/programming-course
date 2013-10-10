#include "mainheader.h"

#define VOWEL_MULTIPLIER 3
#define CONSONANT_MULTIPLIER 1

//{-------------vowel_tripple.cpp----------------------
//! @ingroup vowel_tripple
//! @brief   Проверяет, является ли переменная 
//!			 гласной буквой латинницы.
//!
//! @param   symb		проверяемая переменная
//!
//! @return  1 (True) | 0 (False).
//!
//! @see     vowel_tripple ()
//!
//! @warning symb считается буквой латинницы.
//!			 Если это не так, функция вернет 0.
//}-------------vowel_tripple.cpp----------------------

int is_vowel (char symb)
{
	return (strchr ("AEIOUY", toupper (symb)) != NULL);   
}

//{-------------vowel_tripple.cpp----------------------
//! @ingroup vowel_tripple
//! @brief   Функция, которая вставляет вместо каждой 
//!			 гласной буквы в строке три таких буквы.
//!
//! @param[out]		str[]	строка
//!
//! @see     is_vowel ()
//}-------------vowel_tripple.cpp----------------------

void vowel_tripple (char str[])
{
	int nVowel = 0, i = 0;
	while (str[i] != '\0') 
		if (is_vowel (str[i++])) nVowel++;
	OUT ("# Number of vowels checked: %d.\n", nVowel);
	i--;
	int shift = nVowel * (VOWEL_MULTIPLIER - 1);
	while (i >= 0) {
		//ASSERT();
		str[i + shift] = str[i--];
	}
	OUT ("# String shifted.\n");
	i = shift;
	int i_new = 0, n = 0;
	while (str[i] != '\0') {
		if (is_vowel (str[i])) 
			for (n = 0; n < VOWEL_MULTIPLIER; n++)
				str[i_new++] = str[i];
		else 
			for (n = 0; n < CONSONANT_MULTIPLIER; n++)
				str[i_new++] = str[i];
		i++;
	}
}

//{-------------vowel_tripple.cpp----------------------
//! @ingroup vowel_tripple
//! @brief   Функция псевдо_main, исполняется в main.cpp, 
//!			 если в main_defines определен VOWEL
//!
//! @return  1 (Ошибка выполнения) | 0 (Все хорошо).
//!
//! @see     is_vowel (), vowel_tripple ()
//}-------------vowel_tripple.cpp----------------------

int vowel_main (void)
{
	VERSION_OUT;

	if (VOWEL_MULTIPLIER < 1) { OUT ("# Wrong multiplier defined.\n"); return 1; }
	OUT ("# Input a string.\n");

	int i = 0;
	char current_c = NULL;
	char str[MAXSTRING * 3 + 1] = {};
	while ((current_c = getchar ()) && (current_c != '\n') && (current_c != EOF)) {
		if (i >= MAXSTRING) break;
		str[i++] = current_c;
	}
	str[MAXSTRING] = '\0';
	OUT ("# Got this.\n");

	vowel_tripple(str);

	fputs(str, stdout);
	putchar ('\n');

	OUT ("# There is your string with every vowel x%d and any other letter x%d\n",
		 VOWEL_MULTIPLIER, CONSONANT_MULTIPLIER);

	return 0;
}