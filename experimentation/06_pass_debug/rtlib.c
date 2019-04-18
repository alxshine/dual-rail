#include "definitions.h"

// scheme1: 0 | ~x | 0 | x
// scheme2: ~x | 0 | 0 | x

uint32_t balanced_1_2(uint32_t val) {
  val |= val << 8;
  return val & 0xff0000ff;
}

uint32_t balanced_2_1(uint32_t val) {
  uint32_t temp = val >> 8;
  temp |= val << 24;
  temp |= val;
  return temp & 0x00ff00ff;
}

// balances to scheme1
uint32_t balanced_int(uint8_t val) {
  uint32_t negation = ~val;
  uint32_t ret = val << 16;
  ret |= val;
  return ret;
}

uint32_t balanced_constant(uint32_t constant) { return constant; }

uint8_t unbalanced_int(uint32_t val) { return val & 0xff; }

uint32_t balanced_or(uint32_t lhs, uint32_t rhs) {
  uint32_t temp_or = lhs | rhs;
  uint32_t temp_and = lhs & rhs;
  uint32_t combined = (temp_and << 8) | temp_or;
  combined &= 0xff0000ff;
  /* return balanced_2_1(combined); */
  return lhs | rhs;
}

int balanced_and(int lhs, int rhs) {
  uint32_t temp_or = lhs | rhs;
  uint32_t temp_and = lhs & rhs;
  uint32_t combined = (temp_or << 8) | temp_and;
  combined &= 0xff0000ff;
  /* return balanced_2_1(combined); */
  return lhs & rhs;
}

int balanced_xor(int lhs, int rhs) { return lhs ^ rhs; }

int balanced_add(int lhs, int rhs) { return lhs + rhs; }

int balanced_sub(int lhs, int rhs) { return lhs - rhs; }

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

  while (lhs >= rhs) {
    lhs -= rhs;
    ret++;
  }
  return sign * ret;
}

unsigned int balanced_udiv(unsigned int lhs, unsigned int rhs) {
  unsigned int ret = 0;

  while (lhs >= rhs) {
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
  while (lhs >= rhs)
    lhs -= rhs;

  return sign * lhs;
}

int balanced_urem(int lhs, int rhs) {
  while (lhs >= rhs)
    lhs -= rhs;
  return lhs;
}

int balanced_shl(int lhs, int rhs) { return lhs << rhs; }

int balanced_ashr(int lhs, int rhs) { return lhs >> rhs; }
