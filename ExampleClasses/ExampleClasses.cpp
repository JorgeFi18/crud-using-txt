// 1990-17-1450
// Jorge Eduardo Figueroa Melendez
// Progra 1 - seccion A
//Hola Hector

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <locale.h>

#include "Menu.h"

using namespace std;



string NombrePlanta;

Menu menuClase;
int opcion = 0, opcionSubMenu = 0;

int main()
{
	setlocale(LC_CTYPE, "Spanish");
	do {
		opcion = menuClase.Principal();
		switch (opcion)
		{
		case 1: //Planta medicinal
			opcionSubMenu = menuClase.SubMenu("medicinal");
			menuClase.OpcionesMenu(opcionSubMenu, "medicinal");
			break;
		case 2: //Planta silvestre
			opcionSubMenu = menuClase.SubMenu("silvestre");
			menuClase.OpcionesMenu(opcionSubMenu, "silvestre");
			break;
		case 3: //Planta ornamental
			opcionSubMenu = menuClase.SubMenu("ornamental");
			menuClase.OpcionesMenu(opcionSubMenu, "ornamental");
			break;
		case 4:
			exit(0);
			break;
		}
	} while (opcion < 4);
	_getch();
	return 0;
}