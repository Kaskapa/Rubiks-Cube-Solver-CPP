#ifndef CUBIECUBE_H
#define CUBIECUBE_H

#include <set>
#include <cstdint>
#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <vector>
#include "pieces.h"

// Constants for various cube states
extern const std::array<Corner, 8> _cpU;
extern const std::array<int, 8> _coU;
extern const std::array<Edge, 12> _epU;
extern const std::array<int, 12> _eoU;

extern const std::array<Corner, 8> _cpU2;
extern const std::array<int, 8> _coU2;
extern const std::array<Edge, 12> _epU2;
extern const std::array<int, 12> _eoU2;

extern const std::array<Corner, 8> _cpUP;
extern const std::array<int, 8> _coUP;
extern const std::array<Edge, 12> _epUP;
extern const std::array<int, 12> _eoUP;

extern const std::array<Corner, 8> _cpR;
extern const std::array<int, 8> _coR;
extern const std::array<Edge, 12> _epR;
extern const std::array<int, 12> _eoR;

extern const std::array<Corner, 8> _cpR2;
extern const std::array<int, 8> _coR2;
extern const std::array<Edge, 12> _epR2;
extern const std::array<int, 12> _eoR2;

extern const std::array<Corner, 8> _cpRP;
extern const std::array<int, 8> _coRP;
extern const std::array<Edge, 12> _epRP;
extern const std::array<int, 12> _eoRP;

extern const std::array<Corner, 8> _cpF;
extern const std::array<int, 8> _coF;
extern const std::array<Edge, 12> _epF;
extern const std::array<int, 12> _eoF;

extern const std::array<Corner, 8> _cpF2;
extern const std::array<int, 8> _coF2;
extern const std::array<Edge, 12> _epF2;
extern const std::array<int, 12> _eoF2;

extern const std::array<Corner, 8> _cpFP;
extern const std::array<int, 8> _coFP;
extern const std::array<Edge, 12> _epFP;
extern const std::array<int, 12> _eoFP;

extern const std::array<Corner, 8> _cpD;
extern const std::array<int, 8> _coD;
extern const std::array<Edge, 12> _epD;
extern const std::array<int, 12> _eoD;

extern const std::array<Corner, 8> _cpD2;
extern const std::array<int, 8> _coD2;
extern const std::array<Edge, 12> _epD2;
extern const std::array<int, 12> _eoD2;

extern const std::array<Corner, 8> _cpDP;
extern const std::array<int, 8> _coDP;
extern const std::array<Edge, 12> _epDP;
extern const std::array<int, 12> _eoDP;

extern const std::array<Corner, 8> _cpL;
extern const std::array<int, 8> _coL;
extern const std::array<Edge, 12> _epL;
extern const std::array<int, 12> _eoL;

extern const std::array<Corner, 8> _cpL2;
extern const std::array<int, 8> _coL2;
extern const std::array<Edge, 12> _epL2;
extern const std::array<int, 12> _eoL2;

extern const std::array<Corner, 8> _cpLP;
extern const std::array<int, 8> _coLP;
extern const std::array<Edge, 12> _epLP;
extern const std::array<int, 12> _eoLP;

extern const std::array<Corner, 8> _cpB;
extern const std::array<int, 8> _coB;
extern const std::array<Edge, 12> _epB;
extern const std::array<int, 12> _eoB;

extern const std::array<Corner, 8> _cpB2;
extern const std::array<int, 8> _coB2;
extern const std::array<Edge, 12> _epB2;
extern const std::array<int, 12> _eoB2;

extern const std::array<Corner, 8> _cpBP;
extern const std::array<int, 8> _coBP;
extern const std::array<Edge, 12> _epBP;
extern const std::array<int, 12> _eoBP;

extern const std::array<Corner, 8> _corners;
extern const std::array<Edge, 12> _edges;
extern const std::set<Edge> _edgesCross_set;

class CubieCube {
public:
    CubieCube(const std::vector<Corner>& corners = {}, const std::vector<Edge>& edges = {});
    CubieCube(const CubieCube& other);

    void corner_multiply(const CubieCube& b);
    void edge_multiply(const CubieCube& b);
    void move(CubieCube b);

    void set_cp(const std::array<Corner, 8>& cp);
    void set_co(const std::array<int, 8>& co);
    void set_ep(const std::array<Edge, 12>& ep);
    void set_eo(const std::array<int, 12>& eo);
    void set_epc(const std::array<Edge, 12>& epc);
    void set_eoc(const std::array<int, 12>& eoc);
    void set_epf(const std::array<Edge, 12>& epf);
    void set_eof(const std::array<int, 12>& eof);
    void set_cpf(const std::array<Corner, 8>& cpf);
    void set_cof(const std::array<int, 8>& cof);

    std::array<Corner ,8> get_cp() const;
    std::array<int, 8> get_co() const;
    std::array<Edge, 12> get_ep() const;
    std::array<int, 12> get_eo() const;
    std::array<Edge, 12> get_epc() const;
    std::array<int, 12> get_eoc() const;
    std::array<Edge, 12> get_epf() const;
    std::array<int, 12> get_eof() const;
    std::array<Corner, 8> get_cpf() const;
    std::array<int, 8> get_cof() const;

private:
    std::array<Corner, 8> cp;
    std::array<int, 8> co;
    std::array<Edge, 12> ep;
    std::array<int, 12> eo;
    std::array<Edge, 12> epc;
    std::array<int, 12> eoc;
    std::array<Edge, 12> epf;
    std::array<int, 12> eof;
    std::vector<Corner> corners;
    std::vector<Edge> edges;
    std::array<Corner, 8> cpf;
    std::array<int, 8> cof;
};

std::array<CubieCube, 18> initialize_move_cube();

#endif // CUBIECUBE_H