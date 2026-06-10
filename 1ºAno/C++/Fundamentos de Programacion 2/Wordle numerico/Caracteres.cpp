#include <iostream>

using namespace std;

const int MAX = 2000;


class Multiconjunto
{
private:
	struct Elem
	{
		int valor;
		int multiplicidad;
	};
	

public:
	Multiconjunto()
	{
		num_elems = 0;
	}
	Elem elems[MAX];
	int num_elems;

	void insertar(int elem)
	{
		bool encontrado = false;

		for (int i = 0; i < num_elems; i++)
		{
			if (elems[i].valor == elem)
			{
				elems[i].multiplicidad++;
				encontrado = true;
			}
		}

		if (encontrado == false)
		{
			elems[num_elems].valor = elem;
			elems[num_elems].multiplicidad = 1;
			num_elems++;
		}
	}

	void eliminar(int elem)
	{
		for (int i = 0; i < num_elems; i++)
		{
			if (elems[i].valor == elem)
			{
				elems[i].multiplicidad--;

				if (elems[i].multiplicidad == 0)
				{
					elems[i] = elems[num_elems - 1];
					num_elems--;
				}
			}
		}
	}

	bool pertenece(int elem)
	{
		bool encontrado = false;

		for (int i = 0; i < num_elems; i++)
		{
			if (elems[i].valor == elem)
			{
				if (elems[i].multiplicidad > 0)
				{
					encontrado = true;
				}
			}
		}
		return encontrado;
	}
};

int main()
{
	int aux;

	cin >> aux;

	while (aux != 0)
	{
		Multiconjunto numeros;

		int secreta[MAX];
		int intento[MAX];
		char resultado[MAX];

		for (int i = 0; i < aux; i++)
		{
			cin >> secreta[i];
		}

		for (int i = 0; i < aux; i++)
		{
			cin >> intento[i];
		}

		for (int i = 0; i < aux; i++)
		{
			if (secreta[i] != intento[i])
			{
				numeros.insertar(secreta[i]);
			}
		}

		for (int i = 0; i < aux; i++)
		{
			if (secreta[i] == intento[i])
			{
				resultado[i] = '#';
			}
			else
			{
				if (numeros.pertenece(intento[i]))
				{
					resultado[i] = 'O';
					numeros.eliminar(intento[i]);
				}
				else
				{
					resultado[i] = '.';
				}
			}
		}

		for (int i = 0; i < aux; i++)
		{
			cout << resultado[i];
		}
		cout << "\n";
		cin >> aux;
	}
}