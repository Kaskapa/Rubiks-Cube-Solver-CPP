#include "idaStarF2l.h"

IDA_star_F2L::IDA_star_F2L(std::vector<Corner> corners, std::vector<Edge> edges, std::string cornerStr, std::string edgeStr, int max_depth){
    this->max_depth = max_depth;
    CubieCube cubeCheck = CubieCube(corners, edges);
    this->goal_cross_state = get_cross_state(cubeCheck);
    this->goal_corner_state = get_corner_state(cubeCheck);
    this->goal_edge_state = get_edge_state(cubeCheck);
    this->crossHeur = tableLoader.getHeuristics("cross");
    this->cornerHeur = tableLoader.getHeuristics(cornerStr);
    this->edgeHeur = tableLoader.getHeuristics(edgeStr);
    this->corners = corners;
    this->edges = edges;

}

std::vector<int> IDA_star_F2L::run(CubieCube cube) {
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

int IDA_star_F2L::search(CubieCube cube, int g_score, int threshold) {
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

    if (is_goal_state(get_cross_state(cube), goal_cross_state, goal_edge_state, goal_corner_state, get_edge_state(cube), get_corner_state(cube))) {
        transposition_table[cube_state] = {g_score, 0};
        return 0;
    }

    int min_cost = std::numeric_limits<int>::max();
    for (int action = 0; action < 18; ++action) {
        CubieCube cube_copy = cube;
        cube_copy.move(MOVE_CUBE[action]);

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

std::string IDA_star_F2L::get_cube_state(const CubieCube& cube) {
    std::string state = get_cross_state(cube) + " " + get_edge_state(cube) + " " + get_corner_state(cube);
    return state;
}

std::string IDA_star_F2L::get_cross_state(const CubieCube& cube) {
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

std::string IDA_star_F2L::get_edge_state(const CubieCube& cube) {
    std::string edgeState = "(";
    std::array<Edge, 12> epf = cube.get_epf();
    std::array<int, 12> eof = cube.get_eof();

    for(int i = 0; i < 12; i++){
        if(epf[i] == Edge::FR){
            edgeState += "<Edge.FR: 8>, ";
        } else if(epf[i] == Edge::BR){
            edgeState += "<Edge.BR: 11>, ";
        } else if(epf[i] == Edge::BL){
            edgeState += "<Edge.BL: 10>, ";
        } else if(epf[i] == Edge::FL){
            edgeState += "<Edge.FL: 9>, ";
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

std::string IDA_star_F2L::get_corner_state(const CubieCube& cube) {
    std::string cornerState = "(";
    std::array<Corner, 8> cpf = cube.get_cpf();
    std::array<int, 8> cof = cube.get_cof();

    for(int i = 0; i < 8; i++){
        if(cpf[i] == Corner::URF){
            cornerState += "<Corner.URF: 0>, ";
        } else if(cpf[i] == Corner::UFL){
            cornerState += "<Corner.UFL: 1>, ";
        } else if(cpf[i] == Corner::UBR){
            cornerState += "<Corner.UBR: 3>, ";
        } else if(cpf[i] == Corner::ULB){
            cornerState += "<Corner.ULB: 2>, ";
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

int IDA_star_F2L::heuristic_value(const CubieCube& cube) {
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

bool IDA_star_F2L::is_goal_state(std::string crossState, std::string goal_cross_state, std::string goal_edge_stae, std::string goal_corner_state, std::string edge_state, std::string corner_state) {
    return crossState == goal_cross_state && edge_state == goal_edge_stae && corner_state == goal_corner_state;
}

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
                    cube.move(MOVE_CUBE[f2l_sol[k][l]]);
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

// int main(){
//     std::string scramble = "D' F2 U2 L B D' R' F' L U' F' L' U' B2 D F2 R D L F U' L' F";
//     std::string crossSolution = "F B' R F D B2";

//     std::vector<std::vector<std::vector<int>>> all_sol = getSolutions(scramble, crossSolution);

//     std::cout << "Solutions: " << '\n';
//     for(std::vector<std::vector<int>> f2l_sol : all_sol){
//         for(std::vector<int> alg : f2l_sol){
//             for(int move : alg){
//                 std::cout << ACTIONS.at(move) << " ";
//             }
//             std::cout << '\n';
//         }
//         std::cout << '\n';
//     }

//     return 0;
// };