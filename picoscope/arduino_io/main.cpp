#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "tty_utils.hpp"
#include "tty.hpp"

#define BAUDRATE B115200
#define DEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1

const char* defaultInput = "testtesttesttest";

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s numPlaintexts\n", argv[0]);
    return 1;
  }
  int numPlaintexts = atoi(argv[1]);
  FILE* ptxtd = fopen("plaintexts.txt", "w+");
  Tty tty{DEVICE, BAUDRATE};
  char buf[255];

  char input[17];
  input[16] = '\n';
  srand(time(NULL));
  for (int i = 0; i < numPlaintexts; i++) {
    printf("Plaintext %d ", i+1);
    randFill(input, 16);
    tty.write(input);

    auto res = tty.read(buf, 255);
    printf("Read %lu bytes\n", res);
    buf[res] = 0;
    printToFile(ptxtd, buf, 16);
  }
  fclose(ptxtd);
}
