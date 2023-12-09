#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Sum up all last Numbers from each line to get the last one for our first line
long long nextValue(std::vector<long long> lastNumbers){
    long long currentNum = 0;

    for (auto num : lastNumbers){
        currentNum += num;
    }
    return currentNum;
}

//Check if a whole line is 0
bool all_zero(std::vector<long long>& vec) {
    for (long long i : vec) {
        if (i != 0) return false;
    }
    return true;
}

long long extrapolate_next_value(std::vector<std::vector<long long>>& histories) {
    long long sum = 0;
    // Take all lines from input
    for (auto& history : histories) {
        // Vec to store every last number from our line
        std::vector<long long> lastNumbers;
        // We also want the last number from our initial line
        lastNumbers.push_back(history.back());
        while (true) {
            std::vector<long long> differences;
            for (size_t i = 1; i < history.size(); ++i) {
                differences.push_back(history[i] - history[i - 1]);
            }

            lastNumbers.push_back(differences.back());

            // Check if we already reached all 0 if not extrapolate another line
            if (all_zero(differences)) {
                sum += nextValue(lastNumbers);
                break;
            } else {
                history = differences;
            }
        }
    }
    return sum;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<long long>> oasisReport;

    while(std::getline(inputFile, line))
    {
        std::vector<long long> lineData;
        std::stringstream lineStream(line);

        long long value;
        while (lineStream >> value)
        {
            lineData.push_back(value);
        }

        oasisReport.push_back(lineData);
    }

    for (const auto &lineData : oasisReport) {
        for (long long value : lineData) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    long long sum = extrapolate_next_value(oasisReport);
    std::cout << "The sum of extrapolated values is: " << sum << '\n';
}