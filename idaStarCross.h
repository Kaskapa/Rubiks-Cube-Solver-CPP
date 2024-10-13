#include <cstdint>
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

Tableloader tableLoader = Tableloader();
const std::array<CubieCube, 18> MOVE_CUBE = initialize_move_cube();

const std::unordered_map<int, std::string> ACTIONS = {
    {0, "U"}, {1, "R"}, {2, "F"}, {3, "D"}, {4, "L"}, {5, "B"},
    {6, "U2"}, {7, "R2"}, {8, "F2"}, {9, "D2"}, {10, "L2"}, {11, "B2"},
    {12, "U'"}, {13, "R'"}, {14, "F'"}, {15, "D'"}, {16, "L'"}, {17, "B'"}
};

const std::unordered_map<int, std::vector<int>> REDUNDANT_ACTIONS = {
    {0, {0, 6, 12}}, {1, {1, 7, 13}}, {2, {2, 8, 14}}, {3, {3, 9, 15}},
    {4, {4, 10, 16}}, {5, {5, 11, 17}}, {6, {0, 6, 12}}, {7, {1, 7, 13}},
    {8, {2, 8, 14}}, {9, {3, 9, 15}}, {10, {4, 10, 16}}, {11, {5, 11, 17}},
    {12, {0, 6, 12}}, {13, {1, 7, 13}}, {14, {2, 8, 14}}, {15, {3, 9, 15}},
    {16, {4, 10, 16}}, {17, {5, 11, 17}}
};

const std::unordered_map<int, std::vector<int>> REDUNDANT_ACTIONS_2 = {
    {0, {3, 9, 15}}, {1, {4, 10, 16}}, {2, {5, 11, 17}}, {3, {0, 6, 12}},
    {4, {1, 7, 13}}, {5, {2, 8, 14}}, {6, {3, 9, 15}}, {7, {4, 10, 16}},
    {8, {5, 11, 17}}, {9, {0, 6, 12}}, {10, {1, 7, 13}}, {11, {2, 8, 14}},
    {12, {3, 9, 15}}, {13, {4, 10, 16}}, {14, {5, 11, 17}}, {15, {0, 6, 12}},
    {16, {1, 7, 13}}, {17, {2, 8, 14}}
};

bool is_goal_state(std::string crossState, std::string goal_cross_state) {
    return crossState == goal_cross_state;
}

CubieCube actionsWithNotations(const std::string& action, CubieCube cube) {
    if(action == "U") cube.move(0, MOVE_CUBE[0]);
    else if(action == "R") cube.move(1, MOVE_CUBE[1]);
    else if(action == "F") cube.move(2, MOVE_CUBE[2]);
    else if(action == "D") cube.move(3, MOVE_CUBE[3]);
    else if(action == "L") cube.move(4, MOVE_CUBE[4]);
    else if(action == "B") cube.move(5, MOVE_CUBE[5]);
    else if(action == "U'") cube.move(12, MOVE_CUBE[12]);
    else if(action == "R'") cube.move(13, MOVE_CUBE[13]);
    else if(action == "F'") cube.move(14, MOVE_CUBE[14]);
    else if(action == "D'") cube.move(15, MOVE_CUBE[15]);
    else if(action == "L'") cube.move(16, MOVE_CUBE[16]);
    else if(action == "B'") cube.move(17, MOVE_CUBE[17]);
    else if(action == "U2") cube.move(6, MOVE_CUBE[6]);
    else if(action == "R2") cube.move(7, MOVE_CUBE[7]);
    else if(action == "F2") cube.move(8, MOVE_CUBE[8]);
    else if(action == "D2") cube.move(9, MOVE_CUBE[9]);
    else if(action == "L2") cube.move(10, MOVE_CUBE[10]);
    else if(action == "B2") cube.move(11, MOVE_CUBE[11]);
    return cube;
}

CubieCube do_algorithm(const std::string& algorithm, CubieCube cube) {
    std::istringstream iss(algorithm);
    std::string move;
    while (iss >> move) {
        cube = actionsWithNotations(move, cube);
    }
    return cube;
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
        // (-1, <Edge.UF: 1>, <Edge.UL: 2>, <Edge.UB: 3>, -1, -1, -1, -1, -1, -1, -1, <Edge.UR: 0>, -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, 0)
        std::string crossState = "(";
        std::array<Edge, 12> epc = cube.get_epc();
        std::array<int, 12> eoc = cube.get_eoc();

        for(int i = 0; i < 12; i++){
            if(epc[i] == Edge::UF){
                crossState += "<Edge.UF: 1>, ";
            } else if(epc[i] == Edge::UL){
                crossState += "<Edge.UL: 2>, ";
            } else if(epc[i] == Edge::UB){
                crossState += "<Edge.UB: 3>, ";
            } else if(epc[i] == Edge::UR){
                crossState += "<Edge.UR: 0>, ";
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

// int main(){
//     // CubieCube cube = CubieCube();
//     // std::string scramble = "L' B' D F L2 D2 R' U' B2 L D B2 R F L2 U2 F' R U B R'";
//     // cube = do_algorithm(scramble, cube);
//     // IDA_star_cross ida_star_cross = IDA_star_cross();
//     // std::vector<int> solution = ida_star_cross.run(cube);

//     // for (int action : solution) {
//     //     std::cout << ACTIONS.at(action) << " ";
//     // }
//     // std::cout << std::endl;

//     // return 0;
// };

#endif