#pragma once

#include <iostream>
#include <map>

#include "functions.h"
#include "MouseInput.h"

#include "Color.h"
#include "coords.h"

using namespace std;

class GameController
{
	int** field;
	
	map<int, COORD> steps;

	int field_row;
	int field_col;

	int steps_count;

	MouseInput mouseInput;

	bool end, win;

	Color color;

	void GenerateField();
	void ShowField();

	map<int, COORD>::iterator GetStepByCoord(COORD coord);

	COORD ConvertToFieldCoords(COORD mouse_pos);
	COORD ConvertToFieldCoords(int clickable_field_id);
public:

	GameController();

	void Start();
	void Update();
	void End();
};