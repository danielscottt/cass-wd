#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "murmur3.h"

// a dirty insertion sort
void sort(int* arr, int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = i; j < size; j++) {
      if (arr[j] < arr[i]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}

int main(int argc, char **argv) {
  int i;
  int key_hash;
  int seed = 64;

  if (argc != 3) {
    printf("%s: a cassandra work distribution simulator\n", argv[0]);
    printf("usage: %s [node_count] [key]\n", argv[0]);
    exit(1);
  }

  int node_count;
  sscanf(argv[1], "%d", &node_count);
  int points[node_count];

  // Here we hash each node's identfier. This point is used to calculate the
  // range the node is resposible for.
  // For this experiment, the identifier is arbitrarily set to srv{node_number}.
  for (i = 0; i < node_count; i++) {
    int hash;
    char node_name[8];
    sprintf(node_name, "srv%d", i);
    MurmurHash3_x86_32(node_name, strlen(node_name), seed, &hash);
    points[i] = hash;
  }

  // sort the points
  // Sorting the points only has to be done when a node is added.
  // Removing a node just causes the union of the two adjacent ranges.
  sort(points, node_count);

  // hash our key
  MurmurHash3_x86_32(argv[2], strlen(argv[2]), seed, &key_hash);

  // Print the node points.  This is primarily to check our work.
  printf("node points:\n");
  for (i = 0; i < node_count; i++) {
    printf("  srv%d => %d\n", i, points[i]);
  }

  // Walk through the points in ascending order.  If we find a point which is 
  // greater than our hashed value, we know we've found our node.
  for (i = 0; i < node_count; i++) {
    if (key_hash < points[i]) {
      printf("key \"%s\" hashes to %d and is predicted to land on node %d/%d\n",
             argv[2], key_hash, i, node_count-1);
      return 0;
    }
  }

  // If we never reach a point which is greater than our hashed key, then we
  // belong in node 0, which is responsible for the range in the ring between
  // point n-1 through point 0.
  printf("key \"%s\" hashes to %d and is predicted to land on node %d/%d\n",
         argv[2], key_hash, 0, node_count-1);
  return 0;
}
