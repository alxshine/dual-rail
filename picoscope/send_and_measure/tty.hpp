#ifndef TTY_H
#define TTY_H

#include <memory>
#include <string>
#include <exception>
#include <sstream>
#include <iomanip>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

class Tty {
private:
  int fd;
  struct termios oldConfig;

public:
  Tty(std::string deviceName, int baudRateFlag);
  virtual ~Tty();

  std::size_t write(std::string s);
  template <typename T, size_t N> std::size_t write(T (&arr)[N]) {
    std::stringstream stream;
    for(unsigned i=0; i<N; i++){
      stream << std::setfill('0') << std::setw(3) << ((int) arr[i] & 0xff);
      if(i<N-1)
        stream << ",";
    }
    std::string tempString;
    stream >> tempString;
    tempString += "\n";

    return ::write(fd, tempString.c_str(), tempString.length());
  };

  std::size_t read(void *buf, std::size_t nbyte);
};

#endif /* TTY_H */
