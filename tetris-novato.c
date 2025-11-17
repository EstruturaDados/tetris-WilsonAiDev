#include <stdio.h>
#include <stdlib.h> // Para rand() e srand()
#include <string.h>
#include <time.h>   // Para time()
#include <stdbool.h> // Para usar o tipo 'bool'

// --- Constantes Globais ---
#define TAM_FILA 5 // A fila deve conter exatamente 5 elementos

// --- Estrutura de Dados ---

// Struct Peca com os campos: tipo (char) e id (int)
struct Peca {
    char tipo;
    int id;
};

// Estrutura da Fila Circular
struct Fila {
    struct Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int total;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
void pausar();

// Funções da Fila
void inicializarFila(struct Fila *f);
bool filaVazia(struct Fila *f);
bool filaCheia(struct Fila *f);
void enqueue(struct Fila *f, struct Peca peca);
struct Peca dequeue(struct Fila *f);
void mostrarFila(struct Fila *f);

// Função de Jogo
struct Peca gerarPeca();

// Variável global estática para garantir IDs exclusivos
static int proximoId = 1;


// --- Função Principal (main) ---
int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    struct Fila filaDePecas;
    int opcao;

    // 1. Inicializar a fila
    inicializarFila(&filaDePecas);

    // 2. Preencher a fila inicial com 5 peças geradas automaticamente
    printf("Gerando fila inicial de pecas...\n");
    for(int i = 0; i < TAM_FILA; i++) {
        enqueue(&filaDePecas, gerarPeca());
    }

    // 3. Laço Principal do Jogo (Menu)
    do {
        mostrarFila(&filaDePecas); // Exibe a fila a cada ação
        
        printf("\n--- TETRIS STACK ---\n");
        printf("1. Jogar peca (dequeue)\n"); 
        printf("0. Sair\n");                   
        printf("Escolha sua acao: ");
        
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                // Jogar peça: Remove da frente (dequeue) e insere uma nova no final (enqueue)
                if (!filaVazia(&filaDePecas)) {
                    struct Peca pecaJogada = dequeue(&filaDePecas);
                    printf("\n>> Peca jogada: [%c %d]\n", pecaJogada.tipo, pecaJogada.id);

                    // Automaticamente insere uma nova peça para manter a fila cheia
                    struct Peca novaPeca = gerarPeca();
                    enqueue(&filaDePecas, novaPeca);
                    printf(">> Nova peca [%c %d] entrou no final da fila.\n", novaPeca.tipo, novaPeca.id);
                } else {
                    printf("\nFila vazia (isso nao deveria acontecer no modo de jogo normal!)\n");
                }
                pausar();
                break;
            case 0:
                printf("\nSaindo do jogo. Ate a proxima!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
                break;
        }

    } while (opcao != 0);

    return 0;
}


// --- Implementação das Funções Auxiliares ---

// Limpa o buffer de entrada do teclado
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Pausa a execução e espera o usuário pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

// --- Implementação das Funções da Fila ---

// Inicializa os ponteiros da fila
void inicializarFila(struct Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está vazia
bool filaVazia(struct Fila *f) {
    return (f->total == 0);
}

// Verifica se a fila está cheia
bool filaCheia(struct Fila *f) {
    return (f->total == TAM_FILA);
}

// Adiciona um item no final da fila (enqueue)
void enqueue(struct Fila *f, struct Peca peca) {
    if (filaCheia(f)) {
        printf("ERRO: Fila cheia!\n"); 
        return;
    }
    
    f->itens[f->fim] = peca;
    f->fim = (f->fim + 1) % TAM_FILA; // Lógica circular
    f->total++;
}

// Remove um item do início da fila (dequeue)
struct Peca dequeue(struct Fila *f) {
    struct Peca pecaVazia = {'?', -1}; // Peça "vazia" para retorno em caso de erro
    
    if (filaVazia(f)) {
        printf("ERRO: Fila vazia!\n");
        return pecaVazia;
    }
    
    struct Peca pecaRemovida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA; // Lógica circular
    f->total--;
    
    return pecaRemovida;
}

// Exibe o estado atual da fila
void mostrarFila(struct Fila *f) {
    printf("\n-----------------------------------\n");
    printf("Fila de Pecas: "); 
    
    if (filaVazia(f)) {
        printf("[VAZIA]");
    } else {
        int i = f->inicio;
        for (int count = 0; count < f->total; count++) {
            // Imprime no formato [TIPO ID]
            printf("[%c %d] ", f->itens[i].tipo, f->itens[i].id);
            i = (i + 1) % TAM_FILA; // Avança circularmente
        }
    }
    printf("\n-----------------------------------\n");
}


// --- Implementação da Função de Jogo ---

// Gera uma nova peça aleatória
struct Peca gerarPeca() {
    struct Peca novaPeca;
    
    // Tipos de peças mencionados no desafio
    char tiposPossiveis[] = "IOTL"; 
    
    // Sorteia um dos 4 tipos
    novaPeca.tipo = tiposPossiveis[rand() % 4]; 
    
    // Atribui o próximo ID exclusivo
    novaPeca.id = proximoId;
    proximoId++; // Incrementa o ID para a próxima chamada
    
    return novaPeca;
}