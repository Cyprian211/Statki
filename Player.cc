#include "Player.h"
#include <iostream>
#include "Board.h"

using namespace std;

Player::Player(const string& name) : name(name), ships() {
    ownBoard = new Board;       // Plansza gracza (na której umieszczane są statki)
    shotBoard = new Board;      // Plansza strzałów (wyniki ataków) 
    // Inicjalizacja statków
    ships.push_back(Ship(0, 0, 1, true));  // 1-masztowiec
    ships.push_back(Ship(1, 0, 1, true));  // 1-masztowiec
    ships.push_back(Ship(2, 0, 1, true));  // 1-masztowiec
    ships.push_back(Ship(3, 0, 1, true));  // 1-masztowiec
    ships.push_back(Ship(0, 1, 2, true));  // 2-masztowiec
    ships.push_back(Ship(0, 2, 2, true));  // 2-masztowiec
    ships.push_back(Ship(0, 3, 2, true));  // 2-masztowiec
    ships.push_back(Ship(0, 4, 3, true));  // 3-masztowiec
    ships.push_back(Ship(0, 5, 3, true));  // 3-masztowiec
    ships.push_back(Ship(0, 6, 4, true));  // 4-masztowiec
}



void Player::placeShips(Player& opponent) {
    cout << "Umiesc statki dla " << name << endl;

    // Definiowanie liczby statków
    const int oneMastCount = 4;
    const int twoMastCount = 3;
    const int threeMastCount = 2;
    const int fourMastCount = 1;

    // Umieszczanie statków
    for (int i = 0; i < oneMastCount; i++) {
        cout << "Umiesc 1-masztowiec " << endl;
        placeShip(1, opponent);
    }
    for (int i = 0; i < twoMastCount; i++) {
        cout << "Umiesc 2-masztowiec " << endl;
        placeShip(2, opponent);
    }
    for (int i = 0; i < threeMastCount; i++) {
        cout << "Umiesc 3-masztowiec " << endl;
        placeShip(3, opponent);
    }
    for (int i = 0; i < fourMastCount; i++) {
        cout << "Umiesc 4-masztowiec " << endl;
        placeShip(4, opponent);
    }
}


void Player::displayBoardWithCoordinates() const {
    cout << "\n--- " << name << " - Twoja plansza ---\n";
    ownBoard->display();

    cout << "\n--- " << name << " - Plansza strzalow na przeciwnika ---\n";
    shotBoard->display(); 
}

void Player::updateShotBoard(int x, int y, bool hit) {
    shotBoard->setCell(x, y, hit ? 'X' : 'O');  // 'X' dla trafienia, 'O' dla pudła
}

void Player::placeShip(int length, Player& opponent) {
    char direction = 'H';  // Domyślny kierunek dla jednomasztowca
    int x, y;

    if (length == 1) {
    } else {
        // Pytanie o kierunek dla statków dłuższych niż 1
        while (true) {
            cout << "Podaj kierunek (H-poziomo/V-pionowo): ";
            cin >> direction;
            direction = toupper(direction);  // Konwersja na wielką literę

            // Walidacja kierunku
            if (direction != 'H' && direction != 'V') {
                cout << "Kierunek musi być H (poziomo) lub V (pionowo). Spróbuj ponownie." << endl;
                continue;
            }
            break;  // Wyjście z pętli, jeśli kierunek jest poprawny
        }
    }

    while (true) {
        string input;
        cout << "Podaj wspolrzedne (np. A5): ";
        cin >> input;

        // Walidacja współrzędnych
        if (input.length() < 2 || input.length() > 3) {
            cout << "Niepoprawny format wspolrzednych. Sprobuj ponownie." << endl;
            continue;  // Powrót do początku pętli
        }

        // Konwersja współrzędnych
        x = toupper(input[0]) - 'A';  // Konwersja litery na indeks
        if(input[1] == '0')
        {
            cout << "Nie mozesz zaznaczyc tego pola!" << endl;
            continue;
        }

        if(input[1] < '0' || input[1] > 9)
        {
            cout << "To nie jest liczba!" << endl;
            continue;
        }

        if(input.size() == 3)
        {
            if(input[2] < '0' || input[1] > 9)
            {
                cout << "To nie jest liczba!" << endl;
                continue;
            }
        }

        y = stoi(input.substr(1)) - 1;  // Konwersja liczby na indeks

        // Sprawdzenie, czy współrzędne są w odpowiednim zakresie
        if (x < 0 || x >= Board::BOARD_SIZE || y < 0 || y >= Board::BOARD_SIZE) {
            cout << "Wspolrzedne musza byc w zakresie A1 do J10. Sprobuj ponownie." << endl;
            continue;  // Powrót do początku pętli
        }

        // Sprawdzenie, czy statek może być umieszczony
        bool canPlace = ownBoard->canPlaceShip(x, y, length, direction == 'H');
        if (canPlace) {
            ownBoard->addShip(x, y, length, direction == 'H');
            cout << "Statek ustawiony pomyslnie!" << endl;
            displayBoardWithCoordinates();  // Wyświetlenie obu plansz
            break;  // Wyjście z pętli po udanym umieszczeniu statku
        } else {
            cout << "Nie mozna umiescic statku w tej lokalizacji! Sprobuj ponownie." << endl;
            displayBoardWithCoordinates();  // Wyświetlenie obu plansz po nieudanej próbie
        }
    }
}

Board& Player::getOwnBoard() {
    return *ownBoard;
}


bool Player::attack(int x, int y, Player& opponent) {
    // Wykonanie strzału na planszy przeciwnika (ownBoard przeciwnika)
    char hit = opponent.ownBoard->shoot(x, y);
    

    // Aktualizacja targetBoard na podstawie wyniku strzału
    shotBoard->setCell(x, y, hit);  // 'X' oznacza trafienie, 'O' oznacza pudło

    return hit == 'X';  // Zwracamy 'hit' - true dla trafienia, false dla pudła
}

bool Player::takeTurn(Player& opponent) {
    int x, y;
    bool validShot = false;
    bool hit = false;

    while (!validShot) {
        string input;
        cout << getName() << ", podaj wspolrzedne ataku (np. A5): ";
        cin >> input;

        // Sprawdzenie długości inputu
        if (input.length() < 2 || input.length() > 3) {
            cout << "Niepoprawny format wspolrzednych! Uzyj formatu A1 do J10." << endl;
            continue;
        }

        // Zamiana pierwszego znaku na indeks kolumny (A -> 0, B -> 1, itd.)
        x = toupper(input[0]) - 'A';

        // Sprawdzamy, czy pozostałe znaki są cyframi, czyli liczbą
        string rowPart = input.substr(1);
        bool isNumber = true;
        for (unsigned int i = 0; i < rowPart.length(); i++) 
        {
            if (!isdigit(rowPart[i])) 
            {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Niepoprawny format liczby w wierszu! Uzyj cyfr od 1 do 10." << endl;
            continue;
        }

        // Konwersja numeru wiersza i przestawienie go na indeks od zera
        y = stoi(rowPart) - 1;

        // Sprawdzanie, czy współrzędne mieszczą się w zakresie
        if (x < 0 || x >= Board::BOARD_SIZE || y < 0 || y >= Board::BOARD_SIZE) {
            cout << "Wspolrzedne musza byc w zakresie A1 do J10. Sprobuj ponownie." << endl;
            continue;
        }

        char currentCell = shotBoard->getCell(x, y);
        if (currentCell == 'X' || currentCell == 'O') {
            cout << "Juz strzelano w to miejsce! Wybierz inne wspolrzedne." << endl;
            continue;  // Strzał nie został wykonany, gracz musi wybrać inne pole
        }

        // Wykonanie ataku i oznaczenie strzału jako ważny
        //!!!!!!!!!!!!Poprawić działanie funkcji
        hit = attack(x, y, opponent);
        validShot = true;
    }

    if (hit) {
        // Jeśli statek został zatopiony, otaczamy go "O" na planszy przeciwnika
        shotBoard->markSunkShipsWithO(opponent.ownBoard);
    }

    return hit;  // Zwraca true, jeśli trafiono, false jeśli było pudło
}

Player::~Player()
{
    delete ownBoard;      
    delete shotBoard;  
}

bool Player::allShipsSunk() const {
    return ownBoard->allShipsSunk();  // Sprawdzenie, czy wszystkie statki zostały zestrzelone
}

string Player::getName() const
{
    return name; 
}
