#define _GNU_SOURCE
#include <ctype.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *strip(char *in) {
  if (in == NULL) {
    return NULL;
  }

  // lstrip
  // we need to ensure the char is read as unsigned
  while (isspace((unsigned char)*in))
    in++;

  char *pend = in + strlen(in) - 1;
  while (isspace((unsigned char)*pend)) {
    pend--;
  }

  *(pend + 1) = '\0';

  return in;
}

void take_input(char **pline, size_t *len) {
  printf("> ");
  ssize_t size = getline(pline, len, stdin);

  if (size == -1) {
    perror("An EOF error was encountered in the sdin stream");
    free(*pline);
    exit(1);
  }
}

int main() {
  char *pline;

  while (true) {
    char *pline = NULL;
    size_t len = 0;

    take_input(&pline, &len);
    pline = strip(pline);
    if (pline[0] == '\0') {
      continue;
    }

    pid_t pid;
    pid = fork();

    switch (pid) {
    // Code adapted from man fork
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);

    case 0:
      if (pline == NULL) {
        perror("nullptr");
        _exit(EXIT_FAILURE);
      }
      execl(pline, pline, NULL);
      perror("execl");
      continue;

    default:
      puts("");

      int status;
      waitpid(pid, &status, 0);
      continue;
    }
  }

  free(pline);
  return 0;
}
