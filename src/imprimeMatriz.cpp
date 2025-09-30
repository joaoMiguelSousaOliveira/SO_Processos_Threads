#include "../include/imprimeMatriz.hpp"
#include "../include/gravaMatriz.hpp"

void imprimeMatriz (vector<vector<int>> matriz) {
    cout << "Matriz:" << endl;
    for (const auto& linha : matriz) {
        for (const auto& elemento : linha) {
            cout << elemento << " ";
        }
        cout << endl;
    }
}