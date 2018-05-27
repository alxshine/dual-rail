#include <stdio.h>

#include "dual-rail.h"
#include "s_box.h"

int main(void){
	int radix = 4;
	unsigned char lhs, rhs, res, decoded, desired, operand;
	int correct = 1;
	for(int i=0; i<1<<(radix-1); i++){
		lhs = encode(i);
		for(int j=0; j<1<<(radix-1); j++){
			rhs = encode(j);
			
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
				fprintf(stderr, "%d*%d is not evaluated correctly: is %d but should be %d; res: %02x\n", i, j, decoded, desired, res);
				correct = 0;
			}
		}
	}
	printf("%s!\n", correct ? "SUCCESS" : "FAILURE");
}
