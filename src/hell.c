// hell Copyright (C) 2024 kernaltrap8
// This program comes with ABSOLUTELY NO WARRANTY
// This is free software, and you are welcome to redistribute it
// under certain conditions

/*
    hell.c
*/

#include "hell.h"
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

unsigned long generate_random_index(unsigned long *seed, int array_size) {
  // Initialize the seed using /dev/urandom
  int urandom = open("/dev/urandom", O_RDONLY);
  if (urandom < 0) {
    perror("Unable to open /dev/urandom");
    exit(EXIT_FAILURE);
  }
  if (read(urandom, seed, sizeof(*seed)) < 0) {
    perror("Unable to read from /dev/urandom");
    close(urandom);
    exit(EXIT_FAILURE);
  }
  close(urandom);

  // Generate a random number using the LCG
  *seed = (MULTIPLIER * (*seed) + INCREMENT) % MODULUS;

  // Return a random index within the array size
  return *seed % array_size;
}

int main(int argc, char *argv[]) {
  if ((argc > 1 && !strcmp(argv[1], "-v")) || !strcmp(argv[1], "--version")) {
    printf("hell v%s\nLicensed under BSD-Clause-3\n", VERSION);
    exit(0);
  }
  if ((argc > 1 && !strcmp(argv[1], "-h")) || !strcmp(argv[1], "--help")) {
    puts(HELP_BANNER);
    exit(0);
  }
  puts(BANNER);
  puts("leave while you still can...\n");
  sleep(1);
  while (true) {
    if ((argc > 1 && !strcmp(argv[1], "-f")) || !strcmp(argv[1], "--fork")) {
      pid_t proc = fork();
      printf("created new process %d\n", proc);
    }
    unsigned long seed;
    unsigned long n = generate_random_index(&seed, INT_MAX);
    void *ptr = malloc(n);
    if (ptr == NULL) {
      perror("malloc");
      exit(1);
    }
    printf("allocated %zu bytes at memory address %p\n", n, ptr);
    // free(ptr);
  }
  return 0;
}
