
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
	int BuscarDatos(int codigoInsumo, std::string tipoDato);
	int SeleccionarInsumo(std::string archivo, int nFactura);

	void ActualizarExistencia(std::string archivo, int codigoPlanta, int cantidad);

private:
	int Correlativo();
	int CorrelativoInventario();
	bool InsumoDuplicado(std::string nombre);
	void EliminarDeHistorial(std::string historial, int codigoInsumo);
	bool InsumoEnInventario(int codigoInsumo);
	std::string BuscarNombreInsumo(int codigoInsumo);
};
