#ifndef HEAP_SPACESHIP_H_INCLUDED
#define HEAP_SPACESHIP_H_INCLUDED
#define TAMANHO_TABELA 666

// Structs
typedef struct {
  int id, idade, doente, intruso, id_espaconave;
  char nome[100];
  char planeta_de_origem[100];
} Passageiro;

typedef struct {
  int num_recursos[5];
  char **str_recursos;
} Recursos;

typedef struct {
  int prioridade, id;
  int *tam;
  Recursos recursos;
  Passageiro *passageiros;
} Espaconave;

typedef struct {
  Espaconave *espaconaves;
  int tam;
  int capacidade;
} MaxHeap;

typedef struct No {
  Recursos recursos;
  struct No *prox;
} No;

typedef struct {
  No tab[TAMANHO_TABELA];
} TabelaHash;

// Funções básicas da Heap
MaxHeap cria_max_heap(Espaconave *espaconaves);
void constroi_heap_vetor(Espaconave *vetor, int tam);
void heapsort(MaxHeap heap);
void subir(Espaconave *espaconaves, int i);
void descer(Espaconave *espaconaves, int i, int tam);
MaxHeap inserir_na_heap(MaxHeap *heap);
Espaconave remover_na_heap(MaxHeap *heap, TabelaHash *tabela);

// Funções para leitura do CSV.
Passageiro *cria_passageiro(int id, char *nome, int idade,
                            char *planeta_de_origem, int doente, int intruso,
                            int id_espaconave);
Passageiro *le_passageiro(char *path);
Espaconave cria_espaconave(Passageiro *passageiros, int num);
Espaconave *cria_lista_espaconaves(Passageiro *passageiros);
int *atribuiRecursosInteiros(Espaconave espaconave);
int quadrado(int x);

// Gerenciamento de novas espaconaves
// char **cria_novos_recursos();
char **cria_novos_recursos(int *vetor);
Espaconave criar_nova_espaconave(MaxHeap heap);
Passageiro cria_novo_passageiro(int id_espaconave);

// Impressão de dados
void print_passageiros(Espaconave espaconave);
void print_espaconaves(MaxHeap heap);

// Outras
char ***gera_recursos();
int peso_recursos(Espaconave espaconave);
void recebe_prioridade(Espaconave *espaconaves);
MaxHeap prioridade_dez_por_cento(MaxHeap heap);
int descobrePosicaoPorId(Espaconave *espaconaves, int tam, int id);
int gera_aleatorios();

// Tabela hash
int vetorParaInteiro(int vetor[5]);
int *ordenarVetor(int vetor[3]);
int *vetorTruncado(int vetor[5]);
void buscaHeterogenea(TabelaHash tabela, Recursos recurso, int *a, int *end);
int buscaNaHash(TabelaHash *tabela, Recursos recurso);
int eIgual(int *vetor1, int *vetor2);
void inserirRecurso(TabelaHash *tabela, Recursos recurso, MaxHeap heap);
TabelaHash *inicializarTabela();
void expandirPassagem(MaxHeap *heap, TabelaHash *tabela);
void printarTabelaHash(TabelaHash *tabela);

#endif // HEAP_SPACESHIP_H_INCLUDED
