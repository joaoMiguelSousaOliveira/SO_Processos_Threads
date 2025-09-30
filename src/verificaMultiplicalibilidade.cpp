#include "../include/verificaMultiplicabilidade.hpp"

int verificaMultiplicalibidade (int colunas_primeira_matriz, int linhas_segunda_matriz) {
    if (colunas_primeira_matriz != linhas_segunda_matriz) {
        throw invalid_argument("As matrizes nao podem ser multiplicadas");
        return 1;
    } else {
        cout << "As matrizes podem ser multiplicadas" << endl;
        return 0;
    }
}