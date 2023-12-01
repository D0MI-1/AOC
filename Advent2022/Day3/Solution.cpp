#include <algorithm>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream MyFile("Rucksack.txt");
    std::string items;
    int score{0};
    int score2{0};

    std::array<int, 57> counter;
    std::fill(counter.begin(), counter.end(), 0);

    while (getline(MyFile, items)){
        const auto c{*std::find_first_of(items.begin(), std::next(std::begin(items), items.size()/2),
                           std::next(std::begin(items), items.size()/2), items.end())};
        if (c >= 'a') {
            score += c - 'a' + 1;
        } else {
            score += c - 'A' + 1 + 26;
        }

        std::sort(items.begin(), items.end());
        items.erase(std::unique(items.begin(), items.end()), items.end());

        for (const auto c : items) {
            counter[c - 'A'] += 1;
            if (counter[c - 'A'] == 3) {
                if (c >= 'a') {
                    score2 += c - 'a' + 1;
                } else {
                    score2 += c - 'A' + 1 + 26;
                }
                std::fill(counter.begin(), counter.end(), 0);
                break;
            }
        }
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;


    MyFile.close();
}