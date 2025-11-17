#include <stdio.h>
#include <stdlib.h> // Para rand() e srand()
#include <string.h>
#include <time.h>   // Para time()
#include <stdbool.h> // Para usar o tipo 'bool'

// --- Constantes Globais ---
#define TAM_FILA 5  // Fila deve conter 5 elementos
#define TAM_PILHA 3 // Pilha tem capacidade máxima de 3 peças

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

// Estrutura da Pilha Linear
struct Pilha {
    struct Peca itens[TAM_PILHA];
    int topo;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
void pausar();
struct Peca gerarPeca();

// Funções da Fila
void inicializarFila(struct Fila *f);
bool filaVazia(struct Fila *f);
bool filaCheia(struct Fila *f);
void enqueue(struct Fila *f, struct Peca peca);
struct Peca dequeue(struct Fila *f);
void mostrarFila(struct Fila *f);

// Funções da Pilha
void inicializarPilha(struct Pilha *p);
bool pilhaVazia(struct Pilha *p);
bool pilhaCheia(struct Pilha *p);
void push(struct Pilha *p, struct Peca peca);
struct Peca pop(struct Pilha *p);
void mostrarPilha(struct Pilha *p);

// Funções do Nível Mestre
void trocarFrenteTopo(struct Fila *f, struct Pilha *p);
void trocarTres(struct Fila *f, struct Pilha *p);

// Variável global estática para garantir IDs exclusivos
static int proximoId = 1;

// --- Função Principal (main) ---
int main() {
    srand(time(NULL));
    
    struct Fila filaDePecas;
    struct Pilha pilhaDeReserva;
    int opcao;

    // 1. Inicializar as estruturas
    inicializarFila(&filaDePecas);
    inicializarPilha(&pilhaDeReserva);

    // 2. Preencher a fila inicial com 5 peças
    printf("Gerando fila inicial de pecas...\n");
    for(int i = 0; i < TAM_FILA; i++) {
        enqueue(&filaDePecas, gerarPeca());
    }

    // 3. Laço Principal do Jogo (Menu)
    do {
        mostrarFila(&filaDePecas);
        mostrarPilha(&pilhaDeReserva);
        
        printf("\n--- TETRIS STACK (Mestre) ---\n");
        printf("1. Jogar peca (da fila)\n");
        printf("2. Reservar peca (fila -> pilha)\n");
        printf("3. Usar peca reservada (da pilha)\n");
        printf("4. Trocar [FRENTE] da Fila com [TOPO] da Pilha\n"); //
        printf("5. Trocar [3 PRIMEIROS] da Fila com [3] da Pilha\n"); //
        printf("0. Sair\n");
        printf("Escolha sua acao: ");
        
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1: // Jogar peça (dequeue)
                if (!filaVazia(&filaDePecas)) {
                    struct Peca pecaJogada = dequeue(&filaDePecas);
                    printf("\n>> Peca jogada: [%c %d]\n", pecaJogada.tipo, pecaJogada.id);

                    struct Peca novaPeca = gerarPeca();
                    enqueue(&filaDePecas, novaPeca);
                    printf(">> Nova peca [%c %d] entrou no final da fila.\n", novaPeca.tipo, novaPeca.id);
                } else {
                    printf("\nERRO: Fila de pecas esta vazia!\n");
                }
                pausar();
                break;
            
            case 2: // Reservar peça (fila -> pilha)
                if (pilhaCheia(&pilhaDeReserva)) {
                    printf("\nERRO: Pilha de reserva esta cheia! Nao pode reservar.\n");
                } else if (filaVazia(&filaDePecas)) {
                    printf("\nERRO: Fila de pecas esta vazia! Nao pode reservar.\n");
                } else {
                    struct Peca pecaReservada = dequeue(&filaDePecas);
                    push(&pilhaDeReserva, pecaReservada);
                    printf("\n>> Peca [%c %d] movida para a reserva.\n", pecaReservada.tipo, pecaReservada.id);
                    
                    struct Peca novaPeca = gerarPeca();
                    enqueue(&filaDePecas, novaPeca);
                    printf(">> Nova peca [%c %d] entrou no final da fila.\n", novaPeca.tipo, novaPeca.id);
                }
                pausar();
                break;

            case 3: // Usar peça reservada (pop)
                if (pilhaVazia(&pilhaDeReserva)) {
                    printf("\nERRO: Pilha de reserva esta vazia! Nao ha peca para usar.\n");
                } else {
                    struct Peca pecaUsada = pop(&pilhaDeReserva);
                    printf("\n>> Peca usada da reserva: [%c %d]\n", pecaUsada.tipo, pecaUsada.id);
                }
                pausar();
                break;

            case 4: // Trocar 1 (Frente da Fila com Topo da Pilha)
                trocarFrenteTopo(&filaDePecas, &pilhaDeReserva);
                pausar();
                break;

            case 5: // Trocar 3 (3 primeiros da Fila com 3 da Pilha)
                trocarTres(&filaDePecas, &pilhaDeReserva);
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

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

struct Peca gerarPeca() {
    struct Peca novaPeca;
    char tiposPossiveis[] = "IOTL"; 
    novaPeca.tipo = tiposPossiveis[rand() % 4]; 
    novaPeca.id = proximoId;
    proximoId++;
    return novaPeca;
}

// --- Funções da Fila ---

void inicializarFila(struct Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

bool filaVazia(struct Fila *f) {
    return (f->total == 0);
}

bool filaCheia(struct Fila *f) {
    return (f->total == TAM_FILA);
}

void enqueue(struct Fila *f, struct Peca peca) {
    if (filaCheia(f)) {
        printf("ERRO INTERNO: Tentativa de inserir em fila cheia!\n"); 
        return;
    }
    f->itens[f->fim] = peca;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->total++;
}

struct Peca dequeue(struct Fila *f) {
    struct Peca pecaVazia = {'?', -1};
    if (filaVazia(f)) {
        return pecaVazia;
    }
    struct Peca pecaRemovida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;
    return pecaRemovida;
}

void mostrarFila(struct Fila *f) {
    printf("\n-----------------------------------\n");
    printf("Fila de Pecas (Proxima -> ... -> Ultima):\n");
    if (filaVazia(f)) {
        printf("[VAZIA]");
    } else {
        int i = f->inicio;
        for (int count = 0; count < f->total; count++) {
            printf("[%c %d] ", f->itens[i].tipo, f->itens[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }
    printf("\n-----------------------------------\n");
}

// --- Funções da Pilha ---

void inicializarPilha(struct Pilha *p) {
    p->topo = -1;
}

bool pilhaVazia(struct Pilha *p) {
    return (p->topo == -1);
}

bool pilhaCheia(struct Pilha *p) {
    return (p->topo == TAM_PILHA - 1);
}

void push(struct Pilha *p, struct Peca peca) {
    if (pilhaCheia(p)) {
        printf("ERRO INTERNO: Tentativa de PUSH em pilha cheia!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = peca;
}

struct Peca pop(struct Pilha *p) {
    struct Peca pecaVazia = {'?', -1};
    if (pilhaVazia(p)) {
        return pecaVazia;
    }
    struct Peca pecaRemovida = p->itens[p->topo];
    p->topo--;
    return pecaRemovida;
}

void mostrarPilha(struct Pilha *p) {
    printf("Pilha de Reserva (Topo -> ... -> Base):\n");
    if (pilhaVazia(p)) {
        printf("[VAZIA]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
        }
    }
    printf("\n-----------------------------------\n");
}

// --- Funções do Nível Mestre ---

// 4 - Trocar a peça da frente da fila com o topo da pilha
void trocarFrenteTopo(struct Fila *f, struct Pilha *p) {
    // Validação: Verifica se ambas as estruturas têm peças
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("\nERRO: A Fila e a Pilha devem ter pelo menos 1 peca para trocar.\n");
        return;
    }

    // Troca direta nos arrays
    struct Peca temp = f->itens[f->inicio]; // Pega a peça da frente da fila
    f->itens[f->inicio] = p->itens[p->topo]; // Coloca a peça do topo da pilha na frente da fila
    p->itens[p->topo] = temp;                // Coloca a peça (original) da fila no topo da pilha

    printf("\n>> Troca realizada: Frente da Fila <-> Topo da Pilha.\n");
}

// 5 - Trocar os 3 primeiros da fila com os 3 da pilha
void trocarTres(struct Fila *f, struct Pilha *p) {
    // Validação: Pilha deve estar cheia (3 peças) e Fila deve ter pelo menos 3
    if (f->total < 3 || p->topo != (TAM_PILHA - 1)) {
        printf("\nERRO: A Pilha deve estar cheia (3 pecas) e a Fila deve ter pelo menos 3 pecas para esta troca.\n");
        return;
    }

    struct Peca temp;
    int idxFila;
    int idxPilha;

    // A troca será:
    // Fila[inicio] <-> Pilha[topo]
    // Fila[inicio+1] <-> Pilha[topo-1]
    // Fila[inicio+2] <-> Pilha[topo-2] (base da pilha)

    printf("\n>> Trocando 3 pecas...\n");

    for (int i = 0; i < 3; i++) {
        // Usa lógica circular para pegar o índice da fila
        idxFila = (f->inicio + i) % TAM_FILA; 
        // Usa lógica linear para pegar o índice da pilha (do topo para baixo)
        idxPilha = p->topo - i;

        // Realiza a troca
        temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[idxPilha];
        p->itens[idxPilha] = temp;
    }

    printf(">> Troca de 3 pecas concluida!\n");
}