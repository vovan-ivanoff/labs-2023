#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shop.h"

// gcc main.c
// ./a.out output.bin -p (-f)
int main(int argc, char *argv[])
{
    float maxRating;
	Shop t;
	FILE *file = NULL;

	if (argc < 3) {
		printf("Usage: %s <file> <flag>\nFlags:\n-f - show all data base\n-p - show items with less rating\n <rating> - show rating below\n", argv[0]);
        return 1;
	}

	file = fopen(argv[1], "rb");

	if (file == NULL) {
		printf("Error with %s\n", argv[1]);

		return 1;
	}

	if (!strcmp(argv[2], "-f")) {
		printf("+----------------+---------------+------------+-----------------+--------------------------+\n");
		printf("|   Название     |    Артикул    |   Рейтинг  |      Цена       |      остаток на скл      |\n");
		printf("+----------------+---------------+------------+-----------------+--------------------------+\n");

		while (fread(&t, sizeof(t), 1, file) == 1) {
		    printf("|%16s|%15ld|%12f|%17ld|%26ld|\n",
                t.prod_name,
		    	t.artikul,
                t.rating,
                t.price,
                t.remaining
		    );
		    printf("+----------------+---------------+------------+-----------------+--------------------------+\n");
		}
	} else if (!strcmp(argv[2], "-p")) {
        if (argc < 4) {
            printf("Usage: %s <file> -p <rating> - show items with less rating\n rating - show rating below\n", argv[0]); 
            return 1;
        }
        maxRating = strtof(argv[3], NULL);
        printf("+----------------+---------------+------------+-----------------+--------------------------+\n");
		printf("|   Название     |    Артикул    |   Рейтинг  |      Цена       |      остаток на скл      |\n");
		printf("+----------------+---------------+------------+-----------------+--------------------------+\n");
        while (fread(&t, sizeof(t), 1, file) == 1) {
                if (t.rating < maxRating) {
                    printf("|%16s|%15ld|%12f|%17ld|%26ld|\n",
                    t.prod_name,
			    	t.artikul,
                    t.rating,
                    t.price,
                    t.remaining
			    );
                printf("+----------------+---------------+------------+-----------------+--------------------------+\n");

            }
        }
    } else {
		printf("Usage: %s <file> <flag>\nFlags:\n-f - show all data base\n-p - show items with less rating\n <rating> - show rating below\n", argv[0]);
        return 0;
    }
	fclose(file);

	return 0;
}