#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

// Domyślny konstruktor
Board::Board() : size(10), grid(size, vector<char>(size, '~')) {}

// Konstruktor z określonym rozmiarem planszy
Board::Board(int size) : size(size), grid(size, vector<char>(size, '~')) {
    if (size < 1) {
        this->size = BOARD_SIZE; // Ustawienie domyślnego rozmiaru
        grid.resize(this->size, vector<char>(this->size, '~'));
    }
}

// Metoda do dodawania statku na planszy
bool Board::addShip(int x, int y, int length, bool horizontal) {
    if (horizontal) { // Ustawienie statku poziomo
        // Sprawdzenie, czy statek mieści się na planszy
        if (x < 0 || x >= size || y < 0 || y >= size || x + length > size) {
            cout << "Statek nie miesci sie w granicach planszy!" << endl;
            return false;
        }

        // Sprawdzenie, czy pole jest już zajęte
        for (int i = 0; i < length; i++) {
            if (grid[y][x + i] != '~') {
                cout << "Pole (" << x + i << ", " << y << ") jest juz zajete!" << endl;
                return false;
            }
        }

        // Umieszczenie statku na planszy
        for (int i = 0; i < length; i++) {
            grid[y][x + i] = 'S'; // Oznaczenie pola statkiem
        }
    } else { // Ustawienie statku pionowo
        // Sprawdzenie, czy statek mieści się na planszy
        if (x < 0 || x >= size || y < 0 || y >= size || y + length - 1 >= size) {
            cout << "Statek nie miesci sie w granicach planszy!" << endl;
            return false;
        }

        // Sprawdzenie, czy pole jest już zajęte
        for (int i = 0; i < length; i++) {
            if (grid[y + i][x] != '~') {
                cout << "Pole (" << x << ", " << y + i << ") jest juz zajete!" << endl;
                return false;
            }
        }

        // Umieszczenie statku na planszy
        for (int i = 0; i < length; i++) {
            grid[y + i][x] = 'S'; // Oznaczenie pola statkiem
        }
    }
    return true; // Statek został pomyślnie umieszczony
}

// Metoda sprawdzająca, czy dane pole jest zajęte
bool Board::isOccupied(int x, int y) const {
    return grid[y][x] != '~'; // Jeśli pole jest inne niż '~', oznacza to, że jest zajęte
}

// Oznaczenie trafienia na planszy
void Board::markHit(int x, int y) {
    if (grid[y][x] == 'S') {
        grid[y][x] = 'X'; // Oznaczenie trafienia
    }
}


// Pobranie wartości z pola na planszy
char Board::getCell(int x, int y) const {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        throw out_of_range("Wspołrzedne poza zakresem planszy");
    }
    return grid[y][x];
}

// Ustawienie wartości w danym polu
void Board::setCell(int x, int y, char value) {
    grid[y][x] = value; // Ustawienie wartości w danym polu
}

bool Board::sunkedShip(int i, int j)
{
    for(int k = i; k >=0; k--)
    {
        if(grid[k][j] == 'S')
        {
            return false;
        }
        if(grid[k][j] == '~')
        {
            break;
        }
    }

    for(int k = i; k < grid.size(); k++)
    {
        if(grid[k][j] == 'S')
        {
            return false;
        }
        if(grid[k][j] == '~')
        {
            break;
        }
    }

    for(int k = j; k >=0; k--)
    {
        if(grid[i][k] == 'S')
        {
            return false;
        }
        if(grid[i][k] == '~')
        {
            break;
        }
    }

    for(int k = j; k < grid[0].size(); k++)
    {
        if(grid[i][k] == 'S')
        {
            return false;
        }
        if(grid[i][k] == '~')
        {
            break;
        }
    }
    return true;
}

// Oznaczenie pól wokół trafionych statków (po trafieniu)
void Board::markSunkShipsWithO(Board * opponentBoard) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
        if (grid[i][j] == 'X') { // Trafienie statku
            if(opponentBoard->sunkedShip(i,j))
            {
                // Sprawdzamy sąsiednie pola
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int ni = i + dx;
                        int nj = j + dy;

                        // Sprawdzamy, czy sąsiednie pole jest w granicach planszy
                        if (ni >= 0 && ni < size && nj >= 0 && nj < size) {
                            // Jeśli sąsiednie pole jest puste, oznaczamy je 'O'
                            if (grid[ni][nj] == '~') {
                                grid[ni][nj] = 'O';
                            }
                        }
                    }
                }
            }
        }   
    }
}
}

// Wykonanie strzału na planszy
char Board::shoot(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        cout << "Strzal poza granicami planszy!" << endl;
        return false; // Poza granicami planszy
    }

    if (grid[y][x] == 'S') {
        grid[y][x] = 'X'; // Oznaczenie trafienia
        cout << "Trafienie!" << endl;
        return 'X'; // Trafienie
    } else if (grid[y][x] == '~') {
        grid[y][x] = 'O'; // Oznaczenie pudła
        cout << "Pudlo!" << endl;
        return 'O'; // Pudło
    } else {
        cout << "Juz strzelano w to miejsce!" << endl;
        return grid[y][x]; // Już strzelano
    }
}

// Wyświetlanie statków na planszy
void Board::displayShots() const {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "  "; // Pusta przestrzeń w lewym górnym rogu
            for (char c = 'A'; c < 'A' + size; c++) {
                cout << c << " "; // Wyświetlanie liter A-J
            }
            cout << endl;
        }
        cout << i + 1 << " "; // Wyświetlanie numeru wiersza
        for (int j = 0; j < size; j++) {
            // Wyświetlaj tylko strzały
            if (grid[i][j] == 'X' || grid[i][j] == 'O') {
                cout << grid[i][j] << " "; // Trafienie lub pudło
            } else {
                cout << "~ "; // Puste pole, nie wyświetlamy statków
            }
        }
        cout << endl; // Nowa linia po każdym wierszu
    }
}

void Board::displayShips() const {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "  "; // Pusta przestrzeń w lewym górnym rogu
            for (char c = 'A'; c < 'A' + size; c++) {
                cout << c << " "; // Wyświetlanie liter A-J
            }
            cout << endl;
        }
        cout << i + 1 << " "; // Wyświetlanie numeru wiersza
        for (int j = 0; j < size; j++) {
            // Wyświetlaj tylko statki lub puste pole
            if (grid[i][j] == 'S') {
                cout << "S "; // Statek
            } else {
                cout << "~ "; // Puste pole
            }
        }
        cout << endl; // Nowa linia po każdym wierszu
    }
}



// Wyświetlanie całej planszy z współrzędnymi
void Board::display() const {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "   "; // Pusta przestrzeń w lewym górnym rogu
            for (char c = 'A'; c < 'A' + size; c++) {
                cout << c << " "; // Wyświetlanie liter A-J
            }
            cout << endl;
        }
        if(i < 9)
        {
            cout << i + 1 << "  "; // Wyświetlanie numeru wiersza
        }
        else{
            cout << i + 1 << " "; // Wyświetlanie numeru wiersza
        }
        for (int j = 0; j < size; j++) {
            cout << grid[i][j] << " "; // Wyświetlanie zawartości planszy
        }
        cout << endl; // Nowa linia po każdym wierszu
    }
}

// Sprawdzenie, czy wszystkie statki zostały zatopione
bool Board::allShipsSunk() const {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid[row][col] == 'S') {
                return false; // Znaleziono statek, więc nie wszystkie są zatopione
            }
        }
    }
    return true; // Wszystkie statki są zatopione
}

// Sprawdzenie, czy można umieścić statek na planszy
bool Board::canPlaceShip(int x, int y, int length, bool horizontal) const {
    // Sprawdzenie, czy statek mieści się na planszy
    if (horizontal) {
        if (x < 0 || y < 0 || y >= size || x + length > size) {
            return false; // Statek wychodzi poza planszę
        }
        for (int i = 0; i < length; i++) {
            if (grid[y][x + i] != '~') {
                return false; // Pole jest zajęte
            }
        }
        // Sprawdzenie sąsiednich pól dla ustawienia poziomego
        for (int i = -1; i <= length; i++) {
            // Górne sąsiednie pola
            if (y > 0 && (x + i >= 0 && x + i < size) && grid[y - 1][x + i] != '~') {
                return false;
            }
            // Dolne sąsiednie pola
            if (y < size - 1 && (x + i >= 0 && x + i < size) && grid[y + 1][x + i] != '~') {
                return false;
            }
        }
        // Lewa i prawa strona
        if (x > 0 && grid[y][x - 1] != '~') {
            return false;
        }
        if (x + length < size && grid[y][x + length] != '~') {
            return false;
        }
    } else { // Sprawdzenie dla ustawienia pionowego
        if (x < 0 || y < 0 || y + length > size) {
            return false; // Statek wychodzi poza planszę
        }
        for (int i = 0; i < length; i++) {
            if (grid[y + i][x] != '~') {
                return false; // Pole jest zajęte
            }
        }
        // Sprawdzenie sąsiednich pól dla ustawienia pionowego
        for (int i = -1; i <= length; i++) {
            // Lewa strona, tylko w granicach planszy
            if (x > 0 && (y + i >= 0 && y + i < size) && grid[y + i][x - 1] != '~') {
                return false;
            }
            // Prawa strona, tylko w granicach planszy
            if (x < size - 1 && (y + i >= 0 && y + i < size) && grid[y + i][x + 1] != '~') {
                return false;
            }
        }
        // Górne sąsiednie pole
        if (y > 0 && grid[y - 1][x] != '~') {
            return false;
        }
        // Dolne sąsiednie pole
        if (y + length < size && grid[y + length][x] != '~') {
            return false;
        }
    }
    return true; // Można umieścić statek
}
