 /* Proxecto casa domótica. Práctica 2. Control dun LED 
 Doua Hailass Khal, maio 2024*/


#include <WiFi.h>
#include <PubSubClient.h>


// Completa cos teus datos:SSID, contrasinal e IP do broker MQTT
const char* ssid = "Domotica";
const char* password = "tecnoteis";
const char* mqtt_server = "192.168.12.61";

WiFiClient espClient3;
PubSubClient client(espClient3);
long lastMsg = 0;
char msg[50];
int value = 0;


// Pin do LED
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
 
  setup_wifi();
  client.setServer(mqtt_server, 1883);     //porto do broker
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);      //Pin do LED como saída
}

void setup_wifi() {
  delay(10);
  // Conectamos á wifi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("conectado á WiFi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Chegou mensaxe ao topic: ");
  Serial.print(topic);
  Serial.print(". Mensaxe: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Aquí se engadirían os seguintes dispositivos controlados por GPIOs

  // Se chega unha mensaxe ao topic casa/actuadores/led chequea se é 1 ou 2 
  //Non utilizamos True False para poder utilizar os mesmos nodos NodeRed con Arduinoblocks
  // Cambia o estado da saída de acordo coa mensaxe
  if (String(topic) == "casa/actuadores/led3") {
    Serial.print("Cambiando a saída a  ");
    if(messageTemp == "true"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "false"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Bucle ata que conectemos
  while (!client.connected()) {
    Serial.print("Tentando conexión MQTT...");
    // Tentando conectar
    if (client.connect("ESP8266Client")) {
      Serial.println("conectado");
      // Subscribir
      client.subscribe("casa/actuadores/led3");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" tentar de novo en 5 segundos");
      // Esperar 5 segundos antes de reintentar
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    
  }
}

