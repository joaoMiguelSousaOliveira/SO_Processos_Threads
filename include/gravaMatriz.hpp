#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using Matriz = vector<vector<int>>;

void salvar_tempo_execucao(const string& arquivo, int linhas, int colunas, Matriz matriz);