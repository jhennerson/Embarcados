/*
   Firmware para a central do projeto "Detector de Choro Para Pais Deficientes Auditivos"
   utilizando as bibliotecas licenciadas abaixo:

   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>


//Colocar valor em 1 para permitir debug pela porta serial, colocar qualquer outro valor para desabilitar
#define __debug  1


// Variáveis de IO
byte pinIntImput  = 5;  // pino conectado ao pino de interrupção do arduíno

// Variáveis WiFi
const char *ssid = "Central";         // ID da rede
const char *password = "Warframe";   // Senha da rede

// Variáveis UDP
WiFiUDP UDP;

const char *IpPulseira = "192.168.4.2";
unsigned int localPort = 8888;

boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // Buffer para guardar pacote encaminhado
// Variáveis de comandos
char warning[3] = "on"; // String de comando enviado para ativar o alarme da pulseira
boolean sendState = false;

// Declaração de functions
void interrupt_ISR();
void sendRequest();
void sendCommand();
void DecodePacket();

void setup()
{
  #if (__debug == 1)
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    Serial.println();
  #endif
  

  // Configura o pino de interrupção
  pinMode(pinIntImput, INPUT);

WiFi.softAP(ssid, password); // Se quiser pode-se remover a senha e deixar a rede aberta apagando "password"

  IPAddress myIP = WiFi.softAPIP();
  
  #if (__debug == 1)
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  #endif
  
  // Define parâmetros UDP
  udpConnected = connectUDP();

  // Inicializa UDP
  UDP.begin(localPort);

  // Interrupção para envio do comando de acionamento da pulseira
  attachInterrupt(pinIntImput, interrupt_ISR, FALLING);
}

void loop()
{
  // Solicita envio de comando de ativação da pulseira
  sendRequest();
}

// Loop de interrupção para envio do comando de alarme da pulseira
void interrupt_ISR()
{
  sendState = true;
  
  #if (__debug == 1)
  Serial.print("Button pressed");
  #endif
}

// Loop de requisição de envio de comando de ativação da pulseira
void sendRequest()
{
  if (sendState == true)
  {
    sendCommand();
    sendState = false;
  }
}

// Loop para enviar comandos de ativação do alarme da pulseira.
void sendCommand()
{
  UDP.beginPacket(IpPulseira, localPort);
  UDP.write(warning);
  UDP.endPacket();
  
  #if (__debug == 1)
  Serial.println("");
  Serial.println("Command has been sent");
  #endif
  
  delay(5000);
}

// Estabelece uma conexão UDP e retorna "true" se for bem sucedida ou "false" se não for bem sucedida
boolean connectUDP()
{
  boolean state = false;

  #if (__debug == 1)
  Serial.println("");
  Serial.println("Connecting to UDP");
  #endif
  
  if (UDP.begin(localPort) == 1)
  {
    #if (__debug == 1)
    Serial.println("Connection successful");
    state = true;
    #endif
  }
  else
  {
    #if (__debug == 1)
    Serial.println("Connection failed");
    return state;
    #endif
  }
}
