#include <fcntl.h>
#include <stdio.h>
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

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s numPlaintexts\n", argv[0]);
    return 1;
  }
  int numPlaintexts = atoi(argv[1]);

  int fd, res;
  struct termios oldtio, newtio;
  char buf[255];

  /*fd = open(DEVICE, O_RDWR | O_NOCTTY);*/
  fd = open(DEVICE, O_RDWR);
  if (fd < 0) {
    perror(DEVICE);
    return 1;
  }

  tcgetattr(fd, &oldtio); /* save current port settings */

  memset(&newtio, 0, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CS8 | CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;

  /* set input mode (non-canonical, no echo,...) */
  newtio.c_lflag = 0;

  newtio.c_cc[VTIME] = 0; // inter-character timer unused
  newtio.c_cc[VMIN] = 15; // blocking read until 5 chars received

  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);

  char input[17];
  input[16] = '\n';
  srand(time(NULL));

  for (int i = 0; i < numPlaintexts; i++) {
    randFill(input, 16);
    write(fd, input, 17);
    res = read(fd, buf, 255);
    printf("Read %d bytes\n", res);
    buf[res] = 0;
    printf("%s\n", buf);
    if (buf[0] == 'z')
      break;
  }
  tcsetattr(fd, TCSANOW, &oldtio);
  close(fd);
}
