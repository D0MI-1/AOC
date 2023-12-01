#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>

struct Monkey{
    int count{0};
    std::queue<int> queue;
    std::array<std::string, 2> op;
    int div;
    int monkey1;
    int monkey2;
};

int main(){
    std::ifstream MyFile("Monkey.txt");
    std::string items;
    std::array<Monkey, 8> monkies;
    int n;
    int currMonkey {0};
    int currentItem;
    int nextMONK;

    while (getline(MyFile, items)){
        MyFile >> items >> items;
        
        //get all items
        while (MyFile >> n) {
            monkies[currMonkey].queue.push(n);
            if (MyFile.peek() != ',') {
                MyFile.ignore();
                break;
            }
            MyFile.ignore();
        }

        getline(MyFile, items);
        std::regex regex(R"(Operation: new = old (\*|\+) (\d+|old))");
        std::smatch matches;
        std::regex_search(items, matches, regex);
        monkies[currMonkey].op[0] = matches[1].str()[0];
        monkies[currMonkey].op[1] = matches[2].str();

        getline(MyFile, items);
        regex = (R"(Test: divisible by (\d+))");
        std::regex_search(items, matches, regex);
        monkies[currMonkey].div = stoi(matches[1]);

        getline(MyFile, items);
        regex = (R"(If true: throw to monkey (\d+))");
        regex_search(items, matches, regex);
        monkies[currMonkey].monkey1 = stoi(matches[1]);

        getline(MyFile, items);
        regex = (R"(If false: throw to monkey (\d+))");
        regex_search(items, matches, regex);
        monkies[currMonkey].monkey2 = stoi(matches[1]);

        //skip emty line
        if (currMonkey == 7) break;
        getline(MyFile, items);
        currMonkey++;
    }

    for (int i = 0; i < 10000; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            while(!monkies[j].queue.empty())
            {
                monkies[j].count++;	
                currentItem = monkies[j].queue.front();
                if (monkies[j].op.at(0) == "+"){
                    if (monkies[j].op.at(1) == "old")
                    {
                        currentItem += currentItem;
                    }else
                    {
                        currentItem += std::stoi(monkies[j].op.at(1));
                    }
                }else
                {
                    if (monkies[j].op.at(1) == "old")
                    {
                        currentItem *= currentItem;
                    }else
                    {
                        currentItem *= std::stoi(monkies[j].op.at(1));
                    }
                }

                currentItem /= 3;
                nextMONK = currentItem % monkies[j].div == 0 ?  monkies[j].monkey1 :  monkies[j].monkey2;
                monkies[nextMONK].queue.push(currentItem);
                monkies[j].queue.pop();
            }
        }
    }
    
    for (int j = 0; j < 8; ++j){
        std::cout << monkies[j].count << std::endl;
    }

    std::sort(std::begin(monkies), std::end(monkies), [](const auto& m1, const auto& m2) {return m1.count > m2.count;});
    std::cout << monkies[0].count * monkies[1].count  << '\n';
}