#include <iostream>

using namespace std;

void wyswietlplan(char plansza[4][4]) //funkcja rysująca planszę 
{
    int row = 4; // zmienna wyświetlająca rząd 
    for (int i = 0; i < 4; i++)
    {
        cout << row << " |";
        for (int j = 0; j < 4; j++)
        {
            cout << plansza[i][j] << "|";
        }
        cout << endl;
        row--;
    }
    cout << "   A B C D\n"; // podpisanie kolumn 
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

    wyswietlplan(plansza);
}