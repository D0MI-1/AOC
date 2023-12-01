#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <sstream>
#include <memory>

struct File {
   std::string filename;   
   long long size;
};

struct Directory{
    std::string dirname;
    std::vector<std::unique_ptr<File>> files;
    std::vector<std::unique_ptr<Directory>> dirs;
    Directory *parent;
    long long size;
};

std::vector<std::string> split(std::string input){
    std::stringstream inputStream(input);
    std::string s;
    std::vector<std::string> result;

    while (getline(inputStream, s, ' ')) {
        result.push_back(s);
    }

    return result;
}

long long update_dir_size(Directory * main_dir) {
  for (const auto& dir : main_dir->dirs) {
    main_dir->size += update_dir_size(dir.get());
  }
  for (const auto& file : main_dir->files) {
    main_dir->size += file->size;
  }
  return main_dir->size;
}

std::tuple<long long, long long> count_dirs_lte_threshold(Directory * main_dir, long long threshold) {
  long long sum = 0;
  long long count = 0;
  for (const auto& dir : main_dir->dirs) {
    if (dir->size <= threshold) {
      std::cout << dir->dirname << '\n';
      count++;
      sum += dir->size;
    }
    const auto ans = count_dirs_lte_threshold(dir.get(), threshold);
    count += std::get<0>(ans);
    sum += std::get<1>(ans);
  }
  return {count, sum};
}

long long find_directory_gte(Directory * main_dir, long long threshold) {
  auto min = main_dir->size;
  for (const auto& dir : main_dir->dirs) {
    if (dir->size > threshold) {
      const auto min_above_thresh = find_directory_gte(dir.get(), threshold);
      min = std::min(min, min_above_thresh);
    }
  }
  return min;
}

int main(){
    std::ifstream MyFile("Input.txt");
    std::string items;
    int score{0};
    int score2{0};
    std::unique_ptr<Directory> file_system = std::make_unique<Directory>();
    file_system -> dirname = '/';
    file_system -> parent = file_system.get();
    auto current = file_system.get();
    bool skip = false;

    while (skip || getline(MyFile, items)){
        skip = false;
        auto itemsVector = split(items);
        if (itemsVector.at(0) == "$"){
            const auto cmd = itemsVector.at(1); 
            if (cmd == "cd"){
                if (itemsVector.at(2) == "..") current = current->parent;
                else if (itemsVector.at(2) == "/") current = file_system.get();
                else{
                    bool found = false;
                    for (const auto& dir : current->dirs){
                        if (dir->dirname == itemsVector.at(2)){
                            current = dir.get();
                            found = true;
                            std::cout << "Current dir is now: " << current->dirname << '\n';
                            break;
                        }
                    }

                    if (!found){
                        current->dirs.emplace_back();
                        current->dirs.back()->dirname = itemsVector.at(2);
                        current->dirs.back()->parent = current;
                        current = current->dirs.back().get();  
                        std::cout << "Current dir is now: " << current->dirname << '\n';                      
                    }
                }
            } else if (cmd == "ls"){
                while(std::getline(MyFile, items)){
                    auto itemsVector = split(items);
                    if (itemsVector.at(0) == "dir"){
                        const auto dir_name = itemsVector.at(1);
                        bool found = false;
                        for (const auto& dir : current->dirs){
                            if (dir->dirname == dir_name){
                                found = true;
                            }
                        }
                        if (!found){
                            std::cout << "Adding dir: " << dir_name << '\n';
                            current->dirs.push_back(std::make_unique<Directory>());
                            current->dirs.back()->parent = current;
                            current->dirs.back()->dirname = dir_name;
                        }
                    } else if (itemsVector.at(0) != "$"){
                        const auto file_size = itemsVector.at(0);
                        const auto file_name = itemsVector.at(1);
                        std::cout << "Adding file: " << file_name << " with size " << file_size << '\n';
                        current->files.push_back(std::make_unique<File>());
                        current->files.back()->size = std::stoll(file_size);
                        current->files.back()->filename = file_name;
                    } else {
                        skip = true;
                        break;
                    }
                }
            }
        }
    }
    //traverse(file_system.get(), 0);
    update_dir_size(file_system.get());
    /*const long long threshold = 100000;
    auto [count, sum] = count_dirs_lte_threshold(file_system.get(), threshold);
    if (file_system->size <= threshold) {
        count += 1;
        sum += file_system->size;
    }
    std::cout << count << ' ' << sum << '\n';*/

    const auto available = 70000000 - file_system->size;
    const auto required = 30000000 - available;
    std::cout << required << '\n';
    if (required <= 0) return 0;
    auto val = find_directory_gte(file_system.get(), required);
    std::cout << val << '\n';

    return 0;
}