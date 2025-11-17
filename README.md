
# 🔫🎒 Tetris Stack — Controle de Peças com Estruturas de Dados

![C](https://img.shields.io/badge/language-C-0078d7?style=flat-square&logo=c)
![Challenge](https://img.shields.io/badge/challenge-ByteBros-orange?style=flat-square)
![Status](https://img.shields.io/badge/status-Em%20Progresso-yellow?style=flat-square)

Repositório desenvolvido como um desafio educacional para praticar estruturas de dados aplicadas a uma mecânica inspirada em Tetris. O objetivo é implementar e evoluir um sistema de controle de peças usando **fila circular** e **pilha**, com versões incrementais que aumentam a complexidade e introduzem boas práticas.

**Estrutura do repositório**

- `tetris.c`: Arquivo principal com versão base e utilitários compartilhados.
- `tetris-novato.c`: Implementação do Nível Novato (fila circular de peças).
- `tetris-aventureiro.c`: Implementação do Nível Aventureiro (fila + pilha de reserva).
- `tetris-mestre.c`: Implementação do Nível Mestre (operações avançadas entre fila e pilha).
- Executáveis pré-compilados: `tetris-novato`, `tetris-aventureiro`, `tetris-mestre` (quando presentes).
- `README.md`: Documentação (este arquivo).

**Objetivo do desafio**

Construir um conjunto de exercícios em C que ensinem e reforcem o uso de estruturas de dados básicas (fila circular e pilha), modularização, gerenciamento de estado e entrada/saída via terminal.

**Como executar**

Compile e execute cada versão com o compilador Clang (exemplo):

```bash
clang -g tetris-novato.c -o tetris-novato
./tetris-novato

clang -g tetris-aventureiro.c -o tetris-aventureiro
./tetris-aventureiro

clang -g tetris-mestre.c -o tetris-mestre
./tetris-mestre
```

**Principais temas estudados neste projeto**

    - **Estruturas de Dados**: fila circular (queue) e pilha (stack).
    - **Modularização em C**: uso de funções, structs e organização por arquivos.
    - **Gerenciamento de estado**: manter a integridade da fila e da pilha entre operações.
    - **Entrada/Saída via Terminal**: menus interativos e exibição do estado das estruturas.

## 📚 Análise por Nível — O que foi aprendido e utilizado

**Nível Novato** (`tetris-novato.c`):

    - **O que faz:** Implementa uma fila circular fixa com 5 posições que representa as próximas peças do jogo. Permite visualizar a fila, jogar (remover) a peça da frente e inserir automaticamente uma nova peça ao final.
    - **Principais construções usadas:** `struct` para representar peças, arrays estáticos para a fila, índices `head`/`tail`, geração automática de peças (`gerarPeca()`).
    - **I/O e tratamento de strings:** Menu via `printf`/`scanf` (entrada numérica), exibição do estado da fila com `printf`.
    - **Conceitos aprendidos:** Fila circular, gerenciamento de índices, geração automática de elementos, testes básicos via terminal.

**Nível Aventureiro** (`tetris-aventureiro.c`):

    - **O que faz:** Acrescenta uma pilha de reserva (capacidade 3). O jogador pode reservar a peça da frente da fila (push) e usar uma peça reservada (pop). A fila continua sempre com 5 peças, sendo reposta automaticamente.
    - **Principais construções usadas:** Pilha linear (array + topo), chamadas para operações de pilha (`push`/`pop`), reutilização de funções da versão Novato.
    - **I/O e UX:** Menu com opções adicionais; após cada ação, exibe-se o estado da fila e da pilha para feedback imediato.
    - **Conceitos aprendidos:** Integração entre estruturas, limites de capacidade, tratamento de underflow/overflow da pilha e UX simples no terminal.

**Nível Mestre** (`tetris-mestre.c`):

    - **O que faz:** Introduz operações avançadas como troca entre o topo da pilha e a frente da fila, desfazer a última jogada e inverter a interação entre fila e pilha. Mantém a fila circular e a pilha de reserva com todas as validações necessárias.
    - **Principais construções usadas:** Histórico de ações para desfazer, operações de swap entre estruturas, validações robustas e modularização para separar lógica de interface.
    - **Busca e Ordenação:** Não se aplica diretamente ao jogo, foco em manipulação segura de estado e reversibilidade das ações.
    - **Conceitos aprendidos:** Design de operações reversíveis, manutenção da integridade de dados, limpeza e separação de responsabilidades no código.

**Observações gerais e boas práticas aplicadas em todo o projeto**

    - Uso de nomes claros para funções e variáveis, comentários pontuais quando necessário e modularização por responsabilidade.
    - Tratamento de condições de erro (fila vazia/cheia, pilha vazia/cheia) e feedback ao usuário via terminal.
    - Código orientado a ensino: cada versão foca em um conjunto limitado de conceitos, facilitando o aprendizado incremental.

-----

Feito por Wilson Oliveira 🚀


