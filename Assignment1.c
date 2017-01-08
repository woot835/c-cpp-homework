#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>


int main() {

	FILE *input;
	input = fopen("input.txt", "r");

	int i;
	int j;
	int a;
	int b;
	int answers;
	int arrayOne[6];


	for (i = 0; i < 6; i += 2)
	{
		fscanf(input, "%d,%d;", &arrayOne[i], &arrayOne[i + 1]);

	}

	for ( i = 0; i < sizeof(arrayOne)/sizeof(int); i+=2)
	{
		for ( j = i+1; j < sizeof(arrayOne)/sizeof(int); j+=2)
		{
			if (arrayOne[i] > arrayOne[j])
			{
				a = arrayOne[i];
				b = arrayOne[i + 1];

				arrayOne[i] = arrayOne[j];
				arrayOne[i + 1] = arrayOne[j + 1];
				
				arrayOne[j] = a;
				arrayOne[j + 1] = b;
				
			}
		}
	}


	for (i = 0; i < (sizeof(arrayOne) / sizeof(int) - 2); i += 2) {
		answers = arrayOne[i + 3] - arrayOne[i + 1];
		printf("%d\n", answers);
	}
	fclose(input);

	return 0;
}
