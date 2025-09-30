#include "../include/geraMatriz.hpp"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, 100);

vector<vector<int>> geraMatrizAleatoria (int linhas, int colunas) {

    vector<vector<int>> matriz(linhas, vector<int>(colunas));
 
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; i < colunas; j++) {
            matriz[i][j] = dis(gen);
        }   
    }
    return matriz;
}