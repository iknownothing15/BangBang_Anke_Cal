/**
 * @file BangBang_Cal
 * @author UnderLine (dyf_dyf@outlook.com)
 * @brief A simulation of the Bangbang game in this Anke passage [https://bbs.nga.cn/read.php?tid=37770479].
 *                                                  ^^^^(I don't know how to translate it into English TAT)
 * @version 1.0.1 (rev. 2)
 * @date 2024-05-17
 *
 * @warning I'm just a student. If you found something wrong in this program, please don't criticize me too much. TAT
 * 
 * This reporitory uses the GPLv3 license. Everyone can use it freely.
 *
 * @todo Add a GUI for this program.
 * I currently have no idea of how to do this. Maybe I will use Qt or something else.
 * If you have any good suggestions, please tell me (through email github or something else).
 * By the way, I need an artist to help me design the GUI because I'm not good at drawing. TAT
 * 
 * @todo It seems that I mistakenly write the application in .h file. But I'm too lazy to change it. 
 * So it will be like this. (⊙﹏⊙). 
 * You can fix it by a pull request if you want.
 */
#include "libs/Band.h"
#include "libs/Interactions.h"
#include "libs/BangBang.h"
#include "libs/Live_modifiers.h"
/**
 * @brief here is the main function.
 * I give some examples here.
 * Now it will simulate the result of a live between SE and RAS.
 * You may need to change the source code to get the result of other lives.
 * Maybe you need to have some knowledge of C++ to do this. TAT
 */
int main()
{
    Random_Generator G;
    Band RAS(6, "RAS", {90, 80, 80, 85, 75, 70}, {5, 5, 5, 5, 5, 10}, {}, 10);
    Band Roselia(5, "Roselia", {95, 85, 75, 80, 90}, {5, 5, 5, 5, 5}, {}, 30);
    Band SE(3, "SE", {72, 79, 79}, {10, 10, 10}, {Live_modifiers::medium_quality}, 5);
    Interactions::show_BangBang_result(SE, RAS, G, 100000);
    return 0;
}