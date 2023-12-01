#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <regex>

int main(){
    std::ifstream MyFile("Crates.txt");
    std::string items;
    int score{0};
    int score2{0};
    std::vector<std::string> in;
    
    while (getline(MyFile, items) && items.compare(" 1   2   3   4   5   6   7   8   9 ") != 0){
        in.push_back(items);
    }

//items.size() = 35 / 4 = 8 + 1 = 9 
    std::vector<std::stack<char>> stacks(items.size() / 4 + 1);
    std::vector<std::stack<char>> stacks2(items.size() / 4 + 1);

    for (int i = in.size() - 1; i >= 0; i--) {
        for (int j = 0; j < stacks.size(); j ++) {
        //Row von 0 - 35 an at 1 5 9 13 ... one Input für stack 
        const int k = j * 4 + 1;
        if (in[i][k] == ' ') continue;
            stacks[j].push(in[i][k]);
            stacks2[j].push(in[i][k]);
        }
    }

    const std::regex pattern(R"(move ([0-9]+) from ([0-9]+) to ([0-9]+))");
    while (getline(MyFile, items)){
        if (items.empty()){
            continue;
        }
        std::smatch match;
        std::regex_match(items, match, pattern);
        for (size_t i = 0; i < std::stoi(match[1]); i++)
        {
            const auto c = stacks[std::stoi(match[2]) - 1].top();
            stacks[std::stoi(match[2]) - 1].pop();
            stacks[std::stoi(match[3]) - 1].push(c);
        }

        std::vector<char> crates_lifted;
        for (size_t i = 0; i < std::stoi(match[1]); i++)
        {
            const auto c = stacks2[std::stoi(match[2]) - 1].top();
            stacks2[std::stoi(match[2]) - 1].pop();
            crates_lifted.push_back(c);
        }

        for (int i = crates_lifted.size()-1; i>=0; i--) {
            stacks2[std::stoi(match[3]) - 1].push(crates_lifted[i]);
        }
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;
    for(const auto stack : stacks){
        if (!stack.empty()) {
            std::cout << stack.top();
        } else {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    for(const auto stack : stacks2){
        if (!stack.empty()) {
            std::cout << stack.top();
        } else {
            std::cout << ' ';
        }
    }

    MyFile.close();
}