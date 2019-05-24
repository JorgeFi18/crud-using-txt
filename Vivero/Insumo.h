
//hector
class Insumo
{
public:
	void RegistrarInsumo();
	void MostrarInsumo();
	void ModificarInsumo();
	void CambioEstado();
	void CambioEstado(bool alta);

	void InventarioInsumo();
	void ListarInventarioInsumo();

private:
	int Correlativo();
	int CorrelativoInventario();
	bool InsumoDuplicado(std::string nombre);
	void EliminarDeHistorial(std::string historial, int codigoInsumo);
	bool InsumoEnInventario(int codigoInsumo);
	std::string BuscarNombreInsumo(int codigoInsumo);
};
