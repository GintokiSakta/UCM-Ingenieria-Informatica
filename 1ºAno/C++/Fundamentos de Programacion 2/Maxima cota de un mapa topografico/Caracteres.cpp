#include <iostream>

using namespace std;

struct Mapa
{
	int Cuadricula[1000][1000];
};

void Mapear(int x, int y);

Mapa Caso;

int main()
{
	int x, y;
	while (cin >> x >> y && x > 0 && y > 0) {
		Mapear(x, y); //Filas x Columnas
	}
}

void Mapear(int x, int y)
{
	int CotaMax, PosX, PosY;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cin >> Caso.Cuadricula[i][j];
			if (i == 0 && j == 0)
			{
				CotaMax = Caso.Cuadricula[0][0];
				PosX = 0;
				PosY = 0;
			}
			if (CotaMax < Caso.Cuadricula[i][j])
			{
				CotaMax = Caso.Cuadricula[i][j];
				PosX = i;
				PosY = j;
			}
		}
	}
	cout << CotaMax << " " << PosX << " " << PosY << endl;
}