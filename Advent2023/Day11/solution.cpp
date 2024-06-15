#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void expandGalaxies(std::vector<std::string>& universe) {
    int rows = universe.size();
    int cols = universe[0].size();

    std::vector<bool> hasGalaxyRow(rows, false);
    std::vector<bool> hasGalaxyCol(cols, false);

    // Identify rows and columns with galaxies
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (universe[i][j] == '#') {
                hasGalaxyRow[i] = true;
                hasGalaxyCol[j] = true;
            }
        }
    }

    // Duplicate rows without galaxies
    for (int i = 0; i < rows; ++i) {
        if (!hasGalaxyRow[i]) {
            universe.insert(universe.begin() + i, universe[i]);
            hasGalaxyRow.insert(hasGalaxyRow.begin() + i, false);  // Insert a new element in hasGalaxyRow
            ++rows;
            ++i;  // Skip the duplicated row
        }
    }

    // Duplicate columns without galaxies
    for (int j = 0; j < cols; ++j) {
        if (!hasGalaxyCol[j]) {
            for (int i = 0; i < rows; ++i) {
                universe[i].insert(universe[i].begin() + j, universe[i][j]);
            }
            hasGalaxyCol.insert(hasGalaxyCol.begin() + j, false);  // Insert a new element in hasGalaxyCol
            ++cols;
            ++j;  // Skip the duplicated column
        }
    }
}

std::vector<std::pair<int, int>> getGalaxiesPositions(std::vector<std::string>& universe){
    int rows = universe.size();
    int cols = universe[0].size();
    std::vector<std::pair<int, int>> galaxyPositions;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (universe[i][j] == '#') {
                galaxyPositions.push_back(std::make_pair(i, j));
            }
        }
    }

    return galaxyPositions;
}

int manhattanDistance(const std::pair<int,int>& p1, const std::pair<int,int>& p2) {
    return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

std::vector<int> getShortestPath(std::vector<std::pair<int, int>> galaxyPositions){
    std::vector<int> shortestPaths;

    for (int i = 0; i < galaxyPositions.size(); ++i) {
        for (int j = i + 1; j < galaxyPositions.size(); ++j) {
            shortestPaths.push_back(manhattanDistance(galaxyPositions.at(i), galaxyPositions.at(j)));
        }
    }

    return shortestPaths;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::string> universe;

    while (std::getline(inputFile, line)) {
        universe.push_back(line);
    }

    // Expand galaxies in the universe
    expandGalaxies(universe);

    std::vector<std::pair<int, int>> galaxyPositions;

    // Get the position of the galaxy #
    galaxyPositions = getGalaxiesPositions(universe);

    std::vector<int> shortestPaths;

    // Calculate the shortest path of every galaxy
    shortestPaths = getShortestPath(galaxyPositions);

    long long result = 0;

    for(int path : shortestPaths) {
        result += path;
    }

    std::cout << "The sum of the shortest paths: " << result << std::endl;
    /*for (const auto& row : universe) {
        std::cout << row << '\n';
    }*/
}