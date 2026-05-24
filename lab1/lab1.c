#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Please enter some text: ");
    getline(&line, &len, stdin);

    char *saveptr;
    char *token = strtok_r(line, " ", &saveptr);

    printf("Tokens:\n");

    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }
  free(line);
}
