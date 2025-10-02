#pragma once

#include "lerMatriz.hpp"
#include "verificaMultiplicabilidade.hpp"


using namespace std;
using Matriz = vector<vector<int>>;

// Neste caso, declaramos a função que multiplica duas matrizes;
// Isso faz com que possamos calcular o produto matricial;
DadosMatriz_ multiplicaMatrizes(const DadosMatriz_& m1_, const DadosMatriz_& m2_);