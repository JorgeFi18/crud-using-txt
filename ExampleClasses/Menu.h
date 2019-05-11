#include <string>

class Menu
{
	int seleccion = 0;
	public:
		Menu();
		~Menu();
		int Principal ();
		int SubMenu (std::string tipoPlanta);
		int EstadoMenu(std::string tipoPlanta);
		void RegistroPlanta (std::string tipoPlanta);
		void OpcionesMenu (int seleccion, std::string tipoPlanta);
		void OpcionesEstado(int seleccion, std::string tipoPlanta);
};

