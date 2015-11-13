
#include "structs.h"
#include "globals.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//FILENAME_MAX
char string_line_finished(char * string);
void cut_line(char string[],struct token ** tokens_list,unsigned long line_number);

void block_append(struct sentence ** p_sentence_ins_pos,char * Script_Line,unsigned long line_number)
{
    struct sentence * sentence_ins_pos;
    *p_sentence_ins_pos = (struct sentence *)malloc(sizeof(struct sentence));

    //printf("LNNNNN:%d\n",line_number);

    sentence_ins_pos = *p_sentence_ins_pos;
    sentence_ins_pos->jump_target = NULL;
    sentence_ins_pos->type = SENTENCE_TYPE_UNRECOGNIZED;//unrecognized
    sentence_ins_pos->next = NULL;
    sentence_ins_pos->tokens_h = NULL;
    sentence_ins_pos->indent =  get_line_indent_class(TABLE_LEN,Script_Line);
    sentence_ins_pos->line_number = line_number;

    cut_line(Script_Line,&(sentence_ins_pos->tokens_h),line_number);
    recognize_tokens(sentence_ins_pos->tokens_h);



}


void read_file(const char * file , struct sentence ** p_sentence_h)
{
    FILE * f_pointer;
    struct sentence ** p_sentence_ins_pos = p_sentence_h;
    f_pointer = fopen(file,"r"); // "Fopen" 2 GB max
    char  Script_Line[LINE_LEN] = "";
    unsigned long line_number = 1;


    while(f_get_line(Script_Line, f_pointer))
    {
        //printf("\nScript_line:%s\n",Script_Line);
        block_append(p_sentence_ins_pos,Script_Line,line_number);
        p_sentence_ins_pos=&((*p_sentence_ins_pos)->next);
        line_number ++;
    }


    fclose(f_pointer);
}

int f_get_line(char * Script_Line, FILE * f_pointer)
{
    int string_ins_pos = 0;
    char * ret_fgets = NULL;
    while((ret_fgets = fgets(&(Script_Line[string_ins_pos]),LINE_LEN - 1,f_pointer))!=NULL && !string_line_finished(Script_Line))
    {
        string_ins_pos = strlen(Script_Line);
    }
   // printf("LINE:%s\n",Script_Line);
    return ret_fgets;
}



char string_line_finished(char * string)
{
    int len = strlen(string);
    if(len > LINE_LEN - 3 || len == 0)
    {
        printf("Line ERROR! Check if a single line is too long!\n");
    }
    else
    {

        len --;//len is pointing to \0
        while(len > 0 && (string[len]=='\r'||string[len]=='\n' ))
            len --;

    }
    //printf("LINE_LAST:%c\n",string[len]);
    if(string[len] == '\\')
    {
        string[len] = 0;
        return 0;
    }

    else
        return 1;

}


char tokens_line_finished(struct token * tokens_h)
{
    struct token * p_token = tokens_h;
    int adder = 0;
    while(p_token!=NULL)
    {
        if(p_token->type == TOKEN_R_DIV_L_SBRA)
            adder++;
        else if(p_token->type == TOKEN_R_DIV_R_SBRA)
            adder--;
        p_token = p_token->next;
    }
    if(!adder)
        return 1;
    else
        return 0;
}

void combine_sentences(struct sentence * sentence_h)
{
    struct sentence * p_sentence = sentence_h;
    struct token ** pp_token = NULL;
    while(p_sentence != NULL)
    {
        while(p_sentence->next!= NULL && !tokens_line_finished(p_sentence->tokens_h))
        {
            pp_token = &(p_sentence->tokens_h);
            while(*pp_token!=NULL)
                pp_token = &((*pp_token)->next);

            *pp_token = p_sentence->next->tokens_h;
            p_sentence->next = p_sentence->next->next;
            free(p_sentence->next);
        }
        if(p_sentence->next== NULL && !tokens_line_finished(p_sentence->tokens_h))
        {
            printf("ERR:the script contains unfinished sentences!\n");
        }
        p_sentence = p_sentence->next;
    }
}
