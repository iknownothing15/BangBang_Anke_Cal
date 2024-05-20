#ifndef LIVE_MODIFIERS_H
#define LIVE_MODIFIERS_H
#include "Live_Result.h"
#include "Consts.h"
namespace Live_modifiers
{
    /**
     * @brief A preset modifier, Its function is said [Here](https://bbs.nga.cn/read.php?tid=37770479&page=144)
     * 
     * @param r The Live_Result to be modified
     * @return Live_Result the modified Live_Result
     */
    Live_Result mixed_style(Live_Result r)
    {
        if(r.audience_score==GREATEST_FAILURE_ID)
            return r;
        if(r.audience_score==GREATEST_SUCCESS_ID)
            return r;
        if (r.final_performance_score > 69)
            r.audience_score = std::max(r.audience_score, NORMAL_SUCCESS_ID);
        if (r.final_performance_score < 40)
            r.audience_score = std::min(r.audience_score, FAILURE_ID);
        return r;
    }
    /**
     * Add your own modifier here.
     */
    
} // namespace Live_modifiers
#endif