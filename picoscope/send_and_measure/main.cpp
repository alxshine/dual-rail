#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#include "tty.hpp"
#include "tty_utils.hpp"
#include "pico.hpp"

#define BAUDRATE B115200
#define DEVICE "/dev/ttyACM0"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 2){
    cout << "Usage: " << argv[0] << " numPlaintexts";
    return 1;
  }

  Pico p;

  ofstream traceStream{"traces.csv", ios::trunc};

  for(auto i = 0; i<atoi(argv[1]); i++){
    cout << "Run " << i+1 << endl;

    p.startCapture();
    auto trace = p.retrieveData();
    auto size = trace.size();
    for (unsigned k = 0; k < size; ++k) {
      traceStream << trace[k];
      if(k < size -1)
        traceStream << ",";
    }
    traceStream << endl;
  }

  return 0;
}
