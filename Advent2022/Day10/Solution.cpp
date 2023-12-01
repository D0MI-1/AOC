#include <algorithm>
#include <fstream>
#include <iostream>

  void updateCRT(int count, int X, std::array<std::array<char, 40>, 6> &screen) {
    const auto pixel_id = (count - 1) % 240;
    const auto pixel_row = pixel_id / 40;
    const auto pixel_col = pixel_id % 40;
    // std::cout << "CRT at position: " << pixel_id << " (" << pixel_row << ',' << pixel_col << ')' << '\n';
    if (pixel_col == X || pixel_col == (X - 1) || pixel_col == (X + 1)) {
      screen[pixel_row][pixel_col] = '#';
    } else {
      screen[pixel_row][pixel_col] = '.';
    }
  }

void tick(int &count, int &signalStrength, int &X, std::array<std::array<char, 40>, 6> &screen) {
    count++;
    updateCRT(count, X, screen);
    if ((count - 20) % 40 == 0) {
      signalStrength += count * X;
    }
}

int main(){
    std::ifstream MyFile("Signals.txt");
    std::string items;
    int signalStrength{0};
    int cycleCount{0};
    int registerX{1};
    std::array<std::array<char, 40>, 6> screen = {};


    while (getline(MyFile, items)){
        std::string p1 = items.substr(0,items.find(" "));
        if (p1 == "noop"){
            tick(cycleCount, signalStrength, registerX, screen);
            std::cout << cycleCount << std::endl;
        } else {
            std::string p2 = items.substr(items.find(" ") + 1, items.size() - items.find(" "));
            tick(cycleCount, signalStrength, registerX, screen);
            tick(cycleCount, signalStrength, registerX, screen);
            registerX += stoi(p2);
        }
    }

    std::cout << signalStrength << std::endl;

    for(const auto& row : screen) {
      for (const auto ele : row) {
        std::cout << ele;
      }
      std::cout << '\n';
    }
}