//JVida_JLRV_Model - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi

#ifndef JVIDA_JLRV_MODEL_H
#define JVIDA_JLRV_MODEL_H

#define DIM_MIN     10
#define DIM_MAX     60
#define MAX_CONFIG  50                 /* maximo de geracoes iniciais gravadas */
#define MAX_CEL     (DIM_MAX * DIM_MAX)
#define ARQ_CONFIG  "CONFIG_INIC"

#define CEL_VIVA    'O'
#define CEL_MORTA   '.'
#define CEL_VIZ     '+'                /* morta vizinha de uma viva */

typedef struct c
{
    int lin, col;
} Cel;

typedef struct list
{
    int dim;                           /* dimensao do mapa quando foi gravada */
    int cont;                          /* quantidade de celulas vivas */
    Cel L[MAX_CEL];
} TipoLista;

typedef struct arquivo
{
    TipoLista TL;                      /* 1 configuracao inicial */
} Arquivo;

/* ---- variaveis globais do modelo (definidas em model.c) ---- */
extern int  dim;                       /* dimensao escolhida (10 a 60) */
extern char Matriz[DIM_MAX][DIM_MAX];     /* mapa atual */
extern char MatrizAux[DIM_MAX][DIM_MAX];  /* auxiliar (usada na etapa LP5) */
extern int  mostraVizinhas;            /* sentinela: mostrar '+' ? */
extern Arquivo LConfig[MAX_CONFIG];
extern int  qtconf;                    /* configuracoes cadastradas */
extern int  ultrecup;                  /* ultima configuracao recuperada (-1 = nenhuma) */

/* ---- mapa ---- */
void iniciaModelo(int d);
void limpaMapa(void);
int  dentroDoMapa(int lin, int col);
int  celulaViva(int lin, int col);
void nasceCelula(int lin, int col);
void morreCelula(int lin, int col);
int  contaVivas(void);
int  contaVizinhasMortas(void);
void atualizaVizinhasMortas(void);     /* marca/desmarca '+' conforme mostraVizinhas */

/* ---- configuracoes iniciais (persistencia) ---- */
int  copiaVivasParaLista(TipoLista *t);
int  gravaArquivoConfig(void);         /* 1 = ok, 0 = erro */
void carregaArquivoConfig(void);
int  removeArquivoConfig(void);        /* 1 = ok, 0 = erro */

#endif
