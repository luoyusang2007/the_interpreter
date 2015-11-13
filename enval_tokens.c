#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "structs.h"


struct Constant * Op_plus(struct Constant * a, struct Constant * b);
struct Constant * Op_minus(struct Constant * a, struct Constant * b);
struct Constant * Op_multiplied_by(struct Constant * a, struct Constant * b);
struct Constant * Op_divided_by(struct Constant * a, struct Constant * b);




struct Constant * eval_expression(struct token * tokens_list )
{
    struct token * p_token = tokens_list;
    struct Constant * result = NULL;

    //getchar();
    if(tokens_list == NULL)
        printf("Nothing in the tokens list!\n");
    else
    {
        //printf("Token: %s\t type: %c \n",p_token->token_string,p_token->type);//print the first
        if(p_token->child!= NULL)//Nonterminal Symbol
        {

            printf("Here1\n");
            if(p_token->type == TOKEN_R_OP_PLUS){
                result = Op_plus(eval_expression(p_token->child),eval_expression(p_token->child->next));
                if (result->type==VAL_TYPE_INT)
                    printf("PLUS:%d\n",*(long int *)(result->value));
                else if(result->type==VAL_TYPE_FLOAT)
                    printf("PLUS:%f\n",*(double *)(result->value));

            }else if(p_token->type == TOKEN_R_OP_MINUS){
                result = Op_minus(eval_expression(p_token->child),eval_expression(p_token->child->next));
            }else if(p_token->type == TOKEN_R_OP_MULTI_B){
                result = Op_multiplied_by(eval_expression(p_token->child),eval_expression(p_token->child->next));
                printf("MULTI:%d\n",*(long int *)(result->value));
            }else if(p_token->type == TOKEN_R_OP_DIVD_B){
                result = Op_divided_by(eval_expression(p_token->child),eval_expression(p_token->child->next));
            }else{
                printf("ERR:Operator not supported!\n");
            }


        }
        else//Terminal Symbol
        {
            if(p_token->revelent_value->type == VAL_TYPE_FLOAT)
            {
                result = (struct Constant *)malloc(sizeof(struct Constant));
                result->type = VAL_TYPE_FLOAT;
                result->value = malloc(sizeof(double));
                *((double *)(result->value)) = *(double *)(p_token->revelent_value->value);
            }
            else if (p_token->revelent_value->type == VAL_TYPE_INT)
            {
                result = (struct Constant *)malloc(sizeof(struct Constant));
                result->type = VAL_TYPE_INT;
                result->value = malloc(sizeof(long int));
                *((long int *)(result->value)) = *(long int *)(p_token->revelent_value->value);
                printf("INT:%d\n",*(long int *)(p_token->revelent_value->value));
            }
        }
    }
    return result;
}




void enval_tokens(struct token ** pp_token)
{
    struct Constant * zero = NULL;
    struct token * zero_token = NULL;

    struct token ** pp_prev_token = pp_token;
    struct token * p_token = (* pp_token)->next;

    struct token ** pp_token_bracket = pp_token;


    while(*pp_token_bracket!= NULL)
    {
        if((*pp_token_bracket)->type == TOKEN_R_DIV_L_SBRA)
        {
            enval_tokens(&((*pp_token_bracket)->next));
            *pp_token_bracket = (*pp_token_bracket)->next;
            //free something......

            printf("11hehe:\n");
            print_tokens(*pp_token);

            (*pp_token_bracket)->next = (*pp_token_bracket)->next->next;
            //free something.....

            printf("22hehe:\n");
            print_tokens(*pp_token);

            break ;
        }
        pp_token_bracket = &((*pp_token_bracket)->next);
    }


    //reset but i don't know why!??
    pp_prev_token = pp_token;
    p_token = (* pp_token)->next;



    if((*pp_prev_token)->type != TOKEN_R_TYPE_VALUE)
        if((*pp_prev_token)->type == TOKEN_R_OP_MINUS || (*pp_prev_token)->type == TOKEN_R_OP_PLUS)
        {
            zero = (struct Constant *)malloc(sizeof(struct Constant));
            zero->type = VAL_TYPE_INT;
            zero->value = malloc(sizeof(long));
            *((long *)(zero->value)) = 0;
            zero_token = (struct token *)malloc(sizeof(struct token));
            zero_token->revelent_value = zero;
            zero_token->token_string = NULL;
            zero_token->type = TOKEN_R_TYPE_VALUE;
            zero_token->next = *pp_prev_token;
            p_token = *pp_prev_token;
            *pp_prev_token = zero_token;

        }





    while(p_token != NULL && p_token->type != TOKEN_R_DIV_R_SBRA)
    {
        if(p_token->type == TOKEN_R_OP_MULTI_B)
        {

            if(p_token->next == NULL)
            {
                printf("ERR:'*' operator found at the end of the sentence\n");

            }
            else
            {
                printf("hehe3:%d\n",(*pp_prev_token)->type);
                printf("%p\n",pp_prev_token);
                printf("%p\n",pp_token);
                (*pp_prev_token)->revelent_value = Op_multiplied_by((*pp_prev_token)->revelent_value
                                                           ,p_token->next->revelent_value);
                //free....

                (*pp_prev_token)->type = TOKEN_R_TYPE_VALUE;
                free((*pp_prev_token)->token_string);
                (*pp_prev_token)->token_string = NULL;
                (*pp_prev_token)->next = p_token->next->next;
                p_token = p_token->next->next;
            }
        }else if(p_token->type == TOKEN_R_OP_DIVD_B)
        {

            if(p_token->next == NULL)
            {
                printf("ERR:'/' operator found at the end of the sentence\n");

            }
            else
            {

                (*pp_prev_token)->revelent_value = Op_divided_by((*pp_prev_token)->revelent_value
                                                            ,p_token->next->revelent_value);
                //free....

                (*pp_prev_token)->type = TOKEN_R_TYPE_VALUE;
                free((*pp_prev_token)->token_string);
                (*pp_prev_token)->token_string = NULL;
                (*pp_prev_token)->next = p_token->next->next;
                p_token = p_token->next->next;
            }
        }else
        {
            printf("ERR:nor */\n");
            pp_prev_token = &((*pp_prev_token)->next);
            p_token = p_token->next;

        }

    }
    //reset
    pp_prev_token = pp_token;
    p_token = (* pp_token)->next;



    while(p_token != NULL && p_token->type != TOKEN_R_DIV_R_SBRA)
    {

        if(p_token->type == TOKEN_R_OP_PLUS)
        {

            if(p_token->next == NULL)
            {
                printf("ERR:'+' operator found at the end of the sentence\n");

            }
            else
            {

                (*pp_prev_token)->revelent_value = Op_plus((*pp_prev_token)->revelent_value
                                                           ,p_token->next->revelent_value);
                //free....

                (*pp_prev_token)->type = TOKEN_R_TYPE_VALUE;
                free((*pp_prev_token)->token_string);
                (*pp_prev_token)->token_string = NULL;
                (*pp_prev_token)->next = p_token->next->next;
                p_token = p_token->next->next;
            }
        }else if(p_token->type == TOKEN_R_OP_MINUS)
        {

            if(p_token->next == NULL)
            {
                printf("ERR:'-' operator found at the end of the sentence\n");

            }
            else
            {

                (*pp_prev_token)->revelent_value = Op_minus((*pp_prev_token)->revelent_value
                                                           ,p_token->next->revelent_value);
                //free....

                (*pp_prev_token)->type = TOKEN_R_TYPE_VALUE;
                free((*pp_prev_token)->token_string);
                (*pp_prev_token)->token_string = NULL;
                (*pp_prev_token)->next = p_token->next->next;
                p_token = p_token->next->next;
            }
        }else
        {
            printf("ERR:nor +- %d\n",p_token->type);
           // pp_prev_token = &((*pp_prev_token)->next);
          //  p_token = p_token->next;
        }


    }
    printf("dcdc:%p %ld\n",(*pp_token)->revelent_value,*(long *)((*pp_token)->revelent_value->value));
}

















