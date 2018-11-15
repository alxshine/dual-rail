#ifndef PICO_H
#define PICO_H
#pragma pack()

#include <iostream>

#include <libps3000a-1.1/ps3000aApi.h>

class Pico
{
private:
  int16_t picoHandle;

public:
  Pico();
  virtual ~Pico();
};

#endif /* PICO_H */
