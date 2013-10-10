#include "mainheader.h"

//{-------------spacemonster_summon.cpp----------------
//! @ingroup spacemonster_summon
//! @brief   Удаляет все символы @del из строки.
//!
//! @param[out]   str		строка, из которой удаляем символы
//! @param		  del		удаляемый символ
//}-------------spacemonster_summon.cpp----------------

void str_char_delete (char *str, char del)
{
	int i = 0, j = 0;
	int len = strlen (str);
	
	for (i = 0; i < len; i ++) 
		if (str[i] != del) str[j++] = str[i];
	str[j] = '\0';
}

//{-------------spacemonster_summon.cpp----------------
//! @ingroup spacemonster_summon
//! @brief   Функция псевдо_main, исполняется в main.cpp, 
//!			 если в main_defines определен SPACE
//!
//! @return  1 (Ошибка выполнения) | 0 (Все хорошо).
//!
//! @see     str_char_delete()
//}-------------spacemonster_summon.cpp----------------

int spacemonster_main ()
{
	char string[MAXSTRING] = {};
	char current_c = NULL;
	int i = 0;

	VERSION_OUT;

	OUT ("\n# Input a string, containing as much spaces as you can type. \n"
		 "# The more spaces, the better for space monster summon.\n");

	while ((current_c = getchar ()) && (current_c != '\n') && (current_c != EOF)) {
		if (i >= MAXSTRING) { printf("String is full. Input no more than %d symbols\n", MAXSTRING - 1); return 1; }
		string[i++] = current_c;
	}
	OUT ("\n# There are your waste products.\n"
		 "# Unfortunately amount of spaces was too little for summon. :(\n");

	str_char_delete(string, ' ');
	printf("%s\n", string);

	return 0;
}