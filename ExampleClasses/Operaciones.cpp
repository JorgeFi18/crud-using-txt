#include "Operaciones.h"
#include "Helpers.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

Planta datos;

Operaciones::Operaciones()
{
}


Operaciones::~Operaciones()
{
	
}

bool Operaciones::Registro(Planta planta) 
{
	string almacenar = planta.archivo;
	ofstream guardar(almacenar, ios::app);

	guardar << planta.numeroPlanta <<" " << serializeString(planta.nombrePlanta) <<endl;
	return true;
}

void Operaciones::Mostrar(string archivo)
{
	string documento;
	documento = archivo + ".txt";

	ifstream archivoLectura(documento);

	bool isEnd = false;
	
	system("cls");
	cout << "\n ***** Listado de plantas ***** \n";
	cout << " Tipo de planta: " << archivo <<"\n\n";
	cout << "----------------------------------------------------" << endl;
	do {
		archivoLectura >> datos.numeroPlanta >> datos.nombrePlanta;
		if (datos.numeroPlanta != 0 && datos.nombrePlanta != "blank_spaces") 
		{
			cout << "\tNumero Planta: " << datos.numeroPlanta << endl;
			cout << "\tNombre planta: " << serializeString(datos.nombrePlanta, true) << endl;

			cout << "----------------------------------------------------" << endl;
		}
		datos.numeroPlanta = 0;
		datos.nombrePlanta = "blank_spaces";
		isEnd = archivoLectura.eof();
	} while (!isEnd);
	archivoLectura.close();
	cout << endl;
	system("pause");
	return;
}

int Operaciones::Correlativo(string documento) 
{
	string archivo = documento + ".txt";
	ifstream revisar(archivo);
	bool isEnd = false;
	int contador = 0;
	do
	{
		revisar >> datos.numeroPlanta >> datos.nombrePlanta;
		isEnd = revisar.eof();
		if (!isEnd)
		{
			contador++;
		}
	} while (!isEnd);
	revisar.close();
	return contador+1;
	system("pause");
}

void Operaciones::Modificar(string archivo)
{
	int codigoModificar;
	bool plantaBloqueada = false;
	string documento = archivo + ".txt";
	Mostrar(archivo);
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	//Lecrtura
	ifstream encontrar(documento);
	ofstream temporal("temporal.txt");
	do
	{
		encontrar >> datos.numeroPlanta >> datos.nombrePlanta;
		if (!encontrar.eof())
		{
			if (datos.numeroPlanta == codigoModificar && datos.nombrePlanta == "Planta-de-baja")
			{
				plantaBloqueada = true;
			}

			if (datos.numeroPlanta == codigoModificar && datos.nombrePlanta != "Planta-de-baja")
			{
				cout << "Numero de planta: " << datos.numeroPlanta << endl;
				cout << "Nombre de planta: " << datos.nombrePlanta << endl;
				cout << "\n\n-----------------------------------------------------------\n\n";
				cout << "Ingrese nuevo nombre de planta: ";
				cin >> datos.nombrePlanta;
				temporal << datos.numeroPlanta << " " << datos.nombrePlanta << endl;
			}
			else
			{
				temporal << datos.numeroPlanta << " " << datos.nombrePlanta << endl;
			}
		}
	} while (!encontrar.eof());

	if (plantaBloqueada) {
		cout << "\n\tNo se permite modificar nombre si la planta esta de baja!\n";
		system("pause");
	}

	encontrar.close();
	temporal.close();

	const char *cstr = documento.c_str();
	remove(cstr);
	rename("temporal.txt", cstr);
}

void Operaciones::CambioEstado(string archivo)
{
	int codigoModificar;
	string documento = archivo + ".txt";
	Mostrar(archivo);
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	//Lectura
	ifstream archivoFuente(documento);
	string historico = "historial_" + documento;

	ofstream historial(historico, ios::app);
	ofstream nuevoArchivo("temporal.txt");

	do
	{
		archivoFuente >> datos.numeroPlanta >> datos.nombrePlanta;
		if (!archivoFuente.eof())
		{
			if (datos.numeroPlanta == codigoModificar)
			{
				historial << datos.numeroPlanta << " " << datos.nombrePlanta << endl;
				nuevoArchivo << datos.numeroPlanta << " " << "Planta-de-baja" <<endl;
			}
			else
			{
				nuevoArchivo << datos.numeroPlanta << " " << datos.nombrePlanta << endl;
			}
		}
	} while (!archivoFuente.eof());

	//cerrar archivos
	archivoFuente.close();
	historial.close();
	nuevoArchivo.close();

	const char *cstr = documento.c_str();
	remove(cstr);
	rename("temporal.txt", cstr);
}

//Cambio de estado inverso
void Operaciones::CambioEstado(string archivo, bool reverse)
{
	int codigoModificar;
	string documento = archivo + ".txt";
	Mostrar(archivo);
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	string historico = "historial_" + documento;

	//Lectura
	ifstream archivoFuente(documento);
	ifstream historial(historico);

	ofstream nuevoArchivo("temporal.txt");

	string nombreReal;
	do
	{
		historial >> datos.numeroPlanta >> datos.nombrePlanta;
		if (!historial.eof())
		{
			if (datos.numeroPlanta == codigoModificar)
			{
				nombreReal = datos.nombrePlanta;
			}
		}
	} while (!historial.eof());
	historial.close();

	do
	{
		archivoFuente >> datos.numeroPlanta >> datos.nombrePlanta;
		if (!archivoFuente.eof())
		{
			if (datos.numeroPlanta == codigoModificar)
			{
				nuevoArchivo << datos.numeroPlanta << " " << nombreReal << endl;
			}
			else
			{
				nuevoArchivo << datos.numeroPlanta << " " << datos.nombrePlanta << endl;
			}
		}
	} while (!archivoFuente.eof());

	//cerrar archivos
	archivoFuente.close();
	nuevoArchivo.close();

	const char *cstr = documento.c_str();
	remove(cstr);
	rename("temporal.txt", cstr);
}