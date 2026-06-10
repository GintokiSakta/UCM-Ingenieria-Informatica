#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int main()
{
	char sopa[100][100];
	int T;
	cin >> T;

	while (T > 0)
	{
		int N, M;
		cin >> N >> M;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> sopa[i][j];
			}
		}

		int Q;
		cin >> Q;
		int encontradas = 0;
		for (int p = 0; p < Q; p++)
		{
			string palabra;
			cin >> palabra;

			bool aux = false;

			for (int i = 0; i < N; i++) 
			{
				for (int j = 0; j < M; j++)
				{
					for (int df = -1; df <= 1; df++)
					{
						for (int dc = -1; dc <= 1; dc++)
						{
							if (df != 0 || dc != 0)
							{
								bool correcta = true;

								for (int k = 0; k < palabra.length() && correcta; k++)
								{
									int fila = i + df * k;
									int columna = j + dc * k;

									if (fila < 0 || fila >= N)
									{
										correcta = false;
									}

									if (columna < 0 || columna >= M)
									{
										correcta = false;
									}

									if (correcta == true)
									{
										if (sopa[fila][columna] != palabra[k])
										{
											correcta = false;
										}
									}
								}

								if (correcta == true)
								{
									aux = true;
								}
							}
						}
					}
				}
			}
			if (aux == true) 
			{ 
				encontradas++;
			}
		}
		cout << encontradas << "\n";
		T--;
	}
}
