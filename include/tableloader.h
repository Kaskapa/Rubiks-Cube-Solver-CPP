#ifndef TABLELOADER_H
#define TABLELOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

// Function to load heuristics from a CSV file
std::unordered_map<std::string, int> loadHeuristic(const std::string& filename);

class Tableloader {
public:
    Tableloader();
    std::unordered_map<std::string, int> getHeuristics(const std::string& key);

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

#endif // TABLELOADER_H