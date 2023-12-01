#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <queue>

void astar(std::unordered_map<std::string, std::pair<int, std::vector<std::string>>> nodes){
  std::queue<std::string> openQueue;
  openQueue.push("AA");
  std::unordered_map<std::string> cameFrom;
}

int main(){
    std::ifstream MyFile("Input.txt");
    std::string line;
    std::unordered_map<std::string, std::pair<int, std::vector<std::string>>> nodes;

    const std::regex pattern(R"(Valve (..) has flow rate=(\d+); tunnels? leads? to valves? (.+))");
    std::smatch match;

    while (getline(MyFile, line)){

      std::regex_match(line, match, pattern);
      std::string path = match[3];

      std::stringstream ss(path);
      std::string st;
      std::vector<std::string> paths;

      while (ss >> st) {
          if (*st.rbegin() == ',') st = st.substr(0, st.size() - 1);
          paths.emplace_back(st);
      }
      std::pair<int, std::vector<std::string>> p(stoi(match[2]), paths);
      nodes.emplace(match[1],p);
      //std::cout << match[1] << std::endl;
      //std::cout << match[2] << std::endl;
      //std::cout << match[3] << std::endl;
    }
    /*std::cout << nodes.at("VB").first << std::endl;
    std::cout << nodes.at("VB").second.size() << std::endl;
    std::cout << nodes.at("VB").second.at(0) << std::endl;
    std::cout << nodes.at("VB").second.at(1) << std::endl;*/
    astar(nodes);
}