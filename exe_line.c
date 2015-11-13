#include "structs.h"
#include "globals.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void release_all_tokens(struct token ** p_tokens_list);
void print_tokens(struct token * tokens_list);
void recognize_tokens(char * tokens_list);//token list should not be NULL
void enval_tokens(struct token ** pp_token);
void variable_append(struct Variable ** p_Variables_h, struct Constant * val_Constant,char * name);
void print_variables(struct Variable * Variables_h);
int get_line_indent_class(int table_len, char * string);
void cut_line(char string[],struct token ** tokens_list);

void shell_exec_block(indent)
{
    char command_string[512] = "";
    struct sentence * block_h;
    struct sentence ** pp_sentence;
    int line_indent;
    int original_line_indent ;

    gets(command_string);
    line_indent = get_line_indent_class(TABLE_LEN, command_string);
    original_line_indent = line_indent;
    block_h = (struct sentence *)malloc(sizeof(struct sentence));
    block_h->next = NULL;
    pp_sentence = &(block_h);
    cut_line(command_string,&((*pp_sentence)->tokens_h));

    if(line_indent == original_line_indent)
    {
      //  execute_shell_line(<#char *Command_Line_String#>, <#struct Variable **p_Variables_h#>)



    }


    while((*pp_sentence)->tokens_h != NULL)
    {
    //    if(line_indent == )
        gets(command_string);
        line_indent = get_line_indent_class(TABLE_LEN, command_string);
        *pp_sentence = (struct sentence *)malloc(sizeof(struct sentence));
        (*pp_sentence)->next = NULL;
        *pp_sentence = ((*pp_sentence)->next);
        cut_line(command_string,&((*pp_sentence)->tokens_h));

    }

   // freeall
}


struct token * ass_expression_start(struct token * token_h)
{
    while(token_h != NULL)
    {
        printf("%d\n",token_h->type);
        if(token_h->type == TOKEN_R_ASSIGN)
            return token_h->next;
        token_h = token_h->next;
    }

    return NULL;
}



void execute_sentence(struct token ** p_tokens_list,struct Variable ** p_Variables_h)
{





}


void execute_shell_line(char Command_Line_String[],struct Variable ** p_Variables_h)
{
    struct token * tokens_list = NULL;
    cut_line(Command_Line_String,&tokens_list);


    struct token * p_expression = NULL;
    if(tokens_list != NULL)
    {
        //print_tokens(tokens_list);
        recognize_tokens(tokens_list);
        if(tokens_list->type == TOKEN_R_KEYWD_DEF)
        {

            //function

        }

        else if(tokens_list->type == TOKEN_R_KEYWD_IF)
        {
            while(0)
            {}

        }else if(tokens_list->type == TOKEN_R_KEYWD_ELSE)
        {





        }else if(tokens_list->type == TOKEN_R_KEYWD_WHILE)
        {



        }

        else if((p_expression = ass_expression_start(tokens_list))!= NULL)
        {
            //assignment
            enval_tokens(&p_expression);
            print_tokens(tokens_list);
            variable_append(p_Variables_h,p_expression->revelent_value ,(tokens_list)->token_string);
            //attention : after this function is called, the tokens list is useless because the value is freed.
            print_variables(*p_Variables_h);


        }else
        {
            enval_tokens(&p_expression);
            print_tokens(tokens_list);

        }





        printf("-----------\n");


        //variable_append(p_Variables_h, Op_plus(test_cons1,test_cons2),"test_var_1");


        //print_variables(* p_Variables_h);


    }


    release_all_tokens(&tokens_list);
}




