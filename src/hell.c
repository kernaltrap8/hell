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

// pass in argc/argv from main, and the arg to check for
int check_args(int argc, char *argv, char *arg) {
  if (argc > 1 && !strcmp(argv, arg)) {
    return 1;
  } else {
    return 0;
  }
}

// random ulong generator for malloc
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

// main entrypoint
int main(int argc, char *argv[]) {
  if (check_args(argc, argv[1], "-v") ||
      check_args(argc, argv[1], "--version")) {
    printf("hell v%s\nLicensed under BSD-Clause-3\n", VERSION);
    exit(0);
  }
  if (check_args(argc, argv[1], "-h") || check_args(argc, argv[1], "--help")) {
    puts(HELP_BANNER);
    exit(0);
  }
  puts(BANNER);
  puts("leave while you still can...\n");
  sleep(1);
  while (true) {
    if (check_args(argc, argv[1], "-f") ||
        check_args(argc, argv[1], "--fork")) {
      pid_t proc = fork();
      printf("created new process %d\n", proc);
    }
    unsigned long seed; // seed for the rng function
    unsigned long n =
        generate_random_index(&seed, INT_MAX); // random ulong from rng func
    void *ptr = malloc(n); // malloc the random amount of memory
    if (ptr == NULL) {     // maloc has failed, perror and exit
      perror("malloc");
      exit(1);
    }
    printf("allocated %zu bytes at memory address %p\n", n, ptr);
    // free(ptr); // lol
  }
  return 0;
}
