#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> numberDigit = {
    {"one", "o1e"},
    {"two", "t2o"},
    {"three", "t3e"},
    {"four", "f4r"},
    {"five", "f5e"},
    {"six", "s6x"},
    {"seven", "s7n"},
    {"eight", "e8t"},
    {"nine", "n9e"}
};


std::string replaceInput(const std::string& input) {
    std::string result = input;

    for (const auto& pair : numberDigit) {
        size_t pos = result.find(pair.first);

        while (pos != std::string::npos) {
            result.replace(pos, pair.first.length(), pair.second);
            pos = result.find(pair.first, pos + 1);
        }
    }

    return result;
}



int main(){

    std::ifstream MyFile("input.txt");
    std::string line;
    int first = -1;
    int last = -1;
    int sum = 0;

    while (getline(MyFile, line)){
        for (auto c : line){
            if(isdigit(c)){
                if(first == -1){
                    first = c;
                }
                last = c; 
            }
        }

        sum = sum + ((first - '0') * 10 + (last - '0'));
        first = -1;
        last = -1;
    }
    std::cout << "Solution sum :" << std::endl;
    std::cout << sum << std::endl;
    MyFile.close();


    //Part 2
    MyFile.open("input.txt");

    int first2 = -1;
    int last2 = -1;
    int sum2 = 0;

    while (getline(MyFile, line)){
        line = replaceInput(line);
        for (auto c : line){
            if(isdigit(c)){
                if(first2 == -1){
                    first2 = c;
                }
                last2 = c; 
            }
        }
        std::cout << line << std::endl;
        sum2 = sum2 + ((first2 - '0') * 10 + (last2 - '0'));
        first2 = -1;
        last2 = -1;
    }

    std::cout << "Solution sum2 :" << std::endl;
    std::cout << sum2 << std::endl;
    MyFile.close();
}