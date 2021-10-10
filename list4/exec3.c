#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No {
  int valor;
  struct No *noEsq;
  struct No *noDir;
} No;

int addNo(No **ppRaiz, int valor);
int ChecaBalanceamento(No **ppRaiz);
int FB(No *pRaiz);
int AlturaArvore(No *pRaiz);
void RES(No **ppRaiz);
void RDS(No **ppRaiz);
int GiraEsquerda(No **ppRaiz);
int GiraDireita(No **ppRaiz);
int EhArvoreArvl(No *pRaiz);
void FreeArvore(No *ppRaiz);
void SegundoCenario();
void caso1a();
void caso2a();
void caso3a();
void caso1b();
void caso2b();
void caso3b();

int main() {
  int i = 0, valorDoNo, qtdDeNos;
  No *ppRaiz = NULL;

  printf("Informa a quantidade de no: ");
  scanf("%d", &qtdDeNos);
  setbuf(stdin, NULL);

  srand(time(0));

  while (i < qtdDeNos) {
    valorDoNo = rand() % 100;
    addNo(&ppRaiz, valorDoNo);
    i++;
  }

  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  FreeArvore(ppRaiz);

  SegundoCenario();

  return 0;
}

int addNo(No **ppRaiz, int valor) {
  if (*ppRaiz == NULL) {
    *ppRaiz = (No *)malloc(sizeof(No));
    (*ppRaiz)->valor = valor;
    (*ppRaiz)->noEsq = NULL;
    (*ppRaiz)->noDir = NULL;
    return 1;
  } else if ((*ppRaiz)->valor > valor) {
    if (addNo(&(*ppRaiz)->noEsq, valor)) {
      if (ChecaBalanceamento(ppRaiz)) {
        return 0;
      } else {
        return 1;
      }
    }
  } else if ((*ppRaiz)->valor < valor) {
    if (addNo(&(*ppRaiz)->noDir, valor)) {
      if (ChecaBalanceamento(ppRaiz)) {
        return 0;
      } else {
        return 1;
      }
    }
  } else {
    return 0;
  }
}

int ChecaBalanceamento(No **ppRaiz) {
  int fb = FB(*ppRaiz);

  if (fb > 1) {
    return GiraEsquerda(ppRaiz);
  } else if (fb < -1) {
    return GiraDireita(ppRaiz);
  } else {
    return 0;
  }
}

int FB(No *pRaiz) {
  if (pRaiz == NULL) {
    return 0;
  }
  return AlturaArvore(pRaiz->noEsq) - AlturaArvore(pRaiz->noDir);
}

int AlturaArvore(No *pRaiz) {
  int Esq, Dir;

  if (pRaiz == NULL) {
    return 0;
  }

  Esq = AlturaArvore(pRaiz->noEsq);
  Dir = AlturaArvore(pRaiz->noDir);

  if (Esq > Dir) {
    return Esq + 1;
  } else {
    return Dir + 1;
  }
}

void RES(No **ppRaiz) {
  No *pAux;

  pAux = (*ppRaiz)->noDir;
  (*ppRaiz)->noDir = pAux->noEsq;
  pAux->noEsq = (*ppRaiz);
  (*ppRaiz) = pAux;
}

void RDS(No **ppRaiz) {
  No *pAux;

  pAux = (*ppRaiz)->noEsq;
  (*ppRaiz)->noEsq = pAux->noDir;
  pAux->noDir = (*ppRaiz);
  (*ppRaiz) = pAux;
}

int GiraEsquerda(No **ppRaiz) {
  int FBE = FB((*ppRaiz)->noEsq);

  if (FBE > 0) {
    RDS(ppRaiz);

    return 1;
  } else if (FBE < 0) {
    RES(&((*ppRaiz)->noEsq));
    RDS(ppRaiz);

    return 1;
  }
  return 0;
}

int GiraDireita(No **ppRaiz) {
  int FBD = FB((*ppRaiz)->noDir);

  if (FBD <= 0) {
    RES(ppRaiz);

    return 1;
  } else if (FBD > 0) {
    RDS(&((*ppRaiz)->noDir));
    RES(ppRaiz);

    return 1;
  }
  return 0;
}

void FreeArvore(No *ppRaiz) {
  if (ppRaiz == NULL) return;

  FreeArvore(ppRaiz->noEsq);
  FreeArvore(ppRaiz->noDir);

  free(ppRaiz);
}

int EhArvoreArvl(No *ppRaiz) {
  int fb;
  fb = FB(ppRaiz);

  if (ppRaiz == NULL)
    return 1;

  if (!EhArvoreArvl(ppRaiz->noEsq)) {
    return 0;
  }
  if (!EhArvoreArvl(ppRaiz->noDir)) {
    return 0;
  }

  if ((fb > 1) || (fb < -1)) {
    return 0;
  } else {
    return 1;
  }
}

void SegundoCenario() {
  printf("\n--CASO 1A--\n");
  caso1a();
  printf("\n--CASO 2A--\n");
  caso2a();
  printf("\n--CASO 3A--\n");
  caso3a();
  printf("\n--CASO 1B--\n");
  caso1b();
  printf("\n--CASO 2B--\n");
  caso2b();
  printf("\n--CASO 3B--\n");
  caso3b();
}

void caso1a() {
  No *ppRaiz = NULL;
  int valorDoNo;
  valorDoNo = 20;
  addNo(&ppRaiz, valorDoNo);
  valorDoNo = 4;
  addNo(&ppRaiz, valorDoNo);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorDoNo = 15;
  addNo(&ppRaiz, valorDoNo);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  FreeArvore(ppRaiz);
}

void caso2a() {
  No *ppRaiz = NULL;
  int valores[6] = {20, 4, 26, 3, 9, 15};
  int i;

  for (i = 0; i < 5; i++) {
    addNo(&ppRaiz, valores[i]);
  };

  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");

  addNo(&ppRaiz, valores[5]);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  FreeArvore(ppRaiz);
}

void caso3a() {
  No *ppRaiz = NULL;
  int valores[11] = {20, 4, 26, 3, 9, 2, 7, 11, 21, 30, 15};
  int i;

  for (i = 0; i < 10; i++) {
    addNo(&ppRaiz, valores[i]);
  };

  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");

  addNo(&ppRaiz, valores[11]);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  FreeArvore(ppRaiz);
}

void caso1b() {
  No *ppRaiz = NULL;
  int valorDoNo;
  valorDoNo = 20;
  addNo(&ppRaiz, valorDoNo);
  valorDoNo = 4;
  addNo(&ppRaiz, valorDoNo);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorDoNo = 8;
  addNo(&ppRaiz, valorDoNo);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  FreeArvore(ppRaiz);
}

void caso2b() {
  No *ppRaiz = NULL;
  int valores[6] = {20, 4, 26, 3, 9, 8};
  int i;

  for (i = 0; i < 5; i++) {
    addNo(&ppRaiz, valores[i]);
  };

  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");

  addNo(&ppRaiz, valores[5]);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  FreeArvore(ppRaiz);
}

void caso3b() {
  No *ppRaiz = NULL;
  int valores[11] = {20, 4, 26, 3, 9, 2, 7, 11, 21, 30, 8};
  int i;

  for (i = 0; i < 10; i++) {
    addNo(&ppRaiz, valores[i]);
  };

  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");

  addNo(&ppRaiz, valores[11]);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  FreeArvore(ppRaiz);
}