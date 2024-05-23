#ifndef BANGBANG_H
#define BANGBANG_H
#include "Band.h"
#include "Random_Generator.h"
#include "Interactions.h"
/**
 * @brief give the detailed result of the BangBang game.
 *
 * @param A the first band.
 * @param B the second band.
 * @param G a random generator.
 * @param times the number of times the game will be played.
 * @return std::vector<int>
 * [0, 1, 2] means the first band wins, draws, loses in performance score while wins in audience score.
 * [3, 4, 5] means the first band wins, draws, loses in performance score while draws in audience score.
 * [6, 7, 8] means the first band wins, draws, loses in performance score while loses in audience score.
 */
std::vector<int> BangBang_V(Band A, Band B, Random_Generator &G, int times)
{
    std::vector<int> result(9);
    while (times--)
    {
        Live_Result A_result = A.live(G), B_result = B.live(G);
        int x, y;
        if (A_result.audience_score > B_result.audience_score)
            x = 0;
        else if (A_result.audience_score == B_result.audience_score)
            x = 1;
        else
            x = 2;
        if (A_result.final_performance_score > B_result.final_performance_score)
            y = 0;
        else if (A_result.final_performance_score == B_result.final_performance_score)
            y = 1;
        else
            y = 2;
        result[x * 3 + y]++;
    }
    return result;
}
/**
 * @brief return the winning rate of the first band.
 *
 * @param A the first band.
 * @param B the second band.
 * @param G a random generator.
 * @param times the number of times the game will be played.
 * @return double
 * the winning rate of the first band.
 * Audiance score is the first priority, performance score is the second.
 * draw is NOT considered as a win.
 */
double BangBang(Band A, Band B, Random_Generator &G, int times)
{
    int win = 0;
    for (int i = 0; i < times; i++)
    {
        Live_Result A_result = A.live(G), B_result = B.live(G);
        win += B_result < A_result;
    }
    return 100.0 * win / times;
}

double BangBang_over_known_result(Band A,Live_Result B_result, Random_Generator &G, int times)
{
    int win = 0;
    for (int i = 0; i < times; i++)
    {
        Live_Result A_result = A.live(G);
        win += B_result < A_result;
    }
    return 100.0 * win / times;
}
#endif