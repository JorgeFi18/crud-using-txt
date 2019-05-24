
//hector
class Cliente
{
public:
	void RegistrarCliente();
	void MostrarCliente();
	void ModificarCliente();
	void CambioEstado();
	void CambioEstado(bool alta);

	void InventarioCliente();
	void ListarInventarioCliente();

private:
	int Correlativo();
	int CorrelativoInventario();
	bool ClienteDuplicado(std::string nombre);
	void EliminarDeHistorial(std::string historial, int codigoCliente);
	bool ClienteEnInventario(int codigoCliente);
	std::string BuscarNombreCliente(int codigoCliente);
}; 
