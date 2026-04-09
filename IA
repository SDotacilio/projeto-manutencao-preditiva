` ` `python
# =====================================================================
# PROJETO DE EXTENSÃO: Monitoramento de Falhas em Motores Elétricos
# OBJETIVO PRINCIPAL: Prever a probabilidade de falha nas próximas 24h
#                     com base em Temperatura e Vibração.
# ALGORITMO: Classificação (Random Forest - Floresta Aleatória)
# =====================================================================

# ---------------------------------------------------------------------
# METODOLOGIA - PASSO 1: IMPORTAR AS BIBLIOTECAS (Ferramentas)
# O que fazer: Carregar o Pandas para dados e o Scikit-Learn para IA.
# ---------------------------------------------------------------------
import pandas as pd              # Manipulação de tabelas
import numpy as np               # Cálculos matemáticos (para gerar dados falsos)
import matplotlib.pyplot as plt  # Gráficos básicos
import seaborn as sns            # Gráficos estatísticos e interativos (solicitado no plano)

# Ferramentas de Machine Learning (Scikit-Learn)
from sklearn.model_selection import train_test_split # Separar treino/teste
from sklearn.ensemble import RandomForestClassifier  # O algoritmo escolhido no plano
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report # Avaliação (Matriz de Confusão)

# Configuração para gráficos aparecerem melhor no notebook
# %matplotlib inline 

print("Passo 1: Bibliotecas importadas com sucesso!")

# ---------------------------------------------------------------------
# METODOLOGIA DE EXECUÇÃO - PASSO 2: COLETA DE DADOS
# O que fazer: QUANDO TIVER O ARQUIVO REAL (CSV do Kaggle/NASA), 
# descomente a linha abaixo e comente o bloco de "DADOS SINTÉTICOS".
# ---------------------------------------------------------------------

# COMO USAR O DADO REAL DEPOIS:
# df = pd.read_csv('caminho/para/seu_arquivo_do_kaggle.csv')

# --- INÍCIO DO BLOCO DE DADOS SINTÉTICOS (PROVISÓRIO) ---
# Vamos criar 500 exemplos de motores simulando sensores (Vibração RMS e Temperatura Celsius)
# E criar a coluna alvo "Falha_24h" (0 = Não Falhou, 1 = Falhou)
np.random.seed(42) # Para que os dados aleatórios sejam sempre os mesmos ao rodar
n_amostras = 500

# Simulando motores normais (baixa vibração, temperatura estável)
vibracao_normal = np.random.normal(loc=2.5, scale=0.8, size=n_amostras // 2)
temp_normal = np.random.normal(loc=50, scale=5, size=n_amostras // 2)
falha_normal = np.zeros(n_amostras // 2) # Zero falhas

# Simulando motores prestes a falhar (alta vibração, alta temperatura)
vibracao_falha = np.random.normal(loc=8.0, scale=2.0, size=n_amostras // 2)
temp_falha = np.random.normal(loc=85, scale=10, size=n_amostras // 2)
falha_falha = np.ones(n_amostras // 2) # Um falhas

# Juntando tudo em um DataFrame do Pandas
df = pd.DataFrame({
    'vibracao_rms': np.concatenate([vibracao_normal, vibracao_falha]),
    'temperatura_c': np.concatenate([temp_normal, temp_falha]),
    'falha_24h': np.concatenate([falha_normal, falha_falha])
})

# Embaralhar os dados (para não ficarem organizados por tipo de motor)
df = df.sample(frac=1).reset_index(drop=True)
# --- FIM DO BLOCO DE DADOS SINTÉTICOS ---

print("\nPasso 2: Dados carregados (Base Sintética criada para testes).")
print(f"Total de registros: {len(df)}")


# ---------------------------------------------------------------------
# METODOLOGIA DE EXECUÇÃO - PASSO 3: PROCESSAMENTO (E EXPLORAÇÃO)
# O que fazer: Visualizar os dados, verificar correlações e criar gráficos.
# É o que você chamou de "ver o que faz a máquina quebrar".
# ---------------------------------------------------------------------
print("\n--- VISUALIZAÇÃO INICIAL (5 PRIMEIRAS LINHAS) ---")
print(df.head())

print("\n--- RESUMO ESTATÍSTICO (Média, Mínimo, Máximo) ---")
print(df.describe())

# JUSTIFICATIVA DO PLANO: "A análise de vibração e temperatura permite identificar falhas..."
# Vamos provar isso visualmente.
print("\nPasso 3: Criando gráficos de correlação (Demonstração Interativa)...")

# Gráfico 1: Scatter Plot (Dispersão) - Vibração vs Temperatura pintado por Falha
plt.figure(figsize=(10, 6))
sns.scatterplot(x='vibracao_rms', y='temperatura_c', hue='falha_24h', data=df, palette='coolwarm', alpha=0.7)
plt.title('Análise Sensorial: Vibração vs Temperatura por Estado do Motor')
plt.xlabel('Vibração (RMS)')
plt.ylabel('Temperatura (°C)')
plt.legend(title='Estado (0=Bom, 1=Falha)')
plt.grid(True)
plt.show() # Na sua máquina, isso abrirá uma janela com o gráfico.

# Gráfico 2: Matriz de Correlação (Heatmap)
plt.figure(figsize=(6, 5))
correlacao = df.corr()
sns.heatmap(correlacao, annot=True, cmap='Blues', fmt=".2f")
plt.title('Matriz de Correlação entre Variáveis')
plt.show()


# ---------------------------------------------------------------------
# METODOLOGIA DE EXECUÇÃO - PASSO 4: DESENVOLVIMENTO DO MODELO
# O que fazer: Separar X (features) e y (alvo), dividir em treino e teste,
# e treinar o Random Forest escolhido no plano.
# ---------------------------------------------------------------------
# 1. Separar Variáveis de Entrada (X) e Saída Alvo (y)
# Entrada: Vibração e Temperatura
X = df[['vibracao_rms', 'temperatura_c']]
# Alvo: Se vai falhar ou não
y = df['falha_24h']

# 2. Divisão Treino e Teste (80% para IA aprender, 20% para prova final)
X_treino, X_teste, y_treino, y_teste = train_test_split(X, y, test_size=0.2, random_state=42)

print(f"\nPasso 4: Modelo sendo treinado...")
print(f"Dados de treino: {X_treino.shape[0]} amostras.")
print(f"Dados de teste: {X_teste.shape[0]} amostras.")

# 3. Inicializar e Treinar o Algoritmo Random Forest
# Usamos random_state=42 para garantir reprodutibilidade dos resultados
modelo_motor = RandomForestClassifier(n_estimators=100, random_state=42)
modelo_motor.fit(X_treino, y_treino)

print("Random Forest treinado com sucesso!")


# ---------------------------------------------------------------------
# METODOLOGIA DE EXECUÇÃO - PASSO 5: AVALIAÇÃO DO MODELO
# O que fazer: Criar a "Matriz de Confusão" solicitada no plano para mostrar
# a taxa de acerto e gerar o relatório detalhado.
# ---------------------------------------------------------------------
print("\nPasso 5: Avaliando a Inteligência Artificial com os dados de teste...")

# A IA faz previsões para os 20% de dados que ela nunca viu
previsoes = modelo_motor.predict(X_teste)

# Acurácia Geral
acuracia = accuracy_score(y_teste, previsoes)
print(f"-> Acurácia Geral (Taxa de Acerto): {acuracia * 100:.2f}%\n")

# RELATÓRIO DETALHADO (Precision, Recall, F1-Score)
print("--- RELATÓRIO DE CLASSIFICAÇÃO DETALHADO ---")
# Mostra se a IA é boa em prever tanto motores BONS quanto QUEBRADOS.
# Para manutenção preditiva, Recall da classe 1 (Falha) é muito importante!
print(classification_report(y_teste, previsoes, target_names=['Motor Bom', 'Falha Pendente']))

# MATRIZ DE CONFUSÃO (Solicitado na Metodologia)
print("\n--- GERANDO A MATRIZ DE CONFUSÃO (Demonstração)... ---")
matriz = confusion_matrix(y_teste, previsoes)

# Plotando a Matriz de forma bonita usando Seaborn
plt.figure(figsize=(8, 6))
sns.heatmap(matriz, annot=True, fmt='d', cmap='Greens', cbar=False,
            xticklabels=['Previu Bom', 'Previu Falha'],
            yticklabels=['Real Bom', 'Real Falha'])
plt.title('Matriz de Confusão do Monitoramento de Motores')
plt.xlabel('Previsão da IA')
plt.ylabel('Realidade (Chão de Fábrica)')
plt.show()


# ---------------------------------------------------------------------
# OBJETIVO DO PLANO: RESPONDER À PERGUNTA ESPECÍFICA
# Pergunta: Qual a probabilidade de falha nas próximas 24 horas?
# O que fazer: Usar a função 'predict_proba' para um novo motor imaginário.
# ---------------------------------------------------------------------
print("\n" + "="*50)
print("SIMULAÇÃO DE USO NO CHÃO DE FÁBRICA")
print("="*50)

# Suponha que um sensor acabou de ler estes dados do "Motor X":
# Vibração está alta (7.5) e Temperatura subindo (82°C)
vibracao_atual = 7.5
temperatura_atual = 82.0

novo_dado = pd.DataFrame({'vibracao_rms': [vibracao_atual], 'temperatura_c': [temperatura_atual]})

# 1. Previsão Direta (0 ou 1)
previsao_direta = modelo_motor.predict(novo_dado)[0]
status = "ALERTA DE FALHA EM 24H!" if previsao_direta == 1 else "Motor Operando Normalmente."

# 2. Probabilidade (O foco do seu Objetivo 1!)
probabilidades = modelo_motor.predict_proba(novo_dado)[0]
probabilidade_falha = probabilidades[1] # A segunda posição [1] é a chance de falhar

print(f"\n--- LEITURA ATUAL DO MOTOR X ---")
print(f"Vibração: {vibracao_atual} RMS")
print(f"Temperatura: {temperatura_atual} °C")
print("-" * 30)
print(f"RESPOSTA DA IA PARA O ENGENHEIRO:")
print(f"Status Previsto: {status}")
# ESTA É A LINHA QUE RESPONDE SEU OBJETIVO 1:
print(f"Probabilidade de Falha nas próximas 24 horas: {probabilidade_falha * 100:.1f}%")

if probabilidade_falha > 0.7:
    print("\nAÇÃO RECOMENDADA: Agendar manutenção preventiva IMEDIATAMENTE.")
else:
    print("\nAÇÃO RECOMENDADA: Manter monitoramento contínuo.")
` ` `
