//
// Created by Strzeszek on 17.06.2022.
//

#include "StanGry.h"

bool StanGry::check_place(int i, int j) const
{
    if(tablica[i][j] != Gracz::empty)
        return false;
    return true;
}

void StanGry::create_mark(bool condition, int i, int j)
{
    if(check_place(i, j))
    {
        if(condition) tablica[i][j] = Gracz::player;
        else tablica[i][j] = Gracz::cpu;
    }
    else cout << "Miejsce jest zajete, sprobuj gdzie indziej" << endl;
}

void StanGry::delete_mark(int i, int j)
{
    if(tablica[i][j] != Gracz::empty)
    {
        tablica[i][j] = Gracz::empty;
    }
}

void StanGry::print_board() const
{
    const char *przerwa = "   ";

    for (int i = 0; i < N; i++)
    {
        if(i == 0) cout << "0" << "  ";             // Te trzy linie odpowiadają za pomocnicze wypisanie numerów wierszy
        else if(i == N - 1) cout << N - 1 << "  ";    //
        else cout << przerwa;                       //

        for(int j = 0; j < N; j++)
        {
            cout << tablica[i][j];
            if(j == N - 1) cout << endl;
            else if (j != N - 1) cout << "|";
        }

        cout << przerwa;
        cout << endl;
    }

    cout << "--------------------------" << endl << endl;

}

int StanGry::evaluate() const
{
    char TicTacToe[2] = { Gracz::cpu, Gracz::player};

    for(int player = 0; player < 2; player++)
    {
        char mark = TicTacToe[player];
        for(int i = 0; i < N; i ++)
        {
            for(int j = 0; j < N; j++)
            {
                int ct = 0;
                if(tablica[i][j] == mark)
                {
                    /* Pierwsza przekątna */
                    ct = 1;
                    for(int x = 1; x + i < N && x + j < N; x++)
                    {
                        if(tablica[i+x][j+x] != mark) break;
                        ct++;
                        if(ct == win_requirement)
                        {
                            if(mark == Gracz::player) return Wynik::playerWin;
                            else return Wynik::cpuWin;
                        }
                    }

                    /*Druga przekątna*/
                    ct = 1;
                    for(int x = 1; x + i < N && j - x > -1; x++)
                    {
                        if(tablica[i+x][j-x] != mark) break;
                        ct++;
                        if(ct == win_requirement)
                        {
                            if(mark == Gracz::player) return Wynik::playerWin;
                            else return Wynik::cpuWin;
                        }
                    }

                    /*Pionowo*/
                    ct = 1;
                    for(int x = 1; x + j < N; x++)
                    {
                        if(tablica[i][j+x] != mark) break;
                        ct++;
                        if(ct == win_requirement)
                        {
                            if(mark == Gracz::player) return Wynik::playerWin;
                            else return Wynik::cpuWin;
                        }
                    }

                    /*Pionowo*/
                    ct = 1;
                    for(int x = 1; x + i < N; x++)
                    {
                        if(tablica[i+x][j] != mark) break;
                        ct++;
                        if(ct == win_requirement)
                        {
                            if(mark == Gracz::player) return Wynik::playerWin;
                            else return Wynik::cpuWin;
                        }
                    }
                }
            }
        }
    }


    bool remis = true;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(tablica[i][j] == Gracz::cpu || tablica[i][j] == Gracz::player) continue;
            else
            {remis = false; break;}
        }
    }

    if(remis) return Wynik::remis;

    return Wynik::idk;
}

char StanGry::get_place(int i, int j) const
{
    if(i > N - 1 || j > N-1)
    {
        cout << "Zły indeks" << endl;
    }
    return tablica[i][j];
}


#include "StanGry.h"
