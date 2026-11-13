#include <BTAddress.h>
#include <BTAdvertisedDevice.h>
#include <BTScan.h>
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

#include <ESP32Servo.h>

//Criação de 04 objetos, um para cada servo do braço robótico 
Servo motorDireita, motorEsquerda, motorBase, motorGarra;

/* definição das posições 0º e 180º, respectivamente,
com base no tempo de envio do pulso elétrico em microssegundos (µs)*/
int minUs = 1000; //pulso alto equivalente a 0º
int maxUs = 2000; //puslo baixo equivalente a 180º

// These are all GPIO Pinos on the ESP32
// Recommended Pinos include 2,4,12-19,21-23,25-27,32-33
int motorDireitaPino = 18;
int motorEsquerdaPino = 19;
int motorBasePino = 23;
int motorGarraPino = 22;

int posicao = 0; //ângulo em graus
char comando; //comando recebido pelo monitor serial para controle do braço robótico
char incomingChar;

void setup() {
	Serial.begin(115200);
	SerialBT.begin("ESP32_BT_Teste"); // Nome que aparecerá no celular
	motorDireita.setPeriodHertz(50);      // Standard 50hz servo
	motorEsquerda.setPeriodHertz(50);      // Standard 50hz servo
	motorBase.setPeriodHertz(50);      // Standard 50hz servo
	motorGarra.setPeriodHertz(50);      // Standard 50hz servo
	motorDireita.attach(motorDireitaPino, minUs, maxUs);
	motorEsquerda.attach(motorEsquerdaPino, minUs, maxUs);
	motorBase.attach(motorBasePino, minUs, maxUs);
	motorGarra.attach(motorGarraPino, minUs, maxUs);
}

void loop() {
	if (SerialBT.available()) {
    incomingChar = SerialBT.read();
    Serial.print("Recebido do Bluetooth: ");
    Serial.println(incomingChar);
    
    // Exemplo: ecoa de volta para o celular
    SerialBT.print("Você enviou: ");
    SerialBT.println(incomingChar);
  }
  
	if(Serial.available()>0){
		SerialBT.write(Serial.read());
		comando = Serial.read();
	}
	
	delay(20);

	if(comando == 'D' || incomingChar == 'D' ){

    if(posicao <180){
      posicao = posicao + 10;
    }else{
      posicao=180;
      Serial.println("Atenção você chegou no limite");
    }
    
    if(posicao>0){
      posicao = posicao - 10;
    }else{
      posicao=0;
      Serial.println("Atenção você chegou no limite");
    }

		for (posicao = 0; posicao <= 180; posicao += 1) {
			motorDireita.write(posicao);
			delay(20);
		}
		for (posicao = 180; posicao >= 0; posicao -= 1) {
			motorDireita.write(posicao);
			delay(20);
		}

	}
	
	if(comando == 'E' || incomingChar == 'E' ){
    
    if(posicao <180){
      posicao = posicao + 10;
    }else{
      posicao=180;
      Serial.println("Atenção você chegou no limite");
    }
    
    if(posicao>0){
      posicao = posicao - 10;
    }else{
      posicao=0;
      Serial.println("Atenção você chegou no limite");
    }

    motor.write(posicao);
    
		for (posicao = 0; posicao <= 180; posicao += 1) {
			motorEsquerda.write(posicao);
			delay(20);
		}
		for (posicao = 180; posicao >= 0; posicao -= 1) {
			motorEsquerda.write(posicao);
			delay(20);
		}
	}


  if(comando == 'J' || incomingChar == 'J' ){
    
   if(posicao <180){
      posicao = posicao + 10;
    }else{
      posicao=180;
      Serial.println("Atenção você chegou no limite");
    }
    
    if(posicao>0){
      posicao = posicao - 10;
    }else{
      posicao=0;
      Serial.println("Atenção você chegou no limite");
    }

    motorEsquerda.write(posicao);
    motorDireita.write(posicao);

    dalay(45);

		for (posicao = 0; posicao <= 180; posicao += 1) {
			motorEsquerda.write(posicao);
      motorDireita.write(posicao);
			delay(20);
		}

		for (posicao = 180; posicao >= 0; posicao -= 1) {
			motorEsquerda.write(posicao);
      motorDireta.write(posicao);
			delay(20);
		}
	}


	if(comando == 'B' || incomingChar == 'B' ){
    
    if(posicao <180){
      posicao = posicao + 10;
    }else{
      posicao=180;
      Serial.println("Atenção você chegou no limite");
    }
    
    if(posicao>0){
      posicao = posicao - 10;
    }else{
      posicao=0;
      Serial.println("Atenção você chegou no limite");
    }

		// 1. Girar no sentido horário (velocidade média)
		motorBase.writeMicroseconds(1300); 
		delay(4000); // Gira por 2 segundos

		// 2. Parar o motor
		motorBase.writeMicroseconds(1500); 
		delay(1000); // Fica parado por 1 segundo

		// 3. Girar no sentido anti-horário (velocidade média)
		motorBase.writeMicroseconds(1700); 
		delay(4000); // Gira por 2 segundos

		// 4. Parar novamente
		motorBase.writeMicroseconds(1500);
		delay(1000);
	}
	
	if(comando == 'G' || incomingChar == 'G' ){

    if(posicao <180){
      posicao = posicao + 10;
    }else{
      posicao=180;
      Serial.println("Atenção você chegou no limite");
    }
    
    if(posicao>0){
      posicao = posicao - 10;
    }else{
      posicao=0;
      Serial.println("Atenção você chegou no limite");
    }

		for (posicao = 0; posicao <= 180; posicao += 1) {
			motorGarra.write(posicao);
			delay(20);
		}
		for (posicao = 180; posicao >= 0; posicao -= 1) {
			motorGarra.write(posicao);
			delay(20);
		}
	}
