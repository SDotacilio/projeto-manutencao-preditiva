#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_MLX90614.h>

Adafruit_MPU6050 mpu;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);

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
  Serial.println("Sistema Pronto: Monitorando Motor...");
}

void loop() {
  // --- Leitura de Vibração ---
  sensors_event_t a, g, temp_interna;
  mpu.getEvent(&a, &g, &temp_interna);
  
  float magnitude = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));
  float vibracaoReal = magnitude - 11.0; // Sua calibração de repouso

  // --- Leitura de Temperatura ---
  float tempMotor = mlx.readObjectTempC(); // Temperatura do alvo (motor)

  // --- Exibição no Serial Plotter ---
  Serial.print("Vibracao:"); Serial.print(vibracaoReal); Serial.print(" ");
  Serial.print("Temp_Motor:"); Serial.println(tempMotor);

  delay(50); 
}
// --- Definição dos Pinos de Alerta ---
const int pinoLED = 13;
const int pinoBuzzer = 12;

// --- Limites de Engenharia ---
const float MAX_VIBRA = 5.0; 
const float MAX_TEMP = 50.0;

void setup() {
  // ... (mantenha o seu setup anterior do MPU e MLX)
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);
}

void loop() {
  // ... (mantenha a lógica da Magnitude e Temperatura)
  
  // --- Lógica de Alarme ---
  if (vibracaoReal > MAX_VIBRA || tempMotor > MAX_TEMP) {
    digitalWrite(pinoLED, HIGH); // Liga o alerta
    tone(pinoBuzzer, 1000);      // Toca um som de 1kHz
    Serial.println("!!! PERIGO: LIMITE ULTRAPASSADO !!!");
  } else {
    digitalWrite(pinoLED, LOW);  // Desliga o alerta
    noTone(pinoBuzzer);          // Para o som
  }

  delay(50);
}
