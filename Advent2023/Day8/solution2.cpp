#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <sstream>
#include <deque>
#include <unordered_map>
#include <numeric>

auto loopLength(std::string start, std::deque<char> instructions, 
std::unordered_map<std::string, std::pair<std::string, std::string>> mapsLeftRightNavigation)
{   
    std::string currentNode = start;
    std::unordered_map<std::string, int> visited;

    // find end node with ??Z
    while (currentNode.back() != 'Z') {
        char instruction = instructions.front();
        instructions.pop_front();
        instructions.push_back(instruction);
        visited[currentNode] = 1;
        if (instruction == 'L'){
            currentNode = (mapsLeftRightNavigation.at(currentNode).first);
        }else{
            currentNode = (mapsLeftRightNavigation.at(currentNode).second);
        }   
    }

    std::string endNode = currentNode;

    // count number of steps to get to that end node again
    auto step = 0;
    while (visited[currentNode] == 1 && currentNode != endNode || step == 0) {
        char instruction = instructions.front();
        instructions.pop_front();
        instructions.push_back(instruction);

        ++step;
        if (instruction == 'L'){
            currentNode = (mapsLeftRightNavigation.at(currentNode).first);
        }else{
            currentNode = (mapsLeftRightNavigation.at(currentNode).second);
        }    
    }

    return step; 
}

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

    //Get all nodes with A at the end
    std::vector<std::string> startNodes;
    for (const auto& pair : mapsLeftRightNavigation) {
        if (pair.first.back() == 'A') {
            startNodes.push_back(pair.first);
        }
    }

    //Get the length of the loop
    std::vector<long long> loopLengths;
    for (const auto& startNode : startNodes) {
        loopLengths.push_back(loopLength(startNode, instructions, mapsLeftRightNavigation));
    }

    //Calculate least common multiple with every loop length from our vector
    long long totalLCM = 1;
    for(const auto& loop : loopLengths) {
        totalLCM = std::lcm(totalLCM, loop);
    }
    std::cout << "Least Common Multiple of loop lengths: " << totalLCM << std::endl;
}