#include "heap_spaceship.h"
#include <stdio.h>
#include <stdlib.h>

int *vetorTruncado(int vetor[5]) {
  int *vetor_trucado = (int *)malloc(3 * sizeof(int));
  for (int i = 0; i < 3; i++) {
    vetor_trucado[i] = vetor[i];
  }
  return vetor_trucado;
}

int vetorParaInteiro(int *vetor) {
  int resultado = 0;
  int potencia = 1;

  for (int i = 2; i >= 0; i--) {
    resultado += vetor[i] * potencia;
    potencia *= 10;
  }
  return resultado;
}

int *ordenarVetor(int *vetor) {
  int *copia = (int *)malloc(3 * sizeof(int));
  for (int k = 0; k < 3; k++) {
    copia[k] = vetor[k];
  }
  for (int i = 0; i < 2; i++) {
    int indice_menor = i;
    for (int j = i + 1; j < 3; j++) {
      if (copia[j] < copia[indice_menor]) {
        indice_menor = j;
      }
    }
    if (indice_menor != i) {
      int temp = copia[i];
      copia[i] = copia[indice_menor];
      copia[indice_menor] = temp;
    }
  }
  return copia;
}

int funcaoHash(int vetor[5]) {
  int *vetor_truncado = vetorTruncado(vetor);
  int *vetor_ordenado = ordenarVetor(vetor_truncado);
  int pos = vetorParaInteiro(vetor_ordenado);
  return pos;
}

int eIgual(int *vetor1, int *vetor2) {
  int cont = 0;
  for (int i = 0; i < 3; i++) {
    if (vetor1[i] == vetor2[i]) {
      cont++;
    }
  }
  if (cont == 3) {
    return 1;
  }
  return 0;
}

int buscaNaHash(TabelaHash *tabela, Recursos recurso) {
  int *vetor_truncado = vetorTruncado(recurso.num_recursos);
  int hx = funcaoHash(recurso.num_recursos);
  No *atual = (No *)malloc(sizeof(No));
  if (tabela->tab[hx].recursos.num_recursos[0] == 999 &&
      tabela->tab[hx].recursos.num_recursos[1] == 999 &&
      tabela->tab[hx].recursos.num_recursos[2] == 999) {
    return 0;
  } else {
    if (eIgual(vetor_truncado, tabela->tab[hx].recursos.num_recursos) == 1) {
      free(vetor_truncado);
      return 1;
    } else {
      atual = tabela->tab[hx].prox;
      while (atual != NULL) {
        if (eIgual(vetor_truncado, atual->recursos.num_recursos) == 1) {
          free(vetor_truncado);
          return 1;
        }
        atual = atual->prox;
      }
      free(vetor_truncado);
      return -1;
    }
  }
  free(vetor_truncado);
}

void inserirRecurso(TabelaHash *tabela, Recursos recurso, MaxHeap heap) {
  int hx = funcaoHash(recurso.num_recursos);
  int busca = buscaNaHash(tabela, recurso);
  No *atual = (No *)malloc(sizeof(No));
  No *novoNo = (No *)malloc(sizeof(No));
  novoNo->recursos = recurso;
  novoNo->prox = NULL;

  if (busca == 1) {
    printf("O elemento já está na tabela.");
  } else {
    if (busca == 0) {
      tabela->tab[hx] = *novoNo;
    } else {
      int cont = 1;
      atual = &tabela->tab[hx];
      while (atual->prox != NULL) {
        atual = atual->prox;
        cont++;
      }
      if (cont <= 5) {
        atual->prox = novoNo;
        if (cont == 5) {
          printf("Foram atingidas todas as possíveis permutações dos "
                 "seguintes recursos:\nA passagem aumentou de tamanho.\n");
          expandirPassagem(&heap,tabela);
        }
      } else {
        printf("Foram atingidas todas as possíveis permutações desses dos "
               "seguintes recursos: \nA passagem aumentou de tamanho.");
        free(novoNo);
      }
    }
  }
}

TabelaHash *inicializarTabela() {
  TabelaHash *tabela = (TabelaHash *)malloc(sizeof(TabelaHash));
  for (int i = 0; i < TAMANHO_TABELA; i++) {
    tabela->tab[i].recursos.num_recursos[0] = 999;
    tabela->tab[i].recursos.num_recursos[1] = 999;
    tabela->tab[i].recursos.num_recursos[2] = 999;
    tabela->tab[i].prox = NULL;
  }
  return tabela;
}

void expandirPassagem(MaxHeap *heap,TabelaHash *tabela){
  for(int i = 0; i < 6; i++){
    Espaconave espaconave_removida = remover_na_heap(heap, tabela);
  }
}

void printarTabelaHash(TabelaHash *tabela){
  puts("Posições oculpadas:\n");
  for(int i = 0; i < TAMANHO_TABELA; i++){
    if(tabela->tab[i].recursos.num_recursos[0] != NULL && tabela->tab[i].recursos.num_recursos[0] != 999){
      printf("\nNó %d",i);
      
      No *novoNo = (No *)malloc(sizeof(No));
      novoNo = tabela->tab[i].prox;
      while(novoNo != NULL){
        printf("+");
        novoNo = novoNo->prox;
      }
    }
  }
}
