#ifndef PIECES_H
#define PIECES_H

#include <cstdint>

// Enum for the colors of the Rubik's Cube
enum class Color : uint8_t {
    U = 0, // Up
    R = 1, // Right
    F = 2, // Front
    D = 3, // Down
    L = 4, // Left
    B = 5  // Back
};

// Enum for the corners of the Rubik's Cube
enum class Corner : uint8_t {
    URF = 0, // Up-Right-Front
    UFL = 1, // Up-Front-Left
    ULB = 2, // Up-Left-Back
    UBR = 3, // Up-Back-Right
    DFR = 4, // Down-Front-Right
    DLF = 5, // Down-Left-Front
    DBL = 6, // Down-Back-Left
    DRB = 7  // Down-Right-Back
};

// Enum for the edges of the Rubik's Cube
enum class Edge : uint8_t {
    UR = 0, // Up-Right
    UF = 1, // Up-Front
    UL = 2, // Up-Left
    UB = 3, // Up-Back
    DR = 4, // Down-Right
    DF = 5, // Down-Front
    DL = 6, // Down-Left
    DB = 7, // Down-Back
    FR = 8, // Front-Right
    FL = 9, // Front-Left
    BL = 10, // Back-Left
    BR = 11  // Back-Right
};

// Enum for the facelets of the Rubik's Cube
enum class Facelet : uint8_t {
    U1 = 0, U2 = 1, U3 = 2, U4 = 3, U5 = 4, U6 = 5, U7 = 6, U8 = 7, U9 = 8,
    R1 = 9, R2 = 10, R3 = 11, R4 = 12, R5 = 13, R6 = 14, R7 = 15, R8 = 16, R9 = 17,
    F1 = 18, F2 = 19, F3 = 20, F4 = 21, F5 = 22, F6 = 23, F7 = 24, F8 = 25, F9 = 26,
    D1 = 27, D2 = 28, D3 = 29, D4 = 30, D5 = 31, D6 = 32, D7 = 33, D8 = 34, D9 = 35,
    L1 = 36, L2 = 37, L3 = 38, L4 = 39, L5 = 40, L6 = 41, L7 = 42, L8 = 43, L9 = 44,
    B1 = 45, B2 = 46, B3 = 47, B4 = 48, B5 = 49, B6 = 50, B7 = 51, B8 = 52, B9 = 53
};

// Utility functions or constants related to pieces can be added here

#endif // PIECES_H