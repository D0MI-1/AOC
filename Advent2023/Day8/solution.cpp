#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <sstream>
#include <deque>
#include <unordered_map>

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::deque<char> instructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> mapsLeftRightNavigation;

    if (std::getline(inputFile, line)) {
        for (char c : line) {
            instructions.push_back(c);
        }
    }

    while (std::getline(inputFile, line))
    {
        size_t equalPos = line.find('=');
        size_t commaPos = line.find(',');
        size_t leftParenthesisPos = line.find('(');
        size_t rightParenthesisPos = line.find(')');

        if (equalPos != std::string::npos && commaPos != std::string::npos &&
            leftParenthesisPos != std::string::npos &&
            rightParenthesisPos != std::string::npos) 
        {
            std::string key = line.substr(0, equalPos - 1);
            std::string value1 = line.substr(leftParenthesisPos + 1, commaPos - leftParenthesisPos - 1);
            std::string value2 = line.substr(commaPos + 2, rightParenthesisPos - commaPos - 2);

            mapsLeftRightNavigation[key] = std::make_pair(value1, value2);
        }
    }

    /*for (const auto& pair : mapsLeftRightNavigation) {
        std::cout << "Key: " << pair.first << ", Value: (" << pair.second.first << ", " << pair.second.second << ")" << std::endl;
    }*/

    int step = 0;
    std::string destiny = "AAA";
    char instruction;
    while(destiny != "ZZZ"){
        
        instruction = instructions.front();
        instructions.pop_front();
        instructions.push_back(instruction);

        if(instruction == 'L'){
            destiny = mapsLeftRightNavigation.at(destiny).first;
        }else{
            destiny = mapsLeftRightNavigation.at(destiny).second;            
        }

        step++;
    }

    std::cout << "Steps: " << step << std::endl;
}