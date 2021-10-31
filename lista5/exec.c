#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void printVector(int dataVector[], int vectorSize);
void checkOrder(int dataVector[], int vectorSize);
void callSort(int option, int dataVector[], int vectorSize);
void generetaVector(int dataVector[], int vectorSize);
void InsertionSort(int dataVector[], int vectorSize);
void SelectionSort(int dataVector[], int vectorSize);
void QuickSort(int dataVector[], int leftValue, int rightValue);
void MergeSort(int dataVector[], int size, int left, int right);
void Merge(int dataVector[], int size, int left, int meio, int right);

int main() {
  int vectorSize, option;
  srand(time(0));

  printf("Informe o numero de elementos do vetor: ");
  scanf("%d",  &vectorSize);

  int dataVector[vectorSize];

  generetaVector(dataVector, vectorSize);

  
  callSort(1, dataVector, vectorSize);
  callSort(2, dataVector, vectorSize);
  callSort(3, dataVector, vectorSize);
  callSort(4, dataVector, vectorSize);

  checkOrder(dataVector, vectorSize);
  
  return 0;
}

void InsertionSort(int dataVector[], int vectorSize) {
  int auxIndex, temp;
  for (int i = 1; i < vectorSize; i++) {
    temp = dataVector[i];
    auxIndex = i - 1;
    while (auxIndex >= 0 && dataVector[auxIndex] > temp) {
      dataVector[auxIndex + 1] = dataVector[auxIndex];
      auxIndex--;
    }
    dataVector[auxIndex + 1] = temp;
  }
}

void SelectionSort(int dataVector[], int vectorSize) {
  int smallerValue, temp, smallerIndex;

  for (int i = 0; i <= vectorSize; i++) {
    smallerIndex = i;
    smallerValue = dataVector[i];

    for (int j = i + 1; j < vectorSize; j++) {
      if (dataVector[j] < smallerValue) {
        smallerValue = dataVector[j];
        smallerIndex = j;
      }
    }

    temp = dataVector[i];
    dataVector[i] = dataVector[smallerIndex];
    dataVector[smallerIndex] = temp;
  }
}

void QuickSort(int dataVector[], int leftValue, int rightValue) {
  int pivot, temp;
  int i = leftValue, j = rightValue;
  pivot = dataVector[(leftValue + rightValue) / 2];

  do {
    while (dataVector[i] < pivot) { 
      i++;
    }
    while (dataVector[j] > pivot) { 
      j--;
    }
    if (i <= j) {
      temp = dataVector[i];
      dataVector[i] = dataVector[j];
      dataVector[j] = temp;
      i++;
      j--;
    }
  } while (i <= j);
  if (leftValue < j) {
    QuickSort(dataVector, leftValue, j);
  }
  if (rightValue > j) {
    QuickSort(dataVector, i, rightValue);
  }
}

void MergeSort(int dataVector[], int size, int left, int right) {
  if (left >= right) {
    return;
  }

  int meio = (left + right) / 2;

  MergeSort(dataVector, size, left, meio);     
  MergeSort(dataVector, size, meio + 1, right); 

  if (dataVector[meio] <= dataVector[meio + 1]) { 
    return;
  }
  Merge(dataVector, size, left, meio, right); 
}

void Merge(int dataVector[], int size, int left, int meio, int right) {
  int auxIndex = left, iniciodataVector = left, middleIndex = meio + 1;
  int vetorAux[size];

  for (int i = left; i <= right; i++) { 
    vetorAux[i] = dataVector[i];
  }

  while (iniciodataVector <= meio && middleIndex <= right) {
    if (vetorAux[iniciodataVector] <= vetorAux[middleIndex]) {
      dataVector[auxIndex] = vetorAux[iniciodataVector];
      iniciodataVector++;
    } else {
      dataVector[auxIndex] = vetorAux[middleIndex];
      middleIndex++;
    }
    auxIndex++;
  }

  while (iniciodataVector <= meio) {
    dataVector[auxIndex] = vetorAux[iniciodataVector];
    auxIndex++;
    iniciodataVector++;
  }

  while (middleIndex <= right) {
    dataVector[auxIndex] = vetorAux[middleIndex];
    auxIndex++;
    middleIndex++;
  }
}

void generetaVector(int dataVector[], int vectorSize) {
  int i = 0;
  while (i <= vectorSize) {
    dataVector[i] = rand() % 100;
    i++;
  }
}

void callSort(int option, int dataVector[], int vectorSize) {
  struct timeval begin, end;
  long seconds;
  long microseconds;
  double elapsed;
  switch (option) {
  case 1:
    printf("\tInsertion\n");

    gettimeofday(&begin, 0);
    InsertionSort(dataVector, vectorSize);
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("Tempo para o sort: %.9f segundos.\n", elapsed);
    break;
  case 2:
    printf("\tSelection\n");

    gettimeofday(&begin, 0);
    SelectionSort(dataVector, vectorSize);
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("Tempo para o sort: %.3f segundos.\n", elapsed);
    break;
  case 3:
    printf("\tQuick\n");

    gettimeofday(&begin, 0);
    QuickSort(dataVector, 0, vectorSize - 1);
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("Tempo para o sort: %.3f segundos.\n", elapsed);
    break;
  case 4:
    printf("\tMerge\n");

    gettimeofday(&begin, 0);
    MergeSort(dataVector, vectorSize, 0, vectorSize - 1);
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("Tempo para o sort: %.3f segundos.\n", elapsed);
    break;
  default:
   
    break;
  }
}

void printVector(int dataVector[], int vectorSize) {
  for (int i = 0; i < vectorSize; i++) {
    printf("[%d]", dataVector[i]);
  }
  printf("\n");
}

void checkOrder(int dataVector[], int vectorSize) {
  for (int i = 0; i < vectorSize - 1; i++) {
    if (dataVector[i] > dataVector[i + 1]) {
      printf("Lista nã ordenada!!\n");
      return;
    }
  }
  printf("Lista ordenada com sucesso\n");
  return;
}