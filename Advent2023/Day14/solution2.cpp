#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <unordered_map>

struct VectorHash {
    std::size_t operator()(const std::vector<std::vector<char>>& vec) const {
        std::size_t hash = 0;
        for (const auto& row : vec) {
            for (char c : row) {
                hash ^= std::hash<char>{}(c) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
        }
        return hash;
    }
};

long long rockCounter(std::vector<char>& row){
    long long counter = 0;
    for(char c : row){
        if(c == 'O'){
            counter++;
        }
    }

    return counter;
}

void tiltPlatformInAllDir(std::vector<std::vector<char>>& platform) {
    int rows = platform.size();
    int cols = platform[0].size();

    // North
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

    // West
    for (int i = 0; i < rows; ++i){
        for (int j = 1 ; j < cols; ++j){
            if (platform[i][j] == 'O') {
                int k = j;

                while (k > 0 && platform[i][k - 1] == '.'){
                    --k;
                }

                platform[i][k] = 'O';
                if(k != j)
                    platform[i][j] = '.';
            }
        }
    }    

    // South
    for (int i = rows - 2; i >= 0; --i){
        for (int j = 0; j < cols; ++j){
            if (platform[i][j] == 'O') {
                int k = i;

                while (k < (rows - 1) && platform[k + 1][j] == '.'){
                    ++k;
                }

                platform[k][j] = 'O';
                if(k != i)
                    platform[i][j] = '.';
            }
        }
    }    

    // East
    for (int i = 0; i < rows; ++i){
        for (int j = cols - 2; j >= 0; --j){
            if (platform[i][j] == 'O') {
                int k = j;

                while (k < cols - 1 && platform[i][k + 1] == '.'){
                    ++k;
                }

                platform[i][k] = 'O';
                if(k != j)
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

    // i just skip the first 69 objects that are not a cycle and then just get the cycle number
    for (int i = 0; i < 69; i++){
        int j = 0;
        long long sum = 0;
        tiltPlatformInAllDir(platform);
        for (int i = platform[0].size(); i >= 0; --i){
            sum += rockCounter(platform[j]) * i;
            j++;
        }

        std::cout << sum << "; ";
    }

    std::unordered_map<std::vector<std::vector<char>>, long long, VectorHash> platformLoads;

    long long cycles = 0;
    long long cycleStart = 0;
    long long cycleLength = 0;

    while (cycles < (1000000000 - 0)) {
        tiltPlatformInAllDir(platform);

        // Calculate the total load
        long long sum = 0;
        int j = 0;

        for (int i = platform[0].size(); i >= 0; --i) {
            sum += rockCounter(platform[j]) * i;
            j++;
        }

        // Check for repetition
        if (platformLoads.find(platform) != platformLoads.end()) {
            cycleStart = platformLoads[platform];
            cycleLength = cycles - cycleStart;
            break;
        }

        // Save the current platform and its total load
        platformLoads[platform] = cycles;

        cycles++;
    }

        // Calculate the remaining cycles
    long long remainingCycles = (1000000000 - 0) - cycleStart;

    // Perform tilting for the remaining cycles
    for (long long i = 0; i < remainingCycles % cycleLength; ++i) {
        tiltPlatformInAllDir(platform);
    }

    // Calculate the total load after all cycles
    int j = 0;
    long long sum = 0;

    for (int i = platform[0].size(); i >= 0; --i) {
        sum += rockCounter(platform[j]) * i;
        j++;
    }

    std::cout << "Total load after 1000000000 cycles: " << sum << std::endl;
    
    // 95274 too high
    // 95269 too low 
}