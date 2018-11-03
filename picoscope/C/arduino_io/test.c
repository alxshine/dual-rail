#include <stdio.h>

int main(){
  FILE* testFile = fopen("test.dat", "w+");
  fprintf(testFile, "test\n");
  fclose(testFile);
}
