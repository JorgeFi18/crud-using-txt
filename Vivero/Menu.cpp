//Librerias externas
#include <iostream>
#include <string>

//Librerias internas
#include "Menu.h"
#include "Planta.h"
#include "Helpers.h"
#include "Insumo.h"
#include "Cliente.h"
#include "Factura.h"

//Namespaces
using namespace std;

//clases
Planta _planta;
Insumo _Insumo;
Cliente _Cliente;
Factura _Factura;

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
	cout << "6) Listado de facturas. \n";
	cout << "7) Listar facturas por nit. \n";
	cout << "8) Listar facturas por planta. \n";
	cout << "9) Salir.\n";
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
		//Hector
		MenuInsumosOpciones(MenuInsumos());
		break;
	case 3:
		MenuInventarioOpciones(MenuInventario());
		break;

	case 4:
		//Hector
		MenuClientesOpciones(MenuClientes());
		break;
	case 5: 
		_Factura.CrearFactura();
		MenuPrincipalOpciones(MenuPrincipal());
		break;
	case 6:
		_Factura.ListadoFacturas();
		MenuPrincipalOpciones(MenuPrincipal());
		break;
	case 7:
		_Factura.ListarFacturasPorNit();
		MenuPrincipalOpciones(MenuPrincipal());
		break;
	case 8:
		_Factura.ListarFacturaPorPlanta();
		MenuPrincipalOpciones(MenuPrincipal());
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
		if (tipo < 4)
			_planta.InventarioPlanta(tipo);
		else
			_Insumo.InventarioInsumo();

		MenuInventarioOpciones(MenuInventario());
		break;
	case 2:
		if (tipo < 4)
			_planta.ListarInventarioPlanta(tipo);
		else
			_Insumo.ListarInventarioInsumo();

		cout << "\n\nDesea listar de nuevo el inventario (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuInventarioTipoOpciones(2, tipo); }
		else { MenuInventarioOpciones(MenuInventario()); }
		MenuInventarioOpciones(MenuInventario());
		break;
	}
}

//hector

int Menu::MenuCambioEstadoInsumo()
{
	system("cls");
	cout << "\n* * * * MENU CAMBIO DE ESTADO * * * *\n\n";
	cout << "1) Dar insumo de baja.\n";
	cout << "2) Dar imsumo de alta.\n";
	cout << "3) Volver al menu insumo.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;
	return opcion;
}

void Menu::MenuCambioEstadoInsumoOpciones(int opcion)
{
	switch (opcion)
	{
	case 1:
		_Insumo.CambioEstado();
		cout << "\n\nDesea dar de baja otro insumo (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuCambioEstadoInsumoOpciones(1); }
		else { MenuCambioEstadoInsumoOpciones(MenuCambioEstadoInsumo()); }
		break;
	case 2:
		_Insumo.CambioEstado(true);
		cout << "\n\nDesea dar de alta otro insumo (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuCambioEstadoInsumoOpciones(2); }
		else { MenuCambioEstadoInsumoOpciones(MenuCambioEstadoInsumo()); }
		break;
	case 3:
		MenuInsumosOpciones(MenuInsumos());
		break;
	}
}

void Menu::MenuInsumosOpciones(int opcion)
{
	switch (opcion)
	{
	case 1:	
		_Insumo.RegistrarInsumo();
		cout << "\n\nDesea registrar otro insumo (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuInsumosOpciones(1); }
		else { MenuInsumosOpciones(MenuInsumos()); }
		break;

	case 2:
		_Insumo.MostrarInsumo();
		cout << "\n\nDesea listar los insumos de nuevo (s/n):";
		cin >> answer;
		if (validateAnswer(answer)) { MenuInsumosOpciones(2); }
		else { MenuInsumosOpciones(MenuInsumos()); }
		break;

	case 3:
		_Insumo.ModificarInsumo();
		cout << "\n\nDesea modificar otro insumo (s/n):";
		cin >> answer;
		if (validateAnswer(answer)) { MenuInsumosOpciones(3); }
		else { MenuInsumosOpciones(MenuInsumos()); }
		break;

	case 4:
		MenuCambioEstadoInsumoOpciones(MenuCambioEstadoInsumo());
		break;

	case 5:
		MenuPrincipalOpciones(MenuPrincipal());
		break;

	case 6:
		exit(0);
		break;

	default:
		break;
	}
}

void Menu::MenuClientesOpciones(int opcion)
{
	switch (opcion)
	{
	case 1:
		_Cliente.RegistrarCliente("");
		cout << "\n\nDesea registrar otro cliente (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuClientesOpciones(1); }
		else { MenuClientesOpciones(MenuClientes()); }
		break;

	case 2:
		_Cliente.MostrarCliente();
		cout << "\n\nDesea listar de nuevo los clientes (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuClientesOpciones(2); }
		else { MenuClientesOpciones(MenuClientes()); }
		break;

	case 3:
		_Cliente.ModificarCliente();
		cout << "\n\nDesea modificar otro cliente (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuClientesOpciones(3); }
		else { MenuClientesOpciones(MenuClientes()); }
		break;

	case 4:
		MenuCambioEstadoClientesOpciones(MenuCambioEstadoClientes());
		break;

	case 5:
		MenuPrincipalOpciones(MenuPrincipal());
		break;

	case 6:
		exit(0);
		break;

	default:
		break;
	}
}

void Menu::MenuCambioEstadoClientesOpciones(int opcion)
{
	switch (opcion)
	{
	case 1:
		_Cliente.CambioEstado();
		cout << "\n\nDesea dar de baja otro cliente (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuCambioEstadoClientesOpciones(1); }
		else { MenuCambioEstadoClientesOpciones(MenuCambioEstadoClientes()); }
		break;
	case 2:
		_Cliente.CambioEstado(true);
		cout << "\n\nDesea dar de alta otro cliente (s/n): ";
		cin >> answer;
		if (validateAnswer(answer)) { MenuCambioEstadoClientesOpciones(2); }
		else { MenuCambioEstadoClientesOpciones(MenuCambioEstadoClientes()); }
		break;
	case 3:
		MenuClientesOpciones(MenuClientes());
	}
}

//Hector
int Menu::MenuInsumos()
{
	system("cls");
	cout << "\n* * * * MENU INSUMOS * * * *\n\n";
	cout << "1) Registro nuevo insumo.\n";
	cout << "2) Muestra catalogo de insumos.\n";
	cout << "3) Modificacion de insumo.\n";
	cout << "4) Cambio de estado insumo.\n";
	cout << "5) Regresar al menu.\n";
	cout << "6) Salir.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;

	return opcion;
}

int Menu::MenuClientes()
{
	system("cls");
	cout << "\n* * * * MENU Cliente * * * *\n\n";
	cout << "1) Registro nuevo cliente.\n";
	cout << "2) Muestra catalogo de cliente.\n";
	cout << "3) Modificacion de cliente.\n";
	cout << "4) Cambio de estado cliente.\n";
	cout << "5) Regresar al menu.\n";
	cout << "6) Salir.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;

	return opcion;
}

int Menu::MenuCambioEstadoClientes()
{
	system("cls");
	cout << "\n* * * * MENU CAMBIO DE ESTADO * * * *\n\n";
	cout << "1) Dar cliente de baja.\n";
	cout << "2) Dar cliente de alta.\n";
	cout << "3) Volver al menu cliente.\n";
	cout << "\tSeleccione una opcion: ";
	cin >> opcion;
	return opcion;
}
