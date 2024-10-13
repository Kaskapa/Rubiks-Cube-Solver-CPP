#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#ifndef TABLELOADER_H
#define TABLELOADER_H

std::unordered_map<std::string, int> loadHeuristic(std::string filename) {
    // Name of the CSV file to read
    std::ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        std::unordered_map<std::string, int> heuristics = {};
        return heuristics;
    }
    std::string line;
    std::unordered_map<std::string, int> heuristics;

    // Read each line of the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        // Split the line by commas and store each cell in the row vector
        while (std::getline(ss, cell, ';')) {
            row.push_back(cell);
        }

        // Print the contents of the row
        heuristics[row[0]] = std::stoi(row[1]);
    }

    // Close the file
    file.close();
    return heuristics;
}


class Tableloader{
    public:
        Tableloader(){
            std::unordered_map<std::string, int> heuristics0 = loadHeuristic("heuristics/heuristicsJson0.csv");
            std::unordered_map<std::string, int> heuristics1 = loadHeuristic("heuristics/heuristicsJson1.csv");
            std::unordered_map<std::string, int> heuristics01 = loadHeuristic("heuristics/heuristicsJson01.csv");
            std::unordered_map<std::string, int> heuristics2 = loadHeuristic("heuristics/heuristicsJson2.csv");
            std::unordered_map<std::string, int> heuristics02 = loadHeuristic("heuristics/heuristicsJson02.csv");
            std::unordered_map<std::string, int> heuristic3 = loadHeuristic("heuristics/heuristicsJson3.csv");
            std::unordered_map<std::string, int> heuristics03 = loadHeuristic("heuristics/heuristicsJson03.csv");
            std::unordered_map<std::string, int> heuristics8 = loadHeuristic("heuristics/heuristicsJson8.csv");
            std::unordered_map<std::string, int> heuristics9 = loadHeuristic("heuristics/heuristicsJson9.csv");
            std::unordered_map<std::string, int> heuristics10 = loadHeuristic("heuristics/heuristicsJson10.csv");
            std::unordered_map<std::string, int> heuristics11 = loadHeuristic("heuristics/heuristicsJson11.csv");
            std::unordered_map<std::string, int> heuristics12 = loadHeuristic("heuristics/heuristicsJson12.csv");
            std::unordered_map<std::string, int> heuristics012 = loadHeuristic("heuristics/heuristicsJson012.csv");
            std::unordered_map<std::string, int> heuristics13 = loadHeuristic("heuristics/heuristicsJson13.csv");
            std::unordered_map<std::string, int> heuristics013 = loadHeuristic("heuristics/heuristicsJson013.csv");
            std::unordered_map<std::string, int> heuristics23 = loadHeuristic("heuristics/heuristicsJson23.csv");
            std::unordered_map<std::string, int> heuristics023 = loadHeuristic("heuristics/heuristicsJson023.csv");
            std::unordered_map<std::string, int> heuristics89 = loadHeuristic("heuristics/heuristicsJson89.csv");
            std::unordered_map<std::string, int> heuristics123 = loadHeuristic("heuristics/heuristicsJson123.csv");
            std::unordered_map<std::string, int> heuristicsCross = loadHeuristic("heuristics/heuristicsJsonCross.csv");
            std::unordered_map<std::string, int> heuristics810 = loadHeuristic("heuristics/heuristicsJson810.csv");
            std::unordered_map<std::string, int> heuristics811 = loadHeuristic("heuristics/heuristicsJson811.csv");
            std::unordered_map<std::string, int> heuristics910 = loadHeuristic("heuristics/heuristicsJson910.csv");
            std::unordered_map<std::string, int> heuristics911 = loadHeuristic("heuristics/heuristicsJson911.csv");
            std::unordered_map<std::string, int> heuristics1011 = loadHeuristic("heuristics/heuristicsJson1011.csv");
            std::unordered_map<std::string, int> heuristics8910 = loadHeuristic("heuristics/heuristicsJson8910.csv");
            std::unordered_map<std::string, int> heuristics8911 = loadHeuristic("heuristics/heuristicsJson8911.csv");
            std::unordered_map<std::string, int> heuristics81011 = loadHeuristic("heuristics/heuristicsJson81011.csv");
            std::unordered_map<std::string, int> heuristics91011 = loadHeuristic("heuristics/heuristicsJson91011.csv");
            std::unordered_map<std::string, int> heuristics891011 = loadHeuristic("heuristics/heuristicsJson891011.csv");
            std::unordered_map<std::string, int> heuristics0123 = loadHeuristic("heuristics/heuristicsJson0123.csv");
            std::unordered_map<std::string, int> heuristicsEdgeOLL = loadHeuristic("heuristics/heuristicsJsonEdgeOLL.csv");
            std::unordered_map<std::string, int> heuristicsCornerOLL = loadHeuristic("heuristics/heuristicsJsonCornerOLL.csv");


            allHeuristics["0"] = heuristics0;
            allHeuristics["1"] = heuristics1;
            allHeuristics["01"] = heuristics01;
            allHeuristics["2"] = heuristics2;
            allHeuristics["02"] = heuristics02;
            allHeuristics["3"] = heuristic3;
            allHeuristics["03"] = heuristics03;
            allHeuristics["8"] = heuristics8;
            allHeuristics["9"] = heuristics9;
            allHeuristics["10"] = heuristics10;
            allHeuristics["11"] = heuristics11;
            allHeuristics["12"] = heuristics12;
            allHeuristics["012"] = heuristics012;
            allHeuristics["13"] = heuristics13;
            allHeuristics["013"] = heuristics013;
            allHeuristics["23"] = heuristics23;
            allHeuristics["023"] = heuristics023;
            allHeuristics["89"] = heuristics89;
            allHeuristics["123"] = heuristics123;
            allHeuristics["cross"] = heuristicsCross;
            allHeuristics["810"] = heuristics810;
            allHeuristics["811"] = heuristics811;
            allHeuristics["910"] = heuristics910;
            allHeuristics["911"] = heuristics911;
            allHeuristics["1011"] = heuristics1011;
            allHeuristics["8910"] = heuristics8910;
            allHeuristics["8911"] = heuristics8911;
            allHeuristics["81011"] = heuristics81011;
            allHeuristics["91011"] = heuristics91011;
            allHeuristics["891011"] = heuristics891011;
            allHeuristics["0123"] = heuristics0123;
            allHeuristics["edgeOLL"] = heuristicsEdgeOLL;
            allHeuristics["cornerOLL"] = heuristicsCornerOLL;
        }
        std::unordered_map<std::string, int> getHeuristics(std::string key){
            return allHeuristics[key];
        }
    private:
        std::unordered_map<std::string, int> heuristics0;
        std::unordered_map<std::string, int> heuristics1;
        std::unordered_map<std::string, int> heuristics01;
        std::unordered_map<std::string, int> heuristics2;
        std::unordered_map<std::string, int> heuristics02;
        std::unordered_map<std::string, int> heuristic3;
        std::unordered_map<std::string, int> heuristics03;
        std::unordered_map<std::string, int> heuristics8;
        std::unordered_map<std::string, int> heuristics9;
        std::unordered_map<std::string, int> heuristics10;
        std::unordered_map<std::string, int> heuristics11;
        std::unordered_map<std::string, int> heuristics12;
        std::unordered_map<std::string, int> heuristics012;
        std::unordered_map<std::string, int> heuristics13;
        std::unordered_map<std::string, int> heuristics013;
        std::unordered_map<std::string, int> heuristics23;
        std::unordered_map<std::string, int> heuristics023;
        std::unordered_map<std::string, int> heuristics89;
        std::unordered_map<std::string, int> heuristics123;
        std::unordered_map<std::string, int> heuristicsCross;
        std::unordered_map<std::string, int> heuristics810;
        std::unordered_map<std::string, int> heuristics811;
        std::unordered_map<std::string, int> heuristics910;
        std::unordered_map<std::string, int> heuristics911;
        std::unordered_map<std::string, int> heuristics1011;
        std::unordered_map<std::string, int> heuristics8910;
        std::unordered_map<std::string, int> heuristics8911;
        std::unordered_map<std::string, int> heuristics81011;
        std::unordered_map<std::string, int> heuristics91011;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> allHeuristics;
};

#endif