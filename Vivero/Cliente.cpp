//Librerias externas

#include <iostream>
#include <string>
#include <fstream>

//Librerias internas
#include "Helpers.h"
#include "Cliente.h"

//Namespaces
using namespace std;

//structs
struct Cliente_struct
{
	int numeroCliente;
	string nombreCliente;
	string descripcionCliente;
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
			LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
			contador = datos.numeroCliente;
			isEnd = LeerArchivo3.eof();
		} while (!isEnd);
	}
	LeerArchivo3.close();
	return contador + 1;
}


int Cliente::CorrelativoInventario()
{
	int contador = 0;
	string archivo = "Clientes/inventario_cliente.txt";
	LeerArchivo3.open(archivo);
	Cliente_inventario_struct datos;
	if (LeerArchivo3.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo3 >> datos.correlativo >> datos.codigoCliente2 >> datos.existencia >> datos.costo;
			contador = datos.correlativo;
			isEnd = LeerArchivo3.eof();
		} while (!isEnd);
	}
	LeerArchivo3.close();
	return contador + 1;
}


bool Cliente::ClienteDuplicado(std::string nombre)
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
			Lectura >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
			if (datos.nombreCliente == nombre)
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
			LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
			if (datos.numeroCliente != codigoCliente2)
			{
				EscribirArchivo3 << endl << datos.numeroCliente << " " << datos.nombreCliente << " " << datos.descripcionCliente;
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

bool Cliente::ClienteEnInventario(int codigoCliente2)
{
	bool existe = false;
	Cliente_inventario_struct datos;
	string archivo = "Clientes/inventario_cliente.txt";
	LeerArchivo3.open(archivo);
	if (LeerArchivo3.fail())
	{
		return existe;
	}
	else
	{
		do
		{
			LeerArchivo3 >> datos.correlativo >> datos.codigoCliente2 >> datos.existencia >> datos.costo;
			if (datos.codigoCliente2 == codigoCliente2)
			{
				existe = true;
			}
		} while (!LeerArchivo3.eof());
	}
	LeerArchivo3.close();
	return existe;
}

string Cliente::BuscarNombreCliente(int codigoCliente2)
{
	string nombreDeCliente;
	string archivo = "Clientes/cliente.txt";
	Cliente_struct datos;
	ifstream LeerArchivo3(archivo);
	do
	{
		LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
		if (datos.numeroCliente == codigoCliente2)
		{
			nombreDeCliente = datos.nombreCliente;
		}
	} while (!LeerArchivo3.eof());

	LeerArchivo3.close();
	return nombreDeCliente;
}

//Public
void Cliente::RegistrarCliente()
{
	system("cls");
	Cliente_struct datosCliente;
	bool clienteDuplicado = false;
	datosCliente.numeroCliente = Correlativo();
	cout << "\nRegistro de Cliente\n\n";
	cout << "Codigo de Cliente: " << datosCliente.numeroCliente << endl;
	do
	{
		cout << "Ingrese nombre del Cliente: ";
		while (isspace(cin.peek())) cin.ignore();
		getline(cin, datosCliente.nombreCliente);
		clienteDuplicado = ClienteDuplicado(serializeString(datosCliente.nombreCliente, false));
		if (clienteDuplicado)
		{
			cout << "\n Cliente duplicada!\n\n";
		}
	} while (clienteDuplicado);

	cout << "Ingrese descripcion del Cliente: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, datosCliente.descripcionCliente);

	string archivo2 = "Clientes/cliente.txt";
	EscribirArchivo3.open(archivo2, ios::app);
	if (datosCliente.numeroCliente > 1)
	{
		EscribirArchivo3
			<< endl
			<< datosCliente.numeroCliente
			<< " "
			<< serializeString(datosCliente.nombreCliente, false)
			<< " "
			<< serializeString(datosCliente.descripcionCliente, false);
	}
	else
	{
		EscribirArchivo3
			<< datosCliente.numeroCliente
			<< " "
			<< serializeString(datosCliente.nombreCliente, false)
			<< " "
			<< serializeString(datosCliente.descripcionCliente, false);
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
	cout << "\nCatalogo de Clientes" << "\n";
	if (LeerArchivo3.fail())
	{
		cout << "\n\n\tOcurrio un error al tratar de abrir el archivo *" << archivo << "* intente mas tarde.\n";
	}
	else
	{
		do {
			LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
			cout << "\tCodigo de Cliente: " << datos.numeroCliente << endl;
			cout << "\tNombre de Cliente: " << serializeString(datos.nombreCliente, true) << endl;
			cout << "\tDescripcion de Cliente: " << serializeString(datos.descripcionCliente, true) << "\n\n";

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
	cout << "Modificar nombre de Cliente\n";
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
		LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
		isEnd = LeerArchivo3.eof();
		if (datos.numeroCliente == codigoModificar && datos.nombreCliente == "Cliente-de-baja")
		{
			ClienteBloqueado = true;
		}

		if (datos.numeroCliente == codigoModificar && datos.nombreCliente != "Cliente-de-baja")
		{
			cout << "Numero de Cliente: " << datos.numeroCliente << endl;
			cout << "Nombre de Cliente: " << serializeString(datos.nombreCliente, true) << endl;
			cout << "Descripcion de Cliente: " << serializeString(datos.descripcionCliente, true) << endl;
			cout << "\n\n-----------------------------------------------------------\n\n";
			do {
				cout << "Ingrese nuevo nombre de Cliente: ";
				while (isspace(cin.peek())) cin.ignore();
				getline(cin, datos.nombreCliente);
				//ClienteDuplicado = ClienteDuplicado(serializeString(datos.nombreCliente, false));
				if (ClienteDuplicado)
				{
					cout << "\n Cliente duplicada!\n\n";
				}
			} while (ClienteDuplicado);

			if (datos.numeroCliente > 1) {
				EscribirArchivo3
					<< endl
					<< datos.numeroCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.descripcionCliente, false);
			}
			else {
				EscribirArchivo3
					<< datos.numeroCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.descripcionCliente, false);
			}
		}
		else
		{
			if (datos.numeroCliente > 1) {
				EscribirArchivo3
					<< endl
					<< datos.numeroCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.descripcionCliente, false);
			}
			else {
				EscribirArchivo3
					<< datos.numeroCliente
					<< " "
					<< serializeString(datos.nombreCliente, false)
					<< " "
					<< serializeString(datos.descripcionCliente, false);
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
	cout << "Dar de baja Cliente\n";
	cout << "Tipo de Cliente: " << nombreCliente << "\n\n";
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
		LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
		if (datos.numeroCliente == codigoModificar && datos.nombreCliente != "Cliente-de-baja")
		{
			EscribirArchivo3 << endl << datos.numeroCliente << " " << datos.nombreCliente << " " << datos.descripcionCliente;
			if (datos.numeroCliente > 1)
			{
				nuevoArchivo2
					<< endl
					<< datos.numeroCliente
					<< " "
					<< "Cliente-de-baja"
					<< " "
					<< "*Descripcion-no-disponible";
			}
			else
			{
				nuevoArchivo2
					<< datos.numeroCliente
					<< " "
					<< "Cliente-de-baja"
					<< " "
					<< "*Descripcion-no-disponible";
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
					<< datos.nombreCliente
					<< " "
					<< datos.descripcionCliente;
			}
			else
			{
				nuevoArchivo2
					<< datos.numeroCliente
					<< " "
					<< datos.nombreCliente
					<< " "
					<< datos.descripcionCliente;
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

	string nombreReal, descripcionReal;
	do
	{
		historial >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
		if (datos.numeroCliente == codigoModificar)
		{
			nombreReal = datos.nombreCliente;
			descripcionReal = datos.descripcionCliente;
		}

	} while (!historial.eof());
	historial.close();

	do
	{
		LeerArchivo3 >> datos.numeroCliente >> datos.nombreCliente >> datos.descripcionCliente;
		if (datos.numeroCliente == codigoModificar)
		{

			if (datos.numeroCliente > 1)
				EscribirArchivo3 << endl << datos.numeroCliente << " " << nombreReal << " " << descripcionReal;
			else
				EscribirArchivo3 << datos.numeroCliente << " " << nombreReal << " " << descripcionReal;

		}
		else
		{
			if (datos.numeroCliente > 1)
				EscribirArchivo3
				<< endl
				<< datos.numeroCliente
				<< " "
				<< datos.nombreCliente
				<< " "
				<< datos.descripcionCliente;
			else
				EscribirArchivo3
				<< datos.numeroCliente
				<< " "
				<< datos.nombreCliente
				<< " "
				<< datos.descripcionCliente;
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

void Cliente::InventarioCliente()
{
	system("cls");
	int codigoCliente2;
	string archivo = "Clientes/inventario_cliente.txt";
	Cliente_inventario_struct datos;
	cout << "Registro de inventario de Cliente: " << nombreCliente << endl;
	MostrarCliente();
	cout << "\n\n ---------------------------------------------\n";
	cout << "Ingrese codigo de Cliente: ";
	cin >> codigoCliente2;

	if (ClienteEnInventario(codigoCliente2))
	{
		cout << "\t\nCliente ya existe en inventario\n\n";
		system("pause");
	}
	else
	{
		if (BuscarNombreCliente(codigoCliente2) == "Cliente-de-baja")
		{
			cout << "\t\nNo se puede realizar la operacion si el Cliente esta de baja \n\n";
			system("pause");
		}
		else
		{
			datos.correlativo = CorrelativoInventario();
			cout << "Correlativo: " << datos.correlativo << endl;
			datos.codigoCliente2 = codigoCliente2;
			std::cout << "Ingrese existencia: ";
			cin >> datos.existencia;
			std::cout << "Ingrese precio: ";
			cin >> datos.costo;

			EscribirArchivo3.open(archivo, ios::app);
			if (datos.correlativo > 1)
			{
				EscribirArchivo3 << endl << datos.correlativo << " " << datos.codigoCliente2 << " " << datos.existencia << " " << datos.costo;
			}
			else
			{
				EscribirArchivo3 << datos.correlativo << " " << datos.codigoCliente2 << " " << datos.existencia << " " << datos.costo;
			}
			EscribirArchivo3.close();
			cout << "\n\tRegistro realizado con exito!";
		}
	}
	return;
}

void Cliente::ListarInventarioCliente()
{
	system("cls");
	int codigoCliente2;
	string archivo = "Clientes/inventario_cliente.txt";
	Cliente_inventario_struct datos;
	cout << "Listado de inventario Cliente: " << nombreCliente << endl << endl;

	LeerArchivo3.open(archivo);

	if (LeerArchivo3.fail())
	{
		cout << "\t\nOcurrio un erro al tratar de abrir el archivo\n\n";
	}
	else
	{
		do
		{
			LeerArchivo3 >> datos.correlativo >> datos.codigoCliente2 >> datos.existencia >> datos.costo;
			cout << "\tCorrelativo: " << datos.correlativo << endl;
			cout << "\tCodigo de Cliente: " << datos.codigoCliente2 << endl;
			cout << "\tNombre de Cliente: " << serializeString(BuscarNombreCliente(datos.codigoCliente2),
				true) << endl;
			cout << "\tExistencia: " << datos.existencia << endl;
			cout << "\tCosto: " << "Q." << datos.costo << endl;
			cout << "\t--------------------------------------------------------------------\n\n";
		} while (!LeerArchivo3.eof());
	}
	LeerArchivo3.close();
	return;
}