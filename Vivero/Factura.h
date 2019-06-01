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
	int MostrarDetalleFactura(int numerofactura, int tipoPlanta);
public:
	void CrearFactura();
	void ListadoFacturas();
	void ListarFacturasPorNit();
	void ListarFacturaPorPlanta();
};