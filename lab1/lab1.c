#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void take_input(char *pline, size_t *len) {
  printf("Please enter some text : ");
  ssize_t size = getline(&pline, len, stdin);

  if (size == -1) {
    perror("An Error or EOF encountered in the stdin stream");
    free(pline);
    exit(1);
  }

  printf("\nTokens:\n");

  char *saveptr = NULL;
  char *ptoken = strtok_r(pline, " ", &saveptr);

  while (ptoken != NULL) {
    printf("%s\n", ptoken);
    ptoken = strtok_r(NULL, " ", &saveptr);
  }
}

int main() {
  char *pline;
  // Code adapted from man getline + c-for-dummies.com + geeksforgeeks.org
  // This initial setting will allow getline to allocate memory internally
  while (true) {
    char *pline = NULL;
    size_t len = 0;

    take_input(pline, &len);
  }

  free(pline);
  return 0;
}
