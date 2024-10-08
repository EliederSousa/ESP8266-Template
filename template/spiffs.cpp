#include <FS.h>
#include <SPIFFS.h>
#include "spiffs.h"


/****************************************************************
                      Operações de arquivo
****************************************************************/
/**
  * @desc escreve conteúdo em um arquivo
  * @param string state - conteúdo a se escrever no arquivo
  * @param string path - arquivo a ser escrito
*/
void writeFile(String state, String path) { 
  //Abre o arquivo para escrita ("w" write)
  //Sobreescreve o conteúdo do arquivo
  File rFile = SPIFFS.open(path,"w+"); 
  if(!rFile){
    Serial.println("[Error]: spiffs::writeFile - Erro ao abrir arquivo.");
  } else {
    rFile.println(state);
  }
  rFile.close();
}
 
/**
  * @desc lê conteúdo de um arquivo
  * @param string path - arquivo a ser lido
  * @return string - conteúdo lido do arquivo
*/
String readFile(String path) {
  File rFile = SPIFFS.open(path,"r");
  if (!rFile) {
    Serial.println("[Error]: spiffs::readFile - Erro ao abrir arquivo.");
  }
  String content = rFile.readStringUntil('\r'); //desconsidera '\r\n'
  rFile.close();
  return content;
}
 
/**
  * @desc inicializa o sistema de arquivos
*/
void openFS(void){
  //Abre o sistema de arquivos
  if(!SPIFFS.begin()){
    Serial.println("[Error]: spiffs::openFS - Erro ao abrir o sistema de arquivos.");
  } else {
    Serial.println("Sistema de arquivos aberto com sucesso.");
  }
}