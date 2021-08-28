#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu();
char* insertName(char* list);
char* removeName(char* list);
void listName(char* list);

int main() {
  int option;
  char* list = NULL;
  list = malloc(1 * sizeof(char));
  list[0] = '\0';

  while (1) {
    option = menu();

    switch (option) {
      case 1:
        list = insertName(list);
        break;
      case 2:
        list = removeName(list);
        break;
      case 3:
        listName(list);
        break;
      case 4:
        free(list);
        exit(0);
        break;
    }
  }

  return 0;
}

int menu() {
  int option = 0;
  while (option < 1 || option > 4) {
    printf("\n____________________");
    printf("\n|Escolha uma opção: |");
    printf("\n|1- Inserir um nome |");
    printf("\n|2- Excluir um nome |");
    printf("\n|3- Listar nomes:   |");
    printf("\n|4- Sair:           |\n");
    printf("---------------------");
    printf("\n|Opcao: ");
    scanf("%d", &option);
  }
  return option;
}

char* insertName(char* list) {
  char newName[20];
  int listSize;
  listSize = strlen(list);

  printf("Digite um nome com no máximo 20 caracteres: ");
  scanf("%s", newName);

  if (listSize == 0) {
    list = realloc(list, (strlen(newName) + 1) * sizeof(char));
    strcat(list, newName);
  } else {
    list = realloc(list, (strlen(list) + 2 + strlen(newName)) * sizeof(char));
    strcat(list, ",");
    strcat(list, newName);
  }
  printf("List size: %lu", strlen(list));

  strcat(list, "\0");
  printf("\nList: %s\n", list);

  return list;
}

void listName(char* list) {
  if (strlen(list) > 0) {
    printf("\nList names: %s", list);
  } else {
    printf("\nA lista encontra-se vazia");
  }
}

char* removeName(char* list) {
  char nameToBeRemoved[20];
  int removeStart, newListSize;

  printf("\nInforme o nome a ser deletado (máx 20 caracteres): ");
  scanf("%s", nameToBeRemoved);

  char* nameToBeRemovedIndex = strstr(list, nameToBeRemoved);

  if (nameToBeRemovedIndex != NULL) {
    removeStart = strlen(list) - strlen(nameToBeRemovedIndex);
    char* isLastName = strstr(nameToBeRemovedIndex, ",");

    if (isLastName != NULL) {
      list = realloc(list, (removeStart) * sizeof(char));
      list[removeStart - 1] = '\0';
      newListSize = strlen(list) + strlen(isLastName);
      printf("\n%d", newListSize);
      list = realloc(list, (newListSize) * sizeof(char));
      strcat(list, isLastName);
      strcat(list, "\0");

    } else {
      newListSize = strlen(list) - strlen(nameToBeRemovedIndex);
      list = realloc(list, (newListSize) * sizeof(char));
      list[newListSize - 1] = '\0';
    }
  } else {
    printf("\n***********************");
    printf("\n* Nome não encontrado *");
    printf("\n***********************");
  }

  return list;
}
