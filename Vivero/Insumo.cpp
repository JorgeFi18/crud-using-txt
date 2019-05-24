//Librerias externas

#include <iostream>
#include <string>
#include <fstream>

//Librerias internas
#include "Helpers.h"
#include "Insumo.h"

//Namespaces
using namespace std;

//structs
struct Insumo_struct
{
	int numeroInsumo;
	string nombreInsumo;
	string descripcionInsumo;
};

struct Insumo_inventario_struct
{
	int correlativo;
	int codigoInsumo2;
	int existencia;
	int costo;
};

//Globales
string nombreInsumo = "";
ifstream LeerArchivo2;
ofstream EscribirArchivo2;

//Private

int Insumo::Correlativo()
{
	int contador = 0;
	string archivo = "Insumos/insumo.txt";
	LeerArchivo2.open(archivo);
	Insumo_struct datos;
	if (LeerArchivo2.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
			contador = datos.numeroInsumo;
			isEnd = LeerArchivo2.eof();
		} while (!isEnd);
	}
	LeerArchivo2.close();
	return contador + 1;
}


int Insumo::CorrelativoInventario()
{
	int contador = 0;
	string archivo = "Insumos/inventario_insumo.txt";
	LeerArchivo2.open(archivo);
	Insumo_inventario_struct datos;
	if (LeerArchivo2.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo2 >> datos.correlativo >> datos.codigoInsumo2 >> datos.existencia >> datos.costo;
			contador = datos.correlativo;
			isEnd = LeerArchivo2.eof();
		} while (!isEnd);
	}
	LeerArchivo2.close();
	return contador + 1;
}


bool Insumo::InsumoDuplicado(std::string nombre)
{
	bool duplicado = false;
	Insumo_struct datos;
	string archivo = "Insumos/insumo.txt";

	ifstream  src(archivo);
	ofstream  dst("Insumos/pivote.txt");

	dst << src.rdbuf();
	dst.close();

	ifstream Lectura("Insumos/pivote.txt");

	if (Lectura.fail())
	{
		duplicado = false;
	}
	else
	{
		bool isEnd = false;
		do
		{
			Lectura >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
			if (datos.nombreInsumo == nombre)
			{
				duplicado = true;
			}
			isEnd = Lectura.eof();
		} while (!isEnd);
	}
	Lectura.close();
	remove("Insumos/pivote.txt");
	return duplicado;
}

void Insumo::EliminarDeHistorial(string historial, int codigoInsumo2)
{
	Insumo_struct datos;
	LeerArchivo2.open(historial);
	EscribirArchivo2.open("Insumos/pivote.txt");
	if (LeerArchivo2.fail())
	{
		//do this
	}
	else
	{
		do {
			LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
			if (datos.numeroInsumo != codigoInsumo2)
			{
				EscribirArchivo2 << endl << datos.numeroInsumo << " " << datos.nombreInsumo << " " << datos.descripcionInsumo;
			}
		} while (!LeerArchivo2.eof());
	}

	LeerArchivo2.close();
	EscribirArchivo2.close();

	const char *cstr = historial.c_str();
	remove(cstr);
	rename("Insumos/pivote.txt", cstr);
	return;
}

bool Insumo::InsumoEnInventario(int codigoInsumo2)
{
	bool existe = false;
	Insumo_inventario_struct datos;
	string archivo = "Insumos/inventario_insumo.txt";
	LeerArchivo2.open(archivo);
	if (LeerArchivo2.fail())
	{
		return existe;
	}
	else
	{
		do
		{
			LeerArchivo2 >> datos.correlativo >> datos.codigoInsumo2 >> datos.existencia >> datos.costo;
			if (datos.codigoInsumo2 == codigoInsumo2)
			{
				existe = true;
			}
		} while (!LeerArchivo2.eof());
	}
	LeerArchivo2.close();
	return existe;
}

string Insumo::BuscarNombreInsumo(int codigoInsumo2)
{
	string nombreDeInsumo;
	string archivo = "Insumos/insumo.txt";
	Insumo_struct datos;
	ifstream LeerArchivo2(archivo);
	do
	{
		LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
		if (datos.numeroInsumo == codigoInsumo2)
		{
			nombreDeInsumo = datos.nombreInsumo;
		}
	} while (!LeerArchivo2.eof());

	LeerArchivo2.close();
	return nombreDeInsumo;
}

//Public
void Insumo::RegistrarInsumo()
{
	system("cls");
	Insumo_struct datosInsumo;
	bool insumoDuplicado = false;
	datosInsumo.numeroInsumo = Correlativo();
	cout << "\nRegistro de insumo: " << nombreInsumo << "\n\n";
	cout << "Codigo de insumo: " << datosInsumo.numeroInsumo << endl;
	do
	{
		cout << "Ingrese nombre del insumo: ";
		while (isspace(cin.peek())) cin.ignore();
		getline(cin, datosInsumo.nombreInsumo);
		insumoDuplicado = InsumoDuplicado(serializeString(datosInsumo.nombreInsumo, false));
		if (insumoDuplicado)
		{
			cout << "\n Planta duplicada!\n\n";
		}
	} while (insumoDuplicado);

	cout << "Ingrese descripcion del insumo: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, datosInsumo.descripcionInsumo);

	string archivo2 = "Insumos/insumo.txt";
	EscribirArchivo2.open(archivo2, ios::app);
	if (datosInsumo.numeroInsumo > 1)
	{
		EscribirArchivo2
			<< endl
			<< datosInsumo.numeroInsumo
			<< " "
			<< serializeString(datosInsumo.nombreInsumo, false)
			<< " "
			<< serializeString(datosInsumo.descripcionInsumo, false);
	}
	else
	{
		EscribirArchivo2
			<< datosInsumo.numeroInsumo
			<< " "
			<< serializeString(datosInsumo.nombreInsumo, false)
			<< " "
			<< serializeString(datosInsumo.descripcionInsumo, false);
	}

	EscribirArchivo2.close();
	return;
}

void Insumo::MostrarInsumo()
{
	string archivo = "Insumos/insumo.txt";

	Insumo_struct datos;

	system("cls");
	LeerArchivo2.open(archivo);
	cout << "\nCatalogo de insumos" << "\n\n";
	if (LeerArchivo2.fail())
	{
		cout << "\n\n\tOcurrio un error al tratar de abrir el archivo *" << archivo << "* intente mas tarde.\n";
	}
	else
	{
		do {
			LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
			cout << "\tCodigo de insumo: " << datos.numeroInsumo << endl;
			cout << "\tNombre de insumo: " << serializeString(datos.nombreInsumo, true) << endl;
			cout << "\tDescripcion de insumo: " << serializeString(datos.descripcionInsumo, true) << "\n\n";

		} while (!LeerArchivo2.eof());

		cout << "\tFin de la lista.\n";
	}

	LeerArchivo2.close();
	return;
}

void Insumo::ModificarInsumo()
{
	int codigoModificar;
	bool insumoBloqueado = false;
	bool isEnd = false;
	bool insumoDuplicado = false;
	Insumo_struct datos;
	cout << "Modificar nombre de insumo\n";
	string archivo = "Insumos/insumo.txt";
	MostrarInsumo();

	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	//Lecrtura
	LeerArchivo2.open(archivo);
	//Escritura
	EscribirArchivo2.open("Insumos/temporal.txt");
	do
	{
		LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
		isEnd = LeerArchivo2.eof();
		if (datos.numeroInsumo == codigoModificar && datos.nombreInsumo == "Insumo-de-baja")
		{
			insumoBloqueado = true;
		}

		if (datos.numeroInsumo == codigoModificar && datos.nombreInsumo != "Insumo-de-baja")
		{
			cout << "Numero de insumo: " << datos.numeroInsumo << endl;
			cout << "Nombre de insumo: " << serializeString(datos.nombreInsumo, true) << endl;
			cout << "Descripcion de insumo: " << serializeString(datos.descripcionInsumo, true) << endl;
			cout << "\n\n-----------------------------------------------------------\n\n";
			do {
				cout << "Ingrese nuevo nombre de insumo: ";
				while (isspace(cin.peek())) cin.ignore();
				getline(cin, datos.nombreInsumo);
				//insumoDuplicado = insumoDuplicado(serializeString(datos.nombreInsumo, false));
				if (insumoDuplicado)
				{
					cout << "\n Planta duplicada!\n\n";
				}
			} while (insumoDuplicado);

			if (datos.numeroInsumo > 1) {
				EscribirArchivo2
					<< endl
					<< datos.numeroInsumo
					<< " "
					<< serializeString(datos.nombreInsumo, false)
					<< " "
					<< serializeString(datos.descripcionInsumo, false);
			}
			else {
				EscribirArchivo2
					<< datos.numeroInsumo
					<< " "
					<< serializeString(datos.nombreInsumo, false)
					<< " "
					<< serializeString(datos.descripcionInsumo, false);
			}
		}
		else
		{
			if (datos.numeroInsumo > 1) {
				EscribirArchivo2
					<< endl
					<< datos.numeroInsumo
					<< " "
					<< serializeString(datos.nombreInsumo, false)
					<< " "
					<< serializeString(datos.descripcionInsumo, false);
			}
			else {
				EscribirArchivo2
					<< datos.numeroInsumo
					<< " "
					<< serializeString(datos.nombreInsumo, false)
					<< " "
					<< serializeString(datos.descripcionInsumo, false);
			}
		}
	} while (!isEnd);

	if (insumoBloqueado) {
		std::cout << "\n\tNo se permite modificar nombre si el insumo esta de baja!\n";
		system("pause");
	}

	LeerArchivo2.close();
	EscribirArchivo2.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Insumos/temporal.txt", cstr);
	return;
}

void Insumo::CambioEstado()
{
	system("cls");
	int codigoModificar;
	string archivo = "Insumos/insumo.txt";
	cout << "Dar de baja insumo\n";
	cout << "Tipo de insumo: " << nombreInsumo << "\n\n";
	MostrarInsumo();
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	Insumo_struct datos;
	//Lectura
	LeerArchivo2.open(archivo);
	string historico = "Insumos/historial_insumo.txt";

	EscribirArchivo2.open(historico, ios::app);
	ofstream nuevoArchivo2("Insumos/temporal.txt");

	do
	{
		LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
		if (datos.numeroInsumo == codigoModificar && datos.nombreInsumo != "Insumo-de-baja")
		{
			EscribirArchivo2 << endl << datos.numeroInsumo << " " << datos.nombreInsumo << " " << datos.descripcionInsumo;
			if (datos.numeroInsumo > 1)
			{
				nuevoArchivo2
					<< endl
					<< datos.numeroInsumo
					<< " "
					<< "Insumo-de-baja"
					<< " "
					<< "*Descripcion-no-disponible";
			}
			else
			{
				nuevoArchivo2
					<< datos.numeroInsumo
					<< " "
					<< "Insumo-de-baja"
					<< " "
					<< "*Descripcion-no-disponible";
			}
		}
		else
		{
			if (datos.numeroInsumo > 1)
			{
				nuevoArchivo2
					<< endl
					<< datos.numeroInsumo
					<< " "
					<< datos.nombreInsumo
					<< " "
					<< datos.descripcionInsumo;
			}
			else
			{
				nuevoArchivo2
					<< datos.numeroInsumo
					<< " "
					<< datos.nombreInsumo
					<< " "
					<< datos.descripcionInsumo;
			}

		}
	} while (!LeerArchivo2.eof());

	//cerrar archivos
	LeerArchivo2.close();
	EscribirArchivo2.close();
	nuevoArchivo2.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Insumos/temporal.txt", cstr);
}

void Insumo::CambioEstado(bool alta)
{
	int codigoModificar;
	string archivo = "Insumos/insumo.txt";
	Insumo_struct datos;
	MostrarInsumo();
	cout << "\nIngrese el codigo a modificar: ";
	cin >> codigoModificar;

	string historico = "Insumos/historial_insumo.txt";

	//Lectura
	LeerArchivo2.open(archivo);
	ifstream historial(historico);

	EscribirArchivo2.open("Insumos/temporal.txt");

	string nombreReal, descripcionReal;
	do
	{
		historial >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
		if (datos.numeroInsumo == codigoModificar)
		{
			nombreReal = datos.nombreInsumo;
			descripcionReal = datos.descripcionInsumo;
		}

	} while (!historial.eof());
	historial.close();

	do
	{
		LeerArchivo2 >> datos.numeroInsumo >> datos.nombreInsumo >> datos.descripcionInsumo;
		if (datos.numeroInsumo == codigoModificar)
		{

			if (datos.numeroInsumo > 1)
				EscribirArchivo2 << endl << datos.numeroInsumo << " " << nombreReal << " " << descripcionReal;
			else
				EscribirArchivo2 << datos.numeroInsumo << " " << nombreReal << " " << descripcionReal;

		}
		else
		{
			if (datos.numeroInsumo > 1)
				EscribirArchivo2
				<< endl
				<< datos.numeroInsumo
				<< " "
				<< datos.nombreInsumo
				<< " "
				<< datos.descripcionInsumo;
			else
				EscribirArchivo2
				<< datos.numeroInsumo
				<< " "
				<< datos.nombreInsumo
				<< " "
				<< datos.descripcionInsumo;
		}
	} while (!LeerArchivo2.eof());

	//cerrar archivos
	LeerArchivo2.close();
	EscribirArchivo2.close();

	const char *cstr = archivo.c_str();
	remove(cstr);
	rename("Insumos/temporal.txt", cstr);
	EliminarDeHistorial(historico, codigoModificar);
}

void Insumo::InventarioInsumo()
{
	system("cls");
	int codigoInsumo2;
	string archivo = "Insumos/inventario_insumo.txt";
	Insumo_inventario_struct datos;
	cout << "Registro de inventario de insumo: " << nombreInsumo << endl;
	MostrarInsumo();
	cout << "\n\n ---------------------------------------------\n";
	cout << "Ingrese codigo de insumo: ";
	cin >> codigoInsumo2;

	if (InsumoEnInventario(codigoInsumo2))
	{
		cout << "\t\nPlanta ya existe en inventario\n\n";
		system("pause");
	}
	else
	{
		if (BuscarNombreInsumo(codigoInsumo2) == "Insumo-de-baja")
		{
			cout << "\t\nNo se puede realizar la operacion si el insumo esta de baja \n\n";
			system("pause");
		}
		else
		{
			datos.correlativo = CorrelativoInventario();
			cout << "Correlativo: " << datos.correlativo << endl;
			datos.codigoInsumo2 = codigoInsumo2;
			std::cout << "Ingrese existencia: ";
			cin >> datos.existencia;
			std::cout << "Ingrese precio: ";
			cin >> datos.costo;

			EscribirArchivo2.open(archivo, ios::app);
			if (datos.correlativo > 1)
			{
				EscribirArchivo2 << endl << datos.correlativo << " " << datos.codigoInsumo2 << " " << datos.existencia << " " << datos.costo;
			}
			else
			{
				EscribirArchivo2 << datos.correlativo << " " << datos.codigoInsumo2 << " " << datos.existencia << " " << datos.costo;
			}
			EscribirArchivo2.close();
			cout << "\n\tRegistro realizado con exito!";
		}
	}
	return;
}

void Insumo::ListarInventarioInsumo()
{
	system("cls");
	int codigoInsumo2;
	string archivo = "Insumos/inventario_insumo.txt";
	Insumo_inventario_struct datos;
	cout << "Listado de inventario insumo: " << nombreInsumo << endl << endl;

	LeerArchivo2.open(archivo);

	if (LeerArchivo2.fail())
	{
		cout << "\t\nOcurrio un erro al tratar de abrir el archivo\n\n";
	}
	else
	{
		do
		{
			LeerArchivo2 >> datos.correlativo >> datos.codigoInsumo2 >> datos.existencia >> datos.costo;
			cout << "\tCorrelativo: " << datos.correlativo << endl;
			cout << "\tCodigo de insumo: " << datos.codigoInsumo2 << endl;
			cout << "\tNombre de insumo: " << serializeString(BuscarNombreInsumo(datos.codigoInsumo2),
				true) << endl;
			cout << "\tExistencia: " << datos.existencia << endl;
			cout << "\tCosto: " << "Q." << datos.costo << endl;
			cout << "\t--------------------------------------------------------------------\n\n";
		} while (!LeerArchivo2.eof());
	}
	LeerArchivo2.close();
	return;
}