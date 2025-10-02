#include "../include/lerMatriz.hpp"
#include "../include/gravaMatriz.hpp" // Assumindo que você terá uma função para gravar com tempo
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <fstream> // Necessário para ofstream

// Usando os namespaces para simplificar
using namespace std;
using namespace chrono;

// Estrutura para passar os dados para cada thread, seguindo a convenção
struct ThreadData_ {
    int thread_id_;
    const DadosMatriz_* m1_;
    const DadosMatriz_* m2_;
    DadosMatriz_* resultado_;
    int start_element_;
    int end_element_;
};

// Função que será executada por cada thread
void multiplica_bloco(ThreadData_ data_) {
    // Inicia a medição do tempo logo antes do cálculo, como especificado
    auto inicio_thread_ = high_resolution_clock::now();

    int colunas_m1_ = data_.m1_->colunas_;
    int colunas_m2_ = data_.m2_->colunas_;

    // Itera sobre os elementos que esta thread é responsável por calcular
    for (int i = data_.start_element_; i < data_.end_element_; ++i) {
        int linha_ = i / colunas_m2_;
        int coluna_ = i % colunas_m2_;

        double soma_ = 0.0;
        for (int j = 0; j < colunas_m1_; ++j) {
            soma_ += data_.m1_->matriz_[linha_][j] * data_.m2_->matriz_[j][coluna_];
        }
        data_.resultado_->matriz_[linha_][coluna_] = soma_;
    }

    auto fim_thread_ = high_resolution_clock::now();
    auto duracao_ = duration_cast<milliseconds>(fim_thread_ - inicio_thread_);
    double tempo_ms_ = duracao_.count();

    // Cria um nome de arquivo para o resultado desta thread
    string nome_arquivo_ = "resultado_thread_" + to_string(data_.thread_id_) + ".txt";
    
    ofstream arquivo_saida_(nome_arquivo_);
    if (!arquivo_saida_.is_open()) {
        cerr << "Erro ao criar arquivo de resultado para thread " << data_.thread_id_ << endl;
        return;
    }

    // Escreve o cabeçalho com as dimensões da matriz *total*, como pedido no PDF
    arquivo_saida_ << data_.resultado_->linhas_ << " " << data_.resultado_->colunas_ << endl;
    
    // Escreve apenas os elementos calculados por esta thread
    for (int i = data_.start_element_; i < data_.end_element_; ++i) {
        int linha_ = i / colunas_m2_;
        int coluna_ = i % colunas_m2_;
        arquivo_saida_ << "c" << linha_ + 1 << "," << coluna_ + 1 << " " << data_.resultado_->matriz_[linha_][coluna_] << endl;
    }

    // Adiciona o tempo de execução desta thread no final do arquivo
    arquivo_saida_ << tempo_ms_ << endl;
    arquivo_saida_.close();
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
        cout << "=== MULTIPLICAÇÃO PARALELA (THREADS) ===" << endl;

        // Lê as matrizes de entrada
        DadosMatriz_ m1_ = lerMatriz(arquivo_m1_);
        cout << "M1: " << m1_.linhas_ << "x" << m1_.colunas_ << endl;
        DadosMatriz_ m2_ = lerMatriz(arquivo_m2_);
        cout << "M2: " << m2_.linhas_ << "x" << m2_.colunas_ << endl;

        // Verifica se a multiplicação é possível
        if (m1_.colunas_ != m2_.linhas_) {
            throw runtime_error("As matrizes não são multiplicáveis.");
        }

        // Prepara a matriz de resultado
        DadosMatriz_ resultado_;
        resultado_.linhas_ = m1_.linhas_;
        resultado_.colunas_ = m2_.colunas_;
        resultado_.matriz_ = vector<vector<int>>(resultado_.linhas_, vector<int>(resultado_.colunas_, 0.0));

        // Calcula o número de threads necessárias
        int total_elementos_ = resultado_.linhas_ * resultado_.colunas_;
        int num_threads_ = ceil((double)total_elementos_ / P_);
        cout << "Total de elementos: " << total_elementos_ << endl;
        cout << "Elementos por thread (P): " << P_ << endl;
        cout << "Número de threads a serem criadas: " << num_threads_ << endl;

        vector<thread> threads_;
        vector<ThreadData_> thread_data_(num_threads_);

        // Divide o trabalho e cria as threads
        for (int i = 0; i < num_threads_; ++i) {
            int start_ = i * P_;
            int end_ = min((i + 1) * P_, total_elementos_);

            thread_data_[i] = {i, &m1_, &m2_, &resultado_, start_, end_};
            
            cout << "Criando thread " << i << " para calcular elementos de " << start_ << " a " << end_ - 1 << endl;
            threads_.emplace_back(multiplica_bloco, thread_data_[i]);
        }

        // Aguarda todas as threads terminarem
        cout << "\nAguardando a finalização das threads..." << endl;
        for (auto& t_ : threads_) {
            if (t_.joinable()) {
                t_.join();
            }
        }

        cout << "\n=== MULTIPLICAÇÃO CONCLUÍDA COM SUCESSO ===" << endl;
        cout << "Resultados parciais salvos em arquivos 'resultado_thread_*.txt'" << endl;

    } catch (const exception& e) {
        cerr << "ERRO: " << e.what() << endl;
        return 1;
    }

    return 0;
}
