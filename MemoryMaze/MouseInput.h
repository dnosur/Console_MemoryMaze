#pragma once

#include <vector>
#include <Windows.h>

class MouseInput
{
	HANDLE hin;
	INPUT_RECORD InputRecord;
	DWORD Events;
	COORD coord;

	std::vector<COORD> clickableFilds;
public: 
	MouseInput();

	COORD Read();

	void PushToClickable(COORD coord);
	void SetClickableFields(std::vector<COORD> clickableFilds);
	std::vector<COORD> GetClickableFields();
	int GetClickableFieldId(COORD coord);
	COORD GetClickableFieldById(int i);
	void ClearClickableFields();
	bool ContainsClickableField(COORD coord);
};

