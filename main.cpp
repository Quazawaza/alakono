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