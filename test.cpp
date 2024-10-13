#include <iostream>
#include "cubiecube.h"
#include "pieces.h"
#include "tableloader.h"

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

int main(){
    CubieCube cube = CubieCube();

    std::cout << to_facecube_state_corner(cube) << std::endl;
    std::cout << to_facecube_state_edge(cube) << std::endl;

    return 0;
};