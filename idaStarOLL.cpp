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

// Maps corner positions to facelet positions
const std::array<std::array<Facelet, 3>, 8> corner_facelet = {{
    {Facelet::U9, Facelet::R1, Facelet::F3},
    {Facelet::U7, Facelet::F1, Facelet::L3},
    {Facelet::U1, Facelet::L1, Facelet::B3},
    {Facelet::U3, Facelet::B1, Facelet::R3},
    {Facelet::D3, Facelet::F9, Facelet::R7},
    {Facelet::D1, Facelet::L9, Facelet::F7},
    {Facelet::D7, Facelet::B9, Facelet::L7},
    {Facelet::D9, Facelet::R9, Facelet::B7}
}};

// Maps edge positions to facelet positions
const std::array<std::array<Facelet, 2>, 12> edge_facelet = {{
    {Facelet::U6, Facelet::R2},
    {Facelet::U8, Facelet::F2},
    {Facelet::U4, Facelet::L2},
    {Facelet::U2, Facelet::B2},
    {Facelet::D6, Facelet::R8},
    {Facelet::D2, Facelet::F8},
    {Facelet::D4, Facelet::L8},
    {Facelet::D8, Facelet::B8},
    {Facelet::F6, Facelet::R4},
    {Facelet::F4, Facelet::L6},
    {Facelet::B6, Facelet::L4},
    {Facelet::B4, Facelet::R6}
}};

// Maps corner positions to colours
const std::array<std::array<Color, 3>, 8> corner_color = {{
    {Color::U, Color::R, Color::F},
    {Color::U, Color::F, Color::L},
    {Color::U, Color::L, Color::B},
    {Color::U, Color::B, Color::R},
    {Color::D, Color::F, Color::R},
    {Color::D, Color::L, Color::F},
    {Color::D, Color::B, Color::L},
    {Color::D, Color::R, Color::B}
}};

// Maps edge positions to colours
const std::array<std::array<Color, 2>, 12> edge_color = {{
    {Color::U, Color::R},
    {Color::U, Color::F},
    {Color::U, Color::L},
    {Color::U, Color::B},
    {Color::D, Color::R},
    {Color::D, Color::F},
    {Color::D, Color::L},
    {Color::D, Color::B},
    {Color::F, Color::R},
    {Color::F, Color::L},
    {Color::B, Color::L},
    {Color::B, Color::R}
}};

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

bool is_goal_state(std::string crossState, std::string goal_cross_state, std::string goal_edge_stae, std::string goal_corner_state, std::string edge_state, std::string corner_state, std::string goal_edge_oll_state, std::string goal_corner_oll_state, std::string edge_oll_state, std::string corner_oll_state) {
    return crossState == goal_cross_state && edge_state == goal_edge_stae && corner_state == goal_corner_state && edge_oll_state == goal_edge_oll_state && corner_oll_state == goal_corner_oll_state;
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

class IDA_star_OLL {
public:
    IDA_star_OLL(int max_depth = 100){
        this->max_depth = max_depth;
        CubieCube cubeCheck = CubieCube();
        this->goal_cross_state = get_cross_state(cubeCheck);
        this->goal_corner_state = get_corner_state(cubeCheck);
        this->goal_edge_stae = get_edge_state(cubeCheck);
        this->goal_edge_oll_state = to_facecube_state_edge(cubeCheck);
        this->goal_corner_oll_state = to_facecube_state_corner(cubeCheck);
        this->crossHeur = std::move(tableLoader.getHeuristics("cross"));
        this->cornerHeur = std::move(tableLoader.getHeuristics("0123"));
        this->edgeHeur = std::move(tableLoader.getHeuristics("891011"));
        this->cornerOLLHeur = std::move(tableLoader.getHeuristics("cornerOLL"));
        this->edgeOLLHeur = std::move(tableLoader.getHeuristics("edgeOLL"));

    }

    std::vector<int> run(CubieCube cube) {
        int threshold = heuristic_value(cube);
        while (threshold <= max_depth) {
            std::cout << "Threshold: " << threshold << '\n';
            moves.clear();
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
    std::string goal_cross_state;
    std::string goal_corner_state;
    std::string goal_edge_stae;
    std::string goal_edge_oll_state;
    std::string goal_corner_oll_state;
    std::unordered_map<std::string, int> crossHeur;
    std::unordered_map<std::string, int> cornerHeur;
    std::unordered_map<std::string, int> edgeHeur;
    std::unordered_map<std::string, int> cornerOLLHeur;
    std::unordered_map<std::string, int> edgeOLLHeur;

    int search(CubieCube cube, int g_score, int threshold) {
        // std::string cube_state = get_cube_state(cube);

        int f_score = g_score + heuristic_value(cube);
        if (f_score > threshold) {
            return f_score;
        }

        if (is_goal_state(get_cross_state(cube), goal_cross_state, goal_edge_stae, goal_corner_state, get_edge_state(cube), get_corner_state(cube), to_facecube_state_edge(cube), to_facecube_state_corner(cube), goal_edge_oll_state, goal_corner_oll_state)) {
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

        return min_cost;
    }

    std::string get_cube_state(const CubieCube& cube) {
        std::string state = get_cross_state(cube) + " " + get_edge_state(cube) + " " + get_corner_state(cube) + " " + to_facecube_state_edge(cube) + " " + to_facecube_state_corner(cube);
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

    std::string to_facecube_state_corner(const CubieCube& cube) {
        std::string ret(54, '-');
        int index_d = 0;

        for (int i = 0; i < 8 && index_d < 4; ++i) {
            int j = static_cast<int>(cube.get_cp()[i]);
            int ori = cube.get_co()[i];

            for (int k = 0; k < 3; ++k) {
                if (corner_color[j][k] == Color::D) {
                    ++index_d;
                    int index = static_cast<int>(corner_facelet[i][(k + ori) % 3]);
                    ret[index] = 'D';
                }
            }
        }
        return ret;
    }

    std::string to_facecube_state_edge(const CubieCube& cube) {
        std::string ret(54, '-');
        int index_d = 0;

        for (int i = 0; i < 12 && index_d < 4; ++i) {
            int j = static_cast<int>(cube.get_ep()[i]);
            int ori = cube.get_eo()[i];

            for (int k = 0; k < 2; ++k) {
                if (edge_color[j][k] == Color::D) {
                    ++index_d;
                    int index = static_cast<int>(edge_facelet[i][(k + ori) % 3]);
                    ret[index] = 'D';
                }
            }
        }
        return ret;
    }
    inline int heuristic_value(const CubieCube& cube) {
        std::string stateCross = get_cross_state(cube);
        std::string stateEdge = get_edge_state(cube);
        std::string stateCorner = get_corner_state(cube);
        std::string stateCornerOLL = to_facecube_state_corner(cube);
        std::string stateEdgeOLL = to_facecube_state_edge(cube);

        auto itCross = crossHeur.find(stateCross);
        auto itEdge = edgeHeur.find(stateEdge);
        auto itCorner = cornerHeur.find(stateCorner);
        auto itCornerOLL = cornerOLLHeur.find(stateCornerOLL);
        auto itEdgeOLL = edgeOLLHeur.find(stateEdgeOLL);

        int h_cross = 5,  h_edge = 5,  h_corner = 5, h_corner_oll = 5, h_edge_oll = 5;

        if (itCross != crossHeur.end()) {
            h_cross = crossHeur[stateCross] - 1;
        }
        if(itEdge != edgeHeur.end()){
            h_edge = edgeHeur[stateEdge];
        }
        if(itCorner != cornerHeur.end()){
            h_corner = cornerHeur[stateCorner];
        }
        if(itCornerOLL != cornerOLLHeur.end()){
            h_corner_oll = cornerOLLHeur[stateCornerOLL];
        }
        if(itEdgeOLL != edgeOLLHeur.end()){
            h_edge_oll = edgeOLLHeur[stateEdgeOLL];
        }

        int h_f2l = std::max({h_edge, h_corner, h_cross});
        int h_oll = h_corner_oll + h_edge_oll;

        return h_f2l+h_oll;
    }
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    CubieCube cube = CubieCube();
    // std::string scramble = "F D L D' L' F'";
    // std::cout << "Scramble: ";
    std::string scramble = "F L D L' D' L D L' D' F'";
    // std::string scramble = "L D L' D L D' L' D L D2 L'";
    // std::getline(std::cin, scramble);
    int startTime = clock();
    cube = do_algorithm(scramble, cube);
    IDA_star_OLL ida_star_cross = IDA_star_OLL();
    std::vector<int> solution = ida_star_cross.run(cube);

    for (int action : solution) {
        std::cout << ACTIONS.at(action) << " ";
    }
    std::cout << '\n';

    int endTime = clock();
    std::cout << "Time: " << (endTime - startTime) / (double) CLOCKS_PER_SEC << '\n';

    return 0;
};