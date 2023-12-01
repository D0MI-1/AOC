#include <iostream>
#include <fstream>
#include <unordered_map>


void task1(){
    std::ifstream MyFile("Signal.txt");
    std::string signal;
    getline(MyFile, signal);
    std::unordered_map<char,int> s;

    for (size_t i = 0; i < 3; i++)
    {
        s[signal[i]] += 1;
    }

    for (size_t i = 3; i < signal.size(); i++)
    {
        s[signal[i]] += 1;

        if (s.size() == 4){
            std::cout << i + 1 << std::endl;
            break;
        }

        s[signal[i - 3]] -= 1;
        if (s[signal[i - 3]] == 0){
            s.erase(signal[i - 3]);
        }
    }  
}

void task2(){
    std::ifstream MyFile("Signal.txt");
    std::string signal;
    getline(MyFile, signal);
    std::unordered_map<char,int> s;

    for (size_t i = 0; i < 13; i++)
    {
        s[signal[i]] += 1;
    }

    for (size_t i = 13; i < signal.size(); i++)
    {
        s[signal[i]] += 1;

        if (s.size() == 14){
            std::cout << i + 1 << std::endl;
            break;
        }

        s[signal[i - 13]] -= 1;
        if (s[signal[i - 13]] == 0){
            s.erase(signal[i - 13]);
        }
    }    
}

int main(){
    task1();
    task2();  
}