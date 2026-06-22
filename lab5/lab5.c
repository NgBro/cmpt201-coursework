#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  while (free_list_ptr != NULL) {
    if (free_list_ptr->size >= size) {
      return free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  struct header *curr = free_list_ptr;
  uint64_t best_diff = UINT64_MAX;
  while (curr != NULL) {
    if (curr->size >= size) {
      if (curr->size - size < best_diff) {
        best_diff = curr->size - size;
        best_fit_id = curr->id;
      }
    }
    curr = curr->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  struct header *curr = free_list_ptr;
  uint64_t worst_diff = 0;
  while (curr != NULL) {
    if (curr->size >= size) {
      if (curr->size - size >= worst_diff) {
        worst_diff = curr->size - size;
        worst_fit_id = curr->id;
      }
    }
    curr = curr->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  return 0;
}

// Part 2 Algorithm Pseudocode
// void free(mem_block *block, linkedList *list){
//    mem_block *right_block = block + block->size + sizeof(block)
//    search for right_block in list
//    if found:
//      merge block and right_block
//      remove right_block from list
//
//    mem_block *left_block = NULL
//    for item in list:
//      if item + item->size + sizeof(item) = block:
//        left_block = item
//
//    if left_block != NULL:
//      merge left_block and block
//      remove left_block from list
//
//    add block to list
// }
