#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "murmur3.h"

#define HTABLE_SZ (1<<15)-1
#define HTABLE_SEED 64

typedef struct htable {
  void* data[HTABLE_SZ];
} htable;

void put(htable* ht, char* key, void* val)
{
  int32_t hash;
  MurmurHash3_x86_32(key, strlen(key), HTABLE_SEED, &hash);
  ht->data[HTABLE_SZ % hash] = val;
}

void* get(htable* ht, char* key)
{
  int32_t hash;
  MurmurHash3_x86_32(key, strlen(key), HTABLE_SEED, &hash);
  return ht->data[HTABLE_SZ % hash];
}

int main()
{
  htable ht;
  put(&ht, "dan", "rules");
  void* out = get(&ht, "dan");
  char* out_str = (char*) out;
  printf("dan %s\n", out_str);
  return 0;
}
