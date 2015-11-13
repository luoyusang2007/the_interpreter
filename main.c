
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <unistd.h>

long int CurrentLine;
char ErrorFlag;
char CurrentNameSpace[256];
char ErrString[256];
////////////////////////////

void read_file(const char * file , struct sentence ** p_sentence_h);
void creat_ASTree(struct token ** pp_tokens_h);
void print_tokens_tree(struct token * tokens_list);
void recognize_sentences(struct sentence *  sentence_h);
void Shell();
void File();



int main()
{
    //Shell();
    File();

    return 0;
}

void start_shell()
{
    printf("\n===============================================================================\n\n");

    printf("     dUTE#=           dEh        TNMM      JMMT  ^EEEEUUL=_    ^##`      `##`\n");
    printf("  .UUUP==7UUUU_      EEEEE        NMML      MM    EEI   `^##L    ##      ##\n");
    printf("  ##*       ^`~     JEE EEL       NM ML     MM    EEI      i#L    ##    ##\n");
    printf("  M=               .EE   EE.      NM  ML    MM    EEI       #M     ##  ##\n");
    printf("  MM               JEEEEEEEL      NM   ML   MM    EEI       #M      ####\n");
    printf("  MM              JEEI^^^IEEL     NM    ML  MM    EEI      j#V       ##\n");
    printf("  ##*        _.   EEE     EEE     NM     ML MM    EEI     .i#'       ##\n");
    printf("  ^EEddL=JbEEE^   EEE     EEE     NM      MLMM    EEI  _.##V^        ##\n");
    printf("     iP###P      ;EEL     JEE:   JNNL      MMML  _EEUEUV=^          .##_\n");
    printf("\n===============================================================================\n");
    printf("      Candy Can V1.0                                              Bits:%d \n",sizeof(void *)*8);
    printf("                                                             Rain&Sun 2015\n");
    printf("===============================================================================\n\n");


}

void throw_err(char Err[])
{
    puts(Err);
}


void Shell()
{
    start_shell();
    char Command_Line_String[512];
    char Err[512]="";

    struct Variable * Variables_h = NULL;

    while(1)
    {
        printf(">>>");
        gets(Command_Line_String);

        execute_shell_line(Command_Line_String,&Variables_h);

    }
}

void File()
{
    struct sentence * sentence_h = NULL;
    struct Variable * variables_h = NULL;
    read_file("test.txt",&sentence_h);
    struct sentence * p_sentence = sentence_h;

    combine_sentences(sentence_h);

    char path_buffer[256];
    getcwd(path_buffer, 255);
    printf("%s\n",path_buffer);

    recognize_sentences(sentence_h);

    int i = 1;
    while(p_sentence!= NULL)
    {

        //printf("== Sentence   : =======================\n");
        printf("\nSentence:%d\tIndent:%d\n",p_sentence,p_sentence->indent);
        printf("Type: %d\tLineN:%d\tJump:%d\tNext:%d\n",p_sentence->type,p_sentence->line_number,p_sentence->jump_target,p_sentence->next);



        printf("== Exp Tokens List: ====================\n");
        print_tokens(p_sentence->expression_h);

        creat_ASTree(&(p_sentence->expression_h));

        printf("== Tokens Tree: =======================\n");
        print_tokens_tree(p_sentence->expression_h);

        printf("== Evaluate:    =======================\n");
        eval_expression(p_sentence->expression_h );

        p_sentence = p_sentence->next;
        //getchar();
        i++;
    }
}
