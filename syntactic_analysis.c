#include "structs.h"
#include "globals.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void print_tokens_tree(struct token * tokens_list)
{
    struct token * p_token = tokens_list;

    if(p_token->type != TOKEN_R_TYPE_VALUE)
        printf("Token: %s\t type: %d \t\tADD:%d \tChild:%d\n",p_token->token_string,p_token->type,p_token,p_token->child);
    else
    {
        switch(p_token->revelent_value->type)
        {
            case VAL_TYPE_INT : printf("Token:[VAL]\t type:(INT)\t:%ld \tADD:%d \tChild:%d\n",*(long *)p_token->revelent_value->value,p_token,p_token->child);break;
            case VAL_TYPE_FLOAT: printf("Token:[VAL]\t type:(FLOAT):%lf \tADD:%d \tChild:%d\n",*(double *)p_token->revelent_value->value,p_token,p_token->child);break;
            case VAL_TYPE_L_FLOAT: printf("Token:[VAL]\t type:(LONG_F):%llf \tADD:%d \tChild:%d\n",*(long double *)p_token->revelent_value->value,p_token,p_token->child);break;
            case VAL_TYPE_STRING: printf("Token:[VAL]\t type:(STR_CON):%s \tADD:%d \tChild:%d\n",(char *)p_token->revelent_value->value,p_token,p_token->child);break;
            default:printf("ERR:unknown constant type!%d\n",(int)p_token->revelent_value->type);
        }

    }
    printf("Next:%d\n",p_token->next);
    //getchar();
    if(tokens_list == NULL)
        printf("Nothing in the tokens list!\n");
    else
    {
        //printf("Token: %s\t type: %c \n",p_token->token_string,p_token->type);//print the first
        if(p_token->child!= NULL)
        {
            p_token=p_token->child;
            while(p_token!=NULL)
            {

                print_tokens_tree(p_token);
                p_token = p_token->next;
            }
        }

    }
}

/*

void print_scentences(struct sentence *  sentence_h)
{
    struct sentence * p_sentence = sentence_h;
    while(p_sentence!= NULL){
        printf("Sentence:\t type: %d\tlineN:%d\t\n",p_sentence->);




    }
}


*/


struct sentence * find_codeblock_end(struct sentence * p_sentence){
    struct sentence * block_end = p_sentence;
    if(p_sentence == NULL || p_sentence->next == NULL)
    {
        printf("ERR:Code Block Error!\n");
        return NULL;
    }
    while (block_end->next != NULL && (block_end->next->indent > p_sentence->indent))
        block_end = block_end->next;
    return block_end;
}

struct sentence * find_if_blok_end(struct sentence * p_sentence){
    struct  sentence * block_end = p_sentence;
    if(p_sentence == NULL || p_sentence->next == NULL){
        printf("ERR:IF Block Error!\n");
        return NULL;
    }

    while(
              block_end->next != NULL &&
                (
                    (block_end->next->indent > p_sentence->indent)||
                    (block_end->next->tokens_h->type == TOKEN_R_KEYWD_ELIF &&  block_end->next->indent == p_sentence->indent)
                )
          )
        block_end = block_end->next;
    while(
              block_end->next != NULL &&
                (
                    (block_end->next->indent > p_sentence->indent)||
                    (block_end->next->tokens_h->type == TOKEN_R_KEYWD_ELSE &&  block_end->next->indent == p_sentence->indent)
                )
          )
        block_end = block_end->next;

    return block_end;
}

void recognize_sentences(struct sentence *  sentence_h){//Set type and jump target
    struct sentence *  p_sentence = sentence_h;
    struct sentence * p_sentence_2 = sentence_h;
    struct sentence * p_sentence_3 = sentence_h;
    struct token * p_token = NULL;
    int i = 1;
    while(p_sentence!= NULL){

        printf("i:%d\n",i);i++;
        p_token = p_sentence->tokens_h;

        if(p_sentence->tokens_h->type==TOKEN_R_KEYWD_WHILE){
            printf("KWD WHILE!\n");

            p_sentence->expression_h = p_sentence->tokens_h->next;
            p_sentence->expression_h->prev = NULL;

            p_sentence_2 = p_sentence->next;
            if(p_sentence_2==NULL)
                printf("For Error!\n");
            else{
                p_sentence_2 = find_codeblock_end(p_sentence);

                p_sentence_2->type = SENTENCE_TYPE_FORCE_JUMP;
                p_sentence_2->jump_target = p_sentence;         //Jump back to loop start (the "for" sentence)

                p_sentence->type = SENTENCE_TYPE_IF_0_JUMP;
                p_sentence->jump_target = p_sentence_2->next;
            }

            p_sentence_2->expression_h = p_sentence_2->tokens_h; //important!! //!!!!!!
            p_sentence_2->expression_h->prev = NULL;

        }else if(p_sentence->tokens_h->type==TOKEN_R_KEYWD_IF){
            printf("KWD IF!\n");

            p_sentence->expression_h = p_sentence->tokens_h->next;
            p_sentence->expression_h->prev = NULL;

            p_sentence_2 = p_sentence->next;
            if(p_sentence_2==NULL)
                printf("IF Error!\n");
            else{
                p_sentence_2 = find_if_blok_end(p_sentence);  //the total "if" segment end
                p_sentence_3 = find_codeblock_end(p_sentence); // the single block end

                while(p_sentence_3!= p_sentence_2){
                    p_sentence_3->type = SENTENCE_TYPE_FORCE_JUMP;
                    p_sentence_3->jump_target = p_sentence_2->next;

                    p_sentence_3 = find_codeblock_end(p_sentence_3);
                }

                p_sentence_2->type = SENTENCE_TYPE_FORCE_JUMP;
                p_sentence_2->jump_target = p_sentence_2->next;

                p_sentence->type = SENTENCE_TYPE_IF_0_JUMP;
                p_sentence->jump_target = p_sentence_2->next;
            }

            p_sentence_2->expression_h = p_sentence_2->tokens_h->next; //important!!!
            p_sentence_2->expression_h->prev = NULL;

        }else if(p_sentence->type == SENTENCE_TYPE_UNRECOGNIZED){   //Normal situation
            printf("NORM!\n");

            p_sentence->expression_h = p_sentence->tokens_h;

            if(p_sentence->next != NULL && p_sentence->indent<p_sentence->next->indent)
                printf("ERR:Indent error!\n");
            else if(p_sentence->next == NULL){
                p_sentence->type = SENTENCE_TYPE_FORCE_JUMP;
                p_sentence->jump_target = NULL;
            }else{
                p_sentence_2 = (find_codeblock_end(p_sentence))->next;
                p_sentence->type = SENTENCE_TYPE_FORCE_JUMP;
                p_sentence->jump_target = p_sentence_2;
            }
        }
        printf("type changed:%d\n",p_sentence->type);
        p_sentence = p_sentence->next;

    }
}











struct token ** get_pp_lbra(struct token ** pp_tokens_h)//find left bracket
{
    struct token * p_token = *pp_tokens_h;

    while( p_token!= NULL&&p_token->type!= TOKEN_R_DIV_L_SBRA )//&& previous and the expression after "&&" can't exchange position
        p_token = p_token->next;

    if(p_token == NULL)
        return NULL;
    else if(p_token->prev == NULL)
        return pp_tokens_h;
    else
        return &(p_token->prev->next);
}

struct token * get_p_multip_div(struct token ** pp_tokens_h)
{
    struct token * p_token = *pp_tokens_h;

    while(
          p_token!= NULL &&
            (
                (p_token->type!= TOKEN_R_OP_MULTI_B &&  p_token->type!= TOKEN_R_OP_DIVD_B) ||
                p_token->child != NULL
            )
          )//&& previous and the expression after "&&" can't exchange position
        p_token = p_token->next;

    return p_token;
}

struct token * get_p_plus_min(struct token ** pp_tokens_h)
{
    struct token * p_token = *pp_tokens_h;

    while(
          p_token!= NULL &&
            (
                (p_token->type!= TOKEN_R_OP_PLUS &&  p_token->type!= TOKEN_R_OP_MINUS) ||
                p_token->child != NULL
            )
          )//&& previous and the expression after "&&" can't exchange position
        p_token = p_token->next;

    return p_token;
}

void creat_ASTree(struct token ** pp_tokens_h)
{
    struct token * p_token = *pp_tokens_h;
    struct token * p_prev_node = NULL;
    struct token ** pp_lbra,pp_rbra;
    int counter = 0;
    struct token * exchanger = NULL;
    struct token * p_lbra,*p_rbra;

    while((pp_lbra = get_pp_lbra(pp_tokens_h))!= NULL)
    {
        p_lbra = *pp_lbra;
        printf("P_LBRA:%d\n",*pp_lbra);
        for(p_token = (*pp_lbra)->next, counter = 1; counter>0;p_token = p_token->next)//to find relevant right bracket
        {
            if(p_token->type == TOKEN_R_DIV_L_SBRA)
                counter ++;
            if(p_token->type == TOKEN_R_DIV_R_SBRA)
                counter --;

            if(counter == 0)//right bracket found
                p_rbra = p_token;
        }

        printf("P_RBRA:%d\n",p_rbra);




        p_rbra->prev->next = NULL;
        p_lbra->next->prev = NULL;
        creat_ASTree(&(p_lbra->next));

        if(p_lbra->prev == NULL){
            *pp_tokens_h = p_lbra->next;
            p_lbra->next->prev = NULL;//set previous
        }else{
            p_lbra->prev->next = p_lbra->next;
            p_lbra->next->prev = p_lbra->prev;//set previous
        }

        p_lbra->next->next=p_rbra->next;
        if(p_rbra->next!=NULL)
            p_rbra->next->prev = p_lbra->next;

        free(p_lbra) ;
        free(p_lbra->token_string);
        free(p_rbra) ;
        free(p_rbra->token_string);
    }

    while((p_token = get_p_multip_div(pp_tokens_h))!= NULL)
    {
        printf("P_MUL/DIV:%d,\tChild:%d\n",p_token,p_token->child);


        if(p_token->prev == NULL)
            printf("ERR:Left of * or / is Nothing!\n");


        p_token->child = p_token->prev;
        if(p_token->prev->prev == NULL)//the first operator of a expression
            *pp_tokens_h = p_token;
        else//not the first operator
            p_token->prev->prev->next = p_token;

        p_token->child->next = p_token->next;

        p_token->next = p_token->child->next->next;
        if(p_token->next!= NULL)//if p_token->next is null, don't have to care
            p_token->next->prev = p_token;//Double side chain

        p_token->child->next->next=NULL;
        p_token->prev = NULL;

        p_token->child->prev = NULL;
        p_token->child->next->prev =  p_token->child;


    }

    while((p_token = get_p_plus_min(pp_tokens_h))!= NULL)
    {
        printf("P_PLU/MIN:%d,\tChild:%d\n",p_token,p_token->child);


        if(p_token->prev == NULL)
            printf("ERR:Left of + or - is Nothing!\n");// "-5"  "+3" not supported


        p_token->child = p_token->prev;
        if(p_token->prev->prev == NULL)//the first operator of a expression
            *pp_tokens_h = p_token;
        else//not the first operator
            p_token->prev->prev->next = p_token;

        p_token->child->next = p_token->next;

        p_token->next = p_token->child->next->next;
        if(p_token->next!= NULL)//if p_token->next is null, don't have to care
            p_token->next->prev = p_token;//Double side chain

        p_token->child->next->next=NULL;
        p_token->prev = NULL;

        p_token->child->prev = NULL;
        p_token->child->next->prev =  p_token->child;


    }




}
