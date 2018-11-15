#include "tty_utils.hpp"

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

