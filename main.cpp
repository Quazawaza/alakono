#include <iostream>

using namespace std;

void wyswietlplan(char plansza[4][4]) //funkcja rysująca planszę 
{
    int row = 4; // zmienna wyświetlająca rząd 
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
    cout << "   A   B   C   D"<< endl; // podpisanie kolumn 
}

bool czypoprawnedane(char ruch[]) //funkcja sprawdzająca poprawność wprowadzanych danych 
{
    int i = 0;
    while (ruch[i] != '\0') i++;  // sprawdzanie długości wprowadzonego ciągu znaków
    if (i != 5 || ruch[2] != '-') {
        cout << "Nieprawidlowy format. Poprawny format: D4-D2\n";
        return false;
    }

    char startkol = ruch[0]; 
    int startrow = ruch[1] - '0'; 
    char endkol = ruch[3];
    int endrow = ruch[4] - '0';

    startkol = toupper(startkol);
    endkol = toupper(endkol);

    if (startkol < 'A' || startkol > 'D' || endkol < 'A' || endkol > 'D') {
        cout << "Nieprawidlowa kolumna. Kolumny musza byc od A do D.\n";
        return false;
    }

    if (startrow < 1 || startrow > 4 || endrow < 1 || endrow > 4) {
        cout << "Nieprawidlowy wiersz. Wiersze musza byc od 1 do 4.\n";
        return false;
    }

    if (startkol == endkol && startrow == endrow) {
        cout << "Pozycja startowa i docelowa nie moga byc takie same.\n";
        return false;
    }
    return true;
}

bool CzyPionekNalezy(char plansza[4][4], int startkol, int startrow)
{
    char polestartowe = plansza[startrow - 1][startkol - 1];
    if (polestartowe != 'c')
    {
        cout << "Ten pionek nie nalezy do ciebie" << endl;
        return false;
    }
    return true;
}

bool ZrobRuch(char plansza[4][4], int startkol, int startrow, int endkol, int endrow)
{
    if (!CzyPionekNalezy(plansza, startkol, startrow))
    {
        return false;
    }
    
    if (plansza[endrow - 1][endkol - 1] != ' ')
    {
        cout << "pole docelowe nie jest puste" << endl;
        return false;
    }

    return true;
}

int main()
{
    // dwuwymiarowa tablica znaków - predefiniowana ponieważ na starcie gry pionki są zawsze ustawione tak samo 
    char plansza[4][4] = {
        {'b', 'b', 'b', 'b'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'c', 'c', 'c', 'c'}
        };
    
     char ruch[6]; // tablica znaków do formatu ruchu

    while (true) {
        wyswietlplan(plansza);
        cout << "Twoj ruch (format: kolumna wiersz kolumna wiersz, np. A1-A2): ";
        cin >> ruch;
        if (czypoprawnedane(ruch)) 
        {
            // zamiana danych na inty 
            int startkol = toupper(ruch[0]) - 'A' + 1;
            int startrow = ruch[1] - '0' - 1 ;
            int endkol = toupper(ruch[3]) - 'A' + 1;
            int endrow = ruch[4] - '0' - 1;

            //reinterpretacja danych aby można było wykonywać ruchy zgodnie z legendą
            startrow = 4 - startrow;
            endrow = 4 - endrow;

            if (ZrobRuch(plansza, startkol, startrow, endkol, endrow)) 
            {
                plansza[startrow - 1][startkol - 1] = ' ';
                plansza[endrow - 1][endkol - 1] = 'c'; 
            }

        }

    }

    return 0;
    
}