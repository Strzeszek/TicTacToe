//
// Created by Strzeszek on 18.06.2022.
//

#ifndef PAMSI_FINAL_GRAJ_H
#define PAMSI_FINAL_GRAJ_H
#include "minmax.h"
#include "StanGry.h"
using namespace std;

coord GetMove(int N)
{
    coord move;

    bool przerwij = false;
    cout << "W jakim miejscu chcesz umieścić swój znacznik?" << endl;
    while(!przerwij)
    {
        cin >> move.x >> move.y;
        if(std::max(move.x, move.y) > N - 1 || std::min(move.x, move.y) < 0)
        {
            cout << "Nieprawidłowe koordynaty :(" << endl << "Proszę podaj poprawne miejsce!" << endl;
        }
        przerwij = true;
    }
    return move;
}

void ending(const StanGry& game)
{
   int eval = game.evaluate();
   if(eval == Wynik::cpuWin)
       cout << "CPU WIN" << endl;
   else if(eval == Wynik::playerWin)
       cout << "PLAYER WIN" << endl;
   else if(eval == Wynik::remis)
       cout << "REMIS" << endl;
    return;


}

void Graj()
{
    int size;
    int requirement;
    char first;
    int depth;
    bool przerwij = false;
    int choice;

    cout << "Podaj wielkosć planszy:" << endl;
    while(!przerwij)
    {
        cin >> size;
        if(size < 3)
            cout << "Plansza za mała! Podaj prawidłowy rozmiar!" << endl;
        else
            przerwij = true;
    }

    przerwij = false;

    cout << "Ile znaków ma być potrzebnych do wygranej? Podaj wartosć z przedziału [3 - " << size << "]" << endl;
    while(!przerwij)
    {
        cin >> requirement;
        if(requirement > size || requirement < 3)
            cout << "Podałeś nieprawidłową wartość! Podaj jeszcze raz wartość z przedziału [3 - " << size << "]" << endl;
        else przerwij = true;
    }

    przerwij = false;
    while(!przerwij)
    {
        cout << "Kto ma zacząć?" << endl << "1 - gracz" << endl << "2 - AI" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
                first = 'X';
                przerwij = true;
                break;

            case 2:
                first = '0';
                przerwij = true;
                break;

            default:
                cout << "Podaj poprawny argumeny wywołania!" << endl;
                break;
        }
    }

    przerwij = false;
    cout << "Ustaw parametr depth dla algorytmu MinMax z zakresu [1 - " << size * size << "]" << endl;
    while(!przerwij)
    {
        cin >> depth;
        if(depth < 1 || depth > size * size)
            cout << "Podaj poprawną wartość!" << endl;
        przerwij = true;
    }


    StanGry GRA(size);
    GRA.set_win_requirement(requirement);
    if(first == 'X')
        GRA.set_active_turn(true);
    else
        GRA.set_active_turn(false);
    while(GRA.evaluate() == Wynik::idk)
    {
        if(GRA.get_active_turn())
        {
            coord ruch_gracza = GetMove(GRA.get_size());
            GRA.create_mark(GRA.get_active_turn(), ruch_gracza.x, ruch_gracza.y);
            GRA.print_board();
            GRA.set_active_turn(false);
        }
        else if(!GRA.get_active_turn())
        {
            coord ruch_cpu = BestMove(GRA, depth, minus_inf, inf);
            GRA.create_mark(GRA.get_active_turn(), ruch_cpu.x, ruch_cpu.y);
            GRA.print_board();
            GRA.set_active_turn(true);
        }
    }
    ending(GRA);
}
#endif //PAMSI_FINAL_GRAJ_H
