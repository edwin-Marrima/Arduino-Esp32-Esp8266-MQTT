/*
 * Responsavel por conectar a web e ao Broker.... 
 */
 void conectaWiFi() {

                            if (WiFi.status() == WL_CONNECTED) {
                               return;
                            }
                                  
                            Serial.print("Conectando-se na rede: ");
                            Serial.print(SSID);
                            Serial.println("  Aguarde!");
                          
                            WiFi.begin(SSID); // Conecta na rede WI-FI
                            int contador=0;  
                            while (WiFi.status() != WL_CONNECTED) {
                                contador++;
                                delay(100);
                                Serial.print(".");
                                    if(contador==5){
                                      ESP.restart();
                                      }
                            }
                            
                            Serial.println();
                            Serial.print("Conectado com sucesso, na rede: ");
                            Serial.print(SSID);  
                            Serial.print("  IP obtido: ");
                            Serial.println(WiFi.localIP()); 
}

//**********************************B R O K E R**************
void mantemConexoesComBROker() {
                            
                            if (!MQTT.connected()) {
                               conectaWiFi();
                               conectaMQTT(); 
                            }
                            
                            conectaWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
void conectaMQTT() { 
                          while (!MQTT.connected()) {
                              Serial.print("Conectando ao Broker MQTT: ");
                              Serial.println(BROKER_MQTT);
                              if (MQTT.connect(ID_MQTT)) {
                                  Serial.println("Conectado ao Broker com sucesso!");
                                  MQTT.subscribe(TOPIC_SUBSCRIBE);
                              } 
                              else {
                                  Serial.println("Noo foi possivel se conectar ao broker.");
                                  Serial.println("Nova tentatica de conexao em 10s");
                                  delay(10000);
                              }
                          }
}
/*microcontrolador fica um subscriber*/
void recebePacote(char* topic, byte* payload, unsigned int length) {
                              String msg;
                           
                              //obtem a string do payload recebido
                              for(int i = 0; i < length; i++) 
                              {
                                 char c = (char)payload[i];
                                 msg += c;
                              }Serial.println("mesagem:");Serial.println(msg);
                              if(msg.startsWith(IDENTIFICADOR)){
                                if(msg.endsWith("cmd")){
                               AcionamentoIndividual(msg);
                                  }else if(msg.endsWith("all_L")){
                                    EnvioEstadoGeral(msg);
                                    }
                                }
//                              String respostaa = "Estou ligado";
//                              char  aaax[respostaa.length()+1];
//                              respostaa.toCharArray(aaax, respostaa.length()+1);
//                              char* retornoo =aaax;
//                              enviaValores(retornoo);
                              
}
/*O microcontrolado fica um publish*/
void enviaValores(char * as) {
                          Serial.println("Enviando resposta");
                          Serial.println(as);
                          MQTT.publish(TOPIC_PUBLISH,as);
}    
