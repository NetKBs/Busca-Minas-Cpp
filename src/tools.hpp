#include <cstdlib>
#include <iostream>

#ifndef TOOLS_H
#define TOOLS_H

// Identify OS
#ifdef _WIN32
#define OS "Windows"
#elif __linux__
#define OS "Linux"
#endif

inline void clearScreen() {
  if ((std::string)OS == "Linux") {
    system("clear");
  } else {
    system("cls");
  }
}

inline void waitForInput() {
  std::cin.ignore();
  std::cin.get();
}

#endif