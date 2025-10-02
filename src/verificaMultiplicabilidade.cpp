#include "../include/verificaMultiplicabilidade.hpp"

bool verificaMultiplicabilidade(int colunas_primeira_matriz_, int linhas_segunda_matriz_) {
    // Neste caso, verificamos se o número de colunas da primeira matriz é igual ao número de linhas da segunda;
    // Isso faz com que possamos validar se a multiplicação é possível;
    if (colunas_primeira_matriz_ != linhas_segunda_matriz_) {
        throw invalid_argument("As matrizes não podem ser multiplicadas. "
        "Número de colunas da primeira (" + to_string(colunas_primeira_matriz_) + 
        ") é diferente do número de linhas da segunda (" + to_string(linhas_segunda_matriz_) + ").");
    }
    return true;
}