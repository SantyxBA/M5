#include <iostream>
using namespace std;
//Variables de uso

int picas[13];
int diamantes[13];
int treboles[13];
int corazones[13];
bool gameOver = false;
int indiceCarta = 0;


//Variables Jugador 1
string player1 = "Jack";
int pointsPlayer1 = 0;
bool surrender1 = false;
bool winnerP1 = false;
bool loserP1 = false;
int ASvalueplayer;

//Variables Jugador 2
string player2 = "Croupiere";
int pointsPlayer2 = 0;
bool surrender2 = false;
bool winnerP2 = false;
bool loserP2 = false;
int ASvaluecroupiere;



//Funciones

//Inicializa cualquier array con sus 12 posiciones a 1
//de esta forma, indicamos que todas las cartas están disponibles
//si una posición está a 0, esa carta ya está repartida y no se repite

void inicializaArray(int(&pArray)[13]) {

    /* 0 1 2 3 4 5 6 7 8 9 10 11 12
       1 2 3 4 5 6 7 8 9 10 10 10 10 */

    for (int i = 0; i < 13; i++) {
        pArray[i] = 1;
    }
}

//Comprueba aleatoriamente si ha de dar picas,diamantes, treboles o corazones
//y busca una carta al azar. Hasta que no encuentre una posición
// a 1, no asigna esa carta, cuyo valor es el indiceCarta + 1

void chooseCards(int& totalPoints, string player) {
    bool choosed = false;
    int indiceCarta = 0;
    string tipoPalo;
    while (!choosed) {
        //Elije una carta del 1 al 13
        indiceCarta = rand() % 13;

        //Comprueba las Picas

        if ((rand() % 2) == 0) {
            if (picas[indiceCarta] == 1) {
                //devuelve la carta
                picas[indiceCarta] = 0;
                choosed = true;
                tipoPalo = "picas";
            }
        }
        //Comprueba los diamantes
        if ((rand() % 2) == 0) {
            if (diamantes[indiceCarta] == 1) {
                //devuelve la carta
                diamantes[indiceCarta] = 0;
                choosed = true;
                tipoPalo = "diamantes";
            }
        }
        //Comprueba los treboles
        if ((rand() % 2) == 0) {
            if (treboles[indiceCarta] == 1) {
                //devuelve la carta
                treboles[indiceCarta] = 0;
                choosed = true;
                tipoPalo = "treboles";
            }
        }

        //Comprueba los corazones
        if ((rand() % 2) == 0) {
            if (corazones[indiceCarta] == 1) {
                //devuelve la carta
                corazones[indiceCarta] = 0;
                choosed = true;
                tipoPalo = "corazones";
            }
        }


    }
    totalPoints += indiceCarta + 1;
    cout << "El jugador " << player << " ha sacado un " << indiceCarta + 1 << " de " << tipoPalo << " y tiene un total de " << totalPoints << endl;
}


void checkASvaluePlayer() {






}



void checkASvalueCroupiere() {








}


bool checkPoints(int& points, bool& winner, bool& loser) {
    if (points == 21) {
        winner = true;
        return true;
    }
    else if (points > 21) {
        loser = true;
        return true;
    }
    return false;
}

bool checkWhoWins(int points1, int points2, bool& winner2) {
    if (points2 > points1) {
        winner2 = true;
        return true;
    }
    else {
        return false;
    }
}
int main()
{
    inicializaArray(picas);
    inicializaArray(diamantes);
    inicializaArray(treboles);
    inicializaArray(corazones);

   srand(time(NULL));
    //primer reparto de cartas
    chooseCards(pointsPlayer1, player1);
    /*sleep(10);*/
    chooseCards(pointsPlayer1, player1);
    /* sleep(10); */
     //Puede pasar que ganemos o perdamos nada más comenzar
    surrender1 = checkPoints(pointsPlayer1, winnerP1, loserP1);
    /* sleep(10); */
    chooseCards(pointsPlayer2, player2);
    /*  sleep(10);*/
    while (!surrender1) {
        int choice = 0;
        //Comienza el juego con el jugador 1
        while (choice != 1 && choice != 2) {
            cout << "Tienes " << pointsPlayer1 << ".Quieres pedir carta?" << endl;
            cout << "1.- Si" << endl;
            cout << "2.- No" << endl;
            cin >> choice;
            if (choice != 1 && choice != 2) {
                cout << "Por favor, elije una opción válida." << endl;
            }
        }
        if (choice == 1) {
            chooseCards(pointsPlayer1, player1);
            surrender1 = checkPoints(pointsPlayer1, winnerP1, loserP1);
            //comprueba si se ha pasado o ha ganado la partida
        }
        else {
            //Si no quiere carta, es turno de la banca
            surrender1 = true;
        }
    }
    //Termina el turno del jugador 1. Hay que comprobar si ha ganado (winnerP1) o perdido ya (loserP1), o si la banca tiene que tirar
    if (winnerP1) {
        cout << "El jugador " << player1 << " gana y la banca pierde " << endl;
    }
    else if (loserP1) {
        cout << "El jugador " << player1 << " pierde y la banca gana " << endl;
    }
    else {
        //turno de la banca
        while (!surrender2) {
            chooseCards(pointsPlayer2, player2);
            /* sleep(10);*/
            surrender2 = checkPoints(pointsPlayer2, winnerP2, loserP2);
            if (!surrender2) {
                //Comprueba si la banca ya gana por puntos
                surrender2 = checkWhoWins(pointsPlayer1, pointsPlayer2, winnerP2);
            }
        }
        if (winnerP2) {
            cout << " La banca gana y el jugador " << player1 << " pierde " << endl;
        }
        else if (loserP2) {
            cout << " La banca pierde y el jugador " << player1 << " gana " << endl;
        }
    }

}
