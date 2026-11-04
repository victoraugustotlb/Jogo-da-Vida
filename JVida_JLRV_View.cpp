//JVida_JLRV_View - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi

#include "JVida_JLRV_View.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define TAM_LINHA 100

void apresentaTitulo(void)
{
    printf("\n=====================================================\n");
    printf("   J O G O   D A   V I D A   (matriz n X n)\n");
    printf("=====================================================\n");
}

/* limpa o terminal: "cls" no Windows, "clear" em Linux/Mac */
void limpaTela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static int leLinha(char *buf, int tam)
{
    if (fgets(buf, tam, stdin) == NULL)
    {
        printf("\nEntrada encerrada. Saindo do programa.\n");
        exit(0);
    }
    return 1;
}

int lerInteiro(const char *prompt, int min, int max)
{
    char buf[TAM_LINHA];
    int v;

    while (1)
    {
        printf("%s", prompt);
        leLinha(buf, TAM_LINHA);
        if (sscanf(buf, "%d", &v) == 1 && v >= min && v <= max)
            return v;
        printf("  Valor invalido. Digite um numero de %d a %d.\n", min, max);
    }
}

int lerSimNao(const char *prompt)
{
    char buf[TAM_LINHA];

    while (1)
    {
        printf("%s", prompt);
        leLinha(buf, TAM_LINHA);
        if (toupper((unsigned char)buf[0]) == 'S')
            return 1;
        if (toupper((unsigned char)buf[0]) == 'N')
            return 0;
        printf("  Responda s ou n.\n");
    }
}

void apresentaMenu(int totConfig)
{
    printf("\nProjeto J O G O D A V I D A (usando matriz %d X %d)\n", dim, dim);
    printf("===========================================\n");
    printf("1 - Limpar o Mapa\n");
    printf("2 - Incluir/excluir celulas vivas\n");
    printf("3 - Mostrar/Esconder os mortos-vizinhos  [%s]\n",
           mostraVizinhas ? "mostrando" : "escondidos");
    printf("4 - INICIAR O PROCESSO (simular geracoes)\n");
    printf("5 - Apresentar as Listas (etapa LP6)\n");
    printf("6 - Gravar uma geracao inicial\n");
    printf("7 - Recuperar uma geracao inicial cadastrada\n");
    printf("8 - Limpar o cadastro de geracoes iniciais (%d cadastradas)\n", totConfig);
    printf("9 - Regras de evolucao das celulas\n");
    printf("0 - Sair\n");
}

void apresentaMapa(void)
{
    int i, j;

    printf("\n    ");
    for (j = 0; j < dim; j++)
        printf("%d ", j / 10);
    printf("\n    ");
    for (j = 0; j < dim; j++)
        printf("%d ", j % 10);
    printf("\n");

    for (i = 0; i < dim; i++)
    {
        printf("%02d  ", i);
        for (j = 0; j < dim; j++)
            printf("%c ", Matriz[i][j]);
        printf("\n");
    }
    printf("Celulas vivas: %d   Vizinhas-mortas: %d\n",
           contaVivas(), contaVizinhasMortas());
}

void apresentaMensagem(const char *msg)
{
    printf(">> %s\n", msg);
}

void apresentaMensagemNum(const char *msg, int n)
{
    printf(">> %s %d\n", msg, n);
}

void apresentaRegras(void)
{
    printf("\nREGRAS DE EVOLUCAO DAS CELULAS\n");
    printf("- Reproducao: celula vazia com exatamente 3 vizinhos vivos passa a ser viva.\n");
    printf("- Sobrevivencia: celula viva com 2 ou 3 vizinhos vivos continua viva.\n");
    printf("- Morte por falta de comida: viva com 4 ou mais vizinhos morre.\n");
    printf("- Morte por solidao: viva com 0 ou 1 vizinho morre.\n");
    printf("As regras sao aplicadas a todas as celulas ao mesmo tempo.\n");
    printf("Legenda: 'O' = viva, '.' = morta, '+' = morta vizinha de uma viva.\n");
}

/* atraso controlado (valido de 1 a 59 segundos) */
void ftempo(int seg)
{
    time_t lt1, lt2;
    lt1 = time(NULL);
    lt2 = lt1;
    while (difftime(lt2, lt1) < seg)
        lt2 = time(NULL);
}

/* REQ07: identifica a geracao apresentada */
void apresentaGeracao(int ger, int total)
{
    printf("\n######## GERACAO %d de %d ########", ger, total);
}

/* REQ08 (velocidade 0): Enter = proxima geracao, f + Enter = interrompe */
int aguardaPasso(void)
{
    char buf[TAM_LINHA];

    printf("[Enter] proxima geracao  |  [f] + Enter para finalizar: ");
    leLinha(buf, TAM_LINHA);
    if (toupper((unsigned char)buf[0]) == 'F')
        return 0;
    return 1;
}
