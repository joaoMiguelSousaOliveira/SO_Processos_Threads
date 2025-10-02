#include "../include/multiplicaMatrizes.hpp"

DadosMatriz_ multiplicaMatrizes(const DadosMatriz_& m1_, const DadosMatriz_& m2_) {
    // Neste caso, verificamos se as matrizes podem ser multiplicadas;
    // Isso faz com que validemos as dimensões antes de prosseguir;
    verificaMultiplicabilidade(m1_.colunas_, m2_.linhas_);
    
    // Neste caso, criamos a estrutura para o resultado;
    // Isso faz com que tenhamos o espaço para armazenar o produto;
    DadosMatriz_ resultado_;
    resultado_.linhas_ = m1_.linhas_;
    resultado_.colunas_ = m2_.colunas_;
    resultado_.matriz_.resize(resultado_.linhas_, vector<int>(resultado_.colunas_, 0));
    
    // Neste caso, realizamos a multiplicação de matrizes;
    // Isso faz com que calculemos cada elemento do produto;
    for (int i_ = 0; i_ < resultado_.linhas_; i_++) {
        for (int j_ = 0; j_ < resultado_.colunas_; j_++) {
            // Neste caso, calculamos o elemento (i,j) do resultado;
            // Isso faz com que somemos os produtos dos elementos correspondentes;
            for (int k_ = 0; k_ < m1_.colunas_; k_++) {
                resultado_.matriz_[i_][j_] += m1_.matriz_[i_][k_] * m2_.matriz_[k_][j_];
            }
        }
    }
    
    return resultado_;
}