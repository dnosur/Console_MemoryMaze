#include "GameController.h"

void GameController::GenerateField()
{
	if (field_row >= 5 && field_col >= 5 && steps_count && steps_count <= (field_col * field_row)) {

		cout << "\n\n\t\t\t";
		mouseInput.ClearClickableFields();

		if (field) delete[] field;

		field = new int* [field_row];
		for (int i = 0; i < field_row; i++) {
			field[i] = new int[field_col];
			for (int j = 0; j < field_col; j++) {
				field[i][j] = 0;

				cout << "|";
				COORD coords = getxy();
				mouseInput.PushToClickable(coords);
				cout << "X|  ";
			}
			cout << endl << "\t\t\t";
		}

		steps.clear();
		for (int i = 0; i < steps_count;) {
			int y = rand() % field_row;
			int x = rand() % field_col;

			if (field[y][x] > 0) continue;

			field[y][x] = i + 1;

			COORD c = mouseInput.GetClickableFieldById(y * field_col + x);
			steps[i] = c;

			gotoxy(c.X, c.Y);
			color.SetColor(color.White, color.Green);
			cout << i;
			Sleep(2000);

			gotoxy(c.X, c.Y);
			color.ResetColor();
			cout << "X";
			i++;
		}

		gotoxy(0, 0);
	}
	else {
		end = true;
		win = false;
	}
}

void GameController::ShowField()
{
	if (true) {
		for (int i = 0; i < mouseInput.GetClickableFields().size(); i++) {
			COORD field_coords = ConvertToFieldCoords(mouseInput.GetClickableFields()[i]);

			gotoxy(mouseInput.GetClickableFields()[i].X - 1, mouseInput.GetClickableFields()[i].Y);
			cout << "|";

			if (field[field_coords.Y][field_coords.X] == -1) {
				color.SetColor(color.White, color.Green);
				cout << GetStepByCoord(mouseInput.GetClickableFields()[i])->first;
				color.ResetColor();
			}
			else cout << "X";

			cout << "|";
		}
	}
}

map<int, COORD>::iterator GameController::GetStepByCoord(COORD coord)
{
	for (map<int, COORD>::iterator i = steps.begin(); i != steps.end(); i++) {
		if (i->second.X == coord.X && i->second.Y == coord.Y) 
			return i;
	}
}

COORD GameController::ConvertToFieldCoords(COORD mouse_pos)
{
	int i = mouseInput.GetClickableFieldId(mouse_pos);
	COORD field_cords;

	field_cords.Y = trunc(i / field_col);
	field_cords.X = i - field_cords.Y * field_col;

	return field_cords;
}

COORD GameController::ConvertToFieldCoords(int clickable_field_id)
{
	COORD field_cords;

	field_cords.Y = trunc(clickable_field_id / field_col);
	field_cords.X = clickable_field_id - field_cords.Y * field_col;

	return field_cords;
}

GameController::GameController()
{
	field = 0;

	field_row = field_col = 0;
	steps_count = 0;
	end = win = false;
}

void GameController::Start()
{
	clear();

	do {
		cout << "Введите ширину поля (>= 5): ";
		cin >> field_col;
		clear();
	} while (field_col < 5);

	do {
		cout << "Введите высоту поля (>= 5): ";
		cin >> field_row;
		clear();
	} while (field_row < 5);

	do {
		cout << "Введите колличество ходов (>= 1 && <= " << (field_col * field_row) << "): ";
		cin >> steps_count;
		clear();
	} while (steps_count >= 1 && steps_count > (field_col * field_row));

	end = false;

	GenerateField();
	Update();
}

void GameController::Update()
{
	

	while (!end) {

		COORD coord = mouseInput.Read();

		COORD field_coords = ConvertToFieldCoords(coord);

		if (field[field_coords.Y][field_coords.X] > 0) {
			steps_count--;
			field[field_coords.Y][field_coords.X] = -1;

			if (!steps_count) {
				end = true;
				win = true;
			}
		}
		else if(field[field_coords.Y][field_coords.X] != -1) {
			end = true;
			win = false;

			gotoxy(coord.X, coord.Y);
			color.SetColor(color.White, color.Red);
			cout << "X";
			color.ResetColor();
			Sleep(1000);
			break;
		}

		clear();
		ShowField();
		Sleep(500);
	}

	End();
}

void GameController::End()
{
	clear();

	color.SetColor(win ? color.Green : color.Red);
	cout << "\n\n\t\t" << ((win) ? "Вы победили!!!" : "Вы проиграли :(") << endl;
	pause();
}
