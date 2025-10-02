import pandas as pd
import matplotlib.pyplot as plt
import os

# --- Configurações ---

# Arquivo de entrada com os resultados dos experimentos
INPUT_FILE = "resultados_experimentos.csv"

# Diretório para salvar os gráficos
OUTPUT_GRAPH_DIR = "./graphs"

# --- Funções Auxiliares ---

def create_graph_dir():
    """Cria o diretório de saída para os gráficos se ele não existir."""
    if not os.path.exists(OUTPUT_GRAPH_DIR):
        os.makedirs(OUTPUT_GRAPH_DIR)

# --- Geração de Gráficos ---

def generate_graphs():
    """Carrega os dados, calcula as médias e gera os gráficos para E1 e E2."""
    create_graph_dir()

    try:
        df = pd.read_csv(INPUT_FILE)
    except FileNotFoundError:
        print(f"Erro: Arquivo {INPUT_FILE} não encontrado. Certifique-se de que o script de experimentos foi executado.")
        return

    print(f"Dados carregados de {INPUT_FILE}. Total de {len(df)} registros.")

    # 1. Determinação de Valores Fixos de forma Robusta
    
    # E1: P fixo. Assumimos que o P fixo é o valor mais frequente nos dados, 
    # ou o menor valor, pois P é fixo enquanto N varia. Usaremos o mais frequente (mode()).
    if df["P"].empty:
        print("Erro: Coluna 'P' está vazia.")
        return
    # [0] é usado para garantir que pegamos o primeiro valor se houver múltiplos modos
    p_fixo_e1 = df["P"].mode()[0]
    
    # E2: N fixo. Assumimos que o N fixo é o maior N_M1 testado.
    if df["N_M1"].empty:
        print("Erro: Coluna 'N_M1' está vazia.")
        return
    n_fixo_e2 = df["N_M1"].max()

    print(f"Experimento E1: Usando P fixo = {p_fixo_e1}")
    print(f"Experimento E2: Usando N fixo = {n_fixo_e2}")

    # 2. Processamento para o Experimento E1 (P Fixo)
    
    # Filtra os dados com o P fixo
    df_e1 = df[df["P"] == p_fixo_e1]
    
    if df_e1.empty:
        print(f"Aviso: Nenhum dado encontrado para Experimento E1 (P={p_fixo_e1}). Pulando gráfico E1.")
    else:
        # Calcula a média agrupando por Tipo e N_M1 (eixo X)
        df_e1_avg = df_e1.groupby(["Tipo", "N_M1"])["Tempo_ms"].mean().unstack(level=0)

        # --- Gráfico para Experimento E1: Tempo vs. Tamanho da Matriz ---
        plt.figure(figsize=(12, 7))
        df_e1_avg.plot(kind='line', marker='o', ax=plt.gca())
        plt.title(f"Experimento E1: Tempo Médio de Execução vs. Tamanho da Matriz (P={p_fixo_e1} Fixo)")
        plt.xlabel("Tamanho da Matriz (N)")
        plt.ylabel("Tempo Médio (ms)")
        plt.grid(True)
        plt.legend(title="Tipo de Implementação")
        plt.tight_layout()
        graph_e1_path = os.path.join(OUTPUT_GRAPH_DIR, "experimento_e1_tempo_vs_tamanho.png")
        plt.savefig(graph_e1_path)
        print(f"Gráfico E1 salvo em {graph_e1_path}")
        plt.close()

    # 3. Processamento para o Experimento E2 (N Fixo)
    
    # Filtra os dados com o N fixo (o maior N testado)
    df_e2 = df[df["N_M1"] == n_fixo_e2]

    if df_e2.empty:
        print(f"Aviso: Nenhum dado encontrado para Experimento E2 (N={n_fixo_e2}). Pulando gráfico E2.")
    else:
        # Calcula a média agrupando por Tipo e P (eixo X)
        df_e2_avg = df_e2.groupby(["Tipo", "P"])["Tempo_ms"].mean().unstack(level=0)

        # --- Gráfico para Experimento E2: Tempo vs. Valor de P ---
        plt.figure(figsize=(12, 7))
        df_e2_avg.plot(kind='line', marker='o', ax=plt.gca())
        plt.title(f"Experimento E2: Tempo Médio de Execução vs. Tamanho do Bloco P (N={n_fixo_e2} Fixo)")
        plt.xlabel("Tamanho do Bloco/Granularidade (P)") # Rótulo melhorado
        plt.ylabel("Tempo Médio (ms)")
        plt.grid(True)
        plt.legend(title="Tipo de Implementação")
        plt.tight_layout()
        graph_e2_path = os.path.join(OUTPUT_GRAPH_DIR, "experimento_e2_tempo_vs_p.png")
        plt.savefig(graph_e2_path)
        print(f"Gráfico E2 salvo em {graph_e2_path}")
        plt.close()

    print("Geração de gráficos concluída.")

if __name__ == "__main__":
    generate_graphs()