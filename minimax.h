typedef struct nodo {
	int n_hijos;
	char tablero[N][N];
	double valor;
    int nivel;
	struct nodo **hijos;
    int *tiradas_posibles;
} Nodo;

Nodo CrearNodo(char[N][N], int, int);
void CrearHijo(Nodo*, char, int);
void Crear1Nivel(Nodo *, char, int);
void CrearNivelDoble(Nodo *, int);
void CrearArbol(Nodo*, int, int);
void ValorNodo(Nodo*);
void Minimo(Nodo*);
void Maximo(Nodo*);
void MiniMax(Nodo*);
void BorrarArbol(Nodo*);
void ImprimirArbol(Nodo*);
