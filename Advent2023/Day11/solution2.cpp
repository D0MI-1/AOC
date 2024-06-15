#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::pair<std::vector<bool>, std::vector<bool>> expandGalaxies(std::vector<std::string>& universe) {
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

    return {hasGalaxyRow, hasGalaxyCol};
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

std::vector<int> getShortestPath(const std::vector<std::pair<int, int>>& galaxyPositions, const std::vector<bool>& hasGalaxyRow, const std::vector<bool>& hasGalaxyCol) {
    std::vector<int> shortestPaths;

    for (int i = 0; i < galaxyPositions.size(); ++i) {
        for (int j = i + 1; j < galaxyPositions.size(); ++j) {
            int x1 = galaxyPositions[i].first;
            int y1 = galaxyPositions[i].second;
            int x2 = galaxyPositions[j].first;
            int y2 = galaxyPositions[j].second;

            // Adjust the Manhattan distance calculation for expanded rows
            int expandedRows = 0;
            for (int k = std::min(x1, x2); k <= std::max(x1, x2); ++k) {
                if (!hasGalaxyRow[k]) {
                    expandedRows += 1;
                }
            }

            // Adjust the Manhattan distance calculation for expanded columns
            int expandedCols = 0;
            for (int k = std::min(y1, y2); k <= std::max(y1, y2); ++k) {
                if (!hasGalaxyCol[k]) {
                    expandedCols += 1;
                }
            }

            shortestPaths.push_back(manhattanDistance(galaxyPositions[i], galaxyPositions[j]) + (expandedRows + expandedCols) * (1000000 - 1));
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

    // Expand galaxies in the universe and get the Row and Column bool vectors
    auto [hasGalaxyRow, hasGalaxyCol] = expandGalaxies(universe);

    std::vector<std::pair<int, int>> galaxyPositions;

    // Get the position of the galaxy #
    galaxyPositions = getGalaxiesPositions(universe);

    std::vector<int> shortestPaths;

    // Calculate the shortest path of every galaxy
    shortestPaths = getShortestPath(galaxyPositions, hasGalaxyRow, hasGalaxyCol);

    long long result = 0;

    for(int path : shortestPaths) {
        result += path;
    }

    std::cout << "The sum of the shortest paths: " << result << std::endl;
    /*for (const auto& row : universe) {
        std::cout << row << '\n';
    }*/
}