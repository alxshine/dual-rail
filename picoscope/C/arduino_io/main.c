#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BAUDRATE B115200
#define DEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1

void randFill(char* arr, int n){
  for (int i = 0; i < n; ++i) {
    arr[i] = rand();
  }
}

int main() {
  int fd, res;
  struct termios oldtio, newtio;
  char buf[255];

  /*fd = open(DEVICE, O_RDWR | O_NOCTTY);*/
  fd = open(DEVICE, O_RDWR);
  if (fd < 0) {
    perror(DEVICE);
    return -1;
  }

  tcgetattr(fd, &oldtio); /* save current port settings */

  memset(&newtio, 0, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CS8 | CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;

  /* set input mode (non-canonical, no echo,...) */
  newtio.c_lflag = 0;

  newtio.c_cc[VTIME] = 0; // inter-character timer unused
  newtio.c_cc[VMIN] = 16;  // blocking read until 5 chars received

  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);

  char input[16];
  srand(time(NULL));

  while (1) {
    randFill(input, 16);
    write(fd, input, 16);
    res = read(fd, buf, 255);
    buf[res] = 0;
    printf("%s\n", buf);
    if (buf[0] == 'z')
      break;
  }
  tcsetattr(fd, TCSANOW, &oldtio);
}
