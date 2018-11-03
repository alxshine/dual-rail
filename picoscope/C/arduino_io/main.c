#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define BAUDRATE B115200
#define DEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1

const char* defaultInput = "testtesttesttest";

void randFill(char *arr, int n) {
  for (int i = 0; i < n; ++i) {
    arr[i] = rand();
    /*arr[i] = defaultInput[i];*/
  }
}

void printToFile(FILE* fd, char* arr, int n){
  for(int i = 0; i < n; i++){
    fprintf(fd, "%u", (unsigned char) arr[i]);
    if(i<n-1)
      fprintf(fd, ",");
  }
  fprintf(fd, "\n");
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s numPlaintexts\n", argv[0]);
    return 1;
  }
  int numPlaintexts = atoi(argv[1]);

  int tty, res;
  struct termios oldtio, newtio;
  char buf[255];

  tty = open(DEVICE, O_RDWR);
  if (tty < 0) {
    perror(DEVICE);
    return 1;
  }

  FILE* ptxtd = fopen("plaintexts.txt", "w+");

  tcgetattr(tty, &oldtio); /* save current port settings */

  memset(&newtio, 0, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CS8 | CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;

  /* set input mode (non-canonical, no echo,...) */
  newtio.c_lflag = 0;

  newtio.c_cc[VTIME] = 0; // inter-character timer unused
  newtio.c_cc[VMIN] = 4; // blocking read until 5 chars received

  tcflush(tty, TCIFLUSH);
  tcsetattr(tty, TCSANOW, &newtio);

  char input[17];
  input[16] = '\n';
  srand(time(NULL));
  for (int i = 0; i < numPlaintexts; i++) {
    printf("Plaintext %d ", i+1);
    randFill(input, 16);
    write(tty, input, 17);

    res = read(tty, buf, 255);
    printf("Read %d bytes\n", res);
    buf[res] = 0;
    printToFile(ptxtd, buf, 16);
  }
  tcsetattr(tty, TCSANOW, &oldtio);
  close(tty);
  fclose(ptxtd);
}
