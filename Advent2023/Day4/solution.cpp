#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <regex>
#include <fstream>
#include <queue>

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    
    int sum = 0;

    std::regex leftRegex(":\\s*([\\d\\s]+)\\s*\\|");
    std::regex rightRegex("\\|\\s*([\\d\\s]+)");

    while (std::getline(inputFile, line)) {
        std::vector<int> rightVector;
        std::vector<int> leftVector;

        std::smatch leftMatch;
        if (std::regex_search(line, leftMatch, leftRegex)) {
            std::string leftNumbers = leftMatch[1];

            std::istringstream issLeft(leftNumbers);
            int number;
            while (issLeft >> number) {
                leftVector.push_back(number);
            }
        }

        std::smatch rightMatch;
        if (std::regex_search(line, rightMatch, rightRegex)) {
            std::string rightNumbers = rightMatch[1];

            std::istringstream issRight(rightNumbers);
            int number;
            while (issRight >> number) {
                rightVector.push_back(number);
            }
        }

        std::sort(rightVector.begin(), rightVector.end());
        std::sort(leftVector.begin(), leftVector.end());

        int index1 = 0; 
        int index2 = 0;
        int points = 0;
        bool winningNumbers = false;

        while (index1 < leftVector.size() && index2 < rightVector.size()) {
            if (leftVector[index1] < rightVector[index2]) {
                index1++;
            } else if (leftVector[index1] > rightVector[index2]) {
                index2++;
            } else {
                if (!winningNumbers){
                    points += 1;
                }else{
                    points = points << 1;
                }
                index1++;
                index2++;
                winningNumbers = true;
            }
        }
        if(winningNumbers) {
            sum += points;
        }
    }

    std::cout << sum << std::endl;
    inputFile.close();

    //Part2
    inputFile.open("input.txt");

    std::vector<int> cartCopys(209, 1);
    int sum2 = 0;
    int lineCounter = 0;

    while (std::getline(inputFile, line)) {
        std::vector<int> rightVector;
        std::vector<int> leftVector;

        std::smatch leftMatch;
        if (std::regex_search(line, leftMatch, leftRegex)) {
            std::string leftNumbers = leftMatch[1];

            std::istringstream issLeft(leftNumbers);
            int number;
            while (issLeft >> number) {
                leftVector.push_back(number);
            }
        }

        std::smatch rightMatch;
        if (std::regex_search(line, rightMatch, rightRegex)) {
            std::string rightNumbers = rightMatch[1];

            std::istringstream issRight(rightNumbers);
            int number;
            while (issRight >> number) {
                rightVector.push_back(number);
            }
        }

        std::sort(rightVector.begin(), rightVector.end());
        std::sort(leftVector.begin(), leftVector.end());

        int index1 = 0; 
        int index2 = 0;
        int points = 0;

        while (index1 < leftVector.size() && index2 < rightVector.size()) {
            if (leftVector[index1] < rightVector[index2]) {
                index1++;
            } else if (leftVector[index1] > rightVector[index2]) {
                index2++;
            } else {
                points++;
                index1++;
                index2++;
            }
        }

        int tmp = lineCounter;

        while(points > 0) {
            tmp++;
            std::cout << '-------------------' << std::endl;
            std::cout << tmp << std::endl;
            std::cout << lineCounter << std::endl;
            std::cout << cartCopys.at(tmp) << std::endl;
            std::cout << 'Points ' + points << std::endl;
            cartCopys.at(tmp) += 1 * cartCopys.at(lineCounter);
            std::cout << cartCopys.at(tmp) << std::endl;
            points--;
        }

        lineCounter++;
    }

    for(int num : cartCopys){
        sum2 += num;
    }

    std::cout << sum2 << std::endl;

}