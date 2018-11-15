#pragma pack()

#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <iostream>

#include "pico.hpp"

using namespace std;

int main() {
  Pico p{};
  //printf("Running capture\n");
  //int32_t timeIndisposedAfterCapture;
  //status =
      //ps3000aRunBlock(picoHandle, noSamplesBefore, noSamplesAfter, timebase, 0,
                      //&timeIndisposedAfterCapture, 0, NULL, NULL);
  //if (status != PICO_OK)
    //throw status;
  //printf("Capture started, afterwards the scope will take %dms to copy\n",
         //timeIndisposedAfterCapture);

  //int16_t ready = 0;
  //do {
    //status = ps3000aIsReady(picoHandle, &ready);
    //if (status != PICO_OK)
      //throw status;
    //this_thread::sleep_for(100ms);
  //} while (!ready);

  //printf("Capture is done\n");

  //// create buffer for the result
  //printf("Setting data buffer\n");
  //int32_t bufferLength = (noSamplesBefore + noSamplesAfter) * sizeof(int16_t);
  //int16_t *buffer = (int16_t *)malloc(bufferLength);
  //memset(buffer, 0, bufferLength);
  //status = ps3000aSetDataBuffer(picoHandle, PS3000A_CHANNEL_B, buffer,
                                //bufferLength, 0, PS3000A_RATIO_MODE_NONE);
  //if (status != PICO_OK)
    //throw status;

  //printf("Getting values\n");
  //int16_t overflow;
  //status = ps3000aGetValues(picoHandle, 0, &noSamples, 1,
                            //PS3000A_RATIO_MODE_NONE, 0, &overflow);
  //if (status != PICO_OK)
    //throw status;
  //printf("%d samples returned\n", noSamples);
  //if (overflow)
    //printf("an overflow occured: %04x\n", overflow);

  //status = ps3000aStop(picoHandle);
  //if (status != PICO_OK)
    //throw status;

  //printf("\nCompleted successfully\n");

  //printf("Closing connection to picoscope\n");
  //status = ps3000aCloseUnit(picoHandle);
  //if (status != PICO_OK)
    //throw status;

  //printf("Writing data to data.csv\n");
  //auto output = ofstream("data.csv");
  //for (uint32_t i = 0; i < noSamples; i++) {
    //output << buffer[i] << ",";
  //}
  //output << endl;
  //output.flush();

  return 0;
}
