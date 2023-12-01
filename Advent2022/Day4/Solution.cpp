#include <algorithm>
#include <fstream>
#include <iostream>
#include <string_view>
#include <ranges>




int main(){
    std::ifstream MyFile("Pairs.txt");
    std::string items;
    int score{0};
    int score2{0};
    std::pair<int,int> pair, pair2;

    while (getline(MyFile, items)){
        std::string p1 = items.substr(0,items.find(","));
        std::string p2 = items.substr(items.find(",") + 1, items.size() - items.find(","));
        pair.first = stoi(p1.substr(0,p1.find("-")));
        pair.second = stoi(p1.substr(p1.find("-") + 1, p1.size() - p1.find("-")));
        pair2.first = stoi(p2.substr(0,p2.find("-")));
        pair2.second = stoi(p2.substr(p2.find("-") + 1, p2.size() - p2.find("-")));

        if ((pair.first >= pair2.first && pair.second <= pair2.second) ||
            (pair.first <= pair2.first && pair.second >= pair2.second)) {
            score += 1;
        }

        if ((pair.first >= pair2.first && pair.second <= pair2.second) ||
            (pair.first <= pair2.first && pair.second >= pair2.second) || 
            pair.first == pair2.first || 
            pair.second == pair2.second ||
            pair.second >= pair2.first && pair.first <= pair2.second) {
            score2 += 1;
        }
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;


    MyFile.close();
}