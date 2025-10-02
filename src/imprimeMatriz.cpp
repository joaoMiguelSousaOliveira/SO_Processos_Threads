#include "../include/imprimeMatriz.hpp"

void imprimeMatriz(vector<vector<int>> matriz_) {
    cout << "Matriz:" << endl;
    // Neste caso, iteramos por cada linha da matriz;
    // Isso faz com que possamos imprimir todos os elementos;
    for (const auto& linha_ : matriz_) {
        for (const auto& elemento_ : linha_) {
            cout << elemento_ << " ";
        }
        cout << endl;
    }
}

void imprimeMatriz(const DadosMatriz_& dados_) {
    // Neste caso, imprimimos as dimensões da matriz;
    // Isso faz com que o usuário saiba o tamanho da matriz;
    cout << "Matriz: " << dados_.linhas_ << "x" << dados_.colunas_ << endl;
    
    // Neste caso, chamamos a outra função de impressão;
    // Isso faz com que reutilizemos código;
    imprimeMatriz(dados_.matriz_);
}