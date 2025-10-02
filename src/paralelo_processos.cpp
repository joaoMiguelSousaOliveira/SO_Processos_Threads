#include "../include/lerMatriz.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <fstream>
#include <unistd.h>    // Necessário para fork()
#include <sys/wait.h>  // Necessário para wait()

// Usando os namespaces para simplificar
using namespace std;
using namespace chrono;

// Função para o processo-filho executar
void multiplica_e_salva_bloco(int id, const DadosMatriz_& m1, const DadosMatriz_& m2, int start_element, int end_element) {
    // Inicia a medição do tempo DENTRO do processo-filho
    auto inicio_processo = high_resolution_clock::now();

    int colunas_m1 = m1.colunas_;
    int colunas_m2 = m2.colunas_;
    int linhas_resultado = m1.linhas_;

    // Cria um nome de arquivo para o resultado deste processo
    string nome_arquivo = "resultado_processo_" + to_string(id) + ".txt";
    ofstream arquivo_saida(nome_arquivo);
    if (!arquivo_saida.is_open()) {
        cerr << "Erro ao criar arquivo de resultado para processo " << id << endl;
        exit(1); // Termina o processo-filho com erro
    }

    // Escreve o cabeçalho com as dimensões da matriz *total*
    arquivo_saida << linhas_resultado << " " << colunas_m2 << endl;

    // Itera, calcula e escreve os elementos no arquivo
    for (int i = start_element; i < end_element; ++i) {
        int linha = i / colunas_m2;
        int coluna = i % colunas_m2;

        double soma = 0.0;
        for (int j = 0; j < colunas_m1; ++j) {
            soma += m1.matriz_[linha][j] * m2.matriz_[j][coluna];
        }
        
        arquivo_saida << "c" << linha + 1 << "," << coluna + 1 << " " << soma << endl;
    }

    auto fim_processo = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>(fim_processo - inicio_processo);
    double tempo_ms = duracao.count();

    // Adiciona o tempo de execução no final do arquivo
    arquivo_saida << tempo_ms << endl;
    arquivo_saida.close();

    // O processo-filho termina aqui
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " arquivo_M1 arquivo_M2 P" << endl;
        return 1;
    }

    string arquivo_m1_ = argv[1];
    string arquivo_m2_ = argv[2];
    int P_ = stoi(argv[3]);

    if (P_ <= 0) {
        cerr << "Erro: O valor de P deve ser positivo." << endl;
        return 1;
    }

    try {
        cout << "=== MULTIPLICAÇÃO PARALELA (PROCESSOS) ===" << endl;

        DadosMatriz_ m1_ = lerMatriz(arquivo_m1_);
        cout << "M1: " << m1_.linhas_ << "x" << m1_.colunas_ << endl;
        DadosMatriz_ m2_ = lerMatriz(arquivo_m2_);
        cout << "M2: " << m2_.linhas_ << "x" << m2_.colunas_ << endl;

        if (m1_.colunas_ != m2_.linhas_) {
            throw runtime_error("As matrizes não são multiplicáveis.");
        }

        int total_elementos_ = m1_.linhas_ * m2_.colunas_;
        int num_processos_ = ceil((double)total_elementos_ / P_);
        cout << "Total de elementos: " << total_elementos_ << endl;
        cout << "Elementos por processo (P): " << P_ << endl;
        cout << "Número de processos a serem criados: " << num_processos_ << endl;

        // Loop para criar os processos-filhos
        for (int i = 0; i < num_processos_; ++i) {
            int start_ = i * P_;
            int end_ = min((i + 1) * P_, total_elementos_);

            pid_t pid = fork(); // Cria um novo processo

            if (pid < 0) { // Erro ao criar o processo
                cerr << "Erro no fork()!" << endl;
                return 1;
            } else if (pid == 0) { // Este é o código que o processo-filho executa
                cout << "Criando processo " << i << " para calcular elementos de " << start_ << " a " << end_ - 1 << endl;
                multiplica_e_salva_bloco(i, m1_, m2_, start_, end_);
                // A função acima termina com exit(0), então o filho nunca sai daqui.
            }
        }

        // Este é o código que o processo-pai executa
        // O pai deve esperar todos os filhos terminarem
        cout << "\nAguardando a finalização dos processos..." << endl;
        for (int i = 0; i < num_processos_; ++i) {
            wait(NULL);
        }

        cout << "\n=== MULTIPLICAÇÃO CONCLUÍDA COM SUCESSO ===" << endl;
        cout << "Resultados parciais salvos em arquivos 'resultado_processo_*.txt'" << endl;

    } catch (const exception& e) {
        cerr << "ERRO: " << e.what() << endl;
        return 1;
    }

    return 0;
}
