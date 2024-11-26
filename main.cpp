// Tomasz Ciurkowski 203191 Elektronika i telekomunikacja Gra a la Kono (na motywach koreańskiej gry Kono)
#include <iostream>

using namespace std;

struct Ruch
{
    int startkol;
    int startrow;
    int endkol;
    int endrow;
};

void Starter(char gracz1[], char gracz2[])
{
    cout << "wprowadz imie gracza 1 (pionki czarne): ";
    cin >> gracz1;
    cout << endl;

    cout << "wprowadz ime gracza 2 (pionki biale): ";
    cin >> gracz2;
    cout << endl;

}

void wyswietlplan(char plansza[4][4], char gracz1[], char gracz2[]) //funkcja rysująca plansze
{
    int row = 4;
    cout << gracz1 << " (b)" << endl;
    cout << " \xc9\xcd\xcd\xcd\xcb\xcd\xcd\xcd\xcb\xcd\xcd\xcd\xcb\xcd\xcd\xcd\xbb" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << row << "\xba";
        for (int j = 0; j < 4; j++)
        {
            cout << " " << plansza[i][j] << " \xba";
        }
        cout << endl;
        if  (i==0 || i==1 || i==2)
        {
            cout << " \xcc\xcd\xcd\xcd\xce\xcd\xcd\xcd\xce\xcd\xcd\xcd\xce\xcd\xcd\xcd\xb9"<< endl;
        }
        row--;
    }
    cout << " \xc8\xcd\xcd\xcd\xca\xcd\xcd\xcd\xca\xcd\xcd\xcd\xca\xcd\xcd\xcd\xbc" << endl;
    cout << "   A   B   C   D"<< endl;
    cout << gracz2 << " (c)"<< endl;
}

Ruch zamieninput(char ruch[])
{
    Ruch rch;
    rch.startkol = toupper(ruch[0]) - 'A';
    rch.startrow = 4 - (ruch[1] - '0') ;
    rch.endkol = toupper(ruch[3]) - 'A';
    rch.endrow = 4 - (ruch[4] - '0') ;
    return rch;
}

bool czypoprawnedane(char ruch[]) //funkcja sprawdzająca poprawność wprowadzanych danych 
{
    int i = 0;
    while (ruch[i] != '\0') i++;  // sprawdzanie długości wprowadzonego ciagu znaków
    if (i != 5 || ruch[2] != '-') {
        cout << "Nieprawidlowy format." << endl;
        return false;
    }

    char skol = ruch[0]; 
    int srow = ruch[1] - '0'; 
    char ekol = ruch[3];
    int erow = ruch[4] - '0';

    skol = toupper(skol);
    ekol = toupper(ekol);

    if (skol < 'A' || skol > 'D' || ekol < 'A' || ekol > 'D') {
        cout << "Nieprawidlowa kolumna." << endl;
        return false;
    }

    if (srow < 1 || srow > 4 || erow < 1 || erow > 4) {
        cout << "Nieprawidlowy wiersz." << endl;
        return false;
    }


    return true;
}

bool poprawnoscruchu(char plansza[4][4], int startkol, int startrow, int endkol, int endrow) //funkcja sprawdzająca poprawnosc ruchu
{
    char polestartowe = plansza[startrow][startkol];
    if (polestartowe != 'b')
    {
        return false;
    }

    if (plansza[endrow][endkol] != ' ')
    {
        return false;
    }

    if (!(startkol == endkol || startrow == endrow))
    {
        return false;
    }
    if (abs(startkol - endkol) > 1 || abs(startrow - endrow) > 1)
    {
        return false;
    }
    if (startkol == endkol && startrow == endrow) 
    {
        cout << "zly ruch" << endl;
        return false;
    }

    return true;
}

void zrobruch(char plansza[4][4], char ruch[], char grajacy, char patrzacy, Ruch r)
{

    if (poprawnoscruchu(plansza, r.startkol, r.startrow, r.endkol, r.endrow)) 
    {
        plansza[r.startrow][r.startkol] = ' ';
        plansza[r.endrow][r.endkol] = 'b'; 
    }
    else
    {
        cout << "nie mozna wykonac takiego ruchu" << endl;
    }

}

int main()
{
    // dwuwymiarowa tablica znaków - predefiniowana ponieważ na starcie gry pionki są zawsze ustawione tak samo 
    char plansza[4][4] = {
        {'c', 'c', 'c', 'c'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'b', 'b', 'b', 'b'}
        };
    
     char ruch[6]; // tablica znaków do formatu ruchu

     char gracz1[30];
     char gracz2[30];

     Starter(gracz1, gracz2);
    while (true) {
        wyswietlplan(plansza, gracz1, gracz2);
        cout << "Twoj ruch (format: A1-A2): ";
        cin >> ruch;
        if (czypoprawnedane(ruch)) 
        {
            Ruch r = zamieninput(ruch);
            zrobruch(plansza, ruch, 'b', 'c', r);
        }

    }

    return 0;
    
}