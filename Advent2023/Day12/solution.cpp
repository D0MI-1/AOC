#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

//   3  1  3
//   ???.### 1,1,3
long long calcCombinationsHelper(std::vector<char>& spring, std::vector<long long>& damagedGroup, long long i, long long j, long long cur, std::vector<std::vector<std::vector<long long>>>& memo) {
    if (i >= spring.size()) {
        return j == damagedGroup.size();
    }

    if (memo[i][j][cur] != -1) {
        return memo[i][j][cur];
    }

    long long res = 0;

    // Case 1: place a '.'
    if ((spring[i] == '.' || spring[i] == '?') && cur == 0) {
        res += calcCombinationsHelper(spring, damagedGroup, i + 1, j, 0, memo);
    }

    // Case 2: place a '#' and check damagedGroup
    if ((spring[i] == '#' || spring[i] == '?') && j < damagedGroup.size()) {
        if (cur + 1 == damagedGroup[j]) {
            res += (i + 1 == spring.size() || spring[i + 1] != '#') * calcCombinationsHelper(spring, damagedGroup, i + 2, j + 1, 0, memo);
        } else {
            res += calcCombinationsHelper(spring, damagedGroup, i + 1, j, cur + 1, memo);
        }
    }

    memo[i][j][cur] = res;
    return res;
}

long long calcCombinations(std::vector<char> spring, std::vector<long long> damagedGroup, long long totalArrangements){
    long long n = spring.size();
    long long m = damagedGroup.size();
    std::vector<std::vector<std::vector<long long>>> memo(n, std::vector<std::vector<long long>>(m + 1, std::vector<long long>(n + 1, -1)));

    totalArrangements = calcCombinationsHelper(spring, damagedGroup, 0, 0, 0, memo);
    
    return totalArrangements;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    long long totalArrangements = 0;

    std::vector<std::vector<char>> allSprings;
    std::vector<std::vector<long long>> allDamagedGroups;

    while (std::getline(inputFile, line)) {
        std::vector<char> springs;
        std::vector<long long> damagedGroups;

        // Use std::istringstream to parse the line
        std::istringstream iss(line);

        // Read the spring string
        std::string springString;
        iss >> springString;

        // Read the damaged groups
        long long damagedGroup;
        while (iss >> damagedGroup) {
            damagedGroups.push_back(damagedGroup);

            // Check if the next character is ',' and ignore it
            if (iss.peek() == ',') {
                iss.ignore();
            }
        }

        // Convert the spring string to a vector of characters
        for (char c : springString) {
            springs.push_back(c);
        }

        
        std::vector<char> copiedVector = springs;


        /////////////////////////////////////////////////////////////////////////////////
        //Part 2
        // Append the copied vector to itself 5 times
        for (int i = 0; i < 4; ++i) {
            copiedVector.push_back('?');
            copiedVector.insert(copiedVector.end(), springs.begin(), springs.end());
        }

        std::vector<long long> copiedVector2 = damagedGroups;
        for (int i = 0; i < 4; ++i) {
            copiedVector2.insert(copiedVector2.end(), damagedGroups.begin(), damagedGroups.end());
        }

        allSprings.push_back(copiedVector);
        allDamagedGroups.push_back(copiedVector2);
        /////////////////////////////////////////////////////////////////////////////////
        // Part 1
        /*allSprings.push_back(springs);
        allDamagedGroups.push_back(damagedGroups);*/
    }

    for(long long i = 0; i < allSprings.size(); i++){
        totalArrangements += calcCombinations(allSprings[i], allDamagedGroups[i], 0);
    }

    std::cout << "Combinations : " << totalArrangements << std::endl;
}
