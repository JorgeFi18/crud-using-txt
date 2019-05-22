//Librerias externas
#include <iostream>
#include <string>

//Librerias internas
#include "Menu.h"
#include "Planta.h"
#include "Helpers.h"

//Namespaces
using namespace std;

//clases
Planta _planta;

int opcion = 0;
string answer;

int Menu::MenuPrincipal() 
{
	system("cls");
	cout << "\n* * * * MENU PRINCIPAL * * * *\n\n";
	cout << "1) Plantas.\n";
	cout << "2) Insumos.\n";
	cout << "3) Inventario.\n";
	cout << "4) Clientes.\n";
	cout << "5) Facturacion.\n";
	cout << "6) Salir.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;

	return opcion;
}

void Menu::MenuPrincipalOpciones(int opcion) 
{
	switch (opcion) 
	{
	case 1:
		MenuPlantasOpciones(MenuPlantas());
		break;
	case 2:
		break;
	case 3:
		MenuInventarioOpciones(MenuInventario());
		break;
	}
}

int Menu::MenuPlantas()
{
	system("cls");
	cout << "\n* * * * MENU PLANTAS * * * *\n\n";
	cout << "1) Medicinales.\n";
	cout << "2) Silvestres.\n";
	cout << "3) Ornamentales.\n";
	cout << "4) Volver al menu principal.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;

	return opcion;
}

void Menu::MenuPlantasOpciones(int opcion)
{
	switch (opcion)
	{
	case 1: //Medicinal
		MenuTipoPlantaOpciones(MenuTipoPlanta(opcion), 1);
		break;
	case 2: //Silvestre
		MenuTipoPlantaOpciones(MenuTipoPlanta(opcion), 2);
		break;
	case 3: //Ornamental
		MenuTipoPlantaOpciones(MenuTipoPlanta(opcion), 3);
		break;
	case 4:
		MenuPrincipalOpciones(MenuPrincipal());
		break;
	}
}

int Menu::MenuTipoPlanta(int tipoPlanta)
{
	system("cls");
	string nombrePlanta = getNombrePlanta(tipoPlanta);
	cout << "\n* * * * MENU PLANTA * * * *\n\n";
	cout << "-Tipo de planta: " << nombrePlanta << endl <<endl;
	cout << "1) Registrar nueva planta.\n";
	cout << "2) Mostrar catalogo de planta.\n";
	cout << "3) Modificacion de planta.\n";
	cout << "4) Cambio de estado de planta.\n";
	cout << "5) Regresar al menu plantas.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;

	return opcion;
}

void Menu::MenuTipoPlantaOpciones(int opcion, int tipoPlanta)
{
	switch (opcion)
	{
	case 1:
		_planta.RegistrarPlanta(tipoPlanta);
		cout << "\n\nDesea agregar otra planta (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuTipoPlantaOpciones(1, tipoPlanta); }
		else { MenuTipoPlantaOpciones(MenuTipoPlanta(tipoPlanta), tipoPlanta); }
		break;
	case 2:
		_planta.MostrarPlantas(tipoPlanta);
		cout << "\n\nDesea listar las plantas de nuevo (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuTipoPlantaOpciones(2, tipoPlanta); }
		else { MenuTipoPlantaOpciones(MenuTipoPlanta(tipoPlanta), tipoPlanta); }
		break;
	case 3:
		_planta.ModificarPlanta(tipoPlanta);
		cout << "\n\nDesea editar otra planta (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuTipoPlantaOpciones(3, tipoPlanta); }
		else { MenuTipoPlantaOpciones(MenuTipoPlanta(tipoPlanta), tipoPlanta); }
		break;
	case 4:
		MenuCambioEstadoPlantaOpciones(MenuCambioEstadoPlanta(tipoPlanta), tipoPlanta);
		break;
	case 5:
		MenuPlantasOpciones(MenuPlantas());
		break;
	}
}

int Menu::MenuCambioEstadoPlanta(int tipoPlanta)
{
	system("cls");
	string nombrePlanta = getNombrePlanta(tipoPlanta);
	cout << "\n* * * * MENU CAMBIO DE ESTADO * * * *\n\n";
	cout << "-Tipo de planta: " << nombrePlanta << endl << endl;
	cout << "1) Dar planta de baja.\n";
	cout << "2) Dar planta de alta.\n";
	cout << "3) Volver al menu planta.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;

	return opcion;
}

void Menu::MenuCambioEstadoPlantaOpciones(int opcion, int tipoPlanta)
{
	switch (opcion)
	{
	case 1:
		_planta.CambioEstado(tipoPlanta);
		cout << "\n\nDesea dar de baja otra planta (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuCambioEstadoPlantaOpciones(1, tipoPlanta); }
		else { MenuCambioEstadoPlantaOpciones(MenuCambioEstadoPlanta(tipoPlanta), tipoPlanta); }
		break;
	case 2:
		_planta.CambioEstado(tipoPlanta, true);
		cout << "\n\nDesea dar de alta otra planta (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuCambioEstadoPlantaOpciones(2, tipoPlanta); }
		else { MenuCambioEstadoPlantaOpciones(MenuCambioEstadoPlanta(tipoPlanta), tipoPlanta); }
		break;
	case 3:
		MenuTipoPlantaOpciones(MenuTipoPlanta(tipoPlanta), tipoPlanta);
		break;
	}
}

int Menu::MenuInventario()
{
	system("cls");
	cout << "\n* * * * MENU INVENTARIO * * * *\n\n";
	cout << "1) Inventario de plantas medicinales.\n";
	cout << "2) Inventario de plantas silvestres.\n";
	cout << "3) Inventario de plantas ornamentales.\n";
	cout << "4) Iventario de insumos.\n";
	cout << "5) Volver al menu principal.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;
	return opcion;
}

void Menu::MenuInventarioOpciones(int opcion)
{
	switch (opcion)
	{
		case 1:
			MenuInventarioTipoOpciones(MenuInventarioTipo(1), 1);
			break;
		case 2:
			MenuInventarioTipoOpciones(MenuInventarioTipo(2), 2);
			break;
		case 3:
			MenuInventarioTipoOpciones(MenuInventarioTipo(3), 3);
			break;
		case 4:
			MenuInventarioTipoOpciones(MenuInventarioTipo(4), 4);
			break;
		case 5:
			MenuPrincipalOpciones(MenuPrincipal());
			break;
	}
}

int Menu::MenuInventarioTipo(int tipo)
{
	system("cls");
	cout << "\n* * * * MENU INVENTARIO * * * *\n\n";
	cout << "Categoria: " << getNombrePlanta(tipo) <<endl;
	cout << "1) Registro.\n";
	cout << "2) Muestra.\n";
	cout << "3) Volver al menu de inventario.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;
	return opcion;
}

void Menu::MenuInventarioTipoOpciones(int opcion, int tipo)
{
	switch (opcion)
	{
	case 1:
		_planta.InventarioPlanta(tipo);
		MenuInventarioOpciones(MenuInventario());
		break;
	case 2:
		_planta.ListarInventarioPlanta(tipo);
		system("pause");
		MenuInventarioOpciones(MenuInventario());
		break;
	case 3:
		MenuInventarioOpciones(MenuInventario());
		break;
	}
}