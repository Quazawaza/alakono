// Tomasz Ciurkowski 203191 Elektronika i telekomunikacja Gra a la Kono (na motywach koreańskiej gry Kono)
#include <iostream>
#include <ctime>

using namespace std;

struct Gracz
{
    char imie[50];
    char pionki;
    bool aktywny;
};

struct Ruch
{
    int startkol;
    int startrow;
    int endkol;
    int endrow;
};

void Starter(Gracz &gracz1, Gracz &gracz2)
{
    cout << "wprowadz imie gracza 1 (pionki biale): ";
    cin >> gracz1.imie;
    cout << endl;
    gracz1.pionki = 'b';
    gracz1.aktywny = true;
    cout << "wprowadz ime gracza 2 (pionki czarne): ";
    cin >> gracz2.imie;
    cout << endl;
    gracz2.pionki = 'c';
    gracz2.aktywny = false;

}

void wyswietlplan(char plansza[4][4], Gracz &gracz1, Gracz &gracz2)
{
    int row = 4;
    cout << gracz2.imie << " pionki: " << gracz2.pionki << endl;
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
    cout << gracz1.imie<< " pionki: " << gracz1.pionki<< endl;
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

bool popruchu(char plansza[4][4],Ruch r, char grajacy) 

{
    char polestartowe = plansza[r.startrow][r.startkol];
    if (polestartowe != grajacy)
    {
        return false;
    }

    if (plansza[r.endrow][r.endkol] != ' ')
    {
        return false;
    }

    if (!(r.startkol == r.endkol || r.startrow == r.endrow))
    {
        return false;
    }
    if (abs(r.startkol - r.endkol) > 1 || abs(r.startrow - r.endrow) > 1)
    {
        return false;
    }
    if (r.startkol == r.endkol && r.startrow == r.endrow) 
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

bool zrobruch(char plansza[4][4], char grajacy, char patrzacy, Ruch r)
{
    if (popbicia(plansza, r, grajacy, patrzacy))
    {
        if (r.startkol == r.endkol)
        {
            if (r.startrow > r.endrow)
            {
                plansza[r.startrow-3][r.startkol] = ' ';
                plansza[r.endrow-1][r.endkol] = grajacy; 
            }
            if (r.startrow < r.endrow)
            {
                plansza[r.startrow+3][r.startkol] = ' ';
                plansza[r.endrow+1][r.endkol] = grajacy; 
            }
        }
        else if (r.startrow == r.endrow)
        {
            if (r.startkol > r.endkol)
            {
                plansza[r.startrow][r.startkol-3] = ' ';
                plansza[r.endrow][r.endkol-1] = grajacy; 
            }
            if (r.startkol < r.endkol)
            {
                plansza[r.startrow][r.startkol+3] = ' ';
                plansza[r.endrow][r.endkol+1] = grajacy; 
            }
        }
        plansza[r.startrow][r.startkol] = ' ';
        
    }
    

    else if (popruchu(plansza, r, grajacy)) 
    {
        plansza[r.startrow][r.startkol] = ' ';
        plansza[r.endrow][r.endkol] = grajacy; 
    }
    else
    {
        cout << "nie mozna wykonac takiego ruchu" << endl;
        return false;
    }
    return true;
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
void zmianatury(Gracz &gracz1, Gracz &gracz2)
{
    if (gracz1.aktywny)
    {
        gracz1.aktywny = false;
        gracz2.aktywny = true;
    }
    else
    {
        gracz1.aktywny = true;
        gracz2.aktywny = false;
    }
    
}

int GenRuchy(char plansza[4][4], char grajacy, Ruch (&ruchy)[32])
{
    int liczbarochow;
    liczbarochow = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (plansza[i][j] == grajacy)
            {
                for (int k = -1 ; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        if ((k == 0 && l == 0) || (abs(k) != 0 && abs(l) != 0)) {
                            continue;
                        }
                        int endkol;
                        int endrow;
                        endkol = j + l;
                        endrow = i+k;
                        if (endkol >= 0 && endkol < 4 && endrow >= 0 && endrow < 4)
                        {
                            Ruch *pomruch = new Ruch;

                            pomruch->startkol = j;
                            pomruch->startrow = i;
                            pomruch->endkol = endkol;
                            pomruch->endrow = endrow;
                            if (popruchu(plansza, *pomruch, grajacy))
                            {
                                ruchy[liczbarochow] = *pomruch;
                                liczbarochow++;
                            }

                            delete pomruch;
                               
                        }
                        
                    }

                    
                }
                
            }
            
        }
        
    }
    return liczbarochow;
    
}

int GenRuchyBijace(char plansza[4][4], char grajacy, char patrzacy, Ruch (&ruchy)[32])
{
    int liczbabic;
    liczbabic = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (plansza[i][j] == grajacy)
            {
                for (int k = -2; k <= 2; k++)
                {
                    for (int l = -2; l <= 2; l++)
                    {
                        if ((k == 0 && l == 0) || (abs(k) != 0 && abs(l) != 0)) 
                        {
                            continue;
                        }
                        int endkol;
                        int endrow;
                        endkol= j + k;
                        endrow = i + l;
                        if (endkol >= 0 && endkol < 4 && endrow >= 0 && endrow < 4)
                        {
                            Ruch *pomruch = new Ruch;

                            pomruch->startkol = j;
                            pomruch->startrow = i;
                            pomruch->endkol = endkol;
                            pomruch->endrow = endrow;

                            if (popbicia(plansza, *pomruch,grajacy, patrzacy)) 
                            {
                                ruchy[liczbabic] = *pomruch;
                                liczbabic++;
                            }

                            delete pomruch;
                        }
                    }
                    
                }
                
            }
            
        }

    }
    return liczbabic;
}

Ruch AutoRuch(char plansza[4][4], char grajacy, char patrzacy)
{
    Ruch ruchy[32];
    int liczbarochow;
    int liczbabic;
    int index;
    liczbarochow = GenRuchy(plansza, grajacy, ruchy);
    liczbabic = GenRuchyBijace(plansza, grajacy, patrzacy, ruchy);
    if (liczbabic > 0)
    {
        srand(time(0));
        index = rand()%liczbabic;
        return ruchy[index];
    }
    srand(time(0));
    index = rand()%liczbarochow;
    return ruchy[index];
}

int main()
{
    char plansza[4][4] = {
        {'c', 'c', 'c', 'c'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {'b', 'b', 'b', 'b'}
        };

    char ruch[10];

    Gracz gracz1;
    Gracz gracz2;

    Gracz* grajacy;
    Gracz* patrzacy;

    Starter(gracz1, gracz2);
    while (true) {
        wyswietlplan(plansza, gracz1, gracz2);
        if (gracz1.aktywny) {
            grajacy = &gracz1;
            patrzacy = &gracz2;
        } else {
            grajacy = &gracz2;
            patrzacy = &gracz1;
        }
        if (brakpionkow(plansza, grajacy->pionki) || blokadaprzeciw(plansza, grajacy->pionki))
        {
            cout << "wygrywa gracz: " << patrzacy->imie << endl;
            break;
        }
        if (gracz1.aktywny)
        {
            cout << "Ruch gracza: " << gracz1.imie << " pionki: " << gracz1.pionki << " gracz wykonuje ruch automatycznie"<< endl;
            Ruch r = AutoRuch(plansza, grajacy->pionki, patrzacy->pionki);
            if (zrobruch(plansza, grajacy->pionki, patrzacy->pionki, r))
                {
                    zmianatury(gracz1, gracz2);
                }
            
            
        }
        else
        {
            cout << "Ruch gracza: " << gracz2.imie << " pionki: " << gracz2.pionki << endl;
            cout << "wprowadz ruch: ";
            cin >> ruch;
            if (czypoprawnedane(ruch)) 
            {
            Ruch r = zamieninput(ruch);
            if (zrobruch(plansza, grajacy->pionki, patrzacy->pionki, r))
                {
                    zmianatury(gracz1, gracz2);
                }
            }
        }
        
        
    }

    return 0;
    
}