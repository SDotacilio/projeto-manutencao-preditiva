void setup() {
  // Inicia a comunicação serial a 9600 bps
  Serial.begin(9600); 
}

void loop() {
  // Simula a leitura de vibração (entre 1.0 e 9.0 RMS)
  float vibracao = random(10, 90) / 10.0;    
  
  // Simula a leitura de temperatura (entre 40.0 e 95.0 °C)
  float temperatura = random(400, 950) / 10.0; 

  // Envia os dados no formato: vibracao,temperatura
  Serial.print(vibracao);
  Serial.print(",");
  Serial.println(temperatura);

  // Aguarda 2 segundos antes da próxima leitura
  delay(2000); 
}
