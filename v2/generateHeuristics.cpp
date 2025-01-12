#include "cubiecube.h"
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

const std::array<CubieCube, 18> MOVE_CUBE = initialize_move_cube();

const std::unordered_map<int, std::string> ACTIONS = {
    {0, "U"}, {1, "R"}, {2, "F"}, {3, "D"}, {4, "L"}, {5, "B"},
    {6, "U2"}, {7, "R2"}, {8, "F2"}, {9, "D2"}, {10, "L2"}, {11, "B2"},
    {12, "U'"}, {13, "R'"}, {14, "F'"}, {15, "D'"}, {16, "L'"}, {17, "B'"}
};

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

std::string binaryToHex(const std::string& binary) {
    std::string hex;
    int length = binary.size();

    int padding = (4 - (length % 4)) % 4;
    std::string paddedBinary = std::string(padding, '0') + binary;

    for (size_t i = 0; i < paddedBinary.size(); i += 4) {
        std::string nibble = paddedBinary.substr(i, 4);
        int decimalValue = std::stoi(nibble, nullptr, 2);
        hex += "0123456789ABCDEF"[decimalValue];
    }

    return hex;
}

std::string convertToKey(CubieCube cube){
    std::string key = "";
    std::array<Corner, 8> cp = cube.get_cpf();
    std::array<int, 8> co = cube.get_cof();

    for(int i = 0; i < 8; i++){
        int currentValue = -1;
        if(cp[i] != Corner(-1)){
            currentValue = static_cast<int>(cp[i]);
        }
        if(currentValue == -1){
            key += "111";
        }else if(currentValue == 0){
            key += "000";
        }else if(currentValue == 1){
            key += "001";
        }else if(currentValue == 2){
            key += "010";
        }else if(currentValue == 3){
            key += "011";
        }
    }

    for(int i = 0; i < 8; i++){
        int currentValue = co[i];
        if(currentValue == -1){
            key += "111";
        }else if(currentValue == 0){
            key += "000";
        }else if(currentValue == 1){
            key += "001";
        }else if(currentValue == 2){
            key += "010";
        }else if(currentValue == 3){
            key += "011";
        }
    }

    key = binaryToHex(key);

    return key;
}

void generateHeur(int numberOfMoves, CubieCube cube, const int maxDepth, std::unordered_map<std::string, int>& heur) {
    if (numberOfMoves == 0) return;

    for (int i = 0; i < 18; i++) {
        std::string action = ACTIONS.at(i);
        CubieCube newCube = actionsWithNotations(action, cube);
        std::string key = convertToKey(newCube);
        if (heur.find(key) == heur.end()) {
            heur[key] = maxDepth - numberOfMoves;
            generateHeur(numberOfMoves - 1, newCube, maxDepth, heur);
        }
    }
}

int main(){
    std::vector<Corner> corners = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR};
    CubieCube cube(corners);
    
    std::unordered_map<std::string, int> heur;
    generateHeur(8, cube, 8, heur);

    for(auto const& [key, value] : heur){
        std::cout << key << " " << value << std::endl;
    }

    std::cout << heur.size() << std::endl;

    return 0;
}