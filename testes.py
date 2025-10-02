import subprocess
import csv
import os
import math
import time
import glob # Para encontrar múltiplos arquivos de resultado

# --- Configurações ---

# Diretório onde os executáveis estão localizados
BUILD_DIR = "./build"

# Número de repetições para cada experimento para calcular a média
NUM_REPETICOES = 10

# Arquivo de saída para os resultados (formato CSV)
OUTPUT_FILE = "resultados_experimentos.csv"

# --- Funções Auxiliares ---

def run_command(command, check_error=True):
    """Executa um comando shell e retorna a saída."""
    try:
        result = subprocess.run(command, capture_output=True, text=True, check=check_error)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Erro ao executar comando: {" ".join(command)}")
        print(f"Stdout: {e.stdout}")
        print(f"Stderr: {e.stderr}")
        if check_error:
            raise
        return ""

def get_time_from_file(filepath):
    """Extrai o tempo da última linha de um arquivo."""
    try:
        with open(filepath, 'r') as f:
            lines = f.readlines()
            if lines:
                return float(lines[-1].strip())
    except (FileNotFoundError, ValueError):
        return None
    return None

def get_max_parallel_time(prefix):
    """Encontra o tempo máximo entre todos os arquivos de resultado paralelos."""
    max_time = 0.0
    # Usa glob para encontrar todos os arquivos que começam com o prefixo
    for filepath in glob.glob(f"{prefix}*.txt"):
        current_time = get_time_from_file(filepath)
        if current_time is not None and current_time > max_time:
            max_time = current_time
    return max_time if max_time > 0 else None

def clean_temp_result_files():
    """Limpa apenas os arquivos de resultado temporários (não M1.txt e M2.txt)."""
    files_to_remove = [
        "resultado_sequencial.txt",
    ]
    for f in files_to_remove:
        if os.path.exists(f):
            os.remove(f)
    # Remover arquivos de threads/processos
    for f in os.listdir('.'):
        if f.startswith("resultado_thread_") or f.startswith("resultado_processo_"):
            os.remove(f)

def clean_all_temp_files():
    """Limpa todos os arquivos temporários, incluindo M1.txt e M2.txt."""
    clean_temp_result_files()
    for f in ["M1.txt", "M2.txt"]:
        if os.path.exists(f):
            os.remove(f)

# --- Inicialização do Arquivo de Saída ---
with open(OUTPUT_FILE, 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)
    csv_writer.writerow(["Tipo", "N_M1", "M_M1", "N_M2", "M_M2", "P", "Repeticao", "Tempo_ms"])

print("Iniciando experimentos...")

# --- Experimento E1: Variar o tamanho da matriz (N) e calcular P dinamicamente ---
# N = número de linhas/colunas para matrizes quadradas (NxN * NxN)

# Tamanhos de matrizes a serem testados (N x N)
TAMANHOS_N = [100, 200, 400, 800, 1000]

print("\n--- Experimento E1: Variando N, P calculado como ceil(N*N / 8) ---")

for N in TAMANHOS_N:
    # Calcula P conforme a especificação do PDF para E1
    # Assumindo matrizes quadradas N x N * N x N, então n1*m2 = N*N
    P_E1 = math.ceil((N * N) / 8)
    if P_E1 == 0: P_E1 = 1 # Garante que P não seja zero para matrizes muito pequenas

    print(f"Testando N={N} (Matrizes {N}x{N} * {N}x{N}) com P={P_E1}")

    # Gerar matrizes M1 (NxN) e M2 (NxN) UMA VEZ por N
    clean_all_temp_files() # Limpa tudo antes de gerar novas matrizes
    run_command([f"{BUILD_DIR}/auxiliar", str(N), str(N), str(N), str(N)])

    for i in range(1, NUM_REPETICOES + 1):
        print(f"  Repetição {i}/{NUM_REPETICOES}")

        # --- Sequencial ---
        clean_temp_result_files() # Limpa apenas os resultados antes de cada execução
        run_command([f"{BUILD_DIR}/sequencial", "M1.txt", "M2.txt"])
        tempo_sequencial = get_time_from_file("resultado_sequencial.txt")
        with open(OUTPUT_FILE, 'a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(["Sequencial", N, N, N, N, P_E1, i, tempo_sequencial])

        # --- Paralelo Threads ---
        clean_temp_result_files() # Limpa apenas os resultados antes de cada execução
        run_command([f"{BUILD_DIR}/paralelo_threads", "M1.txt", "M2.txt", str(P_E1)])
        tempo_threads = get_max_parallel_time("resultado_thread_")
        with open(OUTPUT_FILE, 'a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(["Threads", N, N, N, N, P_E1, i, tempo_threads])

        # --- Paralelo Processos ---
        clean_temp_result_files() # Limpa apenas os resultados antes de cada execução
        run_command([f"{BUILD_DIR}/paralelo_processos", "M1.txt", "M2.txt", str(P_E1)])
        tempo_processos = get_max_parallel_time("resultado_processo_")
        with open(OUTPUT_FILE, 'a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(["Processos", N, N, N, N, P_E1, i, tempo_processos])

# --- Experimento E2: Manter o tamanho da matriz (N) fixo e variar P ---
# N_FIXO = tamanho fixo da matriz (NxN * NxN)

# Tamanho fixo da matriz para o Experimento E2
# Escolha um N que leve ~2 minutos no sequencial para ter um bom baseline
# VOCÊ DEVE AJUSTAR ESTE VALOR MANUALMENTE APÓS TESTES INICIAIS
N_FIXO_E2 = 500 # Exemplo, ajuste conforme seus testes

print(f"\n--- Experimento E2: N fixo ({N_FIXO_E2}), Variando P ---")

# Gerar matrizes M1 (NxN) e M2 (NxN) UMA VEZ para este experimento E2
clean_all_temp_files() # Limpa tudo antes de gerar novas matrizes para E2
run_command([f"{BUILD_DIR}/auxiliar", str(N_FIXO_E2), str(N_FIXO_E2), str(N_FIXO_E2), str(N_FIXO_E2)])

# Calcula o P inicial e final conforme o PDF
# Assumindo matrizes quadradas N_FIXO_E2 x N_FIXO_E2 * N_FIXO_E2 x N_FIXO_E2
TOTAL_ELEMENTOS_E2 = N_FIXO_E2 * N_FIXO_E2
P_START_E2 = math.ceil(TOTAL_ELEMENTOS_E2 / 8)
P_END_E2 = math.ceil(TOTAL_ELEMENTOS_E2 / 2)

# Gera uma lista de valores de P para o Experimento E2
VALORES_P_E2 = []

# Valores abaixo de P_START_E2 (até 1/4 de P_START_E2)
if P_START_E2 > 0:
    p_quarter = math.ceil(P_START_E2 / 4)
    step_down = max(1, math.ceil((P_START_E2 - p_quarter) / 3)) # 3 passos para baixo
    for p_val in range(P_START_E2, p_quarter - 1, -step_down):
        if p_val > 0 and p_val not in VALORES_P_E2: VALORES_P_E2.append(p_val)

# Valores entre P_START_E2 e P_END_E2
step_up = max(1, math.ceil((P_END_E2 - P_START_E2) / 5)) # 5 passos para cima
for p_val in range(P_START_E2, P_END_E2 + 1, step_up):
    if p_val > 0 and p_val not in VALORES_P_E2: VALORES_P_E2.append(p_val)

VALORES_P_E2 = sorted(list(set(VALORES_P_E2))) # Remove duplicatas e ordena
if not VALORES_P_E2: VALORES_P_E2 = [1] # Garante que haja pelo menos um valor de P

print(f"Valores de P para E2: {VALORES_P_E2}")

for P in VALORES_P_E2:
    print(f"Testando P={P} com Matrizes {N_FIXO_E2}x{N_FIXO_E2}")

    for i in range(1, NUM_REPETICOES + 1):
        print(f"  Repetição {i}/{NUM_REPETICOES}")

        # --- Sequencial (apenas para comparação, o tempo deve ser o mesmo) ---
        clean_temp_result_files() # Limpa apenas os resultados antes de cada execução
        run_command([f"{BUILD_DIR}/sequencial", "M1.txt", "M2.txt"])
        tempo_sequencial = get_time_from_file("resultado_sequencial.txt")
        with open(OUTPUT_FILE, 'a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(["Sequencial", N_FIXO_E2, N_FIXO_E2, N_FIXO_E2, N_FIXO_E2, P, i, tempo_sequencial])

        # --- Paralelo Threads ---
        clean_temp_result_files() # Limpa apenas os resultados antes de cada execução
        run_command([f"{BUILD_DIR}/paralelo_threads", "M1.txt", "M2.txt", str(P)])
        tempo_threads = get_max_parallel_time("resultado_thread_")
        with open(OUTPUT_FILE, 'a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(["Threads", N_FIXO_E2, N_FIXO_E2, N_FIXO_E2, N_FIXO_E2, P, i, tempo_threads])

        # --- Paralelo Processos ---
        clean_temp_result_files() # Limpa apenas os resultados antes de cada execução
        run_command([f"{BUILD_DIR}/paralelo_processos", "M1.txt", "M2.txt", str(P)])
        tempo_processos = get_max_parallel_time("resultado_processo_")
        with open(OUTPUT_FILE, 'a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(["Processos", N_FIXO_E2, N_FIXO_E2, N_FIXO_E2, N_FIXO_E2, P, i, tempo_processos])

clean_all_temp_files() # Limpa tudo no final dos experimentos
print(f"\nExperimentos concluídos. Resultados salvos em {OUTPUT_FILE}")

