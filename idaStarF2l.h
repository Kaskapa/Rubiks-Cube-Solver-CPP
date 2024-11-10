#ifndef IDASTARF2L_H
#define IDASTARF2L_H

#include "solver_common.h"

class IDA_star_F2L {
public:
    IDA_star_F2L(std::vector<Corner> corners, std::vector<Edge> edges, std::string cornerStr, std::string edgeStr, int max_depth = 100);

    std::vector<int> run(CubieCube cube);

private:
    int max_depth;
    std::vector<int> moves;
    std::unordered_map<std::string, std::pair<int, int>> transposition_table;
    std::string goal_cross_state;
    std::string goal_corner_state;
    std::string goal_edge_state;
    std::unordered_map<std::string, int> crossHeur;
    std::unordered_map<std::string, int> cornerHeur;
    std::unordered_map<std::string, int> edgeHeur;
    std::vector<Corner> corners;
    std::vector<Edge> edges;

    int search(CubieCube cube, int g_score, int threshold);
    int heuristic_value(const CubieCube& cube);
    std::string get_cross_state(const CubieCube& cube);
    std::string get_corner_state(const CubieCube& cube);
    std::string get_edge_state(const CubieCube& cube);
    bool is_goal_state(std::string crossState, std::string goal_cross_state, std::string goal_edge_stae, std::string goal_corner_state, std::string edge_state, std::string corner_state);
    std::string get_cube_state(const CubieCube& cube);
};

std::vector<std::vector<std::vector<int>>> getSolutions(std::string scramble, std::string crossSolution);

#endif // IDASTARF2L_H