#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "lexer.h"
#include "AST.h"


typedef struct PARSER_STRUCT
{
    lexer* lexer;
    token* current_token;
    token* prev_token;
} parser_T;

AST_T* parser_parse_statements(parser_T* parser);

parser_T* init_parser(lexer* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = token_buffer(lexer);
    parser->prev_token = parser->current_token;
    return parser;
}

void parser_eat(parser_T* parser, int token_type)
{
    if (parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = token_buffer(parser->lexer);
    }
    else
    {
        printf("Unexpected token '%s', with type '%d'",
                parser->current_token->value,
                parser->current_token->type
        );
        exit(1);
    }

}

AST_T* parser_parse(parser_T* parser) // returns the whole AST tree
{
    
    return parser_parse_statements(parser);
}


// AST_T* parser_parse_factor(parser_T* parser)
// {
//     AST_T* factor = init_ast(AST_FACTOR);

//     if(parser->current_token->type==TOKEN_NUMBER){
//         double num = atof(parser->current_token->value); 
        
//         parser_eat(parser, TOKEN_NUMBER);

//         factor->number = num;
//         return factor;
//     }
//     else if(parser->current_token->type==TOKEN_LPAREN)
//     {

//     }
//     else{
//         return (void*)0;
//     }

//     return factor;
// }

static AST_T* parser_factor(parser_T* parser) {
    AST_T* node = calloc(1, sizeof(AST_T));

    if (parser->current_token->type == TOKEN_NUMBER) {
        node->type = AST_FACTOR;
        node->number = atof(parser->current_token->value);
        parser_eat(parser, parser->current_token->type);
    }
    return node;
}



// AST_T* parser_parse_term(parser_T* parser)
// {

//     AST_T* term = init_ast(AST_TERM);

//     AST_T* first_factor = parser_parse_factor(parser);
//     term->first_factor = first_factor;

//     if(parser->current_token != (void*)0 && (*parser->current_token->value) == '*')
//     {
//         term->md_operator = parser->current_token->value;

//         parser_eat(parser, TOKEN_OPERATOR);

//         AST_T* second_factor = parser_parse_term(parser);
//         term->second_factor = second_factor;
//     }

//     return term;
// }

static AST_T* parser_term(parser_T* parser) {
    AST_T* node = parser_factor(parser);

    while (parser->current_token != (void*)0 && (*parser->current_token->value) == '*') {
        AST_T* new_node = calloc(1, sizeof(AST_T));
        new_node->type = AST_TERM;
        new_node->first_factor = node;
        new_node->md_operator = parser->current_token->value; // Store operator string
        parser_eat(parser, parser->current_token->type);
        new_node->second_factor = parser_factor(parser);
        node = new_node;
    }
    return node;
}



// AST_T* parser_parse_expression(parser_T* parser)
// {
//     AST_T* expression = init_ast(AST_EXPRESSION);

//     AST_T* first_term = parser_parse_term(parser);
//     expression->first_term = first_term;
//     double resultant = first_term->result;

//     if(parser->current_token != (void*)0 && (*parser->current_token->value) == '+')
//     {
//         expression->as_operator = parser->current_token->value;
//         parser_eat(parser, TOKEN_OPERATOR);

//         AST_T* second_term = parser_parse_term(parser);
//         expression->second_term = second_term;
//     }

//     return expression;
// }


static AST_T* parser_expression(parser_T* parser) {
    AST_T* node = parser_term(parser);

    while (parser->current_token != (void*)0 && (*parser->current_token->value) == '+') {
        AST_T* new_node = calloc(1, sizeof(AST_T));
        new_node->type = AST_EXPRESSION;
        new_node->first_term = node;
        new_node->as_operator = parser->current_token->value; // Store operator string
        parser_eat(parser, parser->current_token->type);
        new_node->second_term = parser_term(parser);
        node = new_node;
    }
    return node;
    
}



// <stmt>
AST_T* parser_parse_statement(parser_T* parser)
{
    switch(parser->current_token->type)
    {
        case TOKEN_NUMBER: return parser_expression(parser);
    }

    return init_ast(AST_NOOP);
}

// <stmt-list> ... ROOT NODE
AST_T* parser_parse_statements(parser_T* parser)
{
    AST_T* compound = init_ast(AST_COMPOUND); // create a node for statements
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*)); // allocate memory for an array of statements

    AST_T* ast_statement = parser_parse_statement(parser); // create a node for individual statement
    compound->compound_value[0] = ast_statement; // assign the single statement to the array of statements
    compound->compound_size += 1; // increase the size/number of array statements

    // while (parser->current_token->type == TOKEN_SEMI){ // continue doing so after encountering a semi. Meaning there might be another statements
    //     parser_eat(parser, TOKEN_SEMI);

    //     AST_T* ast_statement = parser_parse_statement(parser);

    //     if (ast_statement)
    //     {
    //         compound->compound_size += 1; 
    //         compound->compound_value = realloc(compound->compound_value, 
    //                                         compound->compound_size *sizeof(struct AST_STRUCT*));
    //         compound->compound_value[compound->compound_size-1] = ast_statement;
    //     }
       
    // }
    return compound;
}

#endif