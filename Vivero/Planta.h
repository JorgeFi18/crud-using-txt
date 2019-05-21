class Planta
{
private:
	int Correlativo (int tipoPlanta);
	bool PlantaDuplicada(int tipoPlanta, std::string nombre);
	void EliminarDeHistorial (std::string historial, int codigoPlanta);
public:
	void RegistrarPlanta(int tipoPlanta);
	void MostrarPlantas(int tipoPlanta);
	void ModificarPlanta(int tipoPlanta);
	void CambioEstado(int tipoPlanta);
	void CambioEstado(int tipoPlanta, bool alta);

	void InventarioPlanta(int tipoPlanta);
};