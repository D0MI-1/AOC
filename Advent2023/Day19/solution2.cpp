#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>

struct Rule {
    char attribute;
    int value;
    std::string nextWorkflow;
    bool isGreaterThan; // true if '>', false if '<'
};

struct Workflow {
    std::string name;
    std::vector<Rule> rules;
};

struct Part {
    std::unordered_map<char, int> ratings;
};

long long count(const std::string& current,
    std::unordered_map<std::string, std::pair<int, int>>& ranges,
    std::unordered_map<std::string, Workflow> workflows) {
    
    if (current == "R") {
        return 0;
    }

    if (current == "A") {
        long long product = 1;
        for (const auto& [_, range] : ranges) {
            product *= range.second - range.first + 1;
        }
        return product;
    }

    long long total = 0;
    Workflow& currentWorkflow = workflows[current];

    for (Rule& rule : currentWorkflow.rules) {
        if (rule.attribute == '.'){
            total += count(rule.nextWorkflow, ranges, workflows);
        } else {
            std::unordered_map<std::string, std::pair<int, int>> new_ranges(ranges);
            std::string str{rule.attribute};
            auto& cur_range = ranges[str];

            if (cur_range.first < rule.value && rule.value < cur_range.second) {
                if (!rule.isGreaterThan) {
                    new_ranges[str] = {cur_range.first, rule.value - 1};
                    ranges[str] = {rule.value, cur_range.second};
                } else {
                    new_ranges[str] = {rule.value + 1, cur_range.second};
                    ranges[str] = {cur_range.first, rule.value};
                }

                total += count(rule.nextWorkflow, new_ranges, workflows);
            }
        }
    }

    return total;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::unordered_map<std::string, Workflow> workflows;

    // Parse workflows
    while (std::getline(inputFile, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string workflowName;
        std::getline(iss, workflowName, '{');
        Workflow workflow;
        workflow.name = workflowName;
        std::string ruleStr;
        while (std::getline(iss, ruleStr, ',')) {
            Rule rule;
            size_t comparisonPos = ruleStr.find_first_of("<>");
            if (comparisonPos != std::string::npos) {
                rule.attribute = ruleStr[0];
                rule.isGreaterThan = (ruleStr[comparisonPos] == '>');
                size_t colonPos = ruleStr.find(':');
                rule.value = std::stoi(ruleStr.substr(comparisonPos + 1, colonPos - comparisonPos - 1));
                rule.nextWorkflow = ruleStr.substr(colonPos + 1);
            } else {
                rule.nextWorkflow = ruleStr.substr(0, ruleStr.size() - 1); // without } am Ende
                rule.value = 0;
                rule.attribute = '.';
            }
            workflow.rules.push_back(rule);
        }
        workflows[workflowName] = workflow;
    }

    std::unordered_map<std::string, std::pair<int, int>> initial_ranges = {
        {"x", {1, 4000}},
        {"m", {1, 4000}},
        {"a", {1, 4000}},
        {"s", {1, 4000}}
    };

    long long result = count("in", initial_ranges, workflows);

    std::cout << "Number of distinct combinations accepted: " << result << std::endl;

    return 0;
}
