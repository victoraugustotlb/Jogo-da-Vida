//JVida_JLRV_Controller - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi
#ifndef JVIDA_JLRV_CONTROLLER_H
#define JVIDA_JLRV_CONTROLLER_H
#include "JVida_JLRV_Model.h"

void defineDimensao(void);       /* REQ01 Permite a definição de tamanho (10-60)*/
void incluiExcluiCelulas(void);  /* REQ02 Definir seres vivos da primeira geração*/
void mostraMapa(void);           /* REQ03 Permite usuário ver o mapa das células vivas atuais*/
void alternaVizinhas(void);      /* REQ04 Opção para mostrar as células vizinhas mortas*/
void limpaTudo(void);            /* REQ05 Permitir limpar todas as células do mundo*/
void gravaCelulas(void);         /* REQ12 Permite o usuário salvar as gerações iniciais de células vivas em arquivo*/
void carregaConfig(void);        /* REQ13 Permite o usuário carregar cada geração previamente armazenada */
void recuperaCelulas(void);      /* REQ13 */
void limpaGer(void);
void executaMenu(void);

#endif
