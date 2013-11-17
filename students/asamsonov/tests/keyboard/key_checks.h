#ifndef KEYCHECKSHEADER
#define KEYCHECKSHEADER
#define KEYCHECKSVERSION 50

#include <stdio.h>
#include <stdlib.h>
#include <shlobj.h>

const int FPS = 30;

bool keyboard_check (int nVirtKey);

bool keyboard_check_pressed (int nVirtKey);

bool keyboard_check_released (int nVirtKey);

#endif