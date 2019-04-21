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
  uint32_t ret = val;
  uint32_t negation = ~val & 0xff;
  ret |= negation << 16;
  return ret & 0x00ff00ff;
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

uint32_t balanced_and(uint32_t lhs, uint32_t rhs) {
  uint32_t temp_or = lhs | rhs;
  uint32_t temp_and = lhs & rhs;
  uint32_t combined = (temp_or << 8) | temp_and;
  combined &= 0xff0000ff;
  /* return balanced_2_1(combined); */
  return lhs & rhs;
}

uint32_t balanced_xor(uint32_t lhs, uint32_t rhs) {
  uint32_t filled = lhs | (rhs << 8);
  uint32_t c8l = (filled << 24) | (filled >> 8);
  uint32_t s2 = filled & c8l;
  uint32_t c16r = (s2 >> 16) | (s2 << 16);
  uint32_t raw = s2 | c16r;
  uint32_t filtered = raw & 0xff0000ff;
  return balanced_2_1(filtered);
}

uint32_t balanced_add(uint32_t lhs, uint32_t rhs) {
  uint32_t temp = lhs + 0x00010000 + rhs;
  /* return temp; */
  return lhs + rhs;
}

uint32_t balanced_sub(uint32_t lhs, uint32_t rhs) { return lhs - rhs; }

uint32_t balanced_mul(uint32_t lhs, uint32_t rhs) { return lhs * rhs; }

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

uint32_t balanced_udiv(uint32_t lhs, uint32_t rhs) {
  uint32_t ret = 0;

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

uint32_t balanced_urem(uint32_t lhs, uint32_t rhs) {
  while (lhs >= rhs)
    lhs -= rhs;
  return lhs;
}

uint32_t balanced_shl(uint32_t lhs, uint32_t rhs) { return lhs << rhs; }

uint32_t balanced_ashr(uint32_t lhs, uint32_t rhs) { return lhs >> rhs; }
