#include <ESP8266WiFi.h>

// configuração da conexão
const char* ssid = "";
const char* password = "";

// variáveis
char temp;
String values;
String TestValues;

// porta de serviço
WiFiServer server(80);

void setup() {
  // valores para testes
  TestValues = "{\"v\":10.00,\"i\":1.00,\"z\":2.00}";
  // taxa de transmissão
  Serial.begin(9600);
  delay(10);

  // configuracão da rede
  IPAddress local_ip(192, 168, 1, 150);
  IPAddress gateway(192, 168, 1, 2);
  IPAddress subnet(255, 255, 255, 0);

  if (!WiFi.config(local_ip, gateway, subnet)) {
    Serial.println("Erro na configuração de rede.");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Conectado à rede sem fio - ");
  Serial.println(ssid);
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop(){
  // verifica nova conexão
  WiFiClient client = server.available();
  if (!client){
    return;
  }

  // verifica se existe envio de dados via serial
  if (Serial.available()){
    values = "";
    while (Serial.available()){
      // armazena o valor enviado em "values" até receber o caractere '\r'
      values = Serial.readStringUntil('\r');
    }
  }

  // faz a leitura da requisição
  String request = client.readStringUntil('\r');
  Serial.println(request);
  // aguarda até que o cliente receba todos os dados necessários
  client.flush();
  // habilita requisição da aplicação externa
  client.println("HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n");
  client.println(values);
  delay(1);
}
