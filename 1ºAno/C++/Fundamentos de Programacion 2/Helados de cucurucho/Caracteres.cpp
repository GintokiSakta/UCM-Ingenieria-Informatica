#include <iostream>
#include <string>
using namespace std;

void generar(int Chocolate, int Vainilla, string actual, bool& primero);

int main() {
    int casos;
    cin >> casos;
    while (casos != 0) 
    {
        int Chocolate, Vainilla;
        cin >> Chocolate;
        cin >> Vainilla;
        bool primero = true;
        
        generar(Chocolate, Vainilla, "", primero);
        cout << "\n";
        casos -= 1;
    }
}

void generar(int Chocolate, int Vainilla, string actual, bool& primero)
{
    if (Chocolate == 0 && Vainilla == 0)
    {
        if (primero == false)
        {
            cout << " ";    
        }
        cout << actual;
        primero = false;
    }
    else
    {
        if (Chocolate > 0)
        {
            generar(Chocolate - 1, Vainilla, actual + "C", primero);
        }

        if (Vainilla > 0) 
        {
            generar(Chocolate, Vainilla - 1, actual + "V", primero);
        }
    }
}
