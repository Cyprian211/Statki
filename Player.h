#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Board.h"
#include "Ship.h" 

using namespace std;

class Player {
public:
    // Stałe
    static const int BOARD_SIZE = 10;  // Rozmiar planszy
    static const int NUM_SHIPS = 5;    // Liczba statków do umieszczenia

    // Konstruktor
    Player(const string& name);
    
    ~Player();
    // Publiczne metody
    bool takeTurn(Player& opponent);                // Wykonanie tury (atak na przeciwnika)
    bool allShipsSunk() const;                      // Sprawdzenie, czy wszystkie statki gracza zostały zatopione
    string getName() const;                         // Zwrócenie nazwy gracza
    bool attack(int x, int y, Player& opponent);    // Atak na planszę przeciwnika       
    void placeShips(Player& opponent);              // Ustawianie wszystkich statków
    void placeRandomShips();                        // Automatyczne ustawienie statków
    void displayBoardWithCoordinates() const;  // Wyświetlanie planszy z koordynatami
    void placeShip(int length, Player& opponent);   // Umieszczanie pojedynczego statku na planszy

    // Publiczne pola
    Board* ownBoard = nullptr;       // Plansza gracza (na której umieszczane są statki)
    Board* shotBoard = nullptr;      // Plansza strzałów (wyniki ataków)
    Board& getOwnBoard(); // Zwracanie referencji do własnej planszy


private:
    // Prywatne pola
    string name;            // Nazwa gracza
    vector<Ship> ships;     // Lista statków gracza

    // Prywatne metody
    void updateShotBoard(int x, int y, bool hit);  // Zaktualizowanie planszy strzałów (trafienie/pudło)
};

#endif // PLAYER_H
