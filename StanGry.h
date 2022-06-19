//
// Created by Strzeszek on 17.06.2022.
//

#ifndef PAMSI_FINAL_STANGRY_H
#define PAMSI_FINAL_STANGRY_H
#include <iostream>
#include <vector>
using namespace std;

enum Gracz
{
    player = 'X',
    cpu = '0',
    empty = ' ',
};

enum Wynik
{
    playerWin = 10,
    cpuWin = -10,
    remis = 0,
    idk = 1,
};

class StanGry
{
private:

    int N;
    vector<vector<char>> tablica;
    bool active_turn; //prawda jeżeli tura jest gracza, fałsz jeżeli komputera
    unsigned int win_requirement;

public:

    StanGry(int size) //inicjalizacja planszy
    {
        N = size;
        active_turn = true;
        win_requirement = 0;

        for(int i = 0; i < N; i++)
        {
            vector<char> vec;
            for(int j = 0; j < N; j++)
            {
                vec.push_back(Gracz::empty);
            }
            tablica.push_back(vec);
        }
    };

    StanGry(const StanGry& gra) //Kopiujący konstruktor stanu gry
    {
        N = gra.N;
        active_turn = gra.active_turn;
        win_requirement = gra.win_requirement;

        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                tablica[i][j] = gra.tablica[i][j];
            }
        }
    };

    void set_win_requirement(int requirement)
    {
        win_requirement = requirement;
    }

    void set_active_turn(bool turn)
    {
        active_turn = turn;
    }

    bool check_place(int i, int j) const;

    void create_mark(bool condition, int i, int j);

    void delete_mark(int i, int j);

    void print_board() const;

    int evaluate() const;

    int get_size() const
    {
        return N;
    }

    bool get_active_turn() const
    {
        return active_turn;
    }

    char get_place(int i, int j) const;
};

#endif //PAMSI_FINAL_STANGRY_H
