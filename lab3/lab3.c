#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *getInput() {
  char *input = NULL;
  size_t bufferLen = 0;
  ssize_t inputLen;

  printf("Enter input: ");
  inputLen = getline(&input, &bufferLen, stdin);

  if (inputLen == -1) {
    return NULL;
  }

  return input;
}

int addToHistory(char *history[], int *index, int *numOfElements, int size, char *string,
                 int *looped) {
  if (string == NULL) {
    return -1;
  }

  if (*looped) {
    free(history[*index]);
  }

  history[*index] = string;

  if (*numOfElements < 5) {
    *numOfElements = *numOfElements + 1;
  }

  if (*index < 5) {
    *index = *index + 1;
  }

  if (*index == 5) {
    *index = 0;
    *looped = 1;
  }

  return 0;
}

void freeMemory(char *arr[], int n) {
  for (int i = 0; i < n; i++) {
    free(arr[i]);
  }
}

void printArray(char *arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%s", arr[i]);
  }
}

int main() {
  int size = 5;

  char *history[size];

  int numOfElem = 0;

  int index = 0;

  int looped = 0;

  while (1) {
    char *input = getInput();

    // if (addToHistory(history, &numOfElem, size, input) == -1) {
    //  printf("Adding to history failed!");
    //}

    addToHistory(history, &index, &numOfElem, size, input, &looped);

    if (strcmp(input, "print\n") == 0) {
      printArray(history, numOfElem);
      freeMemory(history, numOfElem);
      numOfElem = 0;
      index = 0;
      looped = 0;
    }
  }

  return 0;
}
