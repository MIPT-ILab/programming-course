//{-------------head----------------------------------
//
//! @file    key_checks.cpp
//! @brief   Keyboard_check functions.
//!
//}-------------head----------------------------------

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

#include "key_checks.h"

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

#define KEY_PRSD_ON  -127
#define KEY_PRSD_OFF -128

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

bool KeyStatesPre [256] = {};

bool KeyStatesPost[256] = {};

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

/*
bool keyboard_check (int nVirtKey);

bool keyboard_check_pressed (int nVirtKey);

bool keyboard_check_released (int nVirtKey);
*/

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

bool keyboard_check (int nVirtKey)
{
	short Key = GetKeyState (nVirtKey);
	return !!(Key == KEY_PRSD_ON || Key == KEY_PRSD_OFF);
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

bool keyboard_check_pressed (int nVirtKey)
{
	short Key = GetKeyState (nVirtKey);
	bool State = !!(Key == KEY_PRSD_ON || Key == KEY_PRSD_OFF);

	if (State != KeyStatesPre[nVirtKey]) {
		KeyStatesPre[nVirtKey] = State;
		return State;
	}
	return 0;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

bool keyboard_check_released (int nVirtKey)
{
	short Key = GetKeyState (nVirtKey);
	bool State = !!(Key == KEY_PRSD_ON || Key == KEY_PRSD_OFF);

	if (State != KeyStatesPost[nVirtKey]) {
		KeyStatesPost[nVirtKey] = State;
		return !State;
	}
	return 0;
}