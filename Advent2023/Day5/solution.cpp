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

    std::vector<std::tuple<long long, long long>> seedToSoil;
    for (long long seed : seedNumbers) {
        auto it = std::find_if(seedToSoilMap.begin(), seedToSoilMap.end(), [seed](const auto& entry) {
            return seed >= std::get<1>(entry) && seed < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != seedToSoilMap.end()) {
            long long soil = std::get<0>(*it) + seed - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            seedToSoil.push_back(std::make_tuple(soil, seed));
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            seedToSoil.push_back(std::make_tuple(seed, seed));
        }
    }

    std::vector<std::tuple<long long, long long>> soilToFertilizer;
    for (auto seed : seedToSoil) {
        auto it = std::find_if(soilToFertilizerMap.begin(), soilToFertilizerMap.end(), [seed](const auto& entry) {
            return std::get<0>(seed) >= std::get<1>(entry) && std::get<0>(seed) < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != soilToFertilizerMap.end()) {
            long long soil = std::get<0>(*it) + std::get<0>(seed) - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            soilToFertilizer.push_back(std::make_tuple(soil, std::get<0>(seed)));
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            soilToFertilizer.push_back(std::make_tuple(std::get<0>(seed), std::get<0>(seed)));
        }
    }    

    std::vector<std::tuple<long long, long long>> fertilizerToWater;
    for (auto seed : soilToFertilizer) {
        auto it = std::find_if(fertilizerToWaterMap.begin(), fertilizerToWaterMap.end(), [seed](const auto& entry) {
            return std::get<0>(seed) >= std::get<1>(entry) && std::get<0>(seed) < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != fertilizerToWaterMap.end()) {
            long long soil = std::get<0>(*it) + std::get<0>(seed) - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            fertilizerToWater.push_back(std::make_tuple(soil, std::get<0>(seed)));
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            fertilizerToWater.push_back(std::make_tuple(std::get<0>(seed), std::get<0>(seed)));
        }
    }  

    std::vector<std::tuple<long long, long long>> waterToLight;
    for (auto seed : fertilizerToWater) {
        auto it = std::find_if(waterToLightMap.begin(), waterToLightMap.end(), [seed](const auto& entry) {
            return std::get<0>(seed) >= std::get<1>(entry) && std::get<0>(seed) < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != waterToLightMap.end()) {
            long long soil = std::get<0>(*it) + std::get<0>(seed) - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            waterToLight.push_back(std::make_tuple(soil, std::get<0>(seed)));
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            waterToLight.push_back(std::make_tuple(std::get<0>(seed), std::get<0>(seed)));
        }
    }

    std::vector<std::tuple<long long, long long>> lightToTemperature;
    for (auto seed : waterToLight) {
        auto it = std::find_if(lightToTemperatureMap.begin(), lightToTemperatureMap.end(), [seed](const auto& entry) {
            return std::get<0>(seed) >= std::get<1>(entry) && std::get<0>(seed) < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != lightToTemperatureMap.end()) {
            long long soil = std::get<0>(*it) + std::get<0>(seed) - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            lightToTemperature.push_back(std::make_tuple(soil, std::get<0>(seed)));
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            lightToTemperature.push_back(std::make_tuple(std::get<0>(seed), std::get<0>(seed)));
        }
    }

    std::vector<std::tuple<long long, long long>> temperatureToHumidity;
    for (auto seed : lightToTemperature) {
        auto it = std::find_if(temperatureToHumidityMap.begin(), temperatureToHumidityMap.end(), [seed](const auto& entry) {
            return std::get<0>(seed) >= std::get<1>(entry) && std::get<0>(seed) < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != temperatureToHumidityMap.end()) {
            long long soil = std::get<0>(*it) + std::get<0>(seed) - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            temperatureToHumidity.push_back(std::make_tuple(soil, std::get<0>(seed)));
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            temperatureToHumidity.push_back(std::make_tuple(std::get<0>(seed), std::get<0>(seed)));
        }
    }     

    std::vector<std::tuple<long long, long long>> humidityToLocation;
    std::vector<long long> location;

    for (auto seed : temperatureToHumidity) {
        auto it = std::find_if(humidityToLocationMap.begin(), humidityToLocationMap.end(), [seed](const auto& entry) {
            return std::get<0>(seed) >= std::get<1>(entry) && std::get<0>(seed) < std::get<1>(entry) + std::get<2>(entry);
        });
        if (it != humidityToLocationMap.end()) {
            long long soil = std::get<0>(*it) + std::get<0>(seed) - std::get<1>(*it);
            //std::cout << "Seed " << seed << " maps to Soil " << soil << std::endl;                    
            humidityToLocation.push_back(std::make_tuple(soil, std::get<0>(seed)));
            location.push_back(soil);
        } else {
            //std::cerr << "No mapping found for seed " << seed << std::endl;
            humidityToLocation.push_back(std::make_tuple(std::get<0>(seed), std::get<0>(seed)));
            location.push_back(std::get<0>(seed));
        }
    }     

    auto minElement = *std::min_element(location.begin(), location.end());
    
    std::cout << "Min_Element: ";
    std::cout << minElement << std::endl;

    std::cout << "Seed Numbers: ";
    for (long long seed : seedNumbers) {
        std::cout << seed << " ";
    }

    std::cout << "Seed-to-Soil Map: ";
    for (const auto& entry : seedToSoilMap) {
        std::cout << "(" << std::get<0>(entry) << ", " << std::get<1>(entry) << ", " << std::get<2>(entry) << ") ";
    }
}