#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 100;

int Matriz[MAX][MAX];

void definirMatriz(int N, int M, int Matriz[][MAX]);
void mostrarMatriz(int N, int M, int Matriz[][MAX]);
void filas(int N, int M, int Matriz[][MAX]);
void columnas(int N, int M, int Matriz[][MAX]);
void cruz(int N, int M, int Matriz[][MAX]);
void rotarFila(int N, int M, int Matriz[][MAX]);
void rotarCol(int N, int M, int Matriz[][MAX]);



int main()
{
	int N = 1, M = 1;
	string Transformacion;
	int Transformaciones;
	while (N != 0 && M != 0) {
		cin >> N;
		cin >> M;
		if (N != 0 && M != 0) {
			definirMatriz(N, M, Matriz);
			cin >> Transformaciones;
			for (int j = 0; j < Transformaciones; j++)
			{
				cin >> Transformacion;
				if (Transformacion == "filas")
				{
					filas(N, M, Matriz);
				}
				else if (Transformacion == "columnas")
				{
					columnas(N, M, Matriz);
				}
				else if (Transformacion == "cruz")
				{
					cruz(N, M, Matriz);
				}
				else if (Transformacion == "rotarFila")
				{
					rotarFila(N, M, Matriz);
				}
				else if (Transformacion == "rotarCol")
				{
					rotarCol(N, M, Matriz);
				}
			}
			mostrarMatriz(N, M, Matriz);
			cout << "---" << endl;
		}
	}
}

void definirMatriz(int N, int M, int Matriz[][MAX])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) 
		{
			cin >> Matriz[i][j];
		}
	}
}

void mostrarMatriz(int N, int M, int Matriz[][MAX])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << Matriz[i][j] << " ";
		}
		cout << endl;
	}
}

void filas(int N, int M, int Matriz[][MAX])
{
	int a, b, aux;
	cin >> a;
	a -= 1;
	cin >> b;
	b -= 1;
	for (int i = 0; i < M; i++)
	{
		aux = Matriz[a][i];
		Matriz[a][i] = Matriz[b][i];
		Matriz[b][i] = aux;
	}
}

void columnas(int N, int M, int Matriz[][MAX])
{
	int a, b, aux;
	cin >> a;
	a -= 1;
	cin >> b;
	b -= 1;
	for (int i = 0; i < N; i++)
	{
		aux = Matriz[i][a];
		Matriz[i][a] = Matriz[i][b];
		Matriz[i][b] = aux;
	}
}

void cruz(int N, int M, int Matriz[][MAX])
{
	int f, c, d, aux, centro;
	cin >> f;
	f -= 1;
	cin >> c;
	c -= 1;
	cin >> d;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (abs(i - f) == abs(j - c))
			{
				Matriz[i][j] = d;
			}
		}
	}
}

void rotarFila(int N, int M, int Matriz[][MAX])
{
	int f, aux;
	cin >> f;
	if (f > 0)
	{
		f -= 1;
		aux = Matriz[f][M - 1];
		for (int i = M - 1; i > 0; i--)
		{
			Matriz[f][i] = Matriz[f][i - 1];
		}
		Matriz[f][0] = aux;
	}
	else if (f < 0)
	{
		f = abs(f);
		f -= 1;
		for (int i = 0; i < M - 1; i++)
		{
			aux = Matriz[f][i];
			Matriz[f][i] = Matriz[f][i + 1];
			Matriz[f][i + 1] = aux;
		}
	}
}

void rotarCol(int N, int M, int Matriz[][MAX])
{
	int c, aux;
	cin >> c;
	if (c > 0)
	{
		c -= 1;
		aux = Matriz[N-1][c];
		for (int i = N-1; i > 0; i--)
		{
			Matriz[i][c] = Matriz[i -1][c];
		}
		Matriz[0][c] = aux;
	}
	else if (c < 0)
	{
		c = abs(c);
		c -= 1;
		for (int i = 0; i < N-1; i++)
		{
			aux = Matriz[i][c];
			Matriz[i][c] = Matriz[i+1][c];
			Matriz[i+1][c] = aux;
		}
	}
}