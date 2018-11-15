#include <iostream>
#include <fstream>
#include <string>

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

  Tty t{DEVICE, BAUDRATE};
  Pico p;

  ofstream plaintextStream{"plaintexts.csv", ios::trunc};
  ofstream traceStream{"traces.csv", ios::trunc};

  char buffer[16];
  for(auto i = 0; i<atoi(argv[1]); i++){
    randFill(buffer, 16);
    for(auto j = 0; j<16; j++){
      plaintextStream << buffer[j];
      if(j < 15)
        plaintextStream << ",";
    }
    plaintextStream << endl;
    plaintextStream.flush();

    p.startCapture();
    t.write(buffer);
    auto trace = p.retrieveData();
    auto size = trace.size();
    for (unsigned k = 0; k < size; ++k) {
      traceStream << trace[k];
      if(k < size -1)
        traceStream << ",";
    }
    traceStream << endl;
    traceStream.flush();
  }

  return 0;
}
