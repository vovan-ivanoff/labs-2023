#include <stdio.h>
#include "shop.h"
// gcc convert_to_binary.c 
// ./a.out output.bin data.txt
int main(int argc, char *argv[]) {
	Shop t;
	FILE *file_out = NULL;
    FILE *file_in = NULL;

	if (argc != 3) {
		printf("Usage: %s <tsv_file> <output_binary>\n", argv[0]);
		return 1;
	}

	file_out = fopen(argv[2], "wb");
	if (file_out == NULL) {
		printf("Error with %s\n", argv[1]);
		return 1;
	}
    file_in = fopen(argv[1], "r");
    if (file_in == NULL) {
		printf("Error with %s\n", argv[2]);
		return 1;
	}

    while (!feof(file_in)) {
        int res = fscanf(file_in, "%s %ld %f %ld %d",
		t.prod_name,
		&t.artikul,
		&t.rating,
		&t.price,
        &t.remaining
		);
        if (res != EOF) fwrite(&t, sizeof(t), 1, file_out);
    }
	fclose(file_out);
    fclose(file_in);
	return 0;
}