#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  
#define TIPOS_PECAS 4 

// Estrutura da peça
typedef struct {
    char tipo;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];  
    int inicio;       
    int fim;         
    int total;        
    int proximo_id;   
} Fila;

// Inicializar fila 
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    f->proximo_id = 0;
}

// Verificar se a lista está vazia
int filaVazia(Fila *f) {
    
    return f->total == 0;
}

// Verificar se a lista está cheia
int filaCheia(Fila *f) {
   
    return f->total == MAX;
}

//Gera uma nova peça com tipo aleatório e ID único
Peca gerarPeca(Fila *f) {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    //Seleciona tipo aleatório
    nova_peca.tipo = tipos[rand() % TIPOS_PECAS];
    nova_peca.id = f->proximo_id++;
    
    return nova_peca;
}

//Insere uma peça no final da fila (enqueue)
void inserirPeca(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Erro: Tentativa de inserir em fila cheia\n");
        
        return;
    }
    
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;  // Atualização circular
    f->total++;
}

//Remove uma peça do início da fila (dequeue)
Peca removerPeca(Fila *f) {
    Peca peca_vazia = {' ', -1};
    
    if (filaVazia(f)) {
        printf("Erro: Tentativa de remover de fila vazia\n");
        
        return peca_vazia;
    }
    
    Peca peca_removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    
    return peca_removida;
}

//Exibe estado atual da fila de peças
void exibirFila(Fila *f) {
    printf("\n=== FILA DE PEÇAS (%d/5) ===\n", f->total);
    
    if (filaVazia(f)) {
        printf("Fila vazia\n");
        
        return;
    }
    
    printf("Peças: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n");
}

//Exibe menu de opções
void exibirMenu() {
    printf("\n--- MENU DE AÇÕES ---\n");
    printf("1 - Jogar peça (remover da frente)\n");
    printf("2 - Inserir nova peça (adicionar no final)\n");
    printf("0 - Sair do jogo\n");
    printf("Escolha uma opção: ");
}

//Preenche a fila com 5 peças iniciais
void preencherFilaInicial(Fila *f) {
    while (!filaCheia(f)) {
        Peca nova_peca = gerarPeca(f);
        inserirPeca(f, nova_peca);
    }
}

//Função principal
int main() {
    Fila fila_pecas;
    int opcao;
    
    //Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    //Inicializa e preenche a fila
    inicializarFila(&fila_pecas);
    preencherFilaInicial(&fila_pecas);
    
    printf("=== SISTEMA DE FILA DE PEÇAS ===\n");
    printf("Fila circular inicializada com 5 peças.\n");
    
    //Loop principal do programa
    do {
        exibirFila(&fila_pecas);
        exibirMenu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: //Jogar peça (dequeue)
                if (!filaVazia(&fila_pecas)) {
                    Peca peca_removida = removerPeca(&fila_pecas);
                    printf(">>> Peça jogada: [%c %d]\n", peca_removida.tipo, peca_removida.id);

                } else {
                    printf(">>> Erro: Não há peças para jogar\n");
                }
                
                break;
                
            case 2: //Inserir nova peça (enqueue)
                if (!filaCheia(&fila_pecas)) {
                    Peca nova_peca = gerarPeca(&fila_pecas);
                    inserirPeca(&fila_pecas, nova_peca);
                    printf(">>> Nova peça inserida: [%c %d]\n", nova_peca.tipo, nova_peca.id);
                
                } else {
                    printf(">>> A fila já está cheia (5 peças)\n");
                }
                
                break;
                
            case 0: //Sair
                printf(">>> Encerrando o jogo...\n");
                
                break;
                
            default:
                printf(">>> Opção inválida! Use 0, 1 ou 2.\n");
                
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}