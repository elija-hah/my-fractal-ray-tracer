#include "../include/select_menu.h"

const char* fractalNames[FRACTAL_COUNT] = {"Mandelbulb", "Mandelbox"};

FractalType selectFractalMenu() {
	int width, height;
	
	initscr();	// Create standard screen
	cbreak();	// Disable line buffering
	noecho();	// Obvious
	keypad(stdscr, TRUE);	// Enable special keyboard keys (i'll use arrows)
	curs_set(0);	// Hide the cursor
	//start_color();  // Включить поддержку цветов
	//use_default_colors();  // Использовать цвета по умолчанию
	//init_pair(0, COLOR_WHITE, COLOR_BLACK);
	getmaxyx(stdscr, height, width);	// Get terminal dimensions

	FractalType selected = MANDELBULB;
	bool menuActive = true;

	while(menuActive) {
		clear();
		int startX = width/2 - 15;
		int startY = height/2 - FRACTAL_COUNT / 2 - 3;

		attron(A_BOLD);
		mvprintw(startY-3, startX, "FRACTAL RENDERER");
		mvprintw(startY-2, startX, "================");
		attroff(A_BOLD);
		mvprintw(startY-1, startX, "SELECT FRACTAL:");

		for(int i = 0; i < FRACTAL_COUNT; ++i) {
			if (i == selected) attron(A_STANDOUT);
			mvprintw(startY + i, startX, "%d. %s", i + 1, fractalNames[i]);
			if (i == selected) attroff(A_STANDOUT);
		}
		
		attron(A_BOLD);
		mvprintw(startY + FRACTAL_COUNT+1, startX-10, "In menu:");
		attroff(A_BOLD);
		mvprintw(startY + FRACTAL_COUNT+2, startX-10, "Arrows - navigate    Enter - confirm");
		mvprintw(startY + FRACTAL_COUNT+3, startX-10, "q - exit program");

		refresh();

		bool tryAgain = true;
		while (tryAgain) {
			tryAgain = false;
			int ch = getch();
			switch (ch) {
				case KEY_UP:
					selected = static_cast<FractalType>((selected - 1 + FRACTAL_COUNT) % FRACTAL_COUNT); break;
				case KEY_DOWN:
					selected = static_cast<FractalType>((selected + 1) % FRACTAL_COUNT); break;
				case 10: case 13:
					return selected;
				case 'q':
					endwin();
					exit(0);
				case KEY_RESIZE:
					getmaxyx(stdscr, height, width); break;
				default:
					tryAgain = true;
			}	
		}
		
	}
	std::cout << "Reached end of non-void function 'selectFractalMenu()'" << std::endl;
	return FRACTAL_COUNT;
}
