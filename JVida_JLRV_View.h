//JVida_JLRV_View - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi
#ifndef JVIDA_JLRV_VIEW_H
#define JVIDA_JLRV_VIEW_H
#include "JVida_JLRV_Model.h"

void apresentaTitulo(void);
int  lerInteiro(const char *prompt, int min, int max);
int  lerSimNao(const char *prompt);
void apresentaMenu(int totConfig);
void apresentaMapa(void);
void apresentaMensagem(const char *msg);
void apresentaMensagemNum(const char *msg, int n);
void apresentaRegras(void);

#endif
