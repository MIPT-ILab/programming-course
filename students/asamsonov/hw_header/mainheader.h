//{-------------head----------------------------------
//
//! @file    mainheader.h
//! @mainpage
//! @brief   Homework for the ILab course.
//!
//!          $Version: 0.02, Revision: 2 $
//!          $Date: 2013-10-06 00:01 $
//!
//!          mainheader.h is my test of how headers work and so on.
//!			 it will unite some little programs in the bigger one,
//!			 where you can switch between parts easily or even
//!			 choose which one to run in the console.
//!
//! @todo	 write:
//!			 - one program from 1st group.  (+)
//!			 - one program from 2nd group.  (+)
//!			 - one program from 3rd group.  (+)
//!			 - one program from 4th group.  (+)
//!			 - unite them.				    (+)
//!			 - write doxygen docs for this. (+)
//!
//--------------groups--------------------------------
//!
//! @defgroup main_defines			Определения main()
//!	@defgroup vowel_tripple			Утроение гласных
//! @defgroup spacemonster_summon	Удаление всех пробелов из строки.
//! @defgroup russian_vowel			Проверка русских букв на "гласность"
//! @defgroup two_to_eight			Перевод из двоичной СС в восьмеричную.
//! @defgroup technical				Технические детали
//!
//}-------------head----------------------------------

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//{-------------main.cpp------------------------------
//! @ingroup main_defines
//! @brief   Определение @c VOWEL говорит нам о том, что в
//!			 main.cpp запустится функция @c vowel_main().
//!			 То же самое для других определений.
//!
//! @see     vowel_main(), spacemonster_main(), russian_main(), two_to_eight_main()
//!
//! @warning Предполагается, что определена только одна функция
//!			 main. Поэтому если определены две, в main.cpp 
//!			 выполнится та, которая была определена первой.
//! @hideinitializer
//}-------------main.cpp------------------------------

#define VOWEL
//#define SPACE
//#define RUSCV
//#define _TTOE

//{-------------main.cpp------------------------------
//! @ingroup main_defines
//! @brief   @c RUN_PROGRAM - определение запускаемой в @c main.cpp
//!			 программы. Оно зависит от определений main выше.
//!
//! @see     vowel_main(), spacemonster_main(), russian_main(), two_to_eight_main()
//!
//! @warning Предполагается, что определена только одна функция
//!			 main. Поэтому если определены две, в @c main.cpp 
//!			 выполнится та, которая была определена первой.
//! @hideinitializer
//}-------------main.cpp------------------------------

#if   defined (VOWEL)
	#define RUN_PROGRAM			vowel_main()   
#elif defined (SPACE)
	#define RUN_PROGRAM	 spacemonster_main()
#elif defined (RUSCV)
	#define RUN_PROGRAM		  russian_main()
#elif defined (_TTOE)
	#define RUN_PROGRAM  two_to_eight_main()
#else
	#define RUN_PROGRAM  printf("There is nothing to run.\n")
#endif

//{-------------EJudgeClient--------------------------
//! @ingroup technical
//! @brief   Макрос для хорошей работы на системе EJudge.
//!
//! @warning Предполагается, что @c _EJC определена, иначе 
//!			 программа выполняется без поясняющих комментариев.
//! @hideinitializer
//}-------------EJudgeClient--------------------------

#ifdef _EJC
    #define OUT printf
    #define EJC_OUT if (0) printf
#else
    #define OUT if (0) printf
    #define EJC_OUT printf
#endif

//{-------------EJudgeClient--------------------------
//! @ingroup technical
//! @brief   Макрос для вывода информация о программе.
//!
//! @warning Предполагается, что @c _EJC определена, иначе 
//!			 программа выполняется без поясняющих комментариев.
//! @hideinitializer
//}-------------EJudgeClient--------------------------

#define VERSION_OUT OUT ("# Hello @! This is %s. \n# It's compiled %s at %s by Anton Samsonov\n",\
						 strrchr (__FILE__, '\\' ) + 1, __DATE__, __TIME__);

//{------------debugging------------------------------
//! @ingroup technical
//! @brief   Макрос ASSERT. Работает при незакоментированном
//!			 определении DEBUG.
//! @hideinitializer
//}------------debugging------------------------------

#define DEBUG

//-------------debugging------------------------------

#ifdef DEBUG
    #define ASSERT( cond )                          \
    if (!(cond)) {                                  \
        fprintf (stderr, "# Assertion fail : %s. "  \
                        "File %s, line %d\n",       \
                        #cond, __FILE__, __LINE__); \
        abort();                                    \
    }
#else
    #define ASSERT( cond )
#endif

//{-------------max_amount_of_chars_in_string----------
//! @ingroup technical
//! @brief   Максимальная длина строки в подпрограммах.	
//! @hideinitializer
//{-------------max_amount_of_chars_in_string----------
#define MAXSTRING 256

//--------------mainheader.h---------------------------
//{		Функции из подпрограмм:
//--------------mainheader.h---------------------------

int is_vowel (char symb);

void vowel_tripple (char str[]);

int vowel_main (void);

void str_char_delete (char *str, char del);

int spacemonster_main ();

int check_russian(char symb);

int russian_main();

char itoc (int i);

int ctoi (char c);

void ttoe (char *strt, char *stre);

int two_to_eight_main ();