#include <cstdlib>
#include <iostream>

#include "../capa-negocio/Juego.cpp"

using namespace std;

// Identify OS
#ifdef _WIN32
#define OS "Windows"
#elif __linux__
#define OS "Linux"
#endif

void clearScreen() {
  if ((std::string)OS == "Linux") {
    system("clear");
  } else {
    system("cls");
  }
}

void waitForInput() {
    cin.ignore();
    cin.get(); 
}


void menuInicio();
void GameLoop(Juego partida);
void dibujarTablero();

int main() {

    clearScreen();
    menuInicio();

}

void menuInicio() {
    Juego partida;

    int opcion;

    do {
        cout << "1. Nueva partida" << endl;
        cout << "2. Cargar partida" << endl;
        cout << "3. Historial" << endl;
        cout << "4. Salir" << endl;

        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            partida.nuevaPartida();
            GameLoop(partida);

            break;
        case 2:
            // Codigo para cargar partida
            break;
        case 3:
            // Codigo para mostrar historial
            break;
        case 4:
            // Salir del programa
            break;
        default:

            cout << "Opcion invalida" << endl;
        }

    } while (opcion != 4);

}

void dibujarTablero(Juego partida) {
    clearScreen();
    partida.dibujarTablero();

}

void GameLoop(Juego partida) {

     int opcion;

    while (true) {
        dibujarTablero(partida);

        cout << "\n\nQue hacer?"<<endl;
        cout << "1.Elegir Celda\t2.Guardar Y Salir" << endl;
        cout << "\n>>>";
        cin >> opcion;


        if (opcion == 1) { // Elegir Celda

            int fila=-1, columna=-1;

            cout << "inserte numero de fila: ";
            cin >> fila;
            cout << "inserte numero de columna: ";
            cin >> columna;

            string verificacionCoords = partida.verificarCoordenadas(fila, columna); 
            if ( verificacionCoords != "") {
                cout << "\n" << verificacionCoords;
                waitForInput();
                continue;
            }

            while (opcion != -1) {

            printf("Accion a tomar en (%d,%d):\n", fila, columna);
            cout << "1.Revelar Celda\t2.Marcar Celda\t3.Nada"<< endl;
            cout << ">>> ";
            cin >> opcion;

            switch (opcion) {

            case 1: {
                partida.revelarCelda(fila, columna);
                opcion = -1;
                break;
            }

            case 2: {

                partida.marcarCelda(fila, columna);
                cout << "Marcado Hecho con exito" << endl;
                waitForInput();
                opcion = -1; //salir
                break;
            }

            case 3: {
                opcion = -1;
                break;

            }

            default:
                cout << "Opcion invalida" << endl;
                break; 
            }
 
            }



        } else if (opcion == 2) {
            // codigo para guardar y salir
        } else {
            cout << "Opcion invalida" << endl;
            waitForInput();

        }
    }

}