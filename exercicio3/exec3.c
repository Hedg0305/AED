#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu();
void *addPerson(void *pBuffer);
void list(void *pBuffer);
void search(void *pBuffer);

int main() {
  void *pBuffer = malloc(sizeof(int));
  int option;

  if (pBuffer == NULL) {
    printf("Erro de memória!");
    exit(1);
  }

  *(int *)pBuffer = 0;

  while (1) {
    option = menu();

    switch (option) {
      case 1:
        pBuffer = addPerson(pBuffer);
        break;
      case 2:
        break;
      case 3:
        search(pBuffer);
        break;
      case 4:
        list(pBuffer);
        exit(0);
        break;
      default:
        printf("Opção inválida!!\n");
    }
  }
}

int menu() {
  int option = 0;

  printf("_____________________");
  printf("\n|Escolha uma opção: |");
  printf("\n|1- Inserir um nome |");
  printf("\n|2- Excluir um nome |");
  printf("\n|3- Buscar nome:    |");
  printf("\n|4- Listar          |");
  printf("\n|5- Sair:           |");
  printf("\n---------------------");
  printf("\n|Opcao: ");
  scanf("%d", &option);

  return option;
}

void *addPerson(void *pBuffer) {
  //Alloca o primeiro usuário
  pBuffer = (void *)realloc(pBuffer, sizeof(int) * 1 + (sizeof(char) * 10 + sizeof(int) * 2) * (*((int *)(pBuffer)) + 1));
  printf("Digite os dados do usuário que deseja adicionar:");
  printf("\nNome: ");
  scanf("%s", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * (*((int *)(pBuffer)))));
  setbuf(stdin, NULL);
  printf("Idade: ");
  scanf("%d", (int *)(pBuffer + sizeof(int) * 1 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * (*((int *)(pBuffer)))));
  setbuf(stdin, NULL);
  printf("Telefone: ");
  scanf("%d", (int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * (*((int *)(pBuffer)))));
  setbuf(stdin, NULL);

  *(int *)(pBuffer) += 1;
  return pBuffer;
}

void list(void *pBuffer) {
  if (*(int *)(pBuffer) == 0) {
    printf("    AGENDA VAZIA\n");
  } else {
    printf("    AGENDA\n");
    for (int personCounter = 0; personCounter < *(int *)(pBuffer); personCounter++) {
      printf("Nome: %s |  ", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter));
      printf("Idade: %d | ", *(int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter));
      printf("Telefone: %d \n", *(int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter));
    }
  }
}

void search(void *pBuffer) {
  char name[10];
  printf("Digite o nome do usuário que deseja buscar: ");
  scanf("%s", name);

  int hasPerson;
  hasPerson = 0;

  for (int personCounter = 0; personCounter < *(int *)(pBuffer); personCounter++) {
    if (strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter), name) == 0) {
      printf("Nome: %s |  ", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter));
      printf("Idade: %d | ", *(int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter));
      printf("Telefone: %d \n", *(int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * personCounter));
      hasPerson = 1;
    }
  }

  if (hasPerson != 1) {
    printf("Usuário não encontrado!\n");
  }
}