#include "../include/lerMatriz.hpp"
#include "../include/multiplicaMatrizes.hpp"
#include "../include/gravaMatriz.hpp"
#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    // Neste caso, verificamos os argumentos da linha de comando;
    // Isso faz com que validemos se os arquivos foram fornecidos;
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " arquivo_M1 arquivo_M2" << endl;
        return 1;
    }
    
    string arquivo_m1_ = argv[1];
    string arquivo_m2_ = argv[2];
    
    try {
        cout << "=== MULTIPLICAÇÃO SEQUENCIAL DE MATRIZES ===" << endl;
        
        // Neste caso, lemos a primeira matriz;
        // Isso faz com que carregamos M1 do arquivo;
        cout << "Lendo matriz M1 de '" << arquivo_m1_ << "'..." << endl;
        DadosMatriz_ m1_ = lerMatriz(arquivo_m1_);
        cout << "M1: " << m1_.linhas_ << "x" << m1_.colunas_ << endl;
        
        // Neste caso, lemos a segunda matriz;
        // Isso faz com que carregamos M2 do arquivo;
        cout << "Lendo matriz M2 de '" << arquivo_m2_ << "'..." << endl;
        DadosMatriz_ m2_ = lerMatriz(arquivo_m2_);
        cout << "M2: " << m2_.linhas_ << "x" << m2_.colunas_ << endl;
        
        // Neste caso, iniciamos a medição do tempo;
        // Isso faz com que possamos medir apenas o tempo de multiplicação;
        auto inicio_ = high_resolution_clock::now();
        
        cout << "\nMultiplicando matrizes..." << endl;
        
        // Neste caso, realizamos a multiplicação sequencial;
        // Isso faz com que calculemos o produto das matrizes;
        DadosMatriz_ resultado_ = multiplicaMatrizes(m1_, m2_);
        
        // Neste caso, finalizamos a medição do tempo;
        // Isso faz com que possamos calcular a duração total;
        auto fim_ = high_resolution_clock::now();
        auto duracao_ = duration_cast<milliseconds>(fim_ - inicio_);
        double tempo_ns_ = duracao_.count();
        
        cout << "Resultado: " << resultado_.linhas_ << "x" << resultado_.colunas_ << endl;
        cout << "Tempo de execução: " << tempo_ns_ << " ns" << endl;
        
        // Neste caso, salvamos o resultado com o tempo;
        // Isso faz com que tenhamos o arquivo conforme especificação do PDF;
        string arquivo_resultado_ = "resultado_sequencial.txt";
        gravaMatrizComTempo(arquivo_resultado_, resultado_.linhas_, 
                           resultado_.colunas_, resultado_.matriz_, tempo_ns_);
        
        cout << "\nResultado salvo em '" << arquivo_resultado_ << "'" << endl;
        cout << "=== MULTIPLICAÇÃO CONCLUÍDA COM SUCESSO ===" << endl;
        
    } catch (const exception& e_) {
        cerr << "ERRO: " << e_.what() << endl;
        return 1;
    }
    
    return 0;
}
