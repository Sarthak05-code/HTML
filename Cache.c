#include <stdio.h>
#include <stdlib.h>

typedef struct Entry {
  int key, value;
  struct Entry *prev, *next;
  struct Entry *hashNext;
} Entry;

typedef struct {
  int capacity, size, numBuckets;
  Entry **buckets;
  Entry *head, *tail;
} LRUcache;

static Entry *newEntry(int key, int value) {
  Entry *e = calloc(1, sizeof(Entry));
  if (!e) {
    perror("calloc");
    exit(1);
  }
  e->key = key;
  e->value = value;
  return e;
}

static unsigned hashKey(const LRUcache *c, int key) {
  return (unsigned)key % (unsigned)c->numBuckets;
}

static Entry *mapFind(const LRUcache *c, int key) {
  for (Entry *e = c->buckets[hashKey(c, key)]; e; e = e->hashNext) {
    if (e->key == key)
      return e;
  }
  return NULL;
}

static void mapInsert(LRUcache *c, Entry *e) {
  unsigned h = hashKey(c, e->key);
  e->hashNext = c->buckets[h];
  c->buckets[h] = e;
}

static void mapRemove(LRUcache *c, int key) {
  Entry **pp = &c->buckets[hashKey(c, key)];
  while (*pp) {
    if ((*pp)->key == key) {
      *pp = (*pp)->hashNext;
      return;
    }

    pp = &(*pp)->hashNext;
  }
}

static void listRemove(Entry *e) {
  e->prev->next = e->next;
  e->next->prev = e->prev;
}

static void listPushFront(LRUcache *c, Entry *e) {
  e->prev = c->head;
  e->next = c->head->next;
  c->head->next->prev = e;
  c->head->next = e;
}

LRUcache *lruCreate(int capacity) {
  if (capacity < 0) {
    return NULL;
  }
  LRUcache *c = malloc(sizeof(LRUcache));
  if (!c) {
    return NULL;
  }

  c->capacity = capacity;
  c->size = 0;
  c->numBuckets = capacity * 2 + 1;
  c->buckets = calloc(c->numBuckets, sizeof(Entry));
  c->head = newEntry(0, 0);
  c->tail = newEntry(0, 0);
  c->head->next = c->tail;
  c->tail->prev = c->head;

  return c;
}

int lruGet(LRUcache *c, int key, int *out) {
  Entry *e = mapFind(c, key);
  if (!e) {
    return 0;
  }
  listRemove(e);
  listPushFront(c, e);
  *out = e->value;
  return 1;
}

void lruPut(LRUcache *c, int key, int value) {
  Entry *e = mapFind(c, key);
  if (e) {
    e->value = value;
    listRemove(e);
    listPushFront(c, e);
    return;
  }

  if (c->size == c->capacity) {
    Entry *victim = c->tail->prev;

    printf(" (eviciting key %d)\n", victim->key);
    listRemove(victim);
    mapRemove(c, victim->key);
    free(victim);
    c->size--;
  }
  e = newEntry(key, value);
  mapInsert(c, e);
  listPushFront(c, e);
  c->size++;
}

void lruPrint(const LRUcache *c) {
  printf(" MRY -> ");
  for (Entry *e = c->head->next; e != c->tail; e = e->next)
    printf("[%d:%d] ", e->key, e->value);
  printf(" <- LRU \n");
}

void lruFree(LRUcache *c) {
  Entry *e = c->head;
  while (e) {
    Entry *next = e->next;
    free(e);
    e = next;
  }
  free(c->buckets);
  free(c);
}

int main(void) {
  LRUcache *cache = lruCreate(3);
  int v;

  printf("put 1,2,3\n");
  lruPut(cache, 1, 10);
  lruPut(cache, 2, 20);
  lruPut(cache, 3, 30);
  lruPrint(cache);

  printf("get 1\n");
  if (lruGet(cache, 1, &v))
    printf("  hit: %d\n", v);
  lruPrint(cache);

  printf("put 4 (cache is full)\n");
  lruPut(cache, 4, 40);
  lruPrint(cache);

  printf("get 2\n");
  if (!lruGet(cache, 2, &v))
    printf("  miss (2 was evicted)\n");

  printf("put 3 again with new value\n");
  lruPut(cache, 3, 99);
  lruPrint(cache);

  lruFree(cache);
  return 0;
}
