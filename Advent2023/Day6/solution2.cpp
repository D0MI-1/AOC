#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

std::vector<long long> timeDistanceMatcher(std::vector<long long> time, std::vector<long long> distance)
{
    std::vector<long long> solution;

    for (long long i = 0; i < time.size(); i++)
    {
        long long counter = 0;

        for (size_t j = 1; j < time.at(i); j++)
        {
            if ((j * (time.at(i) - j)) > distance.at(i))
            {
                counter++;
            }
        }

        solution.push_back(counter);
    }

    return solution;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<long long> time;
    std::vector<long long> distance;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line.substr(line.find(":") + 1));
        long long num;
        std::string concatenatedNums;

        while (iss >> num)
        {
            concatenatedNums += std::to_string(num);
        }

        if (line.find("Time:") != std::string::npos)
        {
            time.push_back(std::stoll(concatenatedNums));
        }
        else if (line.find("Distance:") != std::string::npos)
        {
            distance.push_back(std::stoll(concatenatedNums));
        }
    }

    std::vector<long long> solution = timeDistanceMatcher(time, distance);
    long long numberOfWays = 1;

    for (auto const &num : solution)
    {
        numberOfWays *= num;
    }

    std::cout << "Number of Ways to beat the record " << numberOfWays << std::endl;
}