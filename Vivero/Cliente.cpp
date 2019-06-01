//Librerias externas

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Librerias internas
#include "Helpers.h"
#include "Cliente.h"
#include "Factura.h"

//Namespaces
using namespace std;

//structs
struct Cliente_struct
{
	int numeroCliente;
	string nitCliente;
	string nombreCliente;
	string direccionCliente;
};

struct Cliente_inventario_struct
{
	int correlativo;
	int codigoCliente2;
	int existencia;
	int costo;
};

//Globales
string nombreCliente = "";
ifstream LeerArchivo3;
ofstream EscribirArchivo3;

Factura facturaReferencia;
//Private

int Cliente::Correlativo()
{
	int contador = 0;
	string archivo = "Clientes/cliente.txt";
	LeerArchivo3.open(archivo);
	Cliente_struct datos;
	if (LeerArchivo3.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo3 >> datos.numeroCliente >> datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
			contador = datos.numeroCliente;
			isEnd = LeerArchivo3.eof();
		} while (!isEnd);
	}
	LeerArchivo3.close();
	return contador + 1;
}

bool Cliente::ClienteDuplicado(std::string nit)
{
	bool duplicado = false;
	Cliente_struct datos;
	string archivo = "Clientes/cliente.txt";

	ifstream  src(archivo);
	ofstream  dst("Clientes/pivote.txt");

	dst << src.rdbuf();
	dst.close();

	ifstream Lectura("Clientes/pivote.txt");

	if (Lectura.fail())
	{
		duplicado = false;
	}
	else
	{
		bool isEnd = false;
		do
		{
			Lectura >> datos.numeroCliente >>datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
			if (datos.nitCliente == nit)
			{
				duplicado = true;
			}
			isEnd = Lectura.eof();
		} while (!isEnd);
	}
	Lectura.close();
	remove("Clientes/pivote.txt");
	return duplicado;
}

void Cliente::EliminarDeHistorial(string historial, int codigoCliente2)
{
	Cliente_struct datos;
	LeerArchivo3.open(historial);
	EscribirArchivo3.open("Clientes/pivote.txt");
	if (LeerArchivo3.fail())
	{
		//do this
	}
	else
	{
		do {
			LeerArchivo3 >> datos.numeroCliente >> datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
			if (datos.numeroCliente != codigoCliente2)
			{
				EscribirArchivo3 << endl << datos.numeroCliente <<" " <<datos.nitCliente << " " << datos.nombreCliente << " " << datos.direccionCliente;
			}
		} while (!LeerArchivo3.eof());
	}

	LeerArchivo3.close();
	EscribirArchivo3.close();

	const char *cstr = historial.c_str();
	remove(cstr);
	rename("Clientes/pivote.txt", cstr);
	return;
}

string Cliente::BuscarNombreCliente(int codigoCliente2)
{
	string nombreDeCliente;
	string archivo = "Clientes/cliente.txt";
	Cliente_struct datos;
	ifstream LeerArchivo3(archivo);
	do
	{
		LeerArchivo3 >> datos.numeroCliente >> datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
		if (datos.numeroCliente == codigoCliente2)
		{
			nombreDeCliente = datos.nombreCliente;
		}
	} while (!LeerArchivo3.eof());

	LeerArchivo3.close();
	return nombreDeCliente;
}

string Cliente::BuscarClientePorNit(string nitCliente)
{
	string nombreDeCliente;
	string archivo = "Clientes/cliente.txt";
	Cliente_struct datos;
	ifstream LeerArchivo3(archivo);
	do
	{
		LeerArchivo3 >> datos.numeroCliente >> datos.nitCliente >>  datos.nombreCliente >> datos.direccionCliente;
		if (datos.nitCliente == nitCliente)
		{
			nombreDeCliente = datos.nombreCliente;
		}
	} while (!LeerArchivo3.eof());

	LeerArchivo3.close();
	return nombreDeCliente;
}

//Public
void Cliente::RegistrarCliente(string nuevoNit)
{
	system("cls");
	Cliente_struct datosCliente;
	bool clienteDuplicado = false;
	bool nitInvalido = false;
	datosCliente.numeroCliente = Correlativo();
	cout << "\nRegistro de Cliente\n\n";
	cout << "Codigo de cliente: " << datosCliente.numeroCliente << endl;
	if (nuevoNit == "")
	{
		do
		{
			cout << "Ingrese nit del cliente: ";
			while (isspace(cin.peek())) cin.ignore();
			getline(cin, datosCliente.nitCliente);

			clienteDuplicado = ClienteDuplicado(datosCliente.nitCliente);
			nitInvalido = datosCliente.nitCliente.length() != 9;
			if (clienteDuplicado)
				cout << "\n\nEste nit ya se encuentra registrado\n\n";
			if (nitInvalido)
				cout << "\n\nNit invalido, el nit debe tener 9 caracteres\n\n";
		} while (clienteDuplicado || nitInvalido);
	}
	else
	{
		datosCliente.nitCliente = nuevoNit;
		cout << "Nit del cliente: " << datosCliente.nitCliente << endl;
	}
	
	

	cout << "Ingrese nombre y apellido del cliente: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, datosCliente.nombreCliente);
		

	cout << "Ingrese direccion del cliente: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, datosCliente.direccionCliente);

	string archivo2 = "Clientes/cliente.txt";
	EscribirArchivo3.open(archivo2, ios::app);
	if (datosCliente.numeroCliente > 1)
	{
		EscribirArchivo3
			<< endl
			<< datosCliente.numeroCliente
			<< " "
			<< datosCliente.nitCliente
			<< " "
			<< serializeString(datosCliente.nombreCliente, false)
			<< " "
			<< serializeString(datosCliente.direccionCliente, false);
	}
	else
	{
		EscribirArchivo3
			<< datosCliente.numeroCliente
			<< " "
			<< datosCliente.nitCliente
			<< " "
			<< serializeString(datosCliente.nombreCliente, false)
			<< " "
			<< serializeString(datosCliente.direccionCliente, false);
	}

	EscribirArchivo3.close();
	return;
}

void Cliente::MostrarCliente()
{
	string archivo = "Clientes/cliente.txt";

	Cliente_struct datos;

	system("cls");
	LeerArchivo3.open(archivo);
	cout << "\nListado de Clientes" << "\n\n";
	if (LeerArchivo3.fail())
	{
		cout << "\n\n\tOcurrio un error al tratar de abrir el archivo *" << archivo << "* intente mas tarde.\n";
	}
	else
	{
		do {
			LeerArchivo3 >> datos.numeroCliente >> datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
			cout << "\tCodigo de cliente: " << datos.numeroCliente << endl;
			cout << "\tNIT de cliente: " << serializeString(datos.nitCliente, true) << endl;
			cout << "\tNombre de cliente: " << serializeString(datos.nombreCliente, true) << endl;
			cout << "\tDescripcion de cliente: " << serializeString(datos.direccionCliente, true) << "\n\n";

		} while (!LeerArchivo3.eof());

		cout << "\tFin de la lista.\n";
	}

	LeerArchivo3.close();
	return;
}

void Cliente::ModificarCliente()
{
	int codigoModificar;
	bool ClienteBloqueado = false;
	bool isEnd = false;
	bool ClienteDuplicado = false;
	Cliente_struct datos;
	cout << "Modificar nombre de Cliente\n\n";
	string archivo = "Clientes/cliente.txt";
	MostrarCliente();

	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	//Lecrtura
	LeerArchivo3.open(archivo);
	//Escritura
	EscribirArchivo3.open("Clientes/temporal.txt");
	do
	{
		LeerArchivo3 >> datos.numeroCliente >>datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
		isEnd = LeerArchivo3.eof();
		if (datos.numeroCliente == codigoModificar && datos.nombreCliente == "Cliente-de-baja")
		{
			ClienteBloqueado = true;
		}

		if (datos.numeroCliente == codigoModificar && datos.nombreCliente != "Cliente-de-baja")
		{
			cout << "Numero de cliente: " << datos.numeroCliente << endl;
			cout << "NIT de cliente: " << datos.nitCliente << endl;
			cout << "Nombre de cliente: " << serializeString(datos.nombreCliente, true) << endl;
			cout << "Descripcion de cliente: " << serializeString(datos.direccionCliente, true) << endl;
			cout << "\n\n-----------------------------------------------------------\n\n";
			cout << "Ingrese nuevo nombre de Cliente: ";
			while (isspace(cin.peek())) cin.ignore();
			getline(cin, datos.nombreCliente);

			if (datos.numeroCliente > 1) {
				EscribirArchivo3
					<< endl
					<< datos.numeroCliente
					<< " "
					<< datos.nitCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.direccionCliente, false);
			}
			else {
				EscribirArchivo3
					<< datos.numeroCliente
					<< " "
					<< datos.nitCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.direccionCliente, false);
			}
		}
		else
		{
			if (datos.numeroCliente > 1) {
				EscribirArchivo3
					<< endl
					<< datos.numeroCliente
					<< " "
					<< datos.nitCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.direccionCliente, false);
			}
			else {
				EscribirArchivo3
					<< datos.numeroCliente
					<< " "
					<< datos.nitCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.direccionCliente, false);
			}
		}
	} while (!isEnd);

	if (ClienteBloqueado) {
		std::cout << "\n\tNo se permite modificar nombre si el Cliente esta de baja!\n";
		system("pause");
	}

	LeerArchivo3.close();
	EscribirArchivo3.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Clientes/temporal.txt", cstr);
	return;
}

void Cliente::CambioEstado()
{
	system("cls");
	int codigoModificar;
	string archivo = "Clientes/cliente.txt";
	cout << "Dar de baja Cliente\n\n";
	MostrarCliente();
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	Cliente_struct datos;
	//Lectura
	LeerArchivo3.open(archivo);
	string historico = "Clientes/historial_Cliente.txt";

	EscribirArchivo3.open(historico, ios::app);
	ofstream nuevoArchivo2("Clientes/temporal.txt");

	do
	{
		LeerArchivo3 >> datos.numeroCliente >> datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
		if (datos.numeroCliente == codigoModificar && datos.nombreCliente != "Cliente-de-baja")
		{
			EscribirArchivo3 << endl << datos.numeroCliente <<" " <<datos.nitCliente << " " << datos.nombreCliente << " " << datos.direccionCliente;
			if (datos.numeroCliente > 1)
			{
				nuevoArchivo2
					<< endl
					<< datos.numeroCliente
					<< " "
					<< "NIT-no-disponible"
					<< " "
					<< "Cliente-de-baja"
					<< " "
					<< "*Direccion-no-disponible";
			}
			else
			{
				nuevoArchivo2
					<< datos.numeroCliente
					<< " "
					<< "NIT-no-disponible"
					<< " "
					<< "Cliente-de-baja"
					<< " "
					<< "*Direccion-no-disponible";
			}
		}
		else
		{
			if (datos.numeroCliente > 1)
			{
				nuevoArchivo2
					<< endl
					<< datos.numeroCliente
					<< " "
					<< datos.nitCliente
					<< " "
					<< datos.nombreCliente
					<< " "
					<< datos.direccionCliente;
			}
			else
			{
				nuevoArchivo2
					<< datos.numeroCliente
					<< " "
					<< datos.nitCliente
					<< " "
					<< datos.nombreCliente
					<< " "
					<< datos.direccionCliente;
			}

		}
	} while (!LeerArchivo3.eof());

	//cerrar archivos
	LeerArchivo3.close();
	EscribirArchivo3.close();
	nuevoArchivo2.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Clientes/temporal.txt", cstr);
}

void Cliente::CambioEstado(bool alta)
{
	int codigoModificar;
	string archivo = "Clientes/cliente.txt";
	Cliente_struct datos;
	MostrarCliente();
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	string historico = "Clientes/historial_Cliente.txt";

	//Lectura
	LeerArchivo3.open(archivo);
	ifstream historial(historico);

	EscribirArchivo3.open("Clientes/temporal.txt");

	string nombreReal, direccionReal, nitReal;
	do
	{
		historial >> datos.numeroCliente >> datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
		if (datos.numeroCliente == codigoModificar)
		{
			nombreReal = datos.nombreCliente;
			nitReal = datos.nitCliente;
			direccionReal = datos.direccionCliente;
		}

	} while (!historial.eof());
	historial.close();

	do
	{
		LeerArchivo3 >> datos.numeroCliente >>datos.nitCliente >> datos.nombreCliente >> datos.direccionCliente;
		if (datos.numeroCliente == codigoModificar)
		{

			if (datos.numeroCliente > 1)
				EscribirArchivo3 << endl << datos.numeroCliente <<" " << nitReal << " " << nombreReal << " " << direccionReal;
			else
				EscribirArchivo3 << datos.numeroCliente <<" " <<nitReal << " " << nombreReal << " " << direccionReal;

		}
		else
		{
			if (datos.numeroCliente > 1)
				EscribirArchivo3
				<< endl
				<< datos.numeroCliente
				<< " "
				<< datos.nitCliente
				<< " "
				<< datos.nombreCliente
				<< " "
				<< datos.direccionCliente;
			else
				EscribirArchivo3
				<< datos.numeroCliente
				<< " "
				<< datos.nitCliente
				<< " "
				<< datos.nombreCliente
				<< " "
				<< datos.direccionCliente;
		}
	} while (!LeerArchivo3.eof());

	//cerrar archivos
	LeerArchivo3.close();
	EscribirArchivo3.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Clientes/temporal.txt", cstr);
	EliminarDeHistorial(historico, codigoModificar);
}