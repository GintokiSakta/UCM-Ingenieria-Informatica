#include <iostream>
#include <string>
using namespace std;

int Letras(const string& palabra, int i, int acumulado);
bool Palindroma(const string& palabra, int i, int j, bool acumulado);
string Inversa(const string& palabra, int i, string acumulado);

int main()
{
    string palabra;
    while (cin >> palabra)
    {
        cout << Letras(palabra, 0, 0) << " ";

        if (Palindroma(palabra, 0, palabra.size() - 1, true)) 
        {
            cout << "SI ";
        }
        else 
        {
            cout << "NO ";
        }
        cout << Inversa(palabra, palabra.size() - 1, "") << "\n";
    }
}

bool esVocal(char c)
{
    bool aux = false;
    c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
        aux = true;
    }
    return aux;
}

int Letras(const string& palabra, int aux, int acumulado)
{
    if (aux == palabra.size())
    {
        acumulado = acumulado;
    }
    else
    {
        if (esVocal(palabra[aux]))
        {
            acumulado = Letras(palabra, aux + 1, acumulado + 1);
        }
        else 
        {
            acumulado = Letras(palabra, aux + 1, acumulado);
        }
    }
    return acumulado;
}

bool Palindroma(const string& palabra, int aux, int temp, bool acumulado)
{
    if (aux >= temp) 
    {
        acumulado = acumulado;
    }
    else if (tolower(palabra[aux]) != tolower(palabra[temp])
)
    {
        acumulado = false;
    }
    else 
    {
        acumulado = Palindroma(palabra, aux + 1, temp - 1, acumulado);
    }
    return acumulado;
}

string Inversa(const string& palabra, int aux, string acumulado)
{
    if (aux < 0) 
    {
        acumulado = acumulado;
    }
    else 
    {
        acumulado = Inversa(palabra, aux - 1, acumulado + palabra[aux]);
    }
    return acumulado;   
}
