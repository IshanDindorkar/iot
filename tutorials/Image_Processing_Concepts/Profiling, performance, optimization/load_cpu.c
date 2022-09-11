#include <stdio.h>
#include <stdlib.h>

int main() {

	unsigned int i, j, k = 0;
	for (i = 0; i < 9000; i++) {
		for (j = 0; j < 9000; j++) {
			k += i + j;
		}
	}
}
