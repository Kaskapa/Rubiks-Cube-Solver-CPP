#include "pieces.h"
#include <array>
#include <string>
#include <vector>
#ifndef FACECUBE_H
#define FACECUBE_H

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

class FaceCube {
public:
    FaceCube() : f{
        Color::U, Color::U, Color::U,
        Color::U, Color::U, Color::U,
        Color::U, Color::U, Color::U,
        Color::R, Color::R, Color::R,
        Color::R, Color::R, Color::R,
        Color::R, Color::R, Color::R,
        Color::F, Color::F, Color::F,
        Color::F, Color::F, Color::F,
        Color::F, Color::F, Color::F,
        Color::D, Color::D, Color::D,
        Color::D, Color::D, Color::D,
        Color::D, Color::D, Color::D,
        Color::L, Color::L, Color::L,
        Color::L, Color::L, Color::L,
        Color::L, Color::L, Color::L,
        Color::B, Color::B, Color::B,
        Color::B, Color::B, Color::B,
        Color::B, Color::B, Color::B
    } {}

    std::string to_string() const {
        std::string result;
        for (const auto& color : f) {
            result += static_cast<char>(color);
        }
        return result;
    }

private:
    std::array<Color, 54> f;
};

#endif