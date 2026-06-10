#include <iostream>
#include <string>

using namespace std;
string resolver(string Frase);
int main()
{
	int Casos;
	string Frase;
	cin >> Casos; //Numero de Casos
	cin.ignore(80, '\n');
	for (int i = 0; i < Casos; i++)
	{
		getline(cin, Frase);
		resolver(Frase);
	}
}

string resolver (string Frase)
{
	cout << Frase.size() << " ";
	for (int i = Frase.size()-1; i >= 0; i--)
	{
		char aux;
		aux = toupper(Frase[i]);
		cout << aux;
	}
	cout << "\n";
	return Frase;
}