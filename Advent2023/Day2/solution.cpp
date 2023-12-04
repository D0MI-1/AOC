#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    int sum = 0;
    int sum2 = 0;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string word;
        std::map<char, int> counter;
        int gameId, value;
        char color;
        bool isPossible = true;

        iss >> word >> gameId;
        iss.ignore(2, ':');

        while (iss >> value >> word) {
            color = word[0];
            counter[color] = std::max(counter[color], value);
            if ((color == 'r' && value > 12) || (color == 'g' && value > 13) || (color == 'b' && value > 14)) {
                isPossible = false;
            }
        }

        int power = counter['r'] * counter['g'] * counter['b'];

        if (isPossible) {
            sum += gameId;
        }
        
        sum2 += power;
    }

    std::cout << "Sum of IDs of possible games: " << sum << std::endl;
    std::cout << "Sum of power of minimum sets: " << sum2 << std::endl;

    return 0;
}