class Menu
{
public:
	//Menus
	int MenuPrincipal ();
	int MenuPlantas ();
	int MenuTipoPlanta (int tipoPlanta);
	int MenuCambioEstadoPlanta(int tipoPlanta);

	//Opciones
	void MenuPrincipalOpciones (int opcion);
	void MenuPlantasOpciones (int opcion);
	void MenuTipoPlantaOpciones (int opcion, int tipoPlanta);
	void MenuCambioEstadoPlantaOpciones(int opcion, int tipoPlanta);
};