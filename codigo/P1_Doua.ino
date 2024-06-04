

/* Proxecto casa domótica. Conexión do ESP32 á wifi e ao MQTT broker */
#include <WiFi.h>
#include <PubSubClient.h>     

#define wifi_ssid "Domotica"                  //wifi ssid
#define wifi_contrasinal "tecnoteis"     // contrasinal wifi 
#define mqtt_server "192.168.12.61"        // nome ou ip do servidor broker mqtt

unsigned long milisAnteriores = 0; 

long lastMsg = 0;
char msg[50];
int value = 0;




// Creanse os obxectos   cliente wifi e cliente mqtt
WiFiClient espCliente3;
PubSubClient client(espCliente3);
 
void setup() {
  Serial.begin(115200);     
  setup_wifi();                           //Conexíon a rede Wifi
  client.setServer(mqtt_server, 1883);  // Configura a conexión MQTT
  
  
}
 
//Preparando a conexión a wifi
void setup_wifi() {
  delay(20);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(wifi_ssid);
  
  WiFi.begin(wifi_ssid, wifi_contrasinal);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
 
 Serial.println("");
 Serial.println("Conexión correcta ");
 Serial.print("=> ESP32 a dirección IP address é: ");
 Serial.print(WiFi.localIP());
 Serial.println("");
}
 
//Reconexión a wifi si a conexión se perdeu
void reconnect() {
 
  while (!client.connected()) {
    Serial.print("Conectando o MQTT broker ...");
    if (client.connect("ESP32Client")) {
      Serial.println("Reconexión ao servidor mqtt correcta");
    } else {
      Serial.print("[Error] Non conectado ao servidor mqtt: ");
      Serial.print(client.state());
      Serial.println("Esperando 5 segundos antes de reintentalo.");
      delay(5000);
    }
  }
}


 
void loop() { 


 unsigned long milisActuais = millis();

  if (milisActuais - milisAnteriores >= 60000) {
    milisAnteriores = milisActuais;

    if (!client.connected()) {
      reconnect();
    }
     
    }
  
}   
     
  


  
