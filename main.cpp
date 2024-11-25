// Tomasz Ciurkowski 203191 Elektronika i telekomunikacja Gra a la Kono (na motywach koreańskiej gry Kono)
#include <iostream>

using namespace std;

void wyswietlplan(char plansza[4][4]) //funkcja rysująca plansze
{
    int row = 4;
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
}

bool czypoprawnedane(char ruch[]) //funkcja sprawdzająca poprawność wprowadzanych danych 
{
    int i = 0;
    while (ruch[i] != '\0') i++;  // sprawdzanie długości wprowadzonego ciagu znaków
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
        cout << "Nieprawidlowa kolumna.\n";
        return false;
    }

    if (startrow < 1 || startrow > 4 || endrow < 1 || endrow > 4) {
        cout << "Nieprawidlowy wiersz.\n";
        return false;
    }

    if (startkol == endkol && startrow == endrow) {
        cout << "zly ruch\n";
        return false;
    }
    return true;
}

bool czynalezy(char plansza[4][4], int startkol, int startrow)
{
    char polestartowe = plansza[startrow - 1][startkol - 1];
    if (polestartowe != 'b')
    {
        return false;
    }
    return true;
}

bool czypoledocelowepuste (char plansza[4][4], int endkol,int endrow)
{
    if (plansza[endrow - 1][endkol - 1] != ' ')
    {
        return false;
    }
    return true;
}
bool czyruchpoprzekatnej(char plansza[4][4], int startkol, int startrow, int endkol, int endrow)
{
    {
        return false;
    }
    return true;
}
bool czydaleki(char plansza[4][4], int startkol, int startrow, int endkol, int endrow)
{
    if (plansza[startrow-2][startkol-1] == 'b')
    {
        if (abs(startkol - endkol) > 1 || abs(startrow - endrow) != 2)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    if (abs(startkol - endkol) > 1 || abs(startrow - endrow) > 1)
    {
        return false;
    }
    return true;
}

bool wykonajruch(char plansza[4][4], int startkol, int startrow, int endkol, int endrow) //funkcja odpowiadajaca za wykonanie ruchu
{
    if (!czynalezy(plansza, startkol, startrow))
    {
        return false;
    }
    if (!czypoledocelowepuste(plansza, endkol, endrow))
    {
        return false;
    }
    if (!czyruchpoprzekatnej(plansza, startkol, startrow, endkol, endrow))
    {
        return false;
    }
    if (!czydaleki(plansza, startkol, startrow, endkol, endrow))
    {
        return false;
    }
    return true;
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

    while (true) {
        wyswietlplan(plansza);
        cout << "Twoj ruch (format: A1-A2): ";
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

            if (wykonajruch(plansza, startkol, startrow, endkol, endrow)) 
            {
                plansza[startrow - 1][startkol - 1] = ' ';
                plansza[endrow - 1][endkol - 1] = 'b'; 
            }
            else
            {
                cout << "nie mozna wykonac takiego ruchu" << endl;
            }

        }

    }

    return 0;
    
}