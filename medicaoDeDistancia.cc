// Define os pinos dos motores
int leftMotorPin1 = 2;
int leftMotorPin2 = 3;
int rightMotorPin1 = 4;
int rightMotorPin2 = 5;

// Define o pino do sensor ultrassônico
const int triggerPin = 8;
const int echoPin = 9;

// Define as constantes para controle dos motores
const int minDistance = 5; // Distância mínima para desligar os motores (em cm)
const int maxSpeed = 255; // Velocidade máxima dos motores
const int minSpeed = 0; // Velocidade mínima dos motores

// Função para controlar a velocidade dos motores
void setMotorSpeed(int speedLeft, int speedRight) {
  // Define a direção do motor esquerdo
  if (speedLeft >= 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    speedLeft = -speedLeft;
  }
  
  // Define a direção do motor direito
  if (speedRight >= 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    speedRight = -speedRight;
  }
  
  // Define a velocidade dos motores
  analogWrite(leftMotorPin1, speedLeft);
  analogWrite(rightMotorPin1, speedRight);
}

void setup() {
  // Inicializa os pinos dos motores como OUTPUT
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  // Inicializa o pino do trigger como OUTPUT e o pino do echo como INPUT
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Gera um pulso no pino do trigger para iniciar a medição
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Mede o tempo de retorno do pulso no pino do echo
  long duration = pulseIn(echoPin, HIGH);
  
  // Converte o tempo de retorno em distância (em cm)
  int distance = duration * 0.034 / 2;
  
  // Verifica a distância e controla a velocidade dos motores
  if (distance > minDistance) {
    // Ajusta a velocidade dos motores com base na distância medida
    int speed = map(distance, minDistance, 400, minSpeed, maxSpeed);
    
    // Envia a velocidade dos motores para a função setMotorSpeed()
    setMotorSpeed(speed, speed);
  } else {
    // Desliga os motores se a distância for menor que a distância mínima
    setMotorSpeed(0, 0);
  }
  
  // Aguarda um intervalo antes de realizar a próxima medição
  delay(100);
}

