#include <iostream>

using namespace std;
int Calculo(int Pilas[], int VoltajeNecesario, int nPilas);
void mostrar(int a[], int b);

int main()
{
	int casos, pilas, vPila[1000], vCoche, sumaPilas = 0;
	cin >> casos;
	for (int i = 0; i < casos; i++) 
	{
		cin >> pilas;
		cin >> vCoche;
		for (int j = 0; j < pilas; j++) 
		{
			cin >> vPila[j];
		}
		cout << Calculo(vPila, vCoche, pilas) << endl;
	}
}

int Calculo(int Pilas[], int VoltajeNecesario, int nPilas)
{
    int pos = 0, resultado = 0;
    bool parejaEncontrada = false;

    for (int j = 0; j < nPilas; j++)
    {
        if (Pilas[j] != -1)
        {
            parejaEncontrada = false;
            for (int i = 0; i < nPilas; i++)
            {
                if (i != j && Pilas[i] != -1)
                {
                    if (Pilas[j] + Pilas[i] >= VoltajeNecesario)
                    {
                        if (parejaEncontrada == true && Pilas[i] < Pilas[pos])
                        {
                            pos = i;
                        }
                        else if (parejaEncontrada == false)
                        {
                            pos = i;
                            parejaEncontrada = true;
                        }
                    }
                }
            }
            if (parejaEncontrada == true)
            {
                Pilas[pos] = -1;
                Pilas[j] = -1;
                resultado += 1;
            }
        }
    }
    return resultado;
}

void mostrar(int a[], int b)
{
	for (int i = 0; i < b; i++)
	{
		cout << a[i] << " ";
	}
}