#pragma once
#include <windows.h>
#include <string>
#include <conio.h>


void clear();
void pause();

void gotoxy(int X, int Y);

COORD getxy();
void getxy(int& x, int& y);

void lower_string(std::string& str);
std::string to_lower_string(std::string str);
