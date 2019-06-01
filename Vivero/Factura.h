class Factura {
	struct Factura_struct {
		int numeroFactura;
		std::string nit;
		int total;
		std::string fechaHora;
	};
private:
	int Correlativo();
	void RegistrarFactura(Factura_struct info);
	void AgregarProductos(int nFactura);
	void AgregarProductosFactura(int tipoProducto, int numeroFactura);
	void MostrarDetalleFactura(int numerofactura);
public:
	void CrearFactura();
	void ListadoFacturas();
};