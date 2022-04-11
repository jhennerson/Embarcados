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

 

 

 

7.1.3. Código do Firmware da Placa WeMos D1 Mini (Pulseira) 

 

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

byte pinIntButton   = 13; // D7 pino de interrupção conectado ao botão de interrupção do alarme 

byte pinAlarmMotor  = 14; // D5 pino conectado ao motor vibracall 

byte pinAlarmLed    = 5;  // D1 pino conectado ao LED de alarme 

byte pinWifiLed     = 2;  // D4 pino conectado ao LED de indicação do Wi-Fi 

 

// Variáveis e constantes Wi-Fi 

const char* ssid = "Central"; 

const char* password = "Warframe"; 

boolean wifiConnected = false; 

 

// Variáveis de comandos 

char warning[3] = "on";               // comando para ativação dos atuadores de alarme 

 

#if (__debug == 1) 

char alarmOn[10] = "LED is On";         // String para indicar que o arlarme está ativado 

char alarmOff[11] = "LED is Off";       // String para indicar que o alarme está desativado 

#endif 

 

boolean activateQuery = false; 

 

// variáveis e constantes UDP 

WiFiUDP UDP; 

const char *IpCentral = "192.168.4.1"; 

unsigned int localPort = 8888; 

boolean udpConnected = false; 

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; // Buffer para guardar o pacote encaminhado 

 

 

// Declaração de functions 

void BlinkWiFiConnected(); 

void BlinkWiFiDisconnected(); 

void DecodePacket(); 

void intStopAlarm_ISR(); 

void activateRequest(); 

void activateAlarm(); 

 

void setup() 

{ 

  // Inicializa comunicação serial 

 

  #if (__debug == 1) 

  Serial.begin(115200); 

  #endif 

 

  // Inicializa os pinos de IO 

  pinMode(pinAlarmMotor, OUTPUT); 

  pinMode(pinWifiLed, OUTPUT); 

  pinMode(pinAlarmLed, OUTPUT); 

  pinMode(pinIntButton, INPUT); 

 

  // Inicializa conexão WiFi 

  wifiConnected = connectWifi(); 

 

  // Inicializa UDP 

  UDP.begin(localPort); 

 

  // Configuração da interrupção de parada do alarme 

  attachInterrupt(pinIntButton, intStopAlarm_ISR, FALLING); 

 

  // Procede apenas se a conexão for bem sucedida 

  if (wifiConnected) 

  { 

    udpConnected = connectUDP(); 

  } 

} 

 

// Loop principal de repetição contínua 

void loop() 

{ 

  activateRequest(); 

 

  if (WiFi.status() == 3) 

  { 

    BlinkWiFiConnected(); 

  } 

  else 

  { 

    BlinkWiFiDisconnected(); 

    connectWifi(); 

  } 

  // Checa se a conexão Wi-Fi foi bem sucedida 

  if (wifiConnected) 

  { 

    if (udpConnected) 

    { 

      activateRequest(); 

      // Se tiver algum pacote disponivel ele é lido 

      int packetSize = UDP.parsePacket(); 

      if (packetSize) 

      { 

         

        #if (__debug == 1) 

        Serial.println(""); 

        Serial.print("Received packet of size "); 

        Serial.println(packetSize); 

        Serial.print("From "); 

        IPAddress remote = UDP.remoteIP(); 

        for (int i = 0; i < 4; i++) 

        { 

          Serial.print(remote[i], DEC); 

          if (i < 3) 

          { 

            Serial.print("."); 

          } 

        } 

        Serial.print(", port "); 

        Serial.println(UDP.remotePort()); 

        #endif 

 

        // Lê o pacote recebido 

        int len = UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); 

        if (len > 0) 

        { 

          packetBuffer[len] = 0; 

        } 

         

        #if (__debug == 1) 

        Serial.println("Contents: "); 

        Serial.println(packetBuffer); 

        #endif 

 

         

        delay(30); 

 // Alterna o estado do pino de ativação dos atuadores da pulseira proporcionalmente ao comando do pacote recebido 

        DecodePacket(); 

      } 

    } 

  } 

} 

 

// Loop para piscar o LED de status do WiFi de maneira a representar que há conexão 

void BlinkWiFiConnected() 

{ 

  digitalWrite(pinWifiLed, HIGH); 

  delay(100); 

  digitalWrite(pinWifiLed, LOW); 

  delay(3000); 

} 

 

// Loop para piscar o LED de status do WiFi de maneira a representar que não há conexão 

void BlinkWiFiDisconnected() 

{ 

  digitalWrite(pinWifiLed, HIGH); 

  delay(250); 

  digitalWrite(pinWifiLed, LOW); 

  delay(250); 

} 

 

// Loop para decodificar o pacote de dados recebido e tomar a ação referente a ele 

void DecodePacket() 

{ 

  if (packetBuffer[0] == warning[0]) 

  { 

    if (packetBuffer[1] == warning[1]) 

    { 

      activateQuery = true; 

    } 

  } 

} 

 

// Loop de interrupção para parar o alarme 

void intStopAlarm_ISR() 

{ 

  digitalWrite(pinAlarmMotor, LOW); 

  digitalWrite(pinAlarmLed, LOW); 

   

  #if (__debug == 1) 

  Serial.print(ledStatusOff); 

  #endif 

   

  packetBuffer[UDP_TX_PACKET_MAX_SIZE] = UDP.read(); 

} 

 

 

// Loop de requisição de ativação dos atuadores de alarme da pulseira 

void activateRequest() 

{ 

  if (activateQuery == true) 

  { 

    activateAlarm(); 

    activateQuery = false; 

  } 

} 

 

// Loop de ativação dos atuadores de alarme da pulseira 

void activateAlarm() 

{ 

  digitalWrite(pinAlarmMotor, HIGH); 

  digitalWrite(pinAlarmLed, HIGH); 

   

  #if (__debug == 1) 

  Serial.print(ledStatusOn); 

  #endif 

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

    #endif 

  } 

 

  return state; 

} 

// Estabelece uma conexão WiFi e retorna "true" se for bem sucedida ou "false" se não for bem sucedida 

boolean connectWifi() 

{ 

  boolean state = true; 

 

  WiFi.begin(ssid, password); 

   

  #if (__debug == 1) 

  Serial.println(""); 

  Serial.println("Connecting to WiFi"); 

  #endif 

 

  // Aguarda pela conexão 

  while (WiFi.status() != WL_CONNECTED) 

  { 

    BlinkWiFiDisconnected(); 

    break; 

  } 

 

// Quando a conexão WiFi for bem sucedida escreve na serial "Connected to " e o endereço IP que foi estabelecido 

  if (WiFi.status() == WL_CONNECTED) 

  { 

     

    #if (__debug == 1) 

    Serial.println(""); 

    Serial.print("Connected to "); 

    Serial.println(ssid); 

    Serial.print("IP address: "); 

    Serial.println(WiFi.localIP()); 

    #endif 

  } 

  return state; 

} 
