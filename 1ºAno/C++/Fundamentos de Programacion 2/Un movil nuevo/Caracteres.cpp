#include <iostream>

using namespace std;

struct Moviles
{
	int Lista[200000];
	int  contador = 0;
};

void ordenar();

Moviles Electro;
Moviles Tecno;
Moviles Resultado;

int main()
{
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; i++)
	{
		cin >> Electro.contador;
		cin >> Tecno.contador;
		for (int j = 0; j < Electro.contador; j++)
		{
			cin >> Electro.Lista[j];
		}
		for (int j = 0; j < Tecno.contador; j++)
		{
			cin >> Tecno.Lista[j];
		}
		ordenar();
	}
}

void ordenar()
{
	Resultado.contador = Electro.contador + Tecno.contador;
	int posElectro = 0, posTecno = 0;
	for (int i = 0; i < Resultado.contador; i++)
	{
		if (posElectro >= Electro.contador)
		{
			Resultado.Lista[i] = Tecno.Lista[posTecno];
			posTecno += 1;
		}
		else if (posTecno >= Tecno.contador)
		{
			Resultado.Lista[i] = Electro.Lista[posElectro];
			posElectro += 1;
		}
		else if (Electro.Lista[posElectro] <= Tecno.Lista[posTecno])
		{
			Resultado.Lista[i] = Electro.Lista[posElectro];
			posElectro += 1;
		}
		else if (Electro.Lista[posElectro] > Tecno.Lista[posTecno])
		{
			Resultado.Lista[i] = Tecno.Lista[posTecno];
			posTecno += 1;
		}
	}

	for (int i = 0; i < Resultado.contador; i++)
	{
		cout << Resultado.Lista[i] << " ";
	}
	cout << endl;
}