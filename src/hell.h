// hell Copyright (C) 2024 kernaltrap8
// This program comes with ABSOLUTELY NO WARRANTY
// This is free software, and you are welcome to redistribute it
// under certain conditions

/*
    hell.h
*/

/*
   required defines
*/

#define VERSION "0.1"
#define MODULUS 2147483648 // 2^31
#define MULTIPLIER 1103515245
#define INCREMENT 12345

#define BANNER                                                                 \
  "\
 _      ________   _________  __  _______  __________    __ ________   __ \n\
| | /| / / __/ /  / ___/ __ \\/  |/  / __/ /_  __/ __ \\  / // / __/ /  / / \n\
| |/ |/ / _// /__/ /__/ /_/ / /|_/ / _/    / / / /_/ / / _  / _// /__/ /__\n\
|__/|__/___/____/\\___/\\____/_/  /_/___/   /_/  \\____/ /_//_/___/____/____/\n\
                                                                          \n"
/*
   function prototypes
*/

unsigned long generate_random_index(unsigned long *seed, int array_size);
int main(int argc, char *argv[]);
