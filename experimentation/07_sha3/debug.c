# 1 "keccak.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 355 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "keccak.c" 2

# 1 "./keccak.h" 1

# 1 "./definitions.h" 1

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned int size_t;
# 7 "./keccak.h" 2

int shake128(uint8_t *, size_t, const uint8_t *, size_t);
int shake256(uint8_t *, size_t, const uint8_t *, size_t);
int sha3_224(uint8_t *, size_t, const uint8_t *, size_t);
int sha3_256(uint8_t *, size_t, const uint8_t *, size_t);
int sha3_384(uint8_t *, size_t, const uint8_t *, size_t);
int sha3_512(uint8_t *, size_t, const uint8_t *, size_t);
# 10 "keccak.c" 2

void clear_mem(uint8_t *dest, char ch, unsigned int count) {
  for (unsigned int i = 0; i < count; ++i)
    dest[i] = ch;
}

static const uint8_t rho[24] = {1,  3,  6,  10, 15, 21,

                                28, 36, 45, 55, 2,  14, 27, 41, 56,
                                8,  25, 43, 62, 18, 39, 61, 20, 44};
static const uint8_t pi[24] = {10, 7,  11, 17, 18, 3,

                               5,  16, 8,  21, 24, 4,  15, 23, 19,
                               13, 12, 2,  20, 14, 22, 9,  6,  1};
static const uint64_t RC[24] = {1ULL,
                                0x8082ULL,
                                0x800000000000808aULL,
                                0x8000000080008000ULL,

                                0x808bULL,
                                0x80000001ULL,
                                0x8000000080008081ULL,
                                0x8000000000008009ULL,
                                0x8aULL,
                                0x88ULL,
                                0x80008009ULL,
                                0x8000000aULL,
                                0x8000808bULL,
                                0x800000000000008bULL,
                                0x8000000000008089ULL,
                                0x8000000000008003ULL,
                                0x8000000000008002ULL,
                                0x8000000000000080ULL,
                                0x800aULL,
                                0x800000008000000aULL,
                                0x8000000080008081ULL,
                                0x8000000000008080ULL,
                                0x80000001ULL,
                                0x8000000080008008ULL};
# 47 "keccak.c"
static inline void keccakf(void *state) {
  uint64_t *a = (uint64_t *)state;
  uint64_t b[5] = {0};
  uint64_t t = 0;
  uint8_t x, y;

  for (int i = 0; i < 24; i++) {

    x = 0;
    b[x] = 0;
    y = 0;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    ;
    x += 1;
    b[x] = 0;
    y = 0;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    ;
    x += 1;
    b[x] = 0;
    y = 0;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    ;
    x += 1;
    b[x] = 0;
    y = 0;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    ;
    x += 1;
    b[x] = 0;
    y = 0;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    b[x] ^= a[x + y];
    ;
    y += 5;
    ;
    x += 1;

    x = 0;
    y = 0;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    ;
    x += 1;
    y = 0;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    ;
    x += 1;
    y = 0;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    ;
    x += 1;
    y = 0;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    ;
    x += 1;
    y = 0;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    a[y + x] ^= b[(x + 4) % 5] ^
                (((b[(x + 1) % 5]) << 1) | ((b[(x + 1) % 5]) >> (64 - 1)));
    ;
    y += 5;
    ;
    x += 1;

    t = a[1];
    x = 0;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;
    b[0] = a[pi[x]];
    a[pi[x]] = (((t) << rho[x]) | ((t) >> (64 - rho[x])));
    t = b[0];
    x++;

    y = 0;
    x = 0;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    x = 0;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    ;
    y += 5;
    x = 0;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    x = 0;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    ;
    y += 5;
    x = 0;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    x = 0;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    ;
    y += 5;
    x = 0;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    x = 0;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    ;
    y += 5;
    x = 0;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    b[x] = a[y + x];
    ;
    x += 1;
    x = 0;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    a[y + x] = b[x] ^ ((~b[(x + 1) % 5]) & b[(x + 2) % 5]);
    ;
    x += 1;
    ;
    y += 5;

    a[0] ^= RC[i];
  }
}
# 101 "keccak.c"
static inline void xorin(uint8_t *dst, const uint8_t *src, size_t len) {
  do {
    for (size_t i = 0; i < len; i += 1) {
      dst[i] ^= src[i];
    }
  } while (0);
}
static inline void setout(const uint8_t *src, uint8_t *dst, size_t len) {
  do {
    for (size_t i = 0; i < len; i += 1) {
      dst[i] = src[i];
    }
  } while (0);
}
# 117 "keccak.c"
static inline int hash(uint8_t *out, size_t outlen, const uint8_t *in,
                       size_t inlen, size_t rate, uint8_t delim) {

  uint8_t a[200];
  for(unsigned char i=0; i<200; ++i)
    a[i] = 0;

  while (inlen >= rate) {
    xorin(a, in, rate);
    keccakf(a);
    in += rate;
    inlen -= rate;
  };

  a[inlen] ^= delim;
  a[rate - 1] ^= 0x80;

  xorin(a, in, inlen);

  keccakf(a);

  while (outlen >= rate) {
    setout(a, out, rate);
    keccakf(a);
    out += rate;
    outlen -= rate;
  };
  setout(a, out, outlen);
  clear_mem(a, 0, 800);
  return 0;
}
# 156 "keccak.c"
int shake128(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  return hash(out, outlen, in, inlen, 200 - (128 / 4), 0x1f);
}
int shake256(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  return hash(out, outlen, in, inlen, 200 - (256 / 4), 0x1f);
}

int sha3_224(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  if (outlen > (224 / 8)) {
    return -1;
  }
  return hash(out, outlen, in, inlen, 200 - (224 / 4), 0x06);
}
int sha3_256(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  if (outlen > (256 / 8)) {
    return -1;
  }
  return hash(out, outlen, in, inlen, 200 - (256 / 4), 0x06);
}
int sha3_384(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  if (outlen > (384 / 8)) {
    return -1;
  }
  return hash(out, outlen, in, inlen, 200 - (384 / 4), 0x06);
}
int sha3_512(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  if (outlen > (512 / 8)) {
    return -1;
  }
  return hash(out, outlen, in, inlen, 200 - (512 / 4), 0x06);
}
