#ifndef BangBang_Cal_RE_CONSTS_H
#define BangBang_Cal_RE_CONSTS_H
#include<string>
/**
 * @brief The possible results of the game.
 * 0 means the greatest failure, 5 means the greatest success.
 * @todo change the fixed array to vector.
 */
const int Scores[] = {-20, -10, 10, 15, 20, 30};
const int POSSIBLE_RESULT_SIZE = 6;
/**
 * @brief The possible results of the audience.
 * 
 */
const int GREATEST_FAILURE_ID = 0;
const int FAILURE_ID = 1;
const int NORMAL_SUCCESS_ID = 2;
const int HARD_SUCCESS_ID = 3;
const int VERY_HARD_SUCCESS_ID = 4;
const int GREATEST_SUCCESS_ID = 5;
const std::string STATUS[]={ "Greatest failure", "Failure", "Normal success", "Hard success", "Very hard success", "Greatest success" };
const int DEFAULT_MONTCARLO_TIMES = 100000;
enum class ScoreResult { Win, Draw, Lose };
#endif