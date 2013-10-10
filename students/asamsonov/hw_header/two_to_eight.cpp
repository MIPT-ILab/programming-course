#include "mainheader.h"

//{-------------two_to_eight.cpp-----------------------
//! @ingroup two_to_eight
//! @brief   Переводит int в char 
//!
//! @param   i		целое число
//!
//! @return  c		символ
//!
//! @see     ctoi(), ttoe()
//!
//! @warning int от '0' до '9'
//}-------------two_to_eight.cpp-----------------------

char itoc (int i)
{
	return i + '0';
}

//{-------------two_to_eight.cpp-----------------------
//! @ingroup two_to_eight
//! @brief   Переводит char в int 
//!
//! @param   c		символ
//!
//! @return  i		целое число
//!
//! @see     itoc(), ttoe()
//!
//! @warning char от '0' до '9'
//}-------------two_to_eight.cpp-----------------------

int ctoi (char c)
{
	return c - '0';
}

//{-------------two_to_eight.cpp-----------------------
//! @ingroup two_to_eight
//! @brief   Переводит строку из двоичной СС в восьмеричную.
//!
//! @param[out]   strt	Строка в двоичной СС
//! @param[out]   stre	Строка в восьмеричной СС
//!
//! @see     itoc(), ctoi()
//!
//! @warning char от '0' до '9'
//}-------------two_to_eight.cpp-----------------------

void ttoe (char *strt, char * stre)
{
	int i = 0;
	int len = strlen (strt);
	int maxi = len / 3;
	int minus = len - maxi * 3;

	if (minus == 1) stre[0] = strt[0];
	if (minus == 2) stre[0] = strt[0] * 2 + strt[1];

	for (i = 0; i < maxi; i ++)
		stre[i + 1] = itoc(ctoi(strt[i * 3 + minus]) * 4 + ctoi(strt[i * 3 + 1 + minus]) * 2 + ctoi(strt[i * 3 + 2 + minus]));
}

//{-------------two_to_eight.cpp-----------------------
//! @ingroup two_to_eight
//! @brief   Функция псевдо_main, исполняется в main.cpp, 
//!			 если в main_defines определен _TTOE
//!
//! @return  1 (Ошибка выполнения) | 0 (Все хорошо).
//!
//! @see     ttoe(), ctoi(), itoc()
//}-------------two_to_eight.cpp-----------------------

int two_to_eight_main()
{
	char *strt = (char *)calloc (MAXSTRING, sizeof(*strt)), *stre = (char *)calloc (MAXSTRING, sizeof(*stre));

	VERSION_OUT;
	OUT ("\n# Input string, containing only '0' and '1'.\n");
	
	scanf("%s", strt);
	ttoe(strt, stre);

	printf("%s\n", stre);
	return 0;
}