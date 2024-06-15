#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

// Function to rotate the board 90 degrees clockwise
std::vector<std::string> rotate(const std::vector<std::string>& board) {
    std::vector<std::string> rotated;
    for (size_t i = 0; i < board[0].size(); ++i) {
        std::string row;
        for (const auto& r : board) {
            row.push_back(r[i]);
        }
        std::reverse(row.begin(), row.end());
        rotated.push_back(row);
    }
    return rotated;
}

int getReflection(const std::vector<std::string> &note) {
    int maxReflection {0};

    for (int i = 0; i < note.size() - 1; ++i) {
        int j {0};
        int currReflection {0};

        while (i - j >= 0 && i + j + 1 < note.size() && note[i - j] == note[i + j + 1]) {
            ++currReflection;
            ++j;
        }

        if (i - j + 1 == 0 || i + j + 1 == note.size()) {
            maxReflection = std::max(maxReflection, currReflection + i - j + 1);
        }
    }

    return maxReflection;
}

bool fixSmudge(std::string_view line1, std::string_view line2) {
  bool updated{false};
  for (int i = 0; i < line1.size(); ++i) {
    if (line1[i] != line2[i]) {
      if (updated) {
        return false;
      } else {
        updated = true;
      }
    }
  }

  return true;
}

int getReflection2(const std::vector<std::string> &note) {
  int maxReflection {0};
  for (int i = 0; i < note.size() - 1; ++i) {
    int j {0};
    int currReflection{0};
    bool updated{false};
    while (i - j >= 0 && i + j + 1 < note.size()) {
      if (note[i - j] == note[i + j + 1]) {
        ++currReflection;
      } else if (!updated && fixSmudge(note[i - j], note[i + j + 1])) {
        updated = true;
        ++currReflection;
      } else {
        break;
      }

      ++j;
    }

    if ((i - j + 1 == 0 || i + j + 1 == note.size()) && updated) {
      maxReflection = std::max(maxReflection, currReflection + i - j + 1);
    }
  }

  return maxReflection;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<std::string>> boards;
    std::vector<std::string> board;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            boards.push_back(board);
            board.clear();
        } else {
            board.push_back(line);
        }
    }
    // Push the last board
    if (!board.empty()) {
        boards.push_back(board);
    }

    int total {0};
    for (const auto& board : boards) {
        total += getReflection(board) * 100 + getReflection(rotate(board));
    }

    int total2 {0};
    for (const auto& board : boards) {
        total2 += getReflection2(board) * 100 + getReflection2(rotate(board));
    }
    std::cout << "The total is: " << total << std::endl;
    std::cout << "The total2 is: " << total2 << std::endl;
}
