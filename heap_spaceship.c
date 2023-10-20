#include "heap_spaceship.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define tam_max 100

// Funções básicas da Heap
MaxHeap cria_max_heap(Espaconave *espaconaves) {
  MaxHeap heap;
  heap.espaconaves = (Espaconave *)malloc(10 * sizeof(Espaconave));
  heap.espaconaves = espaconaves;
  heap.tam = 10;
  heap.capacidade = tam_max;
  return heap;
}

void constroi_heap_vetor(Espaconave *vetor, int tam) {
  for (int i = (int)floor((tam) / 2) - 1; i >= 0; i--) {
    descer(vetor, i, tam);
  }
}

void heapsort(MaxHeap heap) {
  Espaconave aux;
  constroi_heap_vetor(heap.espaconaves, heap.tam);
  for (int i = heap.tam - 1; i > 0; i--) {
    aux = heap.espaconaves[0];
    heap.espaconaves[0] = heap.espaconaves[i];
    heap.espaconaves[i] = aux;
    descer(heap.espaconaves, 0, i);
  }
}

void subir(Espaconave *espaconaves, int i) {
  Espaconave aux;
  if (i <= 0)
    return;
  int j = (int)floor(i / 2);
  if (j >= 1) {
    if (espaconaves[i].prioridade > espaconaves[j].prioridade) {
      aux = espaconaves[j];
      espaconaves[j] = espaconaves[i];
      espaconaves[i] = aux;
      subir(espaconaves, j);
    }
  }
}

void descer(Espaconave *espaconaves, int i, int tam) {
  Espaconave aux;
  int j = 2 * i + 1;
  if (i < 0)
    return;
  if (j < tam) {
    if (j + 1 < tam) {
      if (espaconaves[j + 1].prioridade > espaconaves[j].prioridade) {
        j++;
      }
    }
    if (espaconaves[j].prioridade > espaconaves[i].prioridade) {
      aux = espaconaves[i];
      espaconaves[i] = espaconaves[j];
      espaconaves[j] = aux;
      descer(espaconaves, j, tam);
    }
  }
}

MaxHeap inserir_na_heap(MaxHeap *heap) {
  if (heap->tam >= heap->capacidade) {
    printf("Heap cheio.\n");
    return;
  }
  heap->espaconaves[heap->tam] = criar_nova_espaconave(*heap);
  return *heap;
}

Espaconave remover_na_heap(MaxHeap *heap, TabelaHash *tabela) {
  Espaconave *espaconaves = heap->espaconaves;
  Espaconave vazia = {0};
  if (heap->tam == 0) {
    return vazia;
  }

  Espaconave prioritaria = espaconaves[0];
  inserirRecurso(tabela, prioritaria.recursos, *heap);
  espaconaves[0] = espaconaves[heap->tam - 1];
  descer(espaconaves, 0, heap->tam - 1);
  heap->tam--;
  return prioritaria;
}

// Gerenciamento de novas espaçonaves
Espaconave criar_nova_espaconave(MaxHeap heap) {
  Espaconave nova;
  Passageiro *passageiros = (Passageiro *)malloc(15 * sizeof(Passageiro));
  int cont = 0;
  int res = 2;

  nova.id = heap.tam;
  printf("Lembre-se: Cada nave possui um limite máximo de 15 passageiros.\n");
  while (cont < 15) {
    passageiros[cont] = cria_novo_passageiro(nova.id);
    passageiros[cont].id = cont;
    printf("Deseja criar um novo passageiro para a nova nave? [1 para SIM][2 "
           "para NÃO]: ");
    scanf("%d", &res);
    while (res < 1 || res > 2) {
      printf("Opção inválida. Tente novamente: ");
      scanf("%d", &res);
    }
    cont++;
    if (res == 2) {
      break;
    }
  }
  nova.passageiros = passageiros;
  nova.tam = cont;
  printf("\nAgora, selecione os recursos que a nova espaconave irá levar: \n");
  nova.recursos.str_recursos = cria_novos_recursos(nova.recursos.num_recursos);
  nova.prioridade = gera_aleatorios() % 41;
  return nova;
}

Passageiro cria_novo_passageiro(int id_espaconave) {
  Passageiro novo_passageiro;
  printf("Digite o nome do novo passageiro: ");
  scanf("%s", novo_passageiro.nome);

  printf("Digite a idade do novo passageiro: ");
  scanf("%d", &novo_passageiro.idade);

  printf("Digite o nome do planeta de origem do novo passageiro: ");
  scanf("%s", novo_passageiro.planeta_de_origem);

  printf("O passageiro está saudável ou doente? (0 ou 1, respectivamente): ");
  scanf("%d", &novo_passageiro.doente);
  while (novo_passageiro.doente < 0 || novo_passageiro.doente > 1) {
    printf("Opção inválida. Tente novamente: ");
    scanf("%d", &novo_passageiro.doente);
  }

  printf("O passageiro é discreto ou intruso? (0 ou 1, respectivamente): ");
  scanf("%d", &novo_passageiro.intruso);
  while (novo_passageiro.intruso < 0 || novo_passageiro.intruso > 1) {
    printf("Opção inválida. Tente novamente: ");
    scanf("%d", &novo_passageiro.intruso);
  }

  novo_passageiro.id_espaconave = id_espaconave;
  return novo_passageiro;
}

char **cria_novos_recursos(int *vetor) {
  char **rec = (char **)malloc(5 * sizeof(char *));
  char *ref[] = {"Comida e água", "Remédios",   "Armas",
                 "Tecnologia",    "Construção", "Nada"};

  printf("As opções de recursos são: \n");
  printf("[1] - Comida e "
         "água\n[2] - Remédios\n[3] - Armas\n[4] - Tecnologia\n[5] - "
         "Construção\n[6] - Nada"
         "\n");
  int cont = 0;
  int res;
  while (cont < 5) {
    printf("Digite o número do %d recurso: ", cont + 1);
    scanf("%d", &res);
    while (res <= 0 || res > 6) {
      printf("Opção inválida. Tente novamente: ");
      scanf("%d", &res);
    }
    rec[cont] = ref[res - 1];
    vetor[cont] = res;
    cont++;
  }
  return rec;
}

// Outras
MaxHeap prioridade_dez_por_cento(MaxHeap heap) {
  int dez_por_cento = (int)floor(heap.tam * 0.1);
  if (heap.tam < 10) {
    dez_por_cento = 1;
  }
  int antiga_prioridade;
  for (int i = 0; i < dez_por_cento; i++) {
    int ind_modificado = gera_aleatorios() % heap.tam;
    antiga_prioridade = heap.espaconaves[ind_modificado].prioridade;
    int nova_prioridade = gera_aleatorios() % 41;
    heap.espaconaves[ind_modificado].prioridade = nova_prioridade;
    printf("A espaconave de id %d teve a sua prioridade modificada de %d para "
           "%d.\n",
           heap.espaconaves[ind_modificado].id, antiga_prioridade,
           nova_prioridade);
  }

  return heap;
}

void recebe_prioridade(Espaconave *espaconaves) {
  double cont_di = 0;
  double cont_recursos = 0;
  for (int j = 0; j < 10; j++) {
    cont_di = 0;
    for (int i = 0; i < 15; i++) {
      if (espaconaves[j].passageiros[i].doente == 1) {
        cont_di += 5;
      }
      if (espaconaves[j].passageiros[i].intruso == 1) {
        cont_di -= 3;
      }
    }
    if (cont_di < 0) {
      cont_di = 0;
    }
    cont_recursos = peso_recursos(espaconaves[j]);
    double prioridade = ((cont_di + cont_recursos));
    espaconaves[j].prioridade = (int)floor(prioridade);
  }
}

int peso_recursos(Espaconave espaconave) {
  int cont_recursos = 0;
  for (int i = 0; i < 5; i++) {
    if (strcmp(espaconave.recursos.str_recursos[i], "Tecnologia") == 1) {
      cont_recursos = cont_recursos + 2;
    }
    if (strcmp(espaconave.recursos.str_recursos[i], "Comida e água") == 1) {
      cont_recursos = cont_recursos + 5;
    }
    if (strcmp(espaconave.recursos.str_recursos[i], "Remédio") == 1) {
      cont_recursos = cont_recursos + 4;
    }
    if (strcmp(espaconave.recursos.str_recursos[i], "Construção") == 1) {
      cont_recursos = cont_recursos + 1;
    }
    if (strcmp(espaconave.recursos.str_recursos[i], "Armas") == 1) {
      cont_recursos = cont_recursos + 3;
    }
  }
  return cont_recursos;
}

int descobrePosicaoPorId(Espaconave *espaconaves, int tam, int id) {
  for (int i = 0; i < tam; i++) {
    if (espaconaves[i].id == id) {
      return i;
    }
  }
}

int gera_aleatorios() { return rand(); }

/*
  [1] - mostrar espaçonaves
  [2] - mostrar passageiros de uma determinada espaçonave
  [3] - mostrar recursos de uma determinada espaçonave
  [4] - mostrar naves em fila de prioridade para saida
  [5] - adicionar nova espaçonave (e passageiros e recursos ) ao sistema
  [6] - remover (ou "zapar") uma espaçonave
  [7] - fechar o sistema
*/

int menu() {

  Passageiro *passageiros;
  passageiros = le_passageiro("df_passageiros.csv");
  Espaconave *lista_espaconaves;
  Espaconave removida;
  lista_espaconaves = cria_lista_espaconaves(passageiros);
  MaxHeap heap_espaconaves = cria_max_heap(lista_espaconaves);
  TabelaHash *tabela = inicializarTabela();
  int opcao;
  int id;

  while (1) {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n[1] - Mostrar espaçonaves\n[2] - Mostrar passageiros de uma "
           "determinada espaçonave\n[3] - Mostrar naves em fila de prioridade "
           "para saida\n[4] - Adicionar nova espaçonave ao sistema\n[5] - "
           "Remover uma espaçonave\n[6] - Atualizar prioridades\n[7] - Mostrar "
           "Hash"
           "\n[8] - Fechar o sistema");
    printf("\nDigite sua opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      system("clear");
      print_espaconaves(heap_espaconaves);
      break;
    case 2:
      system("clear");
      puts("Digite o id da espaçonave desejada: ");
      scanf("%d", &id);
      int pos = descobrePosicaoPorId(heap_espaconaves.espaconaves,
                                     heap_espaconaves.tam, id);
      print_passageiros(heap_espaconaves.espaconaves[pos]);
      break;
    case 3:
      system("clear");
      constroi_heap_vetor(heap_espaconaves.espaconaves, heap_espaconaves.tam);
      print_espaconaves(heap_espaconaves);
      break;
    case 4:
      system("clear");
      heap_espaconaves = inserir_na_heap(&heap_espaconaves);
      heap_espaconaves.tam++;
      printf("\nA nave de id %d foi criada com sucesso.\n",
             heap_espaconaves.espaconaves[heap_espaconaves.tam - 1].id);
      subir(heap_espaconaves.espaconaves, heap_espaconaves.tam);
      break;
    case 5:
      system("clear");
      removida = remover_na_heap(&heap_espaconaves, tabela);

      break;
    case 6:
      system("clear");
      heap_espaconaves = prioridade_dez_por_cento(heap_espaconaves);
      break;
    case 7:
      printarTabelaHash(tabela);
      break;
    case 8:
      system("clear");
      printf("Fechando sistema");
      return 0;
    case 9:
      system("clear");
      expandirPassagem(&heap_espaconaves, tabela);
      break;
    default:
      printf("Opção inválida. Tente outra.");
      break;
    }
  }
}
