//JVida_JLRV_Controller - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi

#ifndef JVIDA_JLRV_CONTROLLER_H
#define JVIDA_JLRV_CONTROLLER_H
#include "JVida_JLRV_Model.h"
 
void defineDimensao(void);       /* REQ01 Permite a definicao de tamanho (10-60)*/
void incluiExcluiCelulas(void);  /* REQ02 Definir seres vivos da primeira geracao*/
void mostraMapa(void);           /* REQ03 Permite usuario ver o mapa das celulas vivas atuais*/
void alternaVizinhas(void);      /* REQ04 Opcao para mostrar as celulas vizinhas mortas*/
void limpaTudo(void);            /* REQ05 Permitir limpar todas as celulas do mundo*/
void gravaCelulas(void);         /* REQ12 Permite o usuario salvar as geracoes iniciais de celulas vivas em arquivo*/
void carregaConfig(void);        /* REQ13 Permite o usuario carregar cada geracao previamente armazenada */
void recuperaCelulas(void);      /* REQ13 */
void limpaGer(void);
void simulaGeracoes(void);       /* REQ06 a REQ09 */
void executaMenu(void);
 
#endif
