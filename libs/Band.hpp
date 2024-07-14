#ifndef BAND_DS_HPP
#define BAND_DS_HPP
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <functional>
#include "Consts.hpp"
#include "Live_Result.hpp"
#include "Random_Generator.hpp"
#include "live_modifiers.hpp"
/**
 * @brief The core data structure of the game, representing a band.
 * @param member_count The number of members in the band.
 * @param name The name of the band.
 * @param skill The skill of each member in the band. (0~100) out of the range will result in an undefined behavior.
 * @param modifier The modifier of each member in the band.(0~100) if skill + modifier > 100,
 * I have no idea what will happen. Maybe this is a bug, I might fix it in the future.
 * @param other_mechanism A vector of functions that will be called after the performance score is calculated.
 * The function should only take a Live_Result as input and return a Live_Result.
 * Notice that this program will not check the correctness of the function, so make sure you know what you are doing.
 * @param performance_score_modifier The modifier of the performance score of the band.
 * This will be added to the performance score after the calculation.
 * @param remedial_chances The number of chances that the band can remedial.
 * This will be calculated based on the average skill of the band.
 * IT IS NOT A PARAMETER OF THE CONSTRUCTOR!
 */

class Band
{
private:
    int member_count;
    std::string name;
    std::vector<int> skill, modifier;
    std::vector<std::function<Live_Result(Live_Result, int)>> other_mechanism;
    int performance_score_modifier, remedial_chances;
    /**
     * @brief A function that will normalize the performance score based on the member count.
     *
     * @param normalized_performance_score the original performance score.
     * @return double denoting the normalized performance score.
     */
    double normalize_performance_score(int performance_score, int temporary_modifier = 0) const
    {
        return 5.0 * performance_score / member_count + performance_score_modifier + temporary_modifier;
    }

public:
    /**
     * @brief Get the name of the band.
     *
     * @return std::string the name of the band.
     */
    std::string get_name() const
    {
        return name;
    }
    /**
     * @brief Construct a new Band object
     *
     * parameters are self-explanatory.I believe you can understand them.
     */
    Band(const int &_member_count,
         const std::string &_name,
         const std::vector<int> &_skill,
         const std::vector<int> &_modifier,
         const std::vector<std::function<Live_Result(Live_Result, int)>> &_other_mechanism,
         const int &_performance_score_modifier)
        : member_count(_member_count),
          name(_name),
          skill(_skill),
          modifier(_modifier),
          other_mechanism(_other_mechanism),
          performance_score_modifier(_performance_score_modifier),
          remedial_chances(0)
    {
        int avg = 0;
        for (const auto &s : skill)
            avg += s;
        if (avg >= 60 * member_count)
            remedial_chances++;
        if (avg >= 70 * member_count)
            performance_score_modifier += 5;
        if (avg >= 80 * member_count)
            remedial_chances++;
    }

    /**
     * @brief A default constructor.
     *
     */
    Band()
        : member_count(0),
          name(""),
          skill({}),
          modifier({}),
          other_mechanism({}),
          performance_score_modifier(0),
          remedial_chances(0)
    {
    }

    /**
     * @brief calculate the score of the band after remedial.
     *
     * @param results the results of the band members.
     * @return int the score of the band.
     * The function will change the results vector, so make sure you know what you are doing.
     * The function uses greedy algorithm to calculate the score.
     */
    int remedial_greedy(std::vector<int> &results)
    {
        int score = std::accumulate(results.begin(), results.end(), 0, [](int sum, int result)
                                    { return sum + Scores[result]; });

        for (int i = 1; i <= remedial_chances; i++)
        {
            auto p = std::max_element(results.begin(), results.end(), [](int r1, int r2)
                                      { return Scores[std::min(GREATEST_SUCCESS_ID, r1 + 1)] - Scores[r1] < Scores[std::min(GREATEST_SUCCESS_ID, r2 + 1)] - Scores[r2]; });

            score += Scores[std::min(GREATEST_SUCCESS_ID, *p + 1)] - Scores[*p];
            *p = std::min(GREATEST_SUCCESS_ID, *p + 1);
        }

        return score;
    }

    /**
     * @brief calculate the score of the band after remedial.
     *
     * @param results the results of the band members.
     * @return int the score of the band.
     * The function will change the results vector, so make sure you know what you are doing.
     * The function uses random algorithm to calculate the score.
     */
    int remedial_random(std::vector<int> &results, Random_Generator &G)
    {
        int score = std::accumulate(results.begin(), results.end(), 0, [](int sum, int result)
                                    { return sum + Scores[result]; });
        std::vector<int> remedial_candidates;
        for (int i = 0; i < member_count; i++)
        {
            if (results[i] != GREATEST_SUCCESS_ID)
            {
                remedial_candidates.push_back(i);
            }
        }
        for (int i = 0; i < remedial_chances; i++)
        {
            if (remedial_candidates.empty())
            {
                break;
            }
            int p = G.get_random(0, remedial_candidates.size() - 1);
            int member = remedial_candidates[p];
            score += Scores[results[member] + 1] - Scores[results[member]];
            results[member]++;
            if (results[member] == GREATEST_SUCCESS_ID)
            {
                remedial_candidates.erase(remedial_candidates.begin() + p);
            }
        }
        return score;
    }
    /**
     * @brief calculate the score of the band after the live.
     *
     * @param random_generator the random generator that will be used in the live.
     * @return Live_Result the result of the live.
     */
    Live_Result live(Random_Generator &random_generator)
    {
        std::vector<int> performance_results(member_count);
        for (int i = 0; i < member_count; i++)
            performance_results[i] = random_generator.get_result(skill[i] + modifier[i]);
        double performance_score = remedial_random(performance_results, random_generator);
        double normalized_performance_score = normalize_performance_score(performance_score);
        Live_Result live_result(0, normalized_performance_score, normalized_performance_score - performance_score_modifier);
        for (auto &x : other_mechanism)
            live_result = x(live_result, 0);
        int audience_score = random_generator.get_result(live_result.final_performance_score);
        live_result.audience_score = audience_score;
        for (auto &x : other_mechanism)
            live_result = x(live_result, 1);
        return live_result;
    }

    double get_original_performance_score(double normalized_performance_score)
    {
        return normalized_performance_score - performance_score_modifier;
    }
    
    std::vector<Live_Result> live_result_dirstribution(Random_Generator &random_generator, int times)
    {
        std::vector<Live_Result> results;
        for (int i = 0; i < times; i++)
        {
            results.push_back(live(random_generator));
        }
        return results;
    }
};
#endif