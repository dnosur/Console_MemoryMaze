#include "MouseInput.h"

MouseInput::MouseInput(){}

COORD MouseInput::Read() {
	

	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	DWORD prev_mode;
	GetConsoleMode(hin, &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	SetConsoleMode(hin, ENABLE_MOUSE_INPUT);

	while (!clickableFilds.empty()) {

		ReadConsoleInput(hin, &InputRecord, 1, &Events); 

		if (InputRecord.Event.MouseEvent.dwButtonState == 1)
		{
			coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
			coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

			if(ContainsClickableField(coord)) return coord;
		}
	}
}

void MouseInput::PushToClickable(COORD coord)
{
	clickableFilds.push_back(coord);
}

void MouseInput::SetClickableFields(std::vector<COORD> clickableFilds)
{
	this->clickableFilds.clear();
	this->clickableFilds.swap(clickableFilds);
}

std::vector<COORD> MouseInput::GetClickableFields()
{
	return clickableFilds;
}

int MouseInput::GetClickableFieldId(COORD coord)
{
	for (int i = 0; i < clickableFilds.size(); i++) {
		if (clickableFilds[i].X == coord.X && clickableFilds[i].Y == coord.Y) return i;
	}

	return -1;
}

COORD MouseInput::GetClickableFieldById(int i)
{
	if (i >= 0 && i < clickableFilds.size()) return clickableFilds[i];
	return { -1, -1 };
}

void MouseInput::ClearClickableFields()
{
	clickableFilds.clear();
}

bool MouseInput::ContainsClickableField(COORD coord)
{
	for (COORD value : clickableFilds) {
		if (value.X == coord.X && value.Y == coord.Y) return true;
	}
	return false;
}
