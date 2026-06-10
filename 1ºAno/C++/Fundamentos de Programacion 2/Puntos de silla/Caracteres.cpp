/*
* #include <iostream>

using namespace std;

struct Usuario 
{
	int Identificador, periodoTiempo;
};

struct UCM
{
	Usuario Lista[];
} Datos;

int main()
{
	int numeroUsuarios, Respuestas;
	cin >> numeroUsuarios;
	while (numeroUsuarios != 0)
	{
		for (int i = 0; i < numeroUsuarios; i++)
		{
			cin >> Datos.Lista[i].Identificador;
			cin >> Datos.Lista[i].periodoTiempo;
		}
		cin >> Respuestas;
		CalculoTiempo(numeroUsuarios, Respuestas);
		cin >> numeroUsuarios;
	}
}

void CalculoTiempo(int Usuarios, int Respuestas)
{
	int Tiempo = 0;
	for (int i = 0; i < Usuarios; i++)
	{
		
	}
}
*/

#include <iostream>

using namespace std;

int Matriz[300][300];
void rellenar(int filas, int columnas);
bool buscar(int f, int c, int filas, int columnas);


int main()
{
	int filas = 1, columnas = 1;
	while (filas != 0 && columnas != 0)
	{
		cin >> filas;
		cin >> columnas;

		rellenar(filas, columnas);
		bool aux = false;
		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				if (aux == false)
				{
					if (buscar(i, j, filas, columnas) == true)
					{
						cout << "SI" << "\n";
						aux = true;
					}
					else
					{
						aux = false;
					}
				}
			}
		}
		if (aux == false && filas != 0 && columnas != 0)
		{
			cout << "NO" << "\n";
		}
	}
}


void rellenar(int filas, int columnas)
{
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cin >> Matriz[i][j];
		}
	}
}

bool buscar(int f, int c, int filas, int columnas)
{
	int posibleSilla = Matriz[f][c];
	bool esSilla = true;
	if (esSilla == true)
	{
		for (int i = 0; i < filas; i++)
		{
			if (Matriz[i][c] < posibleSilla)
			{
				esSilla = false;
			}
		}
		for (int i = 0; i < columnas; i++)
		{
			if (Matriz[f][i] > posibleSilla)
			{
				esSilla = false;
			}
		}
	}
	if (esSilla == false)
	{
		esSilla = true;
		for (int i = 0; i < filas; i++)
		{
			if (Matriz[i][c] > posibleSilla)
			{
				esSilla = false;
			}
		}
		for (int i = 0; i < columnas; i++)
		{
			if (Matriz[f][i] < posibleSilla)
			{
				esSilla = false;
			}
		}
	}
	return esSilla;
}