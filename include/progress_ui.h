#ifndef PROGRESS_UI_H
#define PROGRESS_UI_H

#include <ncurses.h>
#include <string>
#include <chrono>

class ProgressUI {
private:
    WINDOW* win;
    int height, width;
    int startY, startX;
    
public:
    ProgressUI(const std::string& title) {
        clear();
        getmaxyx(stdscr, height, width);
        
        int winHeight = 10;
        int winWidth = 60;
        startY = (height - winHeight) / 2;
        startX = (width - winWidth) / 2;
        
        win = newwin(winHeight, winWidth, startY, startX);
        box(win, 0, 0);
        
        wattron(win, A_BOLD);
        mvwprintw(win, 1, 2, "%s", title.c_str());
        wattroff(win, A_BOLD);
        
        mvwprintw(win, 3, 2, "Progress:");
        wrefresh(win);
    }
    
    void update(const std::string& status, int current, int total) {
        float percent = 100.0f * current / total;
        
        // Статус
        mvwprintw(win, 5, 2, "%-40s", status.c_str());
        
        // Прогресс-бар
        int barWidth = 40;
        int filled = barWidth * current / total;
        
        mvwprintw(win, 7, 2, "[");
        for (int i = 0; i < barWidth; i++) {
            if (i < filled) waddch(win, '=');
            else waddch(win, ' ');
        }
        wprintw(win, "] %3.0f%%", percent);
        
        wrefresh(win);
    }
    
    void finish(const std::string& message) {
        mvwprintw(win, 5, 2, "%-40s", message.c_str());
        mvwprintw(win, 8, 2, "Press any key to continue...");
        wrefresh(win);
        getch();
        delwin(win);
        clear();
        refresh();
    }
    
    ~ProgressUI() {
        if (win) delwin(win);
    }
};

#endif