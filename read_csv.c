#include "heap_spaceship.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Mapeamento das naves iniciais do arquivo csv.
Cria um passageiro com base na struct Passageiro e retorna-o.
*/
Passageiro *cria_passageiro(int id, char *nome, int idade,
                            char *planeta_de_origem, int doente, int intruso,
                            int id_espaconave) {
  Passageiro *pass = malloc(sizeof(Passageiro));
  // pass->nome = malloc(sizeof(char) * (strlen(nome) + 1));
  // pass->planeta_de_origem = malloc(sizeof(char) * (strlen(planeta_de_origem)
  // + 1));

  pass->id = id;
  strcpy(pass->nome, nome);
  pass->idade = idade;
  strcpy(pass->planeta_de_origem, planeta_de_origem);
  pass->doente = doente;
  pass->intruso = intruso;
  pass->id_espaconave = id_espaconave;

  return pass;
}

/*
Lê o arquivo csv com os dados dos passageiros e retorna um vetor com os mesmos.
*/

Passageiro *le_passageiro(char *path) {
  FILE *file = fopen(path, "r");
  char buffer[1024];
  int i = 0;
  Passageiro *vet = malloc(151 * sizeof(Passageiro));

  fgets(buffer, sizeof(buffer), file);

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    char *id_str, *nome, *idade_str, *planeta_de_origem, *doente_str,
        *intruso_str, *id_espaconave_str;

    id_str = strtok(buffer, ",");
    nome = strtok(NULL, ",");
    idade_str = strtok(NULL, ",");
    planeta_de_origem = strtok(NULL, ",");
    doente_str = strtok(NULL, ",");
    intruso_str = strtok(NULL, ",");
    id_espaconave_str = strtok(NULL, ",");

    int id = atoi(id_str);
    int idade = atoi(idade_str);
    int doente = atoi(doente_str);
    int intruso = atoi(intruso_str);
    int id_espaconave = atoi(id_espaconave_str);

    Passageiro *pass = cria_passageiro(id, nome, idade, planeta_de_origem,
                                       doente, intruso, id_espaconave);
    vet[i] = *pass;
    free(pass);
    i++;
  }
  fclose(file);
  return vet;
}

/*
Construção do heap inicial. Cria espaçonave com base na struct Espaconave.
*/
Espaconave cria_espaconave(Passageiro *passageiros, int id) {

  Espaconave apollo;
  Passageiro *vet1 = malloc(151 * sizeof(Passageiro));
  int aux = 0;

  srand((unsigned int)time(NULL));

  for (int i = 0; i < 150; i++) {
    if (passageiros[i].id_espaconave == id) {
      vet1[aux] = passageiros[i];
      aux++;
    }
  }

  apollo.id = id;
  apollo.tam = aux;
  apollo.passageiros = malloc(aux * sizeof(Passageiro));
  memcpy(apollo.passageiros, vet1, aux * sizeof(Passageiro));
  return apollo;
}
/*
Cria a lista de espaçonaves com base na lista de passageiros. Retorna a lista de
espaçonaves com cada espçonave com seu devido atributo.
*/
/*
Espaconave *cria_lista_espaconaves(Passageiro *passageiros) {
  Espaconave *lista_espaconaves = malloc(10 * sizeof(Espaconave));
  srand((unsigned int)time(NULL));
  for (int i = 0; i < 10; i++) {
    lista_espaconaves[i] = cria_espaconave(passageiros, i);
  }

  char ***rec = gera_recursos();
  for (int k = 0; k < 10; k++) {
    lista_espaconaves[k].recursos = rec[k];
  }
  recebe_prioridade(lista_espaconaves);
  return lista_espaconaves;
}
*/
Espaconave *cria_lista_espaconaves(Passageiro *passageiros) {
  Espaconave *lista_espaconaves = malloc(10 * sizeof(Espaconave));
  srand((unsigned int)time(NULL));
  for (int i = 0; i < 10; i++) {
    lista_espaconaves[i] = cria_espaconave(passageiros, i);
  }

  char ***rec = gera_recursos();
  for (int k = 0; k < 10; k++) {
    lista_espaconaves[k].recursos.str_recursos = rec[k];
    int *vetor_inteiro = atribuiRecursosInteiros(lista_espaconaves[k]);
    for (int i = 0; i < 5; i++) {
      lista_espaconaves[k].recursos.num_recursos[i] = vetor_inteiro[i];
    }
  }
  recebe_prioridade(lista_espaconaves);
  return lista_espaconaves;
}

int *atribuiRecursosInteiros(Espaconave espaconave) {
  int *vetor = (int *)malloc(5 * sizeof(int));
  for (int i = 0; i < 5; i++) {
    if (strcmp(espaconave.recursos.str_recursos[i], "Tecnologia") == 0) {
      vetor[i] = 4;
    } else if (strcmp(espaconave.recursos.str_recursos[i], "Comida e água") ==
               0) {
      vetor[i] = 1;
    } else if (strcmp(espaconave.recursos.str_recursos[i], "Remédios") == 0) {
      vetor[i] = 2;
    } else if (strcmp(espaconave.recursos.str_recursos[i], "Construção") == 0) {
      vetor[i] = 5;
    } else if (strcmp(espaconave.recursos.str_recursos[i], "Armas") == 0) {
      vetor[i] = 3;
    } else if (strcmp(espaconave.recursos.str_recursos[i], "Nada") == 0) {
      vetor[i] = 0;
    }
  }
  return vetor;
}
/*
Imprime os passageiros de uma determinada espaçonave.
*/
void print_passageiros(Espaconave espaconave) {
  printf("Passageiros da Nave %d:\n", espaconave.id);
  for (int i = 0; i < espaconave.tam; i++) {

    puts("---------------------------------------");
    printf("id: %d\n", espaconave.passageiros[i].id);
    printf("nome: %s\n", espaconave.passageiros[i].nome);
    printf("idade: %d\n", espaconave.passageiros[i].idade);
    printf("planeta_de_origem: %s\n",
           espaconave.passageiros[i].planeta_de_origem);
    printf("doente: %d\n", espaconave.passageiros[i].doente);
    printf("intruso: %d\n", espaconave.passageiros[i].intruso);
    printf("id da espaçonave: %d\n", espaconave.passageiros[i].id_espaconave);
  }
}
/*
Gera recursos de espaçonaves aleatoriamente. Retorna um vetor com esses
recursos.
*/
char ***gera_recursos() {
  char *rec[] = {"Remédios", "Comida e água", "Tecnologia",
                 "Armas",    "Construção",    "Nada"};

  srand(time(NULL)); // Inicializa o gerador de números aleatórios

  char ***vetores = (char ***)malloc(10 * sizeof(char **));
  for (int i = 0; i < 10; i++) {
    vetores[i] = (char **)malloc(5 * sizeof(char *));
    for (int j = 0; j < 5; j++) {
      vetores[i][j] = strdup(rec[rand() % 6]);
    }
  }

  return vetores;
}

/*
Imprime a lista de espaçonves com seus atributos.
*/

/*
void print_espaconaves(MaxHeap heap) {
  printf("Espaçonaves:\n");

  for (int i = 0; i < heap.tam; i++) {
    puts("-------------------------------");
    printf("id: %d\n", heap.espaconaves[i].id);
    printf("prioridade: %d\n", heap.espaconaves[i].prioridade);
    puts("---Recursos--- ");
    for (int j = 0; j < 5; j++) {
      printf("recurso %d: %s\n", j + 1, heap.espaconaves[i].recursos[j]);
    }
  }
}
*/
void print_espaconaves(MaxHeap heap) {
  printf("Espaçonaves:\n");

  for (int i = 0; i < heap.tam; i++) {
    puts("-------------------------------");
    printf("id: %d\n", heap.espaconaves[i].id);
    printf("prioridade: %d\n", heap.espaconaves[i].prioridade);
    puts("---Recursos--- ");
    for (int j = 0; j < 5; j++) {
      printf("recurso %d: %s\n", j + 1,
             heap.espaconaves[i].recursos.str_recursos[j]);
    }
  }
}

int quadrado(x) { return x * x; }
