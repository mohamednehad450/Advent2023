#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;

struct node {
  int number;
  Node *next;
};

typedef struct cardNode CardNode;

struct cardNode {
  int score;
  int count;
  CardNode *next;
};

Node *prepend(int number, Node *root) {
  Node *newRoot = malloc(sizeof(Node));
  newRoot->number = number;
  newRoot->next = root;
  return newRoot;
}

CardNode *appendCard(int score, CardNode *root) {
  CardNode *current = root;
  if (root) {
    while (current && current->next) {
      current = current->next;
    }
    CardNode *newNode = malloc(sizeof(CardNode));
    newNode->score = score;
    newNode->count = 1;
    newNode->next = NULL;

    current->next = newNode;

    return root;
  }

  CardNode *newNode = malloc(sizeof(CardNode));
  newNode->score = score;
  newNode->count = 1;
  newNode->next = NULL;
  return newNode;
}

void freeList(Node *root) {
  Node *current = root;
  while (current) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
}

void freeCards(CardNode *root) {
  CardNode *current = root;
  while (current) {
    CardNode *temp = current;
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

void printCards(CardNode *root) {
  CardNode *current = root;
  while (current) {
    printf("Score: %i, Count: %i \n", current->score, current->count);
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

void calcCardCount(CardNode *cards) {

  CardNode *card = cards;
  while (card) {
    if (!card || !card->next)
      return;

    CardNode *current = card->next;
    for (int i = 0; i < card->score; i++) {
      if (!current)
        break;
      current->count += card->count;
      current = current->next;
    }

    card = card->next;
  }
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

  CardNode *cards = NULL;

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
    int matches = 0;
    Node *current = numbers;
    while (current) {
      if (exists(current->number, winning)) {
        matches++;
      }
      current = current->next;
    }

    cards = appendCard(matches, cards);

    // printf("Winning: ");
    // printList(winning);
    // printf("\n");

    // printf("numbers: ");
    // printList(numbers);
    // printf("\n");

    freeList(winning);
    freeList(numbers);
  }

  // printCards(cards);

  calcCardCount(cards);

  //  printCards(cards);

  int sum = 0;
  CardNode *current = cards;
  while (current) {
    sum += current->count;
    current = current->next;
  }

  printf("%i\n", sum);

  freeCards(cards);
  fclose(fp);

  return 0;
}
