#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Ship.h"

using namespace std;

class Board {
public:
    // Stała rozmiaru planszy
    static const int BOARD_SIZE = 10;

    // Konstruktorzy
    Board();                                                    // Domyślny konstruktor
    Board(int size);                                                // Konstruktor z określonym rozmiarem

    // Metody do zarządzania statkami
    bool addShip(int x, int y, int length, bool horizontal);    // Dodanie statku na planszy
    bool canPlaceShip(int x, int y, int length, bool horizontal) const; // Sprawdzenie, czy statek może być umieszczony
    bool allShipsSunk() const;                                    // Sprawdzenie, czy wszystkie statki zostały zatopione

    // Metody do atakowania
    char shoot(int x, int y);                                    // Wykonanie strzału

    // Metody do wyświetlania planszy
    void displayShips() const;                                    // Wyświetlenie statków
    void displayShots() const;                                    // Wyświetlenie trafień i pudłów
    void display() const;                                         // Wyświetlenie całej planszy

    // Metody do zarządzania stanem planszy
    bool isOccupied(int x, int y) const;                          // Sprawdzenie, czy pole jest zajęte
    void markHit(int x, int y);                                   // Oznaczenie trafienia
    char getCell(int x, int y) const;                             // Pobranie wartości z pola
    void setCell(int x, int y, char value);                       // Ustawienie wartości w polu
    bool sunkedShip(int i, int j);

    // Metody pomocnicze
    void markSunkShipsWithO(Board * opponentBoard);                                    // Oznaczenie zatopionych statków na planszy

private:
    int size;                          // Rozmiar planszy
    vector<vector<char>> grid;         // Plansza reprezentowana jako siatka znaków
    vector<Ship> ships;                // Lista statków na planszy
};

#endif // BOARD_H
