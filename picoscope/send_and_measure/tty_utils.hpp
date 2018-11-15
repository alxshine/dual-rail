#ifndef TTY_UITLS_H
#define TTY_UITLS_H

#include <stdio.h>
#include <cstdlib>

void randFill(char *arr, int n);

void printToFile(FILE* fd, char* arr, int n);
#endif /* ifndef TTY_UITLS_H */
