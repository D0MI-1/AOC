#include <iostream>
#include <vector>
#include <fstream>

enum Direction { UP, DOWN, LEFT, RIGHT };

auto updateDirection = [](Direction current, char mirror) -> Direction {
    switch (mirror) {
        case '/':
            return (current == UP) ? RIGHT : (current == DOWN) ? LEFT : (current == LEFT) ? DOWN : (current == RIGHT) ? UP : current;
        case '\\':
            return (current == UP) ? LEFT : (current == DOWN) ? RIGHT : (current == LEFT) ? UP : (current == RIGHT) ? DOWN : current;
        default:
            return current;
    }
};

long long simulateBeam(std::vector<std::string> contraption, int startX, int startY, Direction startDirection) {
    int rows = contraption.size();
    int cols = contraption[0].size();

    std::vector<std::vector<bool>> energized(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<std::vector<Direction>>> visited(rows, std::vector<std::vector<Direction>>(cols));
    std::vector<std::pair<int, int>> position;
    std::vector<Direction> directions;

    int x = startX;
    int y = startY;
    Direction direction = startDirection;

    position.push_back(std::make_pair(x, y));
    directions.push_back(direction);

    while (!position.empty()) {
        std::pair<int, int> pos = position.back();
        position.pop_back();

        x = pos.first;
        y = pos.second;

        direction = directions.back();
        directions.pop_back();

        while (x >= 0 && x < rows && y >= 0 && y < cols) {
            bool visitedWithDir = false;
            char currentTile = contraption[x][y];

            energized[x][y] = true;

            for (auto vis : visited[x][y]) {
                if (vis == direction)
                    visitedWithDir = true;
            }

            if (visitedWithDir == false) {
                visited[x][y].push_back(direction);
            } else {
                break;
            }

            switch (currentTile) {
                case '.':
                    break;
                case '/':
                    direction = updateDirection(direction, currentTile);
                    break;
                case '\\':
                    direction = updateDirection(direction, currentTile);
                    break;
                case '|':
                    if (direction == LEFT || direction == RIGHT) {
                        direction = UP;

                        position.push_back(std::make_pair(x++, y));
                        directions.push_back(DOWN);
                    }
                    break;
                case '-':
                    if (direction == UP || direction == DOWN) {
                        direction = LEFT;

                        position.push_back(std::make_pair(x, y++));
                        directions.push_back(RIGHT);
                    }
                    break;
                default:
                    break;
            }

            switch (direction) {
                case UP:
                    x--;
                    break;
                case DOWN:
                    x++;
                    break;
                case LEFT:
                    y--;
                    break;
                case RIGHT:
                    y++;
                    break;
            }
        }
    }

    int energizedCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (energized[i][j]) {
                energizedCount++;
            }
        }
    }

    return energizedCount;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::string> contraption;

    while (std::getline(inputFile, line)) {
        contraption.push_back(line);
    }

    int rows = contraption.size();
    int cols = contraption[0].size();

    long long maxEnergizedTiles = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                for (Direction dir : {UP, DOWN, LEFT, RIGHT}) {
                    long long energizedTiles = simulateBeam(contraption, i, j, dir);

                    if (energizedTiles > maxEnergizedTiles) {
                        maxEnergizedTiles = energizedTiles;
                    }
                }
            }
        }
    }

    std::cout << "Max Energized Tiles: " << maxEnergizedTiles << std::endl;

    return 0;
}
