#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

int main() {
    FILE *file = fopen("tokens_out.bin", "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Read the size of the array
    int size;
    fread(&size, sizeof(size), 1, file);

    printf("size is: %d", size);
    // Dynamically allocate memory for the tokens
    token *token_arr = malloc(size * sizeof(token));
    if (token_arr == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return 1;
    }

    // Read the tokens
    fread(token_arr, sizeof(token), size, file);

    fclose(file);

    for (int i = 0; i < size; i++) {
        printf("Token %d: Name=%s\n", token_arr[i].type, token_arr[i].value);
    }

    free(token_arr); 
    return 0;
}
