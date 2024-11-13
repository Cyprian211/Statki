#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>

using namespace std;

class Ship {
public:
    // Konstruktor
    Ship(int x, int y, int length, bool horizontal);

    // Metody publiczne
    int getX() const;               // Zwraca współrzędną X początkową statku
    int getY() const;               // Zwraca współrzędną Y początkową statku
    int getLength() const;          // Zwraca długość statku
    bool isHorizontal() const;      // Sprawdza, czy statek jest ustawiony poziomo
    bool hit(int position);         // Znak trafienia na określonej pozycji
    int getHitCount() const;        // Zwraca liczbę trafionych segmentów statku
    string getStatus() const;       // Zwraca status statku (np. czy zatopiony)

private:
    int x, y;                       // Współrzędne początkowe statku
    int length;                     // Długość statku
    bool horizontal;                // Orientacja statku (poziomy czy pionowy)
    vector<bool> hits;              // Przechowuje informacje o trafieniach w poszczególnych segmentach
};

#endif // SHIP_H
