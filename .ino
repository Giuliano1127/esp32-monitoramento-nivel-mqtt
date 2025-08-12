#include <PubSubClient.h>  // Biblioteca MQTT
#include <WiFi.h>          // Biblioteca WiFi

// Definições de pinos
#define TRIG 5
#define ECHO 18
#define ALARME 22

// Variáveis globais
int duration, distancia, nivel;
const int altura = 100; // Altura do tanque (cm)

// Configurações do broker MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "Tanque/Nivel";

// Objetos de conexão
WiFiClient espClient;
PubSubClient client(espClient);

// =======================
// Função: setup()
// Descrição: Inicializa comunicação serial, Wi-Fi, MQTT e configura pinos.
// =======================
void setup() {
  Serial.begin(115200);

  client.setServer(mqtt_server, mqtt_port);

  iniciarWiFi();   
  conectarMQTT();  

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ALARME, OUTPUT);
}

// =======================
// Função: loop()
// Descrição: Mantém conexão MQTT, lê nível do tanque, publica no broker e aciona alarme.
// =======================
void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  medirNivel();

  Serial.print("Nível: ");
  Serial.println(nivel);

  String msg = String(nivel);
  client.publish(mqtt_topic, msg.c_str());

  verificarAlarme();
}

// =======================
// Função: verificarAlarme()
// Descrição: Ativa o alarme se nível > 80% da altura.
// =======================
void verificarAlarme() {
  if (nivel > 80) {
    digitalWrite(ALARME, HIGH);
  } else {
    digitalWrite(ALARME, LOW);
  }
}

// =======================
// Função: medirNivel()
// Descrição: Mede distância com sensor ultrassônico e calcula nível do tanque.
// =======================
void medirNivel() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);      
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distancia = duration / 58;
  nivel = altura - distancia;

  if (nivel < 0) nivel = 0;
}

// =======================
// Função: iniciarWiFi()
// Descrição: Conecta o ESP32 à rede Wi-Fi.
// =======================
void iniciarWiFi() {
  Serial.print("Conectando-se ao Wi-Fi");
  WiFi.begin("Wokwi-GUEST", "", 6);
  
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 50) {
    delay(200);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi conectado!");
  } else {
    Serial.println("\nFalha ao conectar no Wi-Fi.");
  }
}

// =======================
// Função: conectarMQTT()
// Descrição: Conecta ao broker MQTT com tentativas limitadas.
// =======================
void conectarMQTT() {
  int tentativas = 0;
  
  while (!client.connected() && tentativas < 5) {
    Serial.print("Conectando ao broker MQTT... ");

    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s");
      delay(2000);
      tentativas++;
    }
  }

  if (!client.connected()) {
    Serial.println("Não foi possível conectar ao broker MQTT.");
  }
}
