/* ********************************** /
Proyecto final - Programacion 1

- Seccion A

Integrantes:
	Nombre: Jorge Eduardo Figueroa Melendez
	Carnet: 1990-17-14505

	Nombre: Hector Alfredo Guerra Jimenez
	Carnet: 1990-18-10585

/ ********************************** */

//Librerias externas
#include <iostream>

//Librerias internas
#include "Menu.h"

//Namespaces
using namespace std;


//Variables globales
Menu _menu;

int main()
{
	system("Color 1F");
	_menu.MenuPrincipalOpciones(_menu.MenuPrincipal());
}