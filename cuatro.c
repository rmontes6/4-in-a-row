#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define N 8
#define FichaJugador 'O'
#define FichaMaquina 'X'
#define Espacio ' '
#define V 1000
#include "minimax.h"
#include "cuatro.h"

void main(){
	srand(time(NULL));
	Inicio();
}

void Inicio(){

	system("cls");
	printf("                                                     \n    ");
	printf("  ******** *      * ************************ ******* \n    ");
	printf("  *        *      * *      *    *    *     * *     * \n    ");
	printf("  *        *      * *      *    *    *     * *     * \n    ");
	printf("  *        *      * ********    *    ******* *     * \n    ");
	printf("  *        *      * *      *    *    *   *   *     * \n    ");
	printf("  *        *      * *      *    *    *    *  *     * \n    ");
	printf("  ******** ******** *      *    *    *     * ******* \n    ");
	printf("  __________________________________________________ \n\n\n");

	printf("\t1. Maquina vs Jugador\n\n\n");
	printf("\t2. Jugador vs Jugador\n");

	char Respuesta = getch();

	//JugadorvsCPU
	if(Respuesta=='1'){
		system("cls");
		printf("\t\t\t\tELIGE DIFICULTAD\n\n\n");
		printf("1. Facil\n\n");
		printf("2. Normal\n\n");
		printf("3. Dificil\n\n");
	
		char Respuesta2 = getch();
		int dificultad;
	
		if(Respuesta2=='1'){
			dificultad=1;
		}	 
		if(Respuesta2=='2'){
			dificultad=2;	
		} 
		if(Respuesta2=='3'){
			dificultad=3;	
		} 
	
		char partida[N][N];
		Inicializacion(partida);
		ImprimirTablero(partida);
		int cont_empate=0;
		
		while(cont_empate<N*N){
		
			JugadaJugador(partida);
			ImprimirTablero(partida);
			if(GanadorJugador(partida)){
				printf("HAS GANADO!(%c)\n",FichaJugador);
				system("PAUSE");
				break;
			}
			cont_empate++;
		
			int columna=JugadaMaquina(partida, dificultad);
			TirarFicha(partida,columna,FichaMaquina);
			ImprimirTablero(partida);
			if(GanadorMaquina(partida)){
				printf("HA GANADO LA MAQUINA! (%c)\n",FichaMaquina);
				system("PAUSE");
				break;
			}
			cont_empate++;
		}
		
		if(cont_empate==N*N){
			printf("EMPATE");
			system("PAUSE");
		}
		return;
	}

	//JugadorvsJugador
	if(Respuesta=='2'){
	
		char partida[N][N];
		Inicializacion2(partida);
		ImprimirTablero(partida);
		int cont_empate=0;
		
		while(cont_empate<N*N){
			
			Jugada(partida,1);
			ImprimirTablero(partida);
			if(GanadorJugador(partida)){
				printf("HA GANADO EL JUGADOR 1 (%c)\n",FichaJugador);
				system("PAUSE");
				break;
			}
			cont_empate++;
			
			Jugada(partida,2);
			ImprimirTablero(partida);
			if(GanadorMaquina(partida)){
				printf("HA GANADO EL JUGADOR 2 (%c)\n",FichaMaquina);
				system("PAUSE");
				break;
			}
			cont_empate++;
		}
		
		if(cont_empate==N*N){
			printf("EMPATE!\n");
			system("PAUSE");
		}
		
		return;
	}
}
		
//Funcion que inicia la partida, con las casillas del tablero vacias
void Inicializacion(char tablero[N][N]){
	
	system("color 8E");
	
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++) tablero[i][j] = Espacio;
	}
}

void Inicializacion2(char tablero[N][N]){
	
	system("color 4E");
	
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++) tablero[i][j] = Espacio;
	}
}

//Funcion que imprime el tablero de la partida
void ImprimirTablero(char tablero[N][N]){

	system("cls");
	
	int i,j;
	//Numeracion de columnas
	printf("\t\t\t");
	for(j=0;j<N;j++) printf("  %d ",j+1); printf("\n\n");
	
	//Creacion de limites
	for(i=0;i<N;i++){
		printf("\t\t\t -------------------------------\n"); printf("\t\t\t|");
		for(j=0;j<N;j++) printf(" %c |",tablero[i][j]); printf("\n");
	} 
	
	printf("\t\t\t -------------------------------"); printf("\n");
}

//Funcion la cual el nodo copia el tablero del padre
void CopiarTablero(char tablero1[N][N], char tablero[N][N]){
	
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++) tablero1[i][j]=tablero[i][j];
	}
}

//Funcion que calcula cuantos hijos tiene un nodo
int ColumnasNoLlenas(char tablero[N][N]){
	
	int num_hijos;
	int j;
	int cl=0;
	
	for(j=0;j<N;j++){
		if(tablero[0][j]!=Espacio) cl++;
	}
	
	num_hijos=8-cl;
	
	return num_hijos;
}

//Funcion que permite al jugador tirar una ficha
void JugadaJugador(char tablero[N][N]){
	
	char ficha = FichaJugador;
	
	int columna; int fila = N-1;
	
	printf("\t\t\t");
	printf("(Jugador (%c)) En que columna juegas?\n",FichaJugador);
    
	columna = getch(); 
	
	while(tablero[0][columna-49] != Espacio){
		printf("\t\t\t");
		printf("Columna llena, tira en otra columna!\n");
		columna = getch();
	} 
	
	while(tablero[fila][columna-1] != Espacio) fila--;
	
	tablero[fila][columna-1] = ficha;	
}

//Variante de la funcion anterior, en esta la funcion depende de la variable jugador
void Jugada(char tablero[N][N], int jugador){
	
	char ficha = (jugador == 1)?FichaJugador:FichaMaquina;
	
	int columna; int fila = N-1;
	
	if(jugador==1){
		printf("\t\t\t");
		printf("(Jugador 1 (%c)) En que columna juegas?",FichaJugador);
    } 
    else{
    	printf("\t\t\t");
    	printf("(Jugador 2 (%c)) En que columna juegas?",FichaMaquina);
    }
    
	columna = getch(); 
	
	while(tablero[0][columna-49] != Espacio){
		printf("\t\t\t");
		printf("Columna llena, tira en otra columna!\n");
		columna = getch();
	}
	
	while(tablero[fila][columna-1] != Espacio) fila--;
	
	tablero[fila][columna-1] = ficha;	
}

//Funcion que permite a la CPU aplicar tirada (tambien por cada Nodo)
void TirarFicha(char tablero[N][N], int columna, char ficha){
	int i;
	
	for(i=0;i<N;i++){
		if(tablero[N-i-1][columna]==Espacio){
			tablero[N-i-1][columna]=ficha;
			break;
		}
		
	}	
}

//Funcion que decide si el ganador es el jugador
int GanadorJugador(char tablero[N][N]){
	
	int i; int j;
	
	char ficha = FichaJugador;
	
	/*vertical*/
	for(i=0;i<N-3;i++){
		for(j=0;j<N;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i+1][j] == ficha){
					if(tablero[i+2][j] == ficha){
						if(tablero[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	/*horizontal*/
	for(i=0;i<N;i++){
		for(j=0;j<N-3;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i][j+1] == ficha){
					if(tablero[i][j+2] == ficha){
						if(tablero[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	/*diagonal*/
	for(i=0;i<N-3;i++){
		for(j=0;j<N-3;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i+1][j+1] == ficha){
					if(tablero[i+2][j+2] == ficha){
						if(tablero[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	
	/*diagonal contraria*/
	for(i=0;i<N-3;i++){
		for(j=3;j<N;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i+1][j-1] == ficha){
					if(tablero[i+2][j-2] == ficha){
						if(tablero[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

//Funcion que decide si el ganador es la CPU
int GanadorMaquina(char tablero[N][N]){
	
	int i; int j;
	
	char ficha = FichaMaquina;
	
	/*vertical*/
	for(i=0;i<N-3;i++){
		for(j=0;j<N;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i+1][j] == ficha){
					if(tablero[i+2][j] == ficha){
						if(tablero[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	/*horizontal*/
	for(i=0;i<N;i++){
		for(j=0;j<N-3;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i][j+1] == ficha){
					if(tablero[i][j+2] == ficha){
						if(tablero[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	/*diagonal*/
	for(i=0;i<N-3;i++){
		for(j=0;j<N-3;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i+1][j+1] == ficha){
					if(tablero[i+2][j+2] == ficha){
						if(tablero[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	/*diagonal contraria*/
	for(i=0;i<N-3;i++){
		for(j=3;j<N;j++){
			if(tablero[i][j] == ficha){
				if(tablero[i+1][j-1] == ficha){
					if(tablero[i+2][j-2] == ficha){
						if(tablero[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

//Funcion que mira la altura de una columna
int MirarAltura (char tablero[N][N], int columna)
{
	int i;
	int h=0;
	
	for(i=0;i<N;i++){
		if(tablero[i][columna]==Espacio){
			h++;
		}
	}
	
	return h;
}

//Funcion que se encarga de dar valor por cada situacion de la partida
int Heuristica(char tablero[N][N], int nivel){
	
	int i,j;
	int altura=0;
	
	if(nivel % 2 == 0){
		
		if(GanadorJugador(tablero)) return (nivel-V);
		
		else{
			
			//MIRA TRES CONSECUTIVAS
			/*horitzontal*/
			char ficha= FichaJugador;
			for(i=0;i<N;i++){
				for(j=0;j<N-2;j++){
					if(tablero[i][j] == ficha && tablero[i][j+1] == ficha && tablero[i][j+2] == ficha){
						return (nivel-V/2);
					}
				}
			}
			/*vertical*/
			for(i=0;i<N-2;i++){
				for(j=0;j<N;j++){
					if(tablero[i][j] == ficha && tablero[i+1][j] == ficha && tablero[i+2][j] == ficha){
						return (nivel-V/2);
					}
				}
			}
			/*diagonal*/
			for(i=0;i<N-2;i++){
				for(j=0;j<N-2;j++){
					if(tablero[i][j] == ficha && tablero[i+1][j+1] == ficha && tablero[i+2][j+2] == ficha ){
						return (nivel-V/2);
					}
				}
			}
			/*diagonal contraria*/
			for(i=0;i<N-2;i++){
				for(j=2;j<N;j++){
					if(tablero[i][j] == ficha && tablero[i+1][j-1] == ficha && tablero[i+2][j-2] == ficha ){
						return (nivel-V/2);
					}
				}
			}

			//MIRA DOS ENTRE UN ESPACIO
			for(i=0;i<N;i++){
				for(j=0;j<3;j++){
					if(tablero[i][j] == ficha && tablero[i][j+1] == Espacio && tablero[i][j+2] == ficha){
						
						if(tablero[i][3]==FichaMaquina){
							return 0;
						}
						if(tablero[i+1][j+1] != Espacio){
							if(tablero[i][3]==Espacio){
								altura=abs(MirarAltura(tablero,2)-MirarAltura(tablero,3));
								return ((-V/4)+altura);
							}
						
						}
					}
				}
			}
			
			for(i=0;i<N;i++){
				for(j=N-3;j<N;j++){
					if(tablero[i][j] == ficha && tablero[i][j+1] == Espacio && tablero[i][j+2] == ficha ){
					
						if(tablero[i][4]==FichaMaquina)	{
							return 0;
						}
						
						if(tablero[i+1][j+1] != Espacio){
							if(tablero[i][4]==Espacio){
								altura=abs(MirarAltura(tablero,5)-MirarAltura(tablero,4));
								return ((-V/4)+altura);	
							}
						}
						
					}
				}
			}
			
		return 0;
		
		}
	}
	
	if(nivel % 2 == 1){
		if(GanadorMaquina(tablero)) return (V-nivel);
	}
}

//Funcion que permite a la maquina decidir en que columna jugar
int JugadaMaquina(char tablero[N][N],int dificultad){
	
	Nodo Inicial = CrearNodo(tablero,0,dificultad);
	CrearArbol(&Inicial,dificultad,dificultad);
	ValorNodo(&Inicial);
	MiniMax(&Inicial);
	
	int n = 0;
	int col_igual_valor[8];
	int i; int j=0;
	
	for (i=0;i<Inicial.n_hijos;i++){
		if (Inicial.hijos[i]->valor == Inicial.valor){
			n++;
			col_igual_valor[j] = Inicial.tiradas_posibles[i];
			j++;
		}
	}
	
	int col = col_igual_valor[rand()%n];
	
	/*ImprimirArbol(&Inicial);
	printf("\n");
	printf("Las posibles columnas de igual valor de tirada son:");
	for(i=0;i<n;i++){
		printf("%d ",col_igual_valor[i]+1);
	}
	printf("\nHe elegido tirar en: %d\n",col+1);
	system("PAUSE");*/

	BorrarArbol(&Inicial);

	return col;
}

