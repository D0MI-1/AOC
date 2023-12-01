#include <iostream>
#include <fstream>

int main(){

    std::ifstream MyFile("ElfCalories.txt");
    std::string Calories;
    int highest_calories{0};
    int current_calories{0};
    int elv1{0};
    int elv2{0};
    int elv3{0};

    
    while (getline(MyFile, Calories)){
        if(Calories == "\r"){
            if (current_calories > elv1)
            {
                if(elv1 > elv2){
                    
                    if(elv2 > elv3){
                        elv3 = current_calories;
                        current_calories = 0;
                        continue;
                    }
                    elv2 = current_calories;
                    current_calories = 0;
                    continue;

                }else if(elv1 > elv3){
                    elv3 = current_calories;
                    current_calories = 0;
                    continue;
                }
                elv1 = current_calories;
                current_calories = 0;
                continue;
            }else if(current_calories > elv2){
                if(elv2 > elv3){
                    elv3 = current_calories;
                    current_calories = 0;
                    continue;
                }else{
                    elv2 = current_calories;
                    current_calories = 0;
                    continue;
                }
            }else if(current_calories > elv3){
                elv3 = current_calories;
                current_calories = 0;
                continue;
            }
            current_calories = 0;

        }else{
            current_calories += std::stoi(Calories);
            
            if(current_calories > highest_calories ){
                highest_calories = current_calories;
            }
        }
    }
    std::cout << elv1 << std::endl;
    std::cout << elv2 << std::endl;
    std::cout << elv3 << std::endl;
    std::cout << elv1 + elv2 + elv3 << std::endl;
    std::cout << highest_calories;
    MyFile.close();
}