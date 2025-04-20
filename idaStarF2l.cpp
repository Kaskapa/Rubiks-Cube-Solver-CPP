#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>
#include <map>

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

bool is_goal_state(std::string crossState, std::string goal_cross_state, std::string goal_edge_stae, std::string goal_corner_state, std::string edge_state, std::string corner_state) {
    return crossState == goal_cross_state && edge_state == goal_edge_stae && corner_state == goal_corner_state;
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

class IDA_star_F2L {
public:
    IDA_star_F2L(std::vector<Corner> corners, std::vector<Edge> edges, std::string cornerStr, std::string edgeStr, int max_depth = 100){
        this->max_depth = max_depth;
        CubieCube cubeCheck = CubieCube(corners, edges);
        this->goal_cross_state = get_cross_state(cubeCheck);
        this->goal_corner_state = get_corner_state(cubeCheck);
        this->goal_edge_stae = get_edge_state(cubeCheck);
        this->crossHeur = tableLoader.getHeuristics("cross");
        this->cornerHeur = tableLoader.getHeuristics(cornerStr);
        this->edgeHeur = tableLoader.getHeuristics(edgeStr);
        this->corners = corners;
        this->edges = edges;

    }

    std::vector<int> run(CubieCube cube) {
        int threshold = heuristic_value(cube);
        while (threshold <= max_depth) {
            std::cout << "Threshold: " << threshold << '\n';
            moves.clear();
            transposition_table.clear();
            int distance = search(cube, 0, threshold);
            if (distance == 0) {
                std::cout << "Solution found" << '\n';
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
    std::string goal_corner_state;
    std::string goal_edge_stae;
    std::unordered_map<std::string, int> crossHeur;
    std::unordered_map<std::string, int> cornerHeur;
    std::unordered_map<std::string, int> edgeHeur;
    std::vector<Corner> corners;
    std::vector<Edge> edges;

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

        if (is_goal_state(get_cross_state(cube), goal_cross_state, goal_edge_stae, goal_corner_state, get_edge_state(cube), get_corner_state(cube))) {
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
        std::string state = get_cross_state(cube) + " " + get_edge_state(cube) + " " + get_corner_state(cube);
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

    std::string get_edge_state(const CubieCube& cube) {
        std::string edgeState = "(";
        std::array<Edge, 12> epf = cube.get_epf();
        std::array<int, 12> eof = cube.get_eof();

        for(int i = 0; i < 12; i++){
            if(epf[i] == Edge::FR){
                edgeState += "8, ";
            } else if(epf[i] == Edge::BR){
                edgeState += "11, ";
            } else if(epf[i] == Edge::BL){
                edgeState += "10, ";
            } else if(epf[i] == Edge::FL){
                edgeState += "9, ";
            } else {
                edgeState += "-1, ";
            }
        }

        for(int i = 0; i < 12; i++){
            edgeState += std::to_string(eof[i]) + ", ";
        }

        edgeState.pop_back();
        edgeState.pop_back();
        edgeState += ")";

        return edgeState;
    }

    std::string get_corner_state(const CubieCube& cube) {
        std::string cornerState = "(";
        std::array<Corner, 8> cpf = cube.get_cpf();
        std::array<int, 8> cof = cube.get_cof();

        for(int i = 0; i < 8; i++){
            if(cpf[i] == Corner::URF){
                cornerState += "0, ";
            } else if(cpf[i] == Corner::UFL){
                cornerState += "1, ";
            } else if(cpf[i] == Corner::UBR){
                cornerState += "3, ";
            } else if(cpf[i] == Corner::ULB){
                cornerState += "2, ";
            } else {
                cornerState += "-1, ";
            }
        }

        for(int i = 0; i < 8; i++){
            cornerState += std::to_string(cof[i]) + ", ";
        }

        cornerState.pop_back();
        cornerState.pop_back();
        cornerState += ")";

        return cornerState;
    }

    int heuristic_value(const CubieCube& cube) {
        std::string stateCross = get_cross_state(cube);
        std::string stateEdge = get_edge_state(cube);
        std::string stateCorner = get_corner_state(cube);

        auto itCross = crossHeur.find(stateCross);
        auto itEdge = edgeHeur.find(stateEdge);
        auto itCorner = cornerHeur.find(stateCorner);

        int h_cross = 5,  h_edge = 5,  h_corner = 5;

        if (itCross != crossHeur.end()) {
            h_cross = crossHeur[stateCross] - 1;
        }
        if(itEdge != edgeHeur.end()){
            h_edge = edgeHeur[stateEdge];
        }
        if(itCorner != cornerHeur.end()){
            h_corner = cornerHeur[stateCorner];
        }
        return h_cross + h_edge + h_corner;
    }
};

std::vector<std::vector<std::vector<int>>> getSolutions(std::string scramble, std::string crossSolution){
    CubieCube cube = CubieCube();
    cube = do_algorithm(scramble, cube);

    std::vector<Corner> solved_f2l_corners = {};
    std::vector<Edge> solved_f2l_edges = {};

    std::array<Corner, 4> f2l_corners = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR};
    std::array<Edge, 4> f2l_edges = {Edge::FR, Edge::FL, Edge::BL, Edge::BR};

    std::vector<std::array<Corner, 4>> f2l_corners_combinations;
    std::vector<std::array<Edge, 4>> f2l_edges_combinations;

    std::array<Corner, 4> corners = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR};
    do {
        f2l_corners_combinations.push_back(corners);
    } while (std::next_permutation(corners.begin(), corners.end()));

    std::array<Edge, 4> edges = {Edge::FR, Edge::FL, Edge::BL, Edge::BR};
    do {
        f2l_edges_combinations.push_back(edges);
    } while (std::next_permutation(edges.begin(), edges.end()));

    std::vector<std::vector<std::vector<int>>> all_sol = {};
    std::map<std::array<std::string, 6>, std::vector<int>> sol_heur = {};

    int startTime_main = clock();
    for(int j = 0; j < f2l_corners_combinations.size(); j++){
        std::vector<std::vector<int>> f2l_sol = {};
        std::array<Corner, 4> f2l_corners = f2l_corners_combinations[j];
        std::array<Edge, 4> f2l_edges = f2l_edges_combinations[j];

        for(int i = 0; i < f2l_corners.size(); i++){
            std::cout << "F2L " << i + 1 << '\n';

            std::vector<Corner> corners = {};
            std::vector<Edge> edges = {};

            for(int k = 0; k <= i; k++){
                corners.push_back(f2l_corners[k]);
                edges.push_back(f2l_edges[k]);
            }

            cube = CubieCube(corners, edges);
            cube = do_algorithm(scramble, cube);
            cube = do_algorithm(crossSolution, cube);

            for(int k = 0; k < f2l_sol.size() ; k++){
                for(int l = 0; l < f2l_sol[k].size(); l++){
                    cube.move(f2l_sol[k][l], MOVE_CUBE[f2l_sol[k][l]]);
                }
            }

            std::vector<int> cornerStr, edgeStr;

            for (Corner corner : corners) {
                cornerStr.push_back(static_cast<int>(corner));
            }
            for (Edge edge : edges) {
                edgeStr.push_back(static_cast<int>(edge));
            }

            std::sort(cornerStr.begin(), cornerStr.end());
            std::sort(edgeStr.begin(), edgeStr.end());

            std::string cornerStrJoined;
            std::string edgeStrJoined;
            for (int val : cornerStr) {
                cornerStrJoined += std::to_string(val);
            }
            for (int val : edgeStr) {
                edgeStrJoined += std::to_string(val);
            }

            std::cout << cornerStrJoined << '\n';
            std::cout << edgeStrJoined << '\n';

            std::string cofToString = "";
            std::string eofToString = "";
            std::string cpfToString = "";
            std::string epfToString = "";
            for(Corner corner: cube.get_cpf()){
                cpfToString += std::to_string(static_cast<int>(corner));
            }
            for(int val: cube.get_cof()){
                cofToString += std::to_string(val);
            }
            for(Edge edge: cube.get_epf()){
                epfToString += std::to_string(static_cast<int>(edge));
            }
            for(int val: cube.get_eof()){
                eofToString += std::to_string(val);
            }

            std::array<std::string, 6> key = {cornerStrJoined, edgeStrJoined, cofToString, eofToString, cpfToString, epfToString};

            if(sol_heur.find(key) != sol_heur.end()){
                f2l_sol.push_back(sol_heur[key]);
                continue;
            }

            IDA_star_F2L ida_star_f2l = IDA_star_F2L(corners, edges, cornerStrJoined, edgeStrJoined);
            int startTime = clock();
            std::vector<int> moves = ida_star_f2l.run(cube);

            f2l_sol.push_back(moves);
            int endTime = clock();

            std::cout << "Time: " << (endTime - startTime) / (double) CLOCKS_PER_SEC << '\n';

            sol_heur[key] = moves;
        }
        std::cout << "Scramble: " << scramble << '\n';
        std::cout << "Cross solution: " << crossSolution << '\n';

        for(std::vector<int> alg : f2l_sol){
            for(int move : alg){
                std::cout << ACTIONS.at(move) << " ";
            }
            std::cout << '\n';
        }

        all_sol.push_back(f2l_sol);
    }
    int endTime_main = clock();
    std::cout << "COMPLETE TIME: " << (endTime_main - startTime_main) / (double) CLOCKS_PER_SEC << '\n';

    return all_sol;
}

std::vector<std::vector<std::vector<int>>> getSolutionsOneByOne(std::string scramble, std::string crossSolution, std::vector<int> order){
    CubieCube cube = CubieCube();
    cube = do_algorithm(scramble, cube);

    std::vector<Corner> solved_f2l_corners = {};
    std::vector<Edge> solved_f2l_edges = {};

    std::array<Corner, 4> f2l_corners = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR};
    std::array<Edge, 4> f2l_edges = {Edge::FR, Edge::FL, Edge::BL, Edge::BR};

    std::vector<std::array<Corner, 4>> f2l_corners_combinations;
    std::vector<std::array<Edge, 4>> f2l_edges_combinations;

    std::array<Corner, 4> corners = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR};
    std::array<Edge, 4> edges = {Edge::FR, Edge::FL, Edge::BL, Edge::BR};

    std::array<Corner, 4> ordered_corners;
    std::array<Edge, 4> ordered_edges;

    for (int i = 0; i < 4; ++i) {
        ordered_corners[i] = corners[order[i]];
        ordered_edges[i] = edges[order[i]];
    }

    f2l_corners_combinations.push_back(ordered_corners);
    f2l_edges_combinations.push_back(ordered_edges);


    std::vector<std::vector<std::vector<int>>> all_sol = {};
    std::map<std::array<std::string, 6>, std::vector<int>> sol_heur = {};

    int startTime_main = clock();
    for(int j = 0; j < f2l_corners_combinations.size(); j++){
        std::vector<std::vector<int>> f2l_sol = {};
        std::array<Corner, 4> f2l_corners = f2l_corners_combinations[j];
        std::array<Edge, 4> f2l_edges = f2l_edges_combinations[j];

        for(int i = 0; i < f2l_corners.size(); i++){
            std::cout << "F2L " << i + 1 << '\n';

            std::vector<Corner> corners = {};
            std::vector<Edge> edges = {};

            for(int k = 0; k <= i; k++){
                corners.push_back(f2l_corners[k]);
                edges.push_back(f2l_edges[k]);
            }

            cube = CubieCube(corners, edges);
            cube = do_algorithm(scramble, cube);
            cube = do_algorithm(crossSolution, cube);

            for(int k = 0; k < f2l_sol.size() ; k++){
                for(int l = 0; l < f2l_sol[k].size(); l++){
                    cube.move(f2l_sol[k][l], MOVE_CUBE[f2l_sol[k][l]]);
                }
            }

            std::vector<int> cornerStr, edgeStr;

            for (Corner corner : corners) {
                cornerStr.push_back(static_cast<int>(corner));
            }
            for (Edge edge : edges) {
                edgeStr.push_back(static_cast<int>(edge));
            }

            std::sort(cornerStr.begin(), cornerStr.end());
            std::sort(edgeStr.begin(), edgeStr.end());

            std::string cornerStrJoined;
            std::string edgeStrJoined;
            for (int val : cornerStr) {
                cornerStrJoined += std::to_string(val);
            }
            for (int val : edgeStr) {
                edgeStrJoined += std::to_string(val);
            }

            std::cout << cornerStrJoined << '\n';
            std::cout << edgeStrJoined << '\n';

            std::string cofToString = "";
            std::string eofToString = "";
            std::string cpfToString = "";
            std::string epfToString = "";
            for(Corner corner: cube.get_cpf()){
                cpfToString += std::to_string(static_cast<int>(corner));
            }
            for(int val: cube.get_cof()){
                cofToString += std::to_string(val);
            }
            for(Edge edge: cube.get_epf()){
                epfToString += std::to_string(static_cast<int>(edge));
            }
            for(int val: cube.get_eof()){
                eofToString += std::to_string(val);
            }

            std::array<std::string, 6> key = {cornerStrJoined, edgeStrJoined, cofToString, eofToString, cpfToString, epfToString};

            if(sol_heur.find(key) != sol_heur.end()){
                f2l_sol.push_back(sol_heur[key]);
                continue;
            }

            IDA_star_F2L ida_star_f2l = IDA_star_F2L(corners, edges, cornerStrJoined, edgeStrJoined);
            int startTime = clock();
            std::vector<int> moves = ida_star_f2l.run(cube);

            f2l_sol.push_back(moves);
            int endTime = clock();

            std::cout << "Time: " << (endTime - startTime) / (double) CLOCKS_PER_SEC << '\n';

            sol_heur[key] = moves;
        }
        std::cout << "Scramble: " << scramble << '\n';
        std::cout << "Cross solution: " << crossSolution << '\n';

        for(std::vector<int> alg : f2l_sol){
            for(int move : alg){
                std::cout << ACTIONS.at(move) << " ";
            }
            std::cout << '\n';
        }

        all_sol.push_back(f2l_sol);
    }
    int endTime_main = clock();
    std::cout << "COMPLETE TIME: " << (endTime_main - startTime_main) / (double) CLOCKS_PER_SEC << '\n';

    return all_sol;
}

int main(){
    std::string scramble = "D' F2 U2 L B D' R' F' L U' F' L' U' B2 D F2 R D L F U' L' F";
    std::string crossSolution = "F B' R F D B2";

    std::vector<std::vector<std::vector<int>>> all_sol = getSolutions(scramble, crossSolution);

    std::cout << "Solutions from getSolutions: " << '\n';
    for(std::vector<std::vector<int>> f2l_sol : all_sol){
        for(std::vector<int> alg : f2l_sol){
            for(int move : alg){
                std::cout << ACTIONS.at(move) << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    std::vector<int> order = {0, 1, 2, 3};
    std::vector<std::vector<std::vector<int>>> all_sol_one_by_one = getSolutionsOneByOne(scramble, crossSolution, order);

    std::cout << "Solutions from getSolutionsOneByOne: " << '\n';
    for(std::vector<std::vector<int>> f2l_sol : all_sol_one_by_one){
        for(std::vector<int> alg : f2l_sol){
            for(int move : alg){
                std::cout << ACTIONS.at(move) << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    return 0;
};