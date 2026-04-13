#include <LiquidCrystal.h> // Biblioteca para usar o display


LiquidCrystal lcd (13, 12, 11, 10, 9, 8, 7); // Define os pinos do display

// Definindo os pinos dos LEDs, do buzzer e do sensor de luminosidade
const int ledVerde = 4; // Conecta o pino 4 ao LED verde
const int ledAmarelo = 5; // Conecta o pino 5 ao LED amarelo
const int ledVermelho = 6; // Conecta o pino 6 ao LED vermelho
const int buzzer = 3; // Conecta o pino 3 ao buzzer
const int sensorLuminosidade = A0; // Conecta o pino analógico ao sensor de luminosidade

// Declarando variáveis para o valor de luminosidade e para os limites
int valorLuminosidade = 0; // Armazena o valor lido pelo sensor de luminosidade
int limiteIdeal = 10; // Define o limite em que a luminosidade é considerada ideal
int limiteMaximo = 50; // Define o limite máximo do nível de luminosidade
int limiteAlerta = 200; // Define o limite em que a luminosidade é considerada alerta 

// Configurando os pinos e inicializando a comunicação serial
void setup() {
  lcd.begin(16,2); // inicializa 16 colunas, 2 linhas           
  lcd.clear(); // Limpa o display
  lcd.setCursor(0,0); // Vai pra linha 1         
  lcd.print("Boas-Vindas!"); // Linha 1
  lcd.setCursor(0,1); // Vai pra linha 2
  lcd.print("Vinheria Agnello"); // Linha 2
  
  
  pinMode(ledVerde, OUTPUT); // Define o pino do LED verde como saída
  pinMode(ledAmarelo, OUTPUT); // Define o pino do LED amarelo como saída
  pinMode(ledVermelho, OUTPUT); // Define o pino do LED vermelho como saída
  pinMode(buzzer, OUTPUT); // Define o pino do buzzer como saída
  pinMode(sensorLuminosidade, INPUT); // Define o pino do sensor de luminosidade como entrada
  Serial.begin(9600); // Inicia a comunicação serial a 9600 bps
 
  delay(4000); // delay de 4 segundos
  lcd.clear(); // Limpa o display
}

// Iniciando o loop principal
void loop() {
  int valorLuminosidade = analogRead(sensorLuminosidade); // Lê o valor da luminosidade e armazena o mesmo
  int luminosidade = map(valorLuminosidade, 0, 1023, 0, 100); // transforma o valor da luminosidade em porcentagem (%)
  Serial.print("Luminosidade: "); // Exibe "Luminosidade :" na tela
  Serial.print(luminosidade); // Exibe o valor do sensor em porcentagem na tela
  Serial.println("%"); // Exibe o simbolo de porcentagem na tela
 
  
  lcd.setCursor(0,0); // Vai pra linha 1
  lcd.print("Luminosidade: "); // Exibe "Luminosidade: " na primeira linha do display
  lcd.setCursor(0,1); // Vai pra linha 2
  lcd.print(luminosidade); // Exibe o valor da luminosidade em porcentagem na segunda linha do display
  lcd.setCursor(2,1); // Vai pra coluna 2 da linha 1
  lcd.print("%"); // Exibe o simbolo de porcentagem (%) no display
  

  // Definindo estrutura de condição para acionar os LEDs e o buzzer com base no valor da luminosidade
  if (valorLuminosidade <= limiteIdeal) { 
    // Se a luminosidade estiver abaixo do limite OK:
    digitalWrite(ledVerde, HIGH); // Liga o LED verde
    digitalWrite(ledAmarelo, LOW); // Desliga o LED amarelo
    digitalWrite(ledVermelho, LOW); // Desliga o LED vermelho
    noTone(buzzer); // Buzzer não acionado
  } 
  else if (valorLuminosidade >= limiteMaximo && valorLuminosidade <= limiteAlerta)  {
    // Se a luminosidade estiver entre o limite OK e o limite alerta:
    digitalWrite(ledVerde, LOW); // Desliga o LED verde 
    digitalWrite(ledAmarelo, HIGH); // Liga o LED amarelo
    digitalWrite(ledVermelho, LOW); // Desliga o LED vermelho
    tone(buzzer, 500); // Aciona o buzzer com frequência de 500 Hz
    delay(3000); // Mantém o buzzer acionado por 3 segundos
    noTone(buzzer); // Desliga o buzzer
  } 
  else if (valorLuminosidade >= limiteAlerta) {
    // Se a luminosidade estiver acima do limite alerta:
    digitalWrite(ledVerde, LOW); // Desliga o LED verde
    digitalWrite(ledAmarelo, LOW); // Desliga o LED amarelo
    digitalWrite(ledVermelho, HIGH); // Liga o LED vermelho
    tone(buzzer, 1000); // Aciona o buzzer com uma frequência de 1000 Hz
    
    
  	
  }

  delay(1000); // Pausa de 1 segundo antes do loop ser repetido
}