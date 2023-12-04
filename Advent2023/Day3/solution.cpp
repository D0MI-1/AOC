#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <regex>
#include <fstream>

int main() {
    std::vector<std::string> T;
    std::string line;
    std::ifstream inputFile("input.txt");
    int sum = 0;
    int sum2 = 0;

    while (std::getline(inputFile, line)) {
        T.push_back(line);
    }

    std::vector<std::pair<int, std::set<std::pair<int, int>>>> N;
    std::set<std::pair<int, int>> P;

    for (int i = 0; i < T.size(); ++i) {
        std::regex regex("\\d+");
        std::sregex_iterator iter(T[i].begin(), T[i].end(), regex);
        std::sregex_iterator end;

        while (iter != end) {
            auto m = *iter;
            N.emplace_back(std::stoi(m.str(0)),
                           std::set<std::pair<int, int>>());
            auto& pos = N.back().second;

            for (int x = i - 1; x <= i + 1; ++x) {
                for (int y = m.position() - 1; y <= m.position() + m.length(); ++y) {
                    pos.emplace(x, y);
                }
            }

            ++iter;
        }
    }

    for (int i = 0; i < T.size(); ++i) {
        for (int j = 0; j < T[i].size(); ++j) {
            if (P.find({i, j}) == P.end() && !isdigit(T[i][j]) && T[i][j] != '.') {
                P.emplace(i, j);
            }
        }
    }

    int total1 = 0;
    int total2 = 0;

    for (const auto& entry : N) {
        if (std::any_of(P.begin(), P.end(), [&](const auto& x) {
            return entry.second.find(x) != entry.second.end();
        })) {
            total1 += entry.first;
        }
    }

    for (const auto& entry : P) {
        if (T[entry.first][entry.second] == '*' &&
            std::count_if(N.begin(), N.end(), [&](const auto& n) {
                return n.second.find(entry) != n.second.end();
            }) == 2) {
            int product = 1;
            for (const auto& n : N) {
                if (n.second.find(entry) != n.second.end()) {
                    product *= n.first;
                }
            }
            total2 += product;
        }
    }

    std::cout << total1 << " " << total2 << std::endl;

    return 0;
}
