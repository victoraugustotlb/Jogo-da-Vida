<div align="center">

# Jogo da Vida

**Implementação em C++ do autômato celular de John Conway, com interface de menu no terminal e persistência de configurações.**

![Linguagem](https://img.shields.io/badge/linguagem-C%2B%2B-00599C?logo=cplusplus&logoColor=white)
![Arquitetura](https://img.shields.io/badge/arquitetura-MVC-444444)
![Interface](https://img.shields.io/badge/interface-terminal-2b2b2b)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)

</div>

---

## Índice

- [Visão geral](#visão-geral)
- [Funcionalidades](#funcionalidades)
- [Regras do jogo](#regras-do-jogo)
- [Representação do mapa](#representação-do-mapa)
- [Arquitetura](#arquitetura)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Configuração](#configuração)
- [Instalação e execução](#instalação-e-execução)
- [Persistência de dados](#persistência-de-dados)
- [Compatibilidade e solução de problemas](#compatibilidade-e-solução-de-problemas)
- [Próximos passos](#próximos-passos)
- [Autores](#autores)
- [Licença](#licença)

---

## Visão geral

O **Jogo da Vida** (*Game of Life*) é um autômato celular em que cada célula de uma grade bidimensional assume um de dois estados: **viva** ou **morta**. Este projeto implementa a base da aplicação: criação do mundo, edição da primeira geração, visualização do mapa e gravação/recuperação de configurações iniciais em arquivo.

O código segue o padrão **MVC** (Model, View, Controller), separando o estado do jogo, a apresentação no terminal e a lógica de controle do menu.

> Projeto acadêmico desenvolvido em grupo (19/10/2026).

## Funcionalidades

| ID | Funcionalidade | Descrição |
|:--:|----------------|-----------|
| REQ01 | Definição de dimensão | Define o tamanho do mapa, entre **10 e 60** células por lado |
| REQ02 | Edição da 1ª geração | Inclusão e exclusão de células vivas da geração inicial |
| REQ03 | Visualização do mapa | Exibe o mapa com as células vivas atuais |
| REQ04 | Células vizinhas | Alterna a exibição das células mortas vizinhas de células vivas |
| REQ05 | Limpeza do mundo | Remove todas as células vivas do mapa |
| REQ12 | Gravação de configurações | Salva as gerações iniciais de células vivas em arquivo |
| REQ13 | Recuperação de configurações | Carrega configurações previamente gravadas |

Recursos adicionais: exibição das regras do jogo, validação das entradas do usuário e carregamento automático das configurações salvas ao iniciar o programa.

## Regras do jogo

No modelo clássico de Conway, a próxima geração é determinada pelo número de vizinhos vivos de cada célula (considerando as 8 células ao redor):

1. Uma célula **viva** com menos de 2 vizinhos vivos morre (solidão).
2. Uma célula **viva** com 2 ou 3 vizinhos vivos permanece viva.
3. Uma célula **viva** com mais de 3 vizinhos vivos morre (superpopulação).
4. Uma célula **morta** com exatamente 3 vizinhos vivos torna-se viva (nascimento).

## Representação do mapa

| Símbolo | Significado |
|:-------:|-------------|
| `O` | Célula viva |
| `.` | Célula morta |
| `+` | Célula morta vizinha de uma célula viva (exibição opcional, REQ04) |

Exemplo ilustrativo de um trecho do mapa com a opção de vizinhas ativada:

```
. . . . . . .
. + + + . . .
. + O + . . .
. + O O + . .
. . + + + . .
. . . . . . .
```

## Arquitetura

| Camada | Responsabilidade |
|--------|------------------|
| **Model** | Estado do jogo (matriz do mapa, dimensão, lista de configurações), operações sobre células (nascer, morrer, contar vivas e vizinhas mortas) e persistência em arquivo |
| **View** | Toda a saída em tela (título, menu, mapa, mensagens e regras) e leitura validada de inteiros e respostas sim/não |
| **Controller** | Orquestra Model e View e implementa as ações do menu principal |

Fluxo de inicialização, definido em `main`:

```
apresentaTitulo() → defineDimensao() → carregaConfig() → executaMenu()
```

## Estrutura do repositório

```
Jogo-da-Vida/
├── JVida_JLRV_PROJETO.cpp      # Ponto de entrada (main)
├── Jvida_JLRV_Model.h          # Model: constantes, estruturas e protótipos
├── Jvida_JLRV_Model.cpp        # Model: lógica do mapa e persistência
├── JVida_JLRV_View.h           # View: protótipos de exibição
├── JVida_JLRV_View.cpp         # View: título, menu, mapa, mensagens e regras
├── JVida_JLRV_Controller.h     # Controller: protótipos das operações
├── JVida_JLRV_Controller.cpp   # Controller: menu e fluxo do programa
└── .gitignore
```

## Configuração

Parâmetros definidos em `Jvida_JLRV_Model.h`:

| Constante | Valor | Descrição |
|-----------|:-----:|-----------|
| `DIM_MIN` | `10` | Dimensão mínima do mapa |
| `DIM_MAX` | `60` | Dimensão máxima do mapa |
| `MAX_CONFIG` | `50` | Número máximo de configurações iniciais gravadas |
| `ARQ_CONFIG` | `CONFIG_INIC` | Nome do arquivo de configurações |

## Instalação e execução

### Requisitos

- Compilador C++ (ex.: `g++`, MinGW, MSVC ou Dev-C++)
- Terminal / prompt de comando

### 1. Clonar o repositório

```bash
git clone https://github.com/victoraugustotlb/Jogo-da-Vida.git
cd Jogo-da-Vida
```

### 2. Compilar

O arquivo principal inclui diretamente os `.cpp` das camadas, portanto basta compilar **somente o arquivo principal**:

```bash
g++ JVida_JLRV_PROJETO.cpp -o jogo_da_vida
```

### 3. Executar

```bash
# Linux / macOS
./jogo_da_vida

# Windows
jogo_da_vida.exe
```

### Uso

1. Informe a **dimensão** do mapa (10 a 60).
2. Se existir o arquivo `CONFIG_INIC`, as configurações salvas são carregadas automaticamente.
3. No **menu principal**, inclua ou exclua células, exiba o mapa, alterne as vizinhas mortas, limpe o mundo, grave ou recupere configurações.

## Persistência de dados

As configurações iniciais são gravadas no arquivo `CONFIG_INIC`, no diretório de execução. Para cada configuração, são armazenadas a dimensão do mapa no momento da gravação, a quantidade de células vivas e as coordenadas (linha e coluna) de cada uma. O limite é de 50 configurações.
