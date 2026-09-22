#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 512

typedef struct Node {
  unsigned char ch;
  unsigned freq;
  struct Node *left, *right;

} Node;

typedef struct {
  Node **arr;
  int size;
  int capacity;
} Minheap;

Minheap *createHeap(int capacity) {
  Minheap *h = malloc(sizeof(Minheap));
  h->arr = malloc(capacity * sizeof(Node *));
  h->size = 0;
  h->capacity = capacity;
  return h;
}

void swapNode(Node **a, Node **b) {
  Node *t = *a;
  *a = *b;
  *b = t;
}

void heapifyDown(Minheap *h, int idx) {
  int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
  if (left < h->size && h->arr[left]->freq < h->arr[smallest]->freq) {
    smallest = left;
  }

  if (right < h->size && h->arr[right]->freq < h->arr[smallest]->freq) {
    smallest = right;
  }

  if (smallest != idx) {
    swapNode(&h->arr[idx], &h->arr[smallest]);
    heapifyDown(h, smallest);
  }
}

void heapifyUp(Minheap *h, int idx) {
  while (idx > 0) {
    int parent = (idx - 1) / 2;
    if (h->arr[parent]->freq <= h->arr[idx]->freq)
      break;
    swapNode(&h->arr[parent], &h->arr[idx]);
    idx = parent;
  }
}

void insertHeap(Minheap *h, Node *node) {
  h->arr[h->size] = node;
  heapifyUp(h, h->size);
  h->size++;
}

Node *extractMin(Minheap *h) {
  Node *min = h->arr[0];
  h->arr[0] = h->arr[h->size - 1];
  h->size--;
  heapifyDown(h, 0);
  return min;
}

Node *newNode(unsigned char ch, unsigned freq, Node *left, Node *right) {
  Node *n = malloc(sizeof(Node));
  n->ch = ch;
  n->freq = freq;
  n->left = left;
  n->right = right;
  return n;
}

Node *buildHuffmanTree(unsigned freq[256]) {
  Minheap *h = createHeap(256);
  for (int i = 0; i < 256; ++i) {
    if (freq[i] > 0) {
      insertHeap(h, newNode((unsigned char)i, freq[i], NULL, NULL));
    }
  }

  if (h->size == 1) {
    Node *only = extractMin(h);
    insertHeap(h, newNode(0, 0, only, NULL));
  }

  while (h->size > 1) {
    Node *left = extractMin(h);
    Node *right = extractMin(h);
    Node *merged = newNode('\0', left->freq + right->freq, left, right);
    insertHeap(h, merged);
  }
  Node *root = extractMin(h);
  free(h->arr);
  free(h);
  return root;
}

char *codeTable[256];

void generateCodes(Node *root, char *code, int depth) {
  if (!root)
    return;

  if (!root->left && !root->right) {
    code[depth] = '\0';
    codeTable[root->ch] = strdup(code);
    return;
  }

  code[depth] = '\0';
  generateCodes(root->left, code, depth + 1);

  code[depth] = '1';
  generateCodes(root->right, code, depth + 1);
}

void freeTree(Node *root) {
  if (!root)
    return;

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

void compressFile();
void decompressFile();

int main(void) {
  compressFile("FileTester.txt", "Compress.huff");
  decompressFile("Compress.huff", "Decompressed.txt");

  return 0;
}
