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
		cout << "\n\tNo se permite modificar nombre si la planta esta de baja!\n";
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
		LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta;
		if (datos.numeroPlanta == codigoModificar && datos.nombrePlanta != "Planta-de-baja")
		{
			EscribirArchivo << datos.numeroPlanta << " " << datos.nombrePlanta << endl;
			if (datos.numeroPlanta > 1) 
			{
				nuevoArchivo << endl << datos.numeroPlanta << " " << "Planta-de-baja";
			}
			else
			{
				nuevoArchivo << datos.numeroPlanta << " " << "Planta-de-baja";
			}
		}
		else
		{
			if (datos.numeroPlanta > 1) 
			{
				nuevoArchivo << endl << datos.numeroPlanta << " " << datos.nombrePlanta;
			}
			else
			{
				nuevoArchivo << datos.numeroPlanta << " " << datos.nombrePlanta;
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

	string nombreReal;
	do
	{
		historial >> datos.numeroPlanta >> datos.nombrePlanta;
		if (datos.numeroPlanta == codigoModificar)
		{
			nombreReal = datos.nombrePlanta;
		}
		
	} while (!historial.eof());
	historial.close();

	do
	{
		LeerArchivo >> datos.numeroPlanta >> datos.nombrePlanta;
		if (datos.numeroPlanta == codigoModificar)
		{

			if(datos.numeroPlanta > 1)
				EscribirArchivo <<endl << datos.numeroPlanta << " " << nombreReal;
			else
				EscribirArchivo << datos.numeroPlanta << " " << nombreReal;
			
		}
		else
		{
			if (datos.numeroPlanta > 1)
				EscribirArchivo << endl << datos.numeroPlanta << " " << datos.nombrePlanta;
			else
				EscribirArchivo << datos.numeroPlanta << " " << datos.nombrePlanta;
		}
	} while (!LeerArchivo.eof());

	//cerrar archivos
	LeerArchivo.close();
	EscribirArchivo.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Plantas/temporal.txt", cstr);

}