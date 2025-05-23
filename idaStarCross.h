#ifndef IDASTARCROSS_H
#define IDASTARCROSS_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>

// Assuming these are defined in other header files
#include "cubiecube.h"
#include "tableloader.h"
#include "pieces.h"

bool is_goal_state(std::string crossState, std::string goal_cross_state) {
    return crossState == goal_cross_state;
}

class IDA_star_cross {
public:
    IDA_star_cross(int max_depth = 100){
        this->max_depth = max_depth;
        CubieCube cubeCheck = CubieCube();
        this->goal_cross_state = get_cross_state(cubeCheck);
        this->crossHeur = tableLoader.getHeuristics("cross");
    }

    std::vector<int> run(CubieCube cube) {
        int threshold = heuristic_value(cube);
        while (threshold <= max_depth) {
            std::cout << "Threshold: " << threshold << std::endl;
            moves.clear();
            transposition_table.clear();
            int distance = search(cube, 0, threshold);
            if (distance == 0) {
                std::cout << "Solution found" << std::endl;
                return moves;
            }
            if (distance == std::numeric_limits<int>::max()) {
                return {};
            }
            threshold = distance;
        }
        return {};
    }

private:
    int max_depth;
    std::vector<int> moves;
    std::unordered_map<std::string, std::pair<int, int>> transposition_table;
    std::string goal_cross_state;
    std::unordered_map<std::string, int> crossHeur;

    int search(CubieCube cube, int g_score, int threshold) {
        std::string cube_state = get_cube_state(cube);

        auto it = transposition_table.find(cube_state);
        if (it != transposition_table.end()) {
            auto [stored_g_score, stored_result] = it->second;
            if (stored_g_score <= g_score) {
                return stored_result;
            }
        }

        int f_score = g_score + heuristic_value(cube);
        if (f_score > threshold) {
            transposition_table[cube_state] = {g_score, f_score};
            return f_score;
        }

        if (is_goal_state(get_cross_state(cube), goal_cross_state)) {
            transposition_table[cube_state] = {g_score, 0};
            return 0;
        }

        int min_cost = std::numeric_limits<int>::max();
        for (int action = 0; action < 18; ++action) {
            CubieCube cube_copy = cube;
            cube_copy.move(action, MOVE_CUBE[action]);

            if (!moves.empty() && std::find(REDUNDANT_ACTIONS.at(moves.back()).begin(),
                                            REDUNDANT_ACTIONS.at(moves.back()).end(),
                                            action) != REDUNDANT_ACTIONS.at(moves.back()).end()) {
                continue;
            }

            if (moves.size() > 1 &&
                std::find(REDUNDANT_ACTIONS_2.at(moves.back()).begin(),
                          REDUNDANT_ACTIONS_2.at(moves.back()).end(),
                          action) != REDUNDANT_ACTIONS_2.at(moves.back()).end() &&
                std::find(REDUNDANT_ACTIONS.at(moves[moves.size() - 2]).begin(),
                          REDUNDANT_ACTIONS.at(moves[moves.size() - 2]).end(),
                          action) != REDUNDANT_ACTIONS.at(moves[moves.size() - 2]).end()) {
                continue;
            }

            moves.push_back(action);
            int distance = search(cube_copy, g_score + 1, threshold);
            if (distance == 0) {
                return 0;
            }
            if (distance < min_cost) {
                min_cost = distance;
            }
            moves.pop_back();
        }

        transposition_table[cube_state] = {g_score, min_cost};
        return min_cost;
    }

    std::string get_cube_state(const CubieCube& cube) {
        std::string state = get_cross_state(cube);
        return state;
    }

    std::string get_cross_state(const CubieCube& cube) {
        // (-1, 1, 2, 3, -1, -1, -1, -1, -1, -1, -1, 0, -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, 0)
        std::string crossState = "(";
        std::array<Edge, 12> epc = cube.get_epc();
        std::array<int, 12> eoc = cube.get_eoc();

        for(int i = 0; i < 12; i++){
            if(epc[i] == Edge::UF){
                crossState += "1, ";
            } else if(epc[i] == Edge::UL){
                crossState += "2, ";
            } else if(epc[i] == Edge::UB){
                crossState += "3, ";
            } else if(epc[i] == Edge::UR){
                crossState += "0, ";
            } else {
                crossState += "-1, ";
            }
        }

        for(int i = 0; i < 12; i++){
            crossState += std::to_string(eoc[i]) + ", ";
        }

        crossState.pop_back();
        crossState.pop_back();
        crossState += ")";

        return crossState;
    }

    int heuristic_value(const CubieCube& cube) {
        std::string stateCross = get_cross_state(cube);

        auto it = crossHeur.find(stateCross);
        if (it != crossHeur.end()) {
            return it->second - 1;
        } else {
            return 5;
        }
    }
};

std::vector<int> getCrossSolution(std::string scramble){
    CubieCube cube = CubieCube();
    cube = do_algorithm(scramble, cube);
    IDA_star_cross ida_star_cross = IDA_star_cross();
    std::vector<int> solution = ida_star_cross.run(cube);

    for (int action : solution) {
        std::cout << ACTIONS.at(action) << " ";
    }
    std::cout << std::endl;

    return solution;
};

#endif