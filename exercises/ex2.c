// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void PrintBytes(void *mem_addr, int num_bytes);

int main(int argc, char **argv) {
  char     char_val = '0';
  int32_t  int_val = 1;
  float    float_val = 1.0;
  double   double_val  = 1.0;

  typedef struct {
    char     char_val;
    int32_t  int_val;
    float    float_val;
    double   double_val;
  } Ex2Struct;

  Ex2Struct struct_val = { '0', 1, 1.0, 1.0 };

  PrintBytes(&char_val, sizeof(char));
  PrintBytes(&int_val, sizeof(int32_t));
  PrintBytes(&float_val, sizeof(float));
  PrintBytes(&double_val, sizeof(double));
  PrintBytes(&struct_val, sizeof(struct_val));

  return EXIT_SUCCESS;
}

void PrintBytes(void* mem_addr, int num_bytes) {
    // Cast to 8 bits so we can treat as a byte
    uint8_t* memAddress = (uint8_t*) mem_addr;
    printf("The %d bytes starting at %p are:", num_bytes, mem_addr);
    for (int i = 0; i < num_bytes; i++) {
        printf(" %02" PRIx8, *(memAddress + i));
    }
    printf("\n");
}
