import serial
import joblib
import pandas as pd
import time

print("Carregando Inteligência Artificial...")
try:
    modelo_motor = joblib.load('modelo_motor_treinado.pkl')
    print("✅ Modelo carregado!\n")
except FileNotFoundError:
    print("❌ ERRO: Rode o arquivo 'treinamento_modelo.py' primeiro para gerar o modelo.")
    exit()

# ATENÇÃO: Altere 'COM3' para a porta USB do seu Arduino
PORTA_ARDUINO = 'COM3' 
BAUD_RATE = 9600

try:
    conexao = serial.Serial(PORTA_ARDUINO, BAUD_RATE, timeout=1)
    time.sleep(2)
    print(f"🔌 Conectado ao Arduino na porta {PORTA_ARDUINO}. Aguardando dados...\n")
except Exception as e:
    print(f"❌ ERRO ao conectar no Arduino: Verifique se a porta {PORTA_ARDUINO} está correta.")
    exit()

while True:
    try:
        linha = conexao.readline().decode('utf-8').strip()
        
        if linha:
            dados = linha.split(',')
            
            if len(dados) == 2:
                vib_atual = float(dados[0])
                temp_atual = float(dados[1])
                
                # Prepara o dado para a IA
                dado_novo = pd.DataFrame({'vibracao_rms': [vib_atual], 'temperatura_c': [temp_atual]})
                
                # Previsão
                prob_falha = modelo_motor.predict_proba(dado_novo)[0][1] * 100
                
                print(f"Sensores -> Vibração: {vib_atual:.1f} | Temp: {temp_atual:.1f}°C")
                print(f"IA -> Probabilidade de Falha em 24h: {prob_falha:.1f}%")
                
                if prob_falha > 70.0:
                    print("⚠️ ALERTA: Risco de falha iminente!")
                print("-" * 40)
                
    except KeyboardInterrupt:
        print("\nMonitoramento encerrado.")
        conexao.close()
        break
    except Exception:
        pass # Ignora ruídos na comunicação serial
