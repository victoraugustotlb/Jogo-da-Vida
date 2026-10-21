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

    sprintf(pl, "Linha (0 a %d, -1 para terminar): ", dim - 1);
    sprintf(pc, "Coluna (0 a %d): ", dim - 1);

    mostraMapa();
    while (1)
    {
        l = lerInteiro(pl, -1, dim - 1);
        if (l == -1)
            break;
        c = lerInteiro(pc, 0, dim - 1);

        if (celulaViva(l, c))
        {
            if (lerSimNao("Celula ja existe. Excluir? (s/n): "))
            {
                morreCelula(l, c);
                apresentaMensagem("Celula excluida.");
            }
        }
        else
        {
            nasceCelula(l, c);
            apresentaMensagem("Celula incluida.");
        }
        mostraMapa();
    }
}

/* REQ04 */
void alternaVizinhas(void)
{
    mostraVizinhas = !mostraVizinhas;
    mostraMapa();
}

/* REQ05 */
void limpaTudo(void)
{
    limpaMapa();
    apresentaMensagem("Mapa limpo.");
    mostraMapa();
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
        apresentaMensagem("Cadastro cheio. Limpe o cadastro (opcao 9) para gravar.");
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

    apresentaMensagemNum("Configuracao recuperada, numero:", k + 1);
    if (t->dim != dim)
        apresentaMensagemNum("Atencao: gravada com dimensao", t->dim);
    if (fora > 0)
        apresentaMensagemNum("Celulas fora do mapa atual (ignoradas):", fora);
    mostraMapa();
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

void executaMenu(void)
{
    int op;

    do
    {
        apresentaMenu(qtconf);
        op = lerInteiro("Opcao selecionada: ", 0, 10);
        switch (op)
        {
            case 1:  mostraMapa();          break;
            case 2:  limpaTudo();           break;
            case 3:  incluiExcluiCelulas(); break;
            case 4:  alternaVizinhas();     break;
            case 5:  apresentaMensagem("Simulacao: sera implementada na etapa LP5."); break;
            case 6:  apresentaMensagem("Listas: serao implementadas na etapa LP6.");  break;
            case 7:  gravaCelulas();        break;
            case 8:  recuperaCelulas();     break;
            case 9:  limpaGer();            break;
            case 10: apresentaRegras();     break;
            case 0:  apresentaMensagem("Ate logo!"); break;
        }
    } while (op != 0);
}
