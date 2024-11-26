#ifndef lexer_h
#define lexer_h

typedef struct lexer_struct{
    char current_char;
    int i;
    char* content;

}lexer;

token* determineToken(lexer* myLexer, token* myToken, char* valueToCheck, int tokenType);
void advance_lexer(lexer* myLexer);
void retreat_lexer(lexer* myLexer);
token* get_token_then_advance(lexer* myLexer, token* myToken);
char* char_to_string(char ch);

lexer* lexer_init(char* content){
    lexer* myLexer = malloc(sizeof(lexer));
    myLexer->content = content;
    myLexer->i = 0;
    myLexer->current_char = content[myLexer->i];

    return myLexer;
}

int is_comment(lexer* myLexer){
    // char next_char = myLexer->content[myLexer->i+1];
    // char next_two_char = myLexer->content[myLexer->i+2];

    if(myLexer->current_char == '/'){
        advance_lexer(myLexer);
        if(myLexer->current_char=='*'){
            advance_lexer(myLexer);
            return 2;
        }
        else{
            retreat_lexer(myLexer);
            return 0;
        }
    }
    else if(myLexer->current_char == '#'){
        advance_lexer(myLexer);
        return 1;
    }

    else if(myLexer->current_char == '"'){
        advance_lexer(myLexer);
        if(myLexer->current_char == '"'){
            advance_lexer(myLexer);
            if(myLexer->current_char == '"'){
                retreat_lexer(myLexer);
                retreat_lexer(myLexer);
                return 2;
            }
            else{
                retreat_lexer(myLexer);
                return 0;
            }
        }
        else{
            retreat_lexer(myLexer);
            return 0;
        }
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

void retreat_lexer(lexer* myLexer){
    if(myLexer->i > 0){
        myLexer->i -= 1;
        myLexer->current_char = myLexer->content[myLexer->i];
    }
}

void skip_whitespace(lexer* myLexer){
    while(myLexer->current_char == ' ' || myLexer->current_char == 10 || myLexer->current_char == 13){
        advance_lexer(myLexer);
    }
}

void realloc_token_value_then_advance(token* myToken, lexer* myLexer){
    myToken->value = realloc(myToken->value, strlen(myToken->value) + 2);
    strcat(myToken->value, char_to_string(myLexer->current_char));
    advance_lexer(myLexer);
}

token* get_identifier_token(lexer* myLexer){


    token* myToken = malloc(sizeof(token));

    switch(myLexer->current_char){

        case 'a':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 's': // check for as
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ 
                        return token_init(TOKEN_OPERATOR, myToken->value);
                    }
                    else{
                        break;
                    }

                case 'n': // check for and
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='d'){
                        realloc_token_value_then_advance(myToken, myLexer);

                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){
                                return token_init(TOKEN_OPERATOR, myToken->value);
                            }
                            else{
                                break;
                            }

                    }
                    else{
                        break;
                    }
                default:
                    break;
            }
        break; // of checking the character 'A'

        case 't':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);

            switch(myLexer->current_char){
                case 'r': // check for true or try
                    realloc_token_value_then_advance(myToken, myLexer);

                    switch(myLexer->current_char){
                        case 'u': // check for true
                            realloc_token_value_then_advance(myToken, myLexer);
                            if(myLexer->current_char=='e'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                } 

                            }
                            else{
                                break;
                            }

                        case 'y': // check for try
                            realloc_token_value_then_advance(myToken, myLexer);
                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                return token_init(TOKEN_KEYWORD, myToken->value);
                            }
                            else{
                                break;
                            } 

                        default: 
                            break;

                    }// done checking char 't'

                case 'e': // check for terminate or terminateall
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='r'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='m'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='i'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='n'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char=='a'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(myLexer->current_char=='t'){
                                            realloc_token_value_then_advance(myToken, myLexer);

                                            if(myLexer->current_char=='e'){
                                                realloc_token_value_then_advance(myToken, myLexer);

                                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){
                                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                                }
                                                else if(myLexer->current_char=='a'){
                                                    realloc_token_value_then_advance(myToken, myLexer);

                                                        if(myLexer->current_char=='l'){
                                                            realloc_token_value_then_advance(myToken, myLexer);

                                                            if(myLexer->current_char=='l'){
                                                                realloc_token_value_then_advance(myToken, myLexer);

                                                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){
                                                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                                                }
                                                                else{
                                                                    break;
                                                                }
                                                            }
                                                            else{
                                                                break;
                                                            }
                                                        }
                                                        else{
                                                            break;
                                                        }
                                                }
                                                else{
                                                    break;
                                                }

                                            }
                                            else{
                                                break;
                                            }
                                        }
                                        else{
                                            break;
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                    


                default:
                    break; 
            }  
        break; // done checking char 't'
            
            
        
        case 'f': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'a':
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='l'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='s'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='e'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                }    
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                
                case 'u':
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='n'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='c'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='t'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='i'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char=='o'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(myLexer->current_char=='n'){
                                            realloc_token_value_then_advance(myToken, myLexer);

                                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                                return token_init(TOKEN_KEYWORD, myToken->value);
                                            }
                                            else{
                                                break;
                                            }   
                                        }
                                        else{
                                            break;
                                        }

                                    }
                                    else{
                                        break;
                                    }
                                    
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                case 'i':
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='n'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='a'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='l'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='l'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char=='y'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                            return token_init(TOKEN_KEYWORD, myToken->value);
                                        }
                                        else{
                                            break;
                                        }  

                                    }
                                    else{
                                        break;
                                    }
                                    
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                case 'l':
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='o'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='a'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='t'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_DATATYPE, myToken->value);
                                }
                                else{
                                    break;
                                }    
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                case 'o':
                    realloc_token_value_then_advance(myToken, myLexer);
                    
                    if(myLexer->current_char=='r'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                            return token_init(TOKEN_KEYWORD, myToken->value);
                        }
                        else{
                            break;
                        }   

                    }
                    else{
                        break;
                    }



                default:
                    break;
            } 
        break; // of checking the character 'f'

        case 'l': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'e': // check for let
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='t'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                            return token_init(TOKEN_RESERVEDWORDS, myToken->value);
                        }
                        else{
                            break;
                        }    

                    }
                    else{
                        break;
                    }
                
                case 'a': // check for lambda
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='m'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='b'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='d'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='a'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                        return token_init(TOKEN_RESERVEDWORDS, myToken->value);
                                    }
                                    else{
                                        break;
                                    }    

                                }
                                else{
                                    break;
                                }
                                 
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                case 'o': // check for loop
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='o'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='p'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                return token_init(TOKEN_RESERVEDWORDS, myToken->value);
                            }
                            else{
                                break;
                            }

                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                default:
                    break;
            }
        break; // end of checking for the character 'l'

        case 'c': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);

            switch(myLexer->current_char){
                case 'a': // check for catch or case
                    realloc_token_value_then_advance(myToken, myLexer);
                    
                    switch(myLexer->current_char){
                        case 's': // check for case
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='e'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                }  

                            }
                            else{
                                break;
                            }

                        case 't': // check for catch
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='c'){
                                realloc_token_value_then_advance(myToken, myLexer);
                                
                                if(myLexer->current_char=='h'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                        return token_init(TOKEN_KEYWORD, myToken->value);
                                    }
                                    else{
                                        break;
                                    }

                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }

                        default:
                            
                            break; // end for checking for catch or case
                    }
                break; // end for checking for catch or case
                
                case 'h': // check for char or check
                    realloc_token_value_then_advance(myToken, myLexer);

                    switch(myLexer->current_char){
                        case 'a':
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='r'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_DATATYPE, myToken->value);
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }

                        case 'e':
                            realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='c'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char=='k'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                            return token_init(TOKEN_KEYWORD, myToken->value);
                                        }
                                        else{
                                            break;
                                        }

                                    }
                                    else{
                                        break;
                                    }
                                }
                                else{
                                    break;
                                }
                    }

                    
                
                default:
                    break; 
            }
        break; // end of checking for the character 'c'

        case 'e': 
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);

            switch(myLexer->current_char){
                case 'l': // check for else or elif
                    realloc_token_value_then_advance(myToken, myLexer);
                    
                    switch(myLexer->current_char){
                        case 'i': // check for elif
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='f'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                }  

                            }
                            else{
                                break;
                            }

                        case 's': // check for elif
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='e'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                }  

                            }
                            else{
                                break;
                            }

                        default:
                            break;
                    } // end for checking for else or elif
                
                case 'n': // check for endloop
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char == 'd'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char == 'l'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char == 'o'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char == 'o'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char == 'p'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                            return token_init(TOKEN_KEYWORD, myToken->value);
                                        }
                                        else{
                                            break;
                                        }

                                    }
                                    else{
                                        break;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                    

                default:
                    break; 
            }
        break; // end of checking for the character 'e'

        case 'i':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'f': // check for if
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ 
                        return token_init(TOKEN_KEYWORD, myToken->value);
                    }
                    else{
                        break;
                    }

                case 's': // check for is
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                        return token_init(TOKEN_KEYWORD, myToken->value);
                    }
                    else{
                        break;
                    }

                case 'n': // check for in or int
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                        return token_init(TOKEN_KEYWORD, myToken->value);
                    }
                    else if(myLexer->current_char == 't'){
                        realloc_token_value_then_advance(myToken, myLexer);
                        
                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ 
                            return token_init(TOKEN_DATATYPE, myToken->value);
                        }
                        else{
                            break;
                        }

                    }
                    else{
                        break;
                    }

                default:
                    break;
            }
        break; // end of checking for the character 'i'

        case 'w':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);

            switch(myLexer->current_char){
                case 'h': // check for while
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='i'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='l'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='e'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                }    
                                 
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }


                default:
                    break;
            }

        break; // end of checking for the character 'w'

        case 'd':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);

            switch(myLexer->current_char){
                case 'o': // check for do or double
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // check if it is do
                        return token_init(TOKEN_KEYWORD, myToken->value);
                    }
                    else if(myLexer->current_char=='u'){ // check for double
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='b'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='l'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='e'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                        return token_init(TOKEN_DATATYPE, myToken->value);
                                    }
                                    else{
                                        break;
                                    }  

                                }
                                else{
                                    break;
                                }  
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }


                default:
                    break;
            }
        break; // end of checking for the character 'd'

        case 'r':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'e': // check for return
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='t'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='u'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='r'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='n'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                        return token_init(TOKEN_KEYWORD, myToken->value);
                                    }
                                    else{
                                        break;
                                    }  

                                }
                                else{
                                    break;
                                }
                                 
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                
                case 'a': // check for raise
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='i'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='s'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='e'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_RESERVEDWORDS, myToken->value);
                                }
                                else{
                                    break;
                                }  
                                 
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }


                default:
                    break;
            }
        break; // end of checking for the character 'r'

        case 'b':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'r': // check for break
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='e'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='a'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='k'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                }
                                else{
                                    break;
                                }  
            
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                case 'o': // check for bool
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='o'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='l'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                return token_init(TOKEN_DATATYPE, myToken->value);
                            }
                            else{
                                break;
                            }  

                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                default:
                    break;

            }
        break; // end of checking for the character 'b'

        case 's':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 't': // check for string
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='r'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='i'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='n'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='g'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                        return token_init(TOKEN_DATATYPE, myToken->value);
                                    }
                                    else{
                                        break;
                                    }  

                                }
                                else{
                                    break;
                                }
                                 
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }


                default:
                    break;
            }
        break; // end of checking for the character 's'

        case 'v':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'a': // check for var
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='r'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ 
                            return token_init(TOKEN_RESERVEDWORDS, myToken->value);
                        }
                        else{
                            break;
                        }  
                        
                    }
                    else{
                        break;
                    }
                
                case 'o': // check for void
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='i'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='d'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ 
                                return token_init(TOKEN_DATATYPE, myToken->value);
                            }
                            else{
                                break;
                            }  

                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }


                default:
                    break;
            }
        break; // end of checking for the character 'v'


        case 'o':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){ // check for or or otherwise
                case 'r': // check for or 
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                        return token_init(TOKEN_KEYWORD, myToken->value);
                    }
                    else{
                        break;
                    }   

                case 't': // check for otherwise
                    realloc_token_value_then_advance(myToken, myLexer);
                    if(myLexer->current_char=='h'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='e'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='r'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='w'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char=='i'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(myLexer->current_char=='s'){
                                            realloc_token_value_then_advance(myToken, myLexer);

                                            if(myLexer->current_char=='e'){
                                                realloc_token_value_then_advance(myToken, myLexer);

                                                if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ // 
                                                    
                                                    return token_init(TOKEN_KEYWORD, myToken->value);
                                                }
                                                else{
                                                    break;
                                                }  

                                            }
                                            else{
                                                break;
                                            }
                                        }
                                        else{
                                            break;
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }

                default:
                    break;
            }
        break; // end of checking for the character 'o'


        case 'n':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'o': // check for not
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='t'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){ 
                            return token_init(TOKEN_OPERATOR, myToken->value);
                        }
                        else{
                            break;
                        }

                    }
                    else{
                        break;
                    }
                default:
                    break;
            }

        case 'p':
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            switch(myLexer->current_char){
                case 'r': // check for printout
                    realloc_token_value_then_advance(myToken, myLexer);

                    if(myLexer->current_char=='i'){
                        realloc_token_value_then_advance(myToken, myLexer);

                        if(myLexer->current_char=='n'){
                            realloc_token_value_then_advance(myToken, myLexer);

                            if(myLexer->current_char=='t'){
                                realloc_token_value_then_advance(myToken, myLexer);

                                if(myLexer->current_char=='o'){
                                    realloc_token_value_then_advance(myToken, myLexer);

                                    if(myLexer->current_char=='u'){
                                        realloc_token_value_then_advance(myToken, myLexer);

                                        if(myLexer->current_char=='t'){
                                            realloc_token_value_then_advance(myToken, myLexer);

                                            if(isalnum(myLexer->current_char)==0 && myLexer->current_char!='_'){
                                                return token_init(TOKEN_KEYWORD, myToken->value);
                                            }
                                            else{
                                                break;
                                            }

                                        }
                                        else{
                                            break;
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                default:
                    break;
            }
        break; // end of checking for the character 'n'


        default:
            myToken->value =  char_to_string(myLexer->current_char);
            advance_lexer(myLexer);
            break;
    }

    char* string_buffer = myToken->value;
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
    while(myLexer->current_char!='"'){ // isalnum(myLexer->current_char) ||  myLexer->current_char=='_'
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

// token* get_assignment_token(lexer* myLexer, char curr_operator){
//     char* string_buffer = malloc(sizeof(char)+2);

//     string_buffer[0] = curr_operator;
//     string_buffer[1] = myLexer->current_char;
//     string_buffer[2] = '\0';
//     advance_lexer(myLexer);

//     token* myToken = malloc(sizeof(token));
//     myToken->type = TOKEN_OPERATOR;
//     myToken->value = string_buffer;
// }

char* get_single_line_string(lexer* myLexer){

    skip_whitespace(myLexer);
    char* string_buffer = malloc(sizeof(char));
    string_buffer[0] = '\0';
    while(myLexer->current_char!=10 && myLexer->current_char!=13  && myLexer->current_char!=EOF && myLexer->current_char!='\0'){
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';

        string_buffer = realloc(string_buffer, strlen(string_buffer) + 2);

        strcat(string_buffer, current_char_as_string);
        advance_lexer(myLexer);
    } 

    // printf("%s\n", string_buffer);
    return string_buffer;

}

char* get_multi_line_string(lexer* myLexer){
    char* string_buffer = malloc(sizeof(char));
    string_buffer[0] = '\0';
    while(myLexer->current_char!='\0' && myLexer->current_char!=EOF){
        if(myLexer->current_char=='*'){
            advance_lexer(myLexer);
            if(myLexer->current_char=='/'){
                break;
            }
            retreat_lexer(myLexer);
        }
        char* current_char_as_string = malloc(sizeof(char)+1);
        current_char_as_string[0] = myLexer->current_char;
        current_char_as_string[1] = '\0';
        string_buffer = realloc(string_buffer, strlen(string_buffer) + strlen(current_char_as_string) + 1);
        strcat(string_buffer, current_char_as_string);

        advance_lexer(myLexer);
        free(current_char_as_string);
    } 
    advance_lexer(myLexer);
    advance_lexer(myLexer);

    return string_buffer;

}


// char* get_multi_line_string(lexer* myLexer){
//     char* string_buffer = malloc(sizeof(char));
//     char next_char = myLexer->content[myLexer->i+1];
//     string_buffer[0] = '\0';
//     while((myLexer->current_char!='*' && next_char!='/') && myLexer->current_char!='\0' && myLexer->current_char!=EOF){
//         char* current_char_as_string = malloc(sizeof(char)+1);
//         current_char_as_string[0] = myLexer->current_char;
//         current_char_as_string[1] = '\0';

//         string_buffer = realloc(string_buffer, strlen(string_buffer) + strlen(current_char_as_string) + 1);

//         strcat(string_buffer, current_char_as_string);
//         advance_lexer(myLexer);
//         next_char = myLexer->content[myLexer->i+1];

//         free(current_char_as_string);
//     } 
//     advance_lexer(myLexer);
//     advance_lexer(myLexer);

//     return string_buffer;

// }

token* get_comment_token(lexer* myLexer, int commentType){
    if(commentType==2){
        return token_init(TOKEN_MULTICOMMENT, get_multi_line_string(myLexer));

    }
    else if(commentType==1){
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

        int commentType = is_comment(myLexer);
        if(commentType!=0){
            return get_comment_token(myLexer, commentType);
        }
        else if(is_operator(myLexer->current_char)){
            char operator = myLexer->current_char;
            advance_lexer(myLexer);
            char next_char = myLexer->current_char;
            char* symbol = malloc(sizeof(char)+2);
            symbol[0] = operator;
            symbol[1] = next_char;
            symbol[2] = '\0';

            // printf("%s\n", symbol);
            if(next_char==operator && (next_char=='*' || next_char=='+' || next_char=='-' || next_char=='/' || next_char=='=')){    
                 
                return get_token_then_advance(myLexer, token_init(TOKEN_OPERATOR, symbol));
            }
            else if((operator=='+' || operator=='-' || operator=='/' || operator=='*' || operator=='%' || operator=='<' || operator=='>' || operator=='!') && next_char=='='){ // check if it is an assignment or relational operator  
                return get_token_then_advance(myLexer, token_init(TOKEN_OPERATOR, symbol));
            }

            return token_init(TOKEN_OPERATOR, char_to_string(operator));
        }

        switch(myLexer->current_char){
            case '.': return get_token_then_advance(myLexer, token_init(TOKEN_DOT, char_to_string('.'))); break;
            case '@': return get_token_then_advance(myLexer, token_init(TOKEN_SYMBOL, char_to_string('@'))); break;
            case '^': return get_token_then_advance(myLexer, token_init(TOKEN_SYMBOL, char_to_string('^'))); break;
            case '~': return get_token_then_advance(myLexer, token_init(TOKEN_TILDE, char_to_string('~'))); break;
            case '?': return get_token_then_advance(myLexer, token_init(TOKEN_QUESTION, char_to_string('?'))); break;
            case '!': return get_token_then_advance(myLexer, token_init(TOKEN_OPERATOR, char_to_string('!'))); break;
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


token* determineToken(lexer* myLexer, token* myToken, char* valueToCheck, int tokenType){
    for(int i = 0; isalnum(myLexer->current_char) ||  myLexer->current_char=='_'; i++){

        char next_char = myLexer->content[myLexer->i+1];
        char* current_character = malloc(sizeof(char)+1);
        current_character[0] = myLexer->current_char;
        current_character[1] = '\0';
        myToken->value = realloc(myToken->value, strlen(myToken->value) + 2);

        strcat(myToken->value, current_character);
        if(valueToCheck[i] == myLexer->current_char &&  isalnum(next_char) == 0 &&  next_char != '_' && i < strlen(valueToCheck)){ // if the token is followed by a '_' at the last char it is considered to be an identifier.
            myToken->type = tokenType; 
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

