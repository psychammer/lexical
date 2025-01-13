#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "AST.h"

void visit_expression(AST_T* node);
void visit_term(AST_T* node);
void visit_factor(AST_T* node);

void print_ast_prefix(AST_T* node);
double evaluate_ast(AST_T* node);

char* getContent(char* filePath);
char* getTokenType(int tokenTypeInt);

int main(int argc, char *argv[]){

    token* myToken = token_init(TOKEN_ID, "myVariable");

    char* filePath = argv[1];

    if(filePath[strlen(filePath)-2]!='r' && filePath[strlen(filePath)-1]!='i'){
        printf("Incorrect file format.\n");
        return 1;
    }

    char* content = getContent(filePath);

    if(content==NULL){
        printf("Fail to read file.\n");
        return 1;
    }

    lexer* myLexer = lexer_init(content);



    int size = 0;
    token* token_arr = malloc(sizeof(token));
    
        parser_T* parser = init_parser(myLexer);
        AST_T* root = parser_parse(parser);
        // print_ast_prefix(root->compound_value[0]);
        // double result = evaluate_ast(root->compound_value[0]);
        // printf("\n%lf\n", result);

        // token* token_instance = token_buffer(myLexer);

        // if(token_instance->value != NULL){
        //     size++;

        //     // Resize token array
        //     token* temp = realloc(token_arr, size * sizeof(token));
        //     token_arr = temp;

        //     // Copy token instance data
        //     token_arr[size - 1].type = token_instance->type;
        //     token_arr[size - 1].value = strdup(token_instance->value);
        // }
        
    

    // printf("size of token: %d", size);

    // FILE *file = fopen(argv[2], "w");
    // if (file == NULL) {
    //     perror("Error opening file");
    //     return 1;
    // }


    // for(int i = 0; i < size; i++) {
    //     fprintf(file, "%s, %s\n", getTokenType(token_arr[i].type), token_arr[i].value);
    // }

    // fclose(file);
    
    
    return 0;
}

// void visit_expression(AST_T* node)
// {
//     if(node->first_term != (void*)0)
//     {
//         visit_term(node->first_term);
//     }
//     printf("%s", node->as_operator);
//     if(node->second_term != (void*)0)
//     {
//         visit_term(node->second_term);
//     }
// }

// void visit_term(AST_T* node)
// {
//     if(node->first_factor != (void*)0)
//     {
//         visit_factor(node->first_factor);
//     }
//     printf("%s", node->md_operator);
//     if(node->second_factor != (void*)0)
//     {
//         visit_factor(node->second_factor);
//     }
// }

// void visit_factor(AST_T* node)
// {
//     printf("%lf", node->number);
// }



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
        case TOKEN_IF: return "TOKEN_IF"; break;
        case TOKEN_ELSE: return "TOKEN_ELSE"; break;
        case TOKEN_WHILE: return "TOKEN_WHILE"; break;
        case TOKEN_DO: return "TOKEN_DO"; break;
        case TOKEN_RETURN: return "TOKEN_RETURN"; break;
        case TOKEN_FOR: return "TOKEN_FOR"; break;
        case TOKEN_CASE: return "TOKEN_CASE"; break;
        case TOKEN_BREAK: return "TOKEN_BREAK"; break;
        case TOKEN_TRY: return "TOKEN_TRY"; break;
        case TOKEN_CATCH: return "TOKEN_CATCH"; break;


        case 31: return "TOKEN_RESERVEDWORDS";break;
        case 32: return "TOKEN_DATATYPE";break;
        case 33: return "TOKEN_INT";break;
        case 34: return "TOKEN_FLOAT";break;
        case 35: return "TOKEN_DOUBLE";break;
        case 36: return "TOKEN_CHAR";break;
        case 37: return "TOKEN_VOID";break;
        case 38: return "TOKEN_BOOL";break;
        case 39: return "TOKEN_SINGLECOMMENT";break;
        case 40: return "TOKEN_MULTICOMMENT";break;
        case 41: return "TOKEN_NUMBER";break;
        case TOKEN_CHECK: return "TOKEN_CHECK"; break;
        case TOKEN_ELIF: return "TOKEN_ELIF"; break;
        case TOKEN_ENDLOOP: return "TOKEN_ENDLOOP"; break;
        case TOKEN_FUNCTION: return "TOKEN_FUNCTION"; break;
        case TOKEN_LOOP: return "TOKEN_LOOP"; break;
        case TOKEN_OTHERWISE: return "TOKEN_OTHERWISE"; break;
        case TOKEN_PRINTOUT: return "TOKEN_PRINTOUT"; break;
        case TOKEN_SWITCH: return "TOKEN_SWITCH"; break;
        case TOKEN_TERMINATE: return "TOKEN_TERMINATE"; break;
        case TOKEN_TERMINATEALL: return "TOKEN_TERMINATEALL"; break; 
        default: return "UNKNOWN_TOKEN";break;
    }
}



void print_ast_prefix(AST_T* node) {
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case AST_EXPRESSION:
            printf("%s ", node->as_operator); // Operator first
            print_ast_prefix(node->first_term);
            printf(" "); // Space between operands
            print_ast_prefix(node->second_term);
            break;
        case AST_TERM:
            printf("%s ", node->md_operator); // Operator first
            print_ast_prefix(node->first_factor);
            printf(" "); // Space between operands
            print_ast_prefix(node->second_factor);
            break;
        case AST_FACTOR:
            printf("%f", node->number);
            break;
        case AST_COMPOUND:
            printf("{ ");
            for (size_t i = 0; i < node->compound_size; i++) {
                print_ast_prefix(node->compound_value[i]);
                if (i < node->compound_size - 1) {
                    printf(", ");
                }
            }
            printf(" }");
            break;
        case AST_NOOP:
            printf("NOOP");
            break;
        default:
            printf("UNKNOWN");
            break;
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



double evaluate_ast(AST_T* node) {
    if (node == NULL) {
        return 0; // Or handle error as needed
    }

    switch (node->type) {
        case AST_EXPRESSION:
            if (strcmp(node->as_operator, "+") == 0) {
                return evaluate_ast(node->first_term) + evaluate_ast(node->second_term);
            } else if (strcmp(node->as_operator, "-") == 0) {
                return evaluate_ast(node->first_term) - evaluate_ast(node->second_term);
            }
            // Add other operators as needed (e.g., ^ for exponentiation)
            break;
        case AST_TERM:
            if (strcmp(node->md_operator, "*") == 0) {
                return evaluate_ast(node->first_factor) * evaluate_ast(node->second_factor);
            } else if (strcmp(node->md_operator, "/") == 0) {
                double divisor = evaluate_ast(node->second_factor);
                if (divisor == 0) {
                    printf("Error: Division by zero\n");
                    exit(1); // Or handle error appropriately
                }
                return evaluate_ast(node->first_factor) / divisor;
            }
            break;
        case AST_FACTOR:
            return node->number;
        case AST_COMPOUND:
            // Handle compound statements if needed (e.g., return the result of the last statement)
            if (node->compound_size > 0)
                return evaluate_ast(node->compound_value[node->compound_size - 1]);
            else
                return 0;
            break;
        case AST_NOOP:
            return 0;
        default:
            printf("Error: Unknown AST node type\n");
            exit(1);
    }
    return 0; // Should not reach here in normal cases
}
