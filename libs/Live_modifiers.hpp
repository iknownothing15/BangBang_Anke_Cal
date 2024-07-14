#ifndef LIVE_MODIFIERS_HPP
#define LIVE_MODIFIERS_HPP
#include "Live_Result.hpp"
#include "Consts.hpp"
namespace Live_modifiers
{
    /**
     * @brief A preset modifier, Its function is said [Here](https://bbs.nga.cn/read.php?tid=37770479&page=144)
     *
     * @param r The Live_Result to be modified
     * @return Live_Result the modified Live_Result
     */
    Live_Result mixed_style(Live_Result r, int time)
    {
        if (time != 1)
            return r;
        if (r.audience_score == GREATEST_FAILURE_ID)
            return r;
        if (r.audience_score == GREATEST_SUCCESS_ID)
            return r;
        if (r.final_performance_score > 69)
            r.audience_score = std::max(r.audience_score, NORMAL_SUCCESS_ID);
        if (r.final_performance_score < 40)
            r.audience_score = std::min(r.audience_score, FAILURE_ID);
        return r;
    }

    Live_Result medium_quality(Live_Result r, int time)
    {
        if (time != 0)
            return r;
        if (r.performance_score >= 60)
        {
            r.final_performance_score += 5;
        }
        return r;
    }
    /**
     * Add your own modifier here.
     */

} // namespace Live_modifiers
#endif