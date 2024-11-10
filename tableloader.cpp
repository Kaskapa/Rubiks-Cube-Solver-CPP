#include "tableloader.h"

std::unordered_map<std::string, int> loadHeuristic(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return {};
    }

    std::string line;
    std::unordered_map<std::string, int> heuristics;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ';')) {
            row.push_back(cell);
        }

        heuristics[row[0]] = std::stoi(row[1]);
    }

    file.close();
    return heuristics;
}

Tableloader::Tableloader() {
    heuristics0 = loadHeuristic("heuristics/heuristicsJson0.csv");
    heuristics1 = loadHeuristic("heuristics/heuristicsJson1.csv");
    heuristics01 = loadHeuristic("heuristics/heuristicsJson01.csv");
    heuristics2 = loadHeuristic("heuristics/heuristicsJson2.csv");
    heuristics02 = loadHeuristic("heuristics/heuristicsJson02.csv");
    heuristic3 = loadHeuristic("heuristics/heuristicsJson3.csv");
    heuristics03 = loadHeuristic("heuristics/heuristicsJson03.csv");
    heuristics8 = loadHeuristic("heuristics/heuristicsJson8.csv");
    heuristics9 = loadHeuristic("heuristics/heuristicsJson9.csv");
    heuristics10 = loadHeuristic("heuristics/heuristicsJson10.csv");
    heuristics11 = loadHeuristic("heuristics/heuristicsJson11.csv");
    heuristics12 = loadHeuristic("heuristics/heuristicsJson12.csv");
    heuristics012 = loadHeuristic("heuristics/heuristicsJson012.csv");
    heuristics13 = loadHeuristic("heuristics/heuristicsJson13.csv");
    heuristics013 = loadHeuristic("heuristics/heuristicsJson013.csv");
    heuristics23 = loadHeuristic("heuristics/heuristicsJson23.csv");
    heuristics023 = loadHeuristic("heuristics/heuristicsJson023.csv");
    heuristics89 = loadHeuristic("heuristics/heuristicsJson89.csv");
    heuristics123 = loadHeuristic("heuristics/heuristicsJson123.csv");
    heuristicsCross = loadHeuristic("heuristics/heuristicsJsonCross.csv");
    heuristics810 = loadHeuristic("heuristics/heuristicsJson810.csv");
    heuristics811 = loadHeuristic("heuristics/heuristicsJson811.csv");
    heuristics910 = loadHeuristic("heuristics/heuristicsJson910.csv");
    heuristics911 = loadHeuristic("heuristics/heuristicsJson911.csv");
    heuristics1011 = loadHeuristic("heuristics/heuristicsJson1011.csv");
    heuristics8910 = loadHeuristic("heuristics/heuristicsJson8910.csv");
    heuristics8911 = loadHeuristic("heuristics/heuristicsJson8911.csv");
    heuristics81011 = loadHeuristic("heuristics/heuristicsJson81011.csv");
    heuristics91011 = loadHeuristic("heuristics/heuristicsJson91011.csv");

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
    allHeuristics["Cross"] = heuristicsCross;
    allHeuristics["810"] = heuristics810;
    allHeuristics["811"] = heuristics811;
    allHeuristics["910"] = heuristics910;
    allHeuristics["911"] = heuristics911;
    allHeuristics["1011"] = heuristics1011;
    allHeuristics["8910"] = heuristics8910;
    allHeuristics["8911"] = heuristics8911;
    allHeuristics["81011"] = heuristics81011;
    allHeuristics["91011"] = heuristics91011;
}

std::unordered_map<std::string, int> Tableloader::getHeuristics(const std::string& key) {
    return allHeuristics[key];
}