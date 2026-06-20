#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 256
#define BLOCK_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    write(STDOUT_FILENO, "snprintf error\n", 15);
    return;
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block(struct header *block) {
  char *data = (char *)(block + 1);
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); i++) {
    uint64_t val = (uint64_t)data[i];
    print_out("%lu\n", &val, sizeof(val));
  }
}

int main() {
  void *blockAddress = sbrk(256);

  struct header *firstBlock = (struct header *)blockAddress;
  struct header *secondBlock = (struct header *)(blockAddress + BLOCK_SIZE);

  firstBlock->size = BLOCK_SIZE;
  firstBlock->next = NULL;
  secondBlock->size = BLOCK_SIZE;
  secondBlock->next = firstBlock;

  memset(firstBlock + 1, 0, BLOCK_SIZE - sizeof(struct header));
  memset(secondBlock + 1, 1, BLOCK_SIZE - sizeof(struct header));

  print_out("first block:       %p\n", &firstBlock, sizeof(firstBlock));
  print_out("second block:      %p\n", &secondBlock, sizeof(secondBlock));
  print_out("first block size:  %lu\n", &firstBlock->size, sizeof(firstBlock->size));
  print_out("first block next:  %p\n", &firstBlock->next, sizeof(firstBlock->next));
  print_out("second block size: %lu\n", &secondBlock->size, sizeof(secondBlock->size));
  print_out("second block next: %p\n", &secondBlock->next, sizeof(secondBlock->next));

  print_block(firstBlock);
  print_block(secondBlock);

  return 0;
}
