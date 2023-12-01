#include <algorithm>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream MyFile("Trees.txt");
    std::string items;
    int score{0};
    int score2{0};
    int trees[99][99];
    int y = 0;
    bool top = false;
    bool bottom = false;
    bool left = false;
    bool right = false;
    int scenicScoreTop = 0;
    int scenicScoreBottom = 0;
    int scenicScoreLeft = 0;
    int scenicScoreRight = 0;
    int highestScenicScore = 0;
    
    while (getline(MyFile, items)){
        
        for (size_t i = 0; i < items.size(); i++)
        {
            trees[y][i] = items[i];
        }
        y++;

    }

    for (size_t i = 0; i < 99; i++)
    {
        for (size_t j = 0; j < 99; j++)
        {
            for (int a = j + 1; a < 99; a++)
            {
                scenicScoreRight++;
                if (trees[i][j] <= trees[i][a])
                {
                    right = true;
                    break;
                }
            }

            for (int a = j - 1; a > (-1); a--)
            {
                scenicScoreLeft++;
                if (trees[i][j] <= trees[i][a])
                {
                    left = true;
                    break;
                }
            }

            for (int a = i + 1; a < 99; a++)
            {
                scenicScoreBottom++;
                if (trees[i][j] <= trees[a][j])
                {
                    bottom = true;
                    break;
                }
            }

            for (int a = i - 1; a > (-1); a--)
            {
                scenicScoreTop++;
                if (trees[i][j] <= trees[a][j])
                {
                    top = true;
                    break;
                }
            }
            
            /*if (trees[i][j] <= trees[i][j-1])
            {
                left = true;
            }

            if (trees[i][j] <= trees[i + 1][j])
            {
                bottom = true;
            }

            if (trees[i][j] <= trees[i - 1][j])
            {
                top = true;
            }*/

            if(!right || !left || !top || !bottom){
                score += 1;
            }

            right = false;
            left = false;
            top = false;
            bottom = false;

            int current = scenicScoreLeft * scenicScoreRight * scenicScoreTop * scenicScoreBottom;
            if(current > highestScenicScore) highestScenicScore = current;
            scenicScoreLeft = 0;
            scenicScoreRight = 0;
            scenicScoreTop = 0;
            scenicScoreBottom = 0;
        }
        
    }
    std::cout << score << std::endl;
        std::cout << highestScenicScore << std::endl;

}