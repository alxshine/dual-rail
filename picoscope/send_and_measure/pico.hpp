#ifndef PICO_H
#define PICO_H
#pragma pack()

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <libps3000a-1.1/ps3000aApi.h>

class Pico
{
private:
  int16_t picoHandle;
  uint32_t timebase = 2; // the arduino runs at 84MHz, so once every 12ns, which
                         // means I need half that
  int32_t noSamplesBefore = 100;
  int32_t noSamplesAfter = 250e3;
  uint32_t numSamples = noSamplesBefore + noSamplesAfter;

public:
  Pico(); //TODO: throw exceptions instead of status
  virtual ~Pico();
  void startCapture();
  std::vector<short> retrieveData();
};

#endif /* PICO_H */
