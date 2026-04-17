#ifndef SELECT_MENU_H
#define SELECT_MENU_H

#include <ncurses.h>
#include <iostream>

enum FractalType {
	MANDELBULB,
	MANDELBOX,
	FRACTAL_COUNT
};

FractalType selectFractalMenu();

#endif
