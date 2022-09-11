#include <stdio.h>
#include <stdlib.h>

int main() {

	unsigned int i;
	for (i = 0; i < 3000; i++) {
		FILE *fp = fopen("temp.txt", "w+");
		fprintf(fp, "Hello %d\n", i);
		fclose(fp);
	}
}
