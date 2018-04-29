#include <stdio.h>

#include "dual-rail.h"

int main(void){
	int radix = 4;
	for(int i=0; i<1<<(radix-1); i++){
		for(int j=0; j<1<<(radix-1); j++){
			unsigned char lhs, rhs, res, decoded;
			lhs = encode(i);
			rhs = encode(j);
			res = dual_xor(lhs, rhs);
			decoded = decode(res);
			if(decoded != (i^j))
				fprintf(stderr, "%d/%d is not evaluated correctly", i, j);
		}
	}
}
