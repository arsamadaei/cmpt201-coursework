#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // Code adapted from man getline + c-for-dummies.com + geeksforgeeks.org
  // This initial setting will allow getline to allocate memory internally
  char *pline = NULL;
  size_t len = 0;
  ssize_t text;

  printf("Please enter some text : ");
  text = getline(&pline, &len, stdin);

  if (text == -1) {
    perror("An Error or EOF encountered in the stdin stream");
    free(pline);
    exit(1);
  }

  printf("\nTokens: \n");

  char *saveptr = NULL;
  char *ptoken = strtok_r(pline, " ", &saveptr);

  while (ptoken != NULL) {
    printf("%s\n", ptoken);
    ptoken = strtok_r(NULL, " ", &saveptr);
  }

  free(pline);

  return 0;
}
