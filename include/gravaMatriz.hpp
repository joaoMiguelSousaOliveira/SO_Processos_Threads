#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Neste caso, definimos um tipo para facilitar o uso de matrizes;
// Isso faz com que o código fique mais legível;
typedef vector<vector<int>> Matriz_;

// Neste caso, declaramos a função que grava a matriz em um arquivo;
// Isso faz com que possamos salvar o resultado em disco;
void gravaMatriz(const string& arquivo_, int linhas_, int colunas_, Matriz_ matriz_);

// Neste caso, declaramos a função que grava a matriz com o tempo de execução;
// Isso faz com que possamos medir o desempenho do algoritmo;
void gravaMatrizComTempo(const string& arquivo_, int linhas_, int colunas_, Matriz_ matriz_, double tempo_ms_);

