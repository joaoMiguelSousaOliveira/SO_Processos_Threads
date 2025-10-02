#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Deefinimos o tipo Matriz para representar matrizes como vetores 2D
// Neste caso, definimos uma estrutura para armazenar os dados da matriz;
// Isso faz com que possamos retornar tanto a matriz quanto suas dimensões;
struct DadosMatriz_ {
    int linhas_;
    int colunas_;
    vector<vector<int>> matriz_;
};

// Neste caso, declaramos a função que lê a matriz de um arquivo;
// Isso faz com que possamos carregar matrizes salvas em disco;
DadosMatriz_ lerMatriz(const string& arquivo_);
