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

  code[depth] = '0';
  generateCodes(root->left, code, depth + 1);

  code[depth] = '1';
  generateCodes(root->right, code, depth + 1);
}

/**
 * Frees all nodes of a huffman tree using postorder traversal
 *
 * @param root Pointer to the root node of the tree.
 */
void freeTree(Node *root) {
  if (!root)
    return;

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

typedef struct {
  FILE *fp;
  unsigned char buffer;
  int bitCount;
} BitWriter;

void bitWriterInit(BitWriter *bw, FILE *fp) {
  bw->fp = fp;
  bw->buffer = 0;
  bw->bitCount = 0;
}

void writeBit(BitWriter *bw, int bit) {
  bw->buffer = (bw->buffer << 1) | (bit & 1);
  bw->bitCount++;
  if (bw->bitCount == 8) {
    fputc(bw->buffer, bw->fp);
    bw->buffer = 0;
    bw->bitCount = 0;
  }
}

void writeCode(BitWriter *bw, const char *code) {
  for (int i = 0; code[i]; ++i) {
    writeBit(bw, code[i] - '0');
  }
}

void bitWriterFlush(BitWriter *bw) {
  if (bw->bitCount > 0) {
    bw->buffer <<= (8 - bw->bitCount);
    fputc(bw->buffer, bw->fp);
    bw->buffer = 0;
    bw->bitCount = 0;
  }
}

typedef struct {
  FILE *fp;
  unsigned char buffer;
  int bitCount;
} BitReader;

void bitReaderInit(BitReader *br, FILE *fp) {
  br->fp = fp;
  br->buffer = 0;
  br->bitCount = 0;
}

int readBit(BitReader *br) {
  if (br->bitCount == 0) {
    int c = fgetc(br->fp);
    if (c == EOF)
      return -1;
    br->buffer = (unsigned char)c;
    br->bitCount = 8;
  }

  int bit = (br->buffer >> 7) & 1;
  br->buffer <<= 1;
  br->bitCount--;
  return bit;
}

/**
 * @brief Compresses a file using Huffman coding.
 *
 * Reads the input file, builds a Huffman tree, generates codes,
 * and writes a compressed `.huff` file.
 *
 * @param inputPath Path of the source file.
 * @param outputPath Path of the compressed output file.
 * @return 0 on success, 1 on failure.
 */

int compressFile(const char *inputPath, const char *outputPath) {
  FILE *fptr = fopen(inputPath, "rb");
  if (!fptr) {
    perror("The file was not found !");
    return 1;
  }
  unsigned freq[256] = {0};
  int c;
  long totalChars = 0;

  while ((c = fgetc(fptr)) != EOF) {
    freq[(unsigned char)c]++;
    totalChars++;
  }

  if (totalChars == 0) {
    printf("File is empty: \n");
    fclose(fptr);
    return 0;
  }

  Node *root = buildHuffmanTree(freq);

  memset(codeTable, 0, sizeof(codeTable));
  char code[256];
  generateCodes(root, code, 0);

  FILE *out = fopen(outputPath, "wb");

  if (!out) {
    perror("Could not create an output file.\n");
    fclose(fptr);
    freeTree(root);
    return 1;
  }

  int uniqueCount = 0;
  for (int i = 0; i < 256; ++i)
    if (freq[i] > 0)
      uniqueCount++;

  fwrite(&uniqueCount, sizeof(int), 1, out);
  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
      unsigned char byte = (unsigned char)i;
      fwrite(&byte, sizeof(unsigned char), 1, out);
      fwrite(&freq[i], sizeof(unsigned), 1, out);
    }
  }

  fwrite(&totalChars, sizeof(long), 1, out);
  rewind(fptr);
  BitWriter bw;
  bitWriterInit(&bw, out);

  while ((c = fgetc(fptr)) != EOF) {
    writeCode(&bw, codeTable[(unsigned char)c]);
  }
  bitWriterFlush(&bw);

  fclose(fptr);
  fclose(out);
  for (int i = 0; i < 256; ++i) {
    if (codeTable[i])
      free(codeTable[i]);
  }

  freeTree(root);
  printf("Compressed file has been generated. %s\n", outputPath);
  return 0;
}
int decompressFile(const char *inputPath, const char *outputPath) {
  FILE *in = fopen(inputPath, "rb");
  if (!in) {
    perror("Compressed file not found.\n");
    return 1;
  }

  int uniqueCount;
  fread(&uniqueCount, sizeof(int), 1, in);

  unsigned freq[256] = {0};
  for (int i = 0; i < uniqueCount; ++i) {
    unsigned char byte;
    unsigned f;
    fread(&byte, sizeof(unsigned char), 1, in);
    fread(&f, sizeof(unsigned), 1, in);
    freq[byte] = f;
  }

  long totalChars;
  fread(&totalChars, sizeof(long), 1, in);

  Node *root = buildHuffmanTree(freq);
  FILE *out = fopen(outputPath, "wb");

  if (!out) {
    perror("The file couldn't be created.\n");
    fclose(in);
    freeTree(root);
    return 1;
  }
  BitReader br;
  bitReaderInit(&br, in);

  long decoded = 0;
  Node *curr = root;

  if (uniqueCount == 1) {
    for (long i = 0; i < totalChars; i++) {
      fputc(root->left->ch, out);
    }
    decoded = totalChars;
  } else {
    while (decoded < totalChars) {
      int bit = readBit(&br);
      if (bit == -1)
        break;

      curr = (bit == 0) ? curr->left : curr->right;
      if (!curr->right && !curr->left) {
        fputc(curr->ch, out);
        decoded++;
        curr = root;
      }
    }
  }
  fclose(in);
  fclose(out);
  freeTree(root);
  printf("Decompressed file is ready. %s \n", outputPath);
  return 0;
}

int main(void) {

  int compressStatus = compressFile("FileTester.txt", "Compress.huff");

  if (compressStatus != 0) {
    printf("Compression failed.\n");
    return 1;
  }

  int decompressStatus = decompressFile("Compress.huff", "Decompressed.txt");

  if (decompressStatus != 0) {
    printf("Decompression failed.\n");
    return 1;
  }

  return 0;
}
