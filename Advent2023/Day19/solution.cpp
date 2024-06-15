#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

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

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;

    std::unordered_map<std::string, Workflow> workflows;
    std::vector<Part> parts;

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

    // Parse parts
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        Part part;
        std::string ratingStr;
        while (std::getline(iss, ratingStr, ',')) {
            size_t equalPos = ratingStr.find('=');
            char attribute = ratingStr[equalPos - 1];
            int value = std::stoi(ratingStr.substr(equalPos + 1));
            part.ratings[attribute] = value;
        }
        parts.push_back(part);
    }

    long long sum = 0;
    // Process parts through workflows
    for (Part& part : parts) {
        std::string currentWorkflowName = "in";
        while (currentWorkflowName != "A" && currentWorkflowName != "R") {
            Workflow& currentWorkflow = workflows[currentWorkflowName];
            for (Rule& rule : currentWorkflow.rules) {
                if (rule.attribute == '.'){
                    currentWorkflowName = rule.nextWorkflow;
                    break;
                }
                
                if(rule.isGreaterThan){
                    if (part.ratings[rule.attribute] > rule.value) {
                        currentWorkflowName = rule.nextWorkflow;
                        break;
                    }
                } else if (part.ratings[rule.attribute] < rule.value) {
                    currentWorkflowName = rule.nextWorkflow;
                    break;  
                }
            }
        }
        if (currentWorkflowName == "A") {
            for(std::pair<char, int> i : part.ratings){
                sum += i.second;
            }
        }
    }

    // TODO: Print the total sum of the ratings of all accepted parts

    // Print parts
    /*for (const Part& part : parts) {
        std::cout << "Part: ";
        for (const auto& rating : part.ratings) {
            std::cout << rating.first << "=" << rating.second << ", ";
        }
        std::cout << std::endl;
    }

    // Print workflows
    for (const auto& workflowPair : workflows) {
        const Workflow& workflow = workflowPair.second;
        std::cout << "Workflow: " << workflow.name << std::endl;
        for (const Rule& rule : workflow.rules) {
            if(rule.isGreaterThan){
                std::cout << "  Rule: " << rule.attribute << ">" << rule.value << ":" << rule.nextWorkflow << std::endl;
            } else{
                std::cout << "  Rule: " << rule.attribute << "<" << rule.value << ":" << rule.nextWorkflow << std::endl;
            }
        }
    }*/
    std::cout << "The sum: " << sum << std::endl;

    return 0;
}
