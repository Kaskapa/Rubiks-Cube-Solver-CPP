#ifndef IDASTARCROSS_H
#define IDASTARCROSS_H

#include "solver_common.h"

class IDA_star_cross {
public:
    IDA_star_cross(int max_depth = 100);

    std::vector<int> run(CubieCube cube);

private:
    int max_depth;
    std::vector<int> moves;
    std::unordered_map<std::string, std::pair<int, int>> transposition_table;
    std::string goal_cross_state;
    std::unordered_map<std::string, int> crossHeur;

    int search(CubieCube cube, int g_score, int threshold);
    int heuristic_value(const CubieCube& cube);
    std::string get_cube_state(const CubieCube& cube);
    std::string get_cross_state(const CubieCube& cube);
    bool is_goal_state(std::string crossState, std::string goal_cross_state);
};

std::vector<int> getCrossSolution(std::string scramble);

#endif // IDASTARCROSS_H