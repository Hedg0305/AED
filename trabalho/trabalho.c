#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addPerson(void *pBuffer);
void menu(void *pBuffer);
void list(void *pBuffer);
void search(void *pBuffer);

#define OPTION 0
#define COUNTER (sizeof(int))
#define FIRST_PERSON (sizeof(int) * 2)
#define LAST_PERSON (sizeof(int) * 2 + sizeof(void *))
#define SEARCH_NAME (sizeof(int) * 2 + sizeof(void *) * 2)

#define NAME 0
#define AGE (sizeof(char) * 10)
#define TELEPHONE (sizeof(char) * 10 + sizeof(int))
#define PREVIOUS_PERSON (sizeof(char) * 10 + sizeof(int) * 2)
#define NEXT_PERSON (sizeof(char) * 10 + sizeof(int) * 2 + sizeof(void *))

int main() {
  void *pBuffer = (void *)malloc((sizeof(int) * 2) + sizeof(void *) * 2 + (sizeof(char) * 11));
  //Ordem: Contador - FP - LP
  *(int *)(pBuffer + COUNTER) = 0;
  while (1) {
    menu(pBuffer);

    switch (*(int *)pBuffer) {
      case 1:
        addPerson(pBuffer);
        break;
      case 2:
        // removePerson(pBuffer);
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
  setbuf(stdin, NULL);
}

void addPerson(void *pBuffer) {
  int *counter = &*(int *)(pBuffer + COUNTER);

  void *person = malloc(sizeof(char) * 10 + sizeof(int) * 2 + sizeof(void *) * 2);

  printf("Insira um nome: ");
  scanf("%s", (char *)((person + NAME)));
  printf("Insira a idade: ");
  scanf("%d", (int *)(person + AGE));
  printf("Insira um telefone: ");
  scanf("%d", (int *)(person + TELEPHONE));
  *(void **)(person + NEXT_PERSON) == NULL;

  if (*counter == 0) {
    *(void **)(pBuffer + FIRST_PERSON) = person;
    *(void **)(pBuffer + LAST_PERSON) = person;
    *counter += 1;
  } else {
    void *currentLastPerson = *(void **)(pBuffer + LAST_PERSON);
    *(void **)(currentLastPerson + NEXT_PERSON) = person;
    *(void **)(pBuffer + LAST_PERSON) = person;
    *counter += 1;
  }
}

void list(void *pBuffer) {
  void *person = *(void **)(pBuffer + FIRST_PERSON);

  while (person != NULL) {
    printf("\nNome : %s", (char *)(person + NAME));
    printf("\nIdade : %d", *(int *)(person + AGE));
    printf("\nTelefone : %d", *(int *)(person + TELEPHONE));
    person = *(void **)(person + NEXT_PERSON);
  }
}

void search(void *pBuffer) {
  char *person = &*(char *)(pBuffer + SEARCH_NAME);
  void *auxPerson = *(void **)(pBuffer + FIRST_PERSON);

  printf("Name to be searched :");
  scanf("%s", person);
  printf("Name to be searched %s:", (char *)(auxPerson + NAME));

  while (auxPerson != NULL) {
    if (strcmp(person, (char *)(auxPerson + NAME)) == 0) {
      printf("\nNome : %s", (char *)(auxPerson + NAME));
      printf("\nIdade : %d", *(int *)(auxPerson + AGE));
      printf("\nTelefone : %d", *(int *)(auxPerson + TELEPHONE));
    }
    auxPerson = *(void **)(auxPerson + NEXT_PERSON);
  }
}