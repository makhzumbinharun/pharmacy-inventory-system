#include "utils.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <stdlib.h>
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

/* Detects the actual terminal width in characters.
   Falls back to 80 (classic console width) if detection fails. */
int getTerminalWidth(void) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return 80;
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0) {
        return w.ws_col;
    }
    return 80;
#endif
}

void printCentered(const char *text) {
    int width = getTerminalWidth();
    int len = strlen(text);
    int padding = (width - len) / 2;

    if (padding < 0) {
        padding = 0;
    }

    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }

    printf("%s\n", text);
}

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nPress Enter to continue...");
    fflush(stdout);

    while ((c = getchar()) != '\n' && c != EOF);
}
