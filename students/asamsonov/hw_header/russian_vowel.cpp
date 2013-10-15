#include "mainheader.h"

//{-------------russian_vowel.cpp----------------------
//! @ingroup russian_vowel
//! @brief   Проверяет, является ли переменная 
//!			 гласной буквой кириллицы.
//!
//! @param   symb		проверяемая переменная
//!
//! @return  1 (True) | 0 (False).
//!
//! @warning symb считается буквой кириллицы.
//!			 Если это не так, функция вернет -1.
//}-------------russian_vowel.cpp----------------------

int check_russian(char symb)
{
	if (strchr ("АЕЁИОУЫЭЮЯ", toupper (symb)) != NULL) return 1;
	if (strchr ("БВГДЖЗЙКЛМНПРСТФХЦЧШЩЪЬ", toupper (symb)) != NULL) return 0;
	return -1;
}

//{-------------russian_vowel.cpp----------------------
//! @ingroup russian_vowel
//! @brief   Функция псевдо_main, исполняется в main.cpp, 
//!			 если в main_defines определен RUSCV
//!
//! @return  1 (Ошибка выполнения) | 0 (Все хорошо).
//!
//! @see     check_russian()
//}-------------russian_vowel.cpp----------------------

int russian_main()
{
	char scanned_char = '\0';
	int checked = 0;

	OUT ("# Привет, пользователь! С тобой говорит %s. \n"
		 "# Меня скомпилировал %s в %s Антон Самсонов\n", strrchr (__FILE__, '\\' ) + 1, __DATE__, __TIME__);
	_wsetlocale (LC_ALL, L"Russian_Russia.ACP");
	SetConsoleCP (1251);
    SetConsoleOutputCP (1251);

	scanned_char = getchar ();
	checked = check_russian (scanned_char);
	printf ("\'%c\' - %s\n", scanned_char, (checked == 1)? 
			" гласная буква." : (checked == 0)? " согласная буква." : "вообще непонятно что.");

	return 0;
}