#include <iostream>

using namespace std;

struct ArraySecuencia
{
	int Lista[1000];
	int contador = -1;
};

void resuelveCaso();
int resolver(int Secuencia[], int contador, int Umbral);

int main()
{
	int numeroCasos;
	cin >> numeroCasos;
	for (int i = 0; i < numeroCasos; i++)
	{
		resuelveCaso();
	}
}

void resuelveCaso()
{
	int tamanoSecuencia;
	cin >> tamanoSecuencia;
	int Umbral;
	cin >> Umbral;
	ArraySecuencia Secuencia;
	for (int i = 0; i < tamanoSecuencia; i++)
	{
		int temp = -1;
		while (temp < 0)
		{
			cin >> temp;
		}
		Secuencia.Lista[i] = temp;
		Secuencia.contador += 1;
	}
	int resultado = resolver(Secuencia.Lista, Secuencia.contador, Umbral);
	if (resultado != -1)
	{
		cout << Secuencia.Lista[resultado] << " " << Secuencia.Lista[resultado+1] << "\n";
	}
	else 
	{
		cout << "NO" << "\n";
	}
}

int resolver(int Secuencia[], int contador, int Umbral)
{
	int existe = 0, aux = 0;
	bool yaEncontrado;
	if (contador < 1)
	{
		existe = -1;
		yaEncontrado = true;
	}
	else 
	{
		yaEncontrado= false;
	}

	while (yaEncontrado == false)
	{
		if (Secuencia[aux] + Secuencia[aux + 1] > Umbral && yaEncontrado == false)
		{
			yaEncontrado = true;
			existe = aux;
		}
		aux += 1;
		if (aux == contador && yaEncontrado == false)
		{
			existe = -1;
			yaEncontrado = true;
		}
	}
	return existe;
}