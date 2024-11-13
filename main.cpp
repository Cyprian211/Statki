#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"

using namespace std;

// Funkcja do czyszczenia konsoli
void clearConsole() {
    this_thread::sleep_for(chrono::seconds(2));
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    string player1Name, player2Name;

    // Wprowadzenie imion graczy
    cout << "Podaj imie gracza 1: ";
    cin >> player1Name;
    cout << "Podaj imie gracza 2: ";
    cin >> player2Name;

    // Liczniki wygranych
    int player1Wins = 0;
    int player2Wins = 0;

    // Pętla do powtarzania gry
    while (true) {
        Player player1(player1Name);
        Player player2(player2Name);

        // Rozpoczęcie gry
        Player* currentPlayer = &player1;
        Player* opponentPlayer = &player2;

        // Alias dla wygodniejszego dostępu do plansz aktualnego i przeciwnika
        Board* currentOwnBoard = currentPlayer->ownBoard;
        Board* opponentShotBoard = opponentPlayer->shotBoard;

        Board* currentShotBoard = currentPlayer->shotBoard;
        Board* opponentPlayerShotBoard = opponentPlayer->shotBoard;

        // Ustawianie statków dla gracza 1
        clearConsole();
        currentPlayer->displayBoardWithCoordinates();
        player1.placeShips(player2);

        // Ustawianie statków dla gracza 2
        clearConsole();
        currentPlayer->displayBoardWithCoordinates();
        player2.placeShips(player1); 

        while (true) {
            clearConsole(); // Czyść konsolę przed każdym ruchem

            // Wyświetlenie plansz: własnej i przeciwnika
            currentPlayer->displayBoardWithCoordinates();

            // Wykonanie tury przez aktualnego gracza, strzelając do przeciwnika
            bool hit = currentPlayer->takeTurn(*opponentPlayer);

            // Sprawdzenie, czy wszystkie statki przeciwnika zostały zestrzelone
            if (opponentPlayer->allShipsSunk()) {
                cout << currentPlayer->getName() << " wygral!" << endl;

                // Aktualizacja liczników wygranych
                if (currentPlayer == &player1) {
                    player1Wins++;
                } else {
                    player2Wins++;
                }
                break; // Zakończenie gry
            }

            // Jeśli strzał był pudłem, zmień gracza
            if (!hit) {
                cout << "Pudlo! Przekazanie kolejki do następnego gracza..." << endl;
                clearConsole();
                swap(currentPlayer, opponentPlayer);

                // Aktualizacja aliasów plansz
                currentOwnBoard = currentPlayer->ownBoard;
                currentShotBoard = currentPlayer->shotBoard;
            }
        }

        // Wyświetlenie aktualnych wyników
        cout << "Aktualne wyniki:\n";
        cout << player1.getName() << ": " << player1Wins << " wygranych\n";
        cout << player2.getName() << ": " << player2Wins << " wygranych\n";

        // Zapytanie graczy, czy chcą zagrać ponownie
        char playAgain;
        cout << "Czy chcesz zagrac ponownie? (t/n): ";
        cin >> playAgain;

        if (tolower(playAgain) != 't') {
            break; // Zakończenie pętli, jeśli gracze nie chcą grać ponownie
        }
    }

    return 0;
}
