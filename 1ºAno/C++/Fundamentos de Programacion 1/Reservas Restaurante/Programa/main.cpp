#include <iostream>
#include <fstream>

const int MAX = 20;

using namespace std;

struct tMesa 
{
	char ubicacion;
	int capacidad;
	bool reservada = false;
	string cliente;
	int nComensales;
};

struct tListaMesas
{
	tMesa mesas[MAX];
	int contador = 0;
}listaMesa;

struct tReserva
{
	string reserva; //reserva o cancelacion
	string cliente;
	int comensales;
	char ubicacion;
};

bool cargarMesas();
int buscarCliente(string acronimo);
int buscarMesa(int nComensales, char zonaDeseada);
void reservar(int nComensales, char zonaDeseada, string Cliente);
void Cancelar(string Cliente);
void procesarReservas();
void mostrar();

int main()
{
	cargarMesas();
	procesarReservas();
	cout << "\n";
	mostrar();
	return 0;
}

bool cargarMesas()
{
	ifstream Archivo;
	Archivo.open("mesas.txt");
	bool aux = true;
	if (Archivo.is_open() == false)
	{
		aux = false;
	}
	int capacidad;
	char lugar;
	Archivo >> capacidad;

	while (capacidad != -1)
	{
		Archivo >> lugar;
		listaMesa.mesas[listaMesa.contador].capacidad = capacidad;
		listaMesa.mesas[listaMesa.contador].ubicacion = lugar;
		Archivo >> capacidad;
		listaMesa.contador += 1;
	}
	Archivo.close();
	return aux;
}

int buscarCliente(string acronimo)
{
	int i = 0;
	bool encontrado = false;
	while (encontrado == false && i < listaMesa.contador)
	{
		if (acronimo == listaMesa.mesas[i].cliente)
		{
			encontrado = true;
		}
		else 
		{
			i++;
		}
	}
	if (encontrado == false)
	{
		i = -1;
	}
	return i;
}

int buscarMesa(int nComensales, char zonaDeseada)
{
	int i = 0;
	bool encontrado = false;
	while (encontrado == false && i < listaMesa.contador)
	{
		if ((listaMesa.mesas[i].capacidad == nComensales || listaMesa.mesas[i].capacidad-1 == nComensales) && listaMesa.mesas[i].ubicacion == zonaDeseada && listaMesa.mesas[i].reservada == false)
		{
			encontrado = true;
		}
		else
		{
			i++;
		}
	}
	if (encontrado == false)
	{
		i = -1;
	}
	return i;
}

void reservar(int nComensales, char zonaDeseada, string Cliente)
{
	int aux = buscarMesa(nComensales, zonaDeseada);
	if (aux != -1)
	{
		listaMesa.mesas[aux].reservada = true;
		listaMesa.mesas[aux].nComensales = nComensales;
		listaMesa.mesas[aux].cliente = Cliente;
		if (zonaDeseada == 'I')
		{
			cout << "Reservar en interior, " << Cliente << ", " << nComensales << " pax" << " :" << " Confirmada\n";
		}
		else
		{
			cout << "Reservar en terraza, " << Cliente << ", " << nComensales << " pax" << " :" << " Confirmada\n";
		}
	}
	else 
	{
		if (zonaDeseada == 'I')
		{
			cout << "Reservar en interior, " << Cliente << ", " << nComensales << " pax" << " :" << " Imposible\n";
		}
		else if (zonaDeseada == 'T')
		{
			cout << "Reservar en terraza, " << Cliente << ", " << nComensales << " pax" << " :" << " Imposible\n";
		}
	}
}

void Cancelar(string Cliente)
{
	int aux = buscarCliente(Cliente);
	if (aux != -1)
	{
		listaMesa.mesas[aux].reservada = false;
		cout << "Cancelar mesa de " << Cliente << " :" << " Confirmada\n";
	}
	else 
	{
		cout << "Cancelar mesa de " << Cliente << " :" << " Reserva no encontrada\n";
	}
}

void procesarReservas()
{
	ifstream Archivo;
	Archivo.open("reservas.txt");
	if (Archivo.is_open() == true)
	{
		char auxComando, auxUbicacion;
		string auxCliente;
		int auxComensales;

		Archivo >> auxComando;
		while (auxComando != 'X')
		{
			Archivo >> auxCliente;
			if (auxComando == 'R')
			{
				Archivo >> auxComensales;
				Archivo >> auxUbicacion;
				reservar(auxComensales, auxUbicacion, auxCliente);
			}
			else
			{
				Cancelar(auxCliente);
			}
			Archivo >> auxComando;
		}
	}
	else
	{
		cout << "No se encuentra archivo 'reservas.txt'\n";
	}
	Archivo.close();
}

void mostrar()
{
	cout << "Lista de mesas...\n";
	for (int i = 0; i < listaMesa.contador; i++)
	{
		if (listaMesa.mesas[i].reservada == true)
		{
			cout << "Mesa " << i + 1 << " (" << listaMesa.mesas[i].ubicacion << listaMesa.mesas[i].capacidad << ") :" << " Reservada a " << listaMesa.mesas[i].cliente << " (" << listaMesa.mesas[i].nComensales << ")\n";
		}
		else 
		{
			cout << "Mesa " << i + 1 << " (" << listaMesa.mesas[i].ubicacion << listaMesa.mesas[i].capacidad << ") :" << " No reservada\n";
		}
	}
}