/*Objectivo
 * acionar/conntrolar duas lampadas.. rele, sensor de corrente
 * abrir portao... somente rele 
 * saber o estado da bomba de agua... somente sensor de coorente 
 */
 /*Material necessario
  * tres modulos reles
  * Tres modulos sensor de corrente...
  */
#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>
void conectaWiFi();

/*Valores de Sensores Padronizados*/
const int ValorMinimoLigado = 3000;

/*Conexao Wifi*/
const char* SSID = "POO";                // SSID / nome da rede WiFi que deseja se conectar
const char* PASSWORD = "F9517AFC";   // Senha da rede WiFi que deseja se conectar
WiFiClient wifiClient;   
void enviaValores(char * as);
/*conexao ao Broker*/
const String IDENTIFICADOR = "01-01-02-01";// temos varios clientes, pra poder identificar somente...

const char* BROKER_MQTT = "test.mosquitto.org"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                      // Porta do Broker MQTT
#define ID_MQTT  "BCI01"            //Informe um ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior. 
#define TOPIC_PUBLISH "PublicIluminationSystemReceive"    //Informe um Tópico único. Caso sejam usados tópicos em duplicidade, o último irá eliminar o anterior.
#define TOPIC_SUBSCRIBE "PublicIluminationSystemSend"
PubSubClient MQTT(wifiClient);        // Instancia o Cliente MQTT passando o objeto espClient

void enviaValores(char * as);
int lamp[] = {13,12,27,26,14};
int input_analog[] = {34,35,32};

void setup() {
pinMode(13,OUTPUT);
Serial.begin(115200);  
  //acionamento lampada_1; lampada_2; portao;
for (int i = 0 ; i < 5 ; i++){pinMode(lamp[i],OUTPUT);}
 //controlo lampada_1; lampada_2; bomba de agua
pinMode(input_analog[0],INPUT);pinMode(input_analog[1],INPUT);pinMode(input_analog[2],INPUT);
conectaWiFi(); //conexao ao wifi

MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
MQTT.setCallback(recebePacote);
}

void loop() {
  mantemConexoesComBROker();
  MQTT.loop(); // para que fique em constante comunicacao com o broker....
  //enviaValores("olaaa");
}
