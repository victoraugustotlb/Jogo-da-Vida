//JVida_JLRV_Model - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi

#include <stdio.h>
#include "JVida_JLRV_Model.h"

int  dim = 0;
char Matriz[DIM_MAX][DIM_MAX];
char MatrizAux[DIM_MAX][DIM_MAX];
int  mostraVizinhas = 0;
Arquivo LConfig[MAX_CONFIG];
int  qtconf = 0;
int  ultrecup = -1;

void iniciaModelo(int d)
{
    dim = d;
    mostraVizinhas = 0;
    ultrecup = -1;
    limpaMapa();
}

void limpaMapa(void)
{
    int i, j;
    for (i = 0; i < DIM_MAX; i++)
        for (j = 0; j < DIM_MAX; j++)
        {
            Matriz[i][j] = CEL_MORTA;
            MatrizAux[i][j] = CEL_MORTA;
        }
}

int dentroDoMapa(int lin, int col)
{
    return lin >= 0 && lin < dim && col >= 0 && col < dim;
}

int celulaViva(int lin, int col)
{
    return dentroDoMapa(lin, col) && Matriz[lin][col] == CEL_VIVA;
}

void nasceCelula(int lin, int col)
{
    if (dentroDoMapa(lin, col))
        Matriz[lin][col] = CEL_VIVA;
}

void morreCelula(int lin, int col)
{
    if (dentroDoMapa(lin, col))
        Matriz[lin][col] = CEL_MORTA;
}

int contaVivas(void)
{
    int i, j, n = 0;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            if (Matriz[i][j] == CEL_VIVA)
                n++;
    return n;
}

/* celula nao viva com pelo menos 1 viva nos 8 lados (bordas respeitadas) */
static int ehVizinhaMorta(int lin, int col)
{
    int i, j;
    if (Matriz[lin][col] == CEL_VIVA)
        return 0;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
        {
            if (i == lin && j == col)
                continue;
            if (celulaViva(i, j))
                return 1;
        }
    return 0;
}

int contaVizinhasMortas(void)
{
    int i, j, n = 0;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            if (ehVizinhaMorta(i, j))
                n++;
    return n;
}

void atualizaVizinhasMortas(void)
{
    int i, j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
        {
            if (Matriz[i][j] == CEL_VIVA)
                continue;
            if (mostraVizinhas && ehVizinhaMorta(i, j))
                Matriz[i][j] = CEL_VIZ;
            else
                Matriz[i][j] = CEL_MORTA;
        }
}

/* ---------------- configuracoes iniciais ---------------- */

int copiaVivasParaLista(TipoLista *t)
{
    int i, j, n = 0;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            if (Matriz[i][j] == CEL_VIVA)
            {
                t->L[n].lin = i;
                t->L[n].col = j;
                n++;
            }
    t->cont = n;
    t->dim = dim;
    return n;
}

int gravaArquivoConfig(void)
{
    FILE *fp;
    int i;

    fp = fopen(ARQ_CONFIG, "wb");
    if (fp == NULL)
        return 0;
    for (i = 0; i < qtconf; i++)
    {
        if (fwrite(&LConfig[i], sizeof(Arquivo), 1, fp) != 1)
        {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void carregaArquivoConfig(void)
{
    FILE *fp;

    qtconf = 0;
    fp = fopen(ARQ_CONFIG, "rb");
    if (fp == NULL)
        return;                        /* ainda nao existe: nenhuma config */
    while (qtconf < MAX_CONFIG &&
           fread(&LConfig[qtconf], sizeof(Arquivo), 1, fp) == 1)
        qtconf++;
    fclose(fp);
}

int removeArquivoConfig(void)
{
    return remove(ARQ_CONFIG) == 0;
}
