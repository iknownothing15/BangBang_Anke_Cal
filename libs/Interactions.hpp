#ifndef INTERACTIONS_HPP
#define INTERACTIONS_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Band.hpp"
#include "Consts.hpp"
#include "BangBang.hpp"
#include "Live_modifiers.hpp"

// namespace Interactor_Class
// {
//     class Interactor_Function
//     {
//     private:
//         std::string desc;
//         std::function<void(std::vector<Band>, std::vector<Live_Result>, Random_Generator)> func;
//         int Band_arg_count, Live_Result_arg_count;

//     public:
//         Interactor_Function(std::string desc, std::function<void(std::vector<Band>, std::vector<Live_Result>)> func, int Band_arg_count, int Live_Result_arg_count)
//         {
//             this->desc = desc;
//             this->func = func;
//             this->Band_arg_count = Band_arg_count;
//             this->Live_Result_arg_count = Live_Result_arg_count;
//         }
//     }
// }

namespace Interactor_Utility
{
    int read_num(std::string desc, int l, int r)
    {
        int n;
        while (true)
        {
            std::cout << desc;
            std::cin >> n;
            if (std::cin.fail() || n < l || n > r)
            {
                std::cout << "Invalid input" << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else
                return n;
        }
        std::runtime_error("Unreachable code");
        return -1;
    }
    std::string read_string(std::string desc)
    {
        std::string s;
        std::cout << desc << std::endl;
        std::cin >> s;
        return s;
    }

    Live_Result read_live_result()
    {
        std::cout << "Notice possible audience score are:" << std::endl;
        for (int i = 0; i < POSSIBLE_RESULT_SIZE; i++)
        {
            std::cout << i << ". " << STATUS[i] << std::endl;
        }
        int audience_score = read_num("Please input the audience score(0~" + std::to_string(POSSIBLE_RESULT_SIZE - 1) + "):", 0, POSSIBLE_RESULT_SIZE - 1);
        int final_performance_score = read_num("Please input the final performance score(0-100):", 0, 100);
        return Live_Result(audience_score, final_performance_score, 0);
    }

    Band read_band()
    {
        int member_count = read_num("Please input the member count of the band(1-10):", 1, 20);
        std::string name = read_string("Please input the name of the band(No space):");
        std::vector<int> skill, modifier;

        auto read_member_info = [&](const char *desc, int min, int max)
        {
            std::vector<int> info;
            for (int i = 0; i < member_count; i++)
            {
                std::stringstream ss;
                ss << "Please input the " << desc << " of the member " << i + 1 << "(" << min << "-" << max << "):";
                info.emplace_back(read_num(ss.str(), min, max));
            }
            return info;
        };

        skill = read_member_info("skill level", 0, 100);
        modifier = read_member_info("skill modifier", -20, 20);

        int performance_score_modifier = read_num("Please input the performance score modifier of the band(-20-20):", -20, 20);

        return Band(member_count, name, skill, modifier, {}, performance_score_modifier);
    }
}
/**
 * @brief A namespace that contains functions that interact with the user.
 *
 * I'm not going to add clear comments to each function, They are not important.
 *
 * Interactors is not elegant at all. I have no idea of how to make it better.
 * It might be changed into GUI of Qt or dotnet in the future. Hope
 */
namespace Interactions
{

    void show_result_V(const std::vector<int> &result)
    {
        std::cout << "Winning matrix:" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                std::cout << result[i * 3 + j] << " ";
            std::cout << std::endl;
        }
    }

    void show_BangBang_result(const Band &a, const Band &b, Random_Generator &G, int times)
    {
        double result = BangBang(a, b, G, times);
        std::cout << "The win rate of " << a.get_name() << " vs " << b.get_name() << " is:(draw is considered as lose)" << std::endl;
        std::cout << std::fixed << std::setprecision(2) << result << "%" << std::endl;
    }

    void list_bands(const std::vector<Band> &Bands)
    {
        std::cout << "The bands are:" << std::endl;
        for (size_t i = 0; i < Bands.size(); i++)
        {
            std::cout << i + 1 << ". " << Bands[i].get_name() << std::endl;
        }
    }

    void show_single_live_result(Band &band, Random_Generator &G)
    {
        Live_Result result = band.live(G);
        std::cout << band.get_name() << "'s result is:" << std::endl;
        std::cout << result.show() << std::endl;
    }

    void show_BangBang_over_known_result(Band &band, Live_Result live_result, Random_Generator &G, int times)
    {
        double result = BangBang_over_known_result(band, live_result, G, times);
        std::cout << "The win rate of " << band.get_name() << " over the known result is:" << std::endl;
        std::cout << std::fixed << std::setprecision(2) << result << "%" << std::endl;
    }

    void clear_screen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        // this is not elegant all !!!!!!
        // I will find a better way to do this.
    }

    void interactive_UI_main()
    {
        int band1_id, band2_id;
        Live_Result result(0, 0, 0);
        std::stringstream desc;
        Random_Generator G;
        Band RAS(6, "RAS", {90, 80, 80, 85, 75, 70}, {5, 5, 5, 5, 5, 10}, {}, 10);
        Band Roselia(5, "Roselia", {95, 85, 75, 80, 90}, {5, 5, 5, 5, 5}, {}, 30);
        Band SE(3, "SE", {72, 80, 80}, {10, 10, 10}, {Live_modifiers::mixed_style}, 10);
        std::vector<Band> Bands = {RAS, Roselia, SE};
        while (true)
        {
            desc << "Please choose a option:(RAS Roselia and SE are already in the list.)" << std::endl;
            desc << "0.quit" << std::endl;
            desc << "1.add a band" << std::endl;
            desc << "2.list all the bands" << std::endl;
            desc << "3.show the result of a single live" << std::endl;
            desc << "4.calculate the win rate of two bands" << std::endl;
            desc << "5.calculate the win rate of a band over a known result" << std::endl;
            int opt = Interactor_Utility::read_num(desc.str(), 0, 5);
            // clean the desc
            desc.str("");
            // clean the screen
            clear_screen();
            switch (opt)
            {
            case 0:
                return;
            case 1:
                Bands.push_back(Interactor_Utility::read_band());
                std::cout << "The band is added." << std::endl;
                break;
            case 2:
                list_bands(Bands);
                break;
            case 3:
                std::cout << "Currently, the bands are:" << std::endl;
                list_bands(Bands);
                band1_id = Interactor_Utility::read_num("Please input the id of the first band(1-" + std::to_string(Bands.size()) + "):", 1, Bands.size()) - 1;
                show_single_live_result(Bands[band1_id], G);
                break;
            case 4:
                std::cout << "Currently, the bands are:" << std::endl;
                list_bands(Bands);
                band1_id = Interactor_Utility::read_num("Please input the id of the first band(1-" + std::to_string(Bands.size()) + "):", 1, Bands.size()) - 1;
                band2_id = Interactor_Utility::read_num("Please input the id of the second band(1-" + std::to_string(Bands.size()) + "):", 1, Bands.size()) - 1;
                show_BangBang_result(Bands[band1_id], Bands[band2_id], G, DEFAULT_MONTCARLO_TIMES);
                break;
            case 5:
                list_bands(Bands);
                band1_id = Interactor_Utility::read_num("Please input the id of the band(1-" + std::to_string(Bands.size()) + "):", 1, Bands.size()) - 1;
                result = Interactor_Utility::read_live_result();
                show_BangBang_over_known_result(Bands[band1_id], result, G, DEFAULT_MONTCARLO_TIMES);
            default:
                std::runtime_error("Unreachable code");
            }
            std::cout << std::endl
                      << std::endl;
            system("pause");
            clear_screen();
        }
        return;
    }

    /**
     * @brief display the distribution of the live result.
     *
     * @param band the band to be tested.
     * @param G a random generator.
     * @param times over how many times the live will be played.
     */
    void show_live_result_dirstribution(Band &band, Random_Generator &G, int times)
    {
        std::vector<Live_Result> results = band.live_result_dirstribution(G, times);
        std::sort(results.begin(), results.end());
        std::vector<std::vector<int>> cnt(102, std::vector<int>(POSSIBLE_RESULT_SIZE));
        for (auto &x : results)
        {
            int score = std::min(101, std::max(0, int(x.final_performance_score) + 1));
            cnt[score][x.audience_score]++;
        }
        for (int i = 0; i <= 101; i++)
        {
            int sum = std::accumulate(cnt[i].begin(), cnt[i].end(), 0);
            if (sum == 0)
                continue;
            if (i == 0)
                printf("    <0,");
            else if (i == 101)
                printf(" >=100,");
            else
                printf("%6.d,", i - 1);
            for (int j = 0; j < POSSIBLE_RESULT_SIZE; j++)
            {
                if (cnt[i][j] == 0)
                    printf("   0,");
                else
                    printf("%4.d,", cnt[i][j]);
            }
            puts("");
        }
    }

    void show_live_result_dirstribution(Band &band, Random_Generator &G, int times, std::string file_name)
    {
        FILE *fp = fopen(file_name.c_str(), "w");
        if (fp == NULL)
        {
            std::cout << "Can't open the file" << std::endl;
            return;
        }
        std::vector<Live_Result> results = band.live_result_dirstribution(G, times);
        std::sort(results.begin(), results.end());
        std::vector<std::vector<int>> cnt(102, std::vector<int>(POSSIBLE_RESULT_SIZE));
        for (auto &x : results)
        {
            int score = std::min(101, std::max(0, int(x.final_performance_score) + 1));
            cnt[score][x.audience_score]++;
        }
        // write csv style file
        for (int i = 0; i <= 101; i++)
        {
            int sum = std::accumulate(cnt[i].begin(), cnt[i].end(), 0);
            if (sum == 0)
                continue;
            if (i == 0)
                fprintf(fp, "<0,");
            else if (i == 101)
                fprintf(fp, ">=100,");
            else
                fprintf(fp, "%d,", i - 1);
            for (int j = 0; j < POSSIBLE_RESULT_SIZE; j++)
            {
                fprintf(fp, "%d,", cnt[i][j]);
            }
            fprintf(fp, "\n");
        }
    }

} // namespace Interactions
#endif