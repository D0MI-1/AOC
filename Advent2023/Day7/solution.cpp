#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <sstream>

int checkHandType(const std::string &cards)
{
    std::vector<int> labelCounts(128, 0);

    for (char label : cards)
    {
        labelCounts[label]++;
    }

    std::vector<int> uniqueLabels;
    for (int i = 0; i < labelCounts.size(); ++i)
    {
        if (labelCounts[i] > 0)
        {
            uniqueLabels.push_back(i);
        }
    }
    
    int uniqueLabelCount = uniqueLabels.size();
    if (uniqueLabelCount == 5)
    {
        if (labelCounts[uniqueLabels[0]] == 1 && labelCounts[uniqueLabels[4]] == 1)
        {
            // highCard
            return 1;
        }
    }
    else if (uniqueLabelCount == 4)
    {
        // One Pair
        return 2;
    }
    else if (uniqueLabelCount == 3)
    {
        if (labelCounts[uniqueLabels[0]] == 2 && labelCounts[uniqueLabels[1]] == 2 ||
            labelCounts[uniqueLabels[0]] == 2 && labelCounts[uniqueLabels[2]] == 2 ||
            labelCounts[uniqueLabels[1]] == 2 && labelCounts[uniqueLabels[2]] == 2)
        {
            // Two Pair
            return 3;
        }
        else
        {
            // Three of a kind
            return 4;
        }
    }
    else if (uniqueLabelCount == 2)
    {
        if (labelCounts[uniqueLabels[0]] == 4 || labelCounts[uniqueLabels[1]] == 4)
        {
            // Four of a Kind
            return 6;
        }
        else
        {
            // Full House
            return 5;
        }
    }
    else if (uniqueLabelCount == 1)
    {
        // Five of a Kind
        return 7;
    }
}

bool compareHands(const std::string &hand1, const std::string &hand2, const std::vector<char> &strengths)
{
    for (int i = 0; i < hand1.size(); ++i)
    {
        int indexA = std::distance(strengths.begin(), std::find(strengths.begin(), strengths.end(), hand1[i]));
        int indexB = std::distance(strengths.begin(), std::find(strengths.begin(), strengths.end(), hand2[i]));

        if (indexA != indexB)
        {
            return indexA < indexB;
        }
    }
    return false; 
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<char> strengths = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    std::vector<std::pair<std::string, int>> input;

    std::vector<std::pair<std::string, int>> fiveOfAKind;
    std::vector<std::pair<std::string, int>> fourOfAKind;
    std::vector<std::pair<std::string, int>> fullHouse;
    std::vector<std::pair<std::string, int>> threeOfAKind;
    std::vector<std::pair<std::string, int>> twoPair;
    std::vector<std::pair<std::string, int>> onePair;
    std::vector<std::pair<std::string, int>> highCard;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);

        std::string strPart;
        iss >> strPart;

        int intPart;
        iss >> intPart;

        input.push_back(std::make_pair(strPart, intPart));
    }

    for (const auto &pair : input)
    {
        int handType = checkHandType(pair.first);

        switch (handType)
        {
        case 1:
            highCard.push_back(pair);
            break;
        case 2:
            onePair.push_back(pair);
            break;
        case 3:
            twoPair.push_back(pair);
            break;
        case 4:
            threeOfAKind.push_back(pair);
            break;
        case 5:
            fullHouse.push_back(pair);
            break;
        case 6:
            fourOfAKind.push_back(pair);
            break;
        case 7:
            fiveOfAKind.push_back(pair);
            break;
        default:
            break;
        }
    }

    std::sort(fiveOfAKind.begin(), fiveOfAKind.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    std::sort(fourOfAKind.begin(), fourOfAKind.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    std::sort(fullHouse.begin(), fullHouse.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    std::sort(threeOfAKind.begin(), threeOfAKind.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    std::sort(twoPair.begin(), twoPair.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    std::sort(onePair.begin(), onePair.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    std::sort(highCard.begin(), highCard.end(), [&](const auto &a, const auto &b) {
        return compareHands(a.first, b.first, strengths);
    });

    int counter = 1;
    long long solution = 0;

    for (const auto &highCard : highCard){
        solution += highCard.second * counter;
        counter++;
    }

    for (const auto &onePair : onePair){
        solution += onePair.second * counter;
        counter++;
    }

    for (const auto &twoPair : twoPair){
        solution += twoPair.second * counter;
        counter++;
    }

    for (const auto &threeOfAKind : threeOfAKind){
        solution += threeOfAKind.second * counter;
        counter++;
    }

    for (const auto &fullHouse : fullHouse){
        solution += fullHouse.second * counter;
        counter++;
    }

    for (const auto &fourOfAKind : fourOfAKind){
        solution += fourOfAKind.second * counter;
        counter++;
    }

    for (const auto &fiveOfAKind : fiveOfAKind){
        solution += fiveOfAKind.second * counter;
        counter++;
    }

    std::cout << solution << std::endl;
}