#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alphabetSize 256

typedef struct trie {
  char value;
  struct trie *next[alphabetSize];
  int terminal;
} Trie;

typedef struct trieRoot {
  Trie *root[alphabetSize];
} TrieRoot;

TrieRoot *createTrieRoot() {
  TrieRoot *root = (TrieRoot *)malloc(sizeof(TrieRoot));

  for (int i = 0; i < alphabetSize; i++) {
    root->root[i] = NULL;
  }

  return root;
}

Trie *create_trie(char c, int terminal) {
  Trie *t = (Trie *)malloc(sizeof(Trie));

  t->value = c;

  t->terminal = terminal;

  for (int i = 0; i < alphabetSize; i++) {
    t->next[i] = NULL;
  }

  return t;
}

void add_word_to_trie(Trie *current, char *word) {
  int len = strlen(word);

  if (len == 0) {
    current->terminal = 1;
    return;
  }

  if (current->next[word[0]] == NULL) {
    current->next[word[0]] = create_trie(word[0], len == 1);
    add_word_to_trie(current->next[word[0]], word + 1);
  } else {
    add_word_to_trie(current->next[word[0]], word + 1);
  }
}

void add_word(TrieRoot *root, char *word) {
  int len = strlen(word);

  if (len == 0 || root == NULL) {
    return;
  }

  if (root->root[word[0]] == NULL) {
    root->root[word[0]] = create_trie(word[0], len == 1);
  }

  add_word_to_trie(root->root[word[0]], word + 1);
}

int is_word_in_trie(Trie *trie, char *word) {
  int len = strlen(word);

  if (len == 0) {
    return trie->terminal;
  }

  if (trie->next[word[0]] == NULL) {
    return 0;
  }

  return is_word_in_trie(trie->next[word[0]], word + 1);
}

int is_word_in_root(TrieRoot *root, char *word) {
  if (root == NULL || strlen(word) == 0) {
    return 0;
  }

  if (root->root[word[0]] == NULL) {
    return 0;
  }

  return is_word_in_trie(root->root[word[0]], word + 1);
}

void destroy_trie(Trie *t) {
  for (int i = 0; i < alphabetSize; i++) {
    if (t->next[i]) {
      destroy_trie(t->next[i]);
    }
  }

  free(t);
}

void destroy_root(TrieRoot *root) {
  for (int i = 0; i < alphabetSize; i++) {
    if (root->root[i]) {
      destroy_trie(root->root[i]);
    }
  }

  free(root);
}

int main() {
  TrieRoot *root = createTrieRoot();

  add_word(root, "hello");

  if (is_word_in_root(root, "hello")) {
    printf("hello is in root\n");
  }

  if (!is_word_in_root(root, "kappa")) {
    printf("kappa is not in root\n");
  }

  add_word(root, "kappa");

  if (is_word_in_root(root, "kappa")) {
    printf("kappa is now in root\n");
  }

  if (!is_word_in_root(root, "keepo")) {
    printf("keepo is not in root\n");
  }

  if (is_word_in_root(root, "hello")) {
    printf("hello is in root\n");
  }

  destroy_root(root);
}
