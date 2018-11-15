#include "tty.hpp"

Tty::Tty(std::string deviceName, int baudRateFlag) {
  fd = open(deviceName.c_str(), O_RDWR);
  if (fd < 0) {
    throw "could not open device " + deviceName; //TODO: throw exception
  }
  struct termios newConfig = {};
  newConfig.c_cflag = baudRateFlag | CS8 | CREAD;
  newConfig.c_iflag = IGNPAR;
  newConfig.c_oflag = 0;
  newConfig.c_lflag = 0;

  newConfig.c_cc[VTIME] = 0; // inter-character timer unused
  newConfig.c_cc[VMIN] = 4;  // blocking read until 5 chars received

  tcgetattr(fd, &oldConfig);
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newConfig);
}

std::size_t Tty::write(std::string s) {
  return ::write(fd, s.c_str(), s.length());
}

std::size_t Tty::read(void *buf, std::size_t nbyte) {
  return ::read(fd, buf, nbyte);
}

Tty::~Tty() {
  tcsetattr(fd, TCSANOW, &oldConfig);
  close(fd);
}
