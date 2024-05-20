#ifndef LIVE_RESULT_H
#define LIVE_RESULT_H
#include<sstream>
/**
 * @brief The little struct to store the result of a live.
 * 
 * @param audience_score The score of the audience.
 * @param performance_score The score of the performance.
 */
class Live_Result
{
public:
    int audience_score;
    double final_performance_score;
    Live_Result(const int &_audience_score, const double &_performance_score) : audience_score(_audience_score), final_performance_score(_performance_score) {}
    /**
     * @brief Compare the two Live_Result.
     * 
     * @return whether the left one wins, draw is considered as lose. 
     */
    bool operator<(const Live_Result &x) const
    {
        return audience_score == x.audience_score ? final_performance_score < x.final_performance_score : audience_score < x.audience_score;
    }
    /**
     * @brief Show the result.
     * 
     * @param file_out The file to output the result.
     * 
     * this function is used to debug.
     */
    std::string show(){
        std::stringstream ss;
        ss << "Audience score: " << STATUS[audience_score] << "\nFinal performance score: " << final_performance_score ;
        return ss.str();
    }
};
#endif