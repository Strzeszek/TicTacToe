//
// Created by Strzeszek on 18.06.2022.
//

#ifndef PAMSI_FINAL_MINMAX_H
#define PAMSI_FINAL_MINMAX_H
#include <limits>
#include "StanGry.h"
using namespace std;

constexpr int inf = std::numeric_limits<int>::max();
constexpr int minus_inf = std::numeric_limits<int>::min();

struct coord
{
    int x;
    int y;
};

int minmax(const StanGry& game, int depth, int alpha, int beta, bool turn)
{
    int evaluation =  game.evaluate();
    if(depth <= 0)
    {
        if(evaluation == Wynik::idk)
            return 0;
        return evaluation;
    }
    else if(evaluation == Wynik::playerWin)
        return Wynik::playerWin + depth;

    else if(evaluation == Wynik::cpuWin)
        return Wynik::cpuWin - depth;

    else if(evaluation == Wynik::remis)
    {
        if(turn)
            return Wynik::remis + depth;
        return Wynik::remis - depth;
    }


    if(turn)
    {
        int maxeval = minus_inf;

        StanGry Hypo(game.get_size());  //Skopiowanie stanu gry do rozpatrywania
        Hypo = game;                        //

        bool przerwanie = false;
        for(int i = 0; i < Hypo.get_size(); i++)
        {
            for(int j = 0; j < Hypo.get_size(); j++)
            {
                if(Hypo.get_place(i,j) == Gracz::empty)
                {
                    Hypo.create_mark(turn, i , j);

                    int eval = minmax(Hypo, depth - 1, alpha, beta, false);
                    maxeval = max(maxeval, eval);

                    Hypo.delete_mark(i, j);

                    alpha = max(alpha, maxeval);
                    if(beta <= alpha)
                    {
                        return maxeval;
                    }
                }
            }
        }
        return maxeval;
    }

    else
    {
        int mineval = inf;

        StanGry Hypo(game.get_size());  //Skopiowanie stanu gry do rozpatrywania
        Hypo = game;                        //

        bool przerwanie = false;
        for(int i = 0; i < Hypo.get_size(); i++)
        {
            for(int j = 0; j < Hypo.get_size(); j++)
            {
                if(Hypo.get_place(i, j) == Gracz::empty)
                {
                    Hypo.create_mark(turn, i, j);

                    int eval = minmax(Hypo, depth - 1, alpha, beta, true);
                    mineval = min(mineval, eval);

                    Hypo.delete_mark(i, j);
                    beta = min(beta, mineval);
                    if(beta <= alpha)
                        return mineval;
                }
            }
        }
        return mineval;
    }
}

coord BestMove(StanGry& game, int depth, int alpha, int beta)
{
    coord move;
    move.x = 0;
    move.y = 0;
    int mineval = inf;

    StanGry Hypo(game.get_size());
    Hypo = game;

    bool przerwij = false;
    for(int i = 0; i < Hypo.get_size(); i++)
    {
        for(int j = 0; j < Hypo.get_size(); j++)
        {
            if(Hypo.get_place(i, j) == Gracz::empty)
            {
                Hypo.create_mark(false, i, j);
                int eval = minmax(Hypo, depth - 1, alpha, beta, true);
                Hypo.delete_mark(i, j);
                if(eval < mineval)
                {
                    mineval = eval;
                    move.x = i;
                    move.y = j;
                }
                beta = min(beta, mineval);
                if(beta <= alpha)
                {
                    przerwij = true;
                    break;
                }
            }
        }
        if(przerwij) break;
    }
    return move;
}

#endif //PAMSI_FINAL_MINMAX_H
