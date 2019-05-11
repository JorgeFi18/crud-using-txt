#include <string>
struct Planta
{
	std::string archivo;
	int numeroPlanta;
	std::string nombrePlanta;
};

class Operaciones
{
public:
	Operaciones ();
	~Operaciones ();
	bool Registro (Planta planta);
	void Mostrar (std::string archivo);
	int Correlativo (std::string archivo);
	void Modificar (std::string archivo);
	void CambioEstado (std::string archivo);
	void CambioEstado (std::string archivo, bool reverse);
};

