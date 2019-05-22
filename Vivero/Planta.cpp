//Librerias externas
#include <iostream>
#include <string>
#include <fstream>

//Librerias internas
#include "Helpers.h"
#include "Planta.h"

//Namespaces
using namespace std;

//structs
struct Planta_struct
{
	int numeroPlanta;
	string nombrePlanta;
	string descripcionPlanta;
};

struct Planta_inventario_struct
{
	int correlativo;
	int codigoPlanta;
	int existencia;
	int costo;
};

//Globales
string nombrePlanta = "";
ifstream LeerArchivo;
ofstream EscribirArchivo;

//Private
int Planta::Correlativo(int tipoPlanta)
{
	int contador = 0;
	nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/" + nombrePlanta + ".txt";
	LeerArchivo.open(archivo);
	Planta_struct datos;
	if (LeerArchivo.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
			contador = datos.numeroPlanta;
			isEnd = LeerArchivo.eof();
		} while (!isEnd);
	}
	LeerArchivo.close();
	return contador + 1;
}

int Planta::CorrelativoInventario(int tipoPlanta)
{
	int contador = 0;
	nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/inventario_" + nombrePlanta + ".txt";
	LeerArchivo.open(archivo);
	Planta_inventario_struct datos;
	if (LeerArchivo.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo >> datos.correlativo >> datos.codigoPlanta >> datos.existencia >> datos.costo;
			contador = datos.correlativo;
			isEnd = LeerArchivo.eof();
		} while (!isEnd);
	}
	LeerArchivo.close();
	return contador + 1;
}

bool Planta::PlantaDuplicada(int tipoPlanta, string nombre)
{
	bool duplicado = false;
	Planta_struct datos;
	nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/" + nombrePlanta + ".txt";

	ifstream  src(archivo);
	ofstream  dst("Plantas/pivote.txt");

	dst << src.rdbuf();
	dst.close();

	ifstream Lectura("Plantas/pivote.txt");

	if (Lectura.fail())
	{
		duplicado = false;
	}
	else
	{
		bool isEnd = false;
		do
		{
			Lectura >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
			if (datos.nombrePlanta == nombre)
			{
				duplicado = true;
			}
			isEnd = Lectura.eof();
		} while (!isEnd);
	}
	Lectura.close();
	remove("Plantas/pivote.txt");
	return duplicado;
}

void Planta::EliminarDeHistorial(string historial, int codigoPlanta)
{
	Planta_struct datos;
	LeerArchivo.open(historial);
	EscribirArchivo.open("Plantas/pivote.txt");
	if(LeerArchivo.fail())
	{
	//do this
	}
	else
	{
		do {
			LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
			if (datos.numeroPlanta != codigoPlanta)
			{
				EscribirArchivo <<endl << datos.numeroPlanta << " " << datos.nombrePlanta << " " << datos.descripcionPlanta;
			}
		} while (!LeerArchivo.eof());
	}

	LeerArchivo.close();
	EscribirArchivo.close();

	const char *cstr = historial.c_str();
	remove(cstr);
	rename("Plantas/pivote.txt", cstr);
	return;
}

bool Planta::PlantaEnInventario(int tipoPlanta, int codigoPlanta)
{
	bool existe = false;
	Planta_inventario_struct datos;
	string archivo = "Plantas/inventario_" + getNombrePlanta(tipoPlanta) + ".txt";
	LeerArchivo.open(archivo);
	if (LeerArchivo.fail())
	{
		return existe;
	}
	else 
	{
		do 
		{
			LeerArchivo >> datos.correlativo >> datos.codigoPlanta >> datos.existencia >> datos.costo;
			if (datos.codigoPlanta == codigoPlanta)
			{
				existe = true;
			}
		} while (!LeerArchivo.eof());
	}
	LeerArchivo.close();
	return existe;
}

string Planta::BuscarNombrePlanta(int tipoPlanta, int codigoPlanta)
{
	string nombreDePlanta;
	string archivo = "Plantas/" + getNombrePlanta(tipoPlanta) + ".txt";
	Planta_struct datos;
	ifstream leerArchivo(archivo);
	do
	{
		leerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
		if (datos.numeroPlanta == codigoPlanta)
		{
			nombreDePlanta = datos.nombrePlanta;
		}
	} while (!leerArchivo.eof());
	
	leerArchivo.close();
	return nombreDePlanta;
}

//Public
void Planta::RegistrarPlanta(int tipoPlanta)
{
	system("cls");
	Planta_struct datosPlanta;
	nombrePlanta = getNombrePlanta(tipoPlanta);
	datosPlanta.numeroPlanta = Correlativo(tipoPlanta);
	bool plantaDuplicada = false;
	cout <<"\nRegistro de planta: " <<nombrePlanta <<"\n\n";
	cout << "Codigo de planta: " << datosPlanta.numeroPlanta << endl;
	do 
	{
		cout << "Ingrese nombre de planta: ";
		while (isspace(cin.peek())) cin.ignore();
		getline(cin, datosPlanta.nombrePlanta);
		plantaDuplicada = PlantaDuplicada(tipoPlanta, serializeString(datosPlanta.nombrePlanta, false));
		if (plantaDuplicada)
		{
			cout << "\n Planta duplicada!\n\n";
		}
	} while (plantaDuplicada);
	
	cout << "Ingrese descripcion de planta: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, datosPlanta.descripcionPlanta);

	string archivo = "Plantas/" + nombrePlanta + ".txt";
	EscribirArchivo.open(archivo, ios::app);
	if (datosPlanta.numeroPlanta > 1)
	{
		EscribirArchivo 
			<< endl 
			<< datosPlanta.numeroPlanta 
			<< " " 
			<< serializeString(datosPlanta.nombrePlanta, false) 
			<< " "
			<<serializeString(datosPlanta.descripcionPlanta, false);
	}
	else
	{
		EscribirArchivo 
			<< datosPlanta.numeroPlanta 
			<< " " 
			<< serializeString(datosPlanta.nombrePlanta, false) 
			<< " " 
			<< serializeString(datosPlanta.descripcionPlanta, false);
	}

	EscribirArchivo.close();
	return;
}

void Planta::MostrarPlantas(int tipoPlanta)
{
	string nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/" + nombrePlanta + ".txt";

	Planta_struct datos;

	system("cls");
	LeerArchivo.open(archivo);
	cout << "\nCatalogo de plantas" << "\n";
	cout << "Tipo de planta: " << nombrePlanta << "\n\n";
	if (LeerArchivo.fail())
	{
		cout << "\n\n\tOcurrio un error al tratar de abrir el archivo *" << archivo << "* intente mas tarde.\n";
	}
	else
	{
		do {
			LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
			cout << "\tCodigo de planta: " << datos.numeroPlanta << endl;
			cout << "\tNombre de planta: " << serializeString(datos.nombrePlanta, true) << endl;
			cout << "\tDescripcion de planta: " <<serializeString(datos.descripcionPlanta, true) << "\n\n";

		} while (!LeerArchivo.eof());

		cout << "\tFin de la lista.\n";
	}
	
	LeerArchivo.close();
	return;
}

void Planta::ModificarPlanta(int tipoPlanta)
{
	int codigoModificar;
	bool plantaBloqueada = false;
	bool isEnd = false;
	bool plantaDuplicada = false;
	Planta_struct datos;
	cout << "Modificar nombre de planta\n";
	cout << "Tipo de planta: " << nombrePlanta << "\n\n";
	string nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/" + nombrePlanta + ".txt";
	MostrarPlantas(tipoPlanta);

	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	//Lecrtura
	LeerArchivo.open(archivo);
	//Escritura
	EscribirArchivo.open("Plantas/temporal.txt");
	do
	{
		LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >>datos.descripcionPlanta;
		isEnd = LeerArchivo.eof();
		if (datos.numeroPlanta == codigoModificar && datos.nombrePlanta == "Planta-de-baja")
		{
			plantaBloqueada = true;
		}

		if (datos.numeroPlanta == codigoModificar && datos.nombrePlanta != "Planta-de-baja")
		{
			cout << "Numero de planta: " << datos.numeroPlanta << endl;
			cout << "Nombre de planta: " << serializeString(datos.nombrePlanta, true) << endl;
			cout << "Descripcion de planta: " << serializeString(datos.descripcionPlanta, true) << endl;
			cout << "\n\n-----------------------------------------------------------\n\n";
			do {
				cout << "Ingrese nuevo nombre de planta: ";
				while (isspace(cin.peek())) cin.ignore();
				getline(cin, datos.nombrePlanta);
				plantaDuplicada = PlantaDuplicada(tipoPlanta, serializeString(datos.nombrePlanta, false));
				if (plantaDuplicada)
				{
					cout << "\n Planta duplicada!\n\n";
				}
			} while (plantaDuplicada);
			
			if (datos.numeroPlanta > 1) {
				EscribirArchivo 
					<< endl 
					<< datos.numeroPlanta 
					<< " " 
					<< serializeString(datos.nombrePlanta, false)
					<< " "
					<< serializeString(datos.descripcionPlanta, false);
			}
			else {
				EscribirArchivo 
					<< datos.numeroPlanta 
					<< " " 
					<< serializeString(datos.nombrePlanta, false) 
					<< " "
					<< serializeString(datos.descripcionPlanta, false);
			}
		}
		else
		{
			if (datos.numeroPlanta > 1) {
				EscribirArchivo 
					<< endl 
					<< datos.numeroPlanta 
					<< " " 
					<< serializeString(datos.nombrePlanta, false)
					<< " "
					<< serializeString(datos.descripcionPlanta, false);
			}
			else {
				EscribirArchivo 
					<< datos.numeroPlanta 
					<< " " 
					<< serializeString(datos.nombrePlanta, false)
					<< " "
					<< serializeString(datos.descripcionPlanta, false);
			}
		}
	} while (!isEnd);

	if (plantaBloqueada) {
		std::cout << "\n\tNo se permite modificar nombre si la planta esta de baja!\n";
		system("pause");
	}

	LeerArchivo.close();
	EscribirArchivo.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Plantas/temporal.txt", cstr);
	return;
}

void Planta::CambioEstado(int tipoPlanta)
{
	system("cls");
	int codigoModificar;
	string nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/"+ nombrePlanta + ".txt";
	cout << "Dar de baja planta\n";
	cout << "Tipo de planta: " << nombrePlanta << "\n\n";
	MostrarPlantas(tipoPlanta);
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	Planta_struct datos;
	//Lectura
	LeerArchivo.open(archivo);
	string historico = "Plantas/historial_" + nombrePlanta + ".txt";

	EscribirArchivo.open(historico, ios::app);
	ofstream nuevoArchivo("Plantas/temporal.txt");

	do
	{
		LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
		if (datos.numeroPlanta == codigoModificar && datos.nombrePlanta != "Planta-de-baja")
		{
			EscribirArchivo << endl << datos.numeroPlanta << " " << datos.nombrePlanta <<" " <<datos.descripcionPlanta;
			if (datos.numeroPlanta > 1) 
			{
				nuevoArchivo 
					<< endl 
					<< datos.numeroPlanta 
					<< " " 
					<< "Planta-de-baja" 
					<<" " 
					<<"*Descripcion-no-disponible";
			}
			else
			{
				nuevoArchivo 
					<< datos.numeroPlanta 
					<< " " 
					<< "Planta-de-baja" 
					<<" " 
					<<"*Descripcion-no-disponible";
			}
		}
		else
		{
			if (datos.numeroPlanta > 1) 
			{
				nuevoArchivo 
					<< endl 
					<< datos.numeroPlanta 
					<< " " 
					<< datos.nombrePlanta
					<< " "
					<< datos.descripcionPlanta;
			}
			else
			{
				nuevoArchivo 
					<< datos.numeroPlanta 
					<< " " 
					<< datos.nombrePlanta
					<< " "
					<< datos.descripcionPlanta;
			}
				
		}
	} while (!LeerArchivo.eof());

	//cerrar archivos
	LeerArchivo.close();
	EscribirArchivo.close();
	nuevoArchivo.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Plantas/temporal.txt", cstr);
}

void Planta::CambioEstado(int tipoPlanta, bool alta)
{
	int codigoModificar;
	string nombrePlanta = getNombrePlanta(tipoPlanta);
	string archivo = "Plantas/" + nombrePlanta + ".txt";
	Planta_struct datos;
	MostrarPlantas(tipoPlanta);
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	string historico = "Plantas/historial_" + nombrePlanta + ".txt";

	//Lectura
	LeerArchivo.open(archivo);
	ifstream historial(historico);

	EscribirArchivo.open("Plantas/temporal.txt");

	string nombreReal, descripcionReal;
	do
	{
		historial >> datos.numeroPlanta >> datos.nombrePlanta >>datos.descripcionPlanta;
		if (datos.numeroPlanta == codigoModificar)
		{
			nombreReal = datos.nombrePlanta;
			descripcionReal = datos.descripcionPlanta;
		}
		
	} while (!historial.eof());
	historial.close();

	do
	{
		LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta >> datos.descripcionPlanta;
		if (datos.numeroPlanta == codigoModificar)
		{

			if(datos.numeroPlanta > 1)
				EscribirArchivo <<endl << datos.numeroPlanta << " " << nombreReal <<" " << descripcionReal;
			else
				EscribirArchivo << datos.numeroPlanta << " " << nombreReal <<" " << descripcionReal;
			
		}
		else
		{
			if (datos.numeroPlanta > 1)
				EscribirArchivo 
				<< endl 
				<< datos.numeroPlanta 
				<< " " 
				<< datos.nombrePlanta 
				<<" " 
				<<datos.descripcionPlanta;
			else
				EscribirArchivo 
				<< datos.numeroPlanta 
				<< " " 
				<< datos.nombrePlanta 
				<<" " 
				<< datos.descripcionPlanta;
		}
	} while (!LeerArchivo.eof());

	//cerrar archivos
	LeerArchivo.close();
	EscribirArchivo.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Plantas/temporal.txt", cstr);
	EliminarDeHistorial(historico, codigoModificar);
}

void Planta::InventarioPlanta(int tipoPlanta)
{
	system("cls");
	int codigoPlanta;
	string archivo = "Plantas/inventario_" + getNombrePlanta(tipoPlanta) + ".txt";
	Planta_inventario_struct datos;
	cout << "Registro de inventario de plantas: " <<getNombrePlanta(tipoPlanta) <<endl;
	MostrarPlantas(tipoPlanta);
	cout << "\n\n ---------------------------------------------\n";
	cout << "Ingrese codigo de planta: ";
	cin >> codigoPlanta;

	if (PlantaEnInventario(tipoPlanta, codigoPlanta)) 
	{
		cout << "\t\nPlanta ya existe en inventario\n\n";
		system("pause");
	}
	else 
	{
		if (BuscarNombrePlanta(tipoPlanta, codigoPlanta) == "Planta-de-baja")
		{
			cout << "\t\nNo se puede realizar la operacion si la planta esta de baja \n\n";
			system("pause");
		}
		else
		{
			datos.correlativo = CorrelativoInventario(tipoPlanta);
			cout << "Correlativo: " << datos.correlativo << endl;
			datos.codigoPlanta = codigoPlanta;
			std::cout << "Ingrese existencia: ";
			cin >> datos.existencia;
			std::cout << "Ingrese precio: ";
			cin >> datos.costo;

			EscribirArchivo.open(archivo, ios::app);
			if (datos.correlativo > 1)
			{
				EscribirArchivo << endl << datos.correlativo << " " << datos.codigoPlanta << " " << datos.existencia << " " << datos.costo;
			}
			else
			{
				EscribirArchivo << datos.correlativo << " " << datos.codigoPlanta << " " << datos.existencia << " " << datos.costo;
			}
			EscribirArchivo.close();
			cout << "\n\tRegistro realizado con exito!";
		}
	}
	return;
}

void Planta::ListarInventarioPlanta(int tipoPlanta)
{
	system("cls");
	int codigoPlanta;
	string archivo = "Plantas/inventario_" + getNombrePlanta(tipoPlanta) + ".txt";
	Planta_inventario_struct datos;
	cout << "Listado de inventario plantas: " << getNombrePlanta(tipoPlanta) << endl <<endl;

	LeerArchivo.open(archivo);

	if (LeerArchivo.fail())
	{
		cout << "\t\nOcurrio un erro al tratar de abrir el archivo\n\n";
	}
	else
	{
		do
		{
			LeerArchivo >> datos.correlativo >> datos.codigoPlanta >> datos.existencia >> datos.costo;
			cout << "\tCorrelativo: " << datos.correlativo << endl;
			cout << "\tCodigo de Planta: " << datos.codigoPlanta << endl;
			cout << "\tNombre de Planta: " << serializeString(BuscarNombrePlanta(tipoPlanta, datos.codigoPlanta),
				true) << endl;
			cout << "\tExistencia: " << datos.existencia << endl;
			cout << "\tCosto: " << "Q." << datos.costo <<endl;
			cout << "\t--------------------------------------------------------------------\n\n";
		} while (!LeerArchivo.eof());
	}
	LeerArchivo.close();
	return;
}