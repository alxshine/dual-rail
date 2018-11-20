#include "pico.hpp"

Pico::Pico() {
  std::cout << "Connecting to picoscope\n";
  PICO_STATUS status;
  status = ps3000aOpenUnit(&picoHandle, nullptr);

  if (status != PICO_OK)
    throw status;

  std::cout << "Configuring channel A\n";
  status = ps3000aSetChannel(picoHandle, PS3000A_CHANNEL_A, 1, PS3000A_DC,
                             PS3000A_5V, 0);
  if (status != PICO_OK)
    throw status;

  std::cout << "Getting maximum allowed offset for channel B\n";
  float maximumOffset, minimumOffset;
  status = ps3000aGetAnalogueOffset(picoHandle, PS3000A_200MV, PS3000A_DC,
                                    &maximumOffset, &minimumOffset);
  if (status != PICO_OK)
    throw status;

  std::cout << "Maximum offset " << maximumOffset << ", minimum offset "
            << minimumOffset << std::endl;

  std::cout << "Configuring channel B\n";
  status = ps3000aSetChannel(picoHandle, PS3000A_CHANNEL_B, 1, PS3000A_AC,
                             PS3000A_20MV, 0);
  if (status != PICO_OK)
    throw status;

  std::cout << "Calculating the timebase\n";
  float actualIntervalInNs;
  int32_t maxAvailableSamples;
  status = ps3000aGetTimebase2(picoHandle, timebase, numSamples,
                               &actualIntervalInNs, 0, &maxAvailableSamples, 0);

  if (status != PICO_OK)
    throw status;
  printf("The time between samples is %fns and we can use a maximum of %d "
         "samples\n",
         actualIntervalInNs, maxAvailableSamples);

  printf("Setting up trigger\n");
  PS3000A_TRIGGER_CONDITIONS_V2 triggerConditions = {
      PS3000A_CONDITION_TRUE,      // channel A
      PS3000A_CONDITION_DONT_CARE, // channel B
      PS3000A_CONDITION_DONT_CARE, // channel C
      PS3000A_CONDITION_DONT_CARE, // channel D
      PS3000A_CONDITION_DONT_CARE, // external
      PS3000A_CONDITION_DONT_CARE, // aux
      PS3000A_CONDITION_DONT_CARE, // pulse_width
      PS3000A_CONDITION_DONT_CARE, // digital
  };
  printf("Setting trigger conditions\n");
  status =
      ps3000aSetTriggerChannelConditionsV2(picoHandle, &triggerConditions, 1);
  if (status != PICO_OK)
    throw status;
  printf("Setting trigger directions\n");
  status = ps3000aSetTriggerChannelDirections(
      picoHandle, PS3000A_RISING, PS3000A_NONE, PS3000A_NONE, PS3000A_NONE,
      PS3000A_NONE, PS3000A_NONE);
  if (status != PICO_OK)
    throw status;
  int16_t maxValue;
  printf("Getting maximum value from Picoscope\n");
  status = ps3000aMaximumValue(picoHandle, &maxValue);
  if (status != PICO_OK)
    throw status;
  int16_t triggerValue = maxValue / 5. * 1.5;
  PS3000A_TRIGGER_CHANNEL_PROPERTIES triggerProperties = {
      triggerValue, 0, 0, 0, PS3000A_CHANNEL_A, PS3000A_LEVEL};
  printf("Setting trigger properties\n");
  status = ps3000aSetTriggerChannelProperties(picoHandle, &triggerProperties, 1,
                                              0, 0);
  if (status != PICO_OK)
    throw status;
}

Pico::~Pico() { ps3000aStop(picoHandle); }

void Pico::startCapture() {
  printf("Running capture\n");
  int32_t timeIndisposedAfterCapture;
  PICO_STATUS status =
      ps3000aRunBlock(picoHandle, noSamplesBefore, noSamplesAfter, timebase, 0,
                      &timeIndisposedAfterCapture, 0, NULL, NULL);
  if (status != PICO_OK)
    throw status;
  printf("Capture started, afterwards the scope will take %dms to copy\n",
         timeIndisposedAfterCapture);
}

std::vector<short> Pico::retrieveData() {
  printf("Retrieving data, waiting for capture to end\n");
  int16_t ready = 0;
  PICO_STATUS status;
  do {
    status = ps3000aIsReady(picoHandle, &ready);
    if (status != PICO_OK)
      throw status;
    if(!ready)
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (!ready);

  printf("Capture is done\n");

  // create buffer for the result
  printf("Setting data buffer\n");
  std::vector<short> buffer(numSamples, 0);
  status = ps3000aSetDataBuffer(picoHandle, PS3000A_CHANNEL_B, buffer.data(),
                                numSamples, 0, PS3000A_RATIO_MODE_NONE);
  if (status != PICO_OK)
    throw status;

  printf("Getting values\n");
  int16_t overflow;
  status = ps3000aGetValues(picoHandle, 0, &numSamples, 1,
                            PS3000A_RATIO_MODE_NONE, 0, &overflow);
  if (status != PICO_OK)
    throw status;
  printf("%d samples returned\n", numSamples);
  if (overflow)
    printf("an overflow occured: %04x\n", overflow);
  return buffer;
}
