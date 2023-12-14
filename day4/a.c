#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;

struct node {
  int number;
  Node *next;
};

Node *prepend(int number, Node *root) {
  Node *newRoot = malloc(sizeof(Node));
  newRoot->number = number;
  newRoot->next = root;
  return newRoot;
}

void freeList(Node *root) {
  Node *current = root;
  while (current) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
}

void printList(Node *root) {
  Node *current = root;
  while (current) {
    printf("%i ", current->number);
    current = current->next;
  }
}

int exists(int number, Node *root) {
  Node *current = root;
  while (current) {
    if (current->number == number) {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

int main() {

  // Open file
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL)
    return 1;

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int sum = 0;

  while ((read = getline(&line, &len, fp)) != -1) {

    Node *winning = NULL;
    Node *numbers = NULL;

    int start;
    // Walk to the ":" character 
    for (int i = 0; i < len; i++) {
      if (line[i] == *":") {
        start = i + 1;
        break;
      }
    }

    // Parse winning numbers to the "|" character
    for (int i = start; i < len; i++) {
      if (line[i] == *"|") {
        start = i + 1;
        break;
      }

      int num = 0;
      while (isdigit(line[i])) {
        num = num * 10 + (line[i] - 48);
        i++;
      }
      if (num)
        winning = prepend(num, winning);
    }

    // Parse the remaining numbers
    for (int i = start; i < len; i++) {
      int num = 0;
      while (isdigit(line[i])) {
        num = num * 10 + (line[i] - 48);
        i++;
      }
      if (num)
        numbers = prepend(num, numbers);
    }


    // Calculate score
    int score = 0;
    Node* current = numbers;
    while (current) {
      if (exists(current->number, winning)){
        if (!score) {
          score = 1;
        } else {
          score *=2;
        }
      }
      current = current->next;
    }

    sum+= score;

    // printf("Winning: ");
    // printList(winning);
    // printf("\n");

    // printf("numbers: ");
    // printList(numbers);
    // printf("\n");

    freeList(winning);
    freeList(numbers);
  }
  printf("%i\n", sum);
  
  fclose(fp);
  
  return 0;
}

