#ifndef SOLVER_COMMON_H
#define SOLVER_COMMON_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <tuple>

#include "cubiecube.h"
#include "tableloader.h"
#include "pieces.h"

extern Tableloader tableLoader;
extern const std::array<CubieCube, 18> MOVE_CUBE;
extern const std::unordered_map<int, std::string> ACTIONS;
extern const std::unordered_map<int, std::vector<int>> REDUNDANT_ACTIONS;
extern const std::unordered_map<int, std::vector<int>> REDUNDANT_ACTIONS_2;

CubieCube actionsWithNotations(const std::string& action, CubieCube cube);
CubieCube do_algorithm(const std::string& algorithm, CubieCube cube);

#endif // SOLVER_COMMON_H