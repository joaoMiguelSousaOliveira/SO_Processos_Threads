#pragma once

#include <iostream>
#include <vector>
#include "lerMatriz.hpp"

using namespace std;

// Neste caso, declaramos a função que imprime uma matriz;
// Isso faz com que possamos visualizar o conteúdo das matrizes;
void imprimeMatriz(vector<vector<int>> matriz_);

// Neste caso, sobrecarregamos a função para aceitar DadosMatriz_;
// Isso faz com que possamos imprimir diretamente a estrutura completa;
void imprimeMatriz(const DadosMatriz_& dados_);