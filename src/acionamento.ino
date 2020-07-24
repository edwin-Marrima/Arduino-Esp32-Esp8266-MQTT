void AcionamentoIndividual(String msg) {
                          String transforma  =   msg.substring(12,14);                                       
                          char  aaax[msg.length()+1];
                          transforma.toCharArray(aaax, transforma.length()+1);
                          char* retornoo =aaax;
                          int porta = atoi(retornoo);
                          int c= msg.charAt(15)-'0';
                          digitalWrite(porta,c);
                          resposta(porta,c);
 
  }
 void resposta(int porta,int estado){  
                        String respostaa = IDENTIFICADOR;
                        respostaa = respostaa+' '+String(porta)+'-'+String(estado);
             
                        char  aaax[respostaa.length()+1];
                        respostaa.toCharArray(aaax, respostaa.length()+1);
                        char* retornoo =aaax;
                        enviaValores(retornoo);
  } 
void EnvioEstadoGeral(String msg){
                        String resposta = IDENTIFICADOR;
                        for(int i=0;i<5;i++){
                          if(digitalRead(lamp[i])==false){resposta +=" "+String(lamp[i])+"-"+"0";}
                          else{resposta +=" "+String(lamp[i])+"-"+"1";}
                          }
                          resposta+=" all_L";
                        char  aaax[resposta.length()+1];
                        resposta.toCharArray(aaax, resposta.length()+1);
                        char* retornoo =aaax;
                        enviaValores(retornoo);
      }
