#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

std::vector<int> timeDistanceMatcher(std::vector<int> time, std::vector<int> distance)
{
    std::vector<int> solution;

    for (size_t i = 0; i < time.size(); i++)
    {
        int counter = 0;

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
    std::regex rgx("\\b\\d+\\b");
    std::vector<int> time;
    std::vector<int> distance;

    while (std::getline(inputFile, line))
    {
        std::smatch match;

        if (line.find("Time:") != std::string::npos)
        {
            while (std::regex_search(line, match, rgx))
            {
                time.push_back(std::stoi(match[0]));
                line = match.suffix().str();
            }
        }
        else
        {
            while (std::regex_search(line, match, rgx))
            {
                distance.push_back(std::stoi(match[0]));
                line = match.suffix().str();
            }
        }
    }

    std::vector<int> solution = timeDistanceMatcher(time, distance);
    int numberOfWays = 1;

    for (auto const &num : solution)
    {
        numberOfWays *= num;
    }

    std::cout << "Number of Ways to beat the record " << numberOfWays << std::endl;
}