#include "../include/geraMatriz.hpp"
#include "../include/gravaMatriz.hpp"
#include "../include/multiplicaMatrizes.hpp"
#include "../include/verificaMultiplicabilidade.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Neste caso, verificamos se os argumentos foram fornecidos;
    // Isso faz com que validemos a entrada do usuário;
    if (argc != 5) {
        cerr << "Uso: " << argv[0] << " n1 m1 n2 m2" << endl;
        cerr << "Onde n1 x m1 são dimensões da matriz M1 e n2 x m2 da matriz M2" << endl;
        return 1;
    }
    
    // Neste caso, convertemos os argumentos para inteiros;
    // Isso faz com que possamos usar os valores nas funções;
    int n1_ = stoi(argv[1]);
    int m1_ = stoi(argv[2]);
    int n2_ = stoi(argv[3]);
    int m2_ = stoi(argv[4]);
    
    // Neste caso, validamos se as dimensões são positivas;
    // Isso faz com que evitemos erros na geração das matrizes;
    if (n1_ <= 0 || m1_ <= 0 || n2_ <= 0 || m2_ <= 0) {
        cerr << "Erro: Todas as dimensões devem ser positivas" << endl;
        return 1;
    }
    
    // Neste caso, verificamos se as matrizes podem ser multiplicadas;
    // Isso faz com que validemos a compatibilidade antes de gerar;
    try {
        verificaMultiplicabilidade(m1_, n2_);
    } catch (const exception& e_) {
        cerr << "ERRO: " << e_.what() << endl;
        return 1;
    }
    
    cout << "=== GERADOR DE MATRIZES ALEATÓRIAS ===" << endl;
    cout << "\nGerando matriz M1 (" << n1_ << "x" << m1_ << ")..." << endl;
    
    // Neste caso, geramos a primeira matriz;
    // Isso faz com que tenhamos valores aleatórios para teste;
    Matriz_ M1_ = geraMatrizAleatoria(n1_, m1_);
    gravaMatriz("M1.txt", n1_, m1_, M1_);
    cout << "Matriz M1 salva em 'M1.txt'" << endl;
    
    cout << "Gerando matriz M2 (" << n2_ << "x" << m2_ << ")..." << endl;
    
    // Neste caso, geramos a segunda matriz;
    // Isso faz com que tenhamos a segunda matriz de teste;
    Matriz_ M2_ = geraMatrizAleatoria(n2_, m2_);
    gravaMatriz("M2.txt", n2_, m2_, M2_);
    cout << "Matriz M2 salva em 'M2.txt'" << endl;
    
    cout << "\n=== MATRIZES GERADAS COM SUCESSO ===" << endl;
    
    return 0;
}