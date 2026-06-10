#include <iostream>

using namespace std;

int Digitos(int numero, int aux);
bool Capicua(int numero);
int Inverso(int numero, int acumulado);

int main()
{
		int numero;
		while (cin >> numero)
		{
			cout << Digitos(numero, 0) << " ";
			if (Capicua(numero) == 1)
			{
				cout << "SI" << " ";
			}
			else
			{
				cout << "NO" << " ";
			}
			cout << Inverso(numero, 0);
			cout << "\n";
		}
}

int Digitos(int numero, int aux)
{
	if (numero < 0)
	{
		numero = -numero;
	}
	if (numero < 10)
	{
		aux += 1;
	}
	else 
	{
		aux += 1;
		aux = Digitos(numero / 10, aux);
	}

	return aux;
}

bool Capicua(int numero)
{
	bool aux;
	int dig = Digitos(numero, 0);
	if (numero < 0)
	{
		numero = -numero;
	}
	if (dig <= 1 || numero == 0) 
	{
		aux = true;
	}
	else 
	{
		int potencia = 1;
		for (int i = 1; i < dig; i++)
			potencia *= 10;

		int primero = numero / potencia;
		int ultimo = numero % 10;

		if (primero != ultimo) 
		{
			aux = false;
		}
		else {
			int nuevo = (numero % potencia) / 10;
			aux = Capicua(nuevo);
		}
	}
	return aux;
}

int Inverso(int numero, int acumulado)
{
	int aux, temp = false;
	if (numero < 0)
	{
		temp = true;
		numero = -numero;
	}
	if (numero < 10) {
		aux = acumulado * 10 + numero;
	}
	else {
		aux = Inverso(numero / 10, acumulado * 10 + (numero % 10));
	}
	if (temp == true)
	{
		aux *= -1;
	}
	return aux;
}