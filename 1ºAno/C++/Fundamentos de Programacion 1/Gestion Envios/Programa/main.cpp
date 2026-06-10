#include <iostream>
#include <fstream>
using namespace std;

const int MAXPEDIDOS = 50;
const int NUMRIDERS = 8;

struct tHora {
    int horas;
    int minutos;
};

struct tRider {
    int ganancias;
    tHora disponible;
};

struct tListaRiders {
    tRider lista[NUMRIDERS];
};

struct tPedido {
    tHora momentoSolicitado;
    tHora momentoInicio;
    int duracion;
    int rider;
    bool prioritario;
    bool procesado;
};

struct tListaPedidos {
    tPedido lista[MAXPEDIDOS];
    int contador;
};

bool menor(tHora a, tHora b) {
    bool r;
    int x = a.horas * 60 + a.minutos;
    int y = b.horas * 60 + b.minutos;

    if (x < y) {
        r = true;
    }
    else {
        r = false;
    }

    return r;
}

void mostrar(tHora h) {
    if (h.minutos < 10) {
        cout << h.horas << ":0" << h.minutos;
    }
    else {
        cout << h.horas << ":" << h.minutos;
    }
}

tHora mas(tHora h, int m) {
    tHora r = h;
    r.minutos += m;

    if (r.minutos >= 60) {
        r.horas += r.minutos / 60;
        r.minutos = r.minutos % 60;
    }

    return r;
}

bool cargar(tListaPedidos& P) {
    bool ok = true;
    ifstream f("pedidos.txt");

    if (!f.is_open()) {
        ok = false;
    }
    else {
        P.contador = 0;
        int h;
        f >> h;

        while (h != -1 && P.contador < MAXPEDIDOS) {
            P.lista[P.contador].momentoSolicitado.horas = h;
            f >> P.lista[P.contador].momentoSolicitado.minutos;
            f >> P.lista[P.contador].duracion;
            f >> P.lista[P.contador].prioritario;
            P.lista[P.contador].procesado = false;
            P.contador++;
            f >> h;
        }
    }

    return ok;
}

int siguiente(tListaPedidos P) {
    int pos = -1;

    for (int i = 0; i < P.contador; i++) {
        if (P.lista[i].prioritario && !P.lista[i].procesado) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        for (int i = 0; i < P.contador; i++) {
            if (!P.lista[i].procesado) {
                pos = i;
                break;
            }
        }
    }

    return pos;
}

int eligeRider(tListaRiders R) {
    int pos = 0;

    for (int i = 1; i < NUMRIDERS; i++) {
        if (menor(R.lista[i].disponible, R.lista[pos].disponible)) {
            pos = i;
        }
    }

    return pos;
}

void planifica(tListaPedidos& P, tListaRiders& R) {
    cout << "Se asignan los riders...\n";

    int hechos = 0;

    while (hechos < P.contador) {
        int p = siguiente(P);
        int r = eligeRider(R);

        tHora inicio;

        if (menor(R.lista[r].disponible, P.lista[p].momentoSolicitado)) {
            inicio = P.lista[p].momentoSolicitado;
        }
        else {
            inicio = R.lista[r].disponible;
        }

        tHora fin = mas(inicio, P.lista[p].duracion);

        P.lista[p].momentoInicio = inicio;
        P.lista[p].rider = r;
        P.lista[p].procesado = true;

        R.lista[r].disponible = fin;
        R.lista[r].ganancias += P.lista[p].duracion * 21;

        cout << "Pedido a las ";
        mostrar(P.lista[p].momentoSolicitado);
        cout << " - Prioridad: ";

        if (P.lista[p].prioritario) {
            cout << "S";
        }
        else {
            cout << "N";
        }

        cout << " - " << P.lista[p].duracion << "' - Rider " << r + 1 << " - Envio: ";
        mostrar(inicio);
        cout << " -> ";
        mostrar(fin);
        cout << "\n";

        hechos++;
    }
}

void muestra(tListaPedidos P, tListaRiders R) {
    for (int r = 0; r < NUMRIDERS; r++) {
        cout << "Rider " << r + 1 << "\n";
        cout << "Solicitado    Iniciado   Terminado\n";

        for (int i = 0; i < P.contador; i++) {
            if (P.lista[i].rider == r) {
                mostrar(P.lista[i].momentoSolicitado);
                cout << "      ";
                mostrar(P.lista[i].momentoInicio);
                cout << "      ";
                tHora fin = mas(P.lista[i].momentoInicio, P.lista[i].duracion);
                mostrar(fin);
                cout << "\n";
            }
        }

        cout << "Ganancias: " << R.lista[r].ganancias / 100.0 << "\n\n";
    }
}

int main() {
    tListaPedidos pedidos;
    tListaRiders riders;

    for (int i = 0; i < NUMRIDERS; i++) {
        riders.lista[i].ganancias = 0;
        riders.lista[i].disponible.horas = 13;
        riders.lista[i].disponible.minutos = 0;
    }

    bool ok = cargar(pedidos);

    if (ok) {
        planifica(pedidos, riders);
        muestra(pedidos, riders);
    }

    return 0;
}