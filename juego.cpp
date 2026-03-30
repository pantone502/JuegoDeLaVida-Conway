#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <windows.h> // Lo use para que el comando Sleep y los colores funcionen en mi PC

using namespace std;

// --- CONFIGURACION DE REGLAS ---
// Use constantes en mayusculas para no marearme con los numeros luego
const int NACIMIENTO = 3;
const int MIN_VIVA = 2;
const int MAX_VIVA = 3;

// --- MIS FUNCIONES ---
// Las nombre en snake_case para que el codigo se vea ordenado y profesional
void inicializar_tablero(vector<vector<int>>& tablero, int tamano);
int calcular_vecinos_vivos(const vector<vector<int>>& tablero, int fila, int columna, int tamano);
void actualizar_tablero(vector<vector<int>>& tablero, int tamano);
void imprimir_tablero(const vector<vector<int>>& tablero, int tamano);

int main() {
    // Aqui le meti un poco de estilo hacker con verde (0A) 
    // y le cambie el titulo a la ventana para que no diga la ruta del archivo
    system("title PROYECTO LEO - JUEGO DE LA VIDA");
    system("color 0A"); 

    int tamanoTablero;
    int generacionesSimular;

    cout << "===============================================" << endl;
    cout << "       JUEGO DE LA VIDA por AXEl DARDON      " << endl;
    cout << "===============================================" << endl;
    cout << "[?] De que tamano quieres el mapa ej.23? ";
    cin >> tamanoTablero;
    cout << "[?] Cuantas generaciones corremos? ";
    cin >> generacionesSimular;

    // Use vectores de vectores (matriz dinamica). 
    // Me tomo un rato entender como funcionaban, pero los use porque permiten 
    // que el tablero cambie de tamano segun lo que pida el usuario.
    vector<vector<int>> tableroPrincipal(tamanoTablero, vector<int>(tamanoTablero, 0));

    // Lleno el tablero con vida al azar
    inicializar_tablero(tableroPrincipal, tamanoTablero);

    for (int gen = 0; gen < generacionesSimular; gen++) {
        // El system("cls") es el truco para que parezca una animacion 
        // y no se imprima todo hacia abajo como loco.
        system("cls"); 
        
        cout << ">> GENERACION ACTUAL: " << gen + 1 << " | Leo's Simulation" << endl;
        cout << "-----------------------------------------------" << endl;
        
        imprimir_tablero(tableroPrincipal, tamanoTablero);
        actualizar_tablero(tableroPrincipal, tamanoTablero);

        // Sleep(150) hace que el programa espere un poquito entre cada turno. 
        // Si no lo pongo, va tan rapido que ni se ve que pasa.
        Sleep(150); 
    }

    cout << "\n[!] Fin de la simulacion. Presiona Enter para salir...";
    cin.ignore();
    cin.get();
    return 0;
}

// Lleno el tablero con 0s y 1s de forma aleatoria
void inicializar_tablero(vector<vector<int>>& tablero, int tamano) {
    srand(time(NULL)); 
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            // Use una probabilidad del 25% (rand % 100 < 25).
            // Si ponia 50/50 habia demasiada poblacion y todo moria muy rapido.
            tablero[i][j] = (rand() % 100 < 25) ? 1 : 0; 
        }
    }
}

// Funcion para contar cuantos vecinos tiene cada cuadrito
int calcular_vecinos_vivos(const vector<vector<int>>& tablero, int fila, int columna, int tamano) {
    int contador = 0;
    // Use dos bucles 'for' que revisan el area de 3x3 alrededor de la celula.
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Me salto la celula actual

            int fV = fila + i;
            int cV = columna + j;

            // Este 'if' lo puse para que el programa no de error al revisar 
            // celdas que estan en las esquinas o bordes del mapa.
            if (fV >= 0 && fV < tamano && cV >= 0 && cV < tamano) {
                if (tablero[fV][cV] == 1) contador++;
            }
        }
    }
    return contador;
}

// Aqui aplico las reglas de Conway
void actualizar_tablero(vector<vector<int>>& tablero, int tamano) {
    // Tuve que crear una matriz 'proximaGen'. 
    // No sabia esto, pero si cambio el tablero mientras cuento vecinos, 
    // la logica falla porque estaria usando datos de la generacion nueva antes de tiempo.
    vector<vector<int>> proximaGen = tablero;

    for (int f = 0; f < tamano; f++) {
        for (int c = 0; c < tamano; c++) {
            int vecinos = calcular_vecinos_vivos(tablero, f, c, tamano);

            if (tablero[f][c] == 1) {
                // Regla de muerte por soledad o amontonamiento
                if (vecinos < MIN_VIVA || vecinos > MAX_VIVA) {
                    proximaGen[f][c] = 0;
                }
            } else {
                // Regla de nacimiento por tener 3 vecinos exactos
                if (vecinos == NACIMIENTO) {
                    proximaGen[f][c] = 1;
                }
            }
        }
    }
    // Al final paso todos los cambios que guarde en la copia al tablero real
    tablero = proximaGen;
}

// La parte visual del juego
void imprimir_tablero(const vector<vector<int>>& tablero, int tamano) {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (tablero[i][j] == 1) {
                // Use el char 219 (un bloque solido) dos veces. 
                // Lo hice porque la terminal es mas alta que ancha, 
                // asi que con dos bloques se ve mas como un cuadrado real.
                cout << (char)219 << (char)219; 
            } else {
                // Dos espacios para mantener la simetria con las celdas vivas
                cout << "  "; 
            }
        }
        cout << "\n";
    }
}