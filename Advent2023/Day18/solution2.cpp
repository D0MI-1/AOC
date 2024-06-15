#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

struct Point
{
    long long x, y;
};

long long calculateArea(const std::vector<Point>& polygon, long long picks) {
    double area = 0.0;
    int j = 0;

    for (int i = 1; i < polygon.size(); i++) {
        area += (polygon[j].y + polygon[i].y) * (polygon[j].x - polygon[i].x);
        j = i;
    }

    return std::abs((area + picks)) / 2.0 + 1;
}

char hexDigitToDirection(char hexDigit) {
    switch (hexDigit) {
        case '0': return 'R';
        case '1': return 'D';
        case '2': return 'L';
        case '3': return 'U';
        default: return 'X';
    }
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<char> directions;
    std::vector<long long> numbers;

    char direction;
    long long number;
    std::string color;
    long long hex;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        while (iss >> direction >> number >> color)
        {
            hex = std::stoi(color.substr(2, 5), nullptr, 16);
            direction = *(color.end() - 2);

            directions.push_back(hexDigitToDirection(direction));
            numbers.push_back(hex);
        }
    }

    std::vector<Point> polygon;
    long long picks = 0;

    polygon.push_back({0, 0});

    for (int i = 0; i < numbers.size(); i++)
    {
        switch (directions[i])
        {
        case 'U':
            polygon.push_back({polygon.back().x, polygon.back().y - numbers[i]});
            picks += numbers[i];
            break;
        case 'D':
            polygon.push_back({polygon.back().x, polygon.back().y + numbers[i]});
            picks += numbers[i];
            break;
        case 'L':
            polygon.push_back({polygon.back().x - numbers[i], polygon.back().y});
            picks += numbers[i];            
            break;
        case 'R':
            polygon.push_back({polygon.back().x + numbers[i], polygon.back().y});
            picks += numbers[i];            
            break;
        }
    }

    std::cout << std::endl;

    long long area = calculateArea(polygon, picks);

    std::cout << "The are of the polygon is: " << area << std::endl;
}