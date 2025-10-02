# Define o compilador C++
CXX = g++

# Define as flags de compilação
CXXFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR)

# Define a flag específica para linkar a biblioteca de threads
LDFLAGS_THREAD = -pthread

# Define os diretórios do projeto
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
OBJ_DIR = obj

# Lista de arquivos-fonte (.cpp)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de todos os executáveis que queremos criar
TARGETS = $(BUILD_DIR)/sequencial $(BUILD_DIR)/auxiliar $(BUILD_DIR)/paralelo_threads $(BUILD_DIR)/paralelo_processos
# --- REGRAS DE COMPILAÇÃO ---

# Regra principal: 'all' compila todos os alvos definidos em TARGETS
# Esta é a regra padrão que será executada quando você digitar 'make'
all: $(TARGETS)

# Regra para criar o executável 'sequencial'
$(BUILD_DIR)/sequencial: $(OBJ_DIR)/sequencial.o $(OBJ_DIR)/lerMatriz.o $(OBJ_DIR)/gravaMatriz.o $(OBJ_DIR)/multiplicaMatrizes.o $(OBJ_DIR)/verificaMultiplicabilidade.o
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Executável 'sequencial' criado com sucesso em $(BUILD_DIR)/"

# Regra para criar o executável 'auxiliar'
$(BUILD_DIR)/auxiliar: $(OBJ_DIR)/auxiliar.o $(OBJ_DIR)/geraMatriz.o $(OBJ_DIR)/gravaMatriz.o $(OBJ_DIR)/verificaMultiplicabilidade.o
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Executável 'auxiliar' criado com sucesso em $(BUILD_DIR)/"

# Regra para criar o executável 'paralelo_threads'
$(BUILD_DIR)/paralelo_threads: $(OBJ_DIR)/paralelo_threads.o $(OBJ_DIR)/lerMatriz.o $(OBJ_DIR)/gravaMatriz.o
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_THREAD)
	@echo "Executável 'paralelo_threads' criado com sucesso em $(BUILD_DIR)/"

# Regra para criar o executável 'paralelo_processos'
$(BUILD_DIR)/paralelo_processos: $(OBJ_DIR)/paralelo_processos.o $(OBJ_DIR)/lerMatriz.o
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Executável 'paralelo_processos' criado com sucesso em $(BUILD_DIR)/"

# Regra genérica para criar arquivos de objeto (.o) a partir dos fontes (.cpp)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- REGRAS AUXILIARES ---

# Regra 'run_sequencial': Executa o programa sequencial
run_sequencial: all
	@echo "Executando teste sequencial com matrizes 10x10..."
	./$(BUILD_DIR)/auxiliar 10 10 10 10
	./$(BUILD_DIR)/sequencial M1.txt M2.txt

# Regra 'run_threads': Executa o programa de threads
run_threads: all
	@echo "Executando teste com threads com matrizes 10x10 e P=10..."
	./$(BUILD_DIR)/auxiliar 10 10 10 10
	./$(BUILD_DIR)/paralelo_threads M1.txt M2.txt 10

# Regra 'run_processos': Executa o programa de processos
run_processos: all
	@echo "Executando teste com processos com matrizes 10x10 e P=10..."
	./$(BUILD_DIR)/auxiliar 10 10 10 10
	./$(BUILD_DIR)/paralelo_processos M1.txt M2.txt 10


# Regra 'clean': Remove os diretórios de binários e objetos
clean:
	@echo "Limpando arquivos compilados..."
	rm -rf $(BUILD_DIR) $(OBJ_DIR) M1.txt M2.txt resultado_*.txt
	@echo "Limpeza concluída."

# Phony targets são regras que não representam arquivos
.PHONY: all clean run_sequencial run_threads run_processos
