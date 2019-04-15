#include "definitions.h"

int balanced_int(int constant) { return constant; }

int balanced_or(int lhs, int rhs) { return lhs | rhs; }

int balanced_and(int lhs, int rhs) { return lhs & rhs; }

int balanced_xor(int lhs, int rhs) { return lhs ^ rhs; }

int balanced_add(int lhs, int rhs) { return lhs + rhs; }

int balanced_subtract(int lhs, int rhs) { return lhs - rhs; }

int balanced_mul(int lhs, int rhs) { return lhs * rhs; }

int balanced_sdiv(int lhs, int rhs) {
  int ret = 0;
  int sign = 1;
  if (lhs < 0) {
    sign = -sign;
    lhs = -lhs;
  }
  if (rhs < 0) {
    sign = -sign;
    rhs = -rhs;
  }

  while (lhs > rhs) {
    lhs -= rhs;
    ret++;
  }
  return sign * ret;
}

unsigned int balanced_udiv(unsigned int lhs, unsigned int rhs) {
  unsigned int ret = 0;

  while (lhs > rhs) {
    lhs -= rhs;
    ret++;
  }
  return ret;
}

int balanced_srem(int lhs, int rhs) {
  int sign = 1;
  if (lhs < 0) {
    sign = -sign;
    lhs = -lhs;
  }
  if (rhs < 0) {
    sign = -sign;
    rhs = -rhs;
  }
  while (lhs > rhs)
    lhs -= rhs;

  return sign * lhs;
}

int balanced_shl(int lhs, int rhs) { return lhs << rhs; }

int balanced_ashr(int lhs, int rhs) { return lhs >> rhs; }
