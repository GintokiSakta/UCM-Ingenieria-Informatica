/*---------------------------------------------------------------------
**
**  Fichero:
**    pr4_lab.c  19/10/2022
**
**    (c) Daniel Báscones García
**    Fundamentos de Computadores II
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Fichero de código para la práctica 4_lab
**
**-------------------------------------------------------------------*/
extern int eucl_dist(int w [], int size);
extern void vector_resultado(int *vector, int *res, int mayor_dist, int size);
#define N 5

//nuestros dos vectores de N componentes
int U[N] = {5, 2, -3, 7, 6};
int V[N] = {6, -1, 1, 0, 3};
int res[N];
//variable que almacenará el res: 1 si U es mayor, 0 si es V
char mayor_u;


void guardar(int *vector, int valor, int indice) {
	vector[indice] = valor;
}

int cargar (int *vector, int indice)
{
	return vector[indice];
}

int mul(int a, int b) {
	int res = 0, sign = 0;
	if (a < 0) {
		sign = 1;
		a = -a;
	}
	while (a--) res += b;
	if (sign)
		return -res;
	else
		return res;
}

/**
 * Función simple que obtiene la raíz cuadrada iterativamente
 */
int i_sqrt(int a) {
	int root = 0;
	while (mul(root, root) < a) {
		root++;
	}
	return root;
}

void main() {
	//calculamos la distancia euclídea al origen
	int d_u = eucl_dist(U, N);
	int d_v = eucl_dist(V, N);
	if (d_u > d_v)
	{
		vector_resultado(V, res, d_u, N);
	}
	else {
		vector_resultado(U, res, d_v, N);
	}
	//vemos si U estaba más lejos

	while(1); //quedo en un bucle infinito
}
