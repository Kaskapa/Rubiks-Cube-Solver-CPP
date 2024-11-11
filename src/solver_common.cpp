#include "solver_common.h"

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

CubieCube actionsWithNotations(const std::string& action, CubieCube cube) {
    if(action == "U") cube.move(MOVE_CUBE[0]);
    else if(action == "R") cube.move(MOVE_CUBE[1]);
    else if(action == "F") cube.move(MOVE_CUBE[2]);
    else if(action == "D") cube.move(MOVE_CUBE[3]);
    else if(action == "L") cube.move(MOVE_CUBE[4]);
    else if(action == "B") cube.move(MOVE_CUBE[5]);
    else if(action == "U'") cube.move(MOVE_CUBE[12]);
    else if(action == "R'") cube.move(MOVE_CUBE[13]);
    else if(action == "F'") cube.move(MOVE_CUBE[14]);
    else if(action == "D'") cube.move(MOVE_CUBE[15]);
    else if(action == "L'") cube.move(MOVE_CUBE[16]);
    else if(action == "B'") cube.move(MOVE_CUBE[17]);
    else if(action == "U2") cube.move(MOVE_CUBE[6]);
    else if(action == "R2") cube.move(MOVE_CUBE[7]);
    else if(action == "F2") cube.move(MOVE_CUBE[8]);
    else if(action == "D2") cube.move(MOVE_CUBE[9]);
    else if(action == "L2") cube.move(MOVE_CUBE[10]);
    else if(action == "B2") cube.move(MOVE_CUBE[11]);
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