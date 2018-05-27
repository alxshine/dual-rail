#ifndef DUAL_RAIL
#define DUAL_RAIL

#include "lut_xor.h"
#include "lut_add.h"
#include "lut_mult.h"
#include "lut_sbox.h"

#define ENCODED_TYPE unsigned char
#define ENCODED_MASK 128
#define PLAIN_TYPE unsigned char
#define PLAIN_MASK 8
#define RADIX 4

ENCODED_TYPE encode(PLAIN_TYPE src){
	ENCODED_TYPE ret = 0;

	char bit = (src & PLAIN_MASK) > 0;
	src <<= 1;
	ret += bit;
	ret <<= 1;
	ret += !bit;

	for(int i = 0; i< RADIX - 1; i++){
		bit = (src & PLAIN_MASK) > 0;
		src <<= 1;

		ret <<= 1;
		ret += bit;
		ret <<= 1;
		ret += !bit;
	}
	return ret;
}

PLAIN_TYPE decode(ENCODED_TYPE src){
	PLAIN_TYPE ret = 0;

	char bit = (src & ENCODED_MASK) > 0;
	ret += bit;

	for(int i=0; i< RADIX - 1; i++){
		ret <<= 1;
		src <<= 2;
		bit = (src & ENCODED_MASK) > 0;
		ret += bit;
	}
	return ret;
}

ENCODED_TYPE dual_xor(ENCODED_TYPE lhs, ENCODED_TYPE rhs){
	int index = (lhs<<8) + rhs;
	return d_xor[index];
}

ENCODED_TYPE dual_add(ENCODED_TYPE lhs, ENCODED_TYPE rhs){
	int index = (lhs<<8) + rhs;
	return d_add[index];
}

ENCODED_TYPE dual_mult(ENCODED_TYPE lhs, ENCODED_TYPE rhs){
	int index = (lhs<<8) + rhs;
	return d_mult[index];
}



#endif
