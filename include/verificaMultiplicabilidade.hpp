#pragma once

#include <iostream>
using namespace std;

// Neste caso, declaramos a função que verifica se as matrizes podem ser multiplicadas;
// Isso faz com que possamos validar as dimensões antes de tentar a multiplicação;
bool verificaMultiplicabilidade(int colunas_primeira_matriz_, int linhas_segunda_matriz_);