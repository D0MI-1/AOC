#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>
#include <set>
#include <tuple>

const int INF = INT_MAX;

enum Direction { RIGHT, DOWN, LEFT, UP };

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

auto getAdj(int x, int y, Direction dir, int steps) -> std::vector<std::tuple<int, int, int, Direction>>
{
    std::vector<std::tuple<int, int, int, Direction>> ret;
    if (steps < 10)
        ret.push_back({x + dx[dir], y + dy[dir], steps + 1, dir});
    if (steps >= 4)
    {
        int d = (dir + 1) % 4;
        ret.push_back({x + dx[d], y + dy[d], 1, static_cast<Direction>(d)});
        d = (dir + 3) % 4;
        ret.push_back({x + dx[d], y + dy[d], 1, static_cast<Direction>(d)});
    }
    return ret;
}

auto dijkstra(const std::vector<std::vector<int>>& heatMap) {
    int rows = heatMap.size();
    int cols = heatMap[0].size();

    std::set<std::tuple<int, int, int, int, Direction>> S;
    std::vector<std::vector<std::vector<std::vector<int>>>> dist(rows, 
        std::vector<std::vector<std::vector<int>>>(cols, 
            std::vector<std::vector<int>>(10 + 1, std::vector<int>(4, INT_MAX))));

    for (auto dir : {UP, DOWN, LEFT, RIGHT}) {
        S.insert(std::make_tuple(0, 0, 0, 0, dir));
        dist[0][0][0][dir] = 0;
    }


    while (!S.empty())
        {
            auto [d, x, y, steps, dir] = *S.begin();
            S.erase(S.begin());

            if (d > dist[x][y][steps][dir])
                continue;

            for (auto [nx, ny, nsteps, ndir] : getAdj(x, y, dir, steps))
            {
                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                    continue;

                if (nsteps > 10)
                    continue;

                int weight = heatMap[nx][ny];
                if (dist[nx][ny][nsteps][ndir] > dist[x][y][steps][dir] + weight)
                {
                    dist[nx][ny][nsteps][ndir] = dist[x][y][steps][dir] + weight;
                    S.insert({dist[nx][ny][nsteps][ndir], nx, ny, nsteps, ndir});
                }
            }
        }

        return dist;
    }

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<int>> heatMap;

    while (std::getline(inputFile, line)) {
        std::vector<int> row;

        for (char ch : line) {
            row.push_back(ch - '0');
        }

        heatMap.push_back(row);
    }

    int sol = INT_MAX;

    std::vector<std::vector<std::vector<std::vector<int>>>> dist = dijkstra(heatMap);

    for (auto dir : {UP, DOWN, LEFT, RIGHT}){
        for (int steps = 4; steps <= 10; ++steps){
            sol = std::min(sol, dist[heatMap.size() - 1][heatMap[0].size() - 1][steps][dir]);
        }
    }

        std::cout << "Minimum cost from (0,0) to (" << heatMap.size() - 1 << "," << heatMap[0].size() - 1 << "): " << sol << std::endl;
}