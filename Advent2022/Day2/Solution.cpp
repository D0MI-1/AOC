//A for Rock, B for Paper, and C for Scissors
//X for Rock, Y for Paper, and Z for Scissors
//1 for Rock, 2 for Paper, and 3 for Scissors
//0 if you lost, 3 if the round was a draw, and 6 if you won

//Task2 X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win

#include <iostream>
#include <fstream>
#include <unordered_map>

int main(){
    std::ifstream MyFile("Strategy.txt");
    std::string round;
    int score{0};
    int score2{0};

    std::unordered_map<std::string, int>
    roundMap {{"A X", 4}, {"A Y", 8}, {"A Z", 3}, {"B X", 1}, {"B Y", 5}, {"B Z", 9}, {"C X", 7}, {"C Y", 2}, {"C Z", 6}};
    std::unordered_map<std::string, int>
    secondStarRoundMap {{"A X", 3}, {"A Y", 4}, {"A Z", 8}, {"B X", 1}, {"B Y", 5},
                        {"B Z", 9}, {"C X", 2}, {"C Y", 6}, {"C Z", 7}};

    
    while (getline(MyFile, round)){
        score += roundMap.at(round);
        score2 += secondStarRoundMap.at(round);

    }
    
    std::cout << score << std::endl;
    std::cout << score2 << std::endl;
    MyFile.close();
}