#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>

// --- Instanciando os sensores ---
Adafruit_MPU6050 mpu;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// --- Definição dos Pinos de Alerta ---
const int pinoLED = 13;
const int pinoBuzzer = 12;

// --- Limites de Engenharia (Ajuste conforme seus testes) ---
const float MAX_VIBRA = 5.0; 
const float MAX_TEMP = 50.0;
const float REPOUSO_OFFSET = 11.0; // Sua calibração de repouso atual

void setup() {
  Serial.begin(115200);
  
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);

  // Inicializa MPU-6050
  if (!mpu.begin()) {
    Serial.println("Erro no MPU-6050!");
    while (1);
  }

  // Inicializa GY-906
  if (!mlx.begin()) {
    Serial.println("Erro no GY-906!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.println("Sistema Pronto: Monitorando com LED e Buzzer...");
}

void loop() {
  // --- 1. Leitura de Vibração ---
  sensors_event_t a, g, temp_interna;
  mpu.getEvent(&a, &g, &temp_interna);
  
  float magnitude = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z));
  float vibracaoReal = magnitude - REPOUSO_OFFSET; 

  // --- 2. Leitura de Temperatura ---
  float tempMotor = mlx.readObjectTempC(); 

  // --- 3. Exibição no Serial Monitor/Plotter ---
  Serial.print("Vibracao:"); Serial.print(vibracaoReal); Serial.print(" ");
  Serial.print("Temp_Motor:"); Serial.print(tempMotor); Serial.print(" ");
  Serial.print("Lim_V:"); Serial.print(MAX_VIBRA); Serial.print(" ");
  Serial.print("Lim_T:"); Serial.println(MAX_TEMP);

  // --- 4. Lógica de Alarme Unificada ---
  if (vibracaoReal > MAX_VIBRA || tempMotor > MAX_TEMP) {
    digitalWrite(pinoLED, HIGH); // Liga o alerta visual
    tone(pinoBuzzer, 1000);      // Toca um som de 1kHz no Buzzer
    
    if (vibracaoReal > MAX_VIBRA) Serial.print(" !!! ALERTA VIBRACAO !!! ");
    if (tempMotor > MAX_TEMP) Serial.print(" !!! ALERTA CALOR !!! ");
    Serial.println();
    
  } else {
    digitalWrite(pinoLED, LOW);  // Desliga o alerta
    noTone(pinoBuzzer);          // Para o som
  }

  delay(100); 
}
