#include "../include/gravaMatriz.hpp"

void gravaMatriz(const string& arquivo, int linhas, int colunas, Matriz matriz) {

    ofstream file_out(arquivo);
    file_out << "Número de linhas;Número de colunas;\n";
    file_out.close();

    for (const auto& linha : matriz) {
        ofstream file(arquivo, ios::app);
        if (file.is_open()) {
            for (const auto& elemento : linha) {
                file << elemento << ";";
            }
            file << "\n";
            file.close();
        } else {
            cerr << "Não foi possível abrir o arquivo: " << arquivo << endl;
        }
    }
}
