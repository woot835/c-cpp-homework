#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

int main() {
	

	char *buffer = NULL;
	int filesize;
	int stringsize;
	int i;
	int countOfPairs = 1;
	FILE *input = fopen("input.txt", "r");

	fseek(input, 0, SEEK_END);
	filesize = ftell(input);
	
	rewind(input);
	buffer = (char*) malloc(sizeof(char) * (filesize + 1));
	stringsize = fread(buffer, sizeof(char), filesize, input);
	
	buffer[filesize] = '\0';
	fclose(input);

	for (i = 0; i < stringsize; i++) {
		if (buffer[i] == ';') {
			countOfPairs++;
		}
	}

	if (countOfPairs == 1) {
		free(buffer);
		getchar();
		return 0;
	}

	int* keys = (int*) malloc(sizeof(int) * countOfPairs);
	int* values = (int*)malloc(sizeof(int) * countOfPairs);

	int k = 0;
	int startChar = 0;
	int isKey = 1;
	int pairsParsed = 0;
	for (i = 0; i < stringsize; i++) {
		if (buffer[i] == ';' || buffer[i] == ',' || i == stringsize - 1) {
			int endChar = i - 1;
			if (i == stringsize - 1) {
				endChar = i;
			}
			int length = endChar - startChar + 1;
			char *subbuf = (char*)malloc(sizeof(char) * (length + 1));
			for (k = 0; k < length; k++) {
				subbuf[k] = buffer[startChar + k];
			}
			subbuf[length + 1] = '\0';

			if (isKey) {
				keys[pairsParsed] = atoi(subbuf);
				isKey = 0;
			}
			else {
				values[pairsParsed] = atoi(subbuf);
				isKey = 1;
				pairsParsed++;
			}

			startChar = i + 1;
		}
	}

	int x, y;
	for (x = 0; x < countOfPairs - 1; x++) {
		for (y = x + 1; y < countOfPairs; y++) {
			if (keys[x] > keys[y]) {
				int temp = keys[x];
				keys[x] = keys[y];
				keys[y] = temp;

				temp = values[x];
				values[x] = values[y];
				values[y] = temp;
			}
		}
	}

	int hadprev = 0;
	for (i = 1; i < countOfPairs; i++) {
		int dif = values[i - 1] - values[i];
		if (dif < 0) dif = dif * -1;
		if (hadprev) {
			printf(",");
		}
		printf("%d", dif);
		hadprev = 1;
	}

	free(keys);
	free(values);
	free(buffer);
	getchar();
	return 0;
}
