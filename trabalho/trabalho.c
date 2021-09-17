#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addPerson(void *pBuffer);
void menu(void *pBuffer);
void list(void *pBuffer);
void search(void *pBuffer);
void sort(void *pBuffer, void *person);
void POP(void *pBuffer);
void RESET(void *pBuffer);

#define OPTION 0
#define FIRST_PERSON (sizeof(int))
#define LAST_PERSON (sizeof(int) + sizeof(void **))
#define SEARCH_NAME (sizeof(int) + sizeof(void *) * 2)

#define NAME 0
#define AGE (sizeof(char) * 11)
#define TELEPHONE (sizeof(char) * 11 + sizeof(int))
#define PREVIOUS_PERSON (sizeof(char) * 11 + sizeof(int) * 2)
#define NEXT_PERSON (sizeof(char) * 11 + sizeof(int) * 2 + sizeof(void *))

int main() {
  void *pBuffer = (void *)malloc(sizeof(int) + sizeof(void *) * 2 + (sizeof(char) * 11));

  memset(pBuffer, 0, (sizeof(int) + (sizeof(void *) * 2) + (sizeof(char) * 11)));
  //Ordem: Contador - FP - LP
  *(void **)(pBuffer + FIRST_PERSON) == NULL;
  *(void **)(pBuffer + LAST_PERSON) == NULL;

  while (1) {
    setbuf(stdin, NULL);
    menu(pBuffer);

    switch (*(int *)(pBuffer + OPTION)) {
      case 1:
        addPerson(pBuffer);
        break;
      case 2:
        POP(pBuffer);
        break;
      case 3:
        search(pBuffer);
        break;
      case 4:
        list(pBuffer);
        break;
      case 5:
        RESET(pBuffer);
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
  printf("\n|2- Andar fila      |");
  printf("\n|3- Buscar nome:    |");
  printf("\n|4- Listar          |");
  printf("\n|5- Sair:           |");
  printf("\n---------------------");
  printf("\n|Opcao: ");
  scanf("%d", &*(int *)(pBuffer + OPTION));
  setbuf(stdin, NULL);
}

void addPerson(void *pBuffer) {
  void *person = (void *)malloc(sizeof(char) * 11 + sizeof(int) * 2 + sizeof(void *) * 2);

  memset(person, 0, (sizeof(char) * 11 + sizeof(int) * 2 + sizeof(void *) * 2));

  printf("Insira um nome: ");
  scanf("%s", (char *)((person + NAME)));
  setbuf(stdin, NULL);

  while (strlen((char *)((person + NAME))) > 10) {
    printf("*********************************************** \n");
    printf("* Insira um nome com no máximo 10 caracteres! *\n");
    printf("*********************************************** \n");
    printf("Insira um nome: ");
    scanf("%s", (char *)((person + NAME)));
    setbuf(stdin, NULL);
  }

  printf("Insira a idade: ");
  scanf("%d", (int *)(person + AGE));
  setbuf(stdin, NULL);

  printf("Insira um telefone: ");
  scanf("%d", (int *)(person + TELEPHONE));
  setbuf(stdin, NULL);

  *(void **)(person + NEXT_PERSON) == NULL;
  *(void **)(person + PREVIOUS_PERSON) == NULL;

  if (*(void **)(pBuffer + FIRST_PERSON) == NULL) {
    *(void **)(pBuffer + FIRST_PERSON) = person;
    *(void **)(pBuffer + LAST_PERSON) = person;
  } else {
    sort(person, pBuffer);
  }
  return;
}

void POP(void *pBuffer) {
  void *person = *(void **)(pBuffer + FIRST_PERSON);
  if (person == NULL) {
    printf("A fila encontra-se vazia\n");
    return;
  }

  if (*(void **)(person + NEXT_PERSON) != NULL) {
    *(void **)(pBuffer + FIRST_PERSON) = *(void **)(person + NEXT_PERSON);
    void *auxPerson = *(void **)(pBuffer + FIRST_PERSON);
    *(void **)(auxPerson + PREVIOUS_PERSON) = NULL;

    printf("Pessoa removida: ");
    printf("\nNome : %s", (char *)(person + NAME));
    printf("\nIdade : %d", *(int *)(person + AGE));
    printf("\nTelefone : %d\n", *(int *)(person + TELEPHONE));
    free(person);

  } else {
    printf("Pessoa removida: ");
    printf("\nNome : %s", (char *)(person + NAME));
    printf("\nIdade : %d", *(int *)(person + AGE));
    printf("\nTelefone : %d\n", *(int *)(person + TELEPHONE));
    free(person);
    *(void **)(pBuffer + FIRST_PERSON) = NULL;
    *(void **)(pBuffer + LAST_PERSON) = NULL;
    printf("Fila limpa!!\n");
  }
}

void search(void *pBuffer) {
  char *person = &*(char *)(pBuffer + SEARCH_NAME);
  void *auxPerson = *(void **)(pBuffer + FIRST_PERSON);

  if (auxPerson == NULL) {
    printf("A lista encontra-se vazia!\n");
    return;
  }

  printf("Name to be searched :");
  scanf("%s", person);
  setbuf(stdin, NULL);

  while (auxPerson != NULL) {
    if (strcmp(person, (char *)(auxPerson + NAME)) == 0) {
      printf("Nome encontrado:");
      printf("\n\tNome : %s", (char *)(auxPerson + NAME));
      printf("\n\tIdade : %d", *(int *)(auxPerson + AGE));
      printf("\n\tTelefone : %d\n", *(int *)(auxPerson + TELEPHONE));

      return;
    }
    auxPerson = *(void **)(auxPerson + NEXT_PERSON);
  }

  printf("Nome não encontrado\n");
}

void list(void *pBuffer) {
  void *person = *(void **)(pBuffer + FIRST_PERSON);
  if (person == NULL) {
    printf("A fila encontra-se vazia\n");
    return;
  }

  while (person != NULL) {
    printf("\nNome : %s", (char *)(person + NAME));
    printf("\nIdade : %d", *(int *)(person + AGE));
    printf("\nTelefone : %d\n", *(int *)(person + TELEPHONE));
    person = *(void **)(person + NEXT_PERSON);
  }
}

void RESET(void *pBuffer) {
  void *person = *(void **)(pBuffer + FIRST_PERSON);
  void *auxPerson;

  while (person != NULL) {
    auxPerson = *(void **)(person + NEXT_PERSON);
    free(person);
    person = auxPerson;
  }
  free(pBuffer);
}

void sort(void *person, void *pBuffer) {
  void *auxPerson = *(void **)(pBuffer + LAST_PERSON);

  while (auxPerson != NULL) {
    if (strcmp((char *)(auxPerson + NAME), (char *)(person + NAME)) <= 0 && *(void **)(auxPerson + NEXT_PERSON) == NULL) {
      *(void **)(person + PREVIOUS_PERSON) = *(void **)(pBuffer + LAST_PERSON);
      void *auxPerson = *(void **)(pBuffer + LAST_PERSON);
      *(void **)(pBuffer + LAST_PERSON) = person;
      *(void **)(auxPerson + NEXT_PERSON) = person;
      return;
    }
    if (strcmp((char *)(auxPerson + NAME), (char *)(person + NAME)) <= 0) {
      *(void **)(person + NEXT_PERSON) = *(void **)(auxPerson + NEXT_PERSON);
      *(void **)(person + PREVIOUS_PERSON) = auxPerson;
      void *tempPersom = *(void **)(auxPerson + NEXT_PERSON);
      *(void **)(tempPersom + PREVIOUS_PERSON) = person;
      *(void **)(auxPerson + NEXT_PERSON) = person;

      return;
    }
    auxPerson = *(void **)(auxPerson + PREVIOUS_PERSON);
    if (auxPerson == NULL) {
      *(void **)(person + NEXT_PERSON) = *(void **)(pBuffer + FIRST_PERSON);
      auxPerson = *(void **)(pBuffer + FIRST_PERSON);
      *(void **)(auxPerson + PREVIOUS_PERSON) = person;
      *(void **)(pBuffer + FIRST_PERSON) = person;
      return;
    }
  }
}
