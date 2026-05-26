#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter programs to run.\n");
    getline(&line, &len, stdin);

    char *saveptr;
    char *command = strtok_r(line, "\n", &saveptr);

    pid_t pid = fork();

    if (pid == 0) {
      if (execl(command, NULL) == -1) {
        printf("Exec failure. Check command directory.\n");
      }
    } else {
      waitpid(pid, NULL, WCONTINUED);
    }

    command = strtok_r(NULL, " ", &saveptr);
  }
}
