#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTION 0
#define FOR_COUNTER (sizeof(int))
#define PERSON_COUNTER (sizeof(int) * 2)
#define AUX (sizeof(int) * 3)
#define NAME (sizeof(int) * 4)

void menu(void *pBuffer);
void addPerson(void *pBuffer);
void removePerson(void *pBuffer);
void list(void *pBuffer);
void search(void *pBuffer);

typedef struct {
  char nome[10];
  int idade;
  int altura;
} Pessoa;

Pessoa pessoa[10];

int main() {
  void *pBuffer = malloc((sizeof(int) * 4) + (sizeof(char) * 11));
  //positions: OPTION - FOR_COUNTER - PERSON_COUNTER - AUX - name
  *(int *)(pBuffer + PERSON_COUNTER) = 0;

  while (1) {
    menu(pBuffer);

    switch (*(int *)pBuffer) {
      case 1:
        addPerson(pBuffer);
        break;
      case 2:
        removePerson(pBuffer);
        break;
      case 3:
        search(pBuffer);
        break;
      case 4:
        list(pBuffer);
        break;
      case 5:
        free(pBuffer);
        exit(0);
        break;
      default:
        printf("Opção inválida!!\n");
    }
  }

  return 0;
}

void menu(void *pBuffer) {
  printf("_____________________");
  printf("\n|Escolha uma opção: |");
  printf("\n|1- Inserir um nome |");
  printf("\n|2- Excluir um nome |");
  printf("\n|3- Buscar nome:    |");
  printf("\n|4- Listar          |");
  printf("\n|5- Sair:           |");
  printf("\n---------------------");
  printf("\n|Opcao: ");
  scanf("%d", &*(int *)(pBuffer + OPTION));
}

void addPerson(void *pBuffer) {
  int *counter = &*(int *)(pBuffer + PERSON_COUNTER);

  if (*counter == 10) {
    printf("Lista cheia\n");
  } else {
    printf("Nome: ");
    scanf("%s", pessoa[*counter].nome);
    printf("Idade: ");
    scanf("%d", &pessoa[*counter].idade);
    printf("Altura: ");
    scanf("%d", &pessoa[*counter].altura);
    printf("\nNome adicionado com SUCESSO!!\n");
    *counter += 1;
  }
}

void search(void *pBuffer) {
  int *counter = &*(int *)(pBuffer + FOR_COUNTER);
  int *personCounter = &*(int *)(pBuffer + PERSON_COUNTER);
  int *flag = &*(int *)(pBuffer + AUX);
  char *name = &*(char *)(pBuffer + NAME);

  *flag = 0;

  if (*personCounter == 0) {
    printf("\nLista vazia, nada para procuar aqui\n");
  } else {
    printf("\nInsira o nome a ser procurado: ");
    scanf("%s", name);

    for (*counter = 0; *counter < *personCounter; *counter += 1) {
      if (strcmp(name, pessoa[*counter].nome) == 0) {
        printf("\n\nNome encontrado:");
        printf("\nNome: %s", pessoa[*counter].nome);
        printf("\nIdade: %d", pessoa[*counter].idade);
        printf("\nAltura: %d\n", pessoa[*counter].altura);
        *flag = 1;
      }
    }
    if (*flag == 0) {
      printf("\nNome não listado\n");
    }
  }
}

void removePerson(void *pBuffer) {
  int *counter = &*(int *)(pBuffer + FOR_COUNTER);
  int *personCounter = &*(int *)(pBuffer + PERSON_COUNTER);
  int *flag = &*(int *)(pBuffer + AUX);
  char *name = &*(char *)(pBuffer + NAME);

  *flag = 0;

  if (*personCounter == 0) {
    printf("\nLista vazia, nada para remover!\n");
  } else {
    printf("\nInsira o nome a ser removido: ");
    scanf("%s", name);

    for (*counter = 0; *counter < *personCounter; *counter += 1) {
      if (strcmp(name, pessoa[*counter].nome) == 0) {
        *flag = 1;
      }
      if (*flag == 1) {
        strcpy(pessoa[*counter].nome, pessoa[*counter + 1].nome);
        pessoa[*counter].idade = pessoa[*counter + 1].idade;
        pessoa[*counter].altura = pessoa[*counter + 1].altura;
      }
    }

    if (*flag == 1) {
      *personCounter -= 1;
    }

    if (*flag == 0) {
      printf("\nNome não listado!!\n");
    }
  }
}

void list(void *pBuffer) {
  int *counter = &*(int *)(pBuffer + FOR_COUNTER);
  int *personCounter = &*(int *)(pBuffer + PERSON_COUNTER);

  if (*personCounter == 0) {
    printf("\nLista está vazia");
  } else
    for (*counter = 0; *counter < *personCounter; *counter += 1) {
      printf("\nNome: %s", pessoa[*counter].nome);
      printf("\nIdade: %d", pessoa[*counter].idade);
      printf("\nAltura: %d", pessoa[*counter].altura);
      printf("\n--------------");
    }
  printf("\n");
}