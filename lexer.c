#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

char* getContent(char* filePath);
char* getTokenType(int tokenTypeInt);

int main(void){


    token* myToken = token_init(TOKEN_ID, "myVariable");

    // printf("%d %s", myToken->type, myToken->value);

    char* content = getContent("./sample.ri");
    lexer* myLexer = lexer_init(content);

    // printf("my content: %s %d %c\n", myLexer->content, myLexer->i, myLexer->current_char);

    int size = 0;
    token* token_arr = malloc(sizeof(token));
    while(myLexer->current_char!=EOF && myLexer->i < strlen(myLexer->content)){
        token* token_instance = token_buffer(myLexer);

        if(token_instance->value != NULL){
            size++;

            // Resize token array
            token* temp = realloc(token_arr, size * sizeof(token));
            token_arr = temp;

            // Copy token instance data
            token_arr[size - 1].type = token_instance->type;
            token_arr[size - 1].value = strdup(token_instance->value);
        }
        
    }

    // printf("size of token: %d", size);


    for(int i = 0; i < size; i++) {
        printf("token: %s, value: %s\n", getTokenType(token_arr[i].type), token_arr[i].value);
    }

    // FILE *file = fopen("tokens_out.bin", "wb");
    // if (file == NULL) {
    //     perror("Failed to open file");
    //     return 1;
    // }

    // size = sizeof(token_arr)/sizeof(token_arr[0]);

    // fwrite(&size, sizeof(size), 1, file);

    // printf("%d", size);

    // for (int i = 0; i < size; i++) {
    //     fwrite(&token_arr[i], sizeof(token), 1, file);
    // }

    // fclose(file);

    // free(token_arr);
    

    return 0;
}




 char* getTokenType(int tokenTypeInt) {
    switch (tokenTypeInt) {
        case 0: return "TOKEN_ID"; break;
        case 1: return "TOKEN_EQUALS"; break;
        case 2: return "TOKEN_STRING"; break;
        case 3: return "TOKEN_SYMBOL"; break;
        case 4: return "TOKEN_SEMI"; break;
        case 5: return "TOKEN_LPAREN"; break;
        case 6: return "TOKEN_RPAREN"; break;
        case 7: return "TOKEN_RBRACE"; break;
        case 8: return "TOKEN_LBRACE"; break;
        case 9: return "TOKEN_LBRACKET"; break;
        case 10: return "TOKEN_RBRACKET"; break;
        case 11: return "TOKEN_COMMA"; break;
        case 12: return "TOKEN_COLON"; break;
        case 13: return "TOKEN_TILDE"; break;
        case 14: return "TOKEN_QUESTION";  break;
        case 15: return "TOKEN_EXCLAMATION"; break;
        case 16: return "TOKEN_AMPERSAND"; break;
        case 17: return "TOKEN_DOT"; break;
        case 18: return "TOKEN_EOF";break;
        case 19: return "TOKEN_OPERATOR";break;
        case 20: return "TOKEN_KEYWORD";break;
        case 27: return "TOKEN_RESERVEDWORDS";break;
        case 28: return "TOKEN_DATATYPE";break;
        case 29: return "TOKEN_INT";break;
        case 30: return "TOKEN_FLOAT";break;
        case 31: return "TOKEN_DOUBLE";break;
        case 32: return "TOKEN_CHAR";break;
        case 33: return "TOKEN_VOID";break;
        case 34: return "TOKEN_BOOL";break;
        case 35: return "TOKEN_SINGLECOMMENT";break;
        case 36: return "TOKEN_MULTICOMMENT";break;
        case 37: return "TOKEN_NUMBER";break;
        default: return "UNKNOWN_TOKEN";break;
    }
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