//{-------------head----------------------------------
//
//! @file    main.cpp
//! @brief   Keyboard_check tests.
//!
//}-------------head----------------------------------

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

#include "key_checks.h"

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int main (int argc, const char *argv[])
{
	printf ("# Hello @! This is %s. \n# It's compiled %s at %s by Anton Samsonov\n\n",\
						 strrchr (argv[0], '\\' ) + 1, __DATE__, __TIME__);

	printf ("This is keyboard checks test. Press VK_LEFT to check it is pressed / released.\n" 
			"Press VK_RIGHT to end test. You can change FPS in the \"key_checks.h\".\n\n");

	while (1) {

		if (keyboard_check_pressed (VK_LEFT)) 
			printf ("left pressed\n");
		
		if (keyboard_check (VK_LEFT)) 
			printf ("\t" "left\n");
		
		if (keyboard_check_released (VK_LEFT)) 
			printf ("left released\n");
		
		if (keyboard_check_pressed (VK_RIGHT)) {
			printf ("right got\n");
			break;
		}

		Sleep (1000 / FPS);
	}
	return 0;
}