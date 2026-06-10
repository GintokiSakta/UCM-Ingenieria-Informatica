#include <iostream>

using namespace std;

const int MAX = 100000;

struct SecuenciaLista {
	int Lista[MAX];
	int contador;
};

void resuelveCaso();
int resolver(const int v[MAX], int n);

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
	SecuenciaLista Secuencia;
	for (int i = 0; i < tamanoSecuencia; i++)
	{
		cin >> Secuencia.Lista[i];
		Secuencia.contador += 1;
	}
	if (resolver(Secuencia.Lista, tamanoSecuencia) == -1)
	{
		cout << "NO" << endl;
	}
	else 
	{
		cout << resolver(Secuencia.Lista, tamanoSecuencia) << endl;
	}
}

int resolver(const int v[MAX], int n)
{
	bool Buscando = true;
	int pos, retorno, aux = n-1;
	while (Buscando == true)
	{
		int res = 0;
		for (int i = aux; i < n-1; i++)
		{
			res += v[i+1];
		}
		if (v[aux] == res)
		{
			Buscando = false;
			retorno = aux;
		}
		else 
		{
			aux -= 1;
			if (aux < 0 && Buscando == true)
			{
				Buscando = false;
				retorno = -1;
			}
		}
	}
	return retorno;
}