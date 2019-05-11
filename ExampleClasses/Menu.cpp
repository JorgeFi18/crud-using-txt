#include "Menu.h"
#include "Operaciones.h"
#include "Helpers.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

Operaciones operacion;

//Metodo constructor
Menu::Menu()
{
	seleccion = 0;
}

//Metodo Destructor
Menu::~Menu()
{
	seleccion = 0;
}

int Menu::Principal()
{
	system("cls");

	cout << "\n***** MENU PRINCIPAL *****\n\n";
	cout << "1. Planta Medicinal \n";
	cout << "2. Planta Silvestre \n";
	cout << "3. Planta Ornamental \n";
	cout << "4. Salir \n";

	cout << "\t Seleccione una opcion: ";
	cin >> seleccion;
	return seleccion;
}

int Menu::SubMenu(string tipoPlanta)
{
	string nombrePlanta = plantaMayuscula(tipoPlanta);
	system("cls");
	cout << "\n ***** MENU PLANTA " << nombrePlanta <<" ***** \n\n";
	cout << "1. Registro planta " << tipoPlanta  <<"\n";
	cout << "2. Muestra catalogo de planta " <<tipoPlanta <<"\n";
	cout << "3. Modificacion planta "<<tipoPlanta <<" \n";
	cout << "4. Cambio de estado planta " <<tipoPlanta <<" \n";
	cout << "5. Regresar a menu principal \n";
	cout << "6. Salir \n";

	cout << "\tSeleccione una opcion: ";
	cin >> seleccion;
	if (seleccion == 6)
		exit(0);
	return seleccion;
}

int Menu::EstadoMenu(string tipoPlanta)
{
	string nombrePlanta = plantaMayuscula(tipoPlanta);
	system("cls");
	cout << "\n ***** MENU CAMBIO DE ESTADO DE PLANTA TIPO " << nombrePlanta << " ***** \n\n";
	cout << "1. Dar planta " << tipoPlanta <<" de baja\n";
	cout << "2. Dar planta " << tipoPlanta <<" de alta\n";
	cout << "3. Regresar a menu principal \n";
	cout << "4. Salir \n";	
	cout << "\tSeleccione una opcion: ";
	cin >> seleccion;
	if (seleccion == 4)
		exit(0);
	return seleccion;
}

void Menu::OpcionesMenu(int seleccion, string tipoPlanta)
{
	switch (seleccion)
	{
	case 1: //guardar
		RegistroPlanta(tipoPlanta);
		break;
	case 2: //listar
		operacion.Mostrar(tipoPlanta);
		break;
	case 3://modificar
		operacion.Modificar(tipoPlanta);
		break;
	case 4://cambio de estado
		OpcionesEstado(EstadoMenu(tipoPlanta), tipoPlanta);
		//operacion.CambioEstado(tipoPlanta);
		break;
	}
}

void  Menu::OpcionesEstado(int seleccion, string tipoPlanta)
{
	switch (seleccion)
	{
	case 1:
		operacion.CambioEstado(tipoPlanta);
		break;
	case 2:
		operacion.CambioEstado(tipoPlanta, true);
		break;
	}
}

void Menu::RegistroPlanta(string tipoPlanta) {
	system("cls");
	Planta ingreso;
	cout << "\n ***** Registrar nueva planta ***** \n";
	cout << "Tipo de planta: " << tipoPlanta << "\n\n";
	cout << "\tCodigo de planta: ";
	ingreso.numeroPlanta = operacion.Correlativo(tipoPlanta);
	cout << ingreso.numeroPlanta <<endl;
	cout << "\n\tIngrese nombre de planta: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, ingreso.nombrePlanta);

	ingreso.archivo = tipoPlanta + ".txt";
	
	operacion.Registro(ingreso);
}
