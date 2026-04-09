import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import joblib
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report

print("Iniciando o treinamento do modelo de Machine Learning...")

# 1. GERAÇÃO DE DADOS SINTÉTICOS (Simulando o Dataset)
np.random.seed(42)
n_amostras = 500

vibracao_normal = np.random.normal(loc=2.5, scale=0.8, size=n_amostras // 2)
temp_normal = np.random.normal(loc=50, scale=5, size=n_amostras // 2)
falha_normal = np.zeros(n_amostras // 2)

vibracao_falha = np.random.normal(loc=8.0, scale=2.0, size=n_amostras // 2)
temp_falha = np.random.normal(loc=85, scale=10, size=n_amostras // 2)
falha_falha = np.ones(n_amostras // 2)

df = pd.DataFrame({
    'vibracao_rms': np.concatenate([vibracao_normal, vibracao_falha]),
    'temperatura_c': np.concatenate([temp_normal, temp_falha]),
    'falha_24h': np.concatenate([falha_normal, falha_falha])
})
df = df.sample(frac=1).reset_index(drop=True)

# 2. SEPARAÇÃO E TREINAMENTO
X = df[['vibracao_rms', 'temperatura_c']]
y = df['falha_24h']
X_treino, X_teste, y_treino, y_teste = train_test_split(X, y, test_size=0.2, random_state=42)

modelo_motor = RandomForestClassifier(n_estimators=100, random_state=42)
modelo_motor.fit(X_treino, y_treino)

# 3. AVALIAÇÃO RÁPIDA
previsoes = modelo_motor.predict(X_teste)
print(f"Acurácia do Modelo: {accuracy_score(y_teste, previsoes) * 100:.2f}%\n")

# 4. SALVAR O MODELO TREINADO
joblib.dump(modelo_motor, 'modelo_motor_treinado.pkl')
print("✅ Cérebro da IA salvo com sucesso como 'modelo_motor_treinado.pkl'")
