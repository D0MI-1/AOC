#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Sum up all last Numbers from each line to get the last one for our first line
long long nextValue(std::vector<long long> lastNumbers) {
    long long currentNum = lastNumbers.back();

    // Iterate in reverse to calculate the next value
    for (int i = lastNumbers.size() - 2; i >= 0; --i) {
        currentNum = lastNumbers.at(i) - currentNum;
    }

    return currentNum;
}

bool all_zero(std::vector<long long>& vec) {
    for (long long i : vec) {
        if (i != 0) return false;
    }
    return true;
}

// Extrapolate the previous value for each history
long long extrapolate_previous_value(std::vector<std::vector<long long>>& histories) {
    long long sum = 0;

    // Iterate over each history
    for (auto& history : histories) {
        // Vec to store every first number from our line
        std::vector<long long> firstNumbers;
        // We also want the first number from our initial line
        firstNumbers.push_back(history.front());

        while (true) {
            std::vector<long long> differences;
            for (size_t i = 1; i < history.size(); ++i) {
                differences.push_back(history[i] - history[i - 1]);
            }

            // Store the first number of the new sequence
            firstNumbers.push_back(differences.front());

            // Check if we reached all zeros, if not, continue extrapolating
            if (all_zero(differences)) {
                sum += nextValue(firstNumbers);
                break;
            } else {
                history = differences;
            }
        }
    }

    return sum;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<long long>> oasisReport;

    while (std::getline(inputFile, line)) {
        std::vector<long long> lineData;
        std::stringstream lineStream(line);

        long long value;
        while (lineStream >> value) {
            lineData.push_back(value);
        }

        oasisReport.push_back(lineData);
    }

    for (const auto& lineData : oasisReport) {
        for (long long value : lineData) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    long long sum = extrapolate_previous_value(oasisReport);
    std::cout << "The sum of extrapolated values is: " << sum << '\n';

    return 0;
}
