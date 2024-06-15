#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <deque>
#include <unordered_map>
#include <set>

std::unordered_map<char, std::vector<std::pair<int, int>>> directions = {
    {'|', {{-1, 0}, {1, 0}}},
    {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}},
    {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}},
    {'F', {{1, 0}, {0, 1}}},
    {'S', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}
};

int find_loop_distance(std::vector<std::vector<char>>& field) {
    int n = field.size(), m = field[0].size();
    std::vector<std::vector<int>> distance(n, std::vector<int>(m, -1));
    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;
    int max_distance = 0;

    // Find the starting position and initialize the queue
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == 'S') {
                q.push({i, j});
                distance[i][j] = 0;
                visited.insert({i, j});
                break;
            }
        }
    }

    auto possible = [&](int x, int y, int dx, int dy) -> bool {
        int nx = x + dx, ny = y + dy;
        if (!(nx >= 0 && nx < n && ny >= 0 && ny < m)){
            return false;
        }

        char c = field[nx][ny];
        std::string s = "FLJ7-|";
        bool ok = false;
        for (char ch : s) {
            if (ch == c)
                ok = true;
        }
        if (ok) {
            for (auto &[rdx, rdy] : directions[field[nx][ny]]) {
                if (dx == -rdx and dy == -rdy)
                    return true;
            }
        }
    return false;
  };

    // Breadth-first search
    while (!q.empty()) {
        auto [x, y] = q.front();
        max_distance = std::max(max_distance, distance[x][y]);
        q.pop();
        for (auto [dx, dy] : directions[field[x][y]]) {
            int nx = x + dx, ny = y + dy;
                if (possible(x, y, dx, dy) and distance[nx][ny] == -1) {
                    distance[nx][ny] = distance[x][y] + 1;
                    q.push({nx, ny});
                    visited.insert({nx, ny});
                }
        }
    }

    return max_distance;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<char>> pipes;

    while (std::getline(inputFile, line)) {
        std::vector<char> lineChars;
        for (char c : line) {
            lineChars.push_back(c);
        }

        pipes.push_back(lineChars);
    }

    for (const auto &lineData : pipes) {
        for (char c : lineData) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }

    int result = find_loop_distance(pipes);
    std::cout << "The maximum distance is: " << result << '\n';

    return 0;
}