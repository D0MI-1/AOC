#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

long long hashCalc(std::string& str) {
    long long currentValue {0};

    for (char& c : str) {
        if (c >= 'a' && c <= 'z'){
            long long asciiCode = static_cast<long long>(c);

            currentValue += asciiCode;

            currentValue *= 17;

            currentValue %= 256;
        }
    }    
    return currentValue;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::string> initializationSequence;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ',')) {
            initializationSequence.push_back(token);
        }
    }

    /*for (const auto& str : initializationSequence) {
        std::cout << str << std::endl;
    }*/

    std::vector<std::vector<std::pair<std::string, int>>> boxes(256);

    for(std::string& str : initializationSequence){
        long long hashValue = 0;

        int hash = 0, i;
        for (i = 0; str[i] != '=' && str[i] != '-'; i++) {
            hash += str[i];
            hash *= 17;
            hash %= 256;
        }
        if (str[i] == '-') {
            for (int j = 0; j < boxes[hash].size(); j++) {
                if (boxes[hash][j].first == str.substr(0, str.size() - 1)) {
                    boxes[hash].erase(
                        boxes[hash].begin() + j);
                    break;
                }
            }        
        } else {
            int fl = str[i + 1] - '0', j;
            for (j = 0; j < boxes[hash].size(); j++) {
                if (boxes[hash][j].first == str.substr(0, str.size() - 2)) {
                    boxes[hash][j].second = fl;
                    break;
                }
            }
            if (j == boxes[hash].size()) {
                boxes[hash].push_back({str.substr(0, str.size() - 2), fl});
            }
        }
    }
    
    int p2 = 0;
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            p2 += (i + 1) * (j + 1) * boxes[i][j].second;
        }
    }

    std::cout << p2 << std::endl;
}