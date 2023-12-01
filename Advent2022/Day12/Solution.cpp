#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>

#define valid(i, j, m, n) (i >= 0 && i < m && j >= 0 && j < n)

constexpr int dx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
constexpr int dy[] = {0, -1, 1, 0, -1, 1, -1, 1};

int main()
{
    std::ifstream MyFile("Hill.txt");
    std::string line;
    int path{0};

    std::vector<std::string> lines;

    while (getline(MyFile, line))
    {
        lines.push_back(line);
    }

    long unsigned int m {lines.size()};
    long unsigned int n {lines[0].size()};

    int Si, Sj, Ei, Ej;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (lines[i][j] == 'S')
            {
                Si = i;
                Sj = j;
            }
            if (lines[i][j] == 'E')
            {
                Ei = i;
                Ej = j;
            }
        }
    }

    lines[Si][Sj] = 'a';
    lines[Ei][Ej] = 'z';

    auto solve = [&]() -> int
    {
        int ans = 0;
        std::vector<std::vector<bool>> visited (m, std::vector<bool>(n));
        std::queue<std::pair<int, int>> q;
        //Change if you want to Start from Si Sj
        q.push({Ei, Ej});
        while (!q.empty())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [i, j] = q.front();
                q.pop();
                // Change to for Task1 
                //i == Si && j == Sj
                //i == Ei && j == Ej
                if (lines[i][j] == lines[Si][Sj])
                {
                    return ans;
                }

                for (int k = 0; k < 4; k++)
                {
                    int i2 {i + dx[k]};
                    int j2 {j + dy[k]};
                    // Change to lines[i2[j2] - lines[i][j] > 1 for Si Sj]
                    if (!valid(i2, j2, m, n) 
                    || lines[i][j] - lines[i2][j2] > 1 
                    || visited[i2][j2])
                    {
                        continue;
                    }

                    visited[i2][j2] = true;
                    q.push({i2, j2});
                }
            }
            ans++;
        }
    };
        std::cout << solve() << std::endl;
}