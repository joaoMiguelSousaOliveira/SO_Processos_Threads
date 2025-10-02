# Trabalho Prático 1 - Sistemas Operacionais

## 📋 Estrutura do Projeto

```
├── include/         # Headers (.hpp)
├── src/             # Implementações (.cpp)
├── build/           # Arquivos objeto (gerado automaticamente)
├── graphs/          # Gráficos
├── testes.py        # Testes automáticos
├── graficos.py      # Arquivo responsável pela geração dos gráficos
├── makefile         # Arquivo de compilação
└── .gitgnore
└── requirements.txt
├── resultadis_experimentos.csv  # Dados referentes aos testes dos mecanismos
├── relatorio.pdf  
└── README.md
```

## 🔧 Como Compilar

### Compilar os arquivos .cpp:
```bash
make
```
### Limpar arquivos compilados:
```bash
make clean
```

## 🚀 Como Executar
### 1. Executar Multiplicação Sequencial:
```bash
make run_sequencial
```
Este comando gera:
- `M1.txt` 
- `M2.txt` 
- `resultado_sequencial.txt`
### 2. Executar Multiplicação Threads:
```bash
make run_threads
```
Este comando gera:
- Arquivo `resultado_thread_n` para cada **thread** gerado 
- `resultado_sequencial.txt`
### 3. Executar Testes:
```bash
pyhton3 testes.py
```
Este comando gera:
- `resultado_experimentoss.csv`, se o diretório não o posuir
- Preenche `resultado_experimentoss.csv` com os dados levantados nos passos anteriores
### 4. Gerar Gráficos:
```bash
python3 graficos.py
```
Este comando gera:
- `graphs/`, se a pasta não existir
- Gera e salva os gráficos `experimento_e1_tempo_vs_tamanho.png` e `experimento_e2_tempo_vs_p.png` em `graphs/`
