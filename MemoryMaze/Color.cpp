#include "Color.h"

Color::Color(){
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Color::SetColor(int text, int background) {
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Color::ResetColor() {
	SetConsoleTextAttribute(hStdOut, (WORD)((ConsoleColor::Black << 4) | ConsoleColor::White));
}
