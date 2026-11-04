//JVida_JLRV_Projeto - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi

#include <stdio.h>
#include "JVida_JLRV_Model.cpp"
#include "JVida_JLRV_Controller.cpp"

int main(){
    apresentaTitulo();
    defineDimensao();     //antes do menu e fora dele
    carregaConfig();      //le CONFIG_INIC, se existir
    executaMenu();
    return 0;
}
