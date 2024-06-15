#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

long long hashCalc(std::string& str) {
    long long currentValue {0};

    for (char& c : str) {
        long long asciiCode = static_cast<long long>(c);

        currentValue += asciiCode;

        currentValue *= 17;

        currentValue %= 256;
    }
    std::cout << "string Value: " << currentValue << std::endl;
    
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

    long long allValues = 0;

    for(std::string& str : initializationSequence){
        allValues += hashCalc(str);
    }

    std::cout << "The hash value is : " << allValues << std::endl;
}