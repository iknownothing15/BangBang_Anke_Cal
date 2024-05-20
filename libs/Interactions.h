#ifndef INTERACTIONS_H
#define INTERACTIONS_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Band.h"
#include "Consts.h"
#include "BangBang.h"
#include "Live_modifiers.h"
/**
 * @brief A namespace that contains functions that interact with the user.
 *
 * I'm not going to add clear comments to each function, They are not important.
 */
namespace Interactions
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
    Band read_band()
    {
        int member_count;
        std::string name;
        std::vector<int> skill, modifier;
        int performance_score_modifier;
        member_count = read_num("Please input the member count of the band(1-10):", 1, 20);
        name = read_string("Please input the name of the band(No space):");
        for (int i = 0; i < member_count; i++)
        {
            std::stringstream desc;
            desc << "Please input the skill level of the member " << i + 1 << "(0-100):";
            skill.push_back(read_num(desc.str(), 0, 100));
        }
        for (int i = 0; i < member_count; i++)
        {
            std::stringstream desc;
            desc << "Please input the skill modifier of the member " << i + 1 << "(-20-20):";
            modifier.push_back(read_num(desc.str(), -20, 20));
        }
        performance_score_modifier = read_num("Please input the performance score modifier of the band(-20-20):", -20, 20);
        return Band(member_count, name, skill, modifier, {}, performance_score_modifier);
    }
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
    
    void list_bands(const std::vector<Band> &Bands){
        std::cout<<"The bands are:"<<std::endl;
        for(size_t i=0;i<Bands.size();i++){
            std::cout<<i+1<<". "<<Bands[i].get_name()<<std::endl;
        }
    }
    
    void show_single_live_result(Band &band, Random_Generator &G){
        Live_Result result=band.live(G);
        std::cout<<band.get_name()<<"'s result is:"<<std::endl;
        std::cout<<result.show()<<std::endl;
    }

    void clear_screen(){
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
        //this is not elegant all !!!!!!
        //I will find a better way to do this.
    }

    void interactive_UI_main(){
        int band1_id,band2_id;
        Live_Result result(0,0);
        std::stringstream desc;
        Random_Generator G;
        Band RAS(6, "RAS", {90, 80, 80, 85, 75, 70}, {5, 5, 5, 5, 5, 10}, {}, 10);
        Band Roselia(5, "Roselia", {95, 85, 75, 80, 90}, {5, 5, 5, 5, 5}, {}, 30);
        Band SE(4, "SE", {72, 79, 79, 75}, {10, 10, 10, 10}, {Live_modifiers::mixed_style}, 5);
        std::vector<Band> Bands={RAS,Roselia,SE};
        while(true){
            desc<<"Please choose a option:(RAS Roselia and SE are already in the list.)"<<std::endl;
            desc<<"0.quit"<<std::endl;
            desc<<"1.add a band"<<std::endl;
            desc<<"2.list all the bands"<<std::endl;
            desc<<"3.show the result of a single live"<<std::endl;
            desc<<"4.begin Sub-space lives"<<std::endl;
            int opt=read_num(desc.str(),0,4);
            //clean the desc
            desc.str("");
            //clean the screen
            clear_screen();
            switch (opt){
                case 0:
                    return;
                case 1:
                    Bands.push_back(read_band());
                    std::cout<<"The band is added."<<std::endl;
                    break;
                case 2:
                    list_bands(Bands);
                    break;
                case 3:
                    std::cout<<"Currently, the bands are:"<<std::endl;
                    list_bands(Bands);
                    band1_id=read_num("Please input the id of the first band(1-"+std::to_string(Bands.size())+"):",1,Bands.size())-1;
                    show_single_live_result(Bands[band1_id],G);
                    break;
                case 4:
                    std::cout<<"Currently, the bands are:"<<std::endl;
                    list_bands(Bands);
                    band1_id=read_num("Please input the id of the first band(1-"+std::to_string(Bands.size())+"):",1,Bands.size())-1;
                    band2_id=read_num("Please input the id of the second band(1-"+std::to_string(Bands.size())+"):",1,Bands.size())-1;
                    show_BangBang_result(Bands[band1_id],Bands[band2_id],G,DEFAULT_MONTCARLO_TIMES);
                    break;
                default:
                    std::runtime_error("Unreachable code");
            }
            std::cout<<std::endl<<std::endl;
            system("pause");
            clear_screen();
        }
        return;
    }
} // namespace Interactions
#endif