#ifndef lexer_h
#define lexer_h

typedef struct lexer_struct{
    char current_char;
    int i;
    char* content;

}lexer;

token* isKeyword(lexer* myLexer, token* myToken, char* valueToCheck);
char* char_to_string(char ch);

lexer* lexer_init(char* content){
    lexer* myLexer = malloc(sizeof(lexer));
    myLexer->content = content;
    myLexer->i = 0;
    myLexer->current_char = content[myLexer->i];

    return myLexer;
}

int is_comment(lexer* myLexer){
    char next_char = myLexer->content[myLexer->i+1];
    char next_two_char = myLexer->content[myLexer->i+2];

    if(myLexer->current_char == '/'){
        if(next_char=='/'){
            return 1;
        }
        else if(next_char=='*'){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(myLexer->current_char == '#'){
        return 1;
    }
    else if(myLexer->current_char == '*' && next_char =='/'){
        return 1;
    }
    else if(myLexer->current_char == '"' && next_char =='"' && next_two_char == '"'){
        return 1;
    }
    else{
        return 0;
    }
    
}

int is_operator(char ch){
    // char next_char = myLexer->content[myLexer->i+1];
    switch(ch){
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 1; break;
        case '/': return 1; break;
        case '%': return 1; break;

        case '=': return 1; break;
        case '>': return 1; break;
        case '<': return 1; break;
        case '!': return 1; break;

        default: return 0;
    }

}


void advance_lexer(lexer* myLexer){
    if(myLexer->i < strlen(myLexer->content)){
        myLexer->i += 1;
        myLexer->current_char = myLexer->content[myLexer->i];
    }
}

void skip_whitespace(lexer* myLexer){
    while(myLexer->current_char == ' ' || myLexer->current_char == 10 || myLexer->current_char == 13){
        advance_lexer(myLexer);
    }
}

token* get_identifier_token(lexer* myLexer){
    token* myToken = malloc(sizeof(token));

    switch(myLexer->current_char){

        case 't':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='r'){
                return isKeyword(myLexer, myToken,"rue");
            }
            else return isKeyword(myLexer, myToken, "ry"); break;
        
        case 'f': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='a'){
                return isKeyword(myLexer, myToken, "alse");
            }
            else if(myLexer->current_char=='u'){
                return isKeyword(myLexer, myToken, "unction");
            }
            else{
                return isKeyword(myLexer, myToken, "or");
            }
            break;

        case 'c': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='a'){
                myToken->value = realloc(myToken->value, strlen(myToken->value)+2);
                strcat(myToken->value, char_to_string(myLexer->current_char));
                advance_lexer(myLexer);

                if(myLexer->current_char=='s'){
                    return isKeyword(myLexer, myToken, "se"); 
                }
                else{
                    return isKeyword(myLexer, myToken, "tch"); 
                }
            }
            break;

        case 'e': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='l'){
                myToken->value = realloc(myToken->value, strlen(myToken->value)+2);
                strcat(myToken->value, char_to_string(myLexer->current_char));
                advance_lexer(myLexer);

                if(myLexer->current_char=='i'){
                    return isKeyword(myLexer, myToken, "if"); 
                }
                else{
                    return isKeyword(myLexer, myToken, "se"); 
                }
            }
            break;

        case 'i':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='f'){
                return isKeyword(myLexer, myToken,"f");
            }
            break;

        case 'w':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='h'){
                return isKeyword(myLexer, myToken,"hile");
            }
            break;

        case 'd':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='o'){
                return isKeyword(myLexer, myToken,"o");
            }
            break;

        case 'r':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='e'){
                return isKeyword(myLexer, myToken,"eturn");
            }
            break;

        case 'b':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            if(myLexer->current_char=='r'){
                return isKeyword(myLexer, myToken,"reak");
            }
            break;

        default:
            break;
    }

    char* string_buffer = malloc(sizeof(char));
    string_buffer[0] = '\0';
    while(isalnum(myLexer->current_char) ||  myLexer->current_char=='_'){
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';

        string_buffer = realloc(string_buffer, strlen(string_buffer) + strlen(current_char_as_string) + 1);

        strcat(string_buffer, current_char_as_string);
        advance_lexer(myLexer);
    }
    
    myToken->value = string_buffer;
    myToken->type = TOKEN_ID;


    
    // // printf("buffered: %s %d\n", string_buffer, myToken->type);
    return myToken;
}

token* get_number_token(lexer* myLexer){
    token* myToken = malloc(sizeof(token));

    char* string_buffer = malloc(sizeof(char));
    int point_counter = 0; // decimal point counter
    string_buffer[0] = '\0';
    while(isdigit(myLexer->current_char) ||  (myLexer->current_char=='.' && isdigit(myLexer->content[myLexer->i+1])&& point_counter<2)){
        if(myLexer->content[myLexer->i+1] == '.'){ // check if the next character is a decimal point.
            point_counter++;
        }
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';

        string_buffer = realloc(string_buffer, strlen(string_buffer) + strlen(current_char_as_string) + 1);

        strcat(string_buffer, current_char_as_string);
        advance_lexer(myLexer);
    }
    myToken->type = TOKEN_NUMBER;
    myToken->value = string_buffer;
    
    // printf("buffered: %s %d\n", string_buffer, myToken->type);
    return myToken;
}

token* get_string_token(lexer* myLexer){
    char symbol = myLexer->current_char;
    advance_lexer(myLexer); // skip the "

    token* myToken = malloc(sizeof(token));

    char* string_buffer = malloc(sizeof(char));
    string_buffer[0] = '\0';
    while(isalnum(myLexer->current_char) ||  myLexer->current_char=='_'){
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';

        string_buffer = realloc(string_buffer, strlen(string_buffer) + strlen(current_char_as_string) + 1);

        strcat(string_buffer, current_char_as_string);
        advance_lexer(myLexer);
    }
    advance_lexer(myLexer);

    if(symbol == '"'){
        myToken->type = TOKEN_STRING;
    }
    else if(symbol == '\''){
        myToken->type = TOKEN_CHAR;
    }
    
    myToken->value = string_buffer;
    
    // printf("buffered: %s %d\n", string_buffer, myToken->type);
    return myToken;
}

token* get_assignment_token(lexer* myLexer, char curr_operator){
    char* string_buffer = malloc(sizeof(char)+2);

    string_buffer[0] = curr_operator;
    string_buffer[1] = myLexer->current_char;
    string_buffer[2] = '\0';
    advance_lexer(myLexer);

    token* myToken = malloc(sizeof(token));
    myToken->type = TOKEN_OPERATOR;
    myToken->value = string_buffer;
}

char* get_single_line_string(lexer* myLexer){

    skip_whitespace(myLexer);
    char* string_buffer = malloc(sizeof(char));
    string_buffer[0] = '\0';
    while(myLexer->current_char!=10 && myLexer->current_char!=13   && myLexer->current_char!=EOF){
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';

        string_buffer = realloc(string_buffer, strlen(string_buffer) + 2);

        strcat(string_buffer, current_char_as_string);
        // printf("%s\n", string_buffer);
        advance_lexer(myLexer);
    } 

    // printf("%s\n", string_buffer);
    return string_buffer;

}

char* get_multi_line_string(lexer* myLexer){
    char* string_buffer = malloc(sizeof(char));
    char next_char = myLexer->content[myLexer->i+1];
    string_buffer[0] = '\0';
    while((myLexer->current_char!='*' && next_char!='/') && myLexer->current_char!='\0' && myLexer->current_char!=EOF){
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';

        string_buffer = realloc(string_buffer, strlen(string_buffer) + strlen(current_char_as_string) + 1);

        strcat(string_buffer, current_char_as_string);
        advance_lexer(myLexer);
        next_char = myLexer->content[myLexer->i+1];

        free(current_char_as_string);
    } 
    advance_lexer(myLexer);
    advance_lexer(myLexer);

    return string_buffer;

}

token* get_comment_token(lexer* myLexer){
    char next_char = myLexer->content[myLexer->i+1];
    char next_two_char = myLexer->content[myLexer->i+2];

    if(myLexer->current_char=='/'){
        advance_lexer(myLexer);
        if(next_char=='/'){
            advance_lexer(myLexer);

            return token_init(TOKEN_SINGLECOMMENT, get_single_line_string(myLexer));
        }
        else if(next_char=='*'){
            advance_lexer(myLexer);

            return token_init(TOKEN_MULTICOMMENT, get_multi_line_string(myLexer));
        }
    }
    else if(myLexer->current_char=='#'){
        advance_lexer(myLexer);
        return token_init(TOKEN_SINGLECOMMENT, get_single_line_string(myLexer));
    }
}

token* get_token_then_advance(lexer* myLexer, token* myToken){
    advance_lexer(myLexer);
    return myToken;
}

char* char_to_string(char ch){
    char* char_as_string = malloc(sizeof(char)+1);
    char_as_string[0] = ch;
    char_as_string[1] = '\0';
    return char_as_string;
}

token* token_buffer(lexer* myLexer){
    while(myLexer->current_char != EOF && myLexer->i < strlen(myLexer->content) || myLexer->current_char != '\0'){
        if(myLexer->current_char== ' ' || myLexer->current_char == 10 || myLexer->current_char == 13){
            skip_whitespace(myLexer);
        }

        if(isdigit(myLexer->current_char)){
            return get_number_token(myLexer);
        }

        if(isalnum(myLexer->current_char) || myLexer->current_char=='_'){
            return get_identifier_token(myLexer);
        }

        if(myLexer->current_char == '"' || myLexer->current_char == '\''){
            return get_string_token(myLexer);
        }

        if(is_comment(myLexer)){
            return get_comment_token(myLexer);
        }
        else if(is_operator(myLexer->current_char)){
            char operator = myLexer->current_char;
            if(myLexer->content[myLexer->i+1]=='='){ // check if it is an assignment operator
                advance_lexer(myLexer);

                return get_assignment_token(myLexer, operator);
            }
            else if(myLexer->content[myLexer->i+1]==operator){ // check if it is a unary operator
                advance_lexer(myLexer);
                char* unary_operator = malloc(sizeof(char)+2);

                unary_operator[0] = operator;
                unary_operator[1] = operator;
                unary_operator[2] = '\0';

                return get_token_then_advance(myLexer, token_init(TOKEN_OPERATOR, unary_operator));
            }

            return get_token_then_advance(myLexer, token_init(TOKEN_OPERATOR, char_to_string(operator)));
        }

        switch(myLexer->current_char){
            case '.': return get_token_then_advance(myLexer, token_init(TOKEN_DOT, char_to_string('.'))); break;
            case '@': return get_token_then_advance(myLexer, token_init(TOKEN_SYMBOL, char_to_string('@'))); break;
            case '^': return get_token_then_advance(myLexer, token_init(TOKEN_SYMBOL, char_to_string('^'))); break;
            case '~': return get_token_then_advance(myLexer, token_init(TOKEN_TILDE, char_to_string('~'))); break;
            case '?': return get_token_then_advance(myLexer, token_init(TOKEN_QUESTION, char_to_string('?'))); break;
            case '!': return get_token_then_advance(myLexer, token_init(TOKEN_EXCLAMATION, char_to_string('!'))); break;
            case '&': return get_token_then_advance(myLexer, token_init(TOKEN_AMPERSAND, char_to_string('&'))); break;
            case ':': return get_token_then_advance(myLexer, token_init(TOKEN_COLON, char_to_string(':'))); break;
            case ';': return get_token_then_advance(myLexer, token_init(TOKEN_SEMI, char_to_string(';'))); break;
            case '(': return get_token_then_advance(myLexer, token_init(TOKEN_LPAREN, char_to_string('('))); break;
            case ')': return get_token_then_advance(myLexer, token_init(TOKEN_RPAREN, char_to_string(')'))); break;
            case '{': return get_token_then_advance(myLexer, token_init(TOKEN_LBRACE, char_to_string('{'))); break;
            case '}': return get_token_then_advance(myLexer, token_init(TOKEN_RBRACE, char_to_string('}'))); break;
            case ',': return get_token_then_advance(myLexer, token_init(TOKEN_COMMA, char_to_string(','))); break;
            case '[': return get_token_then_advance(myLexer, token_init(TOKEN_LBRACKET, char_to_string('['))); break;
            case ']': return get_token_then_advance(myLexer, token_init(TOKEN_RBRACKET, char_to_string(']'))); break;


            default: 
                return get_token_then_advance(myLexer, token_init(TOKEN_UNKNOWN, NULL)); break;
        }

        // printf("debug %d\n", myLexer->current_char);
        advance_lexer(myLexer);
        return token_init(404, NULL);
    }

    return NULL;
}

#endif 


token* isKeyword(lexer* myLexer, token* myToken, char* valueToCheck){


    for(int i = 0; isalnum(myLexer->current_char) ||  myLexer->current_char=='_'; i++){

        char next_char = myLexer->content[myLexer->i+1];
        char* current_character = malloc(sizeof(char)+1);
        current_character[0] = myLexer->current_char;
        current_character[1] = '\0';
        myToken->value = realloc(myToken->value, strlen(myToken->value) + 2);

        strcat(myToken->value, current_character);
        if(valueToCheck[i] == myLexer->current_char &&  isalnum(next_char) == 0 && i < strlen(valueToCheck)){
            myToken->type = TOKEN_KEYWORD;
            return get_token_then_advance(myLexer, myToken);
        }
        advance_lexer(myLexer);
    }
    myToken->type =  TOKEN_ID;
    return get_token_then_advance(myLexer, myToken);
}


// int isNumber(const char *str) {
//     if (str == NULL || *str == '\0') {
//         return 0; // Empty or null strings are not numbers
//     }

//     const char *ptr = str;

//     // Check for an optional leading sign
//     if (*ptr == '+' || *ptr == '-') {
//         ptr++;
//     }

//     int hasDigits = 0;
//     int hasDot = 0;

//     while (*ptr != '\0') {
//         if (isdigit(*ptr)) {
//             hasDigits = 1;
//         } else if (*ptr == '.') {
//             if (hasDot) {
//                 return 0; // Multiple dots are not allowed
//             }
//             hasDot = 1;
//         } else {
//             return 0; // Any non-digit and non-dot character invalidates
//         }
//         ptr++;
//     }

//     // A valid number must have at least one digit
//     return hasDigits;
// }

