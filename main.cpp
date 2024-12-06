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

void wyswietlplan(char plansza[4][4], char gracz1[], char gracz2[])
{
    int row = 4;
    cout << gracz2 << " (c)" << endl;
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
    cout << gracz1 << " (b)"<< endl;
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

bool czypoprawnedane(char ruch[])
{
    int i = 0;
    while (ruch[i] != '\0') i++;
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

bool popruchu(char plansza[4][4], int startkol, int startrow, int endkol, int endrow , char grajacy) //funkcja sprawdzająca poprawnosc ruchu

{
    char polestartowe = plansza[startrow][startkol];
    if (polestartowe != grajacy)
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

bool popbicia(char plansza[4][4], Ruch r, char grajacy, char patrzacy)
{
    if (r.startkol != r.endkol && r.startrow != r.endrow)
    {
        return false;
    }

    if (r.startkol == r.endkol)
    {
        if (plansza[r.startrow+1][r.startkol] == grajacy && plansza[r.startrow+3][r.startkol] == patrzacy && plansza[r.endrow][r.endkol] == ' ')
        {
            return true;
        }
        else if (plansza[r.startrow-1][r.startkol] == grajacy && plansza[r.startrow-3][r.startkol] == patrzacy && plansza[r.endrow][r.endkol] == ' ')
        {
            return true;
        }  
        
    }
    if (r.startrow == r.endrow)
    {
        if (plansza[r.startrow][r.startkol+1] == grajacy && plansza[r.startrow][r.startkol+3] == patrzacy && plansza[r.endrow][r.endkol] == ' ')
        {
            return true;
        }
        else if (plansza[r.startrow][r.startkol-1] == grajacy && plansza[r.startrow][r.startkol-3] == patrzacy && plansza[r.endrow][r.endkol] == ' ')
        {
            return true;
        }
    }
    return false;

}

void zrobruch(char plansza[4][4], char grajacy, char patrzacy, Ruch r)
{
    if (popbicia(plansza, r, grajacy, patrzacy))
    {
        if (r.startkol == r.endkol)
        {
            if (r.startrow > r.endrow)
            {
                plansza[r.startrow-3][r.startkol] = ' ';
            }
            if (r.startrow < r.endrow)
            {
                plansza[r.startrow+3][r.startkol] = ' ';
            }
            plansza[r.endrow+1][r.endkol] = grajacy; 
        }
        else if (r.startrow == r.endrow)
        {
            if (r.startkol > r.endkol)
            {
                plansza[r.startrow][r.startkol-3] = ' ';
            }
            if (r.startkol < r.endkol)
            {
                plansza[r.startrow][r.startkol+3] = ' ';
            }
            plansza[r.endrow][r.endkol+1] = grajacy; 
        }
        plansza[r.startrow][r.startkol] = ' ';
        
    }
    

    else if (popruchu(plansza, r.startkol, r.startrow, r.endkol, r.endrow, grajacy)) 
    {
        plansza[r.startrow][r.startkol] = ' ';
        plansza[r.endrow][r.endkol] = grajacy; 
    }
    else
    {
        cout << "nie mozna wykonac takiego ruchu" << endl;
    }
    zmianatury(grajacy, patrzacy);

}

bool blokadaprzeciw(char plansza[4][4], char patrzacy)
{
    int iloscpionprzeciw;
    iloscpionprzeciw = 0;
    int otoczony;
    otoczony = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (plansza[i][j] == patrzacy)
            {
                iloscpionprzeciw++;
                bool dol;
                bool gora;
                bool prawo;
                bool lewo;
                if (i + 1 < 4)
                {
                    dol = plansza[i + 1][j] != ' ';
                }
                else
                {
                    dol = true;
                }
                if (i - 1 >= 0)
                {
                    gora = plansza[i - 1][j] != ' ';
                }
                else
                {
                    gora = true;
                }
                if (j + 1 < 4)
                {
                    prawo = plansza[i][j + 1] != ' ';
                }
                else
                {
                    prawo = true;
                }
                if (j - 1 >= 0)
                {
                    lewo = plansza[i][j - 1] != ' ';
                }
                else
                {
                    lewo = true;
                }

                if (dol && gora && prawo && lewo) 
                {
                    otoczony++;
                }
            }
            
        } 
    }
    if (iloscpionprzeciw == otoczony) {
        return true;
    }
    return false;
    
}

bool brakpionkow(char plansza[4][4], char patrzacy)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (plansza[i][j] == patrzacy)
            {
                return false;
            }
        }
    }
    return true;
    
}

void zmianatury(char &grajacy, char &patrzacy)
{
    if (grajacy == 'c')
    {
        grajacy = 'b';
        patrzacy = 'c';
    }
    else
    {
        grajacy = 'c';
        patrzacy = 'b';
    }
    
}

int main()
{
    char plansza[4][4] = {
        {'c', 'c', 'c', 'c'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'b', 'b', 'b', 'b'}
        };
    
    char ruch[6];

    char gracz1[30];
    char gracz2[30];
    char patrzacy;
    char grajacy;
    grajacy = 'c';
    patrzacy = 'b';

    Starter(gracz1, gracz2);
    while (true) {
        wyswietlplan(plansza, gracz1, gracz2);
        if (brakpionkow(plansza, patrzacy) || blokadaprzeciw(plansza, patrzacy))
        {
            cout << "wygrywa gracz: " << grajacy << endl;
            break;
        }
        
        cout << "Twoj ruch (format: A1-A2): ";
        cin >> ruch;
        if (czypoprawnedane(ruch)) 
        {
            Ruch r = zamieninput(ruch);
            zrobruch(plansza, grajacy, patrzacy, r);
        }
        
    }

    return 0;
    
}