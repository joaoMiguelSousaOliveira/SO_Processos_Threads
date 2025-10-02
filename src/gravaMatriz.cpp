#include "../include/gravaMatriz.hpp"

void gravaMatriz(const string& arquivo_, int linhas_, int colunas_, Matriz_ matriz_) {
    ofstream file_(arquivo_);

    if (!file_.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << arquivo_ << endl;
        return;
    }

    // Neste caso, gravamos as dimensões da matriz na primeira linha;
    // Isso faz com que saibamos o tamanho da matriz ao ler;
    file_ << linhas_ << " " << colunas_ << "\n";

    // Neste caso, gravamos cada elemento com o seu identificador cij;
    // Isso faz com que possamos identificar a posição de cada elemento;
    for (int i_ = 0; i_ < linhas_; i_++) {
        for (int j_ = 0; j_ < colunas_; j_++) {
            file_ << "c" << (i_+1) << (j_+1) << " " << matriz_[i_][j_] << "\n";
        }
    }

    file_.close(); // Neste caso, fechamos o arquivo após a escrita;
    // Isso faz com que os dados sejam salvos corretamente;
}

void gravaMatrizComTempo(const string& arquivo_, int linhas_, int colunas_, Matriz_ matriz_, double tempo_ms_) {
    ofstream file_(arquivo_);

    if (!file_.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << arquivo_ << endl;
        return;
    }

    // Neste caso, gravamos as dimensões da matriz no início do arquivo;
    // Isso faz com que possamos ler o tamanho depois;
    file_ << linhas_ << " " << colunas_ << "\n";

    // Neste caso, gravamos cada elemento com identificador;
    // Isso faz com que mantenhamos o formato padrão;
    for (int i_ = 0; i_ < linhas_; i_++) {
        for (int j_ = 0; j_ < colunas_; j_++) {
            file_ << "c" << (i_ + 1) << (j_ + 1) << " " << matriz_[i_][j_] << "\n";
        }
    }

    // Neste caso, gravamos o tempo de execução no final;
    // Isso faz com que possamos analisar o desempenho;
    file_ << tempo_ms_ << "\n";

    file_.close(); // Neste caso, fechamos o arquivo;
    // Isso faz com que os dados sejam persistidos;
}