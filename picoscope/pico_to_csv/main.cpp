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
  Pico p;
  auto trace = p.runBlockingCapture();
  return 0;
}
