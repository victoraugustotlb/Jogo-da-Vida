//JVida_JLRV_Controller - Projeto Jogo da Vida
//19/10/2026
//Joao Pedro Lemos Romano Francisco da Silva
//Leopoldo Ortuzal Zuchieri
//Renato Corral Silva
//Victor Augusto Toledo Lucio Borghi

#include <stdio.h>
#include "JVida_JLRV_Controller.h"
#include "JVida_JLRV_View.cpp"
#include "JVida_JLRV_Model.h"

/* REQ01 */
void defineDimensao(void)
{
    char prompt[80];
    int d;

    sprintf(prompt, "Dimensao do mapa (%d a %d): ", DIM_MIN, DIM_MAX);
    d = lerInteiro(prompt, DIM_MIN, DIM_MAX);
    iniciaModelo(d);
    limpaTela();
    mostraMapa();
}

/* REQ03 */
void mostraMapa(void)
{
    atualizaVizinhasMortas();
    apresentaMapa();
}

/* REQ02 */
void incluiExcluiCelulas(void)
{
    char pl[80], pc[80];
    int l, c;
    const char *msg = NULL;            /* mensagem mostrada abaixo do mapa */

    sprintf(pl, "Linha (0 a %d, -1 para terminar): ", dim - 1);
    sprintf(pc, "Coluna (0 a %d): ", dim - 1);

    while (1)
    {
        limpaTela();
        mostraMapa();
        if (msg != NULL)
            apresentaMensagem(msg);
        msg = NULL;

        l = lerInteiro(pl, -1, dim - 1);
        if (l == -1)
            break;
        c = lerInteiro(pc, 0, dim - 1);

        if (celulaViva(l, c))
        {
            if (lerSimNao("Celula ja existe. Excluir? (s/n): "))
            {
                morreCelula(l, c);
                msg = "Celula excluida.";
            }
        }
        else
        {
            nasceCelula(l, c);
            msg = "Celula incluida.";
        }
    }
}

/* REQ04 */
void alternaVizinhas(void)
{
    mostraVizinhas = !mostraVizinhas;
    limpaTela();
    mostraMapa();
}

/* REQ05 */
void limpaTudo(void)
{
    limpaMapa();
    limpaTela();
    mostraMapa();
    apresentaMensagem("Mapa limpo.");
}

/* REQ12: grava a configuracao atual (acrescenta ao final do arquivo) */
void gravaCelulas(void)
{
    if (contaVivas() == 0)
    {
        apresentaMensagem("Nao ha celulas vivas para gravar.");
        return;
    }
    if (qtconf >= MAX_CONFIG)
    {
        apresentaMensagem("Cadastro cheio. Limpe o cadastro (opcao 8) para gravar.");
        return;
    }
    copiaVivasParaLista(&LConfig[qtconf].TL);
    qtconf++;
    if (!gravaArquivoConfig())
    {
        qtconf--;
        apresentaMensagem("ERRO: o arquivo CONFIG_INIC nao pode ser gravado.");
        return;
    }
    apresentaMensagemNum("Configuracao gravada OK. Numero da configuracao:", qtconf);
}

/* REQ13: carrega todo o arquivo para o array LConfig (chamado ao iniciar) */
void carregaConfig(void)
{
    carregaArquivoConfig();
    ultrecup = -1;
}

/* REQ13: recupera a PROXIMA configuracao (circular) */
void recuperaCelulas(void)
{
    int k, i, fora = 0;
    TipoLista *t;

    if (qtconf == 0)
    {
        apresentaMensagem("Nao existe configuracao a recuperar.");
        return;
    }
    k = ultrecup + 1;
    if (k >= qtconf)
        k = 0;
    t = &LConfig[k].TL;

    limpaMapa();
    for (i = 0; i < t->cont; i++)
    {
        if (dentroDoMapa(t->L[i].lin, t->L[i].col))
            nasceCelula(t->L[i].lin, t->L[i].col);
        else
            fora++;
    }
    ultrecup = k;

    limpaTela();
    mostraMapa();
    apresentaMensagemNum("Configuracao recuperada, numero:", k + 1);
    if (t->dim != dim)
        apresentaMensagemNum("Atencao: gravada com dimensao", t->dim);
    if (fora > 0)
        apresentaMensagemNum("Celulas fora do mapa atual (ignoradas):", fora);
}

void limpaGer(void)
{
    if (qtconf == 0)
    {
        apresentaMensagem("O deposito de geracoes iniciais ja esta vazio.");
        return;
    }
    if (!lerSimNao("Confirma exclusao das configuracoes iniciais? (s/n): "))
        return;
    removeArquivoConfig();
    qtconf = 0;
    ultrecup = -1;
    apresentaMensagem("O deposito de geracoes iniciais esta vazio.");
}

/* REQ06, REQ07, REQ08, REQ09 */
void simulaGeracoes(void)
{
    int total, seg, g;

    if (contaVivas() == 0)
    {
        apresentaMensagem("Nao ha celulas vivas. Inclua celulas (opcao 2) ou recupere uma geracao (opcao 7).");
        return;
    }

    total = lerInteiro("Quantidade de geracoes a simular (1 a 9999): ", 1, 9999);
    seg = lerInteiro("Velocidade: segundos entre geracoes (0 = passo-a-passo, 1 a 59): ", 0, 59);

    limpaTela();
    apresentaGeracao(1, total);
    mostraMapa();                       /* REQ09: contagens abaixo do mapa */

    for (g = 2; g <= total; g++)
    {
        if (seg == 0)
        {
            if (!aguardaPasso())
            {
                apresentaMensagem("Simulacao interrompida pelo operador.");
                return;
            }
        }
        else
            ftempo(seg);

        proximaGeracao();
        limpaTela();
        apresentaGeracao(g, total);
        mostraMapa();

        if (contaVivas() == 0)
        {
            apresentaMensagem("Todas as celulas morreram. Simulacao encerrada.");
            return;
        }
    }
    apresentaMensagem("Simulacao concluida.");
}

void executaMenu(void)
{
    int op;

    do
    {
        apresentaMenu(qtconf);
        op = lerInteiro("Opcao selecionada: ", 0, 9);
        switch (op)
        {
            case 1:  limpaTudo();           break;   /* ja apresenta o mapa */
            case 2:  incluiExcluiCelulas(); break;   /* apresenta o mapa a cada alteracao */
            case 3:  alternaVizinhas();     break;   /* ja apresenta o mapa */
            case 4:  simulaGeracoes();      break;   /* apresenta cada geracao */
            case 5:  apresentaMensagem("Listas: serao implementadas na etapa LP6.");  break;
            case 6:  gravaCelulas();        break;
            case 7:  recuperaCelulas();     break;   /* ja apresenta o mapa */
            case 8:  limpaGer();            break;
            case 9:  apresentaRegras();     break;
            case 0:  apresentaMensagem("Ate logo!"); break;
        }
    } while (op != 0);
}
