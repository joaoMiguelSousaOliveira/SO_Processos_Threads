#include "../include/geraMatriz.hpp"

// Neste caso, inicializamos o gerador de números aleatórios;
// Isso faz com que tenhamos valores diferentes a cada execução;
random_device rd_;
mt19937 gen_(rd_());
uniform_int_distribution<> dis_(0, 100);

vector<vector<int>> geraMatrizAleatoria(int linhas_, int colunas_) {
    // Neste caso, criamos a matriz com as dimensões especificadas;
    // Isso faz com que tenhamos o espaço necessário alocado;
    vector<vector<int>> matriz_(linhas_, vector<int>(colunas_));

    // Neste caso, preenchemos cada posição com um valor aleatório;
    // Isso faz com que tenhamos uma matriz com valores entre 0 e 100;
    for (int i_ = 0; i_ < linhas_; i_++) {
        for (int j_ = 0; j_ < colunas_; j_++) {
            matriz_[i_][j_] = dis_(gen_);
        }   
    }
    return matriz_;
}