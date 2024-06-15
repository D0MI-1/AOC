#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

long long rockCounter(std::vector<char>& row){
    long long counter = 0;
    for(char c : row){
        if(c == 'O'){
            counter++;
        }
    }

    return counter;
}

void tiltPlatform(std::vector<std::vector<char>>& platform) {
    // I think i need to swap the names yikes
    int rows = platform.size();
    int cols = platform[0].size();

    for (int i = 1; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            if (platform[i][j] == 'O') {
                int k = i;

                while (k > 0 && platform[k - 1][j] == '.'){
                    --k;
                }

                platform[k][j] = 'O';
                if(k != i)
                    platform[i][j] = '.';
            }
        }
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::string> board;

    while (std::getline(inputFile, line)) {
        board.push_back(line);
    }

    std::vector<std::vector<char>> platform;

    for (const auto& row : board) {
        std::vector<char> platformRow(row.begin(), row.end());
        platform.push_back(platformRow);
    }

    /*std::cout << "Platform before tilt:\n";
    for (const auto& row : platform) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }*/

    std::vector<std::vector<char>> platformAfterTilt;
    tiltPlatform(platform);

    /*std::cout << "\nPlatform after tilt:\n";
    for (const auto& row : platformAfterTilt) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }*/

    long long sum = 0;
    int j = 0;

    for (int i = platform[0].size(); i >= 0; --i){
        sum += rockCounter(platform[j]) * i;
        j++;
    }

    std::cout << "Total load: " << sum << std::endl;
}