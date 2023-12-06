#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <regex>
#include <fstream>
#include <queue>
#include <algorithm>

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<long long> seedNumbers;
    std::vector<std::tuple<long long, long long, long long>> seedToSoilMap;
    std::vector<std::tuple<long long, long long, long long>> soilToFertilizerMap;
    std::vector<std::tuple<long long, long long, long long>> fertilizerToWaterMap;
    std::vector<std::tuple<long long, long long, long long>> waterToLightMap;
    std::vector<std::tuple<long long, long long, long long>> lightToTemperatureMap;
    std::vector<std::tuple<long long, long long, long long>> temperatureToHumidityMap;
    std::vector<std::tuple<long long, long long, long long>> humidityToLocationMap;

    while (std::getline(inputFile, line)) { 
        if (line.find("seeds:") != std::string::npos) {
            std::istringstream iss(line.substr(6));
            long long seed;

            while (iss >> seed) {
                seedNumbers.push_back(seed);
            }
        }else if (line.find("seed-to-soil map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    seedToSoilMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid seed-to-soil map format." << std::endl;
                    return 1;
                }
            }
        }else if (line.find("soil-to-fertilizer map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    soilToFertilizerMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid soil-to-fertilizer map format." << std::endl;
                    return 1;
                }
            }
        }else if (line.find("fertilizer-to-water map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    fertilizerToWaterMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid fertilizer-to-water map format." << std::endl;
                    return 1;
                }
            }
        }else if (line.find("water-to-light map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    waterToLightMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid water-to-light map format." << std::endl;
                    return 1;
                }
            }
        }else if (line.find("light-to-temperature map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    lightToTemperatureMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid light-to-temperature map format." << std::endl;
                    return 1;
                }
            }
        }else if (line.find("temperature-to-humidity map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    temperatureToHumidityMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid temperature-to-humidity map format." << std::endl;
                    return 1;
                }
            }
        }else if (line.find("humidity-to-location map:") != std::string::npos) {
            while (std::getline(inputFile, line) && !line.empty()) {
                std::istringstream mapIss(line);
                long long destStart, sourceStart, length;

                if (mapIss >> destStart >> sourceStart >> length) {
                    humidityToLocationMap.push_back(std::make_tuple(destStart, sourceStart, length));
                } else {
                    std::cerr << "Invalid humidity-to-location map format." << std::endl;
                    return 1;
                }
            }
        }
    }

    long long counter = 0;
    bool found = false;
    long long tmp = 0;

    while(!found){

        tmp = counter;
        
        auto it = std::find_if(humidityToLocationMap.begin(), humidityToLocationMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != humidityToLocationMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }
        
        it = std::find_if(temperatureToHumidityMap.begin(), temperatureToHumidityMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != temperatureToHumidityMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }
        
        it = std::find_if(lightToTemperatureMap.begin(), lightToTemperatureMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != lightToTemperatureMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }
        
        it = std::find_if(waterToLightMap.begin(), waterToLightMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != waterToLightMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }
        
        it = std::find_if(fertilizerToWaterMap.begin(), fertilizerToWaterMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != fertilizerToWaterMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }

        it = std::find_if(soilToFertilizerMap.begin(), soilToFertilizerMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != soilToFertilizerMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }

        it = std::find_if(seedToSoilMap.begin(), seedToSoilMap.end(), [tmp](const auto& entry) {
            return tmp >= std::get<0>(entry) && tmp < std::get<0>(entry) + std::get<2>(entry);
        });

        if (it != seedToSoilMap.end()) {
            long long soil = std::get<1>(*it) + tmp - std::get<0>(*it);
            tmp = soil;
        }

        for (size_t i = 0; i < seedNumbers.size(); i += 2) {
            long long start = seedNumbers[i];
            long long range = seedNumbers[i+1];

            if (tmp >= start && tmp < start + range) {
                for (long long j = start; j < start + range; ++j) {
                    if (tmp == j) {
                        std::cout <<" tmp found" << std::endl;
                        std::cout << tmp << std::endl;
                        found = true;
                        break;
                    }
                }
            }

            if (found) {
                break;
            }
        }

        counter++;
    }

    std::cout << counter - 1 << std::endl;
}