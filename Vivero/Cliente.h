
//hector
class Cliente
{
public:
	void RegistrarCliente(std::string nit);
	void MostrarCliente();
	void ModificarCliente();
	void CambioEstado();
	void CambioEstado(bool alta);
	bool ClienteDuplicado(std::string nombre);
	std::string BuscarClientePorNit(std::string nit);

private:
	int Correlativo();
	void EliminarDeHistorial(std::string historial, int codigoCliente);
	std::string BuscarNombreCliente(int codigoCliente);
}; 
