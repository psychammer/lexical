#ifndef AST_H
#define AST_H
#include <stdlib.h>
#include "token.h"

typedef struct AST_STRUCT
{
    enum{
        AST_EXPRESSION,
        AST_TERM,
        AST_FACTOR,
        AST_COMPOUND,
        AST_NOOP // NULL OPERATION
    }type;

    /* AST_EXPRESSION */
    struct AST_STRUCT* first_term;
    char* md_operator; 
    struct AST_STRUCT* second_term;;

    /* AST_TERM */
    struct AST_STRUCT* first_factor;
    char* as_operator;
    struct AST_STRUCT* second_factor;

    /* AST_FACTOR */
    double number;
    struct AST_STRUCT* expression;

    /* AST_COMPOUND */
    struct AST_STRUCT** compound_value;
    size_t compound_size; 

    double result;
} AST_T;






AST_T* init_ast(int type)
{
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    /* AST_EXPRESSION */
    ast->first_term = (void*)0;
    ast->md_operator = (void*)0; 
    ast->second_term = (void*)0;

    /* AST_TERM */
    ast->first_factor = (void*)0;
    ast->as_operator = (void*)0;
    ast->second_factor = (void*)0;

    /* AST_FACTOR */
    ast->expression = (void*)0;

    /* AST_COMPOUND */
    ast->compound_value = (void*)0;

    ast->result = 0;
    ast->number = -1;
    return ast;

}
#endif