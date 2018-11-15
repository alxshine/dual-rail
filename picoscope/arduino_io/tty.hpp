#ifndef TTY_H
#define TTY_H

#include <memory>
#include <string>

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
    return ::write(fd, &arr, N);
  };

  std::size_t read(void *buf, std::size_t nbyte);
};

#endif /* TTY_H */
