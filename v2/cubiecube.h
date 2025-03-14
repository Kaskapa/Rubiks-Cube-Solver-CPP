#include <set>
#include <cstdint>
#include <iostream>
#include <array>
#include <array>
#include "pieces.h"
#include <string>
#include <algorithm>
#include <vector>
#ifndef CUBIECUBE_H
#define CUBIECUBE_H

const std::array<Corner, 8> _cpU = {
    Corner::UBR ,Corner::URF, Corner::UFL, Corner::ULB,
    Corner::DFR, Corner::DLF, Corner::DBL, Corner::DRB
};

const std::array<int, 8> _coU = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epU = {
    Edge::UB, Edge::UR, Edge::UF,
    Edge::UL, Edge::DR, Edge::DF,
    Edge::DL, Edge::DB, Edge::FR,
    Edge::FL, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoU = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpU2 = {
    Corner::ULB, Corner::UBR, Corner::URF, Corner::UFL,
    Corner::DFR, Corner::DLF, Corner::DBL, Corner::DRB
};

const std::array<int, 8> _coU2 = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epU2 = {
    Edge::UL, Edge::UB, Edge::UR, Edge::UF,
    Edge::DR, Edge::DF, Edge::DL, Edge::DB,
    Edge::FR, Edge::FL, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoU2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpUP = {
    Corner::UFL, Corner::ULB, Corner::UBR, Corner::URF,
    Corner::DFR, Corner::DLF, Corner::DBL, Corner::DRB
};

const std::array<int, 8> _coUP = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epUP = {
    Edge::UF, Edge::UL, Edge::UB, Edge::UR,
    Edge::DR, Edge::DF, Edge::DL, Edge::DB,
    Edge::FR, Edge::FL, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoUP = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpR = {
    Corner::DFR, Corner::UFL, Corner::ULB, Corner::URF,
    Corner::DRB, Corner::DLF, Corner::DBL, Corner::UBR
};

const std::array<int, 8> _coR = {2, 0, 0, 1, 1, 0, 0, 2};

const std::array<Edge, 12> _epR = {
    Edge::FR, Edge::UF, Edge::UL, Edge::UB,
    Edge::BR, Edge::DF, Edge::DL, Edge::DB,
    Edge::DR, Edge::FL, Edge::BL, Edge::UR
};

const std::array<int, 12> _eoR = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpR2 = {
    Corner::DRB, Corner::UFL, Corner::ULB, Corner::DFR,
    Corner::UBR, Corner::DLF, Corner::DBL, Corner::URF
};

const std::array<int, 8> _coR2 = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epR2 = {
    Edge::DR, Edge::UF, Edge::UL, Edge::UB,
    Edge::UR, Edge::DF, Edge::DL, Edge::DB,
    Edge::BR, Edge::FL, Edge::BL, Edge::FR
};

const std::array<int, 12> _eoR2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpRP = {
    Corner::UBR, Corner::UFL, Corner::ULB, Corner::DRB,
    Corner::URF, Corner::DLF, Corner::DBL, Corner::DFR
};

const std::array<int, 8> _coRP = {2, 0, 0, 1, 1, 0, 0, 2};

const std::array<Edge, 12> _epRP = {
    Edge::BR, Edge::UF, Edge::UL, Edge::UB,
    Edge::FR, Edge::DF, Edge::DL, Edge::DB,
    Edge::UR, Edge::FL, Edge::BL, Edge::DR
};

const std::array<int, 12> _eoRP = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpF = {
    Corner::UFL, Corner::DLF, Corner::ULB, Corner::UBR,
    Corner::URF, Corner::DFR, Corner::DBL, Corner::DRB
};

const std::array<int, 8> _coF = {1, 2, 0, 0, 2, 1, 0, 0};

const std::array<Edge, 12> _epF = {
    Edge::UR, Edge::FL, Edge::UL, Edge::UB,
    Edge::DR, Edge::FR, Edge::DL, Edge::DB,
    Edge::UF, Edge::DF, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoF = {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};

const std::array<Corner, 8> _cpF2 = {
    Corner::DLF, Corner::DFR, Corner::ULB, Corner::UBR,
    Corner::UFL, Corner::URF, Corner::DBL, Corner::DRB
};

const std::array<int, 8> _coF2 = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epF2 = {
    Edge::UR, Edge::DF, Edge::UL, Edge::UB,
    Edge::DR, Edge::UF, Edge::DL, Edge::DB,
    Edge::FL, Edge::FR, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoF2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpFP = {
    Corner::DFR, Corner::URF, Corner::ULB, Corner::UBR,
    Corner::DLF, Corner::UFL, Corner::DBL, Corner::DRB
};

const std::array<int, 8> _coFP = {1, 2, 0, 0, 2, 1, 0, 0};

const std::array<Edge, 12> _epFP = {
    Edge::UR, Edge::FR, Edge::UL, Edge::UB,
    Edge::DR, Edge::FL, Edge::DL, Edge::DB,
    Edge::DF, Edge::UF, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoFP = {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};

const std::array<Corner, 8> _cpD = {
    Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR,
    Corner::DLF, Corner::DBL, Corner::DRB, Corner::DFR
};

const std::array<int, 8> _coD = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epD = {
    Edge::UR, Edge::UF, Edge::UL, Edge::UB,
    Edge::DF, Edge::DL, Edge::DB, Edge::DR,
    Edge::FR, Edge::FL, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoD = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpD2 = {
    Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR,
    Corner::DBL, Corner::DRB, Corner::DFR, Corner::DLF
};

const std::array<int, 8> _coD2 = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epD2 = {
    Edge::UR, Edge::UF, Edge::UL, Edge::UB,
    Edge::DL, Edge::DB, Edge::DR, Edge::DF,
    Edge::FR, Edge::FL, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoD2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpDP = {
    Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR,
    Corner::DRB, Corner::DFR, Corner::DLF, Corner::DBL
};

const std::array<int, 8> _coDP = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epDP = {
    Edge::UR, Edge::UF, Edge::UL, Edge::UB,
    Edge::DB, Edge::DR, Edge::DF, Edge::DL,
    Edge::FR, Edge::FL, Edge::BL, Edge::BR
};

const std::array<int, 12> _eoDP = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpL = {
    Corner::URF, Corner::ULB, Corner::DBL, Corner::UBR,
    Corner::DFR, Corner::UFL, Corner::DLF, Corner::DRB
};

const std::array<int, 8> _coL = {0, 1, 2, 0, 0, 2, 1, 0};

const std::array<Edge, 12> _epL = {
    Edge::UR, Edge::UF, Edge::BL, Edge::UB,
    Edge::DR, Edge::DF, Edge::FL, Edge::DB,
    Edge::FR, Edge::UL, Edge::DL, Edge::BR
};

const std::array<int, 12> _eoL = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpL2 = {
    Corner::URF, Corner::DBL, Corner::DLF, Corner::UBR,
    Corner::DFR, Corner::ULB, Corner::UFL, Corner::DRB
};

const std::array<int, 8> _coL2 = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epL2 = {
    Edge::UR, Edge::UF, Edge::DL, Edge::UB,
    Edge::DR, Edge::DF, Edge::UL, Edge::DB,
    Edge::FR, Edge::BL, Edge::FL, Edge::BR
};

const std::array<int, 12> _eoL2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpLP = {
    Corner::URF, Corner::DLF, Corner::UFL, Corner::UBR,
    Corner::DFR, Corner::DBL, Corner::ULB, Corner::DRB
};

const std::array<int, 8> _coLP = {0, 1, 2, 0, 0, 2, 1, 0};

const std::array<Edge, 12> _epLP = {
    Edge::UR, Edge::UF, Edge::FL, Edge::UB,
    Edge::DR, Edge::DF, Edge::BL, Edge::DB,
    Edge::FR, Edge::DL, Edge::UL, Edge::BR
};

const std::array<int, 12> _eoLP = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpB = {
    Corner::URF, Corner::UFL, Corner::UBR, Corner::DRB,
    Corner::DFR, Corner::DLF, Corner::ULB, Corner::DBL
};

const std::array<int, 8> _coB = {0, 0, 1, 2, 0, 0, 2, 1};

const std::array<Edge, 12> _epB = {
    Edge::UR, Edge::UF, Edge::UL, Edge::BR,
    Edge::DR, Edge::DF, Edge::DL, Edge::BL,
    Edge::FR, Edge::FL, Edge::UB, Edge::DB
};

const std::array<int, 12> _eoB = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1};

const std::array<Corner, 8> _cpB2 = {
    Corner::URF, Corner::UFL, Corner::DRB, Corner::DBL,
    Corner::DFR, Corner::DLF, Corner::UBR, Corner::ULB
};

const std::array<int, 8> _coB2 = {0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Edge, 12> _epB2 = {
    Edge::UR, Edge::UF, Edge::UL, Edge::DB,
    Edge::DR, Edge::DF, Edge::DL, Edge::UB,
    Edge::FR, Edge::FL, Edge::BR, Edge::BL
};

const std::array<int, 12> _eoB2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const std::array<Corner, 8> _cpBP = {
    Corner::URF, Corner::UFL, Corner::DBL, Corner::ULB,
    Corner::DFR, Corner::DLF, Corner::DRB, Corner::UBR
};

const std::array<int, 8> _coBP = {0, 0, 1, 2, 0, 0, 2, 1};

const std::array<Edge, 12> _epBP = {
    Edge::UR, Edge::UF, Edge::UL,
    Edge::BL, Edge::DR, Edge::DF,
    Edge::DL, Edge::BR, Edge::FR,
    Edge::FL, Edge::DB, Edge::UB
};

const std::array<int, 12> _eoBP = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1};

const std::array<Corner, 8> _corners = {
    Corner::URF,
    Corner::UFL,
    Corner::ULB,
    Corner::UBR,
    Corner::DFR,
    Corner::DLF,
    Corner::DBL,
    Corner::DRB
};

const std::array<Edge, 12> _edges = {
    Edge::UR,
    Edge::UF,
    Edge::UL,
    Edge::UB,
    Edge::DR,
    Edge::DF,
    Edge::DL,
    Edge::DB,
    Edge::FR,
    Edge::FL,
    Edge::BL,
    Edge::BR
};

const std::set<Edge> _edgesCross_set = {Edge::UF, Edge::UR, Edge::UL, Edge::UB};

class CubieCube {
public:
    CubieCube(const std::vector<Corner>& corners = {}, const std::vector<Edge>& edges = {}) {
        this->cp = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR, Corner::DFR, Corner::DLF, Corner::DBL, Corner::DRB};
        this->co = {0, 0, 0, 0, 0, 0, 0, 0};
        if (!corners.empty()) {
            for (int i = 0; i < 8; ++i) {
                this->cpf[i] = (std::find(corners.begin(), corners.end(), _corners[i]) != corners.end()) ? _corners[i] : Corner(-1);
                this->cof[i] = (std::find(corners.begin(), corners.end(), _corners[i]) != corners.end()) ? 0 : -1;
            }
            this->corners = corners;
        } else {
            this->cpf = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR, Corner(-1), Corner(-1), Corner(-1), Corner(-1)};
            this->cof = {0, 0, 0, 0, -1, -1, -1, -1};
            this->corners = {Corner::URF, Corner::UFL, Corner::ULB, Corner::UBR};
        }

        this->ep = {Edge::UR, Edge::UF, Edge::UL, Edge::UB, Edge::DR, Edge::DF, Edge::DL, Edge::DB, Edge::FR, Edge::FL, Edge::BL, Edge::BR};
        this->eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        this->epc = {Edge::UR, Edge::UF, Edge::UL, Edge::UB, Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1)};
        this->eoc = {0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1};

        if (!edges.empty()) {
            for (int i = 0; i < 12; ++i) {
                this->epf[i] = (std::find(edges.begin(), edges.end(), _edges[i]) != edges.end()) ? _edges[i] : Edge(-1);
                this->eof[i] = (std::find(edges.begin(), edges.end(), _edges[i]) != edges.end()) ? 0 : -1;
            }
            this->edges = edges;
        } else {
            this->epf = {Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge::FR, Edge::FL, Edge::BL, Edge::BR};
            this->eof = {-1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0};
            this->edges = {Edge::BL, Edge::BR, Edge::FR, Edge::FL};
        }

    }

    CubieCube(const CubieCube& other) {
        *this = other;
    }

    void corner_multiply(const CubieCube& b) {
        std::array<Corner, 8> corner_perm;
        std::array<int, 8> corner_ori;

        for (int i = 0; i < 8; ++i) {
            corner_perm[i] = cp[static_cast<int>(b.cp[i])];
            corner_ori[i] = (co[static_cast<int>(b.cp[i])] + b.co[i]) % 3;
        }

        cp = corner_perm;
        co = corner_ori;

        std::array<Corner, 8> corner_f2l_perm = {Corner(-1), Corner(-1), Corner(-1), Corner(-1), Corner(-1), Corner(-1), Corner(-1), Corner(-1)};
        std::array<int, 8> corner_f2l_ori = {-1, -1, -1, -1, -1, -1, -1, -1};

        int f2l_i = 0;

        for (int i = 0; i < 8; ++i) {
            if (f2l_i == corners.size()) {
                break;
            }

            Corner cp_i = corner_perm[i];
            int co_i = corner_ori[i];

            if (std::find(corners.begin(), corners.end(), cp_i) != corners.end()) {
                corner_f2l_perm[i] = cp_i;
                corner_f2l_ori[i] = co_i;
                ++f2l_i;
            }
        }

        cof = corner_f2l_ori;
        cpf = corner_f2l_perm;
    }

    void edge_multiply(const CubieCube& b) {
        std::array<Edge, 12> edge_perm;
        std::array<int, 12> edge_ori;

        for (int i = 0; i < 12; ++i) {
            edge_perm[i] = ep[static_cast<int>(b.ep[i])];
            edge_ori[i] = (eo[static_cast<int>(b.ep[i])] + b.eo[i]) % 2;
        }

        eo = edge_ori;
        ep = edge_perm;

        std::array<Edge, 12> edge_cross_perm = {Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1)};
        std::array<int, 12> edge_cross_ori = {-1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1, -1, -1};
        std::array<Edge, 12> edge_f2l_perm = {Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1), Edge(-1)};
        std::array<int, 12> edge_f2l_ori = {-1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1, -1, -1};

        int cross_i = 0;
        int f2l_i = 0;
        int self_edges_len = edges.size();

        for (int i = 0; i < 12; ++i) {
            if (cross_i == 4 && f2l_i == self_edges_len) {
                break;
            }

            Edge ep_i = edge_perm[i];
            int eo_i = edge_ori[i];

            if (_edgesCross_set.find(ep_i) != _edgesCross_set.end()) {
                edge_cross_perm[i] = ep_i;
                edge_cross_ori[i] = eo_i;
                ++cross_i;
            }

            if (std::find(edges.begin(), edges.end(), ep_i) != edges.end()) {
                edge_f2l_perm[i] = ep_i;
                edge_f2l_ori[i] = eo_i;
                ++f2l_i;
            }
        }

        eoc = edge_cross_ori;
        epc = edge_cross_perm;
        eof = edge_f2l_ori;
        epf = edge_f2l_perm;
    }

    void move(int i, CubieCube b) {
        corner_multiply(b);
        edge_multiply(b);
    }

    void set_cp(const std::array<Corner, 8>& cp) {
        this->cp = cp;
    }

    void set_co(const std::array<int, 8>& co) {
        this->co = co;
    }

    void set_ep(const std::array<Edge, 12>& ep) {
        this->ep = ep;
    }

    void set_eo(const std::array<int, 12>& eo) {
        this->eo = eo;
    }

    void set_epc(const std::array<Edge, 12>& epc) {
        this->epc = epc;
    }

    void set_eoc(const std::array<int, 12>& eoc) {
        this->eoc = eoc;
    }

    void set_epf(const std::array<Edge, 12>& epf) {
        this->epf = epf;
    }

    void set_eof(const std::array<int, 12>& eof) {
        this->eof = eof;
    }

    void set_cpf(const std::array<Corner, 8>& cpf) {
        this->cpf = cpf;
    }

    void set_cof(const std::array<int, 8>& cof) {
        this->cof = cof;
    }

    std::array<Corner ,8> get_cp() const {
        return cp;
    }

    std::array<int, 8> get_co() const {
        return co;
    }

    std::array<Edge, 12> get_ep() const {
        return ep;
    }

    std::array<int, 12> get_eo() const {
        return eo;
    }

    std::array<Edge, 12> get_epc() const {
        return epc;
    }

    std::array<int, 12> get_eoc() const {
        return eoc;
    }

    std::array<Edge, 12> get_epf() const {
        return epf;
    }

    std::array<int, 12> get_eof() const {
        return eof;
    }

    std::array<Corner, 8> get_cpf() const {
        return cpf;
    }

    std::array<int, 8> get_cof() const {
        return cof;
    }

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

std::array<CubieCube, 18> initialize_move_cube() {
    std::array<CubieCube, 18> MOVE_CUBE;

    MOVE_CUBE[0].set_cp(_cpU);
    MOVE_CUBE[0].set_co(_coU);
    MOVE_CUBE[0].set_ep(_epU);
    MOVE_CUBE[0].set_eo(_eoU);

    MOVE_CUBE[1].set_cp(_cpR);
    MOVE_CUBE[1].set_co(_coR);
    MOVE_CUBE[1].set_ep(_epR);
    MOVE_CUBE[1].set_eo(_eoR);

    MOVE_CUBE[2].set_cp(_cpF);
    MOVE_CUBE[2].set_co(_coF);
    MOVE_CUBE[2].set_ep(_epF);
    MOVE_CUBE[2].set_eo(_eoF);

    MOVE_CUBE[3].set_cp(_cpD);
    MOVE_CUBE[3].set_co(_coD);
    MOVE_CUBE[3].set_ep(_epD);
    MOVE_CUBE[3].set_eo(_eoD);

    MOVE_CUBE[4].set_cp(_cpL);
    MOVE_CUBE[4].set_co(_coL);
    MOVE_CUBE[4].set_ep(_epL);
    MOVE_CUBE[4].set_eo(_eoL);

    MOVE_CUBE[5].set_cp(_cpB);
    MOVE_CUBE[5].set_co(_coB);
    MOVE_CUBE[5].set_ep(_epB);
    MOVE_CUBE[5].set_eo(_eoB);

    MOVE_CUBE[6].set_cp(_cpU2);
    MOVE_CUBE[6].set_co(_coU2);
    MOVE_CUBE[6].set_ep(_epU2);
    MOVE_CUBE[6].set_eo(_eoU2);

    MOVE_CUBE[7].set_cp(_cpR2);
    MOVE_CUBE[7].set_co(_coR2);
    MOVE_CUBE[7].set_ep(_epR2);
    MOVE_CUBE[7].set_eo(_eoR2);

    MOVE_CUBE[8].set_cp(_cpF2);
    MOVE_CUBE[8].set_co(_coF2);
    MOVE_CUBE[8].set_ep(_epF2);
    MOVE_CUBE[8].set_eo(_eoF2);

    MOVE_CUBE[9].set_cp(_cpD2);
    MOVE_CUBE[9].set_co(_coD2);
    MOVE_CUBE[9].set_ep(_epD2);
    MOVE_CUBE[9].set_eo(_eoD2);

    MOVE_CUBE[10].set_cp(_cpL2);
    MOVE_CUBE[10].set_co(_coL2);
    MOVE_CUBE[10].set_ep(_epL2);
    MOVE_CUBE[10].set_eo(_eoL2);

    MOVE_CUBE[11].set_cp(_cpB2);
    MOVE_CUBE[11].set_co(_coB2);
    MOVE_CUBE[11].set_ep(_epB2);
    MOVE_CUBE[11].set_eo(_eoB2);

    MOVE_CUBE[12].set_cp(_cpUP);
    MOVE_CUBE[12].set_co(_coUP);
    MOVE_CUBE[12].set_ep(_epUP);
    MOVE_CUBE[12].set_eo(_eoUP);

    MOVE_CUBE[13].set_cp(_cpRP);
    MOVE_CUBE[13].set_co(_coRP);
    MOVE_CUBE[13].set_ep(_epRP);
    MOVE_CUBE[13].set_eo(_eoRP);

    MOVE_CUBE[14].set_cp(_cpFP);
    MOVE_CUBE[14].set_co(_coFP);
    MOVE_CUBE[14].set_ep(_epFP);
    MOVE_CUBE[14].set_eo(_eoFP);

    MOVE_CUBE[15].set_cp(_cpDP);
    MOVE_CUBE[15].set_co(_coDP);
    MOVE_CUBE[15].set_ep(_epDP);
    MOVE_CUBE[15].set_eo(_eoDP);

    MOVE_CUBE[16].set_cp(_cpLP);
    MOVE_CUBE[16].set_co(_coLP);
    MOVE_CUBE[16].set_ep(_epLP);
    MOVE_CUBE[16].set_eo(_eoLP);

    MOVE_CUBE[17].set_cp(_cpBP);
    MOVE_CUBE[17].set_co(_coBP);
    MOVE_CUBE[17].set_ep(_epBP);
    MOVE_CUBE[17].set_eo(_eoBP);

    return MOVE_CUBE;
}

#endif
