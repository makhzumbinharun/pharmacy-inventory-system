#ifndef UTILS_H
#define UTILS_H

/* Detects the actual terminal width in characters at runtime.
   Falls back to 80 if detection isn't possible. */
int getTerminalWidth(void);

/* Prints one line of text centered within the current terminal's actual width. */
void printCentered(const char *text);

void clearScreen(void);
void pauseScreen(void);

#endif
