#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdio.h>

#include "Factura.h"
#include "Cliente.h"
#include "Insumo.h"
#include "Planta.h"
#include "Helpers.h"

using namespace std;

ofstream EscribirArchivo4;
ifstream LeerArchivo4;

Planta _Planta2;
Insumo _Insumo2;
Cliente _Cliente2;

string answer2;

struct Detalle_factura_struct{
	int correlativo;
	int tipoProducto;
	int codigoProducto;
	int cantidad;
	int subTotal; 
};

struct Encabezado_factura {
	int numero;
	string nit;
	string fecha;
	int total;
};

struct Detalle_factura_producto{
	int	tipoProducto;
	int codigoProducto;
	string nombreProducto;
	int cantidad;
	int precioUnitario;
	int subTotal;
};

int Factura::Correlativo()
{
	int contador = 0;
	string archivo = "Facturas/listado_facturas.txt";
	LeerArchivo4.open(archivo);
	Factura_struct datos;
	if (LeerArchivo4.fail())
	{
		contador = 0;
	}
	else
	{
		bool isEnd = false;
		do
		{
			LeerArchivo4 >> datos.numeroFactura >> datos.nit >>datos.fechaHora >> datos.total;
			contador = datos.numeroFactura;
			isEnd = LeerArchivo4.eof();
		} while (!isEnd);
	}
	LeerArchivo4.close();
	return contador + 1;
	return 0;
}

void Factura::CrearFactura()
{
	system("cls");
	string nit, agregar;
	bool nitInvalido = false, clienteExiste = true;
	Detalle_factura_struct datosFactura;
	cout << "Registrar Factura\n\n";
	
	do
	{
		cout << "Ingrese nit del cliente: ";
		while (isspace(cin.peek())) cin.ignore();
		getline(cin, nit);

		nitInvalido = nit.length() != 9;
		clienteExiste = _Cliente2.ClienteDuplicado(nit);

		if (nitInvalido)
			cout << "\n\nNit invalido, el nit debe tener 9 caracteres\n\n";
		if (!clienteExiste && !nitInvalido) 
		{
			cout << "\n\nEl cliente no esta registrado\n\n";
			cout << "Desea registrar el nuevo cliente (s/n): ";
			cin >> answer2;
			if (validateAnswer(answer2)) 
			{
				_Cliente2.RegistrarCliente(nit);
				CrearFactura();
				clienteExiste = true;
			}
		}
	} while (nitInvalido || !clienteExiste);

	time_t t = time(NULL);
	string fechaHora = asctime(localtime(&t));

	Factura_struct encabezadoFactura;
	encabezadoFactura.numeroFactura = Correlativo();
	encabezadoFactura.nit = nit;
	encabezadoFactura.total = 0;
	encabezadoFactura.fechaHora = removeBreak(fechaHora);

	RegistrarFactura(encabezadoFactura);
	
	do {
		system("cls");
		cout << "\nNIT: " << nit << "\t\t" << fechaHora << endl;
		cout << "Nombre: " << serializeString(_Cliente2.BuscarClientePorNit(nit), true) << "\n\n";

		cout << "- Detalle de factura - \n\n";
		MostrarDetalleFactura(encabezadoFactura.numeroFactura);
		cout << "\n\tAgregar producto (s/n): ";
		cin >> agregar;
		if (validateAnswer(agregar))
		{
			AgregarProductos(encabezadoFactura.numeroFactura);
		}
	} while (validateAnswer(agregar));
	system("pause");
}

void Factura::ListadoFacturas()
{
	system("cls");
	cout << "Listado de facturas\n\n";
	LeerArchivo4.open("Facturas/listado_facturas.txt");
	int seleccion;
	if (LeerArchivo4.fail())
	{
		cout << "\t\nOcurrio un error tratando de abrir el listado de facturas!";
	}
	else
	{
		Encabezado_factura datos;
		do
		{
			LeerArchivo4 >> datos.numero >> datos.nit >> datos.fecha >> datos.total;
			cout << "Numero de factura: " << datos.numero <<endl;
			cout << "Fecha de emision: " << datos.fecha <<endl;
			cout << "Nombre de cliente: " << serializeString(_Cliente2.BuscarClientePorNit(datos.nit), true) << endl;
			cout << "------------------------------------------- \n\n";
		} while (!LeerArchivo4.eof());
	}
	cout << "\n\t Seleccione factura a mostrar: ";
	cin >> seleccion;
	system("cls");
	cout << "\n\n";
	MostrarDetalleFactura(seleccion);
	system("pause");
	LeerArchivo4.close();
}

void Factura::ListarFacturasPorNit()
{
	system("cls");
	string nit;
	cout << "Ingrese nit: ";
	while (isspace(cin.peek())) cin.ignore();
	getline(cin, nit);

	if (_Cliente2.ClienteDuplicado(nit))
	{
		LeerArchivo4.open("Facturas/listado_facturas.txt");
		int seleccion;
		if (LeerArchivo4.fail())
		{
			cout << "\t\nOcurrio un error tratando de abrir el listado de facturas!";
		}
		else
		{
			Encabezado_factura datos;
			do
			{
				LeerArchivo4 >> datos.numero >> datos.nit >> datos.fecha >> datos.total;
				if (datos.nit == nit)
				{
					cout << "Numero de factura: " << datos.numero << endl;
					cout << "Fecha de emision: " << datos.fecha << endl;
					cout << "Nombre de cliente: " << serializeString(_Cliente2.BuscarClientePorNit(datos.nit), true) << endl;
					cout << "------------------------------------------- \n\n";
					
				}
			} while (!LeerArchivo4.eof());
		}
		cout << "\n\t Seleccione factura a mostrar: ";
		cin >> seleccion;
		system("cls");
		cout << "\n\n";
		MostrarDetalleFactura(seleccion);
		system("pause");
		LeerArchivo4.close();
	}
	else
	{
		cout << "El cliente no existe!\n\n";
		system("pause");
	}
}

void Factura::ListarFacturaPorPlanta()
{
	system("cls");
	int tipoPlanta;
	int contador = 1;
	int granTotal= 0;
	cout << "1) Planta medicinal\n";
	cout << "2) Planta silvestre\n";
	cout << "3) Planta ornamental\n";
	cout << "\tIngrese tipo de planta: ";
	cin >> tipoPlanta;
	cout << "\n\n\n";
	Encabezado_factura datos;
	LeerArchivo4.open("Facturas/listado_facturas.txt");
	do {
		LeerArchivo4 >> datos.numero >> datos.nit >> datos.fecha >> datos.total;
		granTotal += MostrarDetalleFactura(datos.numero, tipoPlanta);
	} while (!LeerArchivo4.eof());

	cout << "\n\n\t\t\tTotal: Q" << granTotal << endl;
	LeerArchivo4.close();
	system("pause");
}

void Factura::RegistrarFactura(Factura_struct info) 
{
	EscribirArchivo4.open("Facturas/listado_facturas.txt", ios::app);
	if (info.numeroFactura > 1) 
	{
		EscribirArchivo4
			<< endl
			<< info.numeroFactura
			<< " "
			<< info.nit
			<< " "
			<< serializeString(info.fechaHora, false)
			<< " " 
			<< info.total;
	}
	else
	{
		EscribirArchivo4 
			<< info.numeroFactura 
			<< " " 
			<< info.nit 
			<< " " 
			<< serializeString(info.fechaHora, false)
			<< " " 
			<< info.total;
	}
	EscribirArchivo4.close();
	return;
}

void Factura::AgregarProductos(int numeroFactura)
{
	int seleccion;
	do 
	{
		system("cls");
		cout << "Productos disponibles\n\n";
		cout << "1) Plantas Medicinales.\n";
		cout << "2) Plantas Silvestre.\n";
		cout << "3) Plantas Ornamentales.\n";
		cout << "4) Insumos. \n";
		cout << "\t Seleccione una opcion: ";
		cin >> seleccion;
	} while (seleccion > 4);
	
	AgregarProductosFactura(seleccion, numeroFactura);
}

void Factura::AgregarProductosFactura(int tipoProducto, int numeroFactura)
{
	if (tipoProducto == 1)
	{
		_Planta2.SeleccionarPlanta("Plantas/inventario_Medicinal.txt", numeroFactura, 1);
	}
	else if (tipoProducto == 2)
	{
		_Planta2.SeleccionarPlanta("Plantas/inventario_Silvestre.txt", numeroFactura, 2);
	}
	else if (tipoProducto == 3)
	{
		_Planta2.SeleccionarPlanta("Plantas/inventario_Ornamental.txt", numeroFactura, 3);
	}
	else if (tipoProducto == 4)
	{
		_Insumo2.SeleccionarInsumo("Insumos/inventario_insumo.txt", numeroFactura);
	}
	return;
}

void Factura::MostrarDetalleFactura(int nFactura)
{
	string numerofactura = "Facturas/factura_" + std::to_string(nFactura) + ".txt";
	ifstream leerDetalle(numerofactura);
	int total = 0;

	Detalle_factura_producto datos;
	string cantidad = "";

	if (!leerDetalle.fail())
	{
		do
		{
			leerDetalle >> datos.tipoProducto >> datos.codigoProducto >> datos.nombreProducto >> datos.cantidad >> datos.precioUnitario >> datos.subTotal;
			if (datos.cantidad < 10) 
			{
				cout <<"0" << datos.cantidad;
			}
			else
			{
				cout << datos.cantidad;
			}
			cout << "| " << datos.nombreProducto << "(Q." << datos.precioUnitario << ")";
			cout << " subtotal - (Q."<<datos.subTotal <<")"<< endl;
			total += datos.subTotal;
		} while (!leerDetalle.eof());
	}
	cout << "\t\t\t\t\tTotal: Q." <<total <<endl;
	leerDetalle.close();
	return;
}

int Factura::MostrarDetalleFactura(int nFactura, int tipoPlanta)
{
	string numerofactura = "Facturas/factura_" + std::to_string(nFactura) + ".txt";
	ifstream leerDetalle(numerofactura);
	int total = 0;

	Detalle_factura_producto datos;
	string cantidad = "";

	if (!leerDetalle.fail())
	{
		do
		{
			leerDetalle >> datos.tipoProducto >> datos.codigoProducto >> datos.nombreProducto >> datos.cantidad >> datos.precioUnitario >> datos.subTotal;
			if (datos.tipoProducto == tipoPlanta)
			{
				if (datos.cantidad < 10)
				{
					cout << "0" << datos.cantidad;
				}
				else
				{
					cout << datos.cantidad;
				}
				cout << "| " << datos.nombreProducto << "(Q." << datos.precioUnitario << ")";
				cout << " subtotal - (Q." << datos.subTotal << ")" << endl;
				total += datos.subTotal;
			}
		} while (!leerDetalle.eof());
	}
	leerDetalle.close();
	return total;
}
