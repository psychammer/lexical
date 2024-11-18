#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

char* getContent(char* filePath);

int main(void){


    token* myToken = token_init(TOKEN_ID, "myVariable");

    // printf("%d %s", myToken->type, myToken->value);

    char* content = getContent("./sample.ri");
    lexer* myLexer = lexer_init(content);

    // printf("my content: %s %d %c\n", myLexer->content, myLexer->i, myLexer->current_char);

    while(myLexer->current_char!=EOF && myLexer->i < strlen(myLexer->content)){
        token* token_instance = token_buffer(myLexer);
        printf("token: %d, value: %s\n", token_instance->type, token_instance->value);
    }
    

    return 0;
}










char* getContent(char* filePath){
    FILE *fptr;

    char ch;

    fptr = fopen(filePath, "r");

    if(fptr == NULL){
        return NULL;
    }

    char* content = malloc(sizeof(char));
    while((ch=fgetc(fptr)) != EOF){
        char* char_as_string = malloc(sizeof(char)+1);
        char_as_string[0] = ch;
        char_as_string[1] = '\0';

        content = realloc(content, strlen(content)+ strlen(content) + 1);
        strcat(content, char_as_string);

        free(char_as_string);
    }

    return content;
}