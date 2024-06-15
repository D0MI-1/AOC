#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <deque>
#include <unordered_map>
#include <set>
#include <functional>

std::unordered_map<char, std::vector<std::pair<int, int>>> directions = {
    {'|', {{-1, 0}, {1, 0}}},
    {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}},
    {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}},
    {'F', {{1, 0}, {0, 1}}},
    {'S', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}};

int find_loop_distance(std::vector<std::vector<char>> &field)
{
    int n = field.size(), m = field[0].size();
    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;
    int max_distance = 0;

    std::vector<std::string> a(2 * field.size(), std::string(2 * field[0].size(), '.'));
    for (int i = 0; i < (int)field.size(); i++)
    {
        for (int j = 0; j < (int)field[0].size(); j++)
        {
            a[2 * i][2 * j] = field[i][j];
        }
    }

    n = (int)a.size(); 
    m = (int)a[0].size();

    auto moves = [&](int x, int y) -> std::vector<std::pair<int, int>> {
    char c = a[x][y];
    if (c == 'S') {
      return {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    } else if (c == 'F') {
      return {{0, 1}, {1, 0}};
    } else if (c == 'L') {
      return {{0, 1}, {-1, 0}};
    } else if (c == 'J') {
      return {{0, -1}, {-1, 0}};
    } else if (c == '7') {
      return {{0, -1}, {1, 0}};
    } else if (c == '-') {
      return {{0, -1}, {0, 1}};
    } else if (c == '|') {
      return {{1, 0}, {-1, 0}};
    }
    return {};
  };

    auto possible = [&](int x, int y, int dx, int dy) -> bool
    {
        int nx = x + dx, ny = y + dy;
        if (!(nx >= 0 && nx < n && ny >= 0 && ny < m))
        {
            return false;
        }

        char c = a[nx][ny];
        std::string s = "SFLJ7-|";
        bool ok = false;
        for (char ch : s)
        {
            if (ch == c)
                ok = true;
        }
        if (ok)
        {
            for (auto &[rdx, rdy] : moves(nx, ny))
            {
                if (dx == -rdx && dy == -rdy)
                    return true;
            }
        }
        return false;
    };

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < m; j += 2)
        {
            if (possible(i, j, 0, -1) && possible(i, j, 0, 1))
                a[i][j] = '-';
                std::cout << i << std::endl;

            if (possible(i, j, -1, 0) && possible(i, j, 1, 0))
                a[i][j] = '|';
                std::cout << j << std::endl;

        }
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 1; i < n; i += 2)
        {
            if (possible(i, j, 0, -1) && possible(i, j, 0, 1))
                a[i][j] = '-';

            if (possible(i, j, -1, 0) && possible(i, j, 1, 0))
                a[i][j] = '|';
        }
    }

    int sx = -1;
    int sy = -1;
    std::vector<std::vector<int>> distance(n, std::vector<int>(m, -1));

    // Find the starting position && initialize the queue
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (a[i][j] == 'S')
            {
                q.push({i, j});
                distance[i][j] = 0;
                visited.insert({i, j});
                sx = i;
                sy = j;               
                break;
            }
        }
    }
  

    // Breadth-first search
    while (!q.empty())
    {
        auto [x, y] = q.front();
        // max_distance = std::max(max_distance, distance[x][y]);
        q.pop();
        for (auto [dx, dy] : directions[a[x][y]])
        {
            int nx = x + dx, ny = y + dy;
            if (possible(x, y, dx, dy) && distance[nx][ny] == -1)
            {
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
                visited.insert({nx, ny});
            }
        }
    }

    std::function<void(int, int)> dfs = [&](int x, int y) -> void
    {

        distance[x][y] = 0;
        for (auto [dx, dy] : moves(sx, sy))
        {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && distance[nx][ny] == -1)
            {
                dfs(nx, ny);
            }
        }
    };

    for (int i = 0; i < n; i++)
    {
        int x = i, y = 0;
        if (distance[x][y] == -1)
            dfs(x, y);
        y = m - 1;
        if (distance[x][y] == -1)
            dfs(x, y);
    }

    for (int j = 0; j < m; j++)
    {
        int x = 0, y = j;
        if (distance[x][y] == -1)
            dfs(x, y);
        x = n - 1;
        if (distance[x][y] == -1)
            dfs(x, y);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            max_distance += (distance[i][j] == -1);
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::vector<std::pair<int, int>> nxt = {
                {i, j}, {i + 1, j + 1}, {i + 1, j}, {i, j + 1}};
            int count = 0;
            for (auto &[x, y] : nxt)
            {
                if ((x >= 0 && x < n && y >= 0 && y < m))
                {
                    count += (distance[x][y] == -1);
                }
            }
            if (count == 4)
            {
                res++;
                for (auto &[x, y] : nxt)
                {
                    distance[x][y] = -2;
                }
            }
        }
    }
    max_distance = res;

    return max_distance;
    // return max_distance;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<char>> pipes;

    while (std::getline(inputFile, line))
    {
        std::vector<char> lineChars;
        for (char c : line)
        {
            lineChars.push_back(c);
        }

        pipes.push_back(lineChars);
    }

    /*for (const auto &lineData : pipes)
    {
        for (char c : lineData)
        {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }*/

    int result = find_loop_distance(pipes);
    std::cout << "The maximum distance is: " << result << '\n';

    return 0;
}