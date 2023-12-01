#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>

struct Head{
    //++U --D ++R --L
    int UD = 0;
    int RL = 0;
};

struct Tail{
    int UD = 0;
    int RL = 0;
};

int main(){
    std::ifstream MyFile("RopeMoves.txt");
    std::string items;
    int positionsTailVisited{1};
    Head head = Head();
    Tail tail = Tail();
    std::set<std::pair<int,int> > locations;
    locations.insert(std::pair{0,0});
    
    //Task 2
    std::set<std::pair<int,int> > locations9;
    locations9.insert(std::pair{0,0});
    std::array<Tail, 8> tails{}; //Tail tails[8];

    while (getline(MyFile, items)){
        std::string p1 = items.substr(0,items.find(" "));
        std::string p2 = items.substr(items.find(" ") + 1, items.size() - items.find(" "));

        for (int i = 0; i < stoi(p2); ++i)
        {
            if(p1 == "U"){ head.UD++;}
            else if(p1 == "D"){ head.UD--;}
            else if(p1 == "R"){ head.RL++;}
            else if(p1 == "L"){ head.RL--;}

            int dy = head.UD - tail.UD; 
            int dx = head.RL - tail.RL;
        
            //If the tail is further than 1 away from the head, move it closer
            if (dx >= 2 or dx <= -2 or dy >= 2 or dy <=-2){          
                dx = std::max(-1, std::min(1, dx));
                dy = std::max(-1, std::min(1, dy));

                tail.UD = tail.UD + dy;
                tail.RL = tail.RL + dx;

                positionsTailVisited++;
                locations.insert(std::pair{tail.UD, tail.RL});

                //Task 2 Unnötige wiederholungen
                for (int i = 0; i < tails.size(); i++)
                {
                    if(i == 0){
                        dy = tail.UD - tails.at(i).UD; 
                        dx = tail.RL - tails.at(i).RL;   

                        if (dx >= 2 or dx <= -2 or dy >= 2 or dy <=-2){          
                            dx = std::max(-1, std::min(1, dx));
                            dy = std::max(-1, std::min(1, dy));

                            tails.at(i).UD += dy;
                            tails.at(i).RL += dx;  
                        }
                    }else if (i == 7){
                        dy = tails.at(i - 1).UD - tails.at(i).UD;
                        dx = tails.at(i - 1).RL - tails.at(i).RL;

                        if (dx >= 2 or dx <= -2 or dy >= 2 or dy <= -2)
                        {
                            dx = std::max(-1, std::min(1, dx));
                            dy = std::max(-1, std::min(1, dy));

                            tails.at(i).UD += dy;
                            tails.at(i).RL += dx;
                            locations9.insert(std::pair{tails.at(i).UD, tails.at(i).RL});
                        }
                    }else {
                        dy = tails.at(i - 1).UD - tails.at(i).UD;
                        dx = tails.at(i - 1).RL - tails.at(i).RL;

                        if (dx >= 2 or dx <= -2 or dy >= 2 or dy <= -2)
                        {
                            dx = std::max(-1, std::min(1, dx));
                            dy = std::max(-1, std::min(1, dy));

                            tails.at(i).UD += dy;
                            tails.at(i).RL += dx;
                        }
                    }
                }
            }
        }
    }

    std::cout << positionsTailVisited << std::endl;
    std::cout << locations.size() << std::endl;
    std::cout << locations9.size() << std::endl;

    //6023
    //2533
}