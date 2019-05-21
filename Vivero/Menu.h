class Menu
{
public:
	//Menus
	int MenuPrincipal ();

	int MenuPlantas ();
	int MenuTipoPlanta (int tipoPlanta);
	int MenuCambioEstadoPlanta(int tipoPlanta);

	int MenuInventario ();
	int MenuInventarioTipo(int tipo);

	//Opciones
	void MenuPrincipalOpciones (int opcion);

	void MenuPlantasOpciones (int opcion);
	void MenuTipoPlantaOpciones (int opcion, int tipoPlanta);
	void MenuCambioEstadoPlantaOpciones(int opcion, int tipoPlanta);

	void MenuInventarioOpciones(int opcion);
	void MenuInventarioTipoOpciones(int opcion, int tipo);
};