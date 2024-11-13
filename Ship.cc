#include "Ship.h"
#include<iostream>

using namespace std;

// Definicja konstruktora
Ship::Ship(int x, int y, int length, bool horizontal)
    : x(x), y(y), length(length), horizontal(horizontal), hits(length, false) { // Inicjalizacja wektora hits
    //TO DO: 
    /*for( int i = 0; i< segments.size(); i++)
    {
        if(segments[i])
        {
            cout << i << " = true\n";
        }
        else{
            cout << i << " = false\n";
        }
    }
    cin >> x;*/

}

// Definicje metod
int Ship::getX() const {
    return x;
}

int Ship::getY() const {
    return y;
}

int Ship::getLength() const {
    return length;
}

bool Ship::isHorizontal() const {
    return horizontal;
}

bool Ship::hit(int position) {
    if (position >= 0 && position < length) {
        return hits[position];
    }
    return false; // Pozycja poza zakresem
}

int Ship::getHitCount() const
{
    int count = 0;
    for (bool hit : hits) {
        if (hit) {
            count++;
        }
    }
    return count;
}

string Ship::getStatus() const
{
    string status = "Statek na pozycji (" + to_string(x) + ", " + to_string(y) + "): ";
    for (int i = 0; i < length; i++) {
        status += hits[i] ? "X" : "O"; // X - trafiony, O - nietrafiony
    }
    return status;
}

