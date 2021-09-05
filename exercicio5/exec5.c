#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[30];
  int idade;
  int altura;
} Pessoa;

int main() {
  int contador = 0, option = 1, i;
  Pessoa *buffer = NULL;

  while (option == 1) {
    if (contador == 0)
      buffer = (Pessoa *)malloc(sizeof(Pessoa));
    else {
      buffer = (Pessoa *)realloc(buffer, (contador + 1) * sizeof(Pessoa));

      if (buffer == NULL) {
        printf("Out of memory");
      }
    }

    printf("Digite o nome da pessoa: ");
    scanf("%s", buffer[contador].nome);
    printf("Digite a idade: ");
    scanf("%d", &buffer[contador].idade);
    printf("Digite a altura: ");
    scanf("%d", &buffer[contador].altura);

    printf("Deseja informar mais uma pessoa?\n");
    printf("1-Sim\n2-Não");
    printf("\nOpcao:");
    scanf("%d", &option);
    if (option == 1) {
      contador++;
    }
  }

  for (i = 0; i <= contador; i++) {
    printf("\nNome: %s", buffer[i].nome);
    printf("\nIdade: %d", buffer[i].idade);
    printf("\nAltura: %d", buffer[i].altura);
    printf("\n-----------------");
  }

  free(buffer);

  return 0;
}