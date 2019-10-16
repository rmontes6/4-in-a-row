#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define N 8
#define FichaJugador 'O'
#define FichaMaquina 'X'
#define Espacio ' '
#define V 1000
#include "cuatro.h"
#include "minimax.h"


Nodo CrearNodo(char tablero[N][N], int nivel, int dificultad){
	
	int i=0; int j;
	
	Nodo p;
	
    p.n_hijos = ColumnasNoLlenas(tablero);
    CopiarTablero(p.tablero,tablero);
    p.valor = 0;
	p.nivel = nivel;
	
	if (GanadorMaquina(p.tablero) || GanadorJugador(p.tablero) || p.nivel==2*dificultad){
        p.n_hijos = 0;
	}
	
	if (p.n_hijos != 0){
        p.hijos = (Nodo **) malloc(p.n_hijos*sizeof(Nodo *));
        p.tiradas_posibles = (int *) malloc(p.n_hijos*sizeof(int));
        for(j=0;j<N;j++){
            if(tablero[0][j] == Espacio){
                p.tiradas_posibles[i] = j;
                i++;
            }
        }
	}
	
	else{
        p.hijos = NULL;
        p.tiradas_posibles = NULL;
	}
	
	return p;
}

void CrearHijo(Nodo* Padre, char ficha, int dificultad){
	
	Nodo* Son;
	int i;
		
	for(i=0;i<Padre->n_hijos;i++){
		
		Son= (Nodo*) malloc(sizeof(Nodo));
		CopiarTablero(Son->tablero, Padre->tablero);
		TirarFicha(Son->tablero, Padre->tiradas_posibles[i], ficha);
		*Son=CrearNodo(Son->tablero, Padre->nivel+1, dificultad);
		Padre->hijos[i]=Son;
		
	}
}

void Crear1Nivel(Nodo* Padre, char ficha, int dificultad){
	CrearHijo(Padre, ficha, dificultad);
}

void CrearNivelDoble(Nodo* Raiz, int dificultad){
	
	Crear1Nivel(Raiz,FichaMaquina,dificultad);
	
	int i;
	for(i=0;i<Raiz->n_hijos;i++) Crear1Nivel(Raiz->hijos[i],FichaJugador,dificultad);
}

void CrearArbol(Nodo* Raiz, int profundidad, int dificultad){
	
	CrearNivelDoble(Raiz,dificultad);
	
	if(profundidad==1){
		return;
	}
	
	else{
		int i,j;
		for(j=0;j<Raiz->n_hijos;j++){
			for(i=0;i<Raiz->hijos[j]->n_hijos;i++){
				CrearArbol(Raiz->hijos[j]->hijos[i],profundidad-1,dificultad);
			}
		}   
	}
	return;
}

void ValorNodo(Nodo* Raiz){
	
    if (Raiz->n_hijos == 0){
        Raiz->valor = Heuristica(Raiz->tablero, Raiz->nivel);
    }
    
    else{
        int i;
        for (i=0;i<Raiz->n_hijos;i++){
            ValorNodo(Raiz->hijos[i]);
        }
    }
}

void Maximo(Nodo*Raiz){
	
	int i;
	Raiz->valor = Raiz->hijos[0]->valor;
	
	for (i=1;i<Raiz->n_hijos;i++){
		if (Raiz->hijos[i]->valor > Raiz->valor){
			Raiz->valor = Raiz->hijos[i]->valor;
        }
    }
}

void Minimo(Nodo* Raiz){
	
	int i;
	Raiz->valor = Raiz->hijos[0]->valor;
	
	for (i=1;i<Raiz->n_hijos;i++){
		if (Raiz->hijos[i]->valor < Raiz->valor){
            Raiz->valor = Raiz->hijos[i]->valor;
        }
    }
}

void MiniMax(Nodo *Raiz){
	
    int i;
    
	if (Raiz->n_hijos != 0){
		
        for (i=0;i<Raiz->n_hijos;i++){
            if (Raiz->hijos[i]->n_hijos != 0){
                MiniMax(Raiz->hijos[i]);
            }
        }
        
		if (Raiz->nivel % 2 == 0){
			Maximo(Raiz);
		}
        

		if (Raiz->nivel % 2 == 1){ 
        	Minimo(Raiz);
        }
	}
}

void BorrarArbol(Nodo* Inicial){
	
	if(Inicial->n_hijos != 0){
		int i;
        for (i=0;i<Inicial->n_hijos;i++){
            BorrarArbol(Inicial->hijos[i]);
        }
        free(Inicial->hijos);
        free(Inicial->tiradas_posibles);
	}
	
	else{
        free(Inicial);
	}

	return;
}

void ImprimirArbol(Nodo* Inicial){
	
    char* guion;
    
    if (Inicial->nivel != 0){
        guion = (char *) malloc((Inicial->nivel+1)*sizeof(char));
        int j; for (j=0;j<Inicial->nivel;j++) guion[j] = '-';
        guion[Inicial->nivel] = '\0';
    }
    
    else{
    	guion = (char *) malloc(sizeof(char));
    	guion[0] = '\0';
    }
    
    if (Inicial->n_hijos == 0) printf("%sNodo (valor %lf, nivel %d)\n",guion,Inicial->valor,Inicial->nivel);
    
    else{
        int i;
        printf("%sNodo (valor %lf, nivel %d)\n",guion,Inicial->valor,Inicial->nivel);
        for (i=0;i<Inicial->n_hijos;i++) ImprimirArbol(Inicial->hijos[i]);
    }
    
    free(guion);
}
