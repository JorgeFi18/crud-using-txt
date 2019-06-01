#include <string>
#include <stdio.h>  
#include <windows.h>  
using namespace std;

string serializeString(string str, bool reverse)
{
	string from = " ";
	string to = "-";
	if (reverse)
	{
		from = "-";
		to = " ";
	}

	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

string removeBreak(string str)
{
	string from = "\n";
	string to = "-";

	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

bool validateAnswer(string answer)
{
	bool output = answer.compare("s") == 0;
	return output;
}

string getNombrePlanta(int tipoPlanta)
{
	string nombre;
	switch (tipoPlanta)
	{
	case 1:
		nombre = "Medicinal";
		break;
	case 2:
		nombre = "Silvestre";
		break;
	case 3:
		nombre = "Ornamental";
		break;
	case 4:
		nombre = "Insumo";
		break;
	}

	return nombre;
}

void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}