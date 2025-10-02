#include "../include/lerMatriz.hpp"

DadosMatriz_ lerMatriz(const string& arquivo_) {
    ifstream file_(arquivo_); // Neste caso, abrimos o arquivo para leitura;
    // Isso faz com que possamos ler os dados da matriz;

    if (!file_.is_open()) {
        throw runtime_error("Nao foi possivel abrir o arquivo: " + arquivo_);
    }
    
    DadosMatriz_ dados_; // Neste caso, criamos a estrutura para armazenar os dados da matriz;
    // Isso faz com que possamos retornar todas as informações necessárias;
    string linha_;

    if (!getline(file_, linha_)){
        throw runtime_error("Arquivo vazio ou inválido");
    }
    
    stringstream ssdimensoes_(linha_);
    ssdimensoes_ >> dados_.linhas_ >> dados_.colunas_;
    
    // Neste caso, validamos as dimensões;
    // Isso faz com que detectemos arquivos mal formatados;
    if (dados_.linhas_ <= 0 || dados_.colunas_ <= 0) {
        throw runtime_error("Dimensões inválidas da matriz");
    }
    
    // Neste caso, inicializamos a matriz com as dimensões lidas;
    // Isso faz com que reservemos o espaço necessário em memória;
    dados_.matriz_.resize(dados_.linhas_, vector<int>(dados_.colunas_));

    // Neste caso, lemos cada linha no formato "cij valor";
    // Isso faz com que possamos preencher a matriz corretamente;
    int elementoslidos_ = 0;
    while (getline(file_, linha_) && elementoslidos_ < dados_.linhas_ * dados_.colunas_) {
        stringstream ss_(linha_);
        string identificador_;
        int valor_;
        
        ss_ >> identificador_ >> valor_;
        
        // Neste caso, verificamos se a linha contém um identificador válido;
        // Isso faz com que possamos extrair os índices i e j;
        if (identificador_.length() >= 3 && identificador_[0] == 'c') {
            // Neste caso, extraímos os índices i e j do identificador "cij";
            // Isso faz com que possamos posicionar o valor corretamente na matriz;
            string indices_ = identificador_.substr(1); // Neste caso, removemos o 'c';
            
            int i_, j_;
            // Neste caso, tratamos identificadores de 1 ou 2 dígitos;
            // Isso faz com que funcione para matrizes de qualquer tamanho;
            if (indices_.length() == 2) {
                i_ = indices_[0] - '0'; // Neste caso, primeiro dígito é i;
                j_ = indices_[1] - '0'; // Neste caso, segundo dígito é j;
            } else {
                // Neste caso, para matrizes maiores, usamos parsing mais robusto;
                // Isso faz com que suportemos índices maiores que 9;
                size_t meio_ = indices_.length() / 2;
                i_ = stoi(indices_.substr(0, meio_));
                j_ = stoi(indices_.substr(meio_));
            }
            
            // Neste caso, convertemos de índices 1-based para 0-based;
            // Isso faz com que acessemos corretamente os vetores C++;
            i_--;
            j_--;
            
            // Neste caso, validamos os índices;
            // Isso faz com que evitemos acessos inválidos à memória;
            if (i_ >= 0 && i_ < dados_.linhas_ && j_ >= 0 && j_ < dados_.colunas_) {
                dados_.matriz_[i_][j_] = valor_;
                elementoslidos_++;
            }
        }
    }

    file_.close(); // Neste caso, fechamos o arquivo após a leitura;
    // Isso faz com que liberemos os recursos do sistema;
    return dados_;
}