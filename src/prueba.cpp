#include <cstdio>
#include <iostream>

#ifdef _WIN32
#define OS "Windows"
#include <curses.h>
#elif __linux__
#define OS "Linux"
#include <ncurses.h>
#endif

using namespace std;

int main() {
  initscr();            // Initialize ncurses
  noecho();             // Disable key echoing
  cbreak();             // Take inputs character by character
  keypad(stdscr, TRUE); // Enable keyboard mapping

  int x = 0, y = 0; // Start at (0,0) position

  while (1) {
    int ch = getch();
    if (ch == 'w' || ch == 'k')
      y--; // Move up
    else if (ch == 's' || ch == 'j')
      y++; // Move down
    else if (ch == 'a' || ch == 'h')
      x--; // Move left
    else if (ch == 'd' || ch == 'l')
      x++; // Move right

    // Wrap around edges
    if (x > 7)
      x = 0;
    if (x < 0)
      x = 7;
    if (y > 7)
      y = 0;
    if (y < 0)
      y = 7;

    mvprintw(y, x, "*"); // Print * at current position
    refresh();
  }

  endwin(); // End ncurses
  return 0;
}