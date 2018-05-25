#include <stdio.h>

#include "dual-rail.h"

int main(void){
	int radix = 4;
	unsigned char lhs, rhs, res, decoded, desired;
	int correct = 1;
	for(int i=0; i<1<<(radix-1); i++){
		for(int j=0; j<1<<(radix-1); j++){
			lhs = encode(i);
			rhs = encode(j);
			//xor
			res = dual_xor(lhs, rhs);
			decoded = decode(res);
			desired = i^j;
			if(decoded != desired){
				fprintf(stderr, "%d^%d is not evaluated correctly\n", i, j);
				correct = 0;
			}

			res = dual_add(lhs, rhs);
			decoded = decode(res);
			desired = (i+j)&15;
			if(decoded != desired){
				fprintf(stderr, "%d+%d is not evaluated correctly\n", i, j);
				correct = 0;
			}

			res = dual_mult(lhs, rhs);
			decoded = decode(res);
			desired = (i*j)&15;
			if(decoded != desired){
				fprintf(stderr, "%d*%d is not evaluated correctly: is %d but should be %d; res: %02x\n", i, j, decoded, (i*j)&15, res);
				correct = 0;
			}
		}
	}
	printf("%s!", correct ? "SUCCESS" : "FAILURE");
}
