#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct Point
{
    double x, y;
};

double calculateArea(const std::vector<Point>& polygon, double picks) {
    double area = 0.0;
    int j = 0;

    for (int i = 1; i < polygon.size(); i++) {
        area += (polygon[j].y + polygon[i].y) * (polygon[j].x - polygon[i].x);
        j = i;
    }

    return std::abs((area + picks)) / 2.0 + 1;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<char> directions;
    std::vector<int> numbers;

    char direction;
    int number;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        while (iss >> direction >> number)
        {
            directions.push_back(direction);
            numbers.push_back(number);
        }
    }

    std::vector<Point> polygon;
    double picks = 0;

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

    for (const auto& point : polygon) {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }
    std::cout << std::endl;

    double area = calculateArea(polygon, picks);

    std::cout << "The are of the polygon is: " << area << std::endl;
}