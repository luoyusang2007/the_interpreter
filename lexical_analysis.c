#include "structs.h"
#include "globals.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void token_append(struct token ** p_tokens_list,char type, char value_string[],unsigned long line_number)
{
    int t_string_len = strlen(value_string);
    struct token * p_new_token_node;
    p_new_token_node = (struct token *)malloc(sizeof(struct token));
    p_new_token_node->next = NULL;
    p_new_token_node->revelent_value = NULL;
    p_new_token_node->token_string = NULL;
    p_new_token_node->child = NULL;
    p_new_token_node->type = type;
    p_new_token_node->line_number = line_number;

    p_new_token_node->token_string = (char *)malloc(sizeof(struct token)*(t_string_len+1));
    strcpy(p_new_token_node->token_string,value_string);
    struct token * p_token = * p_tokens_list;

    if(p_token == NULL)
        *p_tokens_list = p_new_token_node;
    else
    {
        while(p_token->next!= NULL)
            p_token = p_token->next;
        //Here p_token->next is NULL
        p_token->next = p_new_token_node;
    }
    p_new_token_node->prev = p_token;// chain of two directions.
}

void release_all_tokens(struct token ** p_tokens_list)
{
    struct token * p_token = * p_tokens_list;
    struct token * p_token_next = NULL;
    if(p_token == NULL)
        return ;
    else
    {
        while(p_token != NULL)
        {
            p_token_next = p_token->next;
            if(p_token->revelent_value!= NULL)
            {
                free(p_token->revelent_value->value);
                free(p_token->revelent_value);
            }
            free(p_token->token_string);
            free(p_token);
            p_token = p_token_next;//maybe something wrong
        }
    }

    *p_tokens_list = NULL;
}

void print_tokens(struct token * tokens_list)
{
    struct token * p_token = tokens_list;
    if(tokens_list == NULL)
        printf("Nothing in the tokens list!\n");
    else
    {
        //printf("Token: %s\t type: %c \n",p_token->token_string,p_token->type);//print the first
        while(p_token!=NULL)
        {


            if(p_token->type != TOKEN_R_TYPE_VALUE)
                printf("Token: %s\t type: %d \t\tADD:%d \tPrev:%d\n",p_token->token_string,p_token->type,p_token,p_token->prev);
            else
            {
                switch(p_token->revelent_value->type)
                {

                case VAL_TYPE_INT : printf("Token:[VAL]\t type:(INT)\t:%ld \tADD:%d \tPrev:%d\n",*(long *)p_token->revelent_value->value,p_token,p_token->prev);break;
                case VAL_TYPE_FLOAT: printf("Token:[VAL]\t type:(FLOAT):%lf \tADD:%d \tPrev:%d\n",*(double *)p_token->revelent_value->value,p_token,p_token->prev);break;
                case VAL_TYPE_L_FLOAT: printf("Token:[VAL]\t type:(LONG_F):%llf \tADD:%d \tPrev:%d\n",*(long double *)p_token->revelent_value->value,p_token,p_token->prev);break;
                case VAL_TYPE_STRING: printf("Token:[VAL]\t type:(STR_CON):%s \tADD:%d \tPrev:%d\n",(char *)p_token->revelent_value->value,p_token,p_token->prev);break;
                default:printf("ERR:unknown constant type!%d\n",(int)p_token->revelent_value->type);
                }

            }

            p_token = p_token->next;

        }
    }

}

int count_tokens(struct token * tokens_list)
{
    int counter;
    struct token * p_token = tokens_list;
    if(tokens_list == NULL)
        return 0;
    else
    {
        counter = 1;
        while(p_token->next!=NULL)
        {
            p_token = p_token->next;
            counter ++;
        }
        return counter;
    }
}




char len_of_ident(char string[], int i)
{
    int j = 0;
    if(str_char_is_eng(string[i]))
        for(j=0;str_char_is_eng(string[i+j]) || str_char_is_num(string[i+j]);j++);
    return j;
}

char len_of_op_symbol(char string[],int i)
{
    int j = 0;
    if(str_char_is_op_symbol(string[i]))
        for(j = 0;str_char_is_op_symbol(string[i+j]);j++);
    return j;
}

char len_of_num(char string[],int i)
{
    int j = 0;
    if(str_char_is_num(string[i]))
        for(j=0;str_char_is_num(string[i+j]);j++);
    return j;
}

char len_of_str_const(char string[],int i)
{
    int start = i;
    ///////////////////////////////
    if(string[i] == '\'') //the left quote is a single quote
    {
        for(i=i+1;(string[i]!='\''||(string[i] == '\''&& !str_is_real_quote(string,i) ))&& string[i] != 0;i++);
        if(string[i] == 0)
            printf("ERR:single quote not in pairs!\n");
        else
            return i - start + 1;
    }
    else if(string[i] == '\"')//the left quote is a double quote
    {
        for(i=i+1;(string[i]!='\"'||(string[i] == '\"'&& !str_is_real_quote(string,i) ))&& string[i] != 0;i++);
        if(string[i] == 0)
            printf("ERR:dbl quote not in pairs!\n");
        else
            return i - start + 1;


    }else return 0;
    return 0;
}



void cut_line(char string[],struct token ** tokens_list,unsigned long line_number)
{
    int i = 0;
    int j;
    int symb_len;

    for(i = 0;string[i]!=0;)
    {
        if(symb_len = len_of_str_const(string,i))//found quote
        {
           // printf("found string constant between %d and %d\n",i,i+symb_len-1);
            char * token = (char *)malloc(sizeof(char)*symb_len);
            for(j = i;j<i+symb_len;j++)
                token[j-i] = string[j];
            token[symb_len - 1] = 0; //-1 to avoid quote
            token_append(tokens_list,TOKEN_TYPE_STR_CONST,token + 1,line_number); //+1 to avoid quote
            free(token);
            i = i+symb_len;
        }
        else if(symb_len = len_of_ident(string,i))//found identifier
        {
          //  printf("found identifier between %d and %d\n",i,i+symb_len-1);
            char * token = (char *)malloc(sizeof(char)*symb_len);
            for(j = i;j<i+symb_len;j++)
                token[j-i] = string[j];
            token[symb_len] = 0;
            token_append(tokens_list,TOKEN_TYPE_CHAR_STR,token,line_number);
            free(token);
            i = i+symb_len;
        }
        else if(symb_len = len_of_num(string,i))
        {
           // printf("found number between %d and %d\n",i,i+symb_len-1);
            char * token = (char *)malloc(sizeof(char)*symb_len);
            for(j = i;j<i+symb_len;j++)
                token[j-i] = string[j];
            token[symb_len] = 0;
            token_append(tokens_list,TOKEN_TYPE_NUMBER,token,line_number);
            free(token);
            i = i+symb_len;
        }
        else if(symb_len = len_of_op_symbol(string,i))
        {
           // printf("found operational symbol between %d and %d\n",i,i+symb_len-1);
            char * token = (char *)malloc(sizeof(char)*symb_len);
            for(j = i;j<i+symb_len;j++)
                token[j-i] = string[j];
            token[symb_len] = 0;
            token_append(tokens_list,TOKEN_TYPE_OPERATOR,token,line_number);
            free(token);
            i = i+symb_len;
        }
        else if(str_char_is_div_symbol(string[i]))//dividers are only one character
        {
          //  printf("found divider at %d\n",i);
            char * token = (char *)malloc(sizeof(char)*symb_len);
            token[0] = string[i];
            token[1] = 0;
            token_append(tokens_list,TOKEN_TYPE_DIVIDER,token,line_number);
            free(token);
            i = i+1;
        }
        else if(string[i]!=' ' && string[i]!='\n' && string[i]!='\r' && string[i]!='\t')//Character is other symbol but not space
        {
            printf("ERR:Unknown Symbol/Character!%d\n",string[i]);
            i = i+1;
        }else i = i+1;//Character is space
    }
}

char get_key_word(char * string)
{

    if(!strcmp("if" , string))
    {
        return TOKEN_R_KEYWD_IF;

    }else if(!strcmp("elif" , string))
    {
        return TOKEN_R_KEYWD_ELIF;

    }else if(!strcmp("else" , string))
    {
        return TOKEN_R_KEYWD_ELSE;

    }else if(!strcmp("for" , string))
    {
        return TOKEN_R_KEYWD_FOR;

    }else if(!strcmp("while" , string))
    {
        return TOKEN_R_KEYWD_WHILE;

    }else if(!strcmp("from" , string))
    {
        TOKEN_R_KEYWD_FROM;

    }else if(!strcmp("to" , string))
    {
        return TOKEN_R_KEYWD_TO;

    }else if(!strcmp("global" , string))
    {
        return TOKEN_R_KEYWD_GLOBAL;

    }else if(!strcmp("def" , string))
    {
        return TOKEN_R_KEYWD_DEF;

    }else if(!strcmp("var" , string))
    {
        return TOKEN_R_KEYWD_VAR;

    }else if(!strcmp("assign" , string))
    {
        return TOKEN_R_KEYWD_ASSIGN;

    }else if(!strcmp("function" , string))
    {
        return TOKEN_R_KEYWD_FUNCTION;

    }else if(!strcmp("return" , string))
    {
        return TOKEN_R_KEYWD_RETURN;
    }
    else
        return 0;
    return 0;
}

char is_operator(char * string)//check if a string is an operator
{




    return 0;
}


char is_variable(char * string)//check string is variable
{




    return 0;
}

char is_function(char * string)
{
    return 0;
}

long I_e_10(long i)
{
    long int j;
    long int val = 1;
    for(j=1;j<=i;j++)
        val = val * 10;
    return val;
}

struct Constant * string_to_double_constant(char * string)
{
    struct Constant * p_Constant = NULL;
    double double_val = 0.0;
    double * p_double = NULL;

    double_val = atof(string);

    p_double = (double * )malloc(sizeof(double));
    * p_double = double_val;
    p_Constant = (struct Constant *)malloc(sizeof(struct Constant));
    p_Constant->type = VAL_TYPE_FLOAT;
    p_Constant->value = p_double;

    return p_Constant;
}

struct Constant * string_to_long_constant(char * string)
{
    struct Constant * p_Constant = NULL;
    long long_val = 0;
    long * p_long = NULL;
    int end = strlen(string) -1 ;
    int i;
    for(i = end;i>=0;i--)
        if(string[i]<48 || string[i]> 57)
            printf("ERR:not a number in string!\n");
        else
            long_val = long_val + (long)(string[i]-48)*I_e_10(end - i);

    p_long = (long *)malloc(sizeof(long));
    * p_long = long_val;
    p_Constant = (struct Constant *)malloc(sizeof(struct Constant));
    p_Constant->type = VAL_TYPE_INT;
    p_Constant->value = p_long;

    return p_Constant;
}

struct Constant * string_to_string_constant(char * string, char escape)
{
    struct Constant * p_Constant = NULL;
    char char_escaped = 0;
    char step = 1;
    int i = 0;
    int j;

    p_Constant = (struct Constant *)malloc(sizeof(struct Constant));
    p_Constant->type = VAL_TYPE_STRING;
    p_Constant->value  = (char *)calloc(sizeof(char),strlen(string)+1);
    strcpy((char *)(p_Constant->value),string);


    if(escape)
    {
        //not support numbers like "\023"
        while(((char *)(p_Constant->value))[i])
        {
            //only support single character
            if(((char *)(p_Constant->value))[i] == '\\')
            {
                switch(((char *)(p_Constant->value))[i+1])
                {
                    case '\\': char_escaped = '\\'; step = 1 ; break;
                    case '\"': char_escaped = '\"'; step = 1 ; break;
                    case '\'': char_escaped = '\''; step = 1 ; break;
                    case 'n': char_escaped = '\n'; step = 1 ; break;
                    case 't': char_escaped = '\t'; step = 1 ; break;


                    default:printf("ERR:unknown escape!\n");
                }
                ((char *)(p_Constant->value))[i] = char_escaped;
                for(j = i+1;((char *)(p_Constant->value))[j];j++)
                {
                    ((char *)(p_Constant->value))[j] = ((char *)(p_Constant->value))[j+1];
                }
                i = i + (int)step;
            }else
            {
                i++;
            }
        }
    }
    return p_Constant;
}


char type_of_number(char * string)
{
    int end = strlen(string) - 1;
    //Ω¯÷∆‘›«“≤ªπ‹
    int num_of_dot = 0;
    int i;

    if(end == 0 && string[0] == '.')
        return TOKEN_TYPE_OPERATOR;
    for(i = 0;string[i]!=0;i++)
        if(string[i] == '.') num_of_dot ++ ;
    switch(num_of_dot)
    {
        case 0:return VAL_TYPE_INT ;
        case 1:return VAL_TYPE_FLOAT ;
        default:printf("ERR:Fucking 2 many dots!\n");return 0;
    }
}

void recognize_tokens(char * tokens_list)//token list should not be NULL
//this function is to change tokens into real values or simple structures
{
    struct token * p_token = tokens_list;

    while(p_token!= NULL)
    {

        if(p_token->type== TOKEN_TYPE_CHAR_STR )//char string,
        {

            if((p_token->next != NULL) && p_token->next->type == TOKEN_TYPE_STR_CONST )//two sides of and never change position in GCC!
            {
                //a string definer token
                printf("ERR:String definer function in development!\n");
            } else if(is_operator(p_token->token_string))
            {
                //operator

            } else if(get_key_word(p_token->token_string))
            {
                //key word
                p_token->type = get_key_word(p_token->token_string);

                free(p_token->token_string);
                p_token->token_string = NULL;

            } else if(is_variable(p_token->token_string))
            {
                p_token->type =TOKEN_R_TYPE_VALUE ;//value
                p_token->revelent_value;////////

                free(p_token->token_string);
                p_token->token_string = NULL;

            } else if(is_function(p_token->token_string))
            {
                p_token->type = TOKEN_R_TYPE_EX_FUNC ;//function
            } else
            {
                //new identifier




            }
        } else if(p_token->type == TOKEN_TYPE_NUMBER )//number constant
        {
            p_token->type =TOKEN_R_TYPE_VALUE ;//value
            if(type_of_number(p_token->token_string) == TOKEN_TYPE_OPERATOR)
            {
                //a single dot is an operator
                 p_token->type =TOKEN_R_OP_STR_CONNECT ;
                 ////here freed.......so can't see
            }else //the token is number...
            {
                if(type_of_number(p_token->token_string) == VAL_TYPE_INT )
                {

                    p_token->revelent_value=string_to_long_constant(p_token->token_string);


                }else if(type_of_number(p_token->token_string) == VAL_TYPE_FLOAT )
                {
                    p_token->revelent_value = string_to_double_constant(p_token->token_string);

                }else if(type_of_number(p_token->token_string) == VAL_TYPE_L_FLOAT )
                {

                    printf("ERR:long double floating constant in development!\n");
                }
                free(p_token->token_string);
                p_token->token_string = NULL;
            }

        } else if(p_token->type == TOKEN_TYPE_STR_CONST)//string constant
        {
            p_token->type = TOKEN_R_TYPE_VALUE;//value
            p_token->revelent_value = string_to_string_constant(p_token->token_string,1);

            free(p_token->token_string);
            p_token->token_string = NULL;
        } else if(p_token->type == TOKEN_TYPE_OPERATOR)//
        {

            if(!strcmp(p_token->token_string, "=") || !strcmp(p_token->token_string, ":=") )
            {
                p_token->type = TOKEN_R_ASSIGN;
            }

            else if(!strcmp(p_token->token_string, "+"))
            {
                p_token->type = TOKEN_R_OP_PLUS;

            }else if (!strcmp(p_token->token_string,"-"))
            {
                p_token->type = TOKEN_R_OP_MINUS;

            }else if (!strcmp(p_token->token_string,"*"))
            {
                p_token->type = TOKEN_R_OP_MULTI_B;

            }else if (!strcmp(p_token->token_string,"/"))
            {
                p_token->type = TOKEN_R_OP_DIVD_B;
            }
        } else if(p_token->type == TOKEN_TYPE_DIVIDER)//the dividers
        {
            if(!strcmp(p_token->token_string, "("))
            {
                p_token->type = TOKEN_R_DIV_L_SBRA;

            }else if (!strcmp(p_token->token_string,")"))
            {
                p_token->type = TOKEN_R_DIV_R_SBRA;

            }else if (!strcmp(p_token->token_string,","))
            {
                p_token->type = TOKEN_R_DIV_COMMA;

            }
        }
        p_token = p_token->next;
    }

}
