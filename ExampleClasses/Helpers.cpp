#include <string>
using namespace std;

string serializeString(string str, bool reverse)
{
	string from = " ";
	string to = "-";
	if (reverse)
	{
		from = "-";
		to = " ";
	}

	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) 
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

bool validateAnswer(string answer)
{
	bool output = answer.compare("si") == 0;
	return output;
}

string plantaMayuscula(string tipoPlanta)
{
	string mayuscula;
	if (tipoPlanta == "medicinal") 
	{
		mayuscula = "MEDICINAL";
	}
	else if (tipoPlanta == "ornamental")
	{
		mayuscula = "ORNAMENTAL";
	}
	else if (tipoPlanta == "silvestre")
	{
		mayuscula = "SILVESTRE";
	}

	return mayuscula;
}